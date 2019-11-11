#include "time_common.h"

#include "FreeRTOS.h"
#include "os_task.h"

#include <time.h>



//==================================================================
//                             PUBLIC
//==================================================================
int64_t uxr_millis(void)
{
    TimeOut_t tick_count;

    /* Get the current tick count. */
    vTaskSetTimeOutState(&tick_count);

    /* Pack the current tick count in int64_t. */
    int64_t total_tick = (int64_t) tick_count.xOverflowCount;
#if( configUSE_16_BIT_TICKS == 1 )    /* Use 16-bit tick type. */
    total_tick <<= 16;
#else                                 /* Use 32-bit tick type. */
    total_tick <<= 32;
#endif
    total_tick |= (int64_t) tick_count.xTimeOnEntering;

    return (total_tick / (int64_t) portTICK_PERIOD_MS);
}
