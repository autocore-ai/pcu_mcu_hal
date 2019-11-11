/** ***************************************************************************************************
 * @file NetworkInterface.c
 * @author Lovas Szilard <lovas.szilard@gmail.com>
 * @date 2017.04.18
 * @version 0.4
 * @copyright Lovas Szilard
 * GNU GENERAL PUBLIC LICENSE Version 2, June 1991
 *
 * This code is made as a part of a research, that has been supported by the 鍑ghly industrialized region on the west part of
 * Hungary with limited R&D capacity: Research and development programs related to
 * strengthening the strategic futureoriented industries manufacturing technologies and
 * products of regional competences carried out in comprehensive collaboration锟� program of
 * the National Research, Development and Innovation Fund (NKFI), Hungary, Grant. No. VKSZ_12-1-2013-0038.
 *
 *
 * Homepage: http://jkk.sze.hu/fooldal
 *
 * @brief FreeRTOS-Plus-TCP NetworkInterface.c port for Texas Instruments TMS570LC4357 microcontroller.
 *
 * @details
 * Dependencies: Dp83640IDGet
 * -------------
 * - FreeRTOS Labs 160112
 * - Modified HALCoGen 04.04.00
 *
 * Changelog:
 * ----------
 * 2016.02.22
 * Initial release
 * 2016.04.15
 * Using vTaskNotifyGiveFromISR/ulTaskNotifyTake for signaling  EMAC RX interrupt
 * 2016.04.25
 * Doxygen style documentation added.
 * 2016.06.19
 * The new TX method uses IRQ, and blocking (it can do about 95 Mbit/sec iperf).
 * 2017.04.18
 * - Bugfix in uint32 xFreeRTOSEMACHWInit(uint8_t macaddr[6U]) (multiple calling of prvEmacDMAInit(hdkif) in the case of cable not connected)
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_semphr.h"

/* HALCoGen generated header files */
#include "HL_emac.h"
//#include "HL_mdio.h"
//#include "HL_phy_dp83640.h"
#include "HL_sys_vim.h"
#include "HL_gio.h"
#include "HL_reg_het.h"

/* FreeRTOS+TCP includes. */
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "NetworkBufferManagement.h"

/* HALCoGen generated source. */
//#include "HL_emac.c"

#define EMAC_INT_CORE0_RX_THRESH        (0x0U)      // Acknowledge C0RXTHRESH Interrupt
#define EMAC_INT_CORE0_MISC             (0x3U)      // Acknowledge C0MISC Interrupt (STATPEND, HOSTPEND, MDIO LINKINT0, MDIO USERINT0)
#define EMAC_INT_CORE1_RX_THRESH        (0x4U)      // Acknowledge C1RXTHRESH Interrupt
#define EMAC_INT_CORE1_MISC             (0x7U)      // Acknowledge C1MISC Interrupt (STATPEND, HOSTPEND, MDIO LINKINT0, MDIO USERINT0)
#define EMAC_INT_CORE2_RX_THRESH        (0x8U)      // Acknowledge C2RXTHRESH Interrupt
#define EMAC_INT_CORE2_MISC             (0xbU)      // Acknowledge C2MISC Interrupt (STATPEND, HOSTPEND, MDIO LINKINT0, MDIO USERINT0)

/* Missing defines in HL_hw_emac_ctrl.h.. */
#define EMAC_CTRL_C0MISEN_USERINT0EN    (0x00000001U)
#define EMAC_CTRL_C0MISEN_USERINT0EN_SHIFT (0x00000000U)
#define EMAC_CTRL_C0MISEN_LINKINT0EN    (0x00000002U)
#define EMAC_CTRL_C0MISEN_LINKINT0EN_SHIFT (0x000000001)
#define EMAC_CTRL_C0MISEN_HOSTPENDEN    (0x00000004U)
#define EMAC_CTRL_C0MISEN_HOSTPENDEN_SHIFT (0x000000002)
#define EMAC_CTRL_C0MISEN_STATPENDEN    (0x00000008U)
#define EMAC_CTRL_C0MISEN_STATPENDEN_SHIFT (0x000000003)

/* RXINTSTATRAW regiszter threshold pending bitek */
#define RXnTHRESHPEND_BIT(n)            (1 << (8 + n))

/* EMAC related VIM channels */
#define C0_MISC_PULSE                   76U
#define C0_TX_PULSE                     77U
#define C0_THRSH_PULSE                  78U
#define C0_RX_PULSE                     79U

/* Maximum number of retries for reading PHY ID */
#define PHY_INIT_ID_READ_MAX_RETRIES    0xffff

