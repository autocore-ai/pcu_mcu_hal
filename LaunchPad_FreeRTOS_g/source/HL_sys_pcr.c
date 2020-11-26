/** @file HL_sys_pcr.c
*   @brief PCR Driver Source File
*   @date 03.Apr.2015
*   @version 04.04.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the PCR driver.
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


#include "HL_sys_pcr.h"

/** @fn void peripheral_Memory_Protection_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS)
*   @brief Set Peripheral Memory Protection
*
*   @param[in] pcr   PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS   Peripheral memory chip select (PCS0..PCS63)
*
*   This function enables peripheral memory protection (write in privileged mode only) for the selected frame
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_Protection_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS)
{
/* USER CODE BEGIN (0) */
/* USER CODE END */

	if (PCS < 32U)
	{
		pcr->PMPROTSET0 = (uint32)1U << PCS;
	}
	else
	{
		pcr->PMPROTSET1 = (uint32)1U << (PCS - 32U);
	}

/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/** @fn void peripheral_Memory_Protection_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS)
*   @brief Clear Peripheral Memory Protection
*
*   @param[in] pcr   PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS   Peripheral memory chip select (PCS0..PCS63)
*
*   This function disables peripheral memory protection (write in privileged mode only) for the selected frame
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_Protection_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

	if (PCS < 32U)
	{
		pcr->PMPROTCLR0 = (uint32)1U << PCS;
	}
	else
	{
		pcr->PMPROTCLR1 = (uint32)1U << (PCS - 32U);
	}

/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_Protection_Set(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
*   @brief Set Peripheral Frame Protection
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*
*   This function enables peripheral frame protection (write in privileged mode only) for the selected frame
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_Protection_Set(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	if (PS < 8U)
	{
		pcr->PPROTSET0 = quadrant << PS * 4U;
	}
	else if (PS < 16U)
	{
		pcr->PPROTSET1 = quadrant << ((PS - 8U) * 4U);
	}
	else if (PS < 24U)
	{
		pcr->PPROTSET2 = quadrant << ((PS - 16U) * 4U);
	}
	else
	{
		pcr->PPROTSET3 = quadrant << ((PS - 24U) * 4U);
	}

/* USER CODE BEGIN (5) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_Protection_Clr(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
*   @brief Clear Peripheral Frame Protection
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*
*   This function disables peripheral frame protection (write in privileged mode only) for the selected frame
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_Protection_Clr(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	if (PS < 8U)
	{
		pcr->PPROTCLR0 = quadrant << PS * 4U;
	}
	else if (PS < 16U)
	{
		pcr->PPROTCLR1 = quadrant << ((PS - 8U) * 4U);
	}
	else if (PS < 24U)
	{
		pcr->PPROTCLR2 = quadrant << ((PS - 16U) * 4U);
	}
	else
	{
		pcr->PPROTCLR3 = quadrant << ((PS - 24U) * 4U);
	}

/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/** @fn void peripheral_Memory_PowerDown_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS)
*   @brief Set Peripheral Memory Power Down
*
*   @param[in] pcr   PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS   Peripheral memory chip select (PCS0..PCS63)
*
*   This function disables the clocks to the selected peripheral memory
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_PowerDown_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

	if (PCS < 32U)
	{
		pcr->PCSPWRDWNSET0 = (uint32)1U << PCS;
	}
	else
	{
		pcr->PCSPWRDWNSET1 = (uint32)1U << (PCS - 32U);
	}

/* USER CODE BEGIN (9) */
/* USER CODE END */
}

