/*
 * Sci_driver.c
 *
 *  Created on: 2018年12月27日
 *      Author: zhenh
 */

#include "HL_sci.h"
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "Sci_driver.h"
#include "HL_sys_vim.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define UART_TASK_PRIO      configMAX_PRIORITIES - 12
#define UART_STK_SIZE       configMINIMAL_STACK_SIZE

TaskHandle_t Uart1RecvTask_Handler;
void Uart1_Task(void *pvParameters);

TaskHandle_t Uart3RecvTask_Handler;
void Uart3_RecvTask(void *pvParameters);

TaskHandle_t Uart4RecvTask_Handler;
void Uart4_RecvTask(void *pvParameters);


QueueHandle_t Uart1_recv_QueHandle;
uint8   Uart1RecvBuf[UART1_Q_LEN];
uint8   Uart1RecvCount;


QueueHandle_t Uart3_recv_QueHandle;
uint8   Uart3RecvBuf[UART1_Q_LEN];
uint8   Uart3RecvCount;

QueueHandle_t Uart4_recv_QueHandle;
uint8   Uart4RecvBuf[UART1_Q_LEN];
uint8   Uart4RecvCount;


/******************************************************************
*Name    :  FreeRTOS_UartInit
*Function:  创建CAN任务，创建消息队列等等
*Params  :  void
*Return  :  uint8_t  1:成功      0：失败
*******************************************************************/
uint8_t    FreeRTOS_UartInit(void)
{
    uint8_t val;


    taskENTER_CRITICAL();


//    vimDisableInterrupt(Uart1_low_ch);
//    vimDisableInterrupt(Uart2_low_ch);
    vimDisableInterrupt(Uart3_low_ch);
    vimDisableInterrupt(Uart4_low_ch);

#if 0
    Uart2_recv_QueHandle = xQueueCreate(1, sizeof(Uart2RecvBuf));
    if(Uart2_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Uart2_RecvTask,
                    (const char*    )"Uart2Recv_Task",
                    (uint16_t       )UART2_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UART2_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Uart2RecvTask_Handler);
        val =(uint8_t) pdTRUE;
#if (DEBUG)
        UartSendString(sciREG3," UART2 is init: 115200-8-n-1  \r\n\0");
#endif

    }
    else
    {
        vQueueDelete(Uart2_recv_QueHandle);
        Uart2_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }
#endif

    Uart3_recv_QueHandle = xQueueCreate(1, sizeof(Uart3RecvBuf));
    if(Uart3_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Uart3_RecvTask,
                    (const char*    )"Uart3Recv_Task",
                    (uint16_t       )UART_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UART_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Uart3RecvTask_Handler);
        val =(uint8_t) pdTRUE;

#if (DEBUG)
        UartSendString(sciREG3," UART3 is init: 115200-8-n-1  \r\n\0");
#endif

    }
    else
    {
        vQueueDelete(Uart3_recv_QueHandle);
        Uart3_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

#if 0
    Uart4_recv_QueHandle = xQueueCreate(1, sizeof(Uart4RecvBuf));
    if(Uart4_recv_QueHandle !=NULL )
    {

        xTaskCreate((TaskFunction_t )Uart4_RecvTask,
                    (const char*    )"Uart4Recv_Task",
                    (uint16_t       )UART4_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UART4_TASK_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&Uart4RecvTask_Handler);
        val =(uint8_t) pdTRUE;

#if (DEBUG)
        UartSendString(sciREG4," UART4 is init: 115200-8-n-1  \r\n\0");
#endif
    }
    else
    {
        vQueueDelete(Uart4_recv_QueHandle);
        Uart4_recv_QueHandle = NULL;
        val = (uint8_t)pdFALSE;
    }

#endif

    taskEXIT_CRITICAL();

    return val;
}

uint16  UartPrintf(const char *fmt,...)
{
    uint16  i = 0;
    va_list args;
    uint16  len;
    char buf[1024];
    va_start(args,fmt);
    len = vsprintf(buf,fmt,args);
    va_end(args);
    for(i=0;i<len;i++)
        sciSendByte(DEBUGUART,buf[i]);
    return len;
}

//========================================================================
// 函数: UartSendString
// 描述: 把一个字符串从串口发送出去.
// 参数: msg,字符串指针.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void UartSendString(sciBASE_t *sci, uint8 *msg)
{
    uint8  i=0;
    while (msg[i] != '\0')
    {
        while ((sci->FLR & 0x4) == 4)
            ; /* wait until busy */
        sciSendByte(sci, msg[i]); /* send out text   */
        i++;
    };
}

//========================================================================
// 函数: UartSendHexU32
// 描述: 把一个32位长整型数转成十进制送串口发送.
// 参数: j: 要处理的32位整型数.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void    UartSendHexU32(sciBASE_t *sci,uint32 data)
{
    uint8  i,k;
    uint8  tmp[13];
    tmp[0] = '0';
    tmp[1] = 'x';
    for(i=8; i>0; i--)
    {
        k = ((uint8)data) & 0x0f;
        if(k <= 9)
            tmp[i+2-1] = k+'0';
        else
            tmp[i+2-1] = k-10+'A';
        data >>= 4;
    }
    tmp[10] = ' ';
    tmp[11] = ' ';
    tmp[12] = '\0';
    UartSendString(sci,tmp);
}

