#ifndef __FREERTOS_PTP_H__
#define __FREERTOS_PTP_H__


#if( ipconfigUSE_PTP == 1 )
    extern const MACAddress_t xPTP_MacAdress;
    extern const MACAddress_t xPTP_Peer_MacAdress;
#if( ipconfigBYTE_ORDER == pdFREERTOS_BIG_ENDIAN )
    #define ipPTP_IP_ADDR           0xE0000181
#else
    #define ipPTP_IP_ADDR           0x810100E0
#endif

#if( ipconfigBYTE_ORDER == pdFREERTOS_BIG_ENDIAN )
    #define ipPTP_PEER_IP_ADDR      0xE000006B
#else
    #define ipPTP_PEER_IP_ADDR      0x6B0000E0
#endif
#endif



void vStartPTPTask();


#endif //__FREERTOS_PTP_H__
