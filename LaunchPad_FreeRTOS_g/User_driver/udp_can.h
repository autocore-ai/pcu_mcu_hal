/*
 * Udp_can.h
 *
 *  Created on: 2019Äê1ÔÂ9ÈÕ
 *      Author: zhenh
 */

#ifndef USER_DRIVER_UDP_CAN_H_
#define USER_DRIVER_UDP_CAN_H_

#include "HL_hal_stdtypes.h"

#define DATA_QUE(x,y)         x##_##y##_queue
#define TASK_NOTIFY(x,y)      x##_##y##_handle
#define FUNC_R(x,y)           x##_##y##_Task
#define FUNC_S(x)             #x

#define REMOTE_IP_ADDR          "192.168.1.239"
#define remoteIP_ADDR0          192
#define remoteIP_ADDR1          168
#define remoteIP_ADDR2          1
#define remoteIP_ADDR3          239
#define CANNELLONI_PORT1         20000
#define CANNELLONI_REMOTE_PORT1  20000
#define CANNELLONI_PORT2         CANNELLONI_PORT1 + 1
#define CANNELLONI_REMOTE_PORT2  CANNELLONI_REMOTE_PORT1 + 1
#define CANNELLONI_PORT3         CANNELLONI_PORT1 + 2
#define CANNELLONI_REMOTE_PORT3  CANNELLONI_REMOTE_PORT1 + 2
#define CANNELLONI_PORT4         CANNELLONI_PORT1 + 3
#define CANNELLONI_REMOTE_PORT4  CANNELLONI_REMOTE_PORT1 + 3

/* Base size of a canfd_frame (canid + dlc) */
#define CANNELLONI_FRAME_BASE_SIZE 5
/* Size in byte of UDPDataPacket */
#define CANNELLONI_DATA_PACKET_BASE_SIZE 5

#define CANNELLONI_FRAME_VERSION 2
#define CANFD_FRAME              0x80
#define CAN_FRAME                0x08
enum op_codes {DATA, ACK, NACK};

struct  cannelloni_data_packet {

  uint8   version;          /* Version */
  uint8   op_code;          /* OP Code */
  uint8   seq_no;           /* Sequence Number */
  uint16  count;            /* Number of CAN Messages in this packet */
};


/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU /* omit EFF, RTR, ERR flags */

#define CANFD_MAX_DLEN 8

typedef  struct _CANFD_FRAME  {
    uint32   can_id;              /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8    len;                 /* frame payload length in byte */
    uint8    flags;               /* additional flags for CAN FD */
    uint8    data[CANFD_MAX_DLEN];
}canlloni_frame;


uint8    FreeRTOS_udp_can_Init(void);


#endif /* USER_DRIVER_UDP_CAN_H_ */
