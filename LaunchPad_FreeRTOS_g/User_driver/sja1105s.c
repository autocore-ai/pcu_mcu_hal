/******************************************************************
FileName   :sja1105.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-17
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_reg_spi.h"
#include "HL_spi.h"
#include "HL_sci.h"
#include "hardware.h"

/******************************************************
*Name    :  FreeRTOS_NetSwitchInit
*Function:  net switch ≥ı ºªØ∫Ø ˝
*Params  :
*Return  :
*******************************************************/
void    FreeRTOS_NetSwitchInit(void)
{
    Spi1Init();
    Switch_init();
}

/******************************************************
*Name    :  Switch_init
*Function:  net switch ≥ı ºªØ∫Ø ˝
*Params  :
*Return  :  0 ±Ì æ≥ı ºªØ ß∞‹£¨ 1 ±Ì æ≥…π¶
*******************************************************/
uint8   Switch_init(void)
{
    uint32  temp;

    temp = GetDeviceID();
    if (temp == DEVICEID)
    {
#if (DEBUG)

        UartSendString(sciREG4," SJA1105 DeviceID :  \0");
        UartSendHexU32(sciREG4,temp);
        UartSendString(sciREG4,"\r\n\0");
#endif

    }
    else
        return 0;
    temp = GetPartNR();
    if (temp == PARTNR)
    {
#if (DEBUG)
        UartSendString(sciREG4," SJA1105 Part_NR : \0");
        UartSendHexU32(sciREG4,temp);
        UartSendString(sciREG4,"\r\n\0");
#endif

    }
    else
        return 0;

    SpiWrite(spiREG1,(uint16 *)regset_en,4);
/*
    SpiWrite(spiREG1,(uint16 *)port0_pin,4);
    SpiWrite(spiREG1,(uint16 *)port0_idiv0,4);
    SpiWrite(spiREG1,(uint16 *)port0_mii_tx_clk,4);
    SpiWrite(spiREG1,(uint16 *)port0_mii_rx_clk,4);
    SpiWrite(spiREG1,(uint16 *)port0_ext_tx_clk,4);
    SpiWrite(spiREG1,(uint16 *)port0_ext_rx_clk,4);
*/
    SpiWrite(spiREG1,(uint16 *)port0_rmii_idiv0,4);
    SpiWrite(spiREG1,(uint16 *)port0_rmii_refclk,4);

    SpiWrite(spiREG1,(uint16 *)port1_pll,4);
    SpiWrite(spiREG1,(uint16 *)port1_pll1,4);

    SpiWrite(spiREG1,(uint16 *)port1_idiv1,4);
    SpiWrite(spiREG1,(uint16 *)port1_ref_clk1,4);
    SpiWrite(spiREG1,(uint16 *)port1_ext_tx_clk,4);

    SpiWrite(spiREG1,(uint16 *)port2_idiv2,4);
    SpiWrite(spiREG1,(uint16 *)port2_ref_clk2,4);
    SpiWrite(spiREG1,(uint16 *)port2_ext_tx_clk,4);

    SpiWrite(spiREG1,(uint16 *)port3_idiv3,4);
    SpiWrite(spiREG1,(uint16 *)port3_ref_clk3,4);
    SpiWrite(spiREG1,(uint16 *)port3_ext_tx_clk,4);

/*
    SpiWrite(spiREG1,(uint16 *)port4_idiv4,4);
    SpiWrite(spiREG1,(uint16 *)port4_rgmii_clk4,4);
    SpiWrite(spiREG1,(uint16 *)cfg_pad_mii4_tx,4);
*/

    SpiWrite(spiREG1,(uint16 *)basic_control,3);
    SpiWrite(spiREG1,(uint16 *)autoneg_adv,3);
    SpiWrite(spiREG1,(uint16 *)digital_control1,3);
    SpiWrite(spiREG1,(uint16 *)autoneg_control,3);
    SpiWrite(spiREG1,(uint16 *)tx_boost_control,3);
    SpiWrite(spiREG1,(uint16 *)tx_attn_control,3);
    SpiWrite(spiREG1,(uint16 *)tx_edge_control,3);
    SpiWrite(spiREG1,(uint16 *)rx_eq_control,3);
    SpiWrite(spiREG1,(uint16 *)level_control,3);
    SpiWrite(spiREG1,(uint16 *)digital_control2,3);
    SpiWrite(spiREG1,(uint16 *)digital_error_cnt,3);

    SpiWrite(spiREG1,(uint16 *)configBurst0_0,130);
    SpiWrite(spiREG1,(uint16 *)configBurst0_1,130);
    SpiWrite(spiREG1,(uint16 *)configBurst0_2,130);
    SpiWrite(spiREG1,(uint16 *)configBurst0_3,130);
    SpiWrite(spiREG1,(uint16 *)configBurst0_4,130);
    SpiWrite(spiREG1,(uint16 *)configBurst0_5,14);

    temp = GetSetStatus() & 0xf0000000;
    if(temp == 0x80000000)
    {
#if (DEBUG)
        UartSendString(sciREG4," SJA1105 init Success ,stauts regs is : 0x80000000   \r\n\0");
#endif
        return 1;
    }
    else
    {
#if (DEBUG)
        UartSendString(sciREG4," SJA1105 init is fail!  \r\n\0");
#endif
        return 0;
    }
}


/******************************************************
*Name    :  GetDeviceID
*Function:  ∂¡ device ID∫≈
*Params  :
*Return  :  ID∫≈    (1105s =0xae00030e )
*******************************************************/
uint32  GetDeviceID(void)
{
    uint16  addr[]={0x0400,0x0000};
    uint16  netid[2];
    uint32  val;
    val = SpiRead(spiREG1,addr,2,netid,2);
    if (val & 0xFF)
        return 0;
    val = netid[0]<<16 | netid[1];
    return val;
}

/******************************************************
*Name    :  GetParNR
*Function:  ∂¡ part number∫≈
*Params  :
*Return  :  ID∫≈    (1105s = 0x9a871)
*******************************************************/
uint32  GetPartNR(void)
{
    uint16  addr[2];
    uint16  netid[2];
    uint32  val = 0x100bc3;

    val = val << 4;
    val = val | (2<<25);
    addr[0] = (uint16)(val>>16);
    addr[1] = (uint16)(val);
    val = SpiRead(spiREG1,addr,2,netid,2);
    if (val & 0xFF)
        return 0;
    val = netid[0]<<16 | netid[1];
    return val;
}


/******************************************************
*Name    :  GetSetStatus
*Function:  ∂¡ –æ∆¨≈‰÷√◊¥Ã¨
*Params  :
*Return  :  –æ∆¨≈‰÷√◊¥Ã¨
*******************************************************/
uint32  GetSetStatus(void)
{
    uint16  addr[]={0x0400,0x0010};
    uint16  netid[2];
    uint32  val;
    val = SpiRead(spiREG1,addr,2,netid,2);
    if (val & 0xFF)
        return 0;
    val = netid[0]<<16 | netid[1];
    return val;
}
