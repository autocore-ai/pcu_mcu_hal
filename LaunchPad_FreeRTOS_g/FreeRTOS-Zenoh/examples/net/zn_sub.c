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

xTaskHandle xSubHandle;
extern  uint8_t remoteIPAddress[4];
void data_handler(const zn_sample_t *sample)
{
    char subprint[128];
    sprintf(subprint,"[Subscription listener] Received (%.*s, %.*s)\r\n",
           (int)sample->key.len, sample->key.val,
           (int)sample->value.len, sample->value.val);
    UartSendString(sciREG4,subprint);
}
_z_i_gmap_t config;
static void vSubTask(void)
{
    char peerkey[32];
    char *uri = "/demo/example/**\0";
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

    printf("Declaring Subscriber on '%s'...\n", uri);

    zn_reskey_t reskey = zn_rname(uri);
    zn_subinfo_t sub_info = zn_subinfo_default();
    zn_subscriber_t sub;
    zn_subscriber_t * subaddr = &sub;
    subaddr->id  =  zn_declare_subscriber(s,  reskey, sub_info, data_handler, NULL);
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

void vStartSubTask()
{
        xTaskCreate( vSubTask,
                 ( const char * ) "SUB_Task",
                 ZENOH_SUB_TASK_SIZE,
                 NULL,
                 ZENOH_SUB_TASK_PRIO | portPRIVILEGE_BIT,
                 &xSubHandle );

}
