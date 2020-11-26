/******************************************************************
FileName   :watchdog_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-04-23
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_reg_rti.h"
#include "watchdog_driver.h"
#include "HL_sys_vim.h"

TimerHandle_t   WatchdogTimer_Handle;
void Watchdog_func(TimerHandle_t xTimer);

/******************************************************************
*Name    :  prvSetupTimerInterrupt
*Function:  ��ʱ�����Ƚ�����ʼ��
*Params  :  void
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-25
*******************************************************************/
#if 0
void prvSetupTimerInterrupt(void)
{
    rtiREG1->GCTRL =  0x00000000U;
    rtiREG1->TBCTRL = 0x00000000U;
    rtiREG1->COMPCTRL = 0x00001000U | 0x00000100U | 0x00000000U | 0x00000000U;

    rtiREG1->CNT[0U].UCx   = 0x00000000U;
    rtiREG1->CNT[0U].FRCx  = 0x00000000U;
    rtiREG1->CNT[0U].CPUCx = 1U;

    rtiREG1->CMP[0U].COMPx = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;
    rtiREG1->CMP[0U].UDCPx = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;


    rtiREG1->CMP[1U].COMPx = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;
    rtiREG1->CMP[1U].UDCPx = ( configCPU_CLOCK_HZ / 2 ) / configTICK_RATE_HZ;


    rtiREG1->CNT[1U].UCx   = 0x00000000U;
    rtiREG1->CNT[1U].FRCx  = 0x00000000U;
    rtiREG1->CNT[1U].CPUCx = 74U;


    rtiREG1->CMP[2U].COMPx = 400000U;
    rtiREG1->CMP[2U].UDCPx = 400000U;

    rtiREG1->CMP[3U].COMPx = 10000U;
    rtiREG1->CMP[3U].UDCPx = 10000U;

    /** - Clear all pending interrupts */
    rtiREG1->INTFLAG = 0x0007000FU;
    rtiREG1->CLEARINTENA = 0x00070F0FU;

    rtiREG1->SETINTENA |= 0x00040007U;

    rtiREG1->GCTRL |= 0x00000003;
}
#endif

/******************************************************************
*Name    :  FreeRTOS_WatchdogInit
*Function:  ��ʼ�����Ź�������ι����ʱ��
*Params  :  void
*Return  :  uint8_t  1:�ɹ�      0��ʧ��
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/
void FreeRTOS_WatchdogInit(void)
{

    dwwdInit(rtiREG1, Generate_Reset, 4095, Size_100_Percent);
    dwdCounterEnable(rtiREG1);
}

/******************************************************************
*Name    :  WatchdogHwiISR
*Function:  ��ʱ�����ڷ�������ʵ��ι��
*Params  :  void
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/
void Watchdog_func(TimerHandle_t xTimer)
{
    dwdReset(rtiREG1);
}

#pragma INTERRUPT(WatchdogHwiISR,IRQ)
void WatchdogHwiISR(void)
{
    rtiREG1->INTFLAG = 0x00000004;
    dwdReset(rtiREG1);
}

/******************************************************************
*Name    :  dwdInit
*Function:  ���Ź�Ԥװ�ض�ʱ����ʼ��
*Params  :  rtiREG :RTIģ����    dwdPreload:Ԥװ��ֵ    Texp = (dwdPreload +1)*8192 / RTICLK
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/

void dwdInit(rtiBASE_t *rtiREG, uint16 dwdPreload)
{

    rtiREG->WDSTATUS = 0xFFU;

    rtiREG->DWDPRLD = dwdPreload;

}


/******************************************************************
*Name    :  dwwdInit
*Function:  ���Ź���ʼ��
*Params  :  rtiREG :RTIģ����
*Params  :  Reaction: ��ʱʱ�䵽���������ж�   Reset NMI
*Params  :  dwdPreload:Ԥװ��ֵ    Texp = (dwdPreload +1)*8192 / RTICLK
*Params  :  ����ʱ��
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/

void dwwdInit(rtiBASE_t *rtiREG, dwwdReaction_t Reaction, uint16 dwdPreload, dwwdWindowSize_t Window_Size)
{
    rtiREG->WDSTATUS = 0xFFU;

    rtiREG->WWDSIZECTRL = (uint32) Window_Size;
    rtiREG->DWDPRLD     = (uint32) dwdPreload;
    rtiREG->WWDRXNCTRL  = (uint32) Reaction;

}

/******************************************************************
*Name    :  dwwdInit
*Function:  ι��
*Params  :  rtiREG :RTIģ����
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/

void dwdReset(rtiBASE_t *rtiREG)
{
    rtiREG->WDKEY = 0x0000E51AU;
    rtiREG->WDKEY = 0x0000A35CU;
}

/******************************************************************
*Name    :  dwwdInit
*Function:  �������Ź�ֱ�Ӳ�����λ
*Params  :  rtiREG :RTIģ����
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/

void dwdGenerateSysReset(rtiBASE_t *rtiREG)
{
    rtiREG->WDKEY = 0x0000E51AU;
    rtiREG->WDKEY = 0x00002345U;
}

/******************************************************************
*Name    :  dwdCounterEnable
*Function:  �����Ź�����
*Params  :  rtiREG :RTIģ����
*Return  :
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/
void dwdCounterEnable(rtiBASE_t *rtiREG)
{
    rtiREG->DWDCTRL = 0xA98559DAU;
}

/******************************************************************
*Name    :  WatchdogStart
*Function:  �������ǹ���������Ź�״̬λ������λϵͳ
*Params  :  rtiREG :RTIģ����
*------------------------------------------------------------------
*Author      :zhenhua.wang
*Create Date :2019-04-23
*******************************************************************/
void WatchdogStart(rtiBASE_t *rtiREG)
{
    if ((rtiREG->WDSTATUS & 0x2) == 0x2)
    {
        rtiREG->WDSTATUS = 0xFFU;
    }
}
