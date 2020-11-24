/******************************************************************
FileName   :Can_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2018-12-29
****************************************************************/

#include <can_driver.h>
#include <udp_can.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "HL_can.h"
#include "HL_sci.h"

#include "time_common.h"

#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"

#include "string.h"

#define UDP_DEBUG_CNT     0

//#define UDP_SEND_PRIO     19
//#define UDP_RECV_PRIO     20
#define UDP_SEND_PRIO   configMAX_PRIORITIES - 7
#define UDP_RECV_PRIO   configMAX_PRIORITIES - 9
#define UDP_STK_SIZE    configMINIMAL_STACK_SIZE*3

extern  TaskHandle_t    TASK_NOTIFY(Can1,send), TASK_NOTIFY(Can2,send), TASK_NOTIFY(Can3,send), TASK_NOTIFY(Can4,send);
extern  QueueHandle_t   DATA_QUE(Can1,send),  DATA_QUE(Can2,send),  DATA_QUE(Can3,send),  DATA_QUE(Can4,send);

QueueHandle_t   DATA_QUE(udp1,recv), DATA_QUE(udp2,recv), DATA_QUE(udp3,recv), DATA_QUE(udp4,recv);
TaskHandle_t    TASK_NOTIFY(udp1,send), TASK_NOTIFY(udp2,send), TASK_NOTIFY(udp3,send), TASK_NOTIFY(udp4,send);
TaskHandle_t    TASK_NOTIFY(udp1,recv), TASK_NOTIFY(udp2,recv), TASK_NOTIFY(udp3,recv), TASK_NOTIFY(udp4,recv);

static void FUNC_R(udp1,send)( void *pvParameters );
static void FUNC_R(udp1,recv)( void *pvParameters );
static void FUNC_R(udp2,send)( void *pvParameters );
static void FUNC_R(udp2,recv)( void *pvParameters );
static void FUNC_R(udp3,send)( void *pvParameters );
static void FUNC_R(udp3,recv)( void *pvParameters );
static void FUNC_R(udp4,send)( void *pvParameters );
static void FUNC_R(udp4,recv)( void *pvParameters );

uint32  FrameCnt[16] = {0};

uint16  SendCanMsgToUdp(uint8 *p, QueueHandle_t canR_udpS_que, uint32 sequence );
void    SendUdpPackToCan(int dataLen, uint8 *p, QueueHandle_t UdpToCan_queue,TaskHandle_t  TaskHandle);

uint8    FreeRTOS_udp_can_Init(void)
{
    taskENTER_CRITICAL();
    uint8_t val;

    DATA_QUE(udp1,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canlloni_frame));
    if(DATA_QUE(udp1,recv) !=NULL)
    {
        xTaskCreate((TaskFunction_t )FUNC_R(udp1,send),
                    (const char*    )FUNC_S(udp1_send),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp1,send));

        xTaskCreate((TaskFunction_t )FUNC_R(udp1,recv),
                    (const char*    )FUNC_S(udp1_recv),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp1,recv));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(udp1,recv));
        DATA_QUE(udp1,recv) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(udp2,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canlloni_frame));
    if(DATA_QUE(udp2,recv) !=NULL)
    {
        xTaskCreate((TaskFunction_t )FUNC_R(udp2,send),
                    (const char*    )FUNC_S(udp2_send),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp2,send));

        xTaskCreate((TaskFunction_t )FUNC_R(udp2,recv),
                    (const char*    )FUNC_S(udp2_recv),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp2,recv));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(udp2,recv));
        DATA_QUE(udp2,recv) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(udp3,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canlloni_frame));
    if(DATA_QUE(udp3,recv) !=NULL)
    {
        xTaskCreate((TaskFunction_t )FUNC_R(udp3,send),
                    (const char*    )FUNC_S(udp3_send),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp3,send));

        xTaskCreate((TaskFunction_t )FUNC_R(udp3,recv),
                    (const char*    )FUNC_S(udp3_recv),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp3,recv));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(udp3,recv));
        DATA_QUE(udp3,recv) = NULL;
        val = (uint8_t)pdFALSE;
    }

    DATA_QUE(udp4,recv) = xQueueCreate(CAN_Q_NUM, sizeof(canlloni_frame));
    if(DATA_QUE(udp4,recv) !=NULL)
    {
        xTaskCreate((TaskFunction_t )FUNC_R(udp4,send),
                    (const char*    )FUNC_S(udp4_send),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_SEND_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp4,send));

        xTaskCreate((TaskFunction_t )FUNC_R(udp4,recv),
                    (const char*    )FUNC_S(udp4_recv),
                    (uint16_t       )UDP_STK_SIZE,
                    (void*          )NULL,
                    (UBaseType_t    )UDP_RECV_PRIO | portPRIVILEGE_BIT,
                    (TaskHandle_t*  )&TASK_NOTIFY(udp4,recv));

        val =(uint8_t) pdTRUE;
    }
    else
    {
        vQueueDelete(DATA_QUE(udp4,recv));
        DATA_QUE(udp4,recv) = NULL;
        val = (uint8_t)pdFALSE;
    }

    taskEXIT_CRITICAL();
    return val;
}


