#include <stdio.h>
#include <string.h>
#include <time.h>

#include "FreeRTOS.h"
#include "os_task.h"
#include "ff_time.h"
#include "Sci_driver.h"
#include "rti_runtimestats.h"
#include "ma_date_and_time.h"
#include "FreeRTOSTIMEConfig.h"
#include "FreeRTOSIPConfig.h"

int iTimeZone = 3600 * configTIME_TIME_ZONE;

extern volatile time_t xSysTimeSeconds;     /* Rendszerid� (EPOCH) m�sodpercek */
extern volatile unsigned int  xSysTimeMsec; /* Rendszerid� ezred m�sodpercek */

enum ETimeType {
    ETypeGPS,
    ETypeNTP,
    ETypeRTC,
    ETypePTP
};
static enum ETimeType xTimeTpye = ETypePTP;

void FreeRTOS_set_time_type(uint8_t xtype)
{
    xTimeTpye = xtype;
}

uint8_t FreeRTOS_get_time_type()
{
    uint8_t xtype = xTimeTpye;
    return xtype;
}

/* FreeRTOS time() implement�ci�
 * az 1970. janu�r 1. 0:00:00 �ta eltelt m�sodpercek sz�m�t adja vissza
 * A 32 bites time_t probl�m�t jelenthetet 2038-ban. Ez a megval�s�t�s m�r
 * ennek figyelembe v�tel�vel t�rt�nt.
 */
time_t FreeRTOS_time(time_t *pxTime)
{
/* 64 bites hozz�f�r�sn�l kritikus szakasz. */
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

void FreeRTOS_set_time_ptp(time_t *pulSeconds, time_t *pulMsec)
{
    FreeRTOS_set_secs_msec(pulSeconds, pulMsec);
#if( ipconfigUSE_PTP == 1 )
    FreeRTOS_set_time_type(ETypePTP);
#endif
}

void FreeRTOS_gettime(time_t *pulSeconds, time_t *pulMsec)
{
    *pulSeconds = FreeRTOS_get_secs_msec(pulMsec);
    *pulSeconds += iTimeZone;
}


void FreeRTOS_showtime(void)
{
    uint8_t type;
     time_t uxCurrentMS,uxCurrentSeconds;
     type = FreeRTOS_get_time_type();
    char tim[10];
    sprintf(tim,"type is %d!\n",type);

    FF_TimeStruct_t xTimeStruct;
    FreeRTOS_gettime(&uxCurrentSeconds, &uxCurrentMS );
    FreeRTOS_gmtime_r( &uxCurrentSeconds, &xTimeStruct );
    char time[250];
    sprintf(time,"Time: %04d-%02d-%02d %2d:%02d:%02d.%03u\r\n",
            xTimeStruct.tm_year + 1900,
            xTimeStruct.tm_mon + 1,
            xTimeStruct.tm_mday,
            xTimeStruct.tm_hour,
            xTimeStruct.tm_min,
            xTimeStruct.tm_sec,
            ( unsigned )uxCurrentMS);
    UartSendString(sciREG3,time);
}