/* Number of TX and RX DMA buffers */
#define EMAC_TXDMA_PBUF_START_ADDRESS   (EMAC_CTRL_RAM_BASE)
//#define EMAC_TXDMA_PBUF_ALLOC             ((SIZE_EMAC_CTRL_RAM / 2) / sizeof(emac_tx_bd_t))
#define EMAC_TXDMA_PBUF_ALLOC           (3)
#define EMAC_RXDMA_PBUF_START_ADDRESS   (EMAC_CTRL_RAM_BASE + (SIZE_EMAC_CTRL_RAM / 2))
#define EMAC_RXDMA_PBUF_ALLOC           (MAX_RX_PBUF_ALLOC)             /* HALCoGen GUI 闁瀟闁� */

/* EMAC descriptor flags TX+RX */
/* EMAC descriptor flag-ek TX+RX */
#define EMAC_DSC_FLAG_SOP               0x80000000u
#define EMAC_DSC_FLAG_EOP               0x40000000u
#define EMAC_DSC_FLAG_OWNER             0x20000000u
#define EMAC_DSC_FLAG_EOQ               0x10000000u
#define EMAC_DSC_FLAG_TDOWNCMPLT        0x08000000u
#define EMAC_DSC_FLAG_PASSCRC           0x04000000u
/* EMAC descriptor flags only RX */
/* EMAC descriptor flag-ek csak RX */
#define EMAC_DSC_FLAG_JABBER            0x02000000u
#define EMAC_DSC_FLAG_OVERSIZE          0x01000000u
#define EMAC_DSC_FLAG_FRAGMENT          0x00800000u
#define EMAC_DSC_FLAG_UNDERSIZED        0x00400000u
#define EMAC_DSC_FLAG_CONTROL           0x00200000u
#define EMAC_DSC_FLAG_OVERRUN           0x00100000u
#define EMAC_DSC_FLAG_CODEERROR         0x00080000u
#define EMAC_DSC_FLAG_ALIGNERROR        0x00040000u
#define EMAC_DSC_FLAG_CRCERROR          0x00020000u
#define EMAC_DSC_FLAG_NOMATCH           0x00010000u

/* Byte swap macro */
#define BYTE_SWAP(x)    __rev(x)
/* Minimum ethernet frame size without Frame Check Sequence */
#define MIN_ETHERNET_PACKET_SIZE        (60)

#define _CPU_TMS570LS4357_

void vFreeRTOSEMACMiscInterrupt(void);
void vFreeRTOSEMACTxInterrupt(void);
void vFreeRTOSEMACRxThrshInterrupt(void);
void vFreeRTOSEMACRxInterrupt(void);
uint32 xFreeRTOSEMACHWInit(uint8_t macaddr[6U]);
static void prvEmacRxTask(void *pvParameters);
static void prvEmacDMAInit(hdkif_t *hdkif);
static void prvDisableEMACInterrupts(void);
static void prvEnableEMACInterrupts(void);

//static BaseType_t xEMACDriverLoggingLevel = 0;

static xTaskHandle prvEmacRxTaskHandle = NULL;
extern TaskHandle_t xIPTaskHandle;
SemaphoreHandle_t xEMACTxEventSemaphore = NULL;

extern BaseType_t xEMACRxEventSemaphoreFulls;
extern void _dcacheCleanRange_(unsigned int startAddress, unsigned int endAddress);
extern void _dcacheInvalidateRange_(unsigned int startAddress, unsigned int endAddress);


/* The MAC address defined in HL_sys_main.c */
extern uint8 emacAddress[6U];
extern hdkif_t hdkif_data[];

/* If ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES is set to 1, then the Ethernet
driver will filter incoming packets and only pass the stack those packets it
considers need processing. */
#if(ipconfigETHERNET_DRIVER_FILTERS_FRAME_TYPES == 0)
    #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer) eProcessBuffer
#else
    #define ipCONSIDER_FRAME_FOR_PROCESSING(pucEthernetBuffer) eConsiderFrameForProcessing((pucEthernetBuffer))
#endif


/** ***************************************************************************************************
 * @fn      static void prvDisableEMACInterrupts(void)
 * @brief   Disable EMAC module interrupts in VIM.
 */
static void prvDisableEMACInterrupts(void)
{
    vimREG->REQMASKCLR2 = (uint32)1U << (C0_MISC_PULSE-64U) | (uint32)1U << (C0_TX_PULSE-64U) | (uint32)1U << (C0_THRSH_PULSE-64U) | (uint32)1U << (C0_RX_PULSE-64U);
}

