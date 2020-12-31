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


#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "zenoh-pico/net/private/system.h"
#include "zenoh-pico/private/logging.h"
#include "FreeRTOS_IP.h"
#include "Sci_driver.h"
#include "HL_reg_sci.h"
/*------------------ Interfaces and sockets ------------------*/
struct freertos_sockaddr *_zn_make_socket_address(const char *addr, int port)
{
    struct freertos_sockaddr *saddr = (struct freertos_sockaddr *)pvPortMalloc(sizeof(struct freertos_sockaddr));
    memset(saddr, 0, sizeof(struct freertos_sockaddr));
    saddr->sin_family = FREERTOS_AF_INET;
    saddr->sin_port = FreeRTOS_htons(port);
    saddr->sin_addr = FreeRTOS_inet_addr(addr);

    return saddr;
}

_zn_socket_result_t _zn_create_udp_socket(const char *addr, int port, int timeout_usec)
{
    _zn_socket_result_t r;
    r.tag = _z_res_t_OK;

    _Z_DEBUG_VA("Binding UDP Socket to: %s:%d\n", addr, port);
    struct  freertos_sockaddr saddr;

    r.value.socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_DGRAM, FREERTOS_IPPROTO_UDP);

    if (r.value.socket < 0)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = r.value.socket;
        r.value.socket = 0;
        return r;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = FREERTOS_AF_INET;
    saddr.sin_port = FreeRTOS_htons(port);
    saddr.sin_addr = FreeRTOS_inet_addr(addr);

    if (FreeRTOS_bind(r.value.socket, (struct freertos_sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = _zn_err_t_INVALID_LOCATOR;
        r.value.socket = 0;
        return r;
    }

    struct _sys_timeval timeout;
    timeout.pulSeconds = 0;
    timeout.pulMsec = timeout_usec;
    if (FreeRTOS_setsockopt(r.value.socket, 0, FREERTOS_SO_RCVTIMEO, (void *)&timeout, sizeof(struct _sys_timeval)) == -1)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = errno;
        FreeRTOS_closesocket(r.value.socket);
        r.value.socket = 0;
        return r;
    }

    if (FreeRTOS_setsockopt(r.value.socket, 0, FREERTOS_SO_SNDTIMEO, (void *)&timeout, sizeof(struct _sys_timeval)) == -1)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = errno;
        FreeRTOS_closesocket(r.value.socket);
        r.value.socket = 0;
        return r;
    }

    return r;
}

_zn_socket_result_t _zn_open_tx_session(const char *locator)
{
    _zn_socket_result_t r;
    r.tag = _z_res_t_OK;
    char l[32];
    strcpy(l,locator);
    _Z_DEBUG_VA("Connecting to: %s:\n", locator);
    char *tx = strtok(l, "/");
    if (strcmp(tx, "tcp") != 0)
    {
        fprintf(stderr, "Locator provided is not for TCP\n");
        exit(1);
    }
    char addr_name[32];
    strcpy(addr_name,strtok(NULL, ":"));
    char *s_port = strtok(NULL, ":");   
    int port;
        sscanf(s_port, "%d", &port);
    struct freertos_sockaddr serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    r.value.socket = FreeRTOS_socket(FREERTOS_AF_INET, FREERTOS_SOCK_STREAM, FREERTOS_IPPROTO_TCP);
    if (r.value.socket < 0)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = r.value.socket;
        r.value.socket = 0;
        return r;
    }

   /* int flags = 1;
    if (FreeRTOS_setsockopt(r.value.socket, 0, SO_KEEPALIVE, (void *)&flags, sizeof(flags)) == -1)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = errno;
        close(r.value.socket);
        r.value.socket = 0;
        return r;
    }

    struct linger ling;
    ling.l_onoff = 1;
    ling.l_linger = ZN_SESSION_LEASE / 1000;
    if (FreeRTOS_setsockopt(r.value.socket, SOL_SOCKET, SO_LINGER, (void *)&ling, sizeof(struct linger)) == -1)
    {
        r.tag = _z_res_t_ERR;
        r.value.error = errno;
        close(r.value.socket);
        r.value.socket = 0;
        return r;
    }*/ 
    
    serv_addr.sin_family = FREERTOS_AF_INET;
    serv_addr.sin_port = FreeRTOS_htons(port);
    serv_addr.sin_addr = FreeRTOS_inet_addr(addr_name);
    BaseType_t dwRet = FreeRTOS_connect(r.value.socket, (struct freertos_sockaddr *)&serv_addr, sizeof(serv_addr));
    while (dwRet < 0)
    {
        UartSendString(sciREG4,"connect failed \r\n");
        printf("connect failed\r\n");
        dwRet = FreeRTOS_connect(r.value.socket, (struct freertos_sockaddr *)&serv_addr, sizeof(serv_addr));
    }
    UartSendString(sciREG4,"connect ok \r\n");
    return r;
}

