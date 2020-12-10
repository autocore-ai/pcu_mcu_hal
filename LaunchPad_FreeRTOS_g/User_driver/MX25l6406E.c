/******************************************************************
FileName   :mx25L6406e.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-31
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"

#include    "hardware.h"

extern  uint8 emacAddress[6U];
extern  uint8_t ucIPAddress[4];
extern  uint8_t ucGatewayAddress[4];
extern  uint8_t ucDNSServerAddress[4];
extern  uint8_t remoteIPAddress[4];
uint16  NorBuf[NORBUFSIZE];

/******************************************************
*Name    :  FreeRTOS_NorInit
*Function:  Nor Flash  初始化函数
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/
uint8    FreeRTOS_NorInit(void)
{
    uint32  temp;
    uint8   val = 0;
    Spi2Init();
    temp = NorReadID();
    if (temp == SST25VF080B)
    {
#if  (DEBUG)
        UartSendString(sciREG4," Nor Flash is : SST25VF080B    \r\n\0");
        UartSendString(sciREG4,"                manufacturer ID = 0xBF \r\n\0");
        UartSendString(sciREG4,"                memory type     = 0x25 \r\n\0");
        UartSendString(sciREG4,"                memory capacity = 0x17 \r\n\0");
#endif
        val++;
    }
    temp = NorReadMID();
    if (temp == SST25VF080B_ID)
    {
#if (DEBUG)
        UartSendString(sciREG4,"                device ID = 0xBF8E \r\n\0");
#endif
        val++ ;
    }
    if (val == 2)
        return 1;
    else
        return 0;
}

/******************************************************
*Name    :  NorWriteEnable
*Function:  nor write enable
*Return  :  void
*******************************************************/
void    NorWriteEnable(void)
{
    uint16  cmd = WREN;
    SpiWrite(spiREG2, &cmd, 1);
}

/******************************************************
*Name    :  NorWriteEnable
*Function:  nor write enable
*Return  :  void
*******************************************************/
void    NorWriteDisable(void)
{
    uint16   cmd = WRDI;
    SpiWrite(spiREG2, &cmd, 1);
}

/******************************************************
*Name    :  NorReadStatus
*Function:  read status reg
*Params  :
*Return  :  状态值
*******************************************************/
uint8    NorReadStatus(void)
{
    uint16  cmd = RDSR;
    uint16  status = 0;
    uint32  temp;
    temp = SpiRead(spiREG2,&cmd,1,&status,1);
    if (temp & 0xFF)
        return 0;
    else
        return (uint8)status;
}

/******************************************************
*Name    :  NorWriteStatus
*Function:  Write status reg
*Params  :  val : 要写人状态寄存器的值
*Return  :  void
*******************************************************/
void    NorWriteStatus(uint16 val)
{
    uint16  cmd[2];
    cmd[0] = WRSR;
    cmd[1] = val;
    while(NorReadStatus() & SST_BUSY);
    NorWriteEnable();
    SpiWrite(spiREG2, cmd, 2);
}

/******************************************************
*Name    :  NorWriteAutoDisable
*Function:  nor write auto stop
*Return  :  void
*******************************************************/
void    NorWriteAutoDisable(void)
{
    uint16   cmd = DBSY;
    SpiWrite(spiREG2, &cmd, 1);
}

/******************************************************
*Name    :  NorWriteAutoEnable
*Function:  nor write auto enable
*Return  :  void
*******************************************************/
void    NorWriteAutoEnable(void)
{
    uint16   cmd = EBSY;
    SpiWrite(spiREG2, &cmd, 1);
}

/******************************************************
*Name    :  NorReadID
*Function:  read  id
*Params  :
*Return  :  DEVICE ID  (0xC22017)
*******************************************************/
uint32    NorReadID(void)
{
    uint16  cmd = JEDEC_ID;
    uint16  id[3];
    uint32  temp;
    temp = SpiRead(spiREG2,&cmd,1,id,3);
    if (temp & 0xFF)
        return 0;
    temp = ((uint32)(id[0]<<16)) | ((uint32)(id[1]<<8)) | ((uint32)id[2]);
    return temp;
}

