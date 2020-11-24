/******************************************************************
FileName   :Can_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2018-12-29
****************************************************************/

#include <can_driver.h>
#include <can_driver.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_timer.h"

#include "HL_can.h"
#include "HL_sys_vim.h"
#include <string.h>
#include "Ultrasonic.h"
#include "time_common.h"
#include "udp_can.h"
#include "Can_init.h"

#define     DEBUG_SPEED        0
#define     CAN_RECV_PRIO   configMAX_PRIORITIES - 8
#define     CAN_SEND_PRIO   configMAX_PRIORITIES - 6
#define     CAN_STK_SIZE    configMINIMAL_STACK_SIZE

extern  QueueHandle_t   DATA_QUE(udp1,recv),DATA_QUE(udp2,recv),DATA_QUE(udp3,recv),DATA_QUE(udp4,recv);
extern  TaskHandle_t    TASK_NOTIFY(udp1,send),TASK_NOTIFY(udp2,send),TASK_NOTIFY(udp3,send),TASK_NOTIFY(udp4,send);

TaskHandle_t    TASK_NOTIFY(Can1,recv),TASK_NOTIFY(Can1,send);
QueueHandle_t   DATA_QUE(Can1,recv), DATA_QUE(Can1,send);
TaskHandle_t    TASK_NOTIFY(Can2,recv),TASK_NOTIFY(Can2,send);
QueueHandle_t   DATA_QUE(Can2,recv), DATA_QUE(Can2,send);
TaskHandle_t    TASK_NOTIFY(Can3,recv),TASK_NOTIFY(Can3,send);
QueueHandle_t   DATA_QUE(Can3,recv), DATA_QUE(Can3,send);
TaskHandle_t    TASK_NOTIFY(Can4,recv),TASK_NOTIFY(Can4,send);
QueueHandle_t   DATA_QUE(Can4,recv), DATA_QUE(Can4,send);


static void SendCanmsgToUdp(canMsg *can_msg,QueueHandle_t udp_rec_queue,TaskHandle_t udpSend_Handle);
static void FUNC_R(Can1,recv)(void *pvParameters);
static void FUNC_R(Can2,recv)(void *pvParameters);
static void FUNC_R(Can3,recv)(void *pvParameters);
static void FUNC_R(Can4,recv)(void *pvParameters);
static void FUNC_R(Can1,send)(void *pvParameters);
static void FUNC_R(Can2,send)(void *pvParameters);
static void FUNC_R(Can3,send)(void *pvParameters);
static void FUNC_R(Can4,send)(void *pvParameters);
extern  uint32  FrameCnt[16];

/******************************************************************
*Name    :  FreeRTOS_CanInit
*Function:  创建CAN任务，创建消息队列等等
*Params  :  void
*Return  :  uint8_t  1:成功      0：失败
*******************************************************************/

