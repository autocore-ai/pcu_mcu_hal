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

#ifndef _ZENOH_PICO_FREERTOS_TYPES_H
#define _ZENOH_PICO_FREERTOS_TYPES_H

#include <time.h>
#include "os_task.h"

typedef TaskHandle_t _z_task_t;

struct _sys_mut {
  void *mut;
};
typedef struct _sys_mut _z_mutex_t;

struct _sys_sem {
  void *sem;
};
typedef struct _sys_sem _z_condvar_t;

struct _sys_timeval{
    time_t pulSeconds;
    time_t pulMsec;
};
typedef struct _sys_timeval _z_time_t;
#endif /* _ZENOH_PICO_UNIX_TYPES_H_ */