/******************************************************
*Name    :  NorReadID
*Function:  read  id
*Params  :
*Return  :  状态值
*******************************************************/
uint32    NorReadMID(void)
{
    uint16  cmd[4];
    uint16  id[2];
    uint32  temp;

    cmd[0] = RDID;
    cmd[1] = 0x0000;
    cmd[2] = 0x0000;
    cmd[3] = 0x0000;

    temp = SpiRead(spiREG2,cmd,4,id,2);
    if (temp & 0xFF)
        return 0;
    temp = (uint32)(id[0]<<8) | (uint32)id[1] ;
    return temp;
}

/******************************************************
*Name    : NorReadByte
*Function: nor flash 读字节函数（从addr地址读一个字节数据）
*Params  :
*Return  : 字节内容
*******************************************************/
uint8   NorReadByte(uint32 addr)
{
    uint16  cmd[4];
    uint16  val;
    uint32  temp;

    cmd[0] = READ;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    temp = SpiRead(spiREG2,cmd,4,&val,1);
    if (temp & 0xFF)
        return 0;
    else
        return (uint8)val;

}

/******************************************************
*Name    : NorFastRead
*Function: nor flash 读字节函数（从addr地址读size字节数据,放到 buf中）
*Params  : addr : flash 地址
*Params  : buf  : 数据缓冲区
*Params  : size : 要读取数据的大小
*Return  : 本次读操作状态  0--失败       1--成功
*******************************************************/
uint8   NorFastRead(uint32 addr,uint16 *buf, uint16 size)
{
    uint16  cmd[5];
    uint32  temp;

    cmd[0] = HIGH_SPEED_READ;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    cmd[4] = 0x0000;
    temp = SpiRead(spiREG2,cmd,5,buf,size);
    if (temp & 0xFF)
        return 0;
    else
        return 1;
}

