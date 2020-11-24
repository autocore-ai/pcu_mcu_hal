/*
 * FreeRTOS+IO V1.0.1 (C) 2012 Real Time Engineers ltd.
 *
 * FreeRTOS+IO is an add-on component to FreeRTOS.  It is not, in itself, part
 * of the FreeRTOS kernel.  FreeRTOS+IO is licensed separately from FreeRTOS,
 * and uses a different license to FreeRTOS.  FreeRTOS+IO uses a dual license
 * model, information on which is provided below:
 *
 * - Open source licensing -
 * FreeRTOS+IO is a free download and may be used, modified and distributed
 * without charge provided the user adheres to version two of the GNU General
 * Public license (GPL) and does not remove the copyright notice or this text.
 * The GPL V2 text is available on the gnu.org web site, and on the following
 * URL: http://www.FreeRTOS.org/gpl-2.0.txt
 *
 * - Commercial licensing -
 * Businesses and individuals who wish to incorporate FreeRTOS+IO into
 * proprietary software for redistribution in any form must first obtain a low
 * cost commercial license - and in-so-doing support the maintenance, support
 * and further development of the FreeRTOS+IO product.  Commercial licenses can
 * be obtained from http://shop.freertos.org and do not require any source files
 * to be changed.
 *
 * FreeRTOS+IO is distributed in the hope that it will be useful.  You cannot
 * use FreeRTOS+IO unless you agree that you use the software 'as is'.
 * FreeRTOS+IO is provided WITHOUT ANY WARRANTY; without even the implied
 * warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. Real Time Engineers Ltd. disclaims all conditions and terms, be they
 * implied, expressed, or statutory.
 *
 * 1 tab == 4 spaces!
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/FreeRTOS-Plus
 *
 */

/* Modified for Texas Instruments TMS570LS20X and TMS570LS31X microcontroller family.
 * FreeRTOS-Plus-IO - TMS570LS20X31X (C) 2015 Lovas Szilárd
 * Email: lovas.szilard@gmail.com
 */


#ifndef TEXAS_TMS570LC4357_HDK_BOARD_H_
#define TEXAS_TMS570LC4357_HDK_BOARD_H_

#define CLRINT	CLEARINT
#define _CPU_TMS570LS4357_
//#define sciREG1 scilinREG
/* Header files for all the driver libraries that can be used with this BSP. */
#include "tms570ls20x31x_uart.h"
#include "tms570ls20x31x_dma.h"
#include <FreeRTOS_DriverInterface.h>

/*******************************************************************************
 * Definitions used by FreeRTOS+IO to determine the peripherals that are
 * available on the board, and the functions used to interface with the target
 * specific peripheral drivers.
 ******************************************************************************/

/*******************************************************************************
 * @def EmifMemorySize
 * @brief Size of exteral memory in bytes
 */
#define boardEMIF_MEMORY_SIZE 0x800000



/*******************************************************************************
 * @def maxNumericalIrqPriority
 * @brief Maximum value of the IRQ priority (the highest number is the lowest priority)
 */
#define maxNumericalIrqPriority 0x3f

/*******************************************************************************
 * @def maxNumberOfDMAChannels
 * @brief Maximum number of the DMA channels
 */
#define maxNumberOfDMAChannels 32

/*******************************************************************************
 * Definitions used by the UART-interrupt-driven-command-console.c example file.
 *
 * See http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_IO/Board_Support_Packages.shtml
 *
 ******************************************************************************/

#define boardAVAILABLE_DEVICES_LIST												\
{																				\
	{ ( const int8_t * const ) "/UART0/", eUART_TYPE, ( void * ) sciREG4 },		\
	{ ( const int8_t * const ) "/UART1/", eUART_TYPE, ( void * ) sciREG3 }		\
}

/*******************************************************************************
 * Set the default baud rate used by a UART.
 ******************************************************************************/
#define boardDEFAULT_UART_BAUD		115200

/*******************************************************************************
 * Command console definitions.
 ******************************************************************************/
#define boardCOMMAND_CONSOLE_UART	( const int8_t * ) "/UART0/"

/*******************************************************************************
 * Map the FreeRTOS+IO interface to the tms570ls20216 specific functions.
 *******************************************************************************/
portBASE_TYPE vFreeRTOS_tms570ls20x31x_PopulateFunctionPointers( const Peripheral_Types_t ePeripheralType, Peripheral_Control_t * const pxPeripheralControl );
#define boardFreeRTOS_PopulateFunctionPointers vFreeRTOS_tms570ls20x31x_PopulateFunctionPointers

/*******************************************************************************
 * These define the number of peripherals available on the microcontroller -
 * not the number of peripherals that are supported by the software
 ******************************************************************************/
#define boardNUM_UARTS				2 /* SCI1, SCI2 */
//#define boardNUM_SPIS				3 /* SPI1 to SPI3. */
//#define boardNUM_CANS				2 /* CAN1 to CAN2. */

#endif /* TEXAS_TMS570LC4357_HDK_BOARD_H_ */
