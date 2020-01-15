/** @file HL_sys_startup.c 
*   @brief Startup Source File
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains:
*   - Include Files
*   - Type Definitions
*   - External Functions
*   - VIM RAM Setup
*   - Startup Routine
*   .
*   which are relevant for the Startup.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com
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

#include "HL_sys_common.h"
#include "HL_system.h"
#include "HL_sys_vim.h"
#include "HL_sys_core.h"
#include "HL_esm.h"
#include "HL_sys_mpu.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* External Functions */

/*SAFETYMCUSW 218 S MR:20.2 <APPROVED> "Functions from library" */
extern void __TI_auto_init(void);
/*SAFETYMCUSW 354 S MR:NA <APPROVED> " Startup code(main should be declared by the user)" */
extern int main(void);
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
/*SAFETYMCUSW 354 S MR:NA <APPROVED> " Startup code(Extern declaration present in the library)" */
extern void exit(int _status);


/* USER CODE BEGIN (3) */
/* USER CODE END */

/* Startup Routine */
void _c_int00(void);
/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma CODE_STATE(_c_int00, 32)
#pragma INTERRUPT(_c_int00, RESET)
#pragma WEAK(_c_int00)

/* SourceId : STARTUP_SourceId_001 */
/* DesignId : STARTUP_DesignId_001 */
/* Requirements : HL_CONQ_STARTUP_SR1 */
void _c_int00(void)
{
    /* Initialize Core Registers to avoid CCM Error */
    _coreInitRegisters_();
    /* Initialize Stack Pointers */
    _coreInitStackPointer_();

    /* Reset handler: the following instructions read from the system exception status register
     * to identify the cause of the CPU reset.
     */
    switch(getResetSource())
    {
        case POWERON_RESET:
        case DEBUG_RESET:
        case EXT_RESET:
        /* Initialize L2RAM to avoid ECC errors right after power on */
        _memInit_();

        _coreEnableEventBusExport_();

        if ((esmREG->SR1[2]) != 0U)
        {
           esmGroup3Notification(esmREG,esmREG->SR1[2]);               
        }

        systemInit();

        _coreEnableIrqVicOffset_();

        vimInit();

        esmInit();

        break;

        case OSC_FAILURE_RESET:
        break;

        case WATCHDOG_RESET:
        case WATCHDOG2_RESET:

//            _coreEnableIrqVicOffset_();

            vimInit();
//            esmInit();

        break;
    
        case CPU0_RESET:

         _coreEnableEventBusExport_();


        break;
    
        case SW_RESET:
        break;
    
        default:

        break;
    }


    _mpuInit_();

    _cacheEnable_();

    systemInit();

    vimInit();

     __TI_auto_init();
    
        /* call the application */
/*SAFETYMCUSW 296 S MR:8.6 <APPROVED> "Startup code(library functions at block scope)" */
/*SAFETYMCUSW 326 S MR:8.2 <APPROVED> "Startup code(Declaration for main in library)" */
/*SAFETYMCUSW 60 D MR:8.8 <APPROVED> "Startup code(Declaration for main in library;Only doing an extern for the same)" */
    main();
/* USER CODE BEGIN (27) */
/* USER CODE END */
/*SAFETYMCUSW 122 S MR:20.11 <APPROVED> "Startup code(exit and abort need to be present)" */
    exit(0);


/* USER CODE BEGIN (28) */
/* USER CODE END */

}

/* USER CODE BEGIN (29) */
/* USER CODE END */



/* USER CODE BEGIN (30) */
/* USER CODE END */
