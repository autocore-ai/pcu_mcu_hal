/*
 * watchdog_driver.h
 *
 *  Created on: 2019Äê4ÔÂ23ÈÕ
 *      Author: zhenh
 */

#ifndef USER_DRIVER_WATCHDOG_DRIVER_H_
#define USER_DRIVER_WATCHDOG_DRIVER_H_

#include "HL_reg_rti.h"

typedef enum dwdViolationTag
{
    NoTime_Violation = 0U,
    Time_Window_Violation = 1U,
    EndTime_Window_Violation = 2U,
    StartTime_Window_Violation = 3U,
    Key_Seq_Violation = 4U
}dwdViolation_t;

/* USER CODE BEGIN (2) */
/* USER CODE END */

/** @enum dwdResetStatusTag
*   @brief DWD Reset status
*/
typedef enum dwdResetStatusTag
{
    No_Reset_Generated = 0U,
    Reset_Generated    = 1U
}dwdResetStatus_t;

/* USER CODE BEGIN (3) */
/* USER CODE END */

/** @enum dwwdReactionTag
*   @brief DWWD Reaction on vioaltion
*/
typedef enum dwwdReactionTag
{
    Generate_Reset = 0x00000005U,
    Generate_NMI   = 0x0000000AU
}dwwdReaction_t;

/* USER CODE BEGIN (4) */
/* USER CODE END */

/** @enum dwwdWindowSizeTag
*   @brief DWWD Window size
*/
typedef enum dwwdWindowSizeTag
{
    Size_100_Percent   = 0x00000005U,
    Size_50_Percent    = 0x00000050U,
    Size_25_Percent    = 0x00000500U,
    Size_12_5_Percent  = 0x00005000U,
    Size_6_25_Percent  = 0x00050000U,
    Size_3_125_Percent = 0x00500000U
}dwwdWindowSize_t;

/* USER CODE BEGIN (5) */
/* USER CODE END */

/* Configuration registers */
typedef struct rti_config_reg
{
    uint32 CONFIG_GCTRL;
    uint32 CONFIG_TBCTRL;
    uint32 CONFIG_CAPCTRL;
    uint32 CONFIG_COMPCTRL;
    uint32 CONFIG_UDCP0;
    uint32 CONFIG_UDCP1;
    uint32 CONFIG_UDCP2;
    uint32 CONFIG_UDCP3;
} rti_config_reg_t;

void prvSetupTimerInterrupt(void);
void Comp2Init(void);
void FreeRTOS_WatchdogInit(void);
void dwwdInit(rtiBASE_t *rtiREG, dwwdReaction_t Reaction, uint16 dwdPreload, dwwdWindowSize_t Window_Size);
void dwdInit(rtiBASE_t *rtiREG, uint16 dwdPreload);
void dwdReset(rtiBASE_t *rtiREG);
void dwdGenerateSysReset(rtiBASE_t *rtiREG);
void dwdCounterEnable(rtiBASE_t *rtiREG);
void WatchdogStart(rtiBASE_t *rtiREG);
void FreeRTOS_TimerInit(void);

#endif /* USER_DRIVER_WATCHDOG_DRIVER_H_ */
