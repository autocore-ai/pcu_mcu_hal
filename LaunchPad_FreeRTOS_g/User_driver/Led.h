/*
 * Led.h
 *
 *  Created on: 2019��9��10��
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
#define LIN_EN          20U


/******************************************************
*Name    :  LedInit
*Function:  led  ��ʼ������
*Params  :
*Return  :
*******************************************************/
void    LedInit(void);

/******************************************************
*Name    : LedRightTop_on
*Function: Right Top Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_on(void);

/******************************************************
*Name    : LedRightTop_off
*Function: Right Top Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_off(void);


/******************************************************
*Name    : LedRightBottom_on
*Function: Right bottom Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_on(void);

/******************************************************
*Name    : LedRightBottom_off
*Function: Right Bottom Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_off(void);

/******************************************************
*Name    : LedLeftTop_on
*Function: Left Top Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_on(void);

/******************************************************
*Name    : LedLeftTop_off
*Function: Left Top Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_off(void);

/******************************************************
*Name    : LedLeftBottom_on
*Function: Left bottom Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_on(void);

/******************************************************
*Name    : LedLeftBottom_off
*Function: Left Bottom Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_off(void);



/******************************************************
*Name    : LedP1Status_on
*Function: AVB P1 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_on(void);

/******************************************************
*Name    : LedP1Status_off
*Function: AVB P1 ��״̬��Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_off(void);


/******************************************************
*Name    : LedP2Status_on
*Function: AVB P2 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_on(void);

/******************************************************
*Name    : LedP2Status_off
*Function: AVB P2 ��״̬��Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_off(void);

/******************************************************
*Name    : LedP3Status_on
*Function: AVB P3 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_on(void);

/******************************************************
*Name    : LedP3Status_off
*Function: AVB P3 ��״̬��Ϩ����
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


/******************************************************
*Name    : LinEn_on
*Function: Lin1 and Lin2  enable
*Params  :
*Return  :
*******************************************************/
void    LinEn_on(void);

/******************************************************
*Name    : LinEn_off
*Function: Lin1 and Lin2  disable
*Params  :
*Return  :
*******************************************************/
void    LinEn_off(void);

#endif /* USER_DRIVER_LED_H_ */
