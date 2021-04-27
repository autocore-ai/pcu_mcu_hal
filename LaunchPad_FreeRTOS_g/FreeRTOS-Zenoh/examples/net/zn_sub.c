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
#include "os_timer.h"

#define ZENOH_SUB_TASK_PRIO          (configMAX_PRIORITIES - 10)
#define ZENOH_SUB_TASK_SIZE          (configMINIMAL_STACK_SIZE*10*3)
#define PUBLEN 3

xTaskHandle xSubHandle;
TimerHandle_t   AutoPubTimer_Handle = NULL;
extern  uint8_t remoteIPAddress[4];
_z_i_gmap_t config;
zn_session_t *s;
zn_reskey_t reskeypub;
zn_publisher_t *pub;
char data_ok[3] ={'o','k','!'};
char data_err[3] ={'e','r','r'};
void data_handler(const zn_sample_t *sample)
{

   char subprint[128];
        sprintf(subprint,"[Subscription listener] Received (%.*s)\r\n",
               (int)sample->key.len, sample->key.val);
        UartSendString(sciREG4,subprint);

    if(strcmp(sample->key.val,"/demo/sdv/start") == 0)
    {
        if(AutoPubTimer_Handle != NULL)
        {
            UartSendString(sciREG4,"start");
            xTimerStart(AutoPubTimer_Handle,0);
        }
    }
    else if(strcmp(sample->key.val,"/demo/sdv/stop") == 0)
    {
         if(AutoPubTimer_Handle != NULL)
         {
             UartSendString(sciREG4,"stop");
             xTimerStop(AutoPubTimer_Handle,0);
         }
    }
    else if(strcmp(sample->key.val,"/demo/sdv/update") == 0)
    {
        if(AutoPubTimer_Handle != NULL)
           xTimerReset(AutoPubTimer_Handle,0);
        zn_write_ext(s, reskeypub, (const uint8_t *)data_ok, PUBLEN, Z_ENCODING_DEFAULT, Z_DATA_KIND_DEFAULT, zn_congestion_control_t_BLOCK);
    }

}

void AutoPubCallback(TimerHandle_t xTimer)
{
    UartSendString(sciREG4,"send  message\r\n");
    zn_write_ext(s, reskeypub, (const uint8_t *)data_err, PUBLEN, Z_ENCODING_DEFAULT, Z_DATA_KIND_DEFAULT, zn_congestion_control_t_BLOCK);
}
static void vSubTask(void)
{
    char peerkey[32];

    char *uri = "/demo/sdv/**\0";
    freertos_config_default(&config);
    sprintf(peerkey,"tcp/%d.%d.%d.%d:7447\0",remoteIPAddress[0],remoteIPAddress[1],remoteIPAddress[2],remoteIPAddress[3]);
    _z_i_gmap_set(&config, ZN_CONFIG_PEER_KEY, peerkey);

    printf("Openning session...\n");
    s = zn_open(&config);
    if (s == 0)
    {
        printf("Unable to open session!\n");
        exit(-1);
    }
    znp_start_read_task(s);
    znp_start_lease_task(s);

    printf("Declaring Subscriber on '%s'...\n", uri);

    AutoPubTimer_Handle=xTimerCreate((const char*        )"AutoReloadTimer",
                                            (TickType_t         )100,
                                            (UBaseType_t        )pdTRUE,
                                            (void*              )1,
                                            (TimerCallbackFunction_t)AutoPubCallback
                                           );

    zn_reskey_t reskey = zn_rname(uri);
    zn_subinfo_t sub_info = zn_subinfo_default();
    zn_subscriber_t sub;
    zn_subscriber_t * subaddr = &sub;
    subaddr->id  =  zn_declare_subscriber(s,  reskey, sub_info, data_handler, NULL);
    subaddr->zn = s;

    UartSendString(sciREG4,"subscriber ok\r\n");

    reskeypub = zn_rid(zn_declare_resource(s, zn_rname("/demo/sdv1/status")));
    pub = zn_declare_publisher(s, reskeypub);
    if (pub == 0)
    {
       printf("Unable to declare publisher.\n");
       exit(-1);
    }
    UartSendString(sciREG4,"publisher ok\r\n");

    while(1)
    {
        _z_sleep_ms(5);
    }
    zn_undeclare_subscriber(subaddr);
    zn_undeclare_publisher(pub);
    zn_close(s);

    return ;

}

void vStartSubTask()
{
        xTaskCreate( vSubTask,
                 ( const char * ) "SUB_Task",
                 ZENOH_SUB_TASK_SIZE,
                 NULL,
                 ZENOH_SUB_TASK_PRIO | portPRIVILEGE_BIT,
                 &xSubHandle );

}
