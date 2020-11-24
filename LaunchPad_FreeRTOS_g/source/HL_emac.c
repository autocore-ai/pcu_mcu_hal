/**
 *  \file   emac.c
 *
 *  \brief  EMAC APIs.
 *
 *   This file contains the device abstraction layer APIs for EMAC.
 */

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/



/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "HL_sys_vim.h"
#include "HL_emac.h"

/* USER CODE BEGIN (1) */
extern SemaphoreHandle_t xEMACRxEventSemaphore, xEMACNetworkDownEventSemaphore;
/* USER CODE END */

/* Defining interface for all the emac instances */
hdkif_t hdkif_data[MAX_EMAC_INSTANCE];
/*SAFETYMCUSW 25 D MR:8.7 <APPROVED> "Statically allocated memory needs to be available to entire application." */
//static uint8_t pbuf_array[MAX_RX_PBUF_ALLOC][MAX_TRANSFER_UNIT];
//static uint8_t pbuf_array[MAX_RX_PBUF_ALLOC][1600]  __attribute__((aligned(8))) __attribute__ ((section(".sdram")));;
/*******************************************************************************
*                       INTERNAL MACRO DEFINITIONS
*******************************************************************************/

#define EMAC_CONTROL_RESET             (0x01U)
#define EMAC_SOFT_RESET                (0x01U)
#define EMAC_MAX_HEADER_DESC           (8U)
#define EMAC_UNICAST_DISABLE           (0xFFU)


/* SourceId : ETH_SourceId_006 */
/* DesignId : ETH_DesignId_006*/
/* Requirements : HL_ETH_SR18 */
/**
 * \brief   This API enables the MII control block. It also needs to be enabled in the PINMUX module.
 *
 * \param   emacBase     Base address of the EMAC Module registers.
 *
 * \return  None
 *
 **/
void EMACMIIEnable(uint32 emacBase)
{
    HWREG(emacBase + EMAC_MACCONTROL) |= EMAC_MACCONTROL_GMIIEN;
}

/**
 * \brief   This API sets the RMII speed. The RMII Speed can be 10 Mbps or
 *          100 Mbps
 *
 * \param   emacBase     Base address of the EMAC Module registers.
 * \param   speed        speed for setting.
 *          speed can take the following values. \n
 *                EMAC_RMIISPEED_10MBPS - 10 Mbps \n
 *                EMAC_RMIISPEED_100MBPS - 100 Mbps.
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_005 */
/* DesignId : ETH_DesignId_005*/
/* Requirements : HL_CONQ_EMAC_SR23 */
void EMACRMIISpeedSet(uint32 emacBase, uint32 speed)
{
    HWREG(emacBase + EMAC_MACCONTROL) &= (~(uint32)EMAC_MACCONTROL_RMIISPEED);

    HWREG(emacBase + EMAC_MACCONTROL) |= speed;
}

/**
 * \brief   Sets the MAC Address in MACSRCADDR registers.
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \param   macAddr       Start address of a MAC address array.
 *                        The array[0] shall be the LSB of the MAC address
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_016 */
/* DesignId : ETH_DesignId_016*/
/* Requirements : HL_ETH_SR7 */
void  EMACMACSrcAddrSet(uint32 emacBase, uint8 macAddr[6])
{
    HWREG(emacBase + EMAC_MACSRCADDRHI) = ((uint32)macAddr[5U] |((uint32)macAddr[4U] << 8U)
                                     |((uint32)macAddr[3U] << 16U) |((uint32)macAddr[2U] << 24U));
    HWREG(emacBase + EMAC_MACSRCADDRLO) = ((uint32)macAddr[1U] | ((uint32)macAddr[0U] << 8U));
}

