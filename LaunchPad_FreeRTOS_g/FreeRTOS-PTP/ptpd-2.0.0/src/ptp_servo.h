/*********************2020.02.23-alex********************/
#ifndef PTP_SERVO_H_
#define PTP_SERVO_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ptp_types.h"

#define max(x,y) (((x) > (y)) ? (x) : (y))
#define min(x,y) (((x) > (y)) ? (x) : (y))

#define DEFAULT_CALIBRATED_OFFSET_NS    10000 /* offset from master < 10us -> calibrated */
#define DEFAULT_UNCALIBRATED_OFFSET_NS  1000000 /* offset from master > 1000us -> uncalibrated */
#define MAX_ADJ_OFFSET_NS               1000000 /* max offset to try to adjust it < 1ms */
#define ADJ_FREQ_MAX                    512000

void initClock(PtpClock *ptpClock);
void updateClock(PtpClock *ptpClock);
void updateDelay(PtpClock * ptpClock, const TimeInternal *delayEventEgressTimestamp,
                 const TimeInternal *recieveTimestamp, const TimeInternal *correctionField);
void updatePeerDelay(PtpClock *ptpClock, const TimeInternal *correctionField, bool  twoStep);

void updateOffset(PtpClock *ptpClock, const TimeInternal *syncEventIngressTimestamp,
                  const TimeInternal *preciseOriginTimestamp, const TimeInternal *correctionField);

#endif