static void FUNC_R(udp1,send)( void *pvParameters )
{
    BaseType_t  err;
    Socket_t    xSocket;
    struct      freertos_sockaddr xDestinationAddress;
    uint8       p[80];
    uint16_t    length = 0;

    uint32_t    udp_sequence_number = 0;

#if UDP_DEBUG_CNT
    uint32_t    counter = 0;
#endif

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr( REMOTE_IP_ADDR );
    xDestinationAddress.sin_port = FreeRTOS_htons( CANNELLONI_REMOTE_PORT1 );

    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
//            p = (uint8 *)pvPortMalloc(sizeof(struct _CANFD_FRAME) * CAN_Q_NUM + CANNELLONI_DATA_PACKET_BASE_SIZE );

            length = SendCanMsgToUdp(p, DATA_QUE(udp1,recv), udp_sequence_number );
            udp_sequence_number++;

#if UDP_DEBUG_CNT
            *(p + length    ) = (uint8)((counter >> 24 )& 0xFF );
            *(p + length +1 ) = (uint8)((counter >> 16 )& 0xFF );
            *(p + length +2 ) = (uint8)((counter >> 8 )& 0xFF );
            *(p + length +3 ) = (uint8)(counter & 0xFF );
            counter++;
            length += 4;
#endif
            FreeRTOS_sendto( xSocket,p,length, 0, &xDestinationAddress, sizeof( xDestinationAddress ) );
            FrameCnt[8]++;
//            vPortFree(p);

        }
    }
}


static void FUNC_R(udp1,recv)( void *pvParameters )
{
    int     datLen;

    uint8   pdat[80];
    struct freertos_sockaddr xClient, xBindAddress;
    uint32_t xClientLength = sizeof( xClient );
    xSocket_t xListeningSocket;
    const TickType_t xReceiveTimeOut = 200 / portTICK_PERIOD_MS;

    xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                                        FREERTOS_SOCK_DGRAM,
                                        FREERTOS_IPPROTO_UDP );

    configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

    xBindAddress.sin_port = FreeRTOS_htons(CANNELLONI_PORT1);
    FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );


    FreeRTOS_setsockopt( xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        0 );

   while(1)
   {

       datLen = FreeRTOS_recvfrom( xListeningSocket,
                                   (void *)pdat,
                                   sizeof(pdat),
                                   0,
                                   &xClient,
                                   &xClientLength );
       if (datLen > 0)
       {
           SendUdpPackToCan(datLen,pdat,DATA_QUE(Can1,send),TASK_NOTIFY(Can1,send));
           FrameCnt[9]++;
       }
   }

}

