/******************************************************************
FileName   :Lin_driver.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-10-25
****************************************************************/

#ifndef USER_DRIVER_LIN_DRIVER_H_
#define USER_DRIVER_LIN_DRIVER_H_

#include    "HL_reg_lin.h"

#define Lin2_low_ch        118
#define BIT(A,B)     ((uint8)((A>>B)&0x01))

typedef struct _LinMsg{
    uint8   lin_id;            // linID
    uint8   len;               // 数据长度，0---7，表示要发送或要接收多少个数据
    uint8   data[8];
}linMsg;

/******************************************************
*Name    :  FreeRTOS_LinInit
*Function:  Lin  初始化函数
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/
uint8    FreeRTOS_LinInit(void);

/******************************************************
*Name    :  LinIdCalcParity
*Function:  LIN id 校验位计算
*Params  :  id : Lin id
*Return  :  加了校验位的 ID
*******************************************************/
uint8   LinIdCalcParity(uint8 id);

/*******************************************************************************************
*Name    :  LinReadData
*Function:  LIN 读数据函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2: lin2
*Return  :  linMsg
***********************************************************************************************/
linMsg  LinReadData(linBASE_t *lin );

/*******************************************************************************************
*Name    :  LinSendData
*Function:  LIN 读数据函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2:  lin2
*Return  :  uint8_t : 1--发送成功       0---失败
***********************************************************************************************/
void    LinSendData(linBASE_t *lin, linMsg *msg, uint8 maskid);

/*******************************************************************************************
*Name    :  LinSendHeader
*Function:  LIN 发送帧头函数
*Params  :  lin : LIN模块基地址指针， linREG1: lin1 , linREG2:  lin2\
*Params  :  id , 帧 ID
*Return  :  void
***********************************************************************************************/
void    LinSendHeader(linBASE_t *lin, uint8 id);

/******************************************************
*Name    :  Lin2Init
*Function:  Lin2  初始化函数
*Params  :
*Return  :  void
*******************************************************/
void    Lin2Init(void);

#endif /* USER_DRIVER_LIN_DRIVER_H_ */
