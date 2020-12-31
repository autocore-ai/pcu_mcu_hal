/*
 * Copyright (c) 2017, 2020 ADLINK Technology Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Apache License, Version 2.0
 * which is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *
 * Contributors:
 *   ADLINK zenoh team, <zenoh@adlink-labs.tech>
 */
#include <stdio.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "zenoh-pico/net.h"
#include "Sci_driver.h"
#include "HL_reg_sci.h"

#define ZENOH_SUB_TASK_PRIO          (configMAX_PRIORITIES - 10)
#define ZENOH_SUB_TASK_SIZE          (configMINIMAL_STACK_SIZE*10)  

xTaskHandle xSubthrHandle;

#define N 500

volatile unsigned long long int count = 0;
volatile _z_time_t start;
volatile _z_time_t stop;
extern  uint8_t remoteIPAddress[4];
void print_stats(volatile _z_time_t *start, volatile _z_time_t *stop)
{
    char subsprint[128];
    double t0 = start->pulSeconds + ((double)start->pulMsec / 1000.0);
    double t1 = stop->pulSeconds + ((double)stop->pulMsec / 1000.0);
    double thpt = N / (t1 - t0);

    sprintf(subsprint,"%f msgs/sec\r\n",thpt);
    UartSendString(sciREG4,subsprint);
}

void subdata_handler(const zn_sample_t *sample, const void *arg)
{
    (void)(sample); // Unused argument
    (void)(arg);    // Unused argument
   /* char subprint[128];
    sprintf(subprint,"receive data %d\r\n",(int)sample->value.len);
    UartSendString(sciREG4,subprint);*/
    printf("receive data %d\r\n",(int)sample->value.len);
    struct _sys_timeval tv;
    if (count == 0)
    {
        FreeRTOS_gettime(&tv.pulSeconds, &tv.pulMsec);
        start = tv;
        count++;
    }
    else if (count < N)
    {
        count++;
    }
    else
    {
        FreeRTOS_gettime(&tv.pulSeconds, &tv.pulMsec);
        stop = tv;
        char subprint[128];
        sprintf(subprint,"receive data %d\r\n",(int)sample->value.len);
        UartSendString(sciREG4,subprint);
        print_stats(&start, &stop);
        count = 0;
    }
}

_z_i_gmap_t config;
static void vSubthrTask(void)
{   
    char peerkey[32];
    freertos_config_default(&config);

    sprintf(peerkey,"tcp/%d.%d.%d.%d:7447\0",remoteIPAddress[0],remoteIPAddress[1],remoteIPAddress[2],remoteIPAddress[3]);
    _z_i_gmap_set(&config, ZN_CONFIG_PEER_KEY, peerkey);

    printf("Openning session...\n");
    zn_session_t *s = zn_open(&config);
    if (s == 0)
    {
        printf("Unable to open session!\n");
        exit(-1);
    }

   
    znp_start_read_task(s);
    znp_start_lease_task(s);

   // unsigned long rid = zn_declare_resource(s, zn_rname("/test/thr"));
    zn_reskey_t reskey =  zn_rname("/test/thr\0");
    zn_subinfo_t sub_info = zn_subinfo_default();
    zn_subscriber_t sub;
    zn_subscriber_t * subaddr = &sub;
    subaddr->id  =  zn_declare_subscriber(s,  reskey, sub_info, subdata_handler, NULL);
    subaddr->zn = s;

    uint16_t aa;
    for(aa = 0;aa <3600;)
    {
        _z_sleep_ms(5);
        aa +=1;
    }
    zn_undeclare_subscriber(subaddr);
    zn_close(s);

    return ;

}

void vStartSubThrTask()
{
        xTaskCreate( vSubthrTask,
                 ( const char * ) "SUB_Task",
                 ZENOH_SUB_TASK_SIZE,
                 NULL,
                 ZENOH_SUB_TASK_PRIO | portPRIVILEGE_BIT,
                 &xSubthrHandle );

}
