/*
 * FreeRTOS_runtimestats.h
 *
 *  Created on: 2015.03.06.
 *      Author: loszi
 */

#ifndef FREERTOS_RUNTIMESTATS_H_
#define FREERTOS_RUNTIMESTATS_H_

#define configUSE_STATS_FORMATTING_FUNCTIONS 1

/* Run Time Stats */
#if ( configGENERATE_RUN_TIME_STATS == 1 )
#define configRunTimeStats_RATE_HZ	( ( portTickType ) 1000000 )
extern void vConfigureTimerForRunTimeStats( void );
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ( * ( ( volatile unsigned long * ) 0xFFFFFC30 ) )
#endif

#endif /* FREERTOS_RUNTIMESTATS_H_ */
