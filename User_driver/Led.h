/*
 * Led.h
 *
 *  Created on: 2019Äê9ÔÂ10ÈÕ
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
#define PHY1_EN         21U
#define PHY2_EN         23U


/******************************************************
*Name    :  LedInit
*Function:  led  ³õÊ¼»¯º¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedInit(void);

/******************************************************
*Name    : LedRightTop_on
*Function: Right Top Led µãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_on(void);

/******************************************************
*Name    : LedRightTop_off
*Function: Right Top Led Ï¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_off(void);


/******************************************************
*Name    : LedRightBottom_on
*Function: Right bottom Led µãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_on(void);

/******************************************************
*Name    : LedRightBottom_off
*Function: Right Bottom Led Ï¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_off(void);

/******************************************************
*Name    : LedLeftTop_on
*Function: Left Top Led µãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_on(void);

/******************************************************
*Name    : LedLeftTop_off
*Function: Left Top Led Ï¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_off(void);

/******************************************************
*Name    : LedLeftBottom_on
*Function: Left bottom Led µãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_on(void);

/******************************************************
*Name    : LedLeftBottom_off
*Function: Left Bottom Led Ï¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_off(void);



/******************************************************
*Name    : LedP1Status_on
*Function: AVB P1 ¿Ú×´Ì¬µÆµãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_on(void);

/******************************************************
*Name    : LedP1Status_off
*Function: AVB P1 ¿Ú×´Ì¬µÆÏ¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_off(void);


/******************************************************
*Name    : LedP2Status_on
*Function: AVB P2 ¿Ú×´Ì¬µÆµãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_on(void);

/******************************************************
*Name    : LedP2Status_off
*Function: AVB P2 ¿Ú×´Ì¬µÆÏ¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_off(void);

/******************************************************
*Name    : LedP3Status_on
*Function: AVB P3 ¿Ú×´Ì¬µÆµãÁÁº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_on(void);

/******************************************************
*Name    : LedP3Status_off
*Function: AVB P3 ¿Ú×´Ì¬µÆÏ¨Ãðº¯Êý
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_off(void);

/******************************************************
*Name    : Phy1En_on
*Function: PHY1  enable
*Params  :
*Return  :
*******************************************************/
void    Phy1En_on(void);

/******************************************************
*Name    : Phy1En_off
*Function: PHY1  disable
*Params  :
*Return  :
*******************************************************/
void    Phy1En_off(void);

/******************************************************
*Name    : Phy2En_on
*Function: PHY2  enable
*Params  :
*Return  :
*******************************************************/
void    Phy2En_on(void);

/******************************************************
*Name    : Phy2En_off
*Function: PHY2  disable
*Params  :
*Return  :
*******************************************************/
void    Phy2En_off(void);

#endif /* USER_DRIVER_LED_H_ */
