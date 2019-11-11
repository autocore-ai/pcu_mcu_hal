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
 * FreeRTOS-Plus-IO - UART TMS570LS20X31X V0.0.2  (C) 2014 Lovas Szilárd
 * Email: lovas.szilard@gmail.com
 */

/**
* @file tms570ls20x31x_uart.c
*   @brief FreeRTOS-Plus-IO Uart Driver Implmentation File
*   @date 12.Aug.2014
*   @version 00.00.02
*
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"

/* FreeRTOS+IO includes. */
#include "FreeRTOS_IO.h"
#include "FreeRTOSIOConfig.h"
#include "IOUtils_Common.h"
#include "FreeRTOS_uart.h"

#include "tms570ls20x31x_uart.h"
#include "tms570ls20x31x_dma.h"

/* HALCoGen generated header files. */
#include "HL_sci.h"
#include "HL_sys_dma.h"
#include "HL_sys_vim.h"

#include "sys_main.h"

/* HALCoGen generated sci API. */
//#include <HL_sci.c>

/* Stores the transfer control structures that are currently in use by the
supported UART ports. */
Transfer_Control_t *pxUartTxTransferControlStructs[ boardNUM_UARTS ] = { NULL };
Transfer_Control_t *pxUartRxTransferControlStructs[ boardNUM_UARTS ] = { NULL };

/* Stores the DMA channels that are currently in use by the supported UART ports. */
uint8_t xUartTX_DMA_Channels[ boardNUM_UARTS ] = { 0xff };

/*-----------------------------------------------------------*/
/**
 * @fn portBASE_TYPE FreeRTOS_UART_open( Peripheral_Control_t * const pxPeripheralControl )
 * @param pxPeripheralControl
 * @return
 */
portBASE_TYPE FreeRTOS_UART_open( Peripheral_Control_t * const pxPeripheralControl )
{
	portBASE_TYPE xReturn;
	const uint8_t cPeripheralNumber = diGET_PERIPHERAL_NUMBER( pxPeripheralControl );
	sciBASE_t * const pxUART = ( sciBASE_t *) diGET_PERIPHERAL_BASE_ADDRESS( ( ( Peripheral_Control_t *) pxPeripheralControl ) );


	/* Sanity check the peripheral number. */
	if( cPeripheralNumber < boardNUM_UARTS )
	{
		pxPeripheralControl->read = FreeRTOS_UART_read;
		pxPeripheralControl->write = FreeRTOS_UART_write;
		pxPeripheralControl->ioctl = FreeRTOS_UART_ioctl;

		/* Setup the pins for the UART being used. */
		taskENTER_CRITICAL();
		{
			/* SCI setup related functions..  */
			sciSetBaudrate(pxUART, boardDEFAULT_UART_BAUD);

			/* Switch to the FreeRTOS-Plus-IO compatibility API mode. */
			configASSERT(xFreeRTOSsciInit(pxUART));
		}
		taskEXIT_CRITICAL();

		xReturn = pdPASS;
	}
	else
	{
		xReturn = pdFAIL;
	}

	return xReturn;
}
/*-----------------------------------------------------------*/
/**
 * @fn size_t FreeRTOS_UART_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes )
 * @param pxPeripheral
 * @param pvBuffer
 * @param xBytes
 * @return
 */