/******************************************************
*Name    : NorSectorErase
*Function: nor flash 扇区擦除函数
*Params  : sector : flash 扇区号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorSectorErase(uint16 sector)
{
    uint16  cmd[4];
    uint32  addr;
    uint16  j;
    uint16  i;
    while(NorReadStatus() & SST_BUSY);
    NorWriteStatus(0x00);
    do{
        NorWriteEnable();
        j = NorReadStatus() & SST_WEL;
    }while(!j);

    addr = sector * SECTORSIZE_4K ;
    cmd[0] = SECTOR_ERASE_4K;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWrite(spiREG2, cmd, 4);

    while(NorReadStatus() & SST_BUSY);
    j = NorReadStatus() & SST_WEL;

    addr = sector * SECTORSIZE_4K;
    for(j=0;j<SECTORSIZE_4K/NORBUFSIZE;j++)
    {
        addr = addr + j * NORBUFSIZE;
        NorFastRead(addr, NorBuf, NORBUFSIZE);
        for(i=0;i<NORBUFSIZE;i++)
        {
            if(NorBuf[i] !=0x00FF)
                return 0;
        }
    }
    return 1;
}

/******************************************************
*Name    : NorBlockErase
*Function: nor flash 块擦除函数
*Params  : block : flash 块号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorBlockErase_32K(uint8 block)
{
    uint16  cmd[4];
    uint32  addr;
    uint16  j;
    uint16  i;
    while(NorReadStatus() & SST_BUSY);

    NorWriteStatus(0x00);

    do{
        NorWriteEnable();
        j = NorReadStatus() & SST_WEL;
    }while(!j);

    addr = block * BLOCKSIZE_32K;
    cmd[0] = BLOCK_ERASE_32K;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWrite(spiREG2, cmd, 4);

    while(NorReadStatus() & SST_BUSY);
    j = NorReadStatus() & SST_WEL;

    addr = block * BLOCKSIZE_32K;
    for(j=0;j<BLOCKSIZE_32K/NORBUFSIZE;j++)
    {
        addr = addr + j * NORBUFSIZE;
        NorFastRead(addr, NorBuf, NORBUFSIZE);
        for(i=0;i<NORBUFSIZE;i++)
        {
            if(NorBuf[i] !=0x00FF)
                return 0;
        }
    }
    return 1;
}

/******************************************************
*Name    : NorBlockErase
*Function: nor flash 块擦除函数
*Params  : block : flash 块号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorBlockErase_64K(uint8 block)
{
    uint16  cmd[4];
    uint32  addr;
    uint16  j;
    uint16  i;
    while(NorReadStatus() & SST_BUSY);

    NorWriteStatus(0x00);

    do{
        NorWriteEnable();
        j = NorReadStatus() & SST_WEL;
    }while(!j);

    addr = block * BLOCKSIZE_64K;
    cmd[0] = BLOCK_ERASE_64K;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWrite(spiREG2, cmd, 4);

    while(NorReadStatus() & SST_BUSY);
    j = NorReadStatus() & SST_WEL;

    addr = block * BLOCKSIZE_64K;
    for(j=0;j<BLOCKSIZE_64K/NORBUFSIZE;j++)
    {
        addr = addr + j * NORBUFSIZE;
        NorFastRead(addr, NorBuf, NORBUFSIZE);
        for(i=0;i<NORBUFSIZE;i++)
        {
            if(NorBuf[i] !=0x00FF)
                return 0;
        }
    }
    return 1;
}

/******************************************************
*Name    : NorChipErase
*Function: nor flash 擦除函数
*Params  :
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorChipErase(void)
{
    uint16  cmd;
    uint32  addr;
    uint32  j;
    uint16  i;

    while(NorReadStatus() & SST_BUSY);

    NorWriteStatus(0x00);

    do{
        NorWriteEnable();
        i = NorReadStatus() & SST_WEL;
    }while(!i);


    cmd = CHIP_ERASE;
    SpiWrite(spiREG2, &cmd, 1);

    while(NorReadStatus() & SST_BUSY);
    i = NorReadStatus() & SST_WEL;

    addr = 0;
    for(j=0;j<CHIPSIZE/NORBUFSIZE;j++)
    {
        addr = addr + j * NORBUFSIZE;
        NorFastRead(addr, NorBuf, NORBUFSIZE);
        for(i=0;i<NORBUFSIZE;i++)
        {
            if(NorBuf[i] !=0x00FF)
                return 0;
        }
    }
    return 1;
}
/******************************************************
*Name    : NorWriteByte
*Function: nor flash 写字节函数
*Params  : addr : 地址
*Return  : 本次写操作状态      0---失败    1---成功
*******************************************************/
uint8   NorWriteByte(uint32 addr, uint16 data)
{
    uint16  cmd[4];
    uint16  i;

    while(NorReadStatus() & SST_BUSY);

    NorWriteStatus(0x00);

    do{
        NorWriteEnable();
        i = NorReadStatus() & SST_WEL;
    }while(!i);

    cmd[0] = BYTE_PROGRAM;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,&data,1);

    while(NorReadStatus() & SST_BUSY);
    i = NorReadStatus() & SST_WEL;

    i = NorReadByte(addr);

    if(i != data)
        return 0;
    return 1;
}


/******************************************************
*Name    : NorPageWrite
*Function: nor flash 页写
*Params  : page : flash 页号
*Return  : 本次写操作状态    0---失败    1---成功
*******************************************************/
uint8   NorPageWrite(uint16 page, uint16 *buf)
{
    uint16  i;
    uint32  addr;

    addr = page * PAGESIZE;

    for(i=0;i<PAGESIZE;i++)
    {
        NorWriteByte(addr, buf[i]);
        addr++;
    }
    return 1;
}

