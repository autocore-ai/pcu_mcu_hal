/******************************************************************
FileName   :mx25L6406e.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-31
****************************************************************/

#include    "hardware.h"

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
        UartSendString(sciREG1," Nor Flash is : SST25VF080B    \r\n\0");
        UartSendString(sciREG1,"                manufacturer ID = 0xBF \r\n\0");
        UartSendString(sciREG1,"                memory type     = 0x25 \r\n\0");
        UartSendString(sciREG1,"                memory capacity = 0x17 \r\n\0");
#endif
        val++;
    }
    temp = NorReadMID();
    if (temp == SST25VF080B_ID)
    {
#if (DEBUG)
        UartSendString(sciREG1,"                device ID = 0xBF8E \r\n\0");
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
    uint16   cmd = 0x0006;
    SpiWrite(spiREG2, &cmd, 1);
}

/******************************************************
*Name    :  NorWriteEnable
*Function:  nor write enable
*Return  :  void
*******************************************************/
void    NorWriteDisable(void)
{
    uint16   cmd = 0x0004;
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
    uint16  cmd = 0x0005;
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
    cmd[0] = 0x0001;
    cmd[1] = val;
    while(NorReadStatus() & WIP);
    NorWriteEnable();
    SpiWrite(spiREG2, cmd, 2);
}


/******************************************************
*Name    :  NorReadID
*Function:  read  id
*Params  :
*Return  :  DEVICE ID  (0xC22017)
*******************************************************/
uint32    NorReadID(void)
{
    uint16  cmd = 0x9F;
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

    cmd[0] = 0x0090;
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

    cmd[0] = 0x0003;
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
*Return  :
*******************************************************/
uint8   NorFastRead(uint32 addr,uint16 *buf, uint16 size)
{
    uint16  cmd[5];
    uint32  temp;

    cmd[0] = 0x000b;
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
    while(NorReadStatus() & WIP);
    do{
        NorWriteEnable();
        j = NorReadStatus() & WEL;
    }while(!j);

    addr = sector * SECTORSIZE - 1;
    cmd[0] = 0x0020;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWrite(spiREG2, cmd, 4);

    while(NorReadStatus() & WIP);
    j = NorReadStatus() & WEL;

    addr = sector * SECTORSIZE - 1;
    for(j=0;j<SECTORSIZE/NORBUFSIZE;j++)
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
uint8   NorBlockErase(uint8 block)
{
    uint16  cmd[4];
    uint32  addr;
    uint16  j;
    uint16  i;
    while(NorReadStatus() & WIP);

    do{
        NorWriteEnable();
        j = NorReadStatus() & WEL;
    }while(!j);

    addr = block * BLOCKSIZE - 1;
    cmd[0] = 0x0052;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWrite(spiREG2, cmd, 4);

    while(NorReadStatus() & WIP);
    j = NorReadStatus() & WEL;

    addr = block * BLOCKSIZE - 1;
    for(j=0;j<BLOCKSIZE/NORBUFSIZE;j++)
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

    while(NorReadStatus() & WIP);

    do{
        NorWriteEnable();
        i = NorReadStatus() & WEL;
    }while(!i);


    cmd = 0x0060;
    SpiWrite(spiREG2, &cmd, 1);

    while(NorReadStatus() & WIP);
    i = NorReadStatus() & WEL;

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
*Name    : NorChipErase
*Function: nor flash 擦除函数
*Params  : page : flash 页号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorPageWrite(uint16 page, uint16 *buf)
{
    uint16  cmd[4];
    uint16  i;
    uint32  addr;
    do{
        NorWriteEnable();
        i = NorReadStatus() & WEL;
    }while(!i);

    addr = page * PAGESIZE;
    cmd[0] = 0x0002;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,buf,PAGESIZE);

    while(NorReadStatus() & WIP);
    i = NorReadStatus() & WEL;

    NorFastRead(addr, NorBuf, PAGESIZE);

    for(i=0;i<PAGESIZE;i++)
    {
        if(NorBuf[i] != buf[i])
            return 0;
    }

    return 1;
}

/******************************************************
*Name    : NorWriteByte
*Function: nor flash 写字节函数
*Params  : addr : 地址
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorWriteByte(uint32 addr, uint16 data)
{
    uint16  cmd[4];
    uint16  i;

    while(NorReadStatus() & WIP);

    do{
        NorWriteEnable();
        i = NorReadStatus() & WEL;
    }while(!i);

    cmd[0] = 0x0002;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,&data,1);

    while(NorReadStatus() & WIP);
    i = NorReadStatus() & WEL;

    i = NorReadByte(addr);

    if(i != data)
        return 0;
    return 1;
}

/******************************************************
*Name    : NorWriteAuto
*Function: nor flash 连续写数据函数
*Params  : addr : flash 地址
*Params  : buf  数据缓冲区
*Params  : len 数据长度,长度必须为偶数
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorWriteAuto(uint32 addr, uint16 *buf,uint16 len)
{
    uint16  cmd[4];
    uint16  i;
    uint16  dat[2];
    while(NorReadStatus() & WIP);

    do{
        NorWriteEnable();
        i = NorReadStatus() & WEL;
    }while(!i);

    cmd[0] = 0x00AD;
    cmd[1] = (uint16)((addr & 0x00FF0000) >> 16);
    cmd[2] = (uint16)((addr & 0x0000FF00) >> 8);
    cmd[3] = (uint16)((addr & 0x000000FF) >> 0);
    SpiWriteData(spiREG2,cmd,4,buf,2);


    for(i=0;i<(len-2)/2;i++)
    {
        while(NorReadStatus() & WIP);

        dat[0] = buf[i*2 + 2];
        dat[1] = buf[i*2 + 3];
        SpiWriteData(spiREG2,cmd,1,dat,2);
    }
    NorWriteDisable();

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

void    NorTest(void)
{
    uint16  i;
    uint16  dat[9] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    uint16  dat1[9] = {0};
    i = NorReadStatus();
    NorWriteStatus(0x0);


    if(NorChipErase())
        UartSendString(sciREG1," Chip erase sucess ! \n\r\0");
    for(i=0;i<9;i++)
        NorWriteByte(0x50+i,dat[i]);
    for(i=0;i<9;i++)
        dat1[i] = NorReadByte(0x50+i);
    for(i=0;i<9;i++)
    {
        if(dat[i] != dat1[i])
        {
            UartSendString(sciREG1," Nor flash write and read fail ! \n\r\0");
            while(1);
        }
    }
    UartSendString(sciREG1," NorFlash read and write is OK ! \n\r\0");
}
