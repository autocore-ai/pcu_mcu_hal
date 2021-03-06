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

#ifndef _ZENOH_NET_PICO_SYSTEM_H
#define _ZENOH_NET_PICO_SYSTEM_H
#include "zenoh-pico/net/private/system/freertos.h"
#include "FreeRTOS_Sockets.h"
/*------------------ Network ------------------*/
// @TODO: remove the platform-s
//pecific include and data types
#include "zenoh-pico/net/private/result.h"

_ZN_RESULT_DECLARE(_zn_socket_t, socket)


_zn_socket_result_t _zn_open_tx_session(const char *locator);
void _zn_close_tx_session(_zn_socket_t sock);

struct freertos_sockaddr *_zn_make_socket_address(const char *addr, int port);
_zn_socket_result_t _zn_create_udp_socket(const char *addr, int port, int recv_timeout);

int _zn_send_dgram_to(_zn_socket_t sock, const _z_wbuf_t *wbf, const struct freertos_sockaddr *dest, socklen_t salen);
int _zn_recv_dgram_from(_zn_socket_t sock, _z_rbuf_t *rbf, struct freertos_sockaddr *from, socklen_t *salen);

int _zn_send_wbuf(_zn_socket_t sock, const _z_wbuf_t *wbf);
int _zn_recv_rbuf(_zn_socket_t sock, _z_rbuf_t *rbf);
int _zn_recv_bytes(_zn_socket_t sock, uint8_t *buf, size_t len);

#endif /* _ZENOH_NET_PICO_SYSTEM_H */
