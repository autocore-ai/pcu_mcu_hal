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
#include "FreeRTOS.h"
#include "os_task.h"
#include "zenoh-pico/net/private/internal.h"
#include "zenoh-pico/net/session.h"
#include "zenoh-pico/private/logging.h"
#include "zenoh-pico/private/system.h"
#include "os_portmacro.h"

void _znp_lease_task(void *arg)
{
    zn_session_t *z = (zn_session_t *)arg;
    z->lease_task_running = 1;

    z->received = 0;
    z->transmitted = 0;

    unsigned int next_lease = z->lease;
    unsigned int next_keep_alive = ZN_KEEP_ALIVE_INTERVAL;
    while (z->lease_task_running)
    {
        // Compute the target interval
        unsigned int interval;
        if (next_lease < next_keep_alive)
            interval = next_lease;
        else if (next_keep_alive < ZN_KEEP_ALIVE_INTERVAL)
            interval = next_keep_alive;
        else
            interval = ZN_KEEP_ALIVE_INTERVAL;

        // The keep alive and lease intervals are expressed in milliseconds
        _z_sleep_ms(interval);

        // Decrement the interval
        next_lease -= interval;
        next_keep_alive -= interval;

        if (next_lease == 0)
        {
            // Check if received data
            if (z->received == 0)
            {
                _Z_DEBUG_VA("Closing session because it has expired after %zums", z->lease);
                _zn_session_close(z, _ZN_CLOSE_EXPIRED);
                return 0;
            }

            // Reset the lease parameters
            z->received = 0;
            next_lease = z->lease;
        }

        if (next_keep_alive == 0)
        {
            // Check if need to send a keep alive
            if (z->transmitted == 0)
            {
                znp_send_keep_alive(z);
            }

            // Reset the keep alive parameters
            z->transmitted = 0;
            next_keep_alive = ZN_KEEP_ALIVE_INTERVAL;
        }
    }

    return 0;
}
xTaskHandle xZnpStartHandle;
#define ZNP_LEASE_STACK_SIZE    ( configMINIMAL_STACK_SIZE * 10 )
int znp_start_lease_task(zn_session_t *z)
{    
    z->lease_task = xZnpStartHandle;
    xTaskCreate( _znp_lease_task,
                 ( const char * ) "znp_start_lease",
                 ZNP_LEASE_STACK_SIZE,
                 z,
                 configMAX_PRIORITIES -12 | portPRIVILEGE_BIT,
                 &xZnpStartHandle );
}

int znp_stop_lease_task(zn_session_t *z)
{
    z->lease_task_running = 0;
    return 0;
}