//============================= CAN2<-->UDP (Send and receive)====================================
static void FUNC_R(udp2,send)( void *pvParameters )
{
    BaseType_t  err;
    Socket_t    xSocket;
    struct      freertos_sockaddr xDestinationAddress;
    uint8       p[80];
    uint16_t    length = 0;

    uint32_t    udp_sequence_number = 0;

#if UDP_DEBUG_CNT
    uint32_t    counter = 0;
#endif

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr( REMOTE_IP_ADDR );
    xDestinationAddress.sin_port = FreeRTOS_htons( CANNELLONI_REMOTE_PORT2 );

    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
//            p = (uint8 *)pvPortMalloc(sizeof(struct _CANFD_FRAME) * CAN_Q_NUM + CANNELLONI_DATA_PACKET_BASE_SIZE );

            length = SendCanMsgToUdp(p, DATA_QUE(udp2,recv), udp_sequence_number );
            udp_sequence_number++;

#if UDP_DEBUG_CNT
            *(p + length    ) = (uint8)((counter >> 24 )& 0xFF );
            *(p + length +1 ) = (uint8)((counter >> 16 )& 0xFF );
            *(p + length +2 ) = (uint8)((counter >> 8 )& 0xFF );
            *(p + length +3 ) = (uint8)(counter & 0xFF );
            counter++;
            length += 4;
#endif

            FreeRTOS_sendto( xSocket,p,length, 0, &xDestinationAddress, sizeof( xDestinationAddress ) );
            FrameCnt[10]++;
//            vPortFree(p);

        }
    }
}


static void FUNC_R(udp2,recv)( void *pvParameters )
{
    int     datLen;

    uint8   pdat[80];
    struct freertos_sockaddr xClient, xBindAddress;
    uint32_t xClientLength = sizeof( xClient );
    xSocket_t xListeningSocket;
    const TickType_t xReceiveTimeOut = 200 / portTICK_PERIOD_MS;

    xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                                        FREERTOS_SOCK_DGRAM,
                                        FREERTOS_IPPROTO_UDP );

    configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

    xBindAddress.sin_port = FreeRTOS_htons(CANNELLONI_PORT2);
    FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );


    FreeRTOS_setsockopt( xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        0 );

   while(1)
   {

       datLen = FreeRTOS_recvfrom( xListeningSocket,
                                   (void *)pdat,
                                   sizeof(pdat),
                                   0,
                                   &xClient,
                                   &xClientLength );
       if (datLen > 0)
       {
           SendUdpPackToCan(datLen,pdat,DATA_QUE(Can2,send),TASK_NOTIFY(Can2,send));
           FrameCnt[11]++;

       }

   }

}

//============================= CAN3<-->UDP (Send and receive)====================================
static void FUNC_R(udp3,send)( void *pvParameters )
{
    BaseType_t  err;
    Socket_t    xSocket;
    struct      freertos_sockaddr xDestinationAddress;
    uint8       p[80];
    uint16_t    length = 0;

    uint32_t    udp_sequence_number = 0;

#if UDP_DEBUG_CNT
    uint32_t    counter = 0;
#endif

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr( REMOTE_IP_ADDR );
    xDestinationAddress.sin_port = FreeRTOS_htons( CANNELLONI_REMOTE_PORT3 );

    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
//            p = (uint8 *)pvPortMalloc(sizeof(struct _CANFD_FRAME) * CAN_Q_NUM + CANNELLONI_DATA_PACKET_BASE_SIZE );

            length = SendCanMsgToUdp(p, DATA_QUE(udp3,recv), udp_sequence_number );
            udp_sequence_number++;

#if UDP_DEBUG_CNT
            *(p + length    ) = (uint8)((counter >> 24 )& 0xFF );
            *(p + length +1 ) = (uint8)((counter >> 16 )& 0xFF );
            *(p + length +2 ) = (uint8)((counter >> 8 )& 0xFF );
            *(p + length +3 ) = (uint8)(counter & 0xFF );
            counter++;
            length += 4;
#endif

            FreeRTOS_sendto( xSocket,p,length, 0, &xDestinationAddress, sizeof( xDestinationAddress ) );
            FrameCnt[12]++;
//            vPortFree(p);

        }
    }
}


static void FUNC_R(udp3,recv)( void *pvParameters )
{
    int     datLen;

    uint8   pdat[80];
    struct freertos_sockaddr xClient, xBindAddress;
    uint32_t xClientLength = sizeof( xClient );
    xSocket_t xListeningSocket;
    const TickType_t xReceiveTimeOut = 200 / portTICK_PERIOD_MS;

    xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                                        FREERTOS_SOCK_DGRAM,
                                        FREERTOS_IPPROTO_UDP );

    configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

    xBindAddress.sin_port = FreeRTOS_htons(CANNELLONI_PORT3);
    FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );


    FreeRTOS_setsockopt( xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        0 );

   while(1)
   {

       datLen = FreeRTOS_recvfrom( xListeningSocket,
                                   (void *)pdat,
                                   sizeof(pdat),
                                   0,
                                   &xClient,
                                   &xClientLength );
       if (datLen > 0)
       {
           SendUdpPackToCan(datLen,pdat,DATA_QUE(Can3,send),TASK_NOTIFY(Can3,send));
           FrameCnt[13]++;
       }

   }

}

