#ifndef __TMS570LS20X31X_DMA_H__
#define __TMS570LS20X31X_DMA_H__

/**
 * Maximum number of bytes can be transfered in one DMA block.
 * 2^13 frame * 1 element/frame * 1 byte/element = 8192 byte
 */
#define maxUART_DMA_BlockSize 8192

void vFreeRTOS_DMA_FTCA_Interrupt(void);
void vFreeRTOS_DMA_LFSA_Interrupt(void);
void vFreeRTOS_DMA_HBCA_Interrupt(void);
void vFreeRTOS_DMA_BTCA_Interrupt(void);
void vFreeRTOS_DMA_BERA_Interrupt(void);

#endif
