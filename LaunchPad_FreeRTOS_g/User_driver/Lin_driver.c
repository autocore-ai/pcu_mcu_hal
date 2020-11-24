/******************************************************************
FileName   :Lin_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-10-25
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"


#include "HL_lin.h"
#include "HL_sys_vim.h"
#include "hardware.h"
#include "Led.h"

#include "string.h"

#define UART_TASK_PRIO      configMAX_PRIORITIES - 12
#define UART_STK_SIZE       configMINIMAL_STACK_SIZE

#define LIN_TASK_PRIO     configMAX_PRIORITIES - 13
#define LIN_STK_SIZE      configMINIMAL_STACK_SIZE
TaskHandle_t Lin1RecvTask_Handler;
void Lin1_RecvTask(void *pvParameters);

TaskHandle_t Lin2RecvTask_Handler;
void Lin2_RecvTask(void *pvParameters);

uint8   linFlag1 = 0;
uint8   linFlag = 0;

QueueHandle_t Lin1_recv_QueHandle;
uint8   Lin1RecvBuf[UART1_Q_LEN];
uint8   Lin1RecvCount;

QueueHandle_t Lin2_recv_QueHandle;
uint8   Lin2RecvBuf[UART1_Q_LEN];
uint8   Lin2RecvCount;

/******************************************************
*Name    :  FreeRTOS_LinInit
*Function:  Lin  初始化函数
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/

uint8    FreeRTOS_LinInit(void)
{
    uint8   val;

    Lin2Init();
    LinEn_on();

    Lin1_recv_QueHandle = xQueueCreate(5, sizeof(linMsg));

    if(Lin1_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Lin1_RecvTask,
                    (const char*    )"Lin1Recv_Task",
                    (uint16_t       )LIN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LIN_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Lin1RecvTask_Handler);
        val =(uint8_t) pdTRUE;

    }
    else
    {
        vQueueDelete(Lin1_recv_QueHandle);
        Lin1_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

    Lin2_recv_QueHandle = xQueueCreate(5, sizeof(linMsg));

    if(Lin2_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Lin2_RecvTask,
                    (const char*    )"Lin2Recv_Task",
                    (uint16_t       )LIN_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )LIN_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Lin2RecvTask_Handler);
        val =(uint8_t) pdTRUE;

    }
    else
    {
        vQueueDelete(Lin2_recv_QueHandle);
        Lin2_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

    return val;
}

/*******************************************************************************************
*Name    :  Lin1_HwiISR
*Function:  LIN1 接收中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Lin1_lowHwiISR, 32)
#pragma INTERRUPT(Lin1_lowHwiISR, IRQ)
void Lin1_lowHwiISR(void)
{
    linMsg  msg;
    BaseType_t  xHigherPriorityTaskWoken;
    uint32 vec = linREG1->INTVECT1;
    switch (vec)
    {
    case 11U:
        /* receive */
        if((linREG1->FLR & LIN_RX_INT) == LIN_RX_INT)
        {
            msg = LinReadData(linREG1);
            if (linFlag)
            {
                linFlag = 0;
                xQueueSendFromISR(Lin1_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
        break;
    case 4U:
        if((linREG1->FLR & LIN_ID_INT) == LIN_ID_INT )
            msg.lin_id = (uint8)((uint32)(linREG1->ID & 0x003F0000U >> 16U));
        break;
    default:
        /* phantom interrupt, clear flags and return */
        linREG1->GCR1 &= (uint32)(~((uint32)0x00000080U));
        linREG1->GCR1 |=  0x00000080U;
        break;
    }
}

/*******************************************************************************************
*Name    :  Lin2_HwiISR
*Function:  LIN2 接收中断处理程序
*Params  :  void
*Return  :  void
***********************************************************************************************/

#pragma CODE_STATE(Lin2_lowHwiISR, 32)
#pragma INTERRUPT(Lin2_lowHwiISR, IRQ)
void Lin2_lowHwiISR(void)
{
    linMsg  msg;
    BaseType_t  xHigherPriorityTaskWoken;
    uint32 vec = linREG2->INTVECT1;
    switch (vec)
    {
    case 11U:
        /* receive */
        if((linREG2->FLR & LIN_RX_INT) == LIN_RX_INT)
        {
            msg = LinReadData(linREG2);
            if (linFlag)
            {
                linFlag = 0;
                xQueueSendFromISR(Lin2_recv_QueHandle,&msg,&xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }
        break;
    case 4U:
        if((linREG2->FLR & LIN_ID_INT) == LIN_ID_INT )
            msg.lin_id = (uint8)((uint32)(linREG2->ID & 0x003F0000U >> 16U));
        break;
    default:
        /* phantom interrupt, clear flags and return */
        linREG2->GCR1 &= (uint32)(~((uint32)0x00000080U));
        linREG2->GCR1 |=  0x00000080U;
        break;
    }
}

/******************************************************************
*Name    :  Lin1_RecvTask
*Function:  Lin1 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/

void Lin1_RecvTask(void *pvParameters)
{
    uint8   i;
    linMsg  lin_msg_queue;
    uint8   flag = 0;
    uint8   id = 0x5;
    LinSendHeader(linREG1, id);

    while(1)
    {
        if (xQueueReceive(Lin1_recv_QueHandle,&lin_msg_queue,portMAX_DELAY ))
        {
            lin_msg_queue.lin_id += 0x10;
            if(flag)
            {
                for (i=0; i<lin_msg_queue.len; i++)
                    lin_msg_queue.data[i] &= 0x0F;
                flag = 0;
            }
            else
            {
                for (i=0; i<lin_msg_queue.len; i++)
                    lin_msg_queue.data[i] &= 0xF0;
                flag = 1;
            }

            LinSendData(linREG1,&lin_msg_queue,lin_msg_queue.lin_id);

            id++;
            if( id > 9)
                id = 5;
            LinSendHeader(linREG1, id);

        }
        else
        {
            vTaskDelay(10);
        }
        vTaskDelay(500);
   }
}

/******************************************************************
*Name    :  Lin2_RecvTask
*Function:  Lin2 接受数据任务
*Params  :  void
*Return  :  无
*******************************************************************/



void Lin2_RecvTask(void *pvParameters)
{
    uint8   i;
    linMsg  lin_msg_queue;
    uint8   flag = 0;
    uint8   id = 0x5;
    LinSendHeader(linREG2, id);

    while(1)
    {
        if (xQueueReceive(Lin2_recv_QueHandle,&lin_msg_queue,portMAX_DELAY ))
        {
            lin_msg_queue.lin_id += 0x10;
            if(flag)
            {
                for (i=0; i<lin_msg_queue.len; i++)
                    lin_msg_queue.data[i] &= 0x0F;
                flag = 0;
            }
            else
            {
                for (i=0; i<lin_msg_queue.len; i++)
                    lin_msg_queue.data[i] &= 0xF0;
                flag = 1;
            }


            LinSendData(linREG2,&lin_msg_queue,lin_msg_queue.lin_id);

            id++;
            if( id > 9) id = 5;
            LinSendHeader(linREG2, id);

        }
        else
        {
            vTaskDelay(10);
        }
        vTaskDelay(500);
   }
}


/******************************************************
*Name    :  LinIdCalcParity
*Function:  LIN id 校验位计算
*Params  :  id : Lin id
*Return  :  加了校验位的 ID
*******************************************************/
uint8   LinIdCalcParity(uint8 id)
{
  uint8 parity, p0,p1;
  parity=id & 0x3F;
  p0=( BIT(parity,0) ^ BIT(parity,1) ^ BIT(parity,2) ^ BIT(parity,4) ) << 6;     //偶校验位
  p1=( !( BIT(parity,1) ^ BIT(parity,3) ^ BIT(parity,4) ^ BIT(parity,5))) <<7;  //奇校验位
  parity|=(p0|p1);
  return parity;
}

/******************************************************
*Name    :  LinDatChecksum
*Function:  LIN data 校验计算
*Params  :  id : Lin id
*Params  :  data  lin 数据
*Return  :  加了校验位的 ID
*******************************************************/
uint8   LinDatChecksum(uint8 id, uint8 *data)
{
    uint32_t sum = id;
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        sum += data[i];
        if(sum & 0xFF00)
            sum = (sum & 0x00FF) + 1;
    }
    sum ^= 0x00FF;
    return (uint8_t)sum;
}

/*******************************************************************************************
*Name    :  LinReadData
*Function:  LIN 读数据函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2: lin2
*Return  :  linMsg
***********************************************************************************************/
linMsg LinReadData(linBASE_t *lin )
{
    linMsg  tMsg;
    uint8   i;
    tMsg.len    = (uint8)((uint32)((lin->FORMAT & 0x00070000U) >> 16U) + 1);
    tMsg.lin_id = (uint8)((uint32)(lin->ID & 0x003F0000U >> 16U));
    for (i=0; i<=(tMsg.len-1); i++)
        tMsg.data[i] = lin->RDx[i];
    return tMsg;
}


/*******************************************************************************************
*Name    :  LinSendData
*Function:  LIN 发送数据函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2:  lin2
*Return  :  uint8_t : 1--发送成功       0---失败
***********************************************************************************************/
void   LinSendData(linBASE_t *lin, linMsg *msg, uint8 maskid)
{
    uint8  len;
    uint8   i=0;

    len = msg->len;
    lin->FORMAT = ((lin->FORMAT & 0xFFF8FFFFU) |(uint32)((len - 1U) << 16U));

    while((lin->FLR & LIN_TX_READY != LIN_TX_READY) || (lin->FLR & 0x8U == 0x8U) );

    maskid = LinIdCalcParity(maskid);

    lin->ID = ((lin->ID & 0xFFFFFF00U) | (uint32)maskid);

    len = (uint8)((uint32)(lin->FORMAT & 0x00070000U) >> 16U);

    for (i=0; i<=len; i++)
        lin->TDx[len - i] = msg->data[len - i];

    while((lin->FLR & 0x800U) != 0x800U);
}

/*******************************************************************************************
*Name    :  LinSendHeader
*Function:  LIN 发送帧头函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2:  lin2\
*Params  :  id , 帧 ID
*Return  :  void
***********************************************************************************************/
void   LinSendHeader(linBASE_t *lin, uint8 id)
{
    uint8   p_id;

    p_id = LinIdCalcParity(id);

    while((!(linIsTxReady(lin))) || (lin->FLR & 0x8U == 0x8U) );

    lin->ID = (lin->ID & 0xFFFFFF00U) | ((uint32)p_id );
    linFlag = 1;
}


/******************************************************
*Name    :  Lin2Init
*Function:  Lin2  初始化函数
*Params  :
*Return  :  void
*******************************************************/
void Lin2Init(void)
{
    /** - Release from reset */
    linREG1->GCR0 = 0U;
    linREG1->GCR0 = 1U;

    /** - Start LIN configuration
    *     - Keep state machine in software reset
    */
    linREG1->GCR1 = 0U;

    /** - Disable all interrupts */
    linREG1->CLEARINT    = 0xFFFFFFFFU;
    linREG1->CLEARINTLVL = 0xFFFFFFFFU;


    /**   - Enable LIN Mode */
    linREG1->GCR1 = 0x40U;

    /** - global control 1 */
    linREG1->GCR1 |=(uint32)((uint32)1U << 25U)        /* enable transmit */
                  | (uint32)((uint32)1U << 24U)        /* enable receive */
                  | (uint32)((uint32)1U << 12U)        /* Enable HGENCTRL (Mask filtering with ID-Byte) */
                  | (uint32)((uint32)1U << 11U)        /* Use enhance checksum */
                  | (uint32)((uint32)1U << 10U)        /* enable multi buffer mode */
                  | (uint32)((uint32)1U << 6U)         /* enable lin mode */
                  | (uint32)((uint32)1U << 5U)         /* internal clock (device has no clock pin) */
                  | (uint32)((uint32)1U << 2U)         /* enable parity */
                  | (uint32)((uint32)0U << 0U);        /* lin length */

    linREG1->GCR2 = 0x00030000;

    /** - Setup maximum baud rate prescaler */
    linREG1->MBRSR = (uint32)3514U;

    /** - Setup baud rate prescaler */
    linREG1->BRS = (uint32)243U;

    /** - Setup RX and TX reception masks */
    linREG1->MASK = ((uint32)((uint32)0xFFU << 16U) | (uint32)0xFFU);

    /** - Setup compare
    *     - Sync delimiter
    *     - Sync break extension
    */
    linREG1->COMP = ((uint32)((uint32)(1U - 1U) << 8U) | ((uint32)13U - 13U));

    /** - Setup response length */
    linREG1->FORMAT = ((linREG2->FORMAT & 0xFFF8FFFFU) | (uint32)(((uint32)8U - 1U) << 16U));

    /** - Set LIN pins functional mode */
    linREG1->PIO0 = (uint32)((uint32)1U << 2U)  /* tx pin */
                  | (uint32)((uint32)1U << 1U); /* rx pin */

    /** - set LIN pins default output value */
    linREG1->PIO3 = (uint32)((uint32)0U << 2U)  /* tx pin */
                 | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins output direction */
    linREG1->PIO1 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins open drain enable */
    linREG1->PIO6 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins pullup/pulldown enable */
    linREG1->PIO7 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins pullup/pulldown select */
    linREG1->PIO8 = (uint32)((uint32)1U << 2U)  /* tx pin */
                  | (uint32)((uint32)1U << 1U);  /* rx pin */

    linREG1->SETINTLVL =((uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000200U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U);

    linREG1->SETINT =((uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000200U    //200
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U);

    /** - Finaly start LIN */
    linREG1->GCR1 |= 0x00000080U;


    /** - Release from reset */
    linREG2->GCR0 = 0U;
    linREG2->GCR0 = 1U;

    /** - Start LIN configuration
    *     - Keep state machine in software reset
    */
    linREG2->GCR1 = 0U;

    /** - Disable all interrupts */
    linREG2->CLEARINT    = 0xFFFFFFFFU;
    linREG2->CLEARINTLVL = 0xFFFFFFFFU;


    /**   - Enable LIN Mode */
    linREG2->GCR1 = 0x40U;

    /** - global control 1 */
    linREG2->GCR1 |=(uint32)((uint32)1U << 25U)        /* enable transmit */
                  | (uint32)((uint32)1U << 24U)        /* enable receive */
                  | (uint32)((uint32)1U << 12U)        /* Enable HGENCTRL (Mask filtering with ID-Byte) */
                  | (uint32)((uint32)1U << 11U)        /* Use enhance checksum */
                  | (uint32)((uint32)1U << 10U)        /* enable multi buffer mode */
                  | (uint32)((uint32)1U << 6U)         /* enable lin mode */
                  | (uint32)((uint32)1U << 5U)         /* internal clock (device has no clock pin) */
                  | (uint32)((uint32)1U << 2U)         /* enable parity */
                  | (uint32)((uint32)0U << 0U);        /* lin length */

    linREG2->GCR2 = 0x00030000;

    /** - Setup maximum baud rate prescaler */
    linREG2->MBRSR = (uint32)3514U;

    /** - Setup baud rate prescaler */
    linREG2->BRS = (uint32)243U;

    /** - Setup RX and TX reception masks */
    linREG2->MASK = ((uint32)((uint32)0xFFU << 16U) | (uint32)0xFFU);

    /** - Setup compare
    *     - Sync delimiter
    *     - Sync break extension
    */
    linREG2->COMP = ((uint32)((uint32)(1U - 1U) << 8U) | ((uint32)13U - 13U));

    /** - Setup response length */
    linREG2->FORMAT = ((linREG2->FORMAT & 0xFFF8FFFFU) | (uint32)(((uint32)8U - 1U) << 16U));

    /** - Set LIN pins functional mode */
    linREG2->PIO0 = (uint32)((uint32)1U << 2U)  /* tx pin */
                  | (uint32)((uint32)1U << 1U); /* rx pin */

    /** - set LIN pins default output value */
    linREG2->PIO3 = (uint32)((uint32)0U << 2U)  /* tx pin */
                 | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins output direction */
    linREG2->PIO1 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins open drain enable */
    linREG2->PIO6 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins pullup/pulldown enable */
    linREG2->PIO7 = (uint32)((uint32)0U << 2U)  /* tx pin */
                  | (uint32)((uint32)0U << 1U); /* rx pin */

    /** - set LIN pins pullup/pulldown select */
    linREG2->PIO8 = (uint32)((uint32)1U << 2U)  /* tx pin */
                  | (uint32)((uint32)1U << 1U);  /* rx pin */

    linREG2->SETINTLVL =((uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000200U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U
                       | (uint32)0x00000000U);

    linREG2->SETINT =((uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000200U    //200
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U
                    | (uint32)0x00000000U);

    /** - Finaly start LIN */
    linREG2->GCR1 |= 0x00000080U;

}
