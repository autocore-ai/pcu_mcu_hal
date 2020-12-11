/*
 * hardware.c
 *
 *  Created on: 2019��6��17��
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
// ����: void  delay_us(uint32 us)
// ����: ��ʱ������
// ����: us,Ҫ��ʱ��us��.
// ����: none.
// �汾: VER1.0
// ��ע:
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
// ����: void  delay_us(uint32 us)
// ����: ��ʱ������
// ����: us,Ҫ��ʱ��us��.
// ����: none.
// �汾: VER1.0
// ��ע:
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


