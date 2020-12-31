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
#include "Sci_driver.h"
#include "HL_reg_sci.h"

#define ZENOH_PUB_TASK_PRIO          (configMAX_PRIORITIES - 10)
#define ZENOH_PUB_TASK_SIZE          (configMINIMAL_STACK_SIZE*10)  

xTaskHandle xPubHandle;
_z_i_gmap_t config;
extern  uint8_t remoteIPAddress[4];
static void vPubTask(void)
{
    char *uri = "/demo/example/zenoh-pico-pub";
    char *value = "Pub from pico!";
    char pubprint[128];
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

    // Start the receive and the session lease loop for zenoh-pico
    znp_start_read_task(s);
    znp_start_lease_task(s);

    printf("Declaring Resource '%s'", uri);
    unsigned long rid = zn_declare_resource(s, zn_rname(uri));
    printf(" => RId %lu\n", rid);
    zn_reskey_t reskey = zn_rid(rid);

    printf("Declaring Publisher on %lu\n", rid);
    zn_publisher_t *pub = zn_declare_publisher(s, reskey);
    if (pub == 0)
    {
        printf("Unable to declare publisher.\n");
        exit(-1);
    }

    char buf[256];
    for (int idx = 0; 1; ++idx)
    {
        _z_sleep_ms(5);
        sprintf(buf, "[%4d] %s", idx, value);
        sprintf(pubprint,"Writing Data ('%lu': '%s')...\r\n", rid, buf);
        UartSendString(sciREG4,pubprint);
        zn_write(s, reskey, (const uint8_t *)buf, strlen(buf));
    }

    zn_undeclare_publisher(pub);
    zn_close(s);

    return 0;
}

void vStartPubTask()
{
        xTaskCreate( vPubTask,
                 ( const char * ) "PUB_Task",
                 ZENOH_PUB_TASK_SIZE,
                 NULL,
                 ZENOH_PUB_TASK_PRIO | portPRIVILEGE_BIT,
                 &xPubHandle );

}
