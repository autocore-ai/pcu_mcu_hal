#ifndef PTP_PROTOCOL_H_
#define PTP_PROTOCOL_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ptp_types.h"


#define getFlag(flagField, mask)   (bool)(((flagField)  & (mask)) == (mask))
#define setFlag(flagField, mask)   (flagField) |= (mask)
#define clearFlag(flagField, mask) (flagField) &= ~(mask)
#define pow2ms(x) (((x)>0) ? (1000 << (x)) : (1000 >>(-(x))))
#define getRand(x) (rand() % (x))

/* Implementation specific constants */
#define DEFAULT_INBOUND_LATENCY         0       /* in nsec */
#define DEFAULT_OUTBOUND_LATENCY        0       /* in nsec */
#define DEFAULT_NO_RESET_CLOCK          false
#define DEFAULT_DOMAIN_NUMBER           0
#define DEFAULT_DELAY_MECHANISM         E2E
#define DEFAULT_AP                      2
#define DEFAULT_AI                      16
#define DEFAULT_DELAY_S                 6 /* exponencial smoothing - 2^s */
#define DEFAULT_OFFSET_S                1 /* exponencial smoothing - 2^s */
#define DEFAULT_ANNOUNCE_INTERVAL       1 /* 0 in 802.1AS */
#define DEFAULT_UTC_OFFSET              34
#define DEFAULT_UTC_VALID               false
#define DEFAULT_PDELAYREQ_INTERVAL      1 /* -4 in 802.1AS */
#define DEFAULT_DELAYREQ_INTERVAL       3 /* from DEFAULT_SYNC_INTERVAL to DEFAULT_SYNC_INTERVAL + 5 */
#define DEFAULT_SYNC_INTERVAL           0 /* -7 in 802.1AS */
#define DEFAULT_SYNC_RECEIPT_TIMEOUT    3
#define DEFAULT_ANNOUNCE_RECEIPT_TIMEOUT 6 /* 3 by default */
#define DEFAULT_QUALIFICATION_TIMEOUT   -9 /* DEFAULT_ANNOUNCE_INTERVAL + N */
#define DEFAULT_FOREIGN_MASTER_TIME_WINDOW 4
#define DEFAULT_FOREIGN_MASTER_THRESHOLD 2
#define DEFAULT_CLOCK_CLASS             248
#define DEFAULT_CLOCK_CLASS_SLAVE_ONLY  255
#define DEFAULT_CLOCK_ACCURACY          0xFE
#define DEFAULT_PRIORITY1               248
#define DEFAULT_PRIORITY2               248
#define DEFAULT_CLOCK_VARIANCE          5000 /* To be determined in 802.1AS */
#define DEFAULT_MAX_FOREIGN_RECORDS     5
#define DEFAULT_PARENTS_STATS           false
#define DEFAULT_TWO_STEP_FLAG           true /* Transmitting only SYNC message or SYNC and FOLLOW UP */
#define DEFAULT_TIME_SOURCE             INTERNAL_OSCILLATOR
#define DEFAULT_TIME_TRACEABLE          false /* time derived from atomic clock? */
#define DEFAULT_FREQUENCY_TRACEABLE     false /* frequency derived from frequency standard? */
#define DEFAULT_TIMESCALE               ARB_TIMESCALE /* PTP_TIMESCALE or ARB_TIMESCALE */

#define NUMBER_PORTS                    1
#define VERSION_PTP                     2
#define BOUNDARY_CLOCK                  false
#define SLAVE_ONLY                      true
#define NO_ADJUST                       false

enum
{
    PTP_INITIALIZING = 0,
    PTP_FAULTY,
    PTP_DISABLED,
    PTP_LISTENING,
    PTP_PRE_MASTER,
    PTP_MASTER,
    PTP_PASSIVE,
    PTP_UNCALIBRATED,
    PTP_SLAVE
};


void ptp_toState(PtpClock *ptpClock, uint8_t state);
void ptp_doState(PtpClock *ptpClock);
bool ptp_doInit(PtpClock *ptpClock);

static void ptp_handle(PtpClock *ptpClock);
static void handleAnnounce(PtpClock *ptpClock, bool isFromSelf);
static void handleSync(PtpClock *ptpClock, TimeInternal *time, bool isFromSelf);
static void handleFollowUp(PtpClock *ptpClock, bool isFromSelf);
static void handleDelayReq(PtpClock *ptpClock, TimeInternal *time, bool isFromSelf);
static void handleDelayResp(PtpClock *ptpClock, bool  isFromSelf);

static void issueAnnounce(PtpClock *ptpClock);
static void issueSync(PtpClock *ptpClock);
static void issueFollowup(PtpClock *ptpClock, const TimeInternal *time);
static void issueDelayReq(PtpClock *ptpClock);
static void issueDelayResp(PtpClock *ptpClock, const TimeInternal *time, const MsgHeader * delayReqHeader);
#endif