size_t FreeRTOS_UART_write( Peripheral_Descriptor_t const pxPeripheral, const void *pvBuffer, const size_t xBytes )
{
	volatile Peripheral_Control_t * const pxPeripheralControl = ( Peripheral_Control_t * ) pxPeripheral;
	sciBASE_t * const pxUART = ( sciBASE_t * ) diGET_PERIPHERAL_BASE_ADDRESS( ( ( Peripheral_Control_t * ) pxPeripheral ) );
	size_t xReturn = 0U;
	portBASE_TYPE i;

	/* Remember which transfer control structure is being used.
	The Tx interrupt will use this to continue to write data to the
	Tx FIFO/UART until the length member of the structure reaches
	zero. */

	int8_t cPeripheralNumber;
	cPeripheralNumber = diGET_PERIPHERAL_NUMBER( pxPeripheralControl );
	pxUartTxTransferControlStructs[ cPeripheralNumber  ] = diGET_TX_TRANSFER_STRUCT( pxPeripheralControl );

	if( diGET_TX_TRANSFER_STRUCT( pxPeripheralControl ) == NULL )
	{
		#if ioconfigUSE_UART_POLLED_TX == 1
		{
			/* No FreeRTOS objects exist to allow transmission without blocking
			the	task, so just send out by polling.  No semaphore or queue is
			used here, so the application must ensure only one task attempts to
			make a polling write at a time. */
			for(i=0;i<xBytes;i++)sciSendByte(pxUART, *((uint8*)pvBuffer+i));
		}
		#endif /* ioconfigUSE_UART_POLLED_TX */
	}

	else
	{
		/* Remember which transfer control structure is being used.
		The Tx interrupt will use this to continue to write data to the
		Tx FIFO/UART until the length member of the structure reaches
		zero. */
		cPeripheralNumber = diGET_PERIPHERAL_NUMBER( pxPeripheralControl );
		pxUartTxTransferControlStructs[ cPeripheralNumber  ] = diGET_TX_TRANSFER_STRUCT( pxPeripheralControl );

		switch( diGET_TX_TRANSFER_TYPE( pxPeripheralControl ) )
		{
			case ioctlUSE_ZERO_COPY_TX :

				#if ioconfigUSE_UART_ZERO_COPY_TX == 1
				{
					/* The implementation of the zero copy write uses a semaphore
					to indicate whether a write is complete (and so the buffer
					being written free again) or not.  The semantics of using a
					zero copy write dictate that a zero copy write can only be
					attempted by a task, once the semaphore has been successfully
					obtained by that task.  This ensure that only one task can
					perform a zero copy write at any one time.  Ensure the semaphore
					is not currently available, if this function has been called
					without it being obtained first then it is an error. */
					configASSERT( xIOUtilsGetZeroCopyWriteMutex( pxPeripheralControl, ioctlOBTAIN_WRITE_MUTEX, 0U ) == pdFALSE );

					Zero_Copy_Tx_State_t * volatile pxZeroCopyState = pxPeripheralControl->pxTxControl->pvTransferState;

					if( xSemaphoreGetMutexHolder( pxZeroCopyState->xWriteAccessMutex ) == xTaskGetCurrentTaskHandle() )
					{
						/* Sends the first to the peripheral. */
						pxUART->TD = *((uint8*)pvBuffer);
						/* Configure the Tx structure to send whatever has not already been	sent to the FIFO. */
						pxZeroCopyState->pucBufferStart = ( uint8_t * ) (pvBuffer);
						pxZeroCopyState->pucBufferStart++;
						pxZeroCopyState->usBufferLength = ( uint16_t ) (xBytes);
						pxZeroCopyState->usBufferLength--;
						/* Enable peripheral interrupt.  */
						pxUART->SETINT = SCI_TX_INT;
						xReturn = xBytes;
					}
					else
					{
						xReturn = 0U;
					}
				}
				#else
				configASSERT(0);
				#endif /* ioconfigUSE_UART_ZERO_COPY_TX */
				break;

			case ioctlUSE_ZERO_COPY_TX_DMA :

				#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
				{
					/* The implementation of the zero copy write uses a semaphore
					to indicate whether a write is complete (and so the buffer
					being written free again) or not.  The semantics of using a
					zero copy write dictate that a zero copy write can only be
					attempted by a task, once the semaphore has been successfully
					obtained by that task.  This ensure that only one task can
					perform a zero copy write at any one time.  Ensure the semaphore
					is not currently available, if this function has been called
					without it being obtained first then it is an error. */

					configASSERT( xIOUtilsGetZeroCopyWriteMutex( pxPeripheralControl, ioctlOBTAIN_WRITE_MUTEX, 0U ) == 0 );
					Zero_Copy_Tx_State_t * pxZeroCopyState = pxPeripheralControl->pxTxControl->pvTransferState;
					g_dmaCTRL xDMA_CtrlPacket;

					if( xSemaphoreGetMutexHolder( pxZeroCopyState->xWriteAccessMutex ) == xTaskGetCurrentTaskHandle() )
					{

						/* Configure DMA Control packet for transmission */
						xDMA_CtrlPacket.SADD      = (uint32)pvBuffer;				/* source address				*/

						#ifdef _little_endian__
						xDMA_CtrlPacket.DADD	  = (uint32_t)(&(pxUART->TD)); 		/* destination address			*/
						#else
						xDMA_CtrlPacket.DADD	  = (uint32_t)(&(pxUART->TD))+3; 	/* destination address			*/
						#endif
						xDMA_CtrlPacket.CHCTRL    = 0;                 				/* channel control 				*/

						if(xBytes < maxUART_DMA_BlockSize)
						{
							xDMA_CtrlPacket.FRCNT = xBytes;           				/* frame count 					*/
							pxZeroCopyState->usBufferLength = 0;
						}
						else
							{
							xDMA_CtrlPacket.FRCNT = maxUART_DMA_BlockSize;      	/* frame count 					*/
							pxZeroCopyState->usBufferLength = xBytes - maxUART_DMA_BlockSize;
							}

						xDMA_CtrlPacket.ELCNT     = 1;                 				/* element count 				*/
						xDMA_CtrlPacket.ELDOFFSET = 0;                 				/* element destination offset 	*/
						xDMA_CtrlPacket.ELSOFFSET = 0;                 				/* element source offset 		*/
						xDMA_CtrlPacket.FRDOFFSET = 0;                 				/* frame destination offset 	*/
						xDMA_CtrlPacket.FRSOFFSET = 0;                 				/* frame source offset 			*/
						xDMA_CtrlPacket.PORTASGN  = 4;                 				/* port b 						*/
					    xDMA_CtrlPacket.RDSIZE    = ACCESS_8_BIT;     				/* read size 					*/
						xDMA_CtrlPacket.WRSIZE    = ACCESS_8_BIT;     				/* write size 					*/
						xDMA_CtrlPacket.TTYPE     = FRAME_TRANSFER ;   				/* transfer type 				*/
						xDMA_CtrlPacket.ADDMODERD = ADDR_INC1;         				/* address mode read 			*/
						xDMA_CtrlPacket.ADDMODEWR = ADDR_FIXED;        				/* address mode write 			*/
					    xDMA_CtrlPacket.AUTOINIT  = AUTOINIT_OFF;      				/* autoinit						*/

						/* - setting dma control packets for transmit */
						dmaSetCtrlPacket((dmaChannel_t )xUartTX_DMA_Channels[cPeripheralNumber],xDMA_CtrlPacket);

						/* Wait for SCI device is ready for TX */
						while ((pxUART->FLR & SCI_TX_INT) == 0U);

						/* SCI_ENABLE_TX_DMA_MODE */
						pxUART->SETINT=(1U<<16U);

						/* Start DMA transfer */
						dmaSetChEnable((dmaChannel_t)xUartTX_DMA_Channels[cPeripheralNumber], DMA_SW);
						if(xBytes > 1)dmaSetChEnable((dmaChannel_t)xUartTX_DMA_Channels[cPeripheralNumber], DMA_HW);

						xReturn = xBytes;
					}
					else
					{
						xReturn = 0U;
					}
				}
				#else
				configASSERT(0);
				#endif /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */
				break;

			case ioctlUSE_CHARACTER_QUEUE_TX :

				#if ioconfigUSE_UART_TX_CHAR_QUEUE == 1
				{
					/* The queue allows multiple tasks to attempt to write
					bytes, but ensures only the highest priority of these tasks
					will actually succeed.  If two tasks of equal priority
					attempt to write simultaneously, then the application must
					ensure mutual exclusion, as time slicing could result in
					the strings being sent to the queue being interleaved. */

					portTickType xTicksToWait;
					uint8_t ucChar;
					xTimeOutType xTimeOut;
					Character_Queue_State_t *pxTxState = prvTX_CHAR_QUEUE_STATE( pxPeripheralControl );
					xQueueHandle xQueue;

					xTicksToWait = pxTxState->xBlockTime;
					xQueue = pxTxState->xQueue;
					vTaskSetTimeOutState( &xTimeOut );

					for( ( xReturn ) = 0U; ( xReturn ) < ( xBytes ); ( xReturn )++ )
					{
						if( xQueueSend( xQueue, &( ( ( uint8_t * ) pvBuffer )[ ( xReturn ) ] ), xTicksToWait ) != pdPASS )
						{
							break;
						}
						else
						{
							/* If this task is low priority it is possible that it only
							gets intermittent CPU time, and therefore possible that the
							peripheral interrupt has drained the Tx queue before this point is
							reached.  If this is the case, and the queue contains more
							data, then force the peripheral ISR to be re-entered. */
							if( (pxUART->FLR & SCI_TX_INT) )
							{
								if( xQueueReceive( xQueue, &ucChar, xTicksToWait ) == pdPASS )
								{
									/* Sends the first to the peripheral. */
									pxUART->TD = ucChar;
									pxUART->SETINT = SCI_TX_INT;
								}
							}
						}

						if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )
						{
							/* Time out has expired. */
							break;
						}
					}
				}
				#else
					configASSERT(0);
				#endif /* ioconfigUSE_UART_TX_CHAR_QUEUE */
				break;

			default :

				/* Other methods can be implemented here.  For now set the
				stored transfer structure back to NULL as nothing is being
				sent. */
				configASSERT( xReturn );
				pxUartTxTransferControlStructs[ cPeripheralNumber ] = NULL;

				/* Prevent compiler warnings when the configuration is set such
				that the following parameters are not used. */
				( void ) pvBuffer;
				( void ) xBytes;
				( void ) pxUART;
				break;
		}
	}
	return xReturn;
}
/*-----------------------------------------------------------*/