/** @fn void peripheral_Memory_PowerDown_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS)
*   @brief Clear Peripheral Memory Power Down
*
*   @param[in] pcr   PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS   Peripheral memory chip select (PCS0..PCS63)
*
*   This function enables the clocks to the selected peripheral memory
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_PowerDown_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

	if (PCS < 32U)
	{
		pcr->PCSPWRDWNCLR0 = (uint32)1U << PCS;
	}
	else
	{
		pcr->PCSPWRDWNCLR1 = (uint32)1U << (PCS - 32U);
	}

/* USER CODE BEGIN (11) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_PowerDown_Set(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
*   @brief Set Peripheral Frame Power Down
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*
*   This function disables the clocks to the selected quadrant(s)
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_PowerDown_Set(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
{
/* USER CODE BEGIN (12) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	if (PS < 8U)
	{
		pcr->PSPWRDWNSET0 = quadrant << (PS * 4U);
	}
	else if (PS < 16U)
	{
		pcr->PSPWRDWNSET1 = quadrant << ((PS - 8U) * 4U);
	}
	else if (PS < 24U)
	{
		pcr->PSPWRDWNSET2 = quadrant << ((PS - 16U) * 4U);
	}
	else
	{
		pcr->PSPWRDWNSET3 = quadrant << ((PS - 24U) * 4U);
	}

/* USER CODE BEGIN (13) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_PowerDown_Set(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
*   @brief Set Peripheral Frame Power Down
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*
*   This function enables the clocks to the selected quadrant(s)
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_PowerDown_Clr(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant)
{
/* USER CODE BEGIN (14) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	if (PS < 8U)
	{
		pcr->PSPWRDWNCLR0 = quadrant << (PS * 4U);
	}
	else if (PS < 16U)
	{
		pcr->PSPWRDWNCLR1 = quadrant << ((PS - 8U) * 4U);
	}
	else if (PS < 24U)
	{
		pcr->PSPWRDWNCLR2 = quadrant << ((PS - 16U) * 4U);
	}
	else
	{
		pcr->PSPWRDWNCLR3 = quadrant << ((PS - 24U) * 4U);
	}

/* USER CODE BEGIN (15) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant, master_ID_t master)
*   @brief Enable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function enables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PSxMSTID[PS].PSxMSTID_L |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PSxMSTID[PS].PSxMSTID_L |= (uint32)1U << (master + 16U);
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PSxMSTID[PS].PSxMSTID_H |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PSxMSTID[PS].PSxMSTID_H |= (uint32)1U << (master + 16U);
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (17) */
/* USER CODE END */
}

/** @fn void peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant, master_ID_t master)
*   @brief Disable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PS        Peripheral chip select (PS0..PS31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function disables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PSx corresponding to each peripheral frame
*/
void peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Frame_t PS, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (18) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PSxMSTID[PS].PSxMSTID_L &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PSxMSTID[PS].PSxMSTID_L &= ~((uint32)1U << (master + 16U));
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PSxMSTID[PS].PSxMSTID_H &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PSxMSTID[PS].PSxMSTID_H &= ~((uint32)1U << (master + 16U));
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, uint32 quadrant, master_ID_t master)
*   @brief Enable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PPS       Privileged Peripheral chip select (PPS0..PPS7)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function enables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPSx corresponding to each peripheral frame
*/
void privileged_Peripheral_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (20) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_L |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_L |= (uint32)1U << (master + 16U);
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_H |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_H |= (uint32)1U << (master + 16U);
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (21) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, uint32 quadrant, master_ID_t master)
*   @brief Disable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PPS       Privileged Peripheral chip select (PPS0..PPS7)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function disables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPSx corresponding to each peripheral frame
*/
void privileged_Peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (22) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_L &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_L &= ~((uint32)1U << (master + 16U));
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_H &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PPSxMSTID[PPS].PPSxMSTID_H &= ~((uint32)1U << (master + 16U));
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (23) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Extended_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, uint32 quadrant, master_ID_t master)
*   @brief Enable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PPSE      Privileged Peripheral Extended chip select (PPSE0..PPSE31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function enables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPSEx corresponding to each peripheral frame
*/
void privileged_Peripheral_Extended_Frame_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (24) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_L |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_L |= (uint32)1U << (master + 16U);
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_H |= (uint32)1U << master;
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_H |= (uint32)1U << (master + 16U);
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (25) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Extended_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, uint32 quadrant, master_ID_t master)
*   @brief Disable permission of the corresponding master to access the peripheral quadrant(s)
*
*   @param[in] pcr       PCR segment that contains the peripheral (pcrREG1..pcrREG3)
*   @param[in] PPSE      Privileged Peripheral Extended chip select (PPSE0..PPSE31)
*   @param[in] quadrant  Quandrant(s) of peripheral frame. Can be ORed value of:
*		                    - QUADRANT0
*		                    - QUADRANT1
*		                    - QUADRANT2
*		                    - QUADRANT3
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function disables the permission of the corresponding master to access the peripheral quadrant(s). This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPSEx corresponding to each peripheral frame
*/
void privileged_Peripheral_Extended_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, uint32 quadrant, master_ID_t master)
{
/* USER CODE BEGIN (26) */
/* USER CODE END */

	quadrant = quadrant & 0xFU;

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	if ((quadrant & QUADRANT0) != 0U)
	{
		/* Quadrant 0 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_L &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT1) != 0U)
	{
		/* Quadrant 2 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_L &= ~((uint32)1U << (master + 16U));
	}

	if ((quadrant & QUADRANT2) != 0U)
	{
		/* Quadrant 3 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_H &= ~((uint32)1U << master);
	}

	if ((quadrant & QUADRANT3) != 0U)
	{
		/* Quadrant 4 selected */
		pcr->PPSExMSTID[PPSE].PPSExMSTID_H &= ~((uint32)1U << (master + 16U));
	}

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (27) */
/* USER CODE END */
}

