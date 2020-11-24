/*********************2020.02.23-alex********************/
#ifndef PTP_TIME_H_
#define PTP_TIME_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ptp_types.h"

enum
{
    DELAYREQ_INTERVAL_TIMER = 0,/**<\brief Timer handling the delayReq Interva */
    SYNC_INTERVAL_TIMER,/**<\brief Timer handling Interval between master sends two Syncs messages */
    ANNOUNCE_RECEIPT_TIMER,/**<\brief Timer handling announce receipt timeout */
    ANNOUNCE_INTERVAL_TIMER, /**<\brief Timer handling interval before master sends two announce messages */
    TIMER_ARRAY_SIZE  /* this one is non-spec */
};

void normalizeTime(TimeInternal *r);
void addTime(TimeInternal *r, const TimeInternal *x, const TimeInternal *y);
void subTime(TimeInternal *r, const TimeInternal *x, const TimeInternal *y);
void div2Time(TimeInternal *r);

void scaledNanosecondsToInternalTime(const int64_t *scaledNanoseconds, TimeInternal *internal);
void toInternalTime(TimeInternal *internal, const Timestamp *external);
void fromInternalTime(const TimeInternal *internal, Timestamp *external);

void initTimer(void);
void timerStop(int32_t index);
void timerStart(int32_t index, uint32_t interval_ms);
bool timerExpired(int32_t index);

void getTime(TimeInternal *time);
void setTime(const TimeInternal *time);

#endif