/**
 * @fn size_t FreeRTOS_UART_read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes )
 * @param pxPeripheral
 * @param pvBuffer
 * @param xBytes
 * @return
 */
size_t FreeRTOS_UART_read( Peripheral_Descriptor_t const pxPeripheral, void * const pvBuffer, const size_t xBytes )
{
	Peripheral_Control_t * const pxPeripheralControl = ( Peripheral_Control_t * ) pxPeripheral;
	sciBASE_t * const pxUART = ( sciBASE_t * ) diGET_PERIPHERAL_BASE_ADDRESS( ( ( Peripheral_Control_t * ) pxPeripheral ) );

	size_t xReturn = 0U;
	size_t xBytesCounter = xBytes;
	uint8_t *pCharBuffer = pvBuffer;


	if( diGET_RX_TRANSFER_STRUCT( pxPeripheralControl ) == NULL )
	{
		#if ioconfigUSE_UART_POLLED_RX == 1
		{
			/* No FreeRTOS objects exist to allow reception without blocking
			the task, so just receive by polling.  No semaphore or queue is
			used here, so the application must ensure only one task attempts
			to make a polling read at a time. */

			while(xBytesCounter)
			{
				if(sciIsRxReady(pxUART))
				{
					(*pCharBuffer++) = sciReceiveByte(pxUART);
					xReturn++;
					xBytesCounter--;
				}
			}
		}
		#endif /* ioconfigUSE_UART_POLLED_RX */
	}
	else
	{
		/* Sanity check the array index. */
		//configASSERT( diGET_PERIPHERAL_NUMBER( pxPeripheralControl ) < ( int8_t ) ( sizeof( xIRQ ) / sizeof( IRQn_Type ) ) );

		switch( diGET_RX_TRANSFER_TYPE( pxPeripheralControl ) )
		{
			case ioctlUSE_CIRCULAR_BUFFER_RX :

				#if ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1
				{
					/* There is nothing to prevent multiple tasks attempting to
					read the circular buffer at any one time.  The implementation
					of the circular buffer uses a semaphore to indicate when new
					data is available, and the semaphore will ensure that only the
					highest priority task that is attempting a read will actually
					receive bytes. */

					ioutilsRECEIVE_CHARS_FROM_CIRCULAR_BUFFER
						(
							pxPeripheralControl,
							sciDisableNotification(pxUART,SCI_RX_INT),			/* Disable peripheral. */
							sciEnableNotification(pxUART,SCI_RX_INT), 			/* Enable peripheral. */
							( ( uint8_t * ) pvBuffer ),							/* Data destination. */
							xBytes,												/* Bytes to read. */
							xReturn												/* Number of bytes read. */
						);

				}
				#else
				configASSERT(0);
				#endif /* ioconfigUSE_UART_CIRCULAR_BUFFER_RX */
				break;


			case ioctlUSE_CHARACTER_QUEUE_RX :

				#if ioconfigUSE_UART_RX_CHAR_QUEUE == 1
				{
					/* The queue allows multiple tasks to attempt to read
					bytes, but ensures only the highest priority of these
					tasks will actually receive bytes.  If two tasks of equal
					priority attempt to read simultaneously, then the
					application must ensure mutual exclusion, as time slicing
					could result in the string being received being partially
					received by each task. */
					xReturn = xIOUtilsReceiveCharsFromRxQueue( pxPeripheralControl, ( uint8_t * ) pvBuffer, xBytes );

				}
				#else
				configASSERT(0);
				#endif /* ioconfigUSE_UART_RX_CHAR_QUEUE */
				break;


			default :

				/* Other methods can be implemented here. */
				configASSERT( xReturn );

				/* Prevent compiler warnings when the configuration is set such
				that the following parameters are not used. */
				( void ) pvBuffer;
				( void ) xBytes;
				( void ) pxUART;
				break;
		}
	}
	return xReturn;
}
/*-----------------------------------------------------------*/