uint8_t    FreeRTOS_CanInit(void)
{
    canInit();
//    can_init();

    taskENTER_CRITICAL();
    uint8_t val;

    vimDisableInterrupt(Can1_low_ch);
    vimDisableInterrupt(Can2_low_ch);
    vimDisableInterrupt(Can3_low_ch);
    vimDisableInterrupt(Can4_low_ch);

    DATA_QUE(Can1,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    DATA_QUE(Can1,send) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    if(DATA_QUE(Can1,recv) !=NULL && DATA_QUE(Can1,send) !=NULL)
    {

        xTaskCreate((TaskFunction_t )FUNC_R(Can1,recv),
                    (const char*    )FUNC_S(Can1_recv),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can1,recv));

        xTaskCreate((TaskFunction_t )FUNC_R(Can1,send),
                    (const char*    )FUNC_S(Can1_send),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can1,send));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(Can1,send));
        vQueueDelete(DATA_QUE(Can1,recv));
        DATA_QUE(Can1,send) = NULL;
        DATA_QUE(Can1,recv) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(Can2,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    DATA_QUE(Can2,send) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    if(DATA_QUE(Can2,recv) !=NULL && DATA_QUE(Can2,send) !=NULL)
    {

        xTaskCreate((TaskFunction_t )FUNC_R(Can2,recv),
                    (const char*    )FUNC_S(Can2_recv),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can2,recv));

        xTaskCreate((TaskFunction_t )FUNC_R(Can2,send),
                    (const char*    )FUNC_S(Can2_send),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can2,send));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(Can2,recv));
        vQueueDelete(DATA_QUE(Can2,send));
        DATA_QUE(Can2,recv) = NULL;
        DATA_QUE(Can2,send) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(Can3,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    DATA_QUE(Can3,send) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    if(DATA_QUE(Can3,recv) !=NULL && DATA_QUE(Can3,send) !=NULL)
    {

        xTaskCreate((TaskFunction_t )FUNC_R(Can3,recv),
                    (const char*    )FUNC_S(Can3_recv),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can3,recv));

        xTaskCreate((TaskFunction_t )FUNC_R(Can3,send),
                    (const char*    )FUNC_S(Can3_send),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can3,send));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(Can3,recv));
        vQueueDelete(DATA_QUE(Can3,send));
        DATA_QUE(Can3,recv) = NULL;
        DATA_QUE(Can3,send) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(Can4,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));
    DATA_QUE(Can4,send) = xQueueCreate(CAN_Q_NUM, sizeof(canMsg));

    if(DATA_QUE(Can4,recv) !=NULL  && DATA_QUE(Can4,send) !=NULL)
    {

        xTaskCreate((TaskFunction_t )FUNC_R(Can4,recv),
                    (const char*    )FUNC_S(Can4_Recv),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can4,recv));

        xTaskCreate((TaskFunction_t )FUNC_R(Can4,send),
                    (const char*    )FUNC_S(Can4_send),
                    (uint16_t       )CAN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )CAN_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(Can4,send));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(Can4,recv));
        vQueueDelete(DATA_QUE(Can4,send));
        DATA_QUE(Can4,recv) = NULL;
        DATA_QUE(Can4,send) = NULL;
        val = (uint8_t)pdFALSE;
    }

    taskEXIT_CRITICAL();
    return val;
}

static void SendCanmsgToUdp(canMsg *can_msg,QueueHandle_t udp_recv_queue,TaskHandle_t udpSend_Handle)
{
    uint32_t        msgid;
    canlloni_frame  can_udp_frame;
    uint8           i;

    if(can_msg->ide)
    {
        msgid = can_msg->can_id & 0x1FFFFFFF;
        can_udp_frame.flags  = CANFD_FRAME;
    }
    else
    {
        msgid = (can_msg->can_id >> 18) & 0x7FF;
        can_udp_frame.flags  = CAN_FRAME;
    }
    can_udp_frame.can_id = msgid;
    can_udp_frame.len    = can_msg->dlc;
    for(i=0;i<can_msg->dlc;i++)
        can_udp_frame.data[i] = can_msg->data[i];
    xQueueSendToBack(udp_recv_queue,&can_udp_frame,0);
    xTaskNotifyGive(udpSend_Handle);
}

static void FUNC_R(Can1,recv)(void *pvParameters)
{
    canMsg          can_msg_queue;

    vimEnableInterrupt(Can1_low_ch,SYS_IRQ);
    while(1)
    {
        if (xQueueReceive(DATA_QUE(Can1,recv),&can_msg_queue,portMAX_DELAY))
        {
            SendCanmsgToUdp(&can_msg_queue,DATA_QUE(udp1,recv),TASK_NOTIFY(udp1,send));
            FrameCnt[1]++;
        }
//        {
//            if(can_msg_queue.ide)
//            {
//                msgid = can_msg_queue.can_id & 0x1FFFFFFF;
//                can_udp_frame.flags  = CANFD_FRAME;
//            }
//            else
//            {
//                msgid = (can_msg_queue.can_id >> 18) & 0x7FF;
//                can_udp_frame.flags  = CAN_FRAME;
//            }
//            can_udp_frame.can_id = msgid;
//            can_udp_frame.len    = can_msg_queue.dlc;
//            for(i=0;i<can_msg_queue.dlc;i++)
//                can_udp_frame.data[i] = can_msg_queue.data[i];
//            xQueueSendToBack(udp_recv_que1_handle,&can_udp_frame,0);
//            xTaskNotifyGive(UdpSend_Task1_Handle);
//        }
    }
}



static void FUNC_R(Can1,send)(void *pvParameters)
{
    canMsg can_msg_queue;
    while(1)
    {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        while(xQueueReceive(DATA_QUE(Can1,send),&can_msg_queue,0))
        {
            can_msg_queue.ide  = 0;
            can_msg_queue.mask = 0;
            CanSendData(canREG1,canMESSAGE_BOX1,&can_msg_queue,can_msg_queue.can_id);
            FrameCnt[0]++;
#if DEBUG_SPEED
            vTaskDelay(1);
#endif
        }
    }
}


