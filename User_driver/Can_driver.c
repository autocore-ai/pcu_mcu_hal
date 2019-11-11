/******************************************************************
FileName   :Can_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2018-12-29
****************************************************************/

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_timer.h"

#include "HL_can.h"
#include "HL_sys_vim.h"
#include "Can_driver.h"
#include <string.h>
#include "Ultrasonic.h"
#include "time_common.h"

extern  QueueHandle_t udp_recv_que_handle;
extern  xTaskHandle  UdpSend_Task_Handle;

#define CAN1_TASK_PRIO     15
#define CAN1_STK_SIZE      128
TaskHandle_t Can1RecvTask_Handler;
QueueHandle_t Can1_recv_QueHandle,Ultra_QueHandle;

#define CAN2_TASK_PRIO     16
#define CAN2_STK_SIZE      64
TaskHandle_t Can2RecvTask_Handler;
QueueHandle_t Can2_recv_QueHandle;

#define CAN3_TASK_PRIO     17
#define CAN3_STK_SIZE      64
TaskHandle_t Can3RecvTask_Handler;
QueueHandle_t Can3_recv_QueHandle;

#define CAN4_TASK_PRIO     18
#define CAN4_STK_SIZE      64
TaskHandle_t Can4RecvTask_Handler;
QueueHandle_t Can4_recv_QueHandle;

TaskHandle_t Can3SendTask_Handler;
#define CAN3_SEND_PRIO     19

TimerHandle_t   Timer50ms_Handle;
void Radar_sim(TimerHandle_t xTimer);


/******************************************************************
*Name    :  FreeRTOS_CanInit
*Function:  创建CAN任务，创建消息队列等等
*Params  :  void
*Return  :  uint8_t  1:成功      0：失败
*******************************************************************/

uint8_t    FreeRTOS_CanInit(void)
{
    canInit();

    taskENTER_CRITICAL();
    uint8_t val;

    vimDisableInterrupt(Can1_low_ch);
    vimDisableInterrupt(Can2_low_ch);
    vimDisableInterrupt(Can3_low_ch);
    vimDisableInterrupt(Can4_low_ch);

    Can1_recv_QueHandle = xQueueCreate(CAN1_Q_NUM, sizeof(canMsg));
    Ultra_QueHandle = xQueueCreate(1,sizeof(Ultrasonic));
    if(Can1_recv_QueHandle !=NULL && Ultra_QueHandle !=NULL)
    {

        xTaskCreate((TaskFunction_t )Can1_RecvTask,
                    (const char*    )"Can1Recv_Task",
                    (uint16_t       )CAN1_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN1_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Can1RecvTask_Handler);
        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(Can1_recv_QueHandle);
        Can1_recv_QueHandle = NULL;
        vQueueDelete(Ultra_QueHandle);
        Ultra_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

    Can2_recv_QueHandle = xQueueCreate(CAN2_Q_NUM, sizeof(canMsg));
    if(Can2_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Can2_RecvTask,
                    (const char*    )"Can2Recv_Task",
                    (uint16_t       )CAN2_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN2_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Can2RecvTask_Handler);
        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(Can2_recv_QueHandle);
        Can2_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

    Can3_recv_QueHandle = xQueueCreate(CAN3_Q_NUM, sizeof(canMsg));
    if(Can3_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Can3_RecvTask,
                    (const char*    )"Can3Recv_Task",
                    (uint16_t       )CAN3_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN3_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Can3RecvTask_Handler);
        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(Can3_recv_QueHandle);
        Can3_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

    Can4_recv_QueHandle = xQueueCreate(CAN4_Q_NUM, sizeof(canMsg));
    if(Can3_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Can4_RecvTask,
                    (const char*    )"Can4Recv_Task",
                    (uint16_t       )CAN4_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN4_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Can4RecvTask_Handler);
        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(Can4_recv_QueHandle);
        Can4_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }
/*
    Timer50ms_Handle = xTimerCreate(
                                   (const char*        )"Radar_sim",
                                   (TickType_t         )500,
                                   (UBaseType_t        )pdTRUE,
                                   (void*              )1,
                                   (TimerCallbackFunction_t)Radar_sim
                                 );

    xTimerStart(Timer50ms_Handle,0);

*/
#if 0
    xTaskCreate((TaskFunction_t )Can3_SendTask,
                (const char*    )"Can3Send_Task",
                (uint16_t       )CAN3_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )CAN3_SEND_PRIO | portPRIVILEGE_BIT,
                (TaskHandle_t*  )&Can3SendTask_Handler);