/**
 * @fn portBASE_TYPE FreeRTOS_UART_ioctl( Peripheral_Descriptor_t pxPeripheral, uint32_t ulRequest, void *pvValue )
 * @param pxPeripheral
 * @param ulRequest
 * @param pvValue
 * @return
 */
portBASE_TYPE FreeRTOS_UART_ioctl( Peripheral_Descriptor_t pxPeripheral, uint32_t ulRequest, void *pvValue )
{
	Peripheral_Control_t * const pxPeripheralControl = ( Peripheral_Control_t * ) pxPeripheral;
	sciBASE_t * const pxUART = ( sciBASE_t * ) diGET_PERIPHERAL_BASE_ADDRESS( ( ( Peripheral_Control_t * ) pxPeripheral ) );
	const int8_t cPeripheralNumber = diGET_PERIPHERAL_NUMBER( ( ( Peripheral_Control_t * ) pxPeripheral ) );
	portBASE_TYPE xReturn = pdPASS;
	uint32_t ulValue = ( uint32_t ) pvValue;

	//taskENTER_CRITICAL();
	{
		switch( ulRequest )
		{
			case ioctlUSE_INTERRUPTS :

				if( ulValue == pdFALSE )
				{
					sciDisableNotification(pxUART, SCI_TX_INT);
					sciDisableNotification(pxUART, SCI_RX_INT);
				}
				else
				{
					/* Enable the Rx and Tx interrupt. */
					sciEnableNotification(pxUART, SCI_TX_INT);
					sciEnableNotification(pxUART, SCI_RX_INT);

					/* If the Rx is configured to use interrupts, remember the
					transfer control structure that should be used.  A reference
					to the Tx transfer control structure is taken when a write()
					operation is actually performed. */
					pxUartRxTransferControlStructs[ cPeripheralNumber ] = pxPeripheralControl->pxRxControl;
				}
				break;

			case ioctlSET_SPEED :

				/* Set up the default UART configuration. */
				sciSetBaudrate(pxUART, (int)pvValue);
				break;

			case ioctlSET_INTERRUPT_PRIORITY :

				/* The ISR uses ISR safe FreeRTOS API functions, so the priority
				being set must be lower than (ie numerically larger than)
				configMAX_LIBRARY_INTERRUPT_PRIORITY. */
				configASSERT( ulValue >= configMAX_LIBRARY_INTERRUPT_PRIORITY );
				configASSERT( xFreeRTOSsciSetInterruptPriority( pxUART, (uint8_t)ulValue ) );
				break;

			case ioctlUSE_ZERO_COPY_TX_DMA :

				#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
				configASSERT( xFreeRTOSsciCommand( pxUART, SCI_ENABLE_TX_DMA_MODE ));
				configASSERT( ulValue <= maxNumberOfDMAChannels );

				/* Note: ulValue holds the DMA channel value. */

				/* Enable DMA */
				dmaEnable();

				/* Enable Interrupt after reception of data */
				// TODO: Eltérés a 20x31x és a 4357 eszközök API-ja között
				//dmaEnableInterrupt(ulValue, BTC);
				dmaEnableInterrupt((dmaChannel_t)ulValue, BTC, DMA_INTA);

				if(pxUART == sciREG1)
				{
					/* Assigning DMA xDMAChannel with request line-29  - TX*/
					dmaReqAssign((dmaChannel_t)ulValue,(dmaRequest_t)29);
					xUartTX_DMA_Channels[0]=ulValue;
				}
				else if(pxUART == sciREG2)
				{
					/* Assigning DMA xDMAChannel with request line-21  - TX*/
					dmaReqAssign((dmaChannel_t)ulValue,(dmaRequest_t)21);
					xUartTX_DMA_Channels[1]=ulValue;
				}
				else
				{
					/* Invalid sciREG */
					configASSERT(0);
				}
				break;
				#else
				configASSERT(0);
				#endif /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */

			default :

				xReturn = pdFAIL;
				break;
		}
	}
	//taskEXIT_CRITICAL();

	return xReturn;
}
/*-----------------------------------------------------------*/

