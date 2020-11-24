#ifndef __TMS570LS20X31X_UART_H__
#define __TMS570LS20X31X_UART_H__

#include <HL_reg_sci.h>
#include <os_portmacro.h>

#include "HL_sys_vim.h"

typedef volatile struct vimRam
{
    t_isrFuncPTR ISR[VIM_CHANNELS];
} vimRAM_t;

#define vimRAM ((vimRAM_t *)0xFFF82000U)

typedef enum
{
    SCI_ENABLE_TX	= 1,
    SCI_DISABLE_TX 	= 2,
    SCI_ENABLE_MULTI_BUFFER_MODE = 3,
    SCI_DISABLE_MULTI_BUFFER_MODE = 4,
    SCI_ENABLE_TX_DMA_MODE = 5,
    SCI_DISABLE_TX_DMA_MODE = 6,
    SCI_ENABLE_RX_DMA_MODE = 7,
    SCI_DISABLE_RX_DMA_MODE = 8
} sciCommand_t;



portBASE_TYPE xFreeRTOSsciCommand(sciBASE_t *sci, sciCommand_t order );
portBASE_TYPE xFreeRTOSsciInit(sciBASE_t *sci);
portBASE_TYPE xFreeRTOSsciSetInterruptPriority(sciBASE_t *sci, uint8_t priority);
void vFreeRTOSsci4Interrupt(void);
void vFreeRTOSsci3Interrupt(void);
void dmaConfigCtrlTxPacket(uint32 sadd, uint32 dadd, uint32 dsize);
#endif