//========================================================================
// 函数: UartSendHexU16
// 描述: 把一个32位长整型数转成十进制送串口发送.
// 参数: j: 要处理的32位整型数.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void    UartSendHexU16(sciBASE_t *sci,uint16 data)
{
    uint8  i,k;
    uint8  tmp[7];
    tmp[0] = '0';
    tmp[1] = 'x';
    for(i=4; i>0; i--)
    {
        k = ((uint8)data) & 0x0f;
        if(k <= 9)
            tmp[i+2-1] = k+'0';
        else
            tmp[i+2-1] = k-10+'A';
        data >>= 4;
    }
    tmp[6] = '\0';
    UartSendString(sci,tmp);
}

//========================================================================
// 函数: UartSendHexU16
// 描述: 把一个32位长整型数转成十进制送串口发送.
// 参数: j: 要处理的32位整型数.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void    UartSendMac(sciBASE_t *sci,uint8 data)
{
    uint8  i,k;
    uint8  tmp[3];
    for(i=2; i>0; i--)
    {
        k = ((uint8)data) & 0x0f;
        if(k <= 9)
            tmp[i-1] = k+'0';
        else
            tmp[i-1] = k-10+'A';
        data >>= 4;
    }
    tmp[2] = '\0';
    UartSendString(sci,tmp);
}

//========================================================================
// 函数: UartSendHexU16
// 描述: 把一个32位长整型数转成十进制送串口发送.
// 参数: j: 要处理的32位整型数.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void    UartSendByte(sciBASE_t *sci,uint8 data)
{
    uint8   i,count = 3;
    uint8  tmp[4];
    tmp[0] = data /100;
    tmp[1] = ( data - tmp[0]*100 )/10;
    tmp[2] = data - tmp[0]*100 - tmp[1]*10;
    tmp[3] = '\0';
    if(tmp[0] == 0 )
    {
        tmp[0] = tmp[1];
        tmp[1] = tmp[2];
        tmp[2] = '\0';
        count--;
    }
    if(tmp[0] == 0)
    {
        tmp[0] = tmp[1];
        tmp[1] = tmp[2];
        tmp[2] = '\0';
        count--;
    }

    for(i=0; i<count; i++)
    {
        if(tmp[i]<= 9)
            tmp[i] = 0x30 + tmp[i];
    }
    UartSendString(sci,tmp);
}

//========================================================================
// 函数: UartSendHexU16
// 描述: 把一个32位长整型数转成十进制送串口发送.
// 参数: j: 要处理的32位整型数.
// 返回: none.
// 版本: V1.0, 2013-4-29
//========================================================================
void    UartSendRtc(sciBASE_t *sci,uint8 data)
{
    uint8  i,k;
    uint8  tmp[4];
    for(i=2; i>0; i--)
    {
        k = ((uint8)data) & 0x0f;
        if(k <= 9)
            tmp[i-1] = k+'0';
        else
            tmp[i-1] = k-10+'A';
        data >>= 4;
    }
    tmp[2] = ' ';
    tmp[3] = '\0';
    UartSendString(sci,tmp);
}

#pragma CODE_STATE(Uart1_HwiISR, 32)
#pragma INTERRUPT(Uart1_HwiISR, IRQ)
void Uart1_HwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    uint8 byte;

    uint32 vec = sciREG1->INTVECT1;
    switch (vec)
    {
    case 11U:
        /* receive */
        byte = (uint8)(sciREG1->RD & 0x000000FFU);
        if (byte != 0x0d)
        {
            Uart1RecvBuf[Uart1RecvCount] = byte;
            Uart1RecvCount++;
            sciSendByte(sciREG1,byte);
        }
        else
        {
            Uart1RecvBuf[Uart1RecvCount] = '\0';
            Uart1RecvCount++;
            sciSendByte(sciREG1,byte);
            sciSendByte(sciREG1,'\r');

            xQueueSendFromISR(Uart1_recv_QueHandle,Uart1RecvBuf,&xHigherPriorityTaskWoken);
            memset(Uart1RecvBuf,0,Uart1RecvCount);
            Uart1RecvCount = 0;
            vTaskNotifyGiveFromISR(Uart1RecvTask_Handler,&xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG1->FLR = sciREG1->SETINTLVL & 0x07000303U;
         break;
    }
/* USER CODE BEGIN (32) */
/* USER CODE END */
}


void Uart1_RecvTask(void *pvParameters)
{
    uint8   uartbuf[UART1_Q_LEN];
    BaseType_t err;

    vimEnableInterrupt(Uart1_low_ch,SYS_IRQ);

    memset(uartbuf,0,UART1_Q_LEN);
    UartSendString(sciREG1,"TMS570LC4357 UART1  Test ,115200-8-n-1 \r\n\0");
    UartSendString(sciREG1,"Please send a character \r\n\0");
    UartSendString(sciREG1," \r\n\0");
    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
            if (xQueueReceive(Uart1_recv_QueHandle,uartbuf,0))
            {
                UartSendString(sciREG1,"Your sent is : \0");
                UartSendString(sciREG1,uartbuf);
                UartSendString(sciREG1,"\r\n\r\n\0");
                memset(uartbuf,0,UART1_Q_LEN);
            }
        }
        else if(err==pdFALSE)
        {
            vTaskDelay(15);
        }
    }
}

