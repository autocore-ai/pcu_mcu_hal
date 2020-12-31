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

#ifndef _ZENOH_PICO_SYSTEM_H
#define _ZENOH_PICO_SYSTEM_H


#include "zenoh-pico/private/system/freertos.h"




/*------------------ Mutex ------------------*/
int _z_mutex_init(_z_mutex_t *m);
int _z_mutex_free(_z_mutex_t *m);

int _z_mutex_lock(_z_mutex_t *m);
int _z_mutex_trylock(_z_mutex_t *m);
int _z_mutex_unlock(_z_mutex_t *m);

/*------------------ CondVar ------------------*/
int _z_condvar_init(_z_condvar_t *cv);
int _z_condvar_free(_z_condvar_t *cv);

int _z_condvar_signal(_z_condvar_t *cv);
int _z_condvar_wait(_z_condvar_t *cv, _z_mutex_t *m);

/*------------------ Sleep ------------------*/
int _z_sleep_ms(unsigned int time);
int _z_sleep_s(unsigned int time);

/*------------------ Time ------------------*/
_z_time_t _z_time_now(void);
time_t _z_time_elapsed_ms(_z_time_t *time);
time_t _z_time_elapsed_s(_z_time_t *time);

#endif /* _ZENOH_PICO_SYSTEM_H */