/** ***************************************************************************************************
 * @fn      static void prvEnableEMACInterrupts(void)
 * @brief   Enable EMAC module interrupts in VIM.
 */
static void prvEnableEMACInterrupts(void)
{
//  vimREG->REQMASKSET2 = (uint32)1U << (C0_MISC_PULSE-64U) | (uint32)1U << (C0_TX_PULSE-64U) | (uint32)1U << (C0_THRSH_PULSE-64U) | (uint32)1U << (C0_RX_PULSE-64U);
    vimREG->REQMASKSET2 = (uint32)1U << (C0_TX_PULSE-64U)  | (uint32)1U << (C0_RX_PULSE-64U);
}

/** ***************************************************************************************************
 * @fn      BaseType_t xNetworkInterfaceInitialise(void)
 * @brief   High level function for initializing EMAC module for sending and receiving ethernet frames.
 *          - Redirects ISR vectors
 *          - Calls the low level EMAC HW init function.
 *          - Creates the necessary task/semaphore(s)
 * @return  pdFAIL Error
 *          pdPASS Success
 */
BaseType_t xNetworkInterfaceInitialise(void)
{
    BaseType_t xReturn = pdFAIL;
    hdkif_t *hdkif = &hdkif_data[0U];

    /* Disable all EMAC interrupts in VIM. */
    prvDisableEMACInterrupts();

    HWREG(EMAC_0_BASE + EMAC_RXCONTROL) = EMAC_RXCONTROL_RXDIS;
    HWREG(EMAC_0_BASE + EMAC_TXCONTROL) = EMAC_TXCONTROL_TXDIS;

    /* Redirect interrupt vectors to the */
    vimChannelMap(C0_TX_PULSE, C0_TX_PULSE, &vFreeRTOSEMACTxInterrupt);
    vimChannelMap(C0_RX_PULSE, C0_RX_PULSE, &vFreeRTOSEMACRxInterrupt);

    if(xFreeRTOSEMACHWInit(emacAddress) != EMAC_ERR_OK)
        xReturn = pdFAIL;
    else
    {
        if(xEMACTxEventSemaphore == NULL)
        {
            xEMACTxEventSemaphore = xSemaphoreCreateBinary();
            configASSERT(xEMACTxEventSemaphore);
        }
        if(prvEmacRxTaskHandle == NULL)
        {
            xTaskCreate(prvEmacRxTask, "EmacRx", ipconfigETHERNET_DRIVER_RX_TASK_STACK_SIZE_WORDS, NULL, ipconfigETHERNET_DRIVER_RX_TASK_PRIORITY, &prvEmacRxTaskHandle);
            configASSERT(prvEmacRxTaskHandle);
        }

        if(prvEmacRxTaskHandle != NULL)
        {
            HWREG(hdkif->emac_base + EMAC_TXINTMASKSET) |= ((uint32)1U << EMAC_CHANNELNUMBER);
            HWREG(hdkif->emac_ctrl_base + EMAC_CTRL_CnTXEN(EMAC_CHANNELNUMBER)) |= ((uint32)1U << EMAC_CHANNELNUMBER);
            HWREG(hdkif->emac_base + EMAC_RXINTMASKSET) |= ((uint32)1U << EMAC_CHANNELNUMBER);
            HWREG(hdkif->emac_ctrl_base + EMAC_CTRL_CnRXEN(EMAC_CHANNELNUMBER)) |= ((uint32)1U << EMAC_CHANNELNUMBER);

            HWREG(hdkif->emac_base + EMAC_RXCONTROL) = EMAC_RXCONTROL_RXEN;
            HWREG(hdkif->emac_base + EMAC_TXCONTROL) = EMAC_TXCONTROL_TXEN;

            prvEnableEMACInterrupts();

            HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER)) = EMAC_RXDMA_PBUF_START_ADDRESS;
            xReturn = pdPASS;
        }
    }

    return xReturn;
}

/** ***************************************************************************************************
 * @fn      BaseType_t xNetworkInterfaceOutput(xNetworkBufferDescriptor_t * const pxDescriptor, BaseType_t xReleaseAfterSend)
 * @brief   Send data over ethernet (EMAC) interface.
 * @param   pxDescriptor pointer to the buffer descriptor
 * @param   xReleaseAfterSend Release the descriptor after send (pdPASS)
 * @return  pdFAIL Error
 *          pdPASS Success
 */