//===============================================================================

//===============================================================================
#pragma CODE_STATE(Uart3_HwiISR, 32)
#pragma INTERRUPT(Uart3_HwiISR, IRQ)
void Uart3_HwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    uint8 byte;

    uint32 vec = sciREG3->INTVECT1;
    switch (vec)
    {
    case 11U:
        /* receive */
        byte = (uint8)(sciREG3->RD & 0x000000FFU);
        if (byte != 0x0d)
        {
            Uart3RecvBuf[Uart3RecvCount] = byte;
            Uart3RecvCount++;
            sciSendByte(sciREG3,byte);
        }
        else
        {
            Uart3RecvBuf[Uart3RecvCount] = '\0';
            Uart3RecvCount++;
            sciSendByte(sciREG3,byte);
            sciSendByte(sciREG3,'\r');

            xQueueSendFromISR(Uart3_recv_QueHandle,Uart3RecvBuf,&xHigherPriorityTaskWoken);
            memset(Uart3RecvBuf,0,Uart3RecvCount);
            Uart3RecvCount = 0;
            vTaskNotifyGiveFromISR(Uart3RecvTask_Handler,&xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG3->FLR = sciREG3->SETINTLVL & 0x07000303U;
         break;
    }
/* USER CODE BEGIN (32) */
/* USER CODE END */
}


void Uart3_RecvTask(void *pvParameters)
{
    uint8   uartbuf[UART1_Q_LEN];
    BaseType_t err;

    vimEnableInterrupt(Uart3_low_ch,SYS_IRQ);

    memset(uartbuf,0,UART1_Q_LEN);
    UartSendString(sciREG3,"TMS570LC4357 UART3  Test ,115200-8-n-1 \r\n\0");
    UartSendString(sciREG3,"Please send a character \r\n\0");
    UartSendString(sciREG3," \r\n\0");
    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
            if (xQueueReceive(Uart3_recv_QueHandle,uartbuf,0))
            {
                UartSendString(sciREG3,"Your sent is : \0");
                UartSendString(sciREG3,uartbuf);
                UartSendString(sciREG3,"\r\n\r\n\0");
                memset(uartbuf,0,UART1_Q_LEN);
            }
        }
        else if(err==pdFALSE)
        {
            vTaskDelay(15);
        }
    }
}

//===============================================================================
#pragma CODE_STATE(Uart4_HwiISR, 32)
#pragma INTERRUPT(Uart4_HwiISR, IRQ)
void Uart4_HwiISR(void)
{
    BaseType_t  xHigherPriorityTaskWoken;
    uint8 byte;

    uint32 vec = sciREG4->INTVECT1;
    switch (vec)
    {
    case 11U:
        /* receive */
        byte = (uint8)(sciREG4->RD & 0x000000FFU);
        if (byte != 0x0d)
        {
            Uart4RecvBuf[Uart4RecvCount] = byte;
            Uart4RecvCount++;
            sciSendByte(sciREG4,byte);
        }
        else
        {
            Uart4RecvBuf[Uart4RecvCount] = '\0';
            Uart4RecvCount++;
            sciSendByte(sciREG4,byte);
            sciSendByte(sciREG4,'\r');

            xQueueSendFromISR(Uart4_recv_QueHandle,Uart4RecvBuf,&xHigherPriorityTaskWoken);
            memset(Uart4RecvBuf,0,Uart4RecvCount);
            Uart4RecvCount = 0;
            vTaskNotifyGiveFromISR(Uart4RecvTask_Handler,&xHigherPriorityTaskWoken);

            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG4->FLR = sciREG4->SETINTLVL & 0x07000303U;
         break;
    }
/* USER CODE BEGIN (32) */
/* USER CODE END */
}


void Uart4_RecvTask(void *pvParameters)
{
    uint8   uartbuf[UART1_Q_LEN];
    BaseType_t err;

    vimEnableInterrupt(Uart4_low_ch,SYS_IRQ);

    memset(uartbuf,0,UART1_Q_LEN);
    UartSendString(sciREG4,"TMS570LC4357 UART4  Test ,115200-8-n-1 \r\n\0");
    UartSendString(sciREG4,"Please send a character \r\n\0");
    UartSendString(sciREG4," \r\n\0");
    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
            if (xQueueReceive(Uart4_recv_QueHandle,uartbuf,0))
            {
                UartSendString(sciREG4,"Your sent is : \0");
                UartSendString(sciREG4,uartbuf);
                UartSendString(sciREG4,"\r\n\r\n\0");
                memset(uartbuf,0,UART1_Q_LEN);
            }
        }
        else if(err==pdFALSE)
        {
            vTaskDelay(15);
        }
    }
}
