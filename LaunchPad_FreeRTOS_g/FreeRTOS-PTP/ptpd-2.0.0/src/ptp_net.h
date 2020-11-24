/*********************2020.02.23-alex********************/
#ifndef PTP_NET_H_
#define PTP_NET_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "ptp_types.h"
#include "ptp_protocol.h"

extern uint8_t emacAddress[6];
extern uint8_t ucIPAddress[4];

#define PTP_EVENT_PORT    319
#define PTP_GENERAL_PORT  320

#define DEFAULT_PTP_DOMAIN_ADDRESS  "224.0.1.129"
#define PEER_PTP_DOMAIN_ADDRESS     "224.0.0.107"

bool netInit(NetPath *netPath, PtpClock *ptpClock);
bool ptp_udp_init(udp_pcb* pcb);
bool ptp_udp_close(udp_pcb* pcb);
int32_t ptp_udp_send(udp_pcb* pcb, const char* buf, int32_t len, uint8_t* errcode);
int32_t ptp_udp_recv(udp_pcb* pcb, char* buf, int32_t len, int timeout, uint8_t* errcode);

bool recv_udp_general_msg(NetPath* netPath, char* buf, int32_t* len, TimeInternal *time);
bool recv_udp_event_msg(NetPath* netPath, char* buf, int32_t* len, TimeInternal *time);

bool send_udp_general_msg(NetPath* netPath, const char* buf, int32_t len);
bool send_udp_event_msg(NetPath* netPath, const char* buf, int32_t len);

int32_t send_udp_peer_general_msg(NetPath *netPath, const char *buf, int32_t  len);
int32_t send_udp_peer_event_msg(NetPath *netPath, const char *buf, int32_t  len);

#endif
