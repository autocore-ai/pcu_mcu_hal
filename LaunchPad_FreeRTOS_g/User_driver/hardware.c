/*
 * hardware.c
 *
 *  Created on: 2019年6月17日
 *      Author: zhenh
 */
#include    "hardware.h"

void    HardwareInit(void)
{
    UartSendString(sciREG4,"\r\n MCU is starting , please wait ...... \r\n\0");

    LedInit();

    FreeRTOS_UartInit();
    FreeRTOS_CanInit();
    FreeRTOS_NetSwitchInit();
    RtcInit();
    FreeRTOS_NorInit();

    FreeRTOS_Phyinit();
    FreeRTOS_AdcInit();
    FreeRTOS_LinInit();

}

//========================================================================
// 函数: void  delay_us(uint32 us)
// 描述: 延时函数。
// 参数: us,要延时的us数.
// 返回: none.
// 版本: VER1.0
// 备注:
//========================================================================
void  DelayUs(unsigned int  us)
{
     unsigned int  i;
     do{
          i = 38;
          while(--i)    ;
     }while(--us);

}

//========================================================================
// 函数: void  delay_us(uint32 us)
// 描述: 延时函数。
// 参数: us,要延时的us数.
// 返回: none.
// 版本: VER1.0
// 备注:
//========================================================================
void  DelayNs(unsigned int  us)
{
     unsigned int  i;
     do{
          i = 20;
          while(--i)    ;
     }while(--us);

}

void  Delayns(void)
{
     unsigned int  i;
     i = 3;
     while(--i)    ;

}


