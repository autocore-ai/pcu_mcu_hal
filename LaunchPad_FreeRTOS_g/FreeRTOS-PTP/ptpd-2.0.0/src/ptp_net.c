/*********************2020.02.23-alex********************/
#include "ptp_net.h"
#include "ma_date_and_time.h"

bool ptp_udp_init(udp_pcb* pcb)
{
    bool rv = false;
    pcb->select_fd.xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                                                   FREERTOS_SOCK_DGRAM,
                                                   FREERTOS_IPPROTO_UDP );
    if (FREERTOS_INVALID_SOCKET != pcb->select_fd.xSocket)
    {
        FreeRTOS_bind( pcb->select_fd.xSocket, &pcb->local_addr, sizeof( struct freertos_sockaddr ));
        pcb->select_fd.xSocketSet = FreeRTOS_CreateSocketSet();
        FreeRTOS_FD_SET(pcb->select_fd.xSocket, pcb->select_fd.xSocketSet, eSELECT_READ);

        rv = true;
    }
    return rv;
}

bool ptp_udp_close(udp_pcb* pcb)
{
    (void)FreeRTOS_closesocket(pcb->select_fd.xSocket);
    return true;
}

int32_t ptp_udp_send(udp_pcb* pcb, const char* buf, int32_t len, uint8_t* errcode)
{
    size_t rv = 0;
    int32_t bytes = FreeRTOS_sendto(pcb->select_fd.xSocket,
                                    (void*)buf,
                                    len,
                                    0,
                                    &pcb->remote_addr,
                                    sizeof(pcb->remote_addr));
    if (bytes > 0)
    {
        rv = (size_t)bytes;
        *errcode = 0;
    }
    else
    {
        FreeRTOS_printf(("bytes_sent = %d...\r\n",bytes));
        *errcode = 1;
    }
    return rv;
}

int32_t ptp_udp_recv(udp_pcb* pcb, char* buf, int32_t len, int timeout, uint8_t* errcode)
{
    size_t rv = 0;
    uint32_t ulAddressLength = sizeof(struct freertos_sockaddr);
    BaseType_t xResult = FreeRTOS_select(pcb->select_fd.xSocketSet, pdMS_TO_TICKS(timeout) );
    if (xResult > 0)
    {
        int32_t bytes = FreeRTOS_recvfrom( pcb->select_fd.xSocket,
                                        buf,
                                        len,
                                        0,
                                        &pcb->remote_addr,
                                        &ulAddressLength);
        if (bytes > 0)
        {
            rv = (size_t)bytes;
            *errcode = 0;
        }
        else
        {
            *errcode = 1;
        }
    }
    else
    {
        *errcode = (0 == xResult) ? 0 : 1;
    }
    return rv;
}


bool recv_udp_general_msg(NetPath* netPath, char* buf, int32_t* len, TimeInternal *time)
{
    uint8_t errcode = 0;
    uint32_t uxSecs,uxmSecs;
    *len = ptp_udp_recv(&netPath->generalPcb, buf, PACKET_SIZE, 1, &errcode);
    uxSecs = FreeRTOS_get_secs_msec(&uxmSecs);
    time->seconds = uxSecs;
    time->nanoseconds = uxmSecs * 1000000;

    if(*len > 0)
        return true;
    else
        return false;
}
bool recv_udp_event_msg(NetPath* netPath, char* buf, int32_t* len, TimeInternal *time)
{
    uint8_t errcode = 0;
    uint32_t uxSecs,uxmSecs;
    *len = ptp_udp_recv(&netPath->eventPcb, buf, PACKET_SIZE, 1, &errcode);
    uxSecs = FreeRTOS_get_secs_msec(&uxmSecs);
    time->seconds = uxSecs;
    time->nanoseconds = uxmSecs * 1000000;

    if(*len > 0)
        return true;
    else
        return false;
}

bool send_udp_general_msg(NetPath* netPath, const char* buf, int32_t len)
{
    uint8_t errcode = 0;
    netPath->generalPcb.remote_addr.sin_addr = netPath->multicastAddr;
    netPath->generalPcb.remote_addr.sin_port = FreeRTOS_htons(PTP_GENERAL_PORT);
    int32_t bytes = ptp_udp_send(&netPath->generalPcb, buf, len, &errcode);
    if(bytes > 0)
        return true;
    else
        return false;
}
bool send_udp_event_msg(NetPath* netPath, const char* buf, int32_t len)
{
    uint8_t errcode = 0;
    netPath->eventPcb.remote_addr.sin_addr = netPath->multicastAddr;
    netPath->eventPcb.remote_addr.sin_port = FreeRTOS_htons(PTP_EVENT_PORT);
    int32_t bytes = ptp_udp_send(&netPath->eventPcb, buf, len, &errcode);
    if(bytes > 0)
        return true;
    else
        return false;
}

int32_t send_udp_peer_general_msg(NetPath *netPath, const char *buf, int32_t  len)
{
    uint8_t errcode = 0;
    netPath->generalPcb.remote_addr.sin_addr = netPath->peerMulticastAddr;
    netPath->generalPcb.remote_addr.sin_port = FreeRTOS_htons(PTP_GENERAL_PORT);
    int32_t bytes = ptp_udp_send(&netPath->generalPcb, buf, len, &errcode);
    if(bytes > 0)
        return true;
    else
        return false;
}

int32_t send_udp_peer_event_msg(NetPath *netPath, const char *buf, int32_t  len)
{
    uint8_t errcode = 0;
    netPath->eventPcb.remote_addr.sin_addr = netPath->peerMulticastAddr;
    netPath->eventPcb.remote_addr.sin_port = FreeRTOS_htons(PTP_EVENT_PORT);
    int32_t bytes = ptp_udp_send(&netPath->eventPcb, buf, len, &errcode);
    if(bytes > 0)
        return true;
    else
        return false;
}

bool netInit(NetPath *netPath, PtpClock *ptpClock)
{
    netPath->unicastAddr = 0;
    netPath->multicastAddr = FreeRTOS_inet_addr(DEFAULT_PTP_DOMAIN_ADDRESS);
    netPath->peerMulticastAddr = FreeRTOS_inet_addr(PEER_PTP_DOMAIN_ADDRESS);
    memcpy(ptpClock->portUuidField, (void *)emacAddress, PTP_UUID_LENGTH);

    netPath->eventPcb.local_addr.sin_addr = 0;
    netPath->eventPcb.local_addr.sin_port = FreeRTOS_htons(PTP_EVENT_PORT);
    ptp_udp_init(&netPath->eventPcb);

    netPath->generalPcb.local_addr.sin_addr = 0;
    netPath->generalPcb.local_addr.sin_port = FreeRTOS_htons(PTP_GENERAL_PORT);
    ptp_udp_init(&netPath->generalPcb);
    return true;
}