/******************************************************
*Name    : NorPageRead
*Function: nor flash 页读
*Params  : page : flash 页号
*Return  : 0---失败    1---成功
*******************************************************/
uint8   NorPageRead(uint16 page, uint16 *buf)
{
    uint16  i;
    uint32  addr;

    addr = page * PAGESIZE;

    for(i=0;i<PAGESIZE;i++)
    {
        buf[i] = NorReadByte(addr);
        addr++;
    }
    return 1;
}

/******************************************************
*Name    : NorWriteAuto
*Function: nor flash 连续写数据函数
*Params  : addr : flash 地址
*Params  : buf  数据缓冲区
*Params  : len 数据长度,长度必须为偶数
*Return  : 本次写操作状态    0---失败    1---成功
*******************************************************/
uint8   NorWriteAuto(uint32 addr, uint16 *buf,uint16 len)
{
    uint16  cmd[4];
    uint16  i;
    uint16  dat[2];
    while(NorReadStatus() & SST_BUSY);

    NorWriteStatus(0x00);

    NorWriteAutoEnable();

    do{
        NorWriteEnable();
        i = NorReadStatus() & SST_WEL;
    }while(!i);


    cmd[0] = AAI_WORD_PROGRAM;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,buf,2);


    for(i=0;i<(len-2)/2;i++)
    {
        while(NorReadStatus() & SST_BUSY);

        dat[0] = buf[i*2 + 2];
        dat[1] = buf[i*2 + 3];
        SpiWriteData(spiREG2,cmd,1,dat,2);
    }
    NorWriteDisable();
    NorWriteAutoDisable();
    i = NorReadStatus() & SST_WEL;

    if (len > PAGESIZE)
    {
        do{
            NorFastRead(addr, NorBuf, PAGESIZE);
            for(i=0;i<PAGESIZE;i++)
            {
                if(NorBuf[i] != buf[i])
                    return 0;
            }
            addr = addr - PAGESIZE;
            len = len - PAGESIZE;
        }while(len-PAGESIZE > 0);

        NorFastRead(addr, NorBuf, len);
        for(i=0;i<PAGESIZE;i++)
        {
            if(NorBuf[i] != buf[i])
                return 0;
        }
    }
    else
    {
        NorFastRead(addr, NorBuf, len);
        for(i=0;i<PAGESIZE;i++)
        {
            if(NorBuf[i] != buf[i])
                return 0;
        }
    }
    return 1;
}