#endif
    taskEXIT_CRITICAL();


    return val;
}


void Can3_SendTask(void *pvParameters)
{
    canMsg can_msg_queue;

    vTaskDelay(1000);
    while (1)
    {
        can_msg_queue.can_id = 0x300;
        can_msg_queue.dlc = 2;
        can_msg_queue.ide = 0;
        can_msg_queue.mask = 0;
        can_msg_queue.data[0] = 5;
//        memset(can_msg_queue.data, 0 , 8);
        can_msg_queue.data[1] = 0xA;

        CanSendData(canREG3,canMESSAGE_BOX1,&can_msg_queue,can_msg_queue.can_id);
        vTaskDelay(50);
    }
}
/******************************************************************
*Name    :  Can1_RecvTask
*Function:  Can1 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/
void Can1_RecvTask(void *pvParameters)
{
    uint8   i;
    BaseType_t err;
    canMsg can_msg_queue;
    Ultrasonic ultra_que_dat;
    int64_t   nanoseconds;
    uint32_t    msgid;
    vimEnableInterrupt(Can1_low_ch,SYS_IRQ);
    while(1)
    {
        if(Can1_recv_QueHandle != NULL)
        {
            if (xQueueReceive(Can1_recv_QueHandle,&can_msg_queue,portMAX_DELAY))
            {
                if(can_msg_queue.ide)
                    msgid = can_msg_queue.can_id & 0x1FFFFFFF;
                else
                    msgid = (can_msg_queue.can_id >> 18) & 0x7FF;

                if((msgid == Ultra_ID1) || (msgid == Ultra_ID2) || (msgid == Ultra_ID3))
                {
                    for(i=0;i<4;i++)
                        ultra_que_dat.data[i] = ((uint32_t)can_msg_queue.data[i*2]<<8) | ((uint32_t)can_msg_queue.data[i*2+1]);
                    ultra_que_dat.id = msgid ;
                    strcpy(ultra_que_dat.header.frame_id,"Ultrasonic");
                    nanoseconds = uxr_millis();
                    ultra_que_dat.header.stamp.sec =  (int32_t)(nanoseconds / 1000000000);
                    ultra_que_dat.header.stamp.nanosec = (uint32_t)nanoseconds % 1000000000;
                    xQueueOverwrite(Ultra_QueHandle,&ultra_que_dat);

    #if 1
                    for(i=0;i<can_msg_queue.dlc;i++)
                        can_msg_queue.data[i] += 0x10;
                    CanSendData(canREG1,canMESSAGE_BOX1,&can_msg_queue,msgid);
    #endif
//-------------------------------------------
//                    xQueueSendToBack(udp_recv_que_handle,&can_msg_queue,0);
//                    xTaskNotifyGive(UdpSend_Task_Handle);
                }
                else if (msgid == 0xD7)
                {
                    vTaskSuspend(Can3SendTask_Handler);
                }
                else if (msgid == 0xD0)
                {
                    vTaskResume(Can3SendTask_Handler);
                }
            }
            else if(err==pdFALSE)
            {
                vTaskDelay(15);
            }
        }
     }
}

/*******************************************************************************************
*Name    :  can1LowLevelInterrupt
*Function:  CAN1中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Can1_lowHwiISR, 32)
#pragma INTERRUPT(Can1_lowHwiISR,IRQ)
void Can1_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG1);
    if (msg.dlc )
    {
        xQueueSendFromISR(Can1_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/******************************************************************
*Name    :  Can2_RecvTask
*Function:  Can1 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/
void Can2_RecvTask(void *pvParameters)
{
    uint8   i;
    BaseType_t err;
    canMsg can_msg_queue;
    uint32_t    msgid;
    vimEnableInterrupt(Can2_low_ch,SYS_IRQ);
    while(1)
    {
        if(Can2_recv_QueHandle != NULL)
        {
            if (xQueueReceive(Can2_recv_QueHandle,&can_msg_queue,portMAX_DELAY))
            {
                if(can_msg_queue.ide)
                    msgid = can_msg_queue.can_id & 0x1FFFFFFF;
                else
                    msgid = (can_msg_queue.can_id >> 18) & 0x7FF;

//                if((msgid == Ultra_ID1) || (msgid == Ultra_ID2) || (msgid == Ultra_ID3))
                {
    #if 1
                    for(i=0;i<can_msg_queue.dlc;i++)
                        can_msg_queue.data[i] += 0x10;
                    CanSendData(canREG2,canMESSAGE_BOX1,&can_msg_queue,msgid+0x100);
    #endif
                }
            }
            else if(err==pdFALSE)
            {
                vTaskDelay(15);
            }
        }
     }

}

/*******************************************************************************************
*Name    :  Can2_lowHwiISR
*Function:  CAN1中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Can2_lowHwiISR, 32)
#pragma INTERRUPT(Can2_lowHwiISR,IRQ)
void Can2_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG2);
    if (msg.dlc )
    {
        xQueueSendFromISR(Can2_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
/******************************************************************
*Name    :  Can3_RecvTask
*Function:  Can1 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/
void Can3_RecvTask(void *pvParameters)
{
    uint8   i;
    BaseType_t err;
    canMsg can_msg_queue;
    uint32_t    msgid;
    vimEnableInterrupt(Can3_low_ch,SYS_IRQ);
    while(1)
    {
        if(Can3_recv_QueHandle != NULL)
        {
            if (xQueueReceive(Can3_recv_QueHandle,&can_msg_queue,portMAX_DELAY))
            {
                if(can_msg_queue.ide)
                    msgid = can_msg_queue.can_id & 0x1FFFFFFF;
                else
                    msgid = (can_msg_queue.can_id >> 18) & 0x7FF;

//                if((msgid == Ultra_ID1) || (msgid == Ultra_ID2) || (msgid == Ultra_ID3))
                {
    #if 1
                    for(i=0;i<can_msg_queue.dlc;i++)
                        can_msg_queue.data[i] += 0x10;
                    CanSendData(canREG3,canMESSAGE_BOX1,&can_msg_queue,msgid - 0x700);
    #endif
                }
            }
            else if(err==pdFALSE)
            {
                vTaskDelay(15);
            }
        }
     }

}

/*******************************************************************************************
*Name    :  Can3_lowHwiISR
*Function:  CAN1中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Can3_lowHwiISR, 32)
#pragma INTERRUPT(Can3_lowHwiISR,IRQ)
void Can3_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG3);
    if (msg.dlc )
    {
        xQueueSendFromISR(Can3_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
/******************************************************************
*Name    :  Can4_RecvTask
*Function:  Can1 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/
void Can4_RecvTask(void *pvParameters)
{
    uint8   i;
    BaseType_t err;
    canMsg can_msg_queue;
    uint32_t    msgid;
    vimEnableInterrupt(Can4_low_ch,SYS_IRQ);
    while(1)
    {
        if(Can4_recv_QueHandle != NULL)
        {
            if (xQueueReceive(Can4_recv_QueHandle,&can_msg_queue,portMAX_DELAY))
            {
                if(can_msg_queue.ide)
                    msgid = can_msg_queue.can_id & 0x1FFFFFFF;
                else
                    msgid = (can_msg_queue.can_id >> 18) & 0x7FF;

//                if((msgid == Ultra_ID1) || (msgid == Ultra_ID2) || (msgid == Ultra_ID3))
                {
    #if 1
                    for(i=0;i<can_msg_queue.dlc;i++)
                        can_msg_queue.data[i] += 0x10;
                    CanSendData(canREG4,canMESSAGE_BOX1,&can_msg_queue,msgid);
    #endif
                }
            }
            else if(err==pdFALSE)
            {
                vTaskDelay(15);
            }
        }
     }

}
/*******************************************************************************************
*Name    :  Can4_lowHwiISR
*Function:  CAN1中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Can4_lowHwiISR, 32)
#pragma INTERRUPT(Can4_lowHwiISR,IRQ)
void Can4_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG4);
    if (msg.dlc )
    {

        xQueueSendFromISR(Can4_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

/*******************************************************************************************
*Name    :  CanReadData
*Function:  CAN 读数据函数
*Params  :  node :CAN模块基地址指针， canREG1: can1 , canREG2: can2, canREG3: can3, canREG4: can4
*Return  :  canMsg
***********************************************************************************************/