BaseType_t xNetworkInterfaceOutput(xNetworkBufferDescriptor_t * const pxDescriptor, BaseType_t xReleaseAfterSend)
{
    hdkif_t *hdkif = &hdkif_data[0U];
    uint32 xFlagsPktlen;
    uint16 xTotalLength;
    static emac_tx_bd_t * pxTransmitBufferDescriptor  = (emac_tx_bd_t *)EMAC_TXDMA_PBUF_START_ADDRESS;
    static emac_tx_bd_t * pxLastQueuedBufferDescriptor  = (emac_tx_bd_t *)EMAC_TXDMA_PBUF_START_ADDRESS;

    /* Is the previous transfer done yet? */
    while(EMAC_DSC_FLAG_OWNER == (BYTE_SWAP(pxTransmitBufferDescriptor->flags_pktlen) & EMAC_DSC_FLAG_OWNER))
    {
        if(xSemaphoreTake(xEMACTxEventSemaphore, ipconfigETHERNET_DRIVER_TX_BLOCK_TIME) == pdFAIL)
        {
            iptraceWAITING_FOR_TX_DMA_DESCRIPTOR();
            return(pdFAIL);
        }
    }

    /* We are going to send the non zero size packets from non zero address only. */
    if(pxDescriptor->xDataLength != 0 && pxDescriptor->pucEthernetBuffer != NULL)
    {
        memcpy((void *)BYTE_SWAP(pxTransmitBufferDescriptor->bufptr), (void *)pxDescriptor->pucEthernetBuffer, pxDescriptor->xDataLength);

        /* If packet size is less than the minimum, it has to be padded */
        while(pxDescriptor->xDataLength < MIN_ETHERNET_PACKET_SIZE)
        {
            pxDescriptor->xDataLength++;
            *(uint8_t *)(pxDescriptor->pucEthernetBuffer + pxDescriptor->xDataLength) = 0x00;
        }
        _dcacheCleanRange_((uint32)BYTE_SWAP(pxTransmitBufferDescriptor->bufptr),(uint32)BYTE_SWAP(pxTransmitBufferDescriptor->bufptr) + MAX_TRANSFER_UNIT);

        /* Creating new BD. */
        pxTransmitBufferDescriptor->bufoff_len = BYTE_SWAP(pxDescriptor->xDataLength);
        xTotalLength = pxDescriptor->xDataLength;
        xFlagsPktlen = ((uint32)(xTotalLength) | (EMAC_DSC_FLAG_SOP | EMAC_DSC_FLAG_EOP | EMAC_DSC_FLAG_OWNER));
        pxTransmitBufferDescriptor->flags_pktlen = BYTE_SWAP(xFlagsPktlen);
        pxTransmitBufferDescriptor->next = NULL;

        prvDisableEMACInterrupts();         /* Start of the critcal section. */
        if(HWREG(hdkif->emac_base + EMAC_TXHDP((uint32)EMAC_CHANNELNUMBER)) == NULL)
        {
            /* Start transmission by writing EMAC Tx Hdr DescPtr, if EMAC is not running... */
            HWREG(hdkif->emac_base + EMAC_TXHDP((uint32)EMAC_CHANNELNUMBER)) = (uint32)(pxTransmitBufferDescriptor);
            pxLastQueuedBufferDescriptor = pxTransmitBufferDescriptor;
        }
        else
        {
            /* ... or append the new BD to the end of the list. */
            pxLastQueuedBufferDescriptor->next = (emac_tx_bd_t *)BYTE_SWAP((uint32_t)pxTransmitBufferDescriptor);
            pxLastQueuedBufferDescriptor = pxTransmitBufferDescriptor;
        }
        prvEnableEMACInterrupts();
        /* End of the critical section. */

        if(pxTransmitBufferDescriptor < (emac_tx_bd_t *)(EMAC_TXDMA_PBUF_START_ADDRESS + EMAC_TXDMA_PBUF_ALLOC))
        {
            pxTransmitBufferDescriptor++;
        }
        else
        {
            pxTransmitBufferDescriptor = (emac_tx_bd_t *)EMAC_TXDMA_PBUF_START_ADDRESS;
        }

        /* Call the standard trace macro to log the send event. */
        iptraceNETWORK_INTERFACE_TRANSMIT();
    }
    else
    {
        /* Try to release the failed network BD */
        xReleaseAfterSend = pdTRUE;
    }

#if(ipconfigZERO_COPY_TX_DRIVER == 0)
    if(xReleaseAfterSend != pdFALSE)
    {
        vReleaseNetworkBufferAndDescriptor(pxDescriptor);
    }
#else
#error ipconfigZERO_COPY_TX_DRIVER not available yet
#endif

    return pdTRUE;
}

