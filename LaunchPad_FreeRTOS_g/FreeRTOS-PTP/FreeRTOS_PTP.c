#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "ptp_protocol.h"
#include "rti_runtimestats.h"

/***************************Global*******************************/
PtpClock    ptpClock;

/***************************Global*******************************/
#define PTP_TASK_PRIO          (configMAX_PRIORITIES - 10)
#define PTP_TASK_SIZE          (configMINIMAL_STACK_SIZE*10)

xTaskHandle xPTPHandle;

#if( ipconfigUSE_PTP == 1 )
    const MACAddress_t xPTP_MacAdress = { { 0x01, 0x00, 0x5e, 0x00, 0x01, 0x81 } };
    const MACAddress_t xPTP_Peer_MacAdress = { { 0x01, 0x00, 0x5e, 0x00, 0x00, 0x6B } };
#endif

static void vPTPTask( void *pvParameters )
{
    ptp_toState(&ptpClock,PTP_INITIALIZING);
    while(1)
    {
        ptp_doState(&ptpClock);
    }
}

void vStartPTPTask()
{
//    vConfigureTimerForSysTime();
    xTaskCreate( vPTPTask,
                 ( const char * ) "PTP_Task",
                 PTP_TASK_SIZE,
                 NULL,
                 PTP_TASK_PRIO | portPRIVILEGE_BIT,
                 &xPTPHandle );
}

