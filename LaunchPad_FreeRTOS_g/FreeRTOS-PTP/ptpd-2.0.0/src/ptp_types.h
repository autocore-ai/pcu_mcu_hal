/*********************2020.02.23-alex********************/
#ifndef DATATYPES_H_
#define DATATYPES_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "os_task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

/*************************Timestamp*************************/
typedef struct {
  int32_t  nsec_prev;
  int32_t  y;
  int32_t  s_exp;
} Filter;

typedef struct
{
    uint32_t lsb;
    uint16_t msb;
} Timesb;

typedef struct
{
    int32_t seconds;
    int32_t nanoseconds;
} TimeInternal;

typedef struct
{
    Timesb secondsField;
    uint32_t nanosecondsField;
} Timestamp;
/*************************Timestamp*************************/
/*****************PortIdentity/ClockIdentity****************/
#define CLOCK_IDENTITY_LENGTH     8
typedef char ClockIdentity[CLOCK_IDENTITY_LENGTH];
typedef struct
{
    uint8_t clockClass;//1
    uint8_t clockAccuracy;//1
    int16_t offsetScaledLogVariance;//1
} ClockQuality;

typedef struct
{
    ClockIdentity clockIdentity;
    int16_t portNumber;
} PortIdentity;
/*****************PortIdentity/ClockIdentity****************/
/**************************messageType**********************/
typedef struct
{
    uint8_t transportSpecific;
    uint8_t messageType;
    uint8_t  versionPTP;
    int16_t messageLength;
    uint8_t domainNumber;
    uint8_t flagField[2];
    int64_t correctionfield;
    PortIdentity sourcePortIdentity;
    int16_t sequenceId;
    uint8_t controlField;
    int8_t logMessageInterval;
} MsgHeader;

typedef struct
{
    Timestamp originTimestamp;
}MsgSync;

typedef struct
{
    Timestamp preciseOriginTimestamp;
}MsgFollowUp;

typedef struct
{
    Timestamp originTimestamp;
}MsgDelayReq;

typedef struct
{
    Timestamp receiveTimestamp;
    PortIdentity requestingPortIdentity;
}MsgDelayResp;

typedef struct
{
    Timestamp originTimestamp;
}MsgPDelayReq;

typedef struct
{
    Timestamp requestReceiptTimestamp;
    PortIdentity requestingPortIdentity;
}MsgPDelayResp;

typedef struct
{
    Timestamp responseOriginTimestamp;
    PortIdentity requestingPortIdentity;
}MsgPDelayRespFollowUp;

typedef struct
{
    PortIdentity targetPortIdentity;
    uint8_t startingBoundaryHops;
    uint8_t boundaryHops;
    uint8_t actionField;
    char* tlv;
}MsgManagement;

typedef struct
{
    Timestamp originTimestamp;
    int16_t currentUtcOffset;
    uint8_t grandmasterPriority1;
    ClockQuality grandmasterClockQuality;
    uint8_t grandmasterPriority2;
    ClockIdentity grandmasterIdentity;
    int16_t stepsRemoved;
    uint8_t timeSource;
}MsgAnnounce;

typedef struct
{
    PortIdentity targetPortIdentity;
    char* tlv;
}MsgSignaling;
/**************************messageType**********************/
/*****************************DS****************************/

typedef struct
{
	int16_t currentUtcOffset;
	bool  currentUtcOffsetValid;
	bool  leap59;
	bool  leap61;
	bool  timeTraceable;
	bool  frequencyTraceable;
	bool  ptpTimescale;
	uint8_t timeSource; /**< spec 7.6.2.6 */
} TimePropertiesDS;

typedef struct
{
	int16_t foreignMasterAnnounceMessages;
    PortIdentity foreignMasterPortIdentity;
    MsgAnnounce  announce;
    MsgHeader    header;
} ForeignMasterRecord;

typedef struct
{
    ForeignMasterRecord *records;//1
    int16_t  count;//1
    int16_t  capacity;//1
    int16_t  i;
    int16_t  best;
} ForeignMasterDS;

typedef struct
{
    PortIdentity parentPortIdentity;/* 7.6.4 Parent clock statistics - parentDS */
    bool    parentStats;//1
    int16_t observedParentOffsetScaledLogVariance;//1
    int32_t observedParentClockPhaseChangeRate;//1

    ClockIdentity grandmasterIdentity;
    ClockQuality grandmasterClockQuality;
    uint8_t grandmasterPriority1;
    uint8_t grandmasterPriority2;
} ParentDS;

