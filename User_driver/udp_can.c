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
#include "HL_can.h"
#include "HL_sci.h"

#include "Can_driver.h"
#include "Ultrasonic.h"
#include "time_common.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

#include "string.h"

QueueHandle_t udp_recv_que_handle;
static void UdpSendDateTask( void *pvParameters );
static void UdpRecvDateTask( void *pvParameters );
xTaskHandle  UdpSend_Task_Handle,UdpRecv_Task_Handle;


void    FreeRTOS_udp_can_Init(void)
{
    taskENTER_CRITICAL();

    udp_recv_que_handle = xQueueCreate(1, sizeof(Ultrasonic));

    if(udp_recv_que_handle !=NULL)
    {
        xTaskCreate((TaskFunction_t )UdpSendDateTask,
                    (const char*    )"UDPSend",
                    (uint16_t       )configMINIMAL_STACK_SIZE*2,
                    (void*          )NULL,
                    (UBaseType_t    )tskIDLE_PRIORITY + 5 | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&UdpSend_Task_Handle);
    }
    else
    {
        vQueueDelete(udp_recv_que_handle);
        udp_recv_que_handle = NULL;
    }
#if 1
    xTaskCreate((TaskFunction_t )UdpRecvDateTask,
                (const char*    )"UDPRecv",
                (uint16_t       )configMINIMAL_STACK_SIZE*2,
                (void*          )NULL,
                (UBaseType_t    )tskIDLE_PRIORITY + 6 | portPRIVILEGE_BIT,
                (TaskHandle_t*  )&UdpRecv_Task_Handle);
#endif
    taskEXIT_CRITICAL();


}
Socket_t xSocket;
/*
static void UdpSendDateTask( void *pvParameters )
{
    BaseType_t err;
    Ultrasonic  ultra_queue;

//    Socket_t xSocket;
    struct  freertos_sockaddr xDestinationAddress;
    uint8_t *dat,i;
    uint16_t  tmp_canid;
   // Create the socket.
    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

   // Check the socket was created.
    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

   // xDestinationAddress.sin_port = FreeRTOS_htons( 20000 );
   // FreeRTOS_bind( xSocket, &xDestinationAddress, sizeof( xDestinationAddress ) );

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr( "192.168.1.40" );
    xDestinationAddress.sin_port = FreeRTOS_htons( 10000 );

//    dat = (uint8_t *)pvPortMalloc(1);
//    *dat = 0;
//
//    FreeRTOS_sendto( xSocket,
//                     (void *)dat,
//                      1 ,
//                      0,
//                      &xDestinationAddress,
//                      sizeof( xDestinationAddress ) );
//    vPortFree(dat);
//    xTaskNotifyGive(UdpRecv_Task_Handle);

    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);  //
        if(err==pdTRUE)
        {
            if (xQueueReceive(udp_recv_que_handle,&ultra_queue,0))
            {
                dat = (uint8_t *)pvPortMalloc(sizeof(ultra_queue));
                if(dat !=NULL)
                {
                    tmp_canid =(uint32_t) ((ultra_queue.id & 0xFFFC0000)>>18);
                    memcpy(dat,&tmp_canid, 4);
                    memcpy(dat+4,ultra_queue.data,16);
//                    memcpy(dat+20,ultra_queue.header.frame_id,15);
//                    memcpy(dat+35,ultra_queue.header.stamp.nanosec,4);
//                    memcpy(dat+39,ultra_queue.header.stamp.sec,4);
                    FreeRTOS_sendto( xSocket,
                                     (void *)dat,
                                      sizeof(ultra_queue) ,
                                      0,
                                      &xDestinationAddress,
                                      sizeof( xDestinationAddress ) );
                    vPortFree(dat);
                }
                else
                {
                    vPortFree(dat);
                }
            }
            else if(err==pdFALSE)
            {
                vTaskDelay(5);
            }
        }

    }
}
*/
uint8_t str1[60];