/** ***************************************************************************************************
* @fn void vFreeRTOSEMACTxInterrupt(void)
* @brief TX Interrupt for EMAC in FreeRTOS-Plus-TCP compatibility mode
*/
#pragma INTERRUPT(vFreeRTOSEMACTxInterrupt, IRQ)
void vFreeRTOSEMACTxInterrupt(void)
{
    static hdkif_t *hdkif = &hdkif_data[0U];
    static BaseType_t xHigherPriorityTaskWoken;
    emac_tx_bd_t *pxCurrentBufferDescriptor;

    /* Acknowledge EMAC by writing completion pointer. */
    pxCurrentBufferDescriptor = (emac_tx_bd_t *)HWREG(hdkif->emac_base + EMAC_TXCP(EMAC_CHANNELNUMBER));
    HWREG(hdkif->emac_base + EMAC_TXCP(EMAC_CHANNELNUMBER)) = (uint32_t)pxCurrentBufferDescriptor;

    /* Restart the transmission if there is more packet to transfer. */
    if(pxCurrentBufferDescriptor->next != NULL)
    {
        HWREG(hdkif->emac_base + EMAC_TXHDP((uint32)EMAC_CHANNELNUMBER)) = BYTE_SWAP((uint32)(pxCurrentBufferDescriptor->next));
    }

    if(xIPTaskHandle != NULL && xEMACTxEventSemaphore != NULL)
    {
        xSemaphoreGiveFromISR(xEMACTxEventSemaphore, &xHigherPriorityTaskWoken);
    }

    /* Acknowledge EMAC control modul TX IRQ */
    EMACCoreIntAck(hdkif->emac_base, EMAC_INT_CORE0_TX);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/** ***************************************************************************************************
* @fn void vFreeRTOSEMACRxThrshInterrupt(void)
* @brief RX Threshold Interrupt for EMAC in FreeRTOS-Plus-TCP compatibility mode
*/
#pragma INTERRUPT(vFreeRTOSEMACRxThrshInterrupt, IRQ)
void vFreeRTOSEMACRxThrshInterrupt(void)
{
    static hdkif_t *hdkif = &hdkif_data[0U];

    if((HWREG(hdkif->emac_base + EMAC_RXINTSTATRAW) & RXnTHRESHPEND_BIT(EMAC_CHANNELNUMBER)) == RXnTHRESHPEND_BIT(EMAC_CHANNELNUMBER))
    {
        HWREG(hdkif->emac_base + EMAC_RXINTMASKCLEAR) = RXnTHRESHPEND_BIT(EMAC_CHANNELNUMBER);
    }

    EMACCoreIntAck(hdkif->emac_base, (uint32)EMAC_INT_CORE0_RX_THRESH);
}

/** ***************************************************************************************************
* @fn void vFreeRTOSEMACRxInterrupt(void)
* @brief RX Interrupt for EMAC in FreeRTOS-Plus-TCP compatibility mode
*/
#pragma INTERRUPT(vFreeRTOSEMACRxInterrupt, IRQ)
void vFreeRTOSEMACRxInterrupt(void)
{
    static BaseType_t xHigherPriorityTaskWoken;
    static hdkif_t *hdkif = &hdkif_data[0U];
    emac_rx_bd_t *pxCurrentBufferDescriptor;

    if(prvEmacRxTaskHandle != NULL)
    {
        vTaskNotifyGiveFromISR(prvEmacRxTaskHandle, &xHigherPriorityTaskWoken);
    }
    pxCurrentBufferDescriptor = (emac_rx_bd_t *)HWREG(hdkif->emac_base + EMAC_RXCP(EMAC_CHANNELNUMBER));
    HWREG(hdkif->emac_base + EMAC_RXCP(EMAC_CHANNELNUMBER)) = (uint32_t)pxCurrentBufferDescriptor;
    EMACCoreIntAck(hdkif->emac_base, EMAC_INT_CORE0_RX);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/** ***************************************************************************************************
* @fn void prvEmacRxTask(void *pvParameters)
* @brief defered EMAC RX interrupt handler task.
*/
void prvEmacRxTask(void *pvParameters)
{
    hdkif_t *hdkif = &hdkif_data[0U];                       /* EMAC pointerek */
    volatile rxch_t *pxRxChannelDMA = &(hdkif->rxchptr);    /* RX DMA pointerek */
    volatile emac_rx_bd_t *pxCurrentBufferDescriptor;
    volatile emac_rx_bd_t *pxCurrentBufferDescTemp;
    volatile emac_rx_bd_t *pxTailBufferDescriptor;
    unsigned int xPacketSize;
    xNetworkBufferDescriptor_t *pxBufferDescriptor;
    xIPStackEvent_t xRxEvent;

    pxCurrentBufferDescriptor = pxRxChannelDMA->active_head;
    pxTailBufferDescriptor = (emac_rx_bd_t *)(0xfc521130);

    while(1)
    {
        if(ulTaskNotifyTake(pdTRUE, ipconfigETHERNET_DRIVER_RX_TASK_BLOCK_TIME) > 0)
        {
            while(1)
            {
                xPacketSize = BYTE_SWAP(pxCurrentBufferDescriptor->flags_pktlen) & 0xffff;

                _dcacheInvalidateRange_(BYTE_SWAP((uint32_t)pxCurrentBufferDescriptor->bufptr), BYTE_SWAP((uint32_t)pxCurrentBufferDescriptor->bufptr) + xPacketSize);

                if((BYTE_SWAP(pxCurrentBufferDescriptor->flags_pktlen) & EMAC_BUF_DESC_OWNER) != EMAC_BUF_DESC_OWNER && (BYTE_SWAP(pxCurrentBufferDescriptor->flags_pktlen) & EMAC_BUF_DESC_SOP) == EMAC_BUF_DESC_SOP)
                {
//                    if(xEMACDriverLoggingLevel > 1)
//                        FreeRTOS_debug_printf(("EMACRX: Packet arrived, BD: %p, RXHP: %p\r\n", pxCurrentBufferDescriptor, HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER))));

//                    if((BYTE_SWAP(pxCurrentBufferDescriptor->flags_pktlen) & EMAC_BUF_DESC_EOP) != EMAC_BUF_DESC_EOP)
//                    {
//                        FreeRTOS_debug_printf(("EMACRX: NO EOP: %p, RXHP: %p\r\n", pxCurrentBufferDescriptor, HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER))));
 //                   }

                    if(eConsiderFrameForProcessing((const uint8_t *)BYTE_SWAP((uint32_t)pxCurrentBufferDescriptor->bufptr)) == eProcessBuffer)
                    {
//                        if(xEMACDriverLoggingLevel > 1)
//                            FreeRTOS_debug_printf(("EMACRX: BD processing: %p, RXHP: %p\r\n", pxCurrentBufferDescriptor, HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER))));

                        pxBufferDescriptor = pxGetNetworkBufferWithDescriptor(xPacketSize, (TickType_t)ipconfigTCP_MAX_RECV_BLOCK_TIME_TICKS);

                        if(pxBufferDescriptor != NULL)
                        {

//                          if(xEMACDriverLoggingLevel > 1)
//                                FreeRTOS_debug_printf(("EMACRX: Network buffer allocated. NP: %p, BD: %p, RXHP: %p\r\n", pxBufferDescriptor, pxCurrentBufferDescriptor, HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER))));

                            memcpy((void *)pxBufferDescriptor->pucEthernetBuffer,(void *)(BYTE_SWAP(pxCurrentBufferDescriptor->bufptr)),xPacketSize);
                            pxBufferDescriptor->xDataLength = xPacketSize;

                            /* The event about to be sent to the TCP/IP is an Rx event. */
                            xRxEvent.eEventType = eNetworkRxEvent;

                            /* pvData is used to point to the network buffer descriptor that references the received data. */
                            xRxEvent.pvData = (void *) pxBufferDescriptor;

                            if(xSendEventStructToIPTask(&xRxEvent, 0) == pdFALSE)
                            {
                                vReleaseNetworkBufferAndDescriptor(pxBufferDescriptor);

                                iptraceETHERNET_RX_EVENT_LOST();
                            }
                            else
                            {
                                /* The message was successfully sent to the TCP/IP stack.
                                Call the standard trace macro to log the occurrence. */
                                iptraceNETWORK_INTERFACE_RECEIVE();
                            }
                        }
//                        else
//                        {
//                            FreeRTOS_debug_printf(("EMACRX: No more free pxBufferDescriptor.\n\r"));
//                        }
                    }
//                    else
//                    {
//                        if(xEMACDriverLoggingLevel > 0)
//                            FreeRTOS_debug_printf(("EMACRX: BD %p dropped, RXHP: %p\r\n", pxCurrentBufferDescriptor, HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER))));
//                    }

                    pxCurrentBufferDescriptor->bufoff_len = BYTE_SWAP(ipTOTAL_ETHERNET_FRAME_SIZE);
                    pxCurrentBufferDescriptor->flags_pktlen = BYTE_SWAP(EMAC_BUF_DESC_OWNER);
                    pxCurrentBufferDescTemp = (emac_rx_bd_t *)BYTE_SWAP((uint32_t)pxCurrentBufferDescriptor->next);
                    pxCurrentBufferDescriptor->next = NULL;

                    if(HWREG(hdkif->emac_base + EMAC_RXFREEBUFFER(EMAC_CHANNELNUMBER)) < ipconfigNUM_NETWORK_BUFFER_DESCRIPTORS)
                        HWREG(hdkif->emac_base + EMAC_RXFREEBUFFER(EMAC_CHANNELNUMBER)) = 1;

                    pxTailBufferDescriptor->next = (emac_rx_bd_t *)BYTE_SWAP((uint32_t)pxCurrentBufferDescriptor);

                    if((BYTE_SWAP(pxTailBufferDescriptor->flags_pktlen) & EMAC_BUF_DESC_EOQ) == EMAC_BUF_DESC_EOQ)
                    {
                        while(HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER)) != 0);
                        HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER)) = (uint32_t)pxCurrentBufferDescriptor;
//                        if(xEMACDriverLoggingLevel > 0)
//                            FreeRTOS_debug_printf(("EMACRX: RX restarted at BD: %p\r\n", pxCurrentBufferDescriptor));
                    }
                    pxTailBufferDescriptor = pxCurrentBufferDescriptor;
                    pxCurrentBufferDescriptor = pxCurrentBufferDescTemp;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            /* Nem kaptunk szemafor-t az adott blocking time-on -> IRQ elveszett */
            if(HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER)) == 0)
            {
                HWREG(hdkif->emac_base + EMAC_RXHDP(EMAC_CHANNELNUMBER)) = (uint32_t)pxCurrentBufferDescriptor;
//                if(xEMACDriverLoggingLevel > 0)
//                    FreeRTOS_debug_printf(("EMACRX: RX restarted at BD: %p\r\n", pxCurrentBufferDescriptor));
            }
        }
    }
}