/**
 * @fn portBASE_TYPE xFreeRTOSsciInit(sciBASE_t *sci)
 * @brief Switch peripherial API from HALCoGen compatibility mode to FreeRTOS-Plus-IO mode.
 * @param sci - sci module base address
 * @return success
 * @note Needs PRIVILEGED MODE
 */
// TODO megírni processzor függetlenre
#if defined(_CPU_TMS570LS20216_) || defined(_CPU_TMS570LS4357_)
portBASE_TYPE xFreeRTOSsciInit(sciBASE_t *sci)
{
	portBASE_TYPE xReturn=pdTRUE;
	if(sci == sciREG1)
	{
		vimRAM->ISR[14] = &vFreeRTOSsci1Interrupt;
		vimRAM->ISR[28] = &vFreeRTOSsci1Interrupt;
	}
	else if(sci == sciREG2)
	{
		vimRAM->ISR[50] = &vFreeRTOSsci2Interrupt;
		vimRAM->ISR[55] = &vFreeRTOSsci2Interrupt;
	}
	else xReturn=pdFALSE;
	return xReturn;
}
#endif

#ifdef _CPU_TMS570LS3137_
portBASE_TYPE xFreeRTOSsciInit(sciBASE_t *sci)
{
	portBASE_TYPE xReturn=pdTRUE;
	if(sci == sciREG1)		// LIN
	{
		vimRAM->ISR[16] = &vFreeRTOSsci1Interrupt;
		vimRAM->ISR[28] = &vFreeRTOSsci1Interrupt;
	}
	else if(sci == sciREG2)	// SCI
	{
		vimRAM->ISR[65] = &vFreeRTOSsci2Interrupt;
		vimRAM->ISR[75] = &vFreeRTOSsci2Interrupt;
	}
	else xReturn=pdFALSE;
	return xReturn;
}
#endif

