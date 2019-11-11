#include <stdio.h>
#include <string.h>
#include <time.h>

#include "FreeRTOS.h"
#include "os_task.h"
#include "rti_runtimestats.h"
#include "ma_date_and_time.h"
#include "FreeRTOSTIMEConfig.h"

int iTimeZone = 3600 * configTIME_TIME_ZONE;

extern volatile time_t xSysTimeSeconds;		/* Rendszeridõ (EPOCH) másodpercek */
extern volatile unsigned int  xSysTimeMsec;	/* Rendszeridõ ezred másodpercek */

/* FreeRTOS time() implementáció
 * az 1970. január 1. 0:00:00 óta eltelt másodpercek számát adja vissza
 * A 32 bites time_t problémát jelenthetet 2038-ban. Ez a megvalósítás már
 * ennek figyelembe vételével történt.
 */
time_t FreeRTOS_time(time_t *pxTime)
{
/* 64 bites hozzáférésnél kritikus szakasz. */
#if(__time64_t)
	portTICK_TYPE_ENTER_CRITICAL();
	time_t xNow = (time_t)xSysTimeSeconds;
	portTICK_TYPE_EXIT_CRITICAL();
#else
	time_t xNow = (time_t)xSysTimeSeconds;
#endif
	if(pxTime != NULL)
	{
		*pxTime = xNow;
	}
	return xNow;
}
/*-----------------------------------------------------------*/

void FreeRTOS_settime(time_t *pxTime)
{
	portTICK_TYPE_ENTER_CRITICAL();
	{
		xSysTimeSeconds = (time_t) *pxTime;
		xSysTimeMsec = (uint32_t) 0;
	}
	portTICK_TYPE_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

time_t FreeRTOS_get_secs_msec(time_t *pulMsec)
{
	time_t uxReturn;
	portTICK_TYPE_ENTER_CRITICAL();
	{
		uxReturn = (time_t) xSysTimeSeconds;
		if(pulMsec != NULL)
		{
			*pulMsec = xSysTimeMsec;
		}
	}
	portTICK_TYPE_EXIT_CRITICAL();

	return uxReturn;
}
/*-----------------------------------------------------------*/

void FreeRTOS_set_secs_msec(time_t *pulSeconds, time_t *pulMsec)
{
	portTICK_TYPE_ENTER_CRITICAL();
	{
		xSysTimeSeconds = *pulSeconds;
		if( pulMsec != NULL )
		{
			xSysTimeMsec = *pulMsec;
		}
	}
	portTICK_TYPE_EXIT_CRITICAL();
}
/*-----------------------------------------------------------*/