/**
 * \brief   Sets the MAC Address in MACADDR registers.
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \param   channel       Channel Number
 * \param   matchFilt     Match or Filter
 * \param   macAddr       Start address of a MAC address array.
 *                        The array[0] shall be the LSB of the MAC address
 *          matchFilt can take the following values \n
 *          EMAC_MACADDR_NO_MATCH_NO_FILTER - Address is not used to match
 *                                             or filter incoming packet. \n
 *          EMAC_MACADDR_FILTER - Address is used to filter incoming packets \n
 *          EMAC_MACADDR_MATCH - Address is used to match incoming packets \n
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_017 */
/* DesignId : ETH_DesignId_017*/
/* Requirements : HL_ETH_SR7 */
void EMACMACAddrSet(uint32 emacBase, uint32 channel, uint8 macAddr[6], uint32 matchFilt)
{
    HWREG(emacBase + EMAC_MACINDEX) = channel;

    HWREG(emacBase + EMAC_MACADDRHI) = ((uint32)macAddr[5U] |((uint32)macAddr[4U] << 8U)
                                     |((uint32)macAddr[3U] << 16U) |((uint32)macAddr[2U] << 24U));
    HWREG(emacBase + EMAC_MACADDRLO) = ((uint32)macAddr[1U] | ((uint32)macAddr[0U] << 8U)
                                     | matchFilt | (channel << 16U));
}

/**
 * \brief   Acknowledges an interrupt processed to the EMAC Control Core.
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \param   eoiFlag       Type of interrupt to acknowledge to the EMAC Control
 *                         module.
 *          eoiFlag can take the following values \n
 *             EMAC_INT_CORE0_TX - Core 0 TX Interrupt
 *             EMAC_INT_CORE1_TX - Core 1 TX Interrupt
 *             EMAC_INT_CORE2_TX - Core 2 TX Interrupt
 *             EMAC_INT_CORE0_RX - Core 0 RX Interrupt
 *             EMAC_INT_CORE1_RX - Core 1 RX Interrupt
 *             EMAC_INT_CORE2_RX - Core 2 RX Interrupt
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_018 */
/* DesignId : ETH_DesignId_018*/
/* Requirements : HL_ETH_SR15 */
void EMACCoreIntAck(uint32 emacBase, uint32 eoiFlag)
{
    /* Acknowledge the EMAC Control Core */
    HWREG(emacBase + EMAC_MACEOIVECTOR) = eoiFlag;
}

/**
* Function to setup the instance parameters inside the interface
* @param   hdkif Network interface structure
* @return  none.
*/
/* SourceId : ETH_SourceId_029 */
/* DesignId : ETH_DesignId_029*/
/* Requirements : HL_ETH_SR6 */
void EMACInstConfig(hdkif_t *hdkif)
{
    hdkif->emac_base = EMAC_0_BASE;
    hdkif->emac_ctrl_base = EMAC_CTRL_0_BASE;
    hdkif->emac_ctrl_ram = EMAC_CTRL_RAM_0_BASE;
}

/**
* Function to setup the link. AutoNegotiates with the phy for link
* setup and set the EMAC with the result of autonegotiation.
* @param  hdkif Network interface structure.
* @return ERR_OK if everything passed
*         others if not passed
*/
/* SourceId : ETH_SourceId_030 */
/* DesignId : ETH_DesignId_030*/
/* Requirements : HL_ETH_SR6 */
uint32 EMACLinkSetup(hdkif_t *hdkif)
{
    uint32 linkstat = EMAC_ERR_CONNECT;
    uint32 phyduplex = EMAC_DUPLEX_HALF;
    volatile uint32 delay = 0xFFFFFU;
    linkstat = EMAC_ERR_OK;
    phyduplex = EMAC_DUPLEX_FULL;

    /* Set the EMAC with the negotiation results if it is successful */
    if(linkstat == EMAC_ERR_OK)
    {
        EMACDuplexSet(hdkif->emac_base, phyduplex);
    }

    while(delay != 0U)
    {
        delay--;
    }

    return linkstat;
}

