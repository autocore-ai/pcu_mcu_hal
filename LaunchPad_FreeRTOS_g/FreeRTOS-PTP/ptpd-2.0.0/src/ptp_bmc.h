#ifndef PTP_BMC_H_
#define PTP_BMC_H_
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ptp_types.h"

 enum
{
    FLAG1_LEAP61 = 0x01,
    FLAG1_LEAP59 = 0x02,
    FLAG1_UTC_OFFSET_VALID = 0x04,
    FLAG1_PTP_TIMESCALE = 0x08,
    FLAG1_TIME_TRACEABLE = 0x10,
    FLAG1_FREQUENCY_TRACEABLE = 0x20,
};

 enum
 {
     E2E = 1,
     P2P = 2,
     DELAY_DISABLED = 0xFE
 };

 enum
 {
     ATOMIC_CLOCK = 0x10,
     GPS = 0x20,
     TERRESTRIAL_RADIO = 0x30,
     PTP = 0x40,
     NTP = 0x50,
     HAND_SET = 0x60,
     OTHER = 0x90,
     INTERNAL_OSCILLATOR = 0xA0
 };
 enum
 {
     ARB_TIMESCALE,
     PTP_TIMESCALE
 };
enum
{
    POWERUP = 0x0001,
    INITIALIZE = 0x0002,
    DESIGNATED_ENABLED = 0x0004,
    DESIGNATED_DISABLED = 0x0008,
    FAULT_CLEARED = 0x0010,
    FAULT_DETECTED = 0x0020,
    STATE_DECISION_EVENT = 0x0040,
    QUALIFICATION_TIMEOUT_EXPIRES = 0x0080,
    ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES = 0x0100,
    SYNCHRONIZATION_FAULT = 0x0200,
    MASTER_CLOCK_SELECTED = 0x0400,
    /* non spec */
    MASTER_CLOCK_CHANGED = 0x0800,
};

void initData(PtpClock *ptpClock);
bool isSamePortIdentity(const PortIdentity * A, const PortIdentity * B);
void s1(PtpClock *ptpClock, const MsgHeader *header, const MsgAnnounce *announce);
void m1(PtpClock *ptpClock);

void addForeign(PtpClock *ptpClock, const MsgHeader *header, const MsgAnnounce * announce);
uint8_t bmc(PtpClock *ptpClock);
int8_t bmcDataSetComparison(MsgHeader *headerA, MsgAnnounce *announceA,
                            MsgHeader *headerB, MsgAnnounce *announceB, PtpClock *ptpClock);
uint8_t bmcStateDecision(MsgHeader *header, MsgAnnounce *announce, PtpClock *ptpClock);
#endif