/******************************************************
*Name    : NorPageWrite
*Function: nor flash 擦除函数
*Params  : page : flash 页号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorPageWrite1(uint16 page, uint16 *buf)
{
    uint16  cmd[4];
    uint16  i;
    uint16  dat[2];
    uint32  addr;
    uint32  timeout;
    addr = page * PAGESIZE;

    NorWriteStatus(0x00);

    NorWriteAutoEnable();

    NorWriteEnable();


    cmd[0] = AAI_WORD_PROGRAM;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,buf,2);


    for(i=0;i<(PAGESIZE-2)/2;i++)
    {
        while(NorReadStatus() & SST_BUSY);

        dat[0] = buf[i*2 + 2];
        dat[1] = buf[i*2 + 3];
        SpiWriteData(spiREG2,cmd,1,dat,2);
    }

    NorWriteDisable();
    NorWriteAutoDisable();
    timeout = 0;
    while(NorReadStatus() & SST_BUSY)
    {
        if(timeout++ > 65536)
            break;
        timeout = timeout;
    }

    return 1;
}

/******************************************************
*Name    : SetIpMac
*Function: 设置MCU IP地址和MAC地址
*******************************************************/
void    SetIpMac(void)
{
    uint16 NorFlagBuf[PAGESIZE];
    uint16 NorDataBuf[PAGESIZE];
    uint8  dat[16];
    uint32  mask;
    uint8   i;
    taskENTER_CRITICAL();
    NorFastRead(NORFLAGPAGE * PAGESIZE, NorFlagBuf,PAGESIZE);
    NorFastRead(NORDATAPAGE * PAGESIZE, NorDataBuf,PAGESIZE);
    mask = (uint32)(NorFlagBuf[IPOFFSET + 0] << 24) |
           (uint32)(NorFlagBuf[IPOFFSET + 1] << 16) |
           (uint32)(NorFlagBuf[IPOFFSET + 2] << 8 ) |
           (uint32)(NorFlagBuf[IPOFFSET + 3] ) ;
    if(mask == IPMASK)
    {
        ucIPAddress[0] = (uint8)(NorDataBuf[IPOFFSET + 0]);
        ucIPAddress[1] = (uint8)(NorDataBuf[IPOFFSET + 1]);
        ucIPAddress[2] = (uint8)(NorDataBuf[IPOFFSET + 2]);
        ucIPAddress[3] = (uint8)(NorDataBuf[IPOFFSET + 3]);

        for(i=0;i<3;i++)
        {
            ucGatewayAddress[i] = ucIPAddress[i];
            ucDNSServerAddress[i] = ucIPAddress[i];
        }
    }

    mask = (uint32)(NorFlagBuf[MACOFFSET + 0] << 24) |
           (uint32)(NorFlagBuf[MACOFFSET + 1] << 16) |
           (uint32)(NorFlagBuf[MACOFFSET + 2] << 8 ) |
           (uint32)(NorFlagBuf[MACOFFSET + 3] ) ;

    if(mask == MACMASK)
    {
        emacAddress[0] = (uint8)(NorDataBuf[MACOFFSET + 0]);
        emacAddress[1] = (uint8)(NorDataBuf[MACOFFSET + 1]);
        emacAddress[2] = (uint8)(NorDataBuf[MACOFFSET + 2]);
        emacAddress[3] = (uint8)(NorDataBuf[MACOFFSET + 3]);
        emacAddress[4] = (uint8)(NorDataBuf[MACOFFSET + 4]);
        emacAddress[5] = (uint8)(NorDataBuf[MACOFFSET + 5]);
    }

    FUNC_IIC(page_read)(dat,REMOTEIP,16);

    mask = (uint32)(dat[0]  << 24)|
           (uint32)(dat[1]  << 16)|
           (uint32)(dat[2]  << 8 )|
           (uint32)(dat[3]  );

    if(mask == IPREMOTEMASK)
    {

        remoteIPAddress[0] = dat[8];
        remoteIPAddress[1] = dat[9];
        remoteIPAddress[2] = dat[10];
        remoteIPAddress[3] = dat[11];
    }

    taskEXIT_CRITICAL();

    UartSendString(sciREG4," \r\n MCU IP    : \0");
    for(i=0;i<4;i++)
    {
        UartSendByte(sciREG4,ucIPAddress[i]);
        if(i!=3)
            UartSendString(sciREG4,".\0");
        else
            UartSendString(sciREG4,"\r\n\0");
    }

    UartSendString(sciREG4," MCU MAC   : \0");
    for(i=0;i<6;i++)
    {
        UartSendMac(sciREG4,emacAddress[i]);
        if(i!=5)
            UartSendString(sciREG4,":\0");
        else
            UartSendString(sciREG4,"\r\n\0");
    }

    UartSendString(sciREG4," REMOTE IP : \0");
    for(i=0;i<4;i++)
    {
        UartSendByte(sciREG4,remoteIPAddress[i]);
        if(i!=3)
            UartSendString(sciREG4,".\0");
        else
            UartSendString(sciREG4,"\r\n\r\n\0");
    }

}

void    NorTest(void)
{
    uint16  i;
    uint16  NorBuf[PAGESIZE];

    NorPageRead(NORFLAGPAGE ,NorBuf);

    for(i=0;i<PAGESIZE;i++)
        NorBuf[i] = i;

    NorSectorErase(DATASECTOR);

    NorPageWrite(NORFLAGPAGE, NorBuf);

    for(i=0;i<PAGESIZE;i++)
        NorBuf[i] = 0;

    NorFastRead(NORFLAGPAGE * PAGESIZE, NorBuf,PAGESIZE);

}