static void UdpSendDateTask( void *pvParameters )
{
    uint8_t  flag = 0;
    uint8_t  str[] = " TMS570LC4357  Udp test!  MCU MAC <---> 1105S port0  !\r\n";
    struct  freertos_sockaddr xDestinationAddress,xClient;
    uint8_t cReceivedString[60];
/*
    uint32_t xClientLength = sizeof( xClient );
    uint8_t flag_rec = 0;
    uint8_t i;
*/
   // Create the socket.
    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,         //FREERTOS_SOCK_DGRAM for UDP.
                               FREERTOS_IPPROTO_UDP );

   // Check the socket was created.
    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

    xDestinationAddress.sin_port = FreeRTOS_htons( 20000 );   // local port
    FreeRTOS_bind( xSocket, &xDestinationAddress, sizeof( xDestinationAddress ) );

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr_quick(192,168,1,40);  // host ip
    xDestinationAddress.sin_port = FreeRTOS_htons( 10000 );    // host port

    while(1)
    {
        if (flag)
        {
            FreeRTOS_sendto( xSocket,
                             cReceivedString,
                             sizeof(cReceivedString) ,
                              0,
                              &xDestinationAddress,
                              sizeof( xDestinationAddress ) );
            flag = 0;
        }
        else
        {
            FreeRTOS_sendto( xSocket,
                             str,
                             sizeof(str) ,
                              0,
                              &xDestinationAddress,
                              sizeof( xDestinationAddress ) );
        }

        xTaskNotifyGive(UdpRecv_Task_Handle);

/*
        memset(cReceivedString,00,60);

        flag_rec = FreeRTOS_recvfrom( xSocket,
                                      cReceivedString,
                                      sizeof( cReceivedString ),
                                      0,
                                      &xClient,
                                      &xClientLength );
        if( cReceivedString[0])
        {
            for(i=0;i<60;i++)
            {
                if (!cReceivedString[i])
                    break;
            }
            cReceivedString[i++]=' ';
            cReceivedString[i++]=' ';
            cReceivedString[i++]='M';
            cReceivedString[i++]='C';
            cReceivedString[i++]='U';
            cReceivedString[i++]=' ';
            cReceivedString[i++]='M';
            cReceivedString[i++]='A';
            cReceivedString[i++]='C';
            cReceivedString[i++]='<';
            cReceivedString[i++]='-';
            cReceivedString[i++]='-';
            cReceivedString[i++]='-';
            cReceivedString[i++]='>';
            cReceivedString[i++]='1';
            cReceivedString[i++]='1';
            cReceivedString[i++]='0';
            cReceivedString[i++]='5';
            cReceivedString[i++]=' ';
            cReceivedString[i++]='p';
            cReceivedString[i++]='o';
            cReceivedString[i++]='r';
            cReceivedString[i++]='t';
            cReceivedString[i++]='0';
            cReceivedString[i++]=' ';
            cReceivedString[i++]='!';

            flag = 1;

        }
*/
        vTaskDelay(500);

    }
}

static void UdpRecvDateTask( void *pvParameters )
{
    uint8_t cReceivedString[60];
    uint8_t i;
    struct freertos_sockaddr xClient;
    uint32_t xClientLength = sizeof( xClient );
    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

   for( ;; )
   {
       memset(cReceivedString,00,60);

       i = FreeRTOS_recvfrom( xSocket,
                              cReceivedString,
                              sizeof( cReceivedString ),
                              0,
                              &xClient,
                             &xClientLength );
       if( cReceivedString[0])
       {
           for(i=0;i<60;i++)
           {
               if (!cReceivedString[i])
                   break;
           }
           cReceivedString[i++]=' ';
           cReceivedString[i++]=' ';
           cReceivedString[i++]='M';
           cReceivedString[i++]='C';
           cReceivedString[i++]='U';
           cReceivedString[i++]=' ';
           cReceivedString[i++]='M';
           cReceivedString[i++]='A';
           cReceivedString[i++]='C';
           cReceivedString[i++]='<';
           cReceivedString[i++]='-';
           cReceivedString[i++]='-';
           cReceivedString[i++]='-';
           cReceivedString[i++]='>';
           cReceivedString[i++]='1';
           cReceivedString[i++]='1';
           cReceivedString[i++]='0';
           cReceivedString[i++]='5';
           cReceivedString[i++]=' ';
           cReceivedString[i++]='p';
           cReceivedString[i++]='o';
           cReceivedString[i++]='r';
           cReceivedString[i++]='t';
           cReceivedString[i++]='0';
           cReceivedString[i++]=' ';
           cReceivedString[i++]='!';
           cReceivedString[i++]='\r';
           cReceivedString[i++]='\n';
           cReceivedString[i++]='\0';
           UartSendString(sciREG1,cReceivedString);
       }

       else
       {
           vTaskDelay(20);
       }
   }

}

