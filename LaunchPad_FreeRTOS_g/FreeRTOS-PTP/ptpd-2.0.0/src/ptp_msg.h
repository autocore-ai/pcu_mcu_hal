/*********************2020.02.23-alex********************/
#ifndef PTP_MSG_H_
#define PTP_MSG_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ptp_types.h"

/*******************************************************/
#define MACHINE_ENDIAN   1  // 0:little 1:big
/*******************************************************/

#define HEADER_LENGTH                 34
#define ANNOUNCE_LENGTH               64
#define SYNC_LENGTH                   44
#define FOLLOW_UP_LENGTH              44
#define PDELAY_REQ_LENGTH             54
#define DELAY_REQ_LENGTH              44
#define DELAY_RESP_LENGTH             54
#define PDELAY_RESP_LENGTH            54
#define PDELAY_RESP_FOLLOW_UP_LENGTH  54
#define MANAGEMENT_LENGTH             48

#define FLAG_FIELD_LENGTH             2

 enum
 {
     FLAG0_ALTERNATE_MASTER = 0x01,
     FLAG0_TWO_STEP = 0x02,
     FLAG0_UNICAST = 0x04,
     FLAG0_PTP_PROFILE_SPECIFIC_1 = 0x20,
     FLAG0_PTP_PROFILE_SPECIFIC_2 = 0x40,
     FLAG0_SECURITY = 0x80,
 };
enum
{
    CTRL_SYNC = 0x00,
    CTRL_DELAY_REQ,
    CTRL_FOLLOW_UP,
    CTRL_DELAY_RESP,
    CTRL_MANAGEMENT,
    CTRL_OTHER,
};
enum
{
    SYNC = 0x0,
    DELAY_REQ,
    PDELAY_REQ,
    PDELAY_RESP,
    FOLLOW_UP = 0x8,
    DELAY_RESP,
    PDELAY_RESP_FOLLOW_UP,
    ANNOUNCE,
    SIGNALING,
    MANAGEMENT,
};

void msgPackHeader(const PtpClock *ptpClock, char *buf);
void msgUnpackHeader(const char *buf, MsgHeader *header);
void msgPackAnnounce(const PtpClock *ptpClock, char *buf);
void msgUnpackAnnounce(const char *buf, MsgAnnounce *announce);
void msgPackSync(const PtpClock *ptpClock, char *buf, const Timestamp *originTimestamp);
void msgUnpackSync(const char *buf, MsgSync *sync);
void msgUnpackFollowUp(const char *buf, MsgFollowUp *follow);
void msgPackDelayReq(const PtpClock *ptpClock, char *buf, const Timestamp *originTimestamp);
void msgUnpackDelayResp(const char *buf, MsgDelayResp *resp);
void msgPackFollowUp(const PtpClock *ptpClock, char*buf, const Timestamp *preciseOriginTimestamp);
void msgPackDelayResp(const PtpClock *ptpClock, char *buf, const MsgHeader *header, const Timestamp *receiveTimestamp);


#endif

