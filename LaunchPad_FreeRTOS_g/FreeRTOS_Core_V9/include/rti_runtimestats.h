/* RTI__runtimestats.h */

#ifndef __RTI__RUNTIMESTATS_H__
#define __RTI__RUNTIMESTATS__
#include "FreeRTOS.h"

/* RTI regiszterek */
#define RTI_GCTRL_REG 			(*((volatile uint32_t *)0xfffffc00)) /* RTI Global Control Register */
#define RTI_TBCTRL_REG 			(*((volatile uint32_t *)0xfffffc04)) /* RTI Timebase Control Register */
#define RTI_CAPCTRL_REG 		(*((volatile uint32_t *)0xfffffc08)) /* RTI Capture Control Register */
#define RTI_COMPCTRL_REG 		(*((volatile uint32_t *)0xfffffc0c)) /* RTI Compare Control Register */
#define RTI_FRC0_REG 			(*((volatile uint32_t *)0xfffffc10)) /* RTI Free Running Counter 0 Register */
#define RTI_UC0_REG 			(*((volatile uint32_t *)0xfffffc14)) /* RTI Up Counter 0 Register */
#define RTI_CPUC0_REG 			(*((volatile uint32_t *)0xfffffc18)) /* RTI Compare Up Counter 0 Register */
#define RTI_CAFRC0_REG 			(*((volatile uint32_t *)0xfffffc20)) /* RTI Capture Free Running Counter 0 Register */
#define RTI_CAUC0_REG 			(*((volatile uint32_t *)0xfffffc24)) /* RTI Capture Up Counter 0 Register */
#define RTI_FRC1_REG 			(*((volatile uint32_t *)0xfffffc30)) /* RTI Free Running Counter 1 Register */
#define RTI_UC1_REG 			(*((volatile uint32_t *)0xfffffc34)) /* RTI Up Counter 1 Register */
#define RTI_CPUC1_REG 			(*((volatile uint32_t *)0xfffffc38)) /* RTI Compare Up Counter 1 Register */
#define RTI_CAFRC1_REG 			(*((volatile uint32_t *)0xfffffc40)) /* RTI Capture Free Running Counter 1 Register */
#define RTI_CAUC1_REG 			(*((volatile uint32_t *)0xfffffc44)) /* RTI Capture Up Counter 1 Register */
#define RTI_COMP0_REG 			(*((volatile uint32_t *)0xfffffc50)) /* RTI Compare 0 Register */
#define RTI_UDCP0_REG 			(*((volatile uint32_t *)0xfffffc54)) /* RTI Update Compare 0 Register */
#define RTI_COMP1_REG 			(*((volatile uint32_t *)0xfffffc58)) /* RTI Compare 1 Register */
#define RTI_UDCP1_REG 			(*((volatile uint32_t *)0xfffffc5c)) /* RTI Update Compare 1 Register */
#define RTI_COMP2_REG 			(*((volatile uint32_t *)0xfffffc60)) /* RTI Compare 2 Register */
#define RTI_UDCP2_REG 			(*((volatile uint32_t *)0xfffffc64)) /* RTI Update Compare 2 Register */
#define RTI_COMP3_REG 			(*((volatile uint32_t *)0xfffffc68)) /* RTI Compare 3 Register */
#define RTI_UDCP3_REG 			(*((volatile uint32_t *)0xfffffc6c)) /* RTI Update Compare 3 Register */
#define RTI_TBLCOMP_REG 		(*((volatile uint32_t *)0xfffffc70)) /* RTI Timebase Low Compare Register */
#define RTI_TBHCOMP_REG 		(*((volatile uint32_t *)0xfffffc74)) /* RTI Timebase High Compare Register */
#define RTI_SETINTENA_REG 		(*((volatile uint32_t *)0xfffffc80)) /* RTI Set Interrupt Enable Register */
#define RTI_CLEARINTENA_REG 	(*((volatile uint32_t *)0xfffffc84)) /* RTI Clear Interrupt Enable Register */
#define RTI_INTFLAG_REG 		(*((volatile uint32_t *)0xfffffc88)) /* RTI Interrupt Flag Register */
#define RTI_DWDCTRL_REG 		(*((volatile uint32_t *)0xfffffc90)) /* Digital Watchdog Control Register */
#define RTI_DWDPRLD_REG 		(*((volatile uint32_t *)0xfffffc94)) /* Digital Watchdog Preload Register */
#define RTI_WDSTATUS_REG 		(*((volatile uint32_t *)0xfffffc98)) /* Watchdog Status Register */
#define RTI_WDKEY_REG 			(*((volatile uint32_t *)0xfffffc9c)) /* RTI Watchdog Key Register */
#define RTI_DWDCNTR_REG 		(*((volatile uint32_t *)0xfffffca0)) /* RTI Digital Watchdog Down Counter Register */
#define RTI_WWDRXNCTRL_REG 		(*((volatile uint32_t *)0xfffffca4)) /* Digital Windowed Watchdog Reaction Control Register */
#define RTI_WWDSIZECTRL_REG 	(*((volatile uint32_t *)0xfffffca8)) /* Digital Windowed Watchdog Window Size Control Register */
#define RTI_INTCLRENABLE_REG 	(*((volatile uint32_t *)0xfffffcac)) /* RTI Compare Interrupt Clear Enable Register */
#define RTI_COMP0CLR_REG 		(*((volatile uint32_t *)0xfffffcb0)) /* RTI Compare 0 Clear Register */
#define RTI_COMP1CLR_REG 		(*((volatile uint32_t *)0xfffffcb4)) /* RTI Compare 1 Clear Register */
#define RTI_COMP2CLR_REG 		(*((volatile uint32_t *)0xfffffcb8)) /* RTI Compare 2 Clear Register */
#define RTI_COMP3CLR _REG		(*((volatile uint32_t *)0xfffffcbc)) /* RTI Compare 3 Clear Register */

/* RTI megszak韙醩 forr醩ok */
#define RTI_COMPARE_0			2U
#define RTI_COMPARE_1			3U
#define RTI_COMPARE_2			4U
#define RTI_COMPARE_3			5U
#define RTI_OVERFLOW_0			6U
#define RTI_OVERFLOW_1			7U
#define RTI_TIMEBASE_1			8U

BaseType_t vSysTimeReady();
void vConfigureTimerForRunTimeStats(void);			/* RTI konfigur醠醩a a runtime statisztik醟 kiszolg醠醩醜oz */
void vConfigureTimerForSysTime(void);				/* RTI konfigur醠醩a a rendszerid� kiszolg醠醩醜oz */
unsigned long long xGetHighResolutionTime(void);	/* usec felbont醩� relat韛 id� */
void vFreeRTOSRTIOverFlow1Interrupt(void);			/* OverFlow 1 interrupt kezel� rutin*/
void vFreeRTOSRTICmp1Interrupt(void);				/* Compare 1 interrupt kezel� rutin*/
#endif