void _zn_close_tx_session(_zn_socket_t sock)
{
    FreeRTOS_shutdown(sock, 2);
}

/*------------------ Datagram ------------------*/
int _zn_send_dgram_to(_zn_socket_t sock, const _z_wbuf_t *wbf, const struct freertos_sockaddr *dest, socklen_t salen)
{
    _Z_DEBUG("Sending data on socket....\n");
    int wb = 0;
    for (size_t i = 0; i < _z_wbuf_len_iosli(wbf); i++)
    {
        z_bytes_t a = _z_iosli_to_bytes(_z_wbuf_get_iosli(wbf, i));
        int res = FreeRTOS_sendto(sock, a.val, a.len, 0, dest, salen);
        _Z_DEBUG_VA("Socket returned: %d\n", wb);
        if (res <= 0)
        {
            _Z_DEBUG_VA("Error while sending data over socket [%d]\n", wb);
            return -1;
        }
        wb += res;
    }
    return wb;
}

int _zn_recv_dgram_from(_zn_socket_t sock, _z_rbuf_t *rbf, struct freertos_sockaddr *from, socklen_t *salen)
{
    int rb = FreeRTOS_recvfrom(sock, _z_rbuf_get_wptr(rbf), _z_rbuf_space_left(rbf), 0, from, salen);
    if (rb > 0)
        _z_rbuf_set_wpos(rbf, _z_rbuf_get_wpos(rbf) + rb);

    return rb;
}

/*------------------ Receive ------------------*/
int _zn_recv_bytes(_zn_socket_t sock, uint8_t *ptr, size_t len)
{
    int n = len;
    int rb;

    do
    {
        rb = FreeRTOS_recv(sock, ptr, n, 0);
        if ((rb < 0)||(rb == 0))
            return -1;
        n -= rb;
        ptr = ptr + (len - n);
    } while (n > 0);

    return 0;
}

int _zn_recv_rbuf(_zn_socket_t sock, _z_rbuf_t *rbf)
{
    int rb = FreeRTOS_recv(sock, _z_rbuf_get_wptr(rbf), _z_rbuf_space_left(rbf), 0);
    if (rb > 0)
        _z_rbuf_set_wpos(rbf, _z_rbuf_get_wpos(rbf) + rb);
    return rb;
}

/*------------------ Send ------------------*/
int _zn_send_wbuf(_zn_socket_t sock, const _z_wbuf_t *wbf)
{
    for (size_t i = 0; i < _z_wbuf_len_iosli(wbf); i++)
    {
        z_bytes_t bs = _z_iosli_to_bytes(_z_wbuf_get_iosli(wbf, i));
        int n = bs.len;
        int wb;
        do
        {
            _Z_DEBUG("Sending wbuf on socket...");

            wb = FreeRTOS_send(sock, bs.val, n, 0);

            _Z_DEBUG_VA("send %d bytes\n", wb);
            if (wb <= 0)
            {
                _Z_DEBUG_VA("Error while sending data over socket [%d]\n", wb);
                return -1;
            }
            n -= wb;
            bs.val += bs.len - n;
        } while (n > 0);
    }

    return 0;
}