/** ***************************************************************************************************
 * @fn      uint32 xFreeRTOSEMACHWInit(uint8_t macaddr[6U])
 * @brief   Low level function for Initializes the EMAC module for transmission and reception.
 * @param   macaddr MAC Address of the Module.
 * @return  EMAC_ERR_OK if everything gets initialized
 *          EMAC_ERR_CONN in case of an error in connecting.
 */
uint32 xFreeRTOSEMACHWInit(uint8_t macaddr[6U])
{
    uint32_t i;
    uint32 xReturn = EMAC_ERR_OK;
    static uint8_t xFirstInit = 1;

    hdkif_t *hdkif;
    hdkif = &hdkif_data[0U];

    EMACInstConfig(hdkif);

    for(i=0;i<EMAC_HWADDR_LEN;i++)
        hdkif->mac_addr[i] = macaddr[(EMAC_HWADDR_LEN - 1U) - i];


    HWREG(hdkif->emac_ctrl_base + EMAC_CTRL_SOFTRESET) = EMAC_CONTROL_RESET;
    while((HWREG(hdkif->emac_ctrl_base + EMAC_CTRL_SOFTRESET) & EMAC_CONTROL_RESET) == EMAC_CONTROL_RESET);
    HWREG(hdkif->emac_base + EMAC_SOFTRESET) = EMAC_SOFT_RESET;
    while((HWREG(hdkif->emac_base + EMAC_SOFTRESET) & EMAC_SOFT_RESET) == EMAC_SOFT_RESET);

    HWREG(hdkif->emac_base + EMAC_MACCONTROL)= 0U;
    HWREG(hdkif->emac_base + EMAC_RXCONTROL)= 0U;
    HWREG(hdkif->emac_base + EMAC_TXCONTROL)= 0U;

    for(i=0;i<EMAC_MAX_HEADER_DESC;i++)
    {
        HWREG(hdkif->emac_base + EMAC_RXHDP(i)) = 0U;
        HWREG(hdkif->emac_base + EMAC_TXHDP(i)) = 0U;
        HWREG(hdkif->emac_base + EMAC_RXCP(i)) = 0U;
        HWREG(hdkif->emac_base + EMAC_TXCP(i)) = 0U;
    }

    HWREG(hdkif->emac_base + EMAC_MACCONTROL) &= 0xFFFFFFE7;          /* Flow control disable */

    HWREG(hdkif->emac_base + EMAC_TXINTMASKCLEAR) = 0xFFU;
    HWREG(hdkif->emac_base + EMAC_RXINTMASKCLEAR) = 0xFFU;

    HWREG(hdkif->emac_base + EMAC_MACHASH1) = 0U;
    HWREG(hdkif->emac_base + EMAC_MACHASH2) = 0U;

    HWREG(hdkif->emac_base + EMAC_RXBUFFEROFFSET) = 0U;

    EMACMACSrcAddrSet(hdkif->emac_base, hdkif->mac_addr);
    for(i=0;i<8U;i++){EMACMACAddrSet(hdkif->emac_base, i, hdkif->mac_addr, EMAC_MACADDR_MATCH);}

    /* EMAC link UP */
    if(EMACLinkSetup(hdkif) != EMAC_ERR_OK)
    {
        xReturn = EMAC_ERR_CONNECT;
    }

    if(xFirstInit)
    {
        prvEmacDMAInit(hdkif);
        xFirstInit = 0;
    }

    EMACRMIISpeedSet(hdkif->emac_base,EMAC_RMIISPEED_100MBPS);
    EMACMIIEnable(hdkif->emac_base);
    EMACRxBroadCastEnable(hdkif->emac_base, (uint32)EMAC_CHANNELNUMBER);
    EMACRxUnicastSet(hdkif->emac_base, (uint32)EMAC_CHANNELNUMBER);
    EMACDisableLoopback(hdkif->emac_base);

    return xReturn;
}


