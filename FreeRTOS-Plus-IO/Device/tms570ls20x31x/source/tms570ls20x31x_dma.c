/* FreeRTOS-Plus-IO - DMA TMS570LS20X31X V0.0.1  (C) 2014 Lovas Szilárd
 * Note: Group "B" DMA interrupt handlers are not implemented.
 * Email: lovas.szilard@gmail.com
 */

/* FreeRTOS headers */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"

/* FreeRTOS-PLUS-IO library includes. */
#include "FreeRTOS_IO.h"
#include "IOUtils_Common.h"

/* FreeRTOS-PLUS-IO BSP (Board Support Package) */
//#include "olimex_tms570can-base-board.h"
#include "tms570ls20x31x_uart.h"
#include "tms570ls20x31x_dma.h"

/* HALCoGen generated headers */
#include "HL_reg_dma.h"
#include "HL_sci.h"

/* Stores the transfer control structures that are currently in use by the
supported UART ports. */
extern Transfer_Control_t *pxUartTxTransferControlStructs[ boardNUM_UARTS ];
extern Transfer_Control_t *pxUartRxTransferControlStructs[ boardNUM_UARTS ];

extern uint8_t xUartTX_DMA_Channels[ boardNUM_UARTS ];

/** @fn void vFreeRTOS_DMA_FTCA_Interrupt(void)
 *  @brief Frame transfer complete (FTC) interrupt.
 *  Frame transfer complete (FTC) interrupt: an interrupt is issued after the last element
 *  of a frame has been transferred.
 *  Routed to VIM channel 33.
 */
#pragma INTERRUPT(vFreeRTOS_DMA_FTCA_Interrupt, IRQ)
void vFreeRTOS_DMA_FTCA_Interrupt(void)
{

}

/** @fn void vFreeRTOS_DMA_LFSA_Interrupt(void)
 *  @brief Last frame transfer started (LFS) interrupt.
 *  Last frame transfer started (LFS) interrupt: an interrupt is issued before the first element
 *  of the last frame of a block transfer has started.
 *  Routed to VIM channel 34.
 */
#pragma INTERRUPT(vFreeRTOS_DMA_LFSA_Interrupt, IRQ)
void vFreeRTOS_DMA_LFSA_Interrupt(void)
{

}

/** @fn void vFreeRTOS_DMA_HBCA_Interrupt(void)
 *  @brief First half of block complete (HBC) interrupt.
 *  First half of block complete (HBC) interrupt: an interrupt is issued if more than half
 *  of the block is transferred.
 *  Routed to VIM channel 39.
 */
#pragma INTERRUPT(vFreeRTOS_DMA_HBCA_Interrupt, IRQ)
void vFreeRTOS_DMA_HBCA_Interrupt(void)
{

}

/** @fn void vFreeRTOS_DMA_BTCA_Interrupt(void)
 *  @brief Block transfer complete (BTC) interrupt.
 *  Block transfer complete (BTC) interrupt: an interrupt is issued after the last element
 *  of the last frame has been transferred.
 *  Routed to VIM channel 40.
 */
#pragma INTERRUPT(vFreeRTOS_DMA_BTCA_Interrupt, IRQ)
void vFreeRTOS_DMA_BTCA_Interrupt(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	Transfer_Control_t *pxTransferStruct;
	Zero_Copy_Tx_State_t *pxZeroCopyState;

	uint32_t interruptSource = dmaREG->BTCAOFFSET;

	if(interruptSource == xUartTX_DMA_Channels[0U]+1)
	{
		#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
		pxTransferStruct = pxUartTxTransferControlStructs[0U];
		pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
		if(pxZeroCopyState->usBufferLength != 0U)
		{
			//sciREG2->TD = pxZeroCopyState->pucBufferStart[0];
			(pxZeroCopyState->pucBufferStart)++;
			pxZeroCopyState->usBufferLength--;
		}
		else
			{
			sciREG1->CLRINT=(1U<<16U);	/* SCI_DISABLE_TX_DMA_MODE */
			sciREG1->SETINT=(1U<<8U);	/* SCI_ENABLE_TX_INT_MODE */
			}
		#else
		configASSERT(0);
		#endif  /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */
	}
	else if(interruptSource == xUartTX_DMA_Channels[1U]+1)
	{
		#if ioconfigUSE_UART_ZERO_COPY_TX_DMA == 1
		pxTransferStruct = pxUartTxTransferControlStructs[1U];
		pxZeroCopyState = ( Zero_Copy_Tx_State_t * ) ( pxTransferStruct )->pvTransferState;
		if(pxZeroCopyState->usBufferLength != 0U)
		{
//			if(pxZeroCopyState->usBufferLength <= maxUART_DMA_BlockSize)
//			{
//				pxZeroCopyState->usBufferLength = 0;
//			}
//			else
//			{
//				pxZeroCopyState->usBufferLength;
//			}
//			(pxZeroCopyState->pucBufferStart)++;
//
//			//sciREG2->TD = pxZeroCopyState->pucBufferStart[0];

		}
		else
			{
			sciREG2->CLRINT=(1U<<16U);	/* SCI_DISABLE_TX_DMA_MODE */
			sciREG2->SETINT=(1U<<8U);	/* SCI_ENABLE_TX_INT_MODE */
			}
		#else
		configASSERT(0);
		#endif  /* ioconfigUSE_UART_ZERO_COPY_TX_DMA */
	}
	else
	{
		/* Not handled interrupt source */
		configASSERT(0);
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

/** @fn void vFreeRTOS_DMA_BERA_Interrupt(void)
 *  @brief Bus error (BER) interrupt.
 *  Bus error (BER) interrupt: an interrupt is issued when DMA detects an error on the bus.
 *  The BER interrupt is connected to the ESM module.
 *  Routed to VIM channel 41.
 */
#pragma INTERRUPT(vFreeRTOS_DMA_BERA_Interrupt, IRQ)
void vFreeRTOS_DMA_BERA_Interrupt(void)
{

}

