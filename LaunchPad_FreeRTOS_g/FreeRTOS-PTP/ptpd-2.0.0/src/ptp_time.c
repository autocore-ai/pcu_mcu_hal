/*********************2020.02.23-alex********************/
#include "ptp_time.h"
#include "ma_date_and_time.h"

static TimerHandle_t ptpdTimers[TIMER_ARRAY_SIZE];
static bool ptpdTimersExpired[TIMER_ARRAY_SIZE];

#if 0
static char *timerString(uint8_t index)
{
    switch (index)
    {
        case DELAYREQ_INTERVAL_TIMER: return (char *) "DELAYREQ_INTERVAL_TIMER";
        case SYNC_INTERVAL_TIMER: return (char *) "SYNC_INTERVAL_TIMER";
        case ANNOUNCE_RECEIPT_TIMER: return (char *) "ANNOUNCE_RECEIPT_TIMER";
        case ANNOUNCE_INTERVAL_TIMER: return (char *) "ANNOUNCE_INTERVAL_TIMER";
        default: break;
    }
    return (char *) "UNKNOWN";
}
#endif

void normalizeTime(TimeInternal *r)
{
    r->seconds += r->nanoseconds / 1000000000;
    r->nanoseconds -= r->nanoseconds / 1000000000 * 1000000000;
    if (r->seconds > 0 && r->nanoseconds < 0)
    {
        r->seconds -= 1;
        r->nanoseconds += 1000000000;
    }
    else if (r->seconds < 0 && r->nanoseconds > 0)
    {
        r->seconds += 1;
        r->nanoseconds -= 1000000000;
    }
}

void addTime(TimeInternal *r, const TimeInternal *x, const TimeInternal *y)
{
    r->seconds = x->seconds + y->seconds;
    r->nanoseconds = x->nanoseconds + y->nanoseconds;
    normalizeTime(r);
}

void subTime(TimeInternal *r, const TimeInternal *x, const TimeInternal *y)
{
    r->seconds = x->seconds - y->seconds;
    r->nanoseconds = x->nanoseconds - y->nanoseconds;
    normalizeTime(r);
}
void div2Time(TimeInternal *r)
{
    r->nanoseconds += r->seconds % 2 * 1000000000;
    r->seconds /= 2;
    r->nanoseconds /= 2;
    normalizeTime(r);
}
void scaledNanosecondsToInternalTime(const int64_t *scaledNanoseconds, TimeInternal *internal)
{
    int sign;
    int64_t nanoseconds = *scaledNanoseconds;
    /* Determine sign of result big integer number */
    if (nanoseconds < 0)
    {
        nanoseconds = -nanoseconds;
        sign = -1;
    }
    else
    {
        sign = 1;
    }
    /* fractional nanoseconds are excluded (see 5.3.2) */
    nanoseconds >>= 16;
    internal->seconds = sign * (nanoseconds / 1000000000);
    internal->nanoseconds = sign * (nanoseconds % 1000000000);
}

void toInternalTime(TimeInternal *internal, const Timestamp *external)
{
    /* Program will not run after 2038... */
    if (external->secondsField.lsb < INT32_MAX)
    {
        internal->seconds = external->secondsField.lsb;
        internal->nanoseconds = external->nanosecondsField;
    }
    else
    {
        FreeRTOS_printf(("Clock servo canno't be executed : seconds field is higher than signed integer (32bits)\r\n"));
        return;
    }
}
void fromInternalTime(const TimeInternal *internal, Timestamp *external)
{
    if ((internal->seconds & ~INT32_MAX) || (internal->nanoseconds & ~INT32_MAX))
    {
        FreeRTOS_printf(("Negative value canno't be converted into timestamp \r\n"));
        return;
    }
    else
    {
        external->secondsField.lsb = internal->seconds;
        external->nanosecondsField = internal->nanoseconds;
        external->secondsField.msb = 0;
    }
}

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    uint32_t index = ( uint32_t ) pvTimerGetTimerID( xTimer );
    if (index >= TIMER_ARRAY_SIZE)
        return;
    ptpdTimersExpired[index] = true;
}

void initTimer(void)
{
    int index = 0;
    for(index = 0; index < TIMER_ARRAY_SIZE; index++)
    {
        ptpdTimers[index] = xTimerCreate( "PTPTimer",
                             3000,
                             pdFALSE,
                             (void*)index,
                             prvAutoReloadTimerCallback );
        ptpdTimersExpired[index] = false;
    }
}

void timerStop(int32_t index)
{
    if (index >= TIMER_ARRAY_SIZE)
            return;
    TimerHandle_t xPTPTimer = ptpdTimers[index];
    if( xPTPTimer != NULL )
    {
        xTimerStop( xPTPTimer, 0 );
        ptpdTimersExpired[index] = false;
    }
}

void timerStart(int32_t index, uint32_t interval_ms)
{
    if (index >= TIMER_ARRAY_SIZE)
            return;
    TimerHandle_t xPTPTimer = ptpdTimers[index];
    if( xPTPTimer != NULL )
    {
        if(xTimerIsTimerActive(xPTPTimer))
        {
            xTimerStop( xPTPTimer, 0 );
        }
        xTimerChangePeriod(xPTPTimer, pdMS_TO_TICKS(interval_ms), 0);
        xTimerStart( xPTPTimer, 0 );
        ptpdTimersExpired[index] = false;
    }
}

bool timerExpired(int32_t index)
{
    if (index >= TIMER_ARRAY_SIZE)
        return false;
    if (!ptpdTimersExpired[index])
        return false;
    ptpdTimersExpired[index] = false;
    return true;
}

void getTime(TimeInternal *time)
{
    uint32_t uxSecs,uxmSecs;
    uxSecs = FreeRTOS_get_secs_msec(&uxmSecs);
    time->seconds = uxSecs;
    time->nanoseconds = uxmSecs * 1000000;
}

void setTime(const TimeInternal *time)
{
    uint32_t uxSecs = time->seconds;
    uint32_t uxmSecs = time->nanoseconds / 1000000;
    FreeRTOS_set_time_ptp(&uxSecs, &uxmSecs);
}
