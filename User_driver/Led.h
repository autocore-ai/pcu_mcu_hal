/*
 * Led.h
 *
 *  Created on: 2019年9月10日
 *      Author: zhenh
 */

#ifndef USER_DRIVER_LED_H_
#define USER_DRIVER_LED_H_

#define RIGHT_TOP       14U
#define RIGHT_BOTTOM    25U
#define LEFT_TOP        18U
#define LEFT_BOTTOM     29U
#define P3100M_STATUS   30U
#define P2100M_STATUS   16U
#define P1100M_STATUS   27U

/******************************************************
*Name    :  LedInit
*Function:  led  初始化函数
*Params  :
*Return  :
*******************************************************/
void    LedInit(void);

/******************************************************
*Name    : LedRightTop_on
*Function: Right Top Led 点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_on(void);

/******************************************************
*Name    : LedRightTop_off
*Function: Right Top Led 熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_off(void);


/******************************************************
*Name    : LedRightBottom_on
*Function: Right bottom Led 点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_on(void);

/******************************************************
*Name    : LedRightBottom_off
*Function: Right Bottom Led 熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_off(void);

/******************************************************
*Name    : LedLeftTop_on
*Function: Left Top Led 点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_on(void);

/******************************************************
*Name    : LedLeftTop_off
*Function: Left Top Led 熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_off(void);

/******************************************************
*Name    : LedLeftBottom_on
*Function: Left bottom Led 点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_on(void);

/******************************************************
*Name    : LedLeftBottom_off
*Function: Left Bottom Led 熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_off(void);



/******************************************************
*Name    : LedP1Status_on
*Function: AVB P1 口状态灯点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_on(void);

/******************************************************
*Name    : LedP1Status_off
*Function: AVB P1 口状态灯熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_off(void);


/******************************************************
*Name    : LedP2Status_on
*Function: AVB P2 口状态灯点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_on(void);

/******************************************************
*Name    : LedP2Status_off
*Function: AVB P2 口状态灯熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_off(void);

/******************************************************
*Name    : LedP3Status_on
*Function: AVB P3 口状态灯点亮函数
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_on(void);

/******************************************************
*Name    : LedP3Status_off
*Function: AVB P3 口状态灯熄灭函数
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_off(void);


#endif /* USER_DRIVER_LED_H_ */