/*-----------------------------------------------------------*/

/**
 * @fn portBASE_TYPE xFreeRTOSsciSetInterruptPriority(sciBASE_t *sci, uint8_t priority)
 * @brief Set SCIx interrupt priority.
 * @param[in] sci - sci module base address
 * @param[in] priority - interrupt priority (0-maxNumericalIrqPriorit)
 * @return success
 * @note Needs PRIVILEGED MODE
 */
portBASE_TYPE xFreeRTOSsciSetInterruptPriority(sciBASE_t *sci, uint8_t priority)
{
	portBASE_TYPE xReturn=pdFALSE;
	uint32_t xTemp;
	if(priority <= maxNumericalIrqPriority)
	{
		if(sci == sciREG1)
		{
			/* Set SCI1 high priority (ISR[14]) interrupt priority. */
			xTemp = vimREG->CHANCTRL[3];
			xTemp &= 0xffff00ff;
			xTemp |= (priority << 8);
			vimREG->CHANCTRL[3] = xTemp;

			/* Set SCI1 low priority (ISR[28]) interrupt priority. */
			xTemp = vimREG->CHANCTRL[7];
			xTemp &= 0x00ffffff;
			xTemp |= (priority << 24);
			vimREG->CHANCTRL[7] = xTemp;
			xReturn=pdTRUE;
		}
		else if(sci == sciREG2)
		{
			/* Set SCI2 high priority (ISR[50]) interrupt priority. */
			xTemp = vimREG->CHANCTRL[12];
			xTemp &= 0xffff00ff;
			xTemp |= (priority << 8);
			vimREG->CHANCTRL[12] = xTemp;

			/* Set SCI2 low priority (ISR[55]) interrupt priority. */
			xTemp = vimREG->CHANCTRL[13];
			xTemp &= 0xffffff00;
			xTemp |= (priority );
			vimREG->CHANCTRL[13] = xTemp;
			xReturn=pdTRUE;
		}
	}
	return xReturn;
}
/*-----------------------------------------------------------*/