/** ***************************************************************************************************
 * @fn      static void prvEmacDMAInit(hdkif_t *hdkif)
 * @brief   Creates linked buffer descriptor lists for sending and receiving ethernet frames
 * @param   hdkif   network interface structure
 * @return  None
 */
static void prvEmacDMAInit(hdkif_t *hdkif)
{
      txch_t *pxTxChannelDMA;
      rxch_t *pxRxChannelDMA;
      volatile emac_rx_bd_t *pxCurrentBD;           /* BD linkelt lista buffer  */
      unsigned int i;

      pxTxChannelDMA = &(hdkif->txchptr);
      pxRxChannelDMA = &(hdkif->rxchptr);

      pxCurrentBD = (void *)EMAC_TXDMA_PBUF_START_ADDRESS;
      pxTxChannelDMA->free_head = (void *)pxCurrentBD;
      pxTxChannelDMA->next_bd_to_process = (void *)pxCurrentBD;
      pxTxChannelDMA->active_tail = NULL;

      /* TX Buffer descriptor  */
      for(i = 0; i < EMAC_TXDMA_PBUF_ALLOC; i++)
      {
          pxCurrentBD->next = NULL;
          pxCurrentBD->bufptr = BYTE_SWAP((uint32)pvPortMalloc(ipTOTAL_ETHERNET_FRAME_SIZE));
          pxCurrentBD->bufoff_len = BYTE_SWAP(ipTOTAL_ETHERNET_FRAME_SIZE);
          pxCurrentBD->flags_pktlen = 0;
          pxCurrentBD++;
      }

      pxCurrentBD = (void *)EMAC_RXDMA_PBUF_START_ADDRESS;

      /* RX Buffer descriptor  */
      pxRxChannelDMA->active_head = pxRxChannelDMA->active_tail = pxRxChannelDMA->free_head = pxCurrentBD;
      for(i = 0; i < EMAC_RXDMA_PBUF_ALLOC; i++)
      {
          if (i < (EMAC_RXDMA_PBUF_ALLOC - 1))
              pxCurrentBD->next = (emac_rx_bd_t *)BYTE_SWAP((uint32)(pxCurrentBD + 1));
          else
              pxCurrentBD->next = NULL;

          pxCurrentBD->bufptr = BYTE_SWAP((uint32)pvPortMalloc(ipTOTAL_ETHERNET_FRAME_SIZE));

          pxCurrentBD->bufoff_len = BYTE_SWAP(ipTOTAL_ETHERNET_FRAME_SIZE);
          pxCurrentBD->flags_pktlen = BYTE_SWAP(EMAC_BUF_DESC_OWNER);
          pxCurrentBD++;
      }

      /* DMA BD  */
      for(; i<(SIZE_EMAC_CTRL_RAM) / sizeof(emac_tx_bd_t); i++)
      {
          pxCurrentBD->next = NULL;
          pxCurrentBD->bufptr = NULL;
          pxCurrentBD->bufoff_len = NULL;
          pxCurrentBD->flags_pktlen = NULL;
          pxCurrentBD++;
      }
}