canMsg CanReadData(canBASE_t *node )
{
    #if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    #else
        uint32 s_canByteOrder[8U] = {3U, 2U, 1U, 0U, 7U, 6U, 5U, 4U};
    #endif
    uint32    messageBox = node->INT >> 16U;
    uint32    regIndex = (messageBox - 1U) >> 5U;
    uint32    bitIndex = 1U << ((messageBox - 1U) & 0x1FU);
    uint8     i;
    canMsg    msg;

    while ((node->IF1STAT & 0x80U) ==0x80U) {    }

    node->IF1CMD = 0x08U;
    node->IF1NO  = (uint8) messageBox;

    while ((node->IF1STAT & 0x80U) ==0x80U) {    }
    node->IF1CMD = 0x87U;

    if ((node->NWDATx[regIndex] & bitIndex) )
    {
        memset(msg.data,0,8);

        while ((node->IF2STAT & 0x80U) ==0x80U)  {   }

        node->IF2CMD = 0x20U;

        node->IF2NO = (uint8) messageBox;

        while ((node->IF2STAT & 0x80U) ==0x80U)  {   }

        msg.can_id = node->IF2ARB & 0x1FFFFFFF;
        msg.ide = (node->IF2ARB >> 30) & 0x01;

        while ((node->IF2STAT & 0x80U) ==0x80U) {   }

        node->IF2CMD = 0x17U;

        node->IF2NO = (uint8) messageBox;

        while ((node->IF2STAT & 0x80U) ==0x80U)  {   }

        msg.dlc = node->IF2MCTL & 0xFU;


        if(msg.dlc > 0x8U)
        {
            msg.dlc = 0x8U;
        }
        for (i = 0U; i < msg.dlc; i++)
        {
            #if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
                msg.data[i] = node->IF2DATx[i];
            #else
                msg.data[i] = node->IF2DATx[s_canByteOrder[i]];
            #endif
        }
        node->IF2CMD = 0x08U;

        return msg ;
    }
    else
    {
        msg.dlc = 0;
        return msg;
    }
}


