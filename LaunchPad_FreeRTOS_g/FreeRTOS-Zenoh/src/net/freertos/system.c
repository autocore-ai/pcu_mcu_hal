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


#include <time.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"
#include "zenoh-pico/net/private/system.h"
#include "zenoh-pico/private/system/freertos.h"
/*------------------ Task ------------------*/

/*------------------ Mutex ------------------*/
// As defined in "zenoh/private/system.h"
// typedef pthread_mutex_t _z_mutex_t;
int _z_mutex_init(_z_mutex_t *m)
{
    m->mut = xSemaphoreCreateRecursiveMutex();
    if(m->mut == NULL)
    {
        return -1;
    }

    return 0;
}

int _z_mutex_free(_z_mutex_t *m)
{
    vSemaphoreDelete(m->mut);
    m->mut = NULL;
    return 0;
}

int _z_mutex_lock(_z_mutex_t *m)
{
    return xSemaphoreTakeRecursive(m->mut, portMAX_DELAY);
}

int _z_mutex_trylock(_z_mutex_t *m)
{
    return xSemaphoreTakeRecursive(m->mut, 0);
}

int _z_mutex_unlock(_z_mutex_t *m)
{
    return xSemaphoreGiveRecursive(m->mut);
}

/*------------------ Condvar ------------------*/
// As defined in "zenoh/private/system.h"
// typedef pthread_cond_t _z_condvar_t;
int _z_condvar_init(_z_condvar_t *cv)
{
     cv->sem = xSemaphoreCreateBinary();
     if(cv->sem == NULL) {
       return -1;
     }
     return 0;
}

int _z_condvar_free(_z_condvar_t *cv)
{
    vSemaphoreDelete(cv->sem);
    cv->sem = NULL;
    return 0;
}

int _z_condvar_signal(_z_condvar_t *cv)
{
    return xSemaphoreGive(cv->sem);;
}

int _z_condvar_wait(_z_condvar_t *cv, _z_mutex_t *m)
{
    xSemaphoreGiveRecursive(m->mut);
    xSemaphoreTake(cv->sem, portMAX_DELAY);
    xSemaphoreTakeRecursive(m->mut, portMAX_DELAY);
}

/*------------------ Sleep ------------------*/

int _z_sleep_ms(unsigned int time)
{
    TickType_t delay_ticks = time / portTICK_RATE_MS;
    vTaskDelay(delay_ticks);
}

int _z_sleep_s(unsigned int time)
{
    TickType_t delay_ticks = 1000*time / portTICK_RATE_MS;
    vTaskDelay(delay_ticks);
}


/*------------------ Time ------------------*/
struct _sys_timeval _z_time_now()
{
    struct _sys_timeval now;
    now.pulSeconds= FreeRTOS_get_secs_msec(&(now.pulMsec));
    return now;
}

time_t _z_time_elapsed_ms(struct _sys_timeval *time)
{
    struct _sys_timeval now;
    now.pulSeconds= FreeRTOS_get_secs_msec(&(now.pulMsec));

    time_t elapsed = (1000 * (now.pulSeconds - time->pulSeconds) + (now.pulMsec - time->pulMsec) );
    return elapsed;
}

time_t _z_time_elapsed_s(struct _sys_timeval *time)
{
    struct _sys_timeval now;
    now.pulSeconds= FreeRTOS_get_secs_msec(&(now.pulMsec));

    time_t elapsed = now.pulSeconds - time->pulSeconds;
    return elapsed;
}