#pragma CODE_STATE(Can1_lowHwiISR, 32)
#pragma INTERRUPT(Can1_lowHwiISR,IRQ)
void Can1_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG1);
    if (msg.dlc )
    {
        xQueueSendFromISR(DATA_QUE(Can1,recv),&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void FUNC_R(Can2,recv)(void *pvParameters)
{
    canMsg          can_msg_queue;

    vimEnableInterrupt(Can2_low_ch,SYS_IRQ);
    while(1)
    {
        if (xQueueReceive(DATA_QUE(Can2,recv),&can_msg_queue,portMAX_DELAY))
        {
            SendCanmsgToUdp(&can_msg_queue,DATA_QUE(udp2,recv),TASK_NOTIFY(udp2,send));
            FrameCnt[3]++;
        }
    }
}

static void FUNC_R(Can2,send)(void *pvParameters)
{
    canMsg can_msg_queue;
    while(1)
    {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        while(xQueueReceive(DATA_QUE(Can2,send),&can_msg_queue,0))
        {
            can_msg_queue.ide  = 0;
            can_msg_queue.mask = 0;
            CanSendData(canREG2,canMESSAGE_BOX1,&can_msg_queue,can_msg_queue.can_id);
            FrameCnt[2]++;

#if DEBUG_SPEED
            vTaskDelay(1);
#endif
        }
    }
}


#pragma CODE_STATE(Can2_lowHwiISR, 32)
#pragma INTERRUPT(Can2_lowHwiISR,IRQ)
void Can2_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG2);
    if (msg.dlc )
    {
        xQueueSendFromISR(DATA_QUE(Can2,recv),&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void FUNC_R(Can3,recv)(void *pvParameters)
{
    canMsg          can_msg_queue;

    vimEnableInterrupt(Can3_low_ch,SYS_IRQ);
    while(1)
    {
        if (xQueueReceive(DATA_QUE(Can3,recv),&can_msg_queue,portMAX_DELAY))
        {
            SendCanmsgToUdp(&can_msg_queue,DATA_QUE(udp3,recv),TASK_NOTIFY(udp3,send));
            FrameCnt[5]++;
        }
    }
}

static void FUNC_R(Can3,send)(void *pvParameters)
{
    canMsg can_msg_queue;
    while(1)
    {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        while(xQueueReceive(DATA_QUE(Can3,send),&can_msg_queue,0))
        {
            can_msg_queue.ide  = 0;
            can_msg_queue.mask = 0;
            CanSendData(canREG3,canMESSAGE_BOX1,&can_msg_queue,can_msg_queue.can_id);
            FrameCnt[4]++;

#if DEBUG_SPEED
            vTaskDelay(1);
#endif
        }
    }
}


#pragma CODE_STATE(Can3_lowHwiISR, 32)
#pragma INTERRUPT(Can3_lowHwiISR,IRQ)
void Can3_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG3);
    if (msg.dlc )
    {
        xQueueSendFromISR(DATA_QUE(Can3,recv),&msg,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void FUNC_R(Can4,recv)(void *pvParameters)
{
    canMsg          can_msg_queue;

    vimEnableInterrupt(Can4_low_ch,SYS_IRQ);
    while(1)
    {
        if (xQueueReceive(DATA_QUE(Can4,recv),&can_msg_queue,portMAX_DELAY))
        {
            SendCanmsgToUdp(&can_msg_queue,DATA_QUE(udp4,recv),TASK_NOTIFY(udp4,send));
            FrameCnt[7]++;
        }
    }
}

static void FUNC_R(Can4,send)(void *pvParameters)
{
    canMsg can_msg_queue;
    while(1)
    {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        while(xQueueReceive(DATA_QUE(Can4,send),&can_msg_queue,0))
        {
            can_msg_queue.ide  = 0;
            can_msg_queue.mask = 0;
            CanSendData(canREG4,canMESSAGE_BOX1,&can_msg_queue,can_msg_queue.can_id);
            FrameCnt[6]++;
#if DEBUG_SPEED
            vTaskDelay(1);
#endif
        }
    }
}


#pragma CODE_STATE(Can4_lowHwiISR, 32)
#pragma INTERRUPT(Can4_lowHwiISR,IRQ)
void Can4_lowHwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    canMsg  msg;
    msg = CanReadData(canREG4);
    if (msg.dlc )
    {

        xQueueSendFromISR(DATA_QUE(Can4,recv),&msg,&xHigherPriorityTaskWoken);
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