/*******************************************************************************************
*Name    :  CanSendData
*Function:  CAN 读数据函数
*Params  :  node :CAN模块基地址指针， canREG1: can1 , canREG2: can2, canREG3: can3, canREG4: can4
*Params  :  messageBox： 要发送的 数据 CAN messageBox 通道号  【1..64】
*Params  :  mask_id : 滤波ID 号
*Return  :  uint8_t : 1--发送成功       0---失败
***********************************************************************************************/
uint8_t   CanSendData(canBASE_t *node, uint32 messageBox, canMsg *msg,uint32_t mask_id)
{
    #if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    #else
        uint32 ByteOrder[8U] = {3U, 2U, 1U, 0U, 7U, 6U, 5U, 4U};
    #endif

    uint8 i;
    uint32 success  = 0U;
    uint32 regIndex = (messageBox - 1U) >> 5U;
    uint32 bitIndex = 1U << ((messageBox - 1U) & 0x1FU);

    while ((node->IF1STAT & 0x80U) ==0x80U)  {       } /* Wait */
    node->IF1ARB |= (uint32)0x20000000U;
    node->IF1CMD  = (uint8) 0xF8U;

    if ((node->TXRQx[regIndex] & bitIndex) != 0U)
        success = 0U;
    else
    {
        while ((node->IF1STAT & 0x80U) ==0x80U)  {    }
        node->IF1CMD  = (uint8) 0xF0U;

        node->IF1ARB &= 0xA0000000U;
        if(msg->ide)
            node->IF1ARB |= ((uint32)msg->ide << 30) | (uint32)mask_id;
        else
            node->IF1ARB |= ((uint32)msg->ide << 30) | ((uint32)mask_id << 18);

        while ((node->IF1STAT & 0x80U) ==0x80U)  {    }
        node->IF1MCTL &= (uint32)0xEFF0;
        node->IF1MCTL |= ((uint32)(msg->mask << 12)) | ((uint32)msg->dlc);
        while ((node->IF1STAT & 0x80U) ==0x80U)  {    }
        node->IF1NO   = messageBox;

        while ((node->IF1STAT & 0x80U) ==0x80U)  {    }
        node->IF1CMD = 0x87U;

        for (i = 0U; i < msg->dlc; i++)
        {
            #if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
                node->IF1DATx[i] = msg->data[i];
            #else
                node->IF1DATx[ByteOrder[i]] = msg->data[i];
            #endif
        }

        node->IF1NO = (uint8) messageBox;
        success = 1U;
    }

    while ((node->IF1STAT & 0x80U) ==0x80U)  {       } /* Wait */
    node->IF1ARB &= (uint32)0xDFFFFFFFU;
    node->IF1CMD  = (uint8) 0xF8U;

    return success;
}



