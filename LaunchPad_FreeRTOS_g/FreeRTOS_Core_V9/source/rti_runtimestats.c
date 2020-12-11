#include <time.h>
#include "rti_runtimestats.h"
#include "HL_sys_vim.h"
#include "FreeRTOS.h"
#include "FreeRTOSTIMEConfig.h"
#include "HL_gio.h"

volatile time_t xSysTimeSeconds = configTIME_START_EPOCH_TIME;	/* Rendszerid� (EPOCH) m醩odpercek.*/
volatile unsigned int xSysTimeMsec;								/* Rendszerid� ezredm醩odpercek */
volatile unsigned int xHighPrecisionTimerUsecMSB = 0;			/* 64 bites Nagyfelbont醩� (usec) timer fels� 32 bit */

static BaseType_t xTimeInit = pdFALSE;
#if ( configGENERATE_RUN_TIME_STATS == 1 )
void vConfigureTimerForRunTimeStats(void)
{
	/* Timer 1. tilt醩a */
	RTI_GCTRL_REG &= 0xFFFFFFFDU;

	/* A counter 閟 prescale regiszterek inicializ醠醩a */
	/* RTI Up counter 1. This register holds the current value of the up counter 1 and prescales the RTI
	clock. It will be only updated by a previous read of free running counter 1 (RTIFRC1). This
	method of updating effectively gives a 64-bit read of both counters, without having the problem
	of a counter being updated between two consecutive reads on RTIUC1 and RTIFRC1. */
	RTI_UC1_REG  =  0x00000000U;

	/* RTI Free running counter 1. This register holds the current value of the free running counter 1 and
	will be updated continuously. A read of this register returns the current value of the counter.
	A write to this register presets the counter. The counter increments then from this written value
	upwards.
	Note: If counters must be preset, they must be disabled in the RTIGCTRL register to
	ensure consistency between RTIUC1 and RTIFRC1. */
	RTI_FRC1_REG =  0x00000000U;

	/* RTI Compare up counter 1. This register holds the compare value, which is compared with the up
	counter 1. When the compare matches, the free running counter 1 (RTIFRC1) is incremented.
	The up counter is cleared to zero when the counter value matches the CPUC1 value. The value
	set in this prescales the RTI clock according to the following formula:
	If CPUC1 = 0, then
	fFRC0 = RTICLK/(232+1) (Setting CPUC1 equal to 0 is not recommended. Doing so will hold the
	Up Counter at 0 for 2 RTICLK cycles after it overflows from FFFF FFFFh to 0.)
	If CPUC1 != 0, then fFRC1 = RTICLK/(RTICPUC1+1) */
	RTI_CPUC1_REG = (configCPU_CLOCK_HZ / configRunTimeStats_RATE_HZ) - 1;

	/* Overflow Interrupt  */
	vimChannelMap(RTI_OVERFLOW_1, RTI_OVERFLOW_1, &vFreeRTOSRTIOverFlow1Interrupt);

	/* Timer 1.*/
	RTI_GCTRL_REG |= 0x00000002U;

}

#pragma INTERRUPT(vFreeRTOSRTIOverFlow1Interrupt, IRQ)
void vFreeRTOSRTIOverFlow1Interrupt(void)
{
	/* RTI OverFLow 1*/
	RTI_CLEARINTENA_REG = 0x00040000;
	/* RTI OverFLow 1  */
	RTI_INTFLAG_REG = 0x00040000;
	xHighPrecisionTimerUsecMSB++;
	/* RTI OverFlow 1 */
	RTI_SETINTENA_REG |= 0x00040000;
}

/*
 * Nagyfelbont醩� (usec) relat韛 id�.
 */
uint64_t xGetHighResolutionTime(void)
{
	unsigned int xHighResolutionTimeMSB;	/* Fels� 32 bit */
	unsigned int xHighResolutionTimeLSB;	/* Als� 32 bit */

	/* 2x32 bites konzisztens adat hozz醘閞閟. */
	do
	{
		xHighResolutionTimeMSB = xHighPrecisionTimerUsecMSB;
		xHighResolutionTimeLSB = RTI_FRC1_REG;
	}while(xHighResolutionTimeMSB != xHighPrecisionTimerUsecMSB);

	return ((uint64_t)xHighResolutionTimeMSB << 32) + xHighResolutionTimeLSB;
}
#endif

/*
 * Az RTI modul konfigur醠醩a a rendszerid� kiszolg醠醩醨a.
 * Felt閠elezi, hogy a HALCoGen m醨 be醠l韙otta az RTI-t az 黷emez� (tick) kiszolg醠醩醨a.
 * Compare 0 modul: tick gener醠醩a (os_port.c)
 * Compare 1 modul: 1ms rendszerid鮝lap gener醠醩a
 */
void vConfigureTimerForSysTime(void)
{
    if(pdFALSE == xTimeInit)
    {
		/* COMPSEL1 az RTIFRC0 sz醡l醠髏 fogja haszn醠ni. */
		RTI_COMPCTRL_REG &= 0xffffffefU;

		/* RTI Compare 1. This register holds a value that is compared with the counter selected in the
		compare control logic. If RTIFRC0 or RTIFRC1, depending on the counter selected, matches
		this compare value, an interrupt is flagged. With this register, it is possible to initiate a DMA request. */
		RTI_COMP1_REG = RTI_FRC0_REG + (( configCPU_CLOCK_HZ / 2 ) / 1000) - 75;

		/* Update compare 1. This register holds a value that is added to the value in the RTICOMP1
		register each time a compare matches. This process allows periodic interrupts to be generated
		without software intervention. */
		RTI_UDCP1_REG = (( configCPU_CLOCK_HZ / 2 ) / 1000) - 75;

		/* Interrupt vektorok  */
		vimChannelMap(RTI_COMPARE_1, RTI_COMPARE_1, &vFreeRTOSRTICmp1Interrupt);

		/* RTI Compare 1  */
		RTI_SETINTENA_REG |= 0x00000002;

		/* RTI OverFlow 1  */
		RTI_SETINTENA_REG |= 0x00040000;

		vimEnableInterrupt(RTI_COMPARE_1,SYS_IRQ);

        xTimeInit = pdTRUE;
    }
}

/*
 * Compare 1 megszak韙醩 kezel� rutin, 1 msec gyakoris醙gal fut le.
 */
#pragma INTERRUPT(vFreeRTOSRTICmp1Interrupt, IRQ)
void vFreeRTOSRTICmp1Interrupt(void)
{
	/* RTI Compare 1  */
	RTI_CLEARINTENA_REG = 0x00000002;

	//gioToggleBit(gioPORTA, 0);
	if(xSysTimeMsec++ > 1000)
	{
		xSysTimeMsec = 0;
		xSysTimeSeconds++;
	}
	/* RTI Compare 1  */
	RTI_INTFLAG_REG = 0x00000002;
	/* RTI Compare 1  */
	RTI_SETINTENA_REG |= 0x00000002;
}

BaseType_t vSysTimeReady()
{
    if(pdTRUE == xTimeInit)
        return pdTRUE;
    else
        return pdFALSE;
}