//============================= CAN4<-->UDP (Send and receive)====================================
static void FUNC_R(udp4,send)( void *pvParameters )
{
    BaseType_t  err;
    Socket_t    xSocket;
    struct      freertos_sockaddr xDestinationAddress;
    uint8       p[80];
    uint16_t    length = 0;

    uint32_t    udp_sequence_number = 0;

#if UDP_DEBUG_CNT
    uint32_t    counter = 0;
#endif

    xDestinationAddress.sin_addr = FreeRTOS_inet_addr( REMOTE_IP_ADDR );
    xDestinationAddress.sin_port = FreeRTOS_htons( CANNELLONI_REMOTE_PORT4 );

    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

    configASSERT( xSocket != FREERTOS_INVALID_SOCKET );

    while(1)
    {
        err = ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(err==pdTRUE)
        {
//            p = (uint8 *)pvPortMalloc(sizeof(struct _CANFD_FRAME) * CAN_Q_NUM + CANNELLONI_DATA_PACKET_BASE_SIZE );

            length = SendCanMsgToUdp(p, DATA_QUE(udp4,recv), udp_sequence_number );
            udp_sequence_number++;

#if UDP_DEBUG_CNT
            *(p + length    ) = (uint8)((counter >> 24 )& 0xFF );
            *(p + length +1 ) = (uint8)((counter >> 16 )& 0xFF );
            *(p + length +2 ) = (uint8)((counter >> 8 )& 0xFF );
            *(p + length +3 ) = (uint8)(counter & 0xFF );
            counter++;
            length += 4;
#endif

            FreeRTOS_sendto( xSocket,p,length, 0, &xDestinationAddress, sizeof( xDestinationAddress ) );
            FrameCnt[14]++;
//            vPortFree(p);

        }
    }
}


static void FUNC_R(udp4,recv)( void *pvParameters )
{
    int     datLen;

    uint8   pdat[80];
    struct freertos_sockaddr xClient, xBindAddress;
    uint32_t xClientLength = sizeof( xClient );
    xSocket_t xListeningSocket;
    const TickType_t xReceiveTimeOut = 200 / portTICK_PERIOD_MS;

    xListeningSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                                        FREERTOS_SOCK_DGRAM,
                                        FREERTOS_IPPROTO_UDP );

    configASSERT( xListeningSocket != FREERTOS_INVALID_SOCKET );

    xBindAddress.sin_port = FreeRTOS_htons(CANNELLONI_PORT4);
    FreeRTOS_bind( xListeningSocket, &xBindAddress, sizeof( xBindAddress ) );


    FreeRTOS_setsockopt( xListeningSocket,
                        0,
                        FREERTOS_SO_RCVTIMEO,
                        &xReceiveTimeOut,
                        0 );

   while(1)
   {

       datLen = FreeRTOS_recvfrom( xListeningSocket,
                                   (void *)pdat,
                                   sizeof(pdat),
                                   0,
                                   &xClient,
                                   &xClientLength );
       if (datLen > 0)
       {
           SendUdpPackToCan(datLen,pdat,DATA_QUE(Can4,send),TASK_NOTIFY(Can4,send));
           FrameCnt[15]++;
       }

   }

}

