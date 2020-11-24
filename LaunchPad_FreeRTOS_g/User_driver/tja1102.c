/******************************************************************
FileName   :tja1102.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-28
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_sys_common.h"
#include "HL_gio.h"
#include "HL_sci.h"
#include "HL_mdio.h"
#include "hardware.h"

#define     MDC         0
#define     MDIO        1
#define     DIR_IN      0
#define     DIR_OUT     1
#define     LOW         0
#define     HIGH        1

#define     HWVER3      1


void gioSetDir(gioPORT_t *port, uint8 bit, uint8 dir)
{
    uint32  tmp;
    tmp = port->DIR;
    if(dir)
    {
        tmp |= (uint32)(1 << bit);
    }
    else
    {
        tmp &= (uint32)(~((uint8)(1 << bit)));
    }
    port->DIR = tmp;
}

/******************************************************
*Name    :  PhyRead
*Function:  读 PHY 寄存器函数
*Params  :  phyaddr : PHY 地址
*Params  :  phyreg  : PHY 寄存器地址
*Return  :  读取的 PHY 寄存器的值
*******************************************************/
uint16    PhyRead_io(uint8 phyaddr,uint8   phyreg)
{
    uint8   i;
    uint16   frame = 0x06;
    gioSetDir(gioPORTB,MDC,DIR_OUT);
    gioSetDir(gioPORTB,MDIO,DIR_OUT);
    DelayUs(1);
    gioSetBit(gioPORTB,MDC,LOW);
    gioSetBit(gioPORTB,MDIO,LOW);
    DelayUs(1);

//------preamble---------------------------------------
    for(i=0;i<32;i++)
    {
        gioSetBit(gioPORTB,MDIO,HIGH);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//--------start & op code --------------------------------
    for(i=0;i<4;i++)
    {

        if( (frame >> (3-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//------------phyaddr-------------------------------
    frame = phyaddr;
    for(i=0;i<5;i++)
    {
        if( (frame >> (4-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//-------------phyreg-----------------------------
    frame = phyreg;
    for(i=0;i<5;i++)
    {
        if( (frame >> (4-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//------------turn around --------------------------
    gioSetDir(gioPORTB,MDIO,DIR_IN);
    Delayns();
    gioSetBit(gioPORTB,MDC,HIGH);
    DelayNs(1);
    gioSetBit(gioPORTB,MDC,LOW);
    DelayNs(1);

    frame = 0;
//------------read-------------------
    for(i=0;i<16;i++)
    {

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        frame = frame << 1;
        frame |=(uint16)gioGetBit(gioPORTB,MDIO);
        DelayNs(1);
    }

    return frame;
}

/******************************************************
*Name    :  PhyWrite
*Function:  写 PHY 寄存器函数
*Params  :  phyaddr : PHY 地址
*Params  :  phyreg  : PHY 寄存器地址
*Params  :  data    : 要写入的数据
*******************************************************/

void    PhyWrite_io(uint8 phyaddr,uint8   phyreg, uint16 data)
{
    uint8   i;
    uint16   frame = 0x05;
    gioSetDir(gioPORTB,MDC,DIR_OUT);
    gioSetDir(gioPORTB,MDIO,DIR_OUT);
    DelayUs(1);
    gioSetBit(gioPORTB,MDC,LOW);
    gioSetBit(gioPORTB,MDIO,LOW);
    DelayUs(1);

//------preamble---------------------------------------
    for(i=0;i<32;i++)
    {
        gioSetBit(gioPORTB,MDIO,HIGH);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//--------start & op code --------------------------------
    for(i=0;i<4;i++)
    {

        if( (frame >> (3-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//------------phyaddr-------------------------------
    frame = phyaddr;
    for(i=0;i<5;i++)
    {
        if( (frame >> (4-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//-------------phyreg-----------------------------
    frame = phyreg;
    for(i=0;i<5;i++)
    {
        if( (frame >> (4-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }

//------------turn around --------------------------
    frame = 0x2;
    for(i=0;i<2;i++)
    {
        if( (frame >> (1-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
//------------read-------------------
    frame = data;
    for(i=0;i<16;i++)
    {
        if( (frame >> (15-i)) & 0x1)
            gioSetBit(gioPORTB,MDIO,HIGH);
        else
            gioSetBit(gioPORTB,MDIO,LOW);
        Delayns();

        gioSetBit(gioPORTB,MDC,HIGH);
        DelayNs(1);
        gioSetBit(gioPORTB,MDC,LOW);
        DelayNs(1);
    }
}


/******************************************************
*Name    :  PhyWrite
*Function:  写 PHY 寄存器函数
*Params  :  phyaddr : PHY 地址
*Params  :  phyreg  : PHY 寄存器地址
*Params  :  data    : 要写入的数据
*******************************************************/
void    PhyWrite(uint8 phyaddr,uint8   phyreg, uint16 data)
{
    #if (HWVER3)
        MDIOPhyRegWrite(MDIO_BASE,phyaddr,phyreg,data);
    #else
        PhyWrite_io(phyaddr,phyreg, data);
    #endif
}
/******************************************************
*Name    :  PhyRead_io
*Function:  读 PHY 寄存器函数
*Params  :  phyaddr : PHY 地址
*Params  :  phyreg  : PHY 寄存器地址
*Return  :  读取的 PHY 寄存器的值
*******************************************************/
uint16    PhyRead(uint8 phyaddr,uint8   phyreg)
{
    uint16  value;
    #if (HWVER3)
        MDIOPhyRegRead(MDIO_BASE,phyaddr,phyreg,&value);
    #else
        value = PhyRead_io(phyaddr, phyreg);
    #endif
    return value;
}

/******************************************************
*Name    :  ReadPhyID
*Function:  读 PHY ID 函数
*Params  :  phyAddr : PHY 地址
*Return  :  32位 ID号
*******************************************************/

uint32 ReadPhyID(uint8 phyAddr)
{
    uint32 id = 0U;
    uint16 data = 0U;
    data = PhyRead( phyAddr, (uint8)PHY_ID1);
    id = (uint32)data;
    id = (uint32)((uint32)id << PHY_ID_SHIFT);
    data = PhyRead(phyAddr, (uint8)PHY_ID2);
    id |= data;
    return id;
}

/******************************************************
*Name    :  Phy_init
*Function:  PHY 初始化函数
*Params  :  phyAddr : PHY 地址
*Return  :  0 表示初始化失败， 1 表示成功
*******************************************************/
uint8 Phy_init(uint32 phyAddr)
{
    uint16  temp;
    uint32  id;
    id = ReadPhyID(phyAddr);
#if (DEBUG)

    UartSendString(sciREG4,"\r\n\0");

     if (id == NXP_PHY_ID_TJA1102S)
     {
         UartSendString(sciREG4," TJA1102S Device ID :  \0");
         UartSendHexU32(sciREG4,id);
         UartSendString(sciREG4,"\r\n\0");
     }
     else if(id ==NXP_PHY_ID_TJA1102P0 )
     {
         UartSendString(sciREG4," TJA1102 Device ID :  \0");
         UartSendHexU32(sciREG4,id);
         UartSendString(sciREG4,"\r\n\0");
     }

#endif

    if((id == NXP_PHY_ID_TJA1102P0 ) || (id == NXP_PHY_ID_TJA1102S))
    {

        PhyWrite(phyAddr,PHY_ECR,0x9804);

        temp = PhyRead(phyAddr,PHY_COM_CR);
        temp |= (uint16)(1<<15);
        PhyWrite(phyAddr,PHY_COM_CR,temp);      //auto_op = 1;

        PhyWrite(phyAddr,PHY_INT_EN ,0x8E00);

        PhyWrite(phyAddr,PHY_ECR,0x9800);

        PhyWrite(phyAddr+1,PHY_ECR,0x9804);

        PhyWrite(phyAddr+1,PHY_INT_EN ,0x8E00);

        PhyWrite(phyAddr+1,PHY_ECR,0x9800);

    }


    temp = PhyRead(phyAddr,PHY_CR1);
    if ((temp & 0x8000) && (temp !=0xFFFF))
        UartSendString(sciREG4," P0 configure as  :  Master \r\n\0");
    else
        UartSendString(sciREG4," P0 configure as  :  Slave  \r\n\0");

    temp = PhyRead(phyAddr,PHY_BSR);
    if ((temp & 0x0004)&& (temp !=0xFFFF))
        UartSendString(sciREG4," P0 link status   :  Up \r\n\0");
    else
        UartSendString(sciREG4," P0 link status   :  Down \r\n\0");

    temp = PhyRead(phyAddr,PHY_COM_SR);
    UartSendString(sciREG4," P0 reg23 value   :  \0");
    UartSendHexU16(sciREG4,temp);
    UartSendString(sciREG4,"\r\n\0");

    UartSendString(sciREG4,"\r\n\0");

    if( id == NXP_PHY_ID_TJA1102P0 )
    {
        temp = PhyRead(phyAddr+1,PHY_CR1);

        if ((temp & 0x8000) && (temp !=0xFFFF))
            UartSendString(sciREG4," P1 configure as  :  Master \r\n\0");
        else
            UartSendString(sciREG4," P1 configure as  :  Slave  \r\n\0");

        temp = PhyRead(phyAddr+1,PHY_BSR);
        if ((temp & 0x0004) && (temp !=0xFFFF))
            UartSendString(sciREG4," P1 link status   :  Up \r\n\0");
        else
            UartSendString(sciREG4," P1 link stauts   :  Down \r\n\0");

        temp = PhyRead(phyAddr+1,PHY_COM_SR);
        UartSendString(sciREG4," P1 reg23 value   :  \0");
        UartSendHexU16(sciREG4,temp);
        UartSendString(sciREG4,"\r\n\0");

    }
    return 1;
}


/******************************************************
*Name    :  FreeRTOS_Phyinit
*Function:  初始化函数所有 PHY
*Params  :
*Return  :  其它： 表示初始化失败， 2 表示成功
*******************************************************/
uint8   FreeRTOS_Phyinit(void)
{
    uint8   flag;

    gioSetBit(gioPORTB,PHY_RST_PIN,0);
    DelayUs(150);
    gioSetBit(gioPORTB,PHY_RST_PIN,1);
    Phy1En_on();
    Phy2En_on();

    #if (HWVER3)
        MDIOInit(MDIO_BASE,MDIO_FREQ_INPUT,MDIO_FREQ_OUTPUT);
    #endif

    DelayUs(100000);

    flag = Phy_init(PHY1_RMII_P0);
    flag = flag << 1;
    flag |= Phy_init(PHY2_RMII_P0);

    return flag;
}

/******************************************************
*Name    :  PHY3_IntISR
*Function:  PHY 中断服务程序，当网络链接状态改变时，产生中断
*Params  :
*Return  :
*******************************************************/
void    PHY3_IntISR()
{
    uint16  temp;
    temp = PhyRead(PHY2_RMII_P0,PHY_INTR);

    if(temp & 0x400)
    {
        UartSendString(sciREG4," TJA1102  P0 link status   :  Down \r\n\0");
        LedP2Status_off();
    }
    else if (temp & 0x200)
    {
        UartSendString(sciREG4," TJA1102  P0 link status   :  Up \r\n\0");
        LedP2Status_on();
    }

    temp = PhyRead(PHY2_RMII_P1,PHY_INTR);
    if( temp & 0x400 )
    {
        UartSendString(sciREG4," TJA1102  P1 link status   :  Down \r\n\0");
        LedP3Status_off();
    }
    else if (temp & 0x200 )
    {
        UartSendString(sciREG4," TJA1102  P1 link status   :  Up \r\n\0");
        LedP3Status_on();
    }
}

/******************************************************
*Name    :  PHY_IntISR
*Function:  PHY 中断服务程序，当网络链接状态改变时，产生中断
*Params  :
*Return  :
*******************************************************/
void    PHY_IntISR()
{
    uint16  temp;

    temp = PhyRead(PHY1_RMII_P0,PHY_INTR);

    if(temp & 0x400 )
    {
        UartSendString(sciREG4," TJA1102S P0 link status   :  Down \r\n\0");
        LedP1Status_off();
    }
    else if (temp & 0x200 )
    {
        UartSendString(sciREG4," TJA1102S P0 link status   :  Up \r\n\0");
        LedP1Status_on();
    }
}