/**
 * \brief   Disables Loopback Mode.
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_039 */
/* DesignId : ETH_DesignId_039*/
/* Requirements : HL_ETH_SR50 */
void EMACDisableLoopback(uint32 emacBase)
{
    uint32 GMIIENval=0U;

    /*Store the value of GMIIEN bit before deasserting it */
    GMIIENval = HWREG(emacBase + EMAC_MACCONTROL) & EMAC_MACCONTROL_GMIIEN;
    HWREG(emacBase + EMAC_MACCONTROL) &= (~(uint32)EMAC_MACCONTROL_GMIIEN);

    /*Disable Loopback */
    HWREG(emacBase + EMAC_MACCONTROL) &= (~(uint32)EMAC_MACCONTROL_LOOPBACK);

    /*Restore the value of GMIIEN bit */
    HWREG(emacBase + EMAC_MACCONTROL) |= GMIIENval;
}
/**
 * \brief   Enables unicast for a specific channel
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \param   channel       Channel Number.
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_025 */
/* DesignId : ETH_DesignId_025*/
/* Requirements : HL_ETH_SR14 */
void EMACRxUnicastSet(uint32 emacBase, uint32 channel)
{
    HWREG(emacBase + EMAC_RXUNICASTSET) |= ((uint32)1U << channel);
}
/**
 * \brief   Enables a specific channel to receive broadcast frames
 *
 * \param   emacBase      Base Address of the EMAC module registers.
 * \param   channel       Channel Number.
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_021 */
/* DesignId : ETH_DesignId_021*/
/* Requirements : HL_ETH_SR28 */
void EMACRxBroadCastEnable(uint32 emacBase, uint32 channel)
{
    HWREG(emacBase + EMAC_RXMBPENABLE) &= (~(uint32)EMAC_RXMBPENABLE_RXBROADCH);

    HWREG(emacBase + EMAC_RXMBPENABLE) |= ((uint32)EMAC_RXMBPENABLE_RXBROADEN | ((uint32)channel << (uint32)EMAC_RXMBPENABLE_RXBROADCH_SHIFT));

}

void EMACRxMultiCastEnable(uint32 emacBase, uint32 channel)
{
    HWREG(emacBase + EMAC_RXMBPENABLE) &= (~(uint32)EMAC_RXMBPENABLE_RXMULTCH);

    HWREG(emacBase + EMAC_RXMBPENABLE) |= ((uint32)EMAC_RXMBPENABLE_RXMULTEN | ((uint32)channel << (uint32)EMAC_RXMBPENABLE_RXMULTCH_SHIFT));
}

/**
 * \brief   This API sets the duplex mode of operation(full/half) for MAC.
 *
 * \param   emacBase     Base address of the EMAC Module registers.
 * \param   duplexMode   duplex mode of operation.
 *          duplexMode can take the following values. \n
 *                EMAC_DUPLEX_FULL - Full Duplex  \n
 *                EMAC_DUPLEX_HALF - Half Duplex.
 *
 * \return  None
 *
 **/
/* SourceId : ETH_SourceId_008 */
/* DesignId : ETH_DesignId_008*/
/* Requirements : HL_ETH_SR21 */
void EMACDuplexSet(uint32 emacBase, uint32 duplexMode)
{
    HWREG(emacBase + EMAC_MACCONTROL) &= (~(uint32)EMAC_MACCONTROL_FULLDUPLEX);

    HWREG(emacBase + EMAC_MACCONTROL) |= duplexMode;
}

/**
 * \brief               This function reads the contents of the 36 network statistics registers that are present in the module.
 * \param   emacBase    Base Address of the EMAC module registers.
 * \param   statRegNo   The number of the register with RXGOODFRAMES (Offset= 0x200) being 0. Refer the Technical Reference Manual for the list of registers and their contents.
 * \return  uint32
 **/
uint32 EMACReadNetStatRegisters(uint32 emacBase, uint32 statRegNo)
{
    return HWREG(emacBase + EMAC_NETSTATREGS(statRegNo));
}

void EMACMACSrcAddrGet(uint32 emacBase, uint8* macAddr)
{
	*(macAddr) = (uint8)(HWREG(emacBase + EMAC_MACSRCADDRLO) >> 8U ) & 0xff;
	*(macAddr + 1U) = (uint8)HWREG(emacBase + EMAC_MACSRCADDRLO) & 0xff;
	*(macAddr + 2U) = (uint8)(HWREG(emacBase + EMAC_MACSRCADDRHI) >> 24U ) & 0xff;
	*(macAddr + 3U) = (uint8)(HWREG(emacBase + EMAC_MACSRCADDRHI) >> 16U ) & 0xff;
	*(macAddr + 4U) = (uint8)(HWREG(emacBase + EMAC_MACSRCADDRHI) >> 8U ) & 0xff;
	*(macAddr + 5U) = (uint8)HWREG(emacBase + EMAC_MACSRCADDRHI) & 0xff;
}



/* USER CODE BEGIN (3) */
/* USER CODE END */

/***************************** End Of File ***********************************/
