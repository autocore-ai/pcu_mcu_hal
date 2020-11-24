/** @file HL_can.c 
*   @brief CAN Driver Source File
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the CAN driver.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
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


/* Include Files */

#include "HL_can.h"
#include "HL_sys_vim.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */



/** @fn void canInit(void)
*   @brief Initializes CAN Driver
*
*   This function initializes the CAN driver.
*
*/
/* USER CODE BEGIN (3) */
/* USER CODE END */
/* SourceId : CAN_SourceId_001 */
/* DesignId : CAN_DesignId_001 */
/* Requirements : HL_CONQ_CAN_SR4 */
void canInit(void)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */
    /** @b Initialize @b CAN1: */

    /** - Setup control register
    *     - Disable automatic wakeup on bus activity
    *     - Local power down mode disabled
    *     - Disable DMA request lines
    *     - Enable global Interrupt Line 0 and 1
    *     - Disable debug mode
    *     - Release from software reset
    *     - Enable/Disable parity or ECC
    *     - Enable/Disable auto bus on timer
    *     - Setup message completion before entering debug state
    *     - Setup normal operation mode
    *     - Request write access to the configuration registers
    *     - Setup automatic retransmission of messages
    *     - Disable error interrupts
    *     - Disable status interrupts
    *     - Enter initialization mode
    */
    canREG1->CTL = (uint32)0x00000000U 
                 | (uint32)0x00000000U 
                 | (uint32)((uint32)0x00000005U  << 10U)
                 | (uint32)0x00020043U;

    /** - Clear all pending error flags and reset current status */
    canREG1->ES |= 0xFFFFFFFFU;

    /** - Assign interrupt level for messages */
    canREG1->INTMUXx[0U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;

    canREG1->INTMUXx[1U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;

    /** - Setup auto bus on timer period */
    canREG1->ABOTR = (uint32)0U;

    /** - Initialize message 1 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */


    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)1U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 1U;

    /** - Initialize message 2 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD5U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 2U;

    /** - Initialize message 3 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD4U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 3U;

    /** - Initialize message 4 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 4U;

    /** - Initialize message 5 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD5U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 5U;

    /** - Initialize message 6 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD4U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 6U;

    /** - Initialize message 7 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 7U;

    /** - Initialize message 8 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD5U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 8U;

    /** - Initialize message 9 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD4U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 9U;

    /** - Initialize message 10 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 10U;

    /** - Initialize message 11 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD5U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 11U;

    /** - Initialize message 12 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD4U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 12U;

    /** - Initialize message 13 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 13U;

    /** - Initialize message 14 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD5U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 14U;

    /** - Initialize message 15 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD4U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 15U;

    /** - Initialize message 16 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF2CMD  = (uint8) 0xF8U;
    canREG1->IF2NO   = 16U;

    /** - Initialize message 17 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG1->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0xD2U & (uint32)0x000007FFU) << (uint32)18U);
    canREG1->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG1->IF1CMD  = (uint8) 0xF8U;
    canREG1->IF1NO   = 17U;

    /** - Setup IF1 for data transmission 
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG1->IF1CMD  = 0x87U;

    /** - Setup IF2 for reading data
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG1->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG1->IF2CMD = 0x17U;

    /** - Setup bit timing 
    *     - Setup baud rate prescaler extension
    *     - Setup TSeg2
    *     - Setup TSeg1
    *     - Setup sample jump width
    *     - Setup baud rate prescaler
    */
    canREG1->BTR = (uint32)((uint32)0U << 16U) |
                   (uint32)((uint32)(4U - 1U) << 12U) |
                   (uint32)((uint32)((6U + 4U) - 1U) << 8U) |
                   (uint32)((uint32)(4U - 1U) << 6U) |
                   (uint32)9U;



     /** - CAN1 Port output values */
    canREG1->TIOC =  (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )                
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )    
                   | (uint32)((uint32)0U << 1U );
                   
    canREG1->RIOC =  (uint32)((uint32)1U  << 18U )    
                   | (uint32)((uint32)0U  << 17U )  
                   | (uint32)((uint32)0U  << 16U )   
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U <<1U );        

    /** - Leave configuration and initialization mode  */
    canREG1->CTL &= ~(uint32)(0x00000041U);


    /** @b Initialize @b CAN2: */

    /** - Setup control register
    *     - Disable automatic wakeup on bus activity
    *     - Local power down mode disabled
    *     - Disable DMA request lines
    *     - Enable global Interrupt Line 0 and 1
    *     - Disable debug mode
    *     - Release from software reset
    *     - Enable/Disable parity or ECC
    *     - Enable/Disable auto bus on timer
    *     - Setup message completion before entering debug state
    *     - Setup normal operation mode
    *     - Request write access to the configuration registers
    *     - Setup automatic retransmission of messages
    *     - Disable error interrupts
    *     - Disable status interrupts
    *     - Enter initialization mode
    */
    canREG2->CTL = (uint32)0x00000000U 
                 | (uint32)0x00000000U 
                 | (uint32)((uint32)0x00000005U << 10U)
                 | 0x00020043U;

    /** - Clear all pending error flags and reset current status */
    canREG2->ES |= 0xFFFFFFFFU;

    /** - Assign interrupt level for messages */
    canREG2->INTMUXx[0U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;

    canREG2->INTMUXx[1U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;


    /** - Setup auto bus on timer period */
    canREG2->ABOTR = (uint32)0U;


    /** - Initialize message 1 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */


    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)1U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 1U;

    /** - Initialize message 2 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65AU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 2U;

    /** - Initialize message 3 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 3U;

    /** - Initialize message 4 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 4U;

    /** - Initialize message 5 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 5U;

    /** - Initialize message 6 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 6U;

    /** - Initialize message 7 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 7U;

    /** - Initialize message 8 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 8U;

    /** - Initialize message 9 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 9U;

    /** - Initialize message 10 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 10U;

    /** - Initialize message 11 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 11U;

    /** - Initialize message 12 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 12U;

    /** - Initialize message 13 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 13U;

    /** - Initialize message 14 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 14U;

    /** - Initialize message 15 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 15U;

    /** - Initialize message 16 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 16U;

    /** - Initialize message 17 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x65BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG2->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 17U;

    /** - Setup IF1 for data transmission 
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG2->IF1CMD  = 0x87U;

    /** - Setup IF2 for reading data
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG2->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG2->IF2CMD = 0x17U;

    /** - Setup bit timing 
    *     - Setup baud rate prescaler extension
    *     - Setup TSeg2
    *     - Setup TSeg1
    *     - Setup sample jump width
    *     - Setup baud rate prescaler
    */
    canREG2->BTR = (uint32)((uint32)0U << 16U) |
                   (uint32)((uint32)(4U - 1U) << 12U) |
                   (uint32)((uint32)((6U + 4U) - 1U) << 8U) |
                   (uint32)((uint32)(4U - 1U) << 6U) |
                   (uint32)9U;		


   /** - CAN2 Port output values */
    canREG2->TIOC =  (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )  
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )    
                   | (uint32)((uint32)0U << 1U );
                   
    canREG2->RIOC =  (uint32)((uint32)1U  << 18U )    
                   | (uint32)((uint32)0U  << 17U )  
                   | (uint32)((uint32)0U  << 16U )   
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U <<1U );   

    /** - Leave configuration and initialization mode  */
    canREG2->CTL &= ~(uint32)(0x00000041U);

    /** @b Initialize @b CAN3: */

    /** - Setup control register
    *     - Disable automatic wakeup on bus activity
    *     - Local power down mode disabled
    *     - Disable DMA request lines
    *     - Enable global Interrupt Line 0 and 1
    *     - Disable debug mode
    *     - Release from software reset
    *     - Enable/Disable parity or ECC
    *     - Enable/Disable auto bus on timer
    *     - Setup message completion before entering debug state
    *     - Setup normal operation mode
    *     - Request write access to the configuration registers
    *     - Setup automatic retransmission of messages
    *     - Disable error interrupts
    *     - Disable status interrupts
    *     - Enter initialization mode
    */
    canREG3->CTL = (uint32)0x00000000U 
                 | (uint32)0x00000000U 
                 | (uint32)((uint32)0x00000005U << 10U)
                 | 0x00020043U;

    /** - Clear all pending error flags and reset current status */
    canREG3->ES |= 0xFFFFFFFFU;

    /** - Assign interrupt level for messages */
    canREG3->INTMUXx[0U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;

    canREG3->INTMUXx[1U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;


    /** - Setup auto bus on timer period */
    canREG3->ABOTR = (uint32)0U;

    /** - Initialize message 1 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */


    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)1U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 1U;

    /** - Initialize message 2 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x60BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 2U;

    /** - Initialize message 3 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x60CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 3U;

    /** - Initialize message 4 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x61BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 4U;

    /** - Initialize message 5 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x61CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 5U;

    /** - Initialize message 6 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x62BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 6U;

    /** - Initialize message 7 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x62CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 7U;

    /** - Initialize message 8 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x63BU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 8U;

    /** - Initialize message 9 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x63CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 9U;

    /** - Initialize message 10 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x63CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 10U;

    /** - Initialize message 11 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x62CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 11U;

    /** - Initialize message 12 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x61CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 12U;

    /** - Initialize message 13 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x60CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 13U;

    /** - Initialize message 14 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x60CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 14U;

    /** - Initialize message 15 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x61CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 15U;

    /** - Initialize message 16 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x62CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF2CMD  = (uint8) 0xF8U;
    canREG3->IF2NO   = 16U;

    /** - Initialize message 17 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG3->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x63CU & (uint32)0x000007FFU) << (uint32)18U);
    canREG3->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG3->IF1CMD  = (uint8) 0xF8U;
    canREG3->IF1NO   = 17U;

    /** - Setup IF1 for data transmission 
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG3->IF1CMD  = 0x87U;

    /** - Setup IF2 for reading data
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG3->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG3->IF2CMD = 0x17U;

    /** - Setup bit timing 
    *     - Setup baud rate prescaler extension
    *     - Setup TSeg2
    *     - Setup TSeg1
    *     - Setup sample jump width
    *     - Setup baud rate prescaler
    */
    canREG3->BTR = (uint32)((uint32)0U << 16U) |
                   (uint32)((uint32)(4U - 1U) << 12U) |
                   (uint32)((uint32)((6U + 4U) - 1U) << 8U) |
                   (uint32)((uint32)(4U - 1U) << 6U) |
                   (uint32)(uint32)9U;


    /** - CAN3 Port output values */
    canREG3->TIOC =  (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )  
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )    
                   | (uint32)((uint32)0U << 1U );
                   
    canREG3->RIOC =  (uint32)((uint32)1U  << 18U )    
                   | (uint32)((uint32)0U  << 17U )  
                   | (uint32)((uint32)0U  << 16U )   
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U << 1U );       

    /** - Leave configuration and initialization mode  */
    canREG3->CTL &= ~(uint32)(0x00000041U);

    /** @b Initialize @b CAN1: */

    /** - Setup control register
    *     - Disable automatic wakeup on bus activity
    *     - Local power down mode disabled
    *     - Disable DMA request lines
    *     - Enable global Interrupt Line 0 and 1
    *     - Disable debug mode
    *     - Release from software reset
    *     - Enable/Disable parity or ECC
    *     - Enable/Disable auto bus on timer
    *     - Setup message completion before entering debug state
    *     - Setup normal operation mode
    *     - Request write access to the configuration registers
    *     - Setup automatic retransmission of messages
    *     - Disable error interrupts
    *     - Disable status interrupts
    *     - Enter initialization mode
    */
    canREG4->CTL = (uint32)0x00000000U 
                 | (uint32)0x00000000U 
                 | ((uint32)0x00000005U  << 10U)
                 | (uint32)0x00020043U;

    /** - Clear all pending error flags and reset current status */
    canREG4->ES |= 0xFFFFFFFFU;

    /** - Assign interrupt level for messages */
    canREG4->INTMUXx[0U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;

    canREG4->INTMUXx[1U] = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000000U;


    /** - Setup auto bus on timer period */
    canREG4->ABOTR = (uint32)0U;

    /** - Initialize message 1 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */


    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)1U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 1U;

    /** - Initialize message 2 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 2U;

    /** - Initialize message 3 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 3U;

    /** - Initialize message 4 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 4U;

    /** - Initialize message 5 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 5U;

    /** - Initialize message 6 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 6U;

    /** - Initialize message 7 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 7U;

    /** - Initialize message 8 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 8U;

    /** - Initialize message 9 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 9U;

    /** - Initialize message 10 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 10U;

    /** - Initialize message 11 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 11U;

    /** - Initialize message 12 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 12U;

    /** - Initialize message 13 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 13U;

    /** - Initialize message 14 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 14U;

    /** - Initialize message 15 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 15U;

    /** - Initialize message 16 
    *     - Wait until IF2 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF2 control byte
    *     - Set IF2 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF2CMD  = (uint8) 0xF8U;
    canREG4->IF2NO   = 16U;

    /** - Initialize message 17 
    *     - Wait until IF1 is ready for use 
    *     - Set message mask
    *     - Set message control word
    *     - Set message arbitration
    *     - Set IF1 control byte
    *     - Set IF1 message number
    */
    /*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */

    canREG4->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0x00000000U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1ARB  = (uint32)0x80000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x372U & (uint32)0x000007FFU) << (uint32)18U);
    canREG4->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG4->IF1CMD  = (uint8) 0xF8U;
    canREG4->IF1NO   = 17U;

    /** - Setup IF1 for data transmission 
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF1STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG4->IF1CMD  = 0x87U;

    /** - Setup IF2 for reading data
    *     - Wait until IF1 is ready for use 
    *     - Set IF1 control byte
    */
	/*SAFETYMCUSW 28 D MR:NA <APPROVED> "Potentially infinite loop found - Hardware Status check for execution sequence" */
    while ((canREG4->IF2STAT & 0x80U) ==0x80U)
    { 
    } /* Wait */
    canREG4->IF2CMD = 0x17U;

    /** - Setup bit timing 
    *     - Setup baud rate prescaler extension
    *     - Setup TSeg2
    *     - Setup TSeg1
    *     - Setup sample jump width
    *     - Setup baud rate prescaler
    */
    canREG4->BTR = ((uint32)0U << 16U) |
                   (((uint32)4U - 1U) << 12U) |
                   ((((uint32)6U + (uint32)4U) - 1U) << 8U) |
                   (((uint32)4U - 1U) << 6U) |
                   (uint32)9U;



				   
    /** - CAN4 Port output values */
    canREG4->TIOC =  (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )  
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )    
                   | (uint32)((uint32)0U << 1U );
                   
    canREG4->RIOC =  (uint32)((uint32)1U  << 18U )    
                   | (uint32)((uint32)0U  << 17U )  
                   | (uint32)((uint32)0U  << 16U )   
                   | (uint32)((uint32)1U  << 3U )  
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U << 1U ); 
    /** - Leave configuration and initialization mode  */
    canREG4->CTL &= ~(uint32)(0x00000041U);


    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in privileged mode.\n
    */

/* USER CODE BEGIN (5) */
/* USER CODE END */
}



