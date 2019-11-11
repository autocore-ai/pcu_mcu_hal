/******************************************************************
FileName   :Adc.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-10-14
****************************************************************/
#include    "FreeRTOS.h"
#include    "os_task.h"
#include    "os_queue.h"
#include    "os_semphr.h"

#include    "HL_adc.h"
#include    "HL_sys_vim.h"
#include    "Hardware.h"

#define     ADC1_GROUP1         15

#define ADC1_START_PRIO     20
#define ADC1_STK_SIZE      128
TaskHandle_t Adc1StartTask_Handler;

#define ADC1_DATA_PRIO     21
#define ADC1_STK_SIZE      128
TaskHandle_t Adc1DataProcessTask_Handler;
QueueHandle_t Adc1_data_QueHandle;

adcData_t   AdcResult[4];

/******************************************************************
*Name    :  FreeRTOS_AdcInit
*Function:  创建CAN任务，创建消息队列等等
*Params  :  void
*Return  :  void
*******************************************************************/
void    FreeRTOS_AdcInit(void)
{
//    vimChannelMap(ADC1_GROUP1, ADC1_GROUP1, &Adc1_HwiISR);
    vimDisableInterrupt(ADC1_GROUP1);

    adcInit();
    adcMidPointCalibration(adcREG1);

    xTaskCreate((TaskFunction_t )Adc1_StartTask,
                (const char*    )"Adc1_StartTask",
                (uint16_t       )ADC1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )ADC1_START_PRIO | portPRIVILEGE_BIT,
                (TaskHandle_t*  )&Adc1StartTask_Handler);

#if 0
    xTaskCreate((TaskFunction_t )Adc1_DataProcessTask,
                (const char*    )"Adc1_DataProcessTask",
                (uint16_t       )ADC1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )ADC1_DATA_PRIO | portPRIVILEGE_BIT,
                (TaskHandle_t*  )&Adc1DataProcessTask_Handler);

#endif
}

/*******************************************************************************************
*Name    :  Adc1_StartTask
*Function:  ADC1 Group1 配置ADC通道启动转换任务，每100ms启动一次转换
*Params  :  void
*Return  :  void
***********************************************************************************************/
void    Adc1_StartTask(void)
{
    vimEnableInterrupt(ADC1_GROUP1,SYS_IRQ);
    adcEnableNotification(adcREG1,adcGROUP1);
    while(1)
    {
        adcStartConversion(adcREG1,adcGROUP1);
        vTaskDelay(100);
    }

}

/*******************************************************************************************
*Name    :  Adc1_DataProcessTask
*Function:  ADC 数据处理任务
*Params  :  void
*Return  :  void
***********************************************************************************************/
void    Adc1_DataProcessTask(void)
{
    BaseType_t err;
    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
            adcGetData(adcREG1, adcGROUP1,&AdcResult[0]);
        }
        else
            vTaskDelay(10);
    }
}

/*******************************************************************************************
*Name    :  Adc1_HwiISR
*Function:  ADC1 Group1 中断处理程序, 当配置的ADC通道完成一次转换时，产生中断
*Params  :  void
*Return  :  void
***********************************************************************************************/
#pragma CODE_STATE(Adc1_HwiISR, 32)
#pragma INTERRUPT(Adc1_HwiISR,IRQ)
void    Adc1_HwiISR(void)
{
//    BaseType_t  xHigherPriorityTaskWoken;

    adcREG1->GxINTFLG[1U] = 9U;
    adcStopConversion(adcREG1,adcGROUP1);
    adcGetData(adcREG1, adcGROUP1,&AdcResult[0]);

//    vTaskNotifyGiveFromISR(Adc1DataProcessTask_Handler,&xHigherPriorityTaskWoken);
//    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