//=========================================================================
void    SendUdpPackToCan(int dataLen, uint8 *p, QueueHandle_t UdpToCan_queue,TaskHandle_t  TaskHandle)
{
    uint8_t i;
    canMsg  can_msg;
    uint32  can_id;

    BaseType_t err = pdTRUE;
    uint16_t    frameCount = 0;

    if ( p[0] != CANNELLONI_FRAME_VERSION)
        err = pdFALSE;
    if ( p[1] != DATA)
        err = pdFALSE;

    frameCount = (uint16)(p[3] << 8 | p[4]);

    if ( frameCount == 0 )
        err = pdFALSE;

    if(err != pdFALSE)
    {
#if 0
        uint8  *dat = p +   CANNELLONI_DATA_PACKET_BASE_SIZE;
        can_id = (uint32_t)((dat[0]<<24) | (dat[1]<<16) | (dat[2]<<8) | dat[3] );
        dat += sizeof(can_msg.can_id);
        for (i=0;i<frameCount;i++ )
        {
            can_msg.can_id = can_id;
            can_msg.dlc = *dat;
            dat += sizeof(can_msg.dlc);
            if(( can_msg.can_id & CAN_RTR_FLAG) == 0)
            {
                if(dat - p + sizeof(can_msg.dlc) > dataLen)
                {
                    err = pdFALSE;
                    break;
                }

                memcpy(can_msg.data,dat,can_msg.dlc);
                dat += can_msg.dlc;
                xQueueSendToBack(UdpToCan_queue,&can_msg,0);
                can_msg.can_id = 0;
                can_msg.dlc    = 0;
                memset(can_msg.data,0,8);
            }
        }
#endif

       uint8  *dat = p +   CANNELLONI_DATA_PACKET_BASE_SIZE;
       for (i=0;i<frameCount;i++ )
       {
//           can_id = (uint32_t)(( *dat<<24) | (*(dat+1)<<16) | (*(dat+2)<<8) | *(dat+3) );
           can_id = (uint32_t)((dat[0]<<24) | (dat[1]<<16) | (dat[2]<<8) | dat[3] );
           can_msg.can_id = can_id;
           dat += sizeof(can_msg.can_id);

           can_msg.dlc = *dat;
           dat += sizeof(can_msg.dlc);

           if(( can_msg.can_id & CAN_RTR_FLAG) == 0)
           {
               if(dat - p + sizeof(can_msg.dlc) > dataLen)
               {
                   err = pdFALSE;
                   break;
               }

               memcpy(can_msg.data,dat,can_msg.dlc);
               dat += can_msg.dlc;
               xQueueSendToBack(UdpToCan_queue,&can_msg,0);
               can_msg.can_id = 0;
               can_msg.dlc    = 0;
               memset(can_msg.data,0,8);
           }

       }
       xTaskNotifyGive(TaskHandle);
    }
}

uint16 SendCanMsgToUdp(uint8 *p, QueueHandle_t canR_udpS_que, uint32 sequence )
{
    canlloni_frame  can_udp_msg;
    uint16      frameCount = 0;
    uint16      len;
    uint8       *dat = p + CANNELLONI_DATA_PACKET_BASE_SIZE;
    while(xQueueReceive(canR_udpS_que,&can_udp_msg,0))
    {
//        dat[0] = can_udp_msg.can_id >> 24 & 0x000000ff;
//        dat[1] = can_udp_msg.can_id >> 16 & 0x000000ff;
//        dat[2] = can_udp_msg.can_id >> 8  & 0x000000ff;
//        dat[3] = can_udp_msg.can_id       & 0x000000ff;
//        *dat       = can_udp_msg.can_id >> 24 & 0x000000ff;
//        *(dat + 1) = can_udp_msg.can_id >> 16 & 0x000000ff;
//        *(dat + 2) = can_udp_msg.can_id >> 16 & 0x000000ff;
//        *(dat + 3) = can_udp_msg.can_id >> 16 & 0x000000ff;
//
//        dat   += sizeof(can_udp_msg.can_id);
        *dat  = (uint8)(can_udp_msg.can_id >> 24 & 0x000000ff);
        dat++;
        *dat  = (uint8)(can_udp_msg.can_id >> 16 & 0x000000ff);
        dat++;
        *dat  = (uint8)(can_udp_msg.can_id >>  8 & 0x000000ff);
        dat++;
        *dat  = (uint8)(can_udp_msg.can_id       & 0x000000ff);
        dat++;

        *dat   = can_udp_msg.len;
        dat ++;

//        dat   += sizeof(can_udp_msg.len);
        memcpy(dat,can_udp_msg.data,can_udp_msg.len);
        dat += can_udp_msg.len;
        frameCount++;
    }
    len = dat - p ;
    p[0] = CANNELLONI_FRAME_VERSION;
    p[1] = DATA;
    p[2] = (uint8)sequence;
    p[3] = (uint8)(frameCount >> 8 & 0x00ff);
    p[4] = (uint8)(frameCount & 0x00ff);

    return  len;
}


