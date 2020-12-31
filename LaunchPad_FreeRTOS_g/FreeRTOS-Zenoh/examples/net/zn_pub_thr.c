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
#include <string.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "zenoh-pico/net.h"


#define ZENOH_PUB_TASK_PRIO          (configMAX_PRIORITIES - 10)
#define ZENOH_PUB_TASK_SIZE          (configMINIMAL_STACK_SIZE*10)  

xTaskHandle xPubThrHandle;
_z_i_gmap_t config;

#define LENGTH 1000
extern  uint8_t remoteIPAddress[4];
static void vPubThrTask(void)
{
    size_t len = LENGTH;
    char peerkey[32];
    printf("Running throughput test for payload of %zu bytes.\n", len);
    
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

    // Start the read session session lease loops
    znp_start_read_task(s);
    znp_start_lease_task(s);

    char *data =pvPortMalloc(LENGTH);
    memset(data, 1, (len-1));

    zn_reskey_t reskey = zn_rid(zn_declare_resource(s, zn_rname("/test/thr")));
    zn_publisher_t *pub = zn_declare_publisher(s, reskey);
    if (pub == 0)
    {
        printf("Unable to declare publisher.\n");
        exit(-1);
    }

    while (1)
    {
        zn_write_ext(s, reskey, (const uint8_t *)data, len, Z_ENCODING_DEFAULT, Z_DATA_KIND_DEFAULT, zn_congestion_control_t_BLOCK);
    }
    vPortFree(data);
}

void vStartPubThrTask()
{
        xTaskCreate( vPubThrTask,
                 ( const char * ) "PUB_Task",
                 ZENOH_PUB_TASK_SIZE,
                 NULL,
                 ZENOH_PUB_TASK_PRIO | portPRIVILEGE_BIT,
                 &xPubThrHandle );

}