typedef struct
{
	uint8_t versionNumber;//PTP版本号
	uint8_t domainNumber;//PTP设备时钟域
	uint16_t numberPorts;
	bool    twoStepFlag;//是否2步同步模式
	bool    slaveOnly;//是否olny salve
	uint8_t portState;//端口当前状态
	uint8_t delayMechanism;//端口模式E2E/P2P
	
	PortIdentity  portIdentity;//时钟唯一标识/端口mac/端口号
	ClockIdentity clockIdentity;//时钟唯一标识/端口mac
	ClockQuality  clockQuality;//时钟优先级
	uint8_t priority1;//时钟信号优先级
	uint8_t priority2;//1
	
	int16_t stepsRemoved;//

	int8_t  announceReceiptTimeout;//announce报文接收时间间隔
	int8_t  logAnnounceInterval;//announce报文发送时间间隔
	int8_t  logSyncInterval;//sync报文发送时间间隔
	int8_t  logMinDelayReqInterval;//delayreq报文发送时间间隔
} PortDS;

/*****************************DS****************************/
/***************************Servo***************************/
typedef struct
{
    bool  noResetClock;//1
    bool  noAdjust;//1
    int16_t ap, ai;//1
    int16_t sDelay;//1
    int16_t sOffset;
} Servo;
/***************************Servo***************************/
/****************************NET****************************/
typedef struct selectfd
{
    Socket_t    xSocket;
    SocketSet_t xSocketSet;
}selectfd;

typedef struct
{
    struct freertos_sockaddr local_addr;
    struct freertos_sockaddr remote_addr;
    struct selectfd          select_fd;
} udp_pcb;

typedef struct
{
    uint32_t   unicastAddr;
    uint32_t   multicastAddr;
    uint32_t   peerMulticastAddr;
    udp_pcb    eventPcb;
    udp_pcb    generalPcb;
} NetPath;
/****************************NET****************************/

/**************************PtpClock*************************/
#define IFACE_NAME_LENGTH         16
#define NET_ADDRESS_LENGTH        16
#define PTP_UUID_LENGTH           6
#define PACKET_SIZE               300 /* ptpdv1 value kept because of use of TLV... */
typedef struct
{
    PortDS   portDS; /**< port data set *///1自己端口状态
    ParentDS parentDS; /**< parent data set */
    ForeignMasterDS foreignMasterDS; /**< foreign master data set */
	TimePropertiesDS timePropertiesDS;
    MsgHeader msgTmpHeader; /**< buffer for incomming message header */
    union
    {
        MsgSync  sync;
        MsgFollowUp  follow;
        MsgDelayReq  req;
        MsgDelayResp resp;
        MsgPDelayReq  preq;
        MsgPDelayResp  presp;
        MsgPDelayRespFollowUp  prespfollow;
        MsgManagement  manage;
        MsgAnnounce  announce;
        MsgSignaling signaling;
    } msgTmp; /**< buffer for incomming message body */

    char msgObuf[PACKET_SIZE]; /**< buffer for outgoing message */
    char msgIbuf[PACKET_SIZE]; /** <buffer for incomming message */
    int32_t  msgIbufLength; /**< length of incomming message */

	int32_t  events;
	int16_t  number_foreign_records;
	int16_t  foreign_record_i;
    bool  messageActivity;
    bool  timeLock;

    NetPath netPath;//1
    char   ifaceName[IFACE_NAME_LENGTH];
	char   unicastAddress[NET_ADDRESS_LENGTH];
	char   portUuidField[PTP_UUID_LENGTH];//1
	
	bool   waitingForFirstOffset;
    bool   waitingForFollowUp; /**< true if sync message was recieved and 2step flag is set *///1

	int16_t recvSyncSequenceId;//followupid == syncid
	int16_t sentDelayReqSequenceId;
    int16_t sentSyncSequenceId;
    int16_t sentAnnounceSequenceId;

	TimeInternal inboundLatency;
	TimeInternal outboundLatency;//1
	TimeInternal timestamp_syncRecieve; /**< timestamp of Sync message t2*/
	TimeInternal correctionField_sync; /**< correction field of Sync and FollowUp messages */
	TimeInternal timestamp_delayReqSend; /**< timestamp of delay request message */
    TimeInternal timestamp_delayReqRecieve; /**< timestamp of delay request message */
	
    TimeInternal Tms; /**< Time Master -> Slave *///1
    TimeInternal Tsm; /**< Time Slave -> Master *///1
    TimeInternal offsetFromMaster;//t2-t1
    TimeInternal meanPathDelay;//[t2-t1) + (t4 - t3)]/2
    Filter  ofm_filt; /**< filter offset from master *///1
    Filter  owd_filt; /**< filter one way delay *///1

    Servo   servo;//1
}PtpClock;
/**************************PtpClock*************************/

#endif /* DATATYPES_H_*/
