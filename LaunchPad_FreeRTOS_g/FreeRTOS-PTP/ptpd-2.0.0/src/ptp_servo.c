/*********************2020.02.23-alex********************/
#include "ptp_servo.h"
#include "ptp_bmc.h"
#include "ptp_protocol.h"
#include "ptp_time.h"



void updateOffset(PtpClock *ptpClock, const TimeInternal *syncEventIngressTimestamp,
                  const TimeInternal *preciseOriginTimestamp, const TimeInternal *correctionField)
{
    subTime(&ptpClock->Tms, syncEventIngressTimestamp, preciseOriginTimestamp);
    subTime(&ptpClock->Tms, &ptpClock->Tms, correctionField);
    ptpClock->offsetFromMaster = ptpClock->Tms;

    if (ptpClock->portDS.delayMechanism == E2E)
    {
        subTime(&ptpClock->offsetFromMaster, &ptpClock->offsetFromMaster, &ptpClock->meanPathDelay);
    }
    if(ptpClock->offsetFromMaster.seconds)
    {
        ptpClock->ofm_filt.nsec_prev = 0;
        return;
    }

    ptpClock->ofm_filt.y = ptpClock->offsetFromMaster.nanoseconds / 2 + ptpClock->ofm_filt.nsec_prev / 2;
    ptpClock->ofm_filt.nsec_prev = ptpClock->offsetFromMaster.nanoseconds;
    ptpClock->offsetFromMaster.nanoseconds = ptpClock->ofm_filt.y;

    //ptpClock->waitingForFirstOffset = true;
}

void updateClock(PtpClock *ptpClock)
{
    TimeInternal timeTmp;

    if (ptpClock->offsetFromMaster.seconds || abs(ptpClock->offsetFromMaster.nanoseconds) > MAX_ADJ_OFFSET_NS)
    {
        getTime(&timeTmp);
        subTime(&timeTmp, &timeTmp, &ptpClock->offsetFromMaster);
        setTime(&timeTmp);
    }
    if (ptpClock->offsetFromMaster.seconds)
        initClock(ptpClock);
    FreeRTOS_printf(("off %d:%d\r\n", ptpClock->offsetFromMaster.seconds, ptpClock->offsetFromMaster.nanoseconds));
}
void updateDelay(PtpClock * ptpClock, const TimeInternal *delayEventEgressTimestamp,
                 const TimeInternal *recieveTimestamp, const TimeInternal *correctionField)
{
    if(!ptpClock->waitingForFirstOffset)
        return;

    subTime(&ptpClock->Tsm, recieveTimestamp, delayEventEgressTimestamp);
    subTime(&ptpClock->Tsm, &ptpClock->Tsm, correctionField);
    addTime(&ptpClock->meanPathDelay, &ptpClock->Tms, &ptpClock->Tsm);
    div2Time(&ptpClock->meanPathDelay);
    if (ptpClock->Tsm.seconds || ptpClock->Tms.seconds || ptpClock->meanPathDelay.seconds)
    {
        ptpClock->meanPathDelay.seconds = ptpClock->meanPathDelay.nanoseconds = 0;
        ptpClock->owd_filt.s_exp = ptpClock->owd_filt.nsec_prev = 0;
        return;
    }
    int16_t s = ptpClock->servo.sDelay;
    while (abs(ptpClock->owd_filt.y) >> (31 - s))
        --s;

    if (ptpClock->owd_filt.s_exp < 1)
        ptpClock->owd_filt.s_exp = 1;
    else if (ptpClock->owd_filt.s_exp < 1 << s)
        ++ptpClock->owd_filt.s_exp;
    else if (ptpClock->owd_filt.s_exp > 1 << s)
        ptpClock->owd_filt.s_exp = 1 << s;

    ptpClock->owd_filt.y = (ptpClock->owd_filt.s_exp - 1) * ptpClock->owd_filt.y / ptpClock->owd_filt.s_exp +
        (ptpClock->meanPathDelay.nanoseconds / 2 + ptpClock->owd_filt.nsec_prev / 2) / ptpClock->owd_filt.s_exp;

    ptpClock->owd_filt.nsec_prev = ptpClock->meanPathDelay.nanoseconds;
    ptpClock->meanPathDelay.nanoseconds = ptpClock->owd_filt.y;
}
void initClock(PtpClock *ptpClock)
{

    ptpClock->offsetFromMaster.seconds = ptpClock->offsetFromMaster.nanoseconds = 0;
    ptpClock->meanPathDelay.seconds    = ptpClock->meanPathDelay.nanoseconds = 0;

    ptpClock->ofm_filt.y         = 0;
    ptpClock->ofm_filt.nsec_prev = 0;
    ptpClock->owd_filt.s_exp     = 0;

    ptpClock->waitingForFirstOffset = false;
}