/**
* @fn void vFreeRTOSsci1Interrupt(void)
* @brief High Level Interrupt for SCI1 in FreeRTOS-Plus-IO compatibility mode
*/
#pragma INTERRUPT(vFreeRTOSsci1Interrupt, IRQ)
void vFreeRTOSsci1Interrupt(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	Transfer_Control_t *pxTransferStruct;
	Zero_Copy_Tx_State_t *pxZeroCopyState;
	uint32_t ulReceived;
	const unsigned portBASE_TYPE uxUARTNumber = 0UL;

	uint32 vec = sciREG1->INTVECT0;
	switch (vec)
	{
	    case 1:					// SCI_WAKE_INT
	    case 3:					// SCI_PE_INT
	    case 6:					// SCI_FE_INT
	    case 7:					// SCI_BREAK_INT
	    case 9:					// SCI_OE_INT
	    	configASSERT(0);	// Nem kezelt megszakítás forrás hibajelzése..
	    //break;
	case 11:					// Receive
		// pxUartRxTransferControlStructs[]-ba el van mentve az SCI1 rx Transfer_Control_t struktúrája.
		pxTransferStruct = pxUartRxTransferControlStructs[uxUARTNumber];
		if( pxTransferStruct != NULL )
		{
			switch(diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT( pxTransferStruct ))
			{
				case ioctlUSE_CHARACTER_QUEUE_RX:
					#if ioconfigUSE_UART_RX_CHAR_QUEUE == 1
					{
						ioutilsRX_CHARS_INTO_QUEUE_FROM_ISR
							(
							pxTransferStruct,
							sciIsRxReady(sciREG1),
							sciREG1->RD,
							ulReceived,
							xHigherPriorityTaskWoken
							);
					}
					#else
					configASSERT(0);
					#endif 	/* ioconfigUSE_UART_RX_CHAR_QUEUE */
				break;
				case ioctlUSE_CIRCULAR_BUFFER_RX:
					#if ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1
					{
						ioutilsRX_CHARS_INTO_CIRCULAR_BUFFER_FROM_ISR
							(
							pxTransferStruct, 		/* The structure that contains the reference to the circular buffer. */
							sciIsRxReady(sciREG1), 	/* While loop condition. */
							sciREG1->RD,			/* Register holding the received character. */
							ulReceived,
							xHigherPriorityTaskWoken
							);
					}
					#else
					configASSERT(0);
					#endif /* ioconfigUSE_UART_CIRCULAR_BUFFER_RX */
				break;
				default :
					/* This must be an error.  Force an assert. */
					configASSERT( xHigherPriorityTaskWoken );
					break;
			}
		}
		break;

	case 12:					// Transmit
		pxTransferStruct = pxUartTxTransferControlStructs[uxUARTNumber];
		if(pxTransferStruct!=NULL)
		{
			switch( diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT( pxTransferStruct ) )
			{
			case ioctlUSE_ZERO_COPY_TX_DMA:
				#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
				{
					pxTransferStruct = pxUartTxTransferControlStructs[uxUARTNumber];
					pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
					xSemaphoreGiveFromISR( pxZeroCopyState->xWriteAccessMutex, &( xHigherPriorityTaskWoken ) );
					sciREG1->CLRINT = SCI_TX_INT;
				}
				#else
				configASSERT(0);
				#endif  /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */

			case ioctlUSE_ZERO_COPY_TX:
					#if ioconfigUSE_UART_ZERO_COPY_TX == 1
					pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
					if(pxZeroCopyState->usBufferLength != 0U)
					{
						sciREG1->TD = pxZeroCopyState->pucBufferStart[0];
						(pxZeroCopyState->pucBufferStart)++;
						pxZeroCopyState->usBufferLength--;
					}
					else
						{
						sciREG1->CLRINT = SCI_TX_INT;
						xSemaphoreGiveFromISR( pxZeroCopyState->xWriteAccessMutex, &( xHigherPriorityTaskWoken ) );
						}
					#else
						configASSERT(0);
					#endif  /* ioconfigUSE_UART_ZERO_COPY_TX */
				break;

				case ioctlUSE_CHARACTER_QUEUE_TX:
					#if ioconfigUSE_UART_TX_CHAR_QUEUE == 1
					{
						Character_Queue_State_t *pxCharQueueState = ( Character_Queue_State_t * ) ( ( pxTransferStruct )->pvTransferState );
						if(uxQueueMessagesWaitingFromISR( pxCharQueueState->xQueue ))
						{
							ioutilsTX_CHARS_FROM_QUEUE_FROM_ISR
								(
								pxTransferStruct,
								( sciREG1->FLR & SCI_TX_INT ),
								( sciREG1->TD = ucChar ),
								xHigherPriorityTaskWoken
								);
						}
						else
						{
							sciREG1->CLRINT = SCI_TX_INT;
						}

					}
					#else
					configASSERT(0);
					#endif /* ioconfigUSE_UART_TX_CHAR_QUEUE */
				break;
				default :
					/* This must be an error.  Force an assert. */
					configASSERT( xHigherPriorityTaskWoken );
					break;
			}
		}
		break;

	default:	/* phantom interrupt, clear flags and return */
		sciREG1->FLR = ~sciREG1->SETINTLVL & 0x07000303U;
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

/** @fn void vFreeRTOSsci2Interrupt(void)
*   @brief High Level Interrupt for SCI2 in FreeRTOS-Plus-IO compatibility mode
*/
#pragma INTERRUPT(vFreeRTOSsci2Interrupt, IRQ)
void vFreeRTOSsci2Interrupt(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	Transfer_Control_t *pxTransferStruct;
	Zero_Copy_Tx_State_t *pxZeroCopyState;
	uint32_t ulReceived;
	const unsigned portBASE_TYPE uxUARTNumber = 1UL;

	uint32 vec = sciREG2->INTVECT0;
	switch (vec)
	{
	    case 1:					// SCI_WAKE_INT
	    case 3:					// SCI_PE_INT
	    case 6:					// SCI_FE_INT
	    case 7:					// SCI_BREAK_INT
	    case 9:					// SCI_OE_INT
	    	configASSERT(0);	// Nem kezelt megszakítás forrás hibajelzése..
	    //break;
	case 11:					// Receive
		// pxUartRxTransferControlStructs[]-ba el van mentve az SCI1 rx Transfer_Control_t struktúrája.
		pxTransferStruct = pxUartRxTransferControlStructs[uxUARTNumber];
		if( pxTransferStruct != NULL )
		{
			switch(diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT( pxTransferStruct ))
			{
				case ioctlUSE_CHARACTER_QUEUE_RX:
					#if ioconfigUSE_UART_RX_CHAR_QUEUE == 1
					{
						ioutilsRX_CHARS_INTO_QUEUE_FROM_ISR
							(
							pxTransferStruct,
							sciIsRxReady(sciREG2),
							sciREG2->RD,
							ulReceived,
							xHigherPriorityTaskWoken
							);
					}
					#else
					configASSERT(0);
					#endif 	/* ioconfigUSE_UART_RX_CHAR_QUEUE */
				break;
				case ioctlUSE_CIRCULAR_BUFFER_RX:
					#if ioconfigUSE_UART_CIRCULAR_BUFFER_RX == 1
					{
						ioutilsRX_CHARS_INTO_CIRCULAR_BUFFER_FROM_ISR
							(
							pxTransferStruct, 		/* The structure that contains the reference to the circular buffer. */
							sciIsRxReady(sciREG2), 	/* While loop condition. */
							sciREG2->RD,			/* Register holding the received character. */
							ulReceived,
							xHigherPriorityTaskWoken
							);
					}
					#else
					configASSERT(0);
					#endif /* ioconfigUSE_UART_CIRCULAR_BUFFER_RX */
				break;
				default :
					/* This must be an error.  Force an assert. */
					configASSERT( xHigherPriorityTaskWoken );
					break;
			}
		}
		break;

	case 12:					// Transmit
		pxTransferStruct = pxUartTxTransferControlStructs[uxUARTNumber];
		if(pxTransferStruct!=NULL)
		{
			switch( diGET_TRANSFER_TYPE_FROM_CONTROL_STRUCT( pxTransferStruct ) )
			{
			case ioctlUSE_ZERO_COPY_TX_DMA:
				#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
				{
					pxTransferStruct = pxUartTxTransferControlStructs[uxUARTNumber];
					pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
					xSemaphoreGiveFromISR( pxZeroCopyState->xWriteAccessMutex, &( xHigherPriorityTaskWoken ) );
					sciREG2->CLRINT = SCI_TX_INT;
				}
				#else
				configASSERT(0);
				#endif  /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */
			break;

				case ioctlUSE_ZERO_COPY_TX:
					#if ioconfigUSE_UART_ZERO_COPY_TX == 1
					pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
					if(pxZeroCopyState->usBufferLength != 0U)
					{
						sciREG2->TD = pxZeroCopyState->pucBufferStart[0];
						(pxZeroCopyState->pucBufferStart)++;
						pxZeroCopyState->usBufferLength--;
					}
					else
						{
						sciREG2->CLRINT = SCI_TX_INT;
						xSemaphoreGiveFromISR( pxZeroCopyState->xWriteAccessMutex, &( xHigherPriorityTaskWoken ) );
						}
					#else
					configASSERT(0);
					#endif  /* ioconfigUSE_UART_ZERO_COPY_TX */
				break;

				case ioctlUSE_CHARACTER_QUEUE_TX:
					#if ioconfigUSE_UART_TX_CHAR_QUEUE == 1
					{
						Character_Queue_State_t *pxCharQueueState = ( Character_Queue_State_t * ) ( ( pxTransferStruct )->pvTransferState );
						if(uxQueueMessagesWaitingFromISR( pxCharQueueState->xQueue ))
						{
							ioutilsTX_CHARS_FROM_QUEUE_FROM_ISR
								(
								pxTransferStruct,
								( sciREG2->FLR & SCI_TX_INT ),
								( sciREG2->TD = ucChar ),
								xHigherPriorityTaskWoken
								);
						}
						else
						{
							sciREG2->CLRINT = SCI_TX_INT;
						}
					}
					#else
					configASSERT(0);
					#endif /* ioconfigUSE_UART_TX_CHAR_QUEUE */
				break;
				default :
					/* This must be an error.  Force an assert. */
					configASSERT( xHigherPriorityTaskWoken );
					break;
			}
		}
		break;

	default:	/* phantom interrupt, clear flags and return */
		sciREG2->FLR = ~sciREG2->SETINTLVL & 0x07000303U;
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

/**
 * @fn portBASE_TYPE xFreeRTOSsciCommand(sciBASE_t *sci, sciCommand_t command )
 * @param[in] sci - sci module base address
 * @param[in] command
 * @return success
 */
portBASE_TYPE xFreeRTOSsciCommand(sciBASE_t *sci, sciCommand_t command )
{
	portBASE_TYPE xReturn=pdTRUE;

	if(sci == sciREG1 || sci == sciREG2)
	{
		switch(command)
		{
			case SCI_ENABLE_TX:
				sci->GCR1|=(1U<<25U);
				break;
			case SCI_DISABLE_TX:
				sci->GCR1&=0xffffffff-(1U<<25U);
				break;
			case SCI_ENABLE_MULTI_BUFFER_MODE:
				sci->GCR1|=(1U<<10U);
				break;
			case SCI_DISABLE_MULTI_BUFFER_MODE:
				sci->GCR1&=0xffffffff-(1U<<10U);
				break;
			case SCI_ENABLE_TX_DMA_MODE:
				sci->SETINT=(1U<<16U);
				break;
			case SCI_DISABLE_TX_DMA_MODE:
				sci->CLRINT=(1U<<16U);
				break;
			case SCI_ENABLE_RX_DMA_MODE:
				sci->SETINT=(1U<<17U);
				break;
			case SCI_DISABLE_RX_DMA_MODE:
				sci->CLRINT=(1U<<17U);
				break;
				// ide még jöhetnek a további parancsok...
			default:
				xReturn=pdFALSE;
		}
	}
	return xReturn;
}
/*-----------------------------------------------------------*/