/** @fn void peripheral_Memory_MasterIDFilter_Enable(pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master)
*   @brief Enable permission of the corresponding master to access the peripheral memory
*
*   @param[in] pcr       PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS       Peripheral memory chip select (PCS0..PCS63)
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function enables the permission of the corresponding master to access the peripheral memory. This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_MasterIDFilter_Enable(pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master)
{
	uint8 i, j;

/* USER CODE BEGIN (28) */
/* USER CODE END */

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	i = PCS / 2U;
	j = PCS % 2U;
	j = j * 16U;  /* j = 0 for even numbers and 16 for odd numbers */

	pcr->PCSxMSTID[i] |= (uint32)1U << (master + j);

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (29) */
/* USER CODE END */
}

/** @fn void peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master)
*   @brief Disable permission of the corresponding master to access the peripheral memory
*
*   @param[in] pcr       PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PCS       Peripheral memory chip select (PCS0..PCS63)
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function disables the permission of the corresponding master to access the peripheral memory. This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PCSx corresponding to each peripheral memory
*/
void peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master)
{
	uint8 i, j;

/* USER CODE BEGIN (30) */
/* USER CODE END */

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	i = PCS / 2U;
	j = PCS % 2U;
	j = j * 16U;  /* j = 0 for even numbers and 16 for odd numbers */

	pcr->PCSxMSTID[i] &= ~((uint32)1U << (master + j));

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (31) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Memory_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master)
*   @brief Enable permission of the corresponding master to access the peripheral memory
*
*   @param[in] pcr       PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PPCS      Privileged Peripheral memory chip select (PPCS0..PPCS15)
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function enables the permission of the corresponding master to access the peripheral memory. This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPCSx corresponding to each peripheral memory
*/
void privileged_Peripheral_Memory_MasterIDFilter_Enable(pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master)
{
	uint8 i, j;

/* USER CODE BEGIN (32) */
/* USER CODE END */

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	i = PPCS / 2U;
	j = PPCS % 2U;
	j = j * 16U;  /* j = 0 for even numbers and 16 for odd numbers */

	pcr->PPCSxMSTID[i] |= (uint32)1U << (master + j);

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (33) */
/* USER CODE END */
}

/** @fn void privileged_Peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master)
*   @brief Disable permission of the corresponding master to access the peripheral memory
*
*   @param[in] pcr       PCR segment that contains the peripheral memory (pcrREG1..pcrREG3)
*   @param[in] PPCS      Privileged Peripheral memory chip select (PPCS0..PPCS15)
*   @param[in] master    Master-ID
*							- Master_CPU0
*							- Master_CPU1(Reserved for Lock-Step device)
*							- Master_DMA
*							- Master_HTU1
*							- Master_HTU2
*							- Master_FTU
*							- Master_DMM
*							- Master_DAP
*							- Master_EMAC
*
*   This function disables the permission of the corresponding master to access the peripheral memory. This function will not enable master-id check for the selected PCR. Application must call the routine  pcrEnableMasterIDCheck to do the same.
*   @Note Please refer the datasheet for PCRx and PPCSx corresponding to each peripheral memory
*/
void privileged_Peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master)
{
	uint8 i, j;

/* USER CODE BEGIN (34) */
/* USER CODE END */

	/* Enable MasterID register writes */
	pcr->MSTIDWRENA = 0xAU;

	i = PPCS / 2U;   /* Find the index of the register to be written  */
	j = PPCS % 2U;   /* Find the bit position                         */
	j = j * 16U;     /* j = 0 for even numbers and 16 for odd numbers */

	pcr->PPCSxMSTID[i] &= ~((uint32)1U << (master + j));

	/* Disable MasterID register writes */
	pcr->MSTIDWRENA = 0x5U;

/* USER CODE BEGIN (35) */
/* USER CODE END */
}

/** @fn void pcrEnableMasterIDCheck(pcrBASE_t *pcr)
*   @brief Enable Master-ID check
*
*   @param[in] pcr  PCR segment (pcrREG1..pcrREG3)
*
*   This function enables master-id check for the selected PCR.
*/
void pcrEnableMasterIDCheck(pcrBASE_t *pcr)
{
/* USER CODE BEGIN (36) */
/* USER CODE END */

	pcr->MSTIDENA = 0xAU;

/* USER CODE BEGIN (37) */
/* USER CODE END */
}

/** @fn void pcrDisableMasterIDCheck(pcrBASE_t *pcr)
*   @brief Disable Master-ID check
*
*   @param[in] pcr  PCR segment (pcrREG1..pcrREG3)
*
*   This function disables master-id check for the selected PCR.
*/
void pcrDisableMasterIDCheck(pcrBASE_t *pcr)
{
/* USER CODE BEGIN (38) */
/* USER CODE END */

	pcr->MSTIDENA = 0x5U;

/* USER CODE BEGIN (39) */
/* USER CODE END */
}
