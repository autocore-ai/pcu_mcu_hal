/******************************************************************
FileName   :Gpio_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-06-14
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_reg_gio.h"
#include "HL_gio.h"
#include "hardware.h"


#pragma CODE_STATE(gioLow_HwiISR, 32)
#pragma INTERRUPT(gioLow_HwiISR, IRQ)

void gioLow_HwiISR(void)
{
    uint32 offset = gioREG->OFF2;

    if (offset != 0U)
    {
        offset = offset - 1U;
        if (offset >= 8U)
        {
            switch(offset-8)
            {
                case  6U:
                    PHY3_IntISR();
                    break;
                case  7U:
                    PHY_IntISR();
                    break;
                default:
                    break;
            }

        }
        else
        {
            switch(offset)
            {
                case  1U:
                    Input0_ISR();
                    break;
                case  2U:
                    Input1_ISR();
                    break;
                case  3U:
                    Input2_ISR();
                    break;
                case  4U:
                    Input3_ISR();
                    break;
                case  6U:
                    Input5_ISR();
                case  7U:
                    StopSwitch_ISR();
                    break;
                default:
                    break;
            }
        }
    }
}


void    Input0_ISR(void)
{

}
void    Input1_ISR(void)
{

}
void    Input2_ISR(void)
{

}
void    Input3_ISR(void)
{

}
void    Input5_ISR(void)
{

}
void    StopSwitch_ISR(void)
{

}
