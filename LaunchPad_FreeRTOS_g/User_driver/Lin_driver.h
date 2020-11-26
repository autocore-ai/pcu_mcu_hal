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
    uint8   len;               // ���ݳ��ȣ�0---7����ʾҪ���ͻ�Ҫ���ն��ٸ�����
    uint8   data[8];
}linMsg;

/******************************************************
*Name    :  FreeRTOS_LinInit
*Function:  Lin  ��ʼ������
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/
uint8    FreeRTOS_LinInit(void);

/******************************************************
*Name    :  LinIdCalcParity
*Function:  LIN id У��λ����
*Params  :  id : Lin id
*Return  :  ����У��λ�� ID
*******************************************************/
uint8   LinIdCalcParity(uint8 id);

/*******************************************************************************************
*Name    :  LinReadData
*Function:  LIN �����ݺ���
*Params  :  lin : LINģ�����ַָ�룬 linREG1: lin1 , linREG2: lin2
*Return  :  linMsg
***********************************************************************************************/
linMsg  LinReadData(linBASE_t *lin );

/*******************************************************************************************
*Name    :  LinSendData
*Function:  LIN �����ݺ���
*Params  :  lin : LINģ�����ַָ�룬 linREG1: lin1 , linREG2:  lin2
*Return  :  uint8_t : 1--���ͳɹ�       0---ʧ��
***********************************************************************************************/
void    LinSendData(linBASE_t *lin, linMsg *msg, uint8 maskid);

/*******************************************************************************************
*Name    :  LinSendHeader
*Function:  LIN ����֡ͷ����
*Params  :  lin : LINģ�����ַָ�룬 linREG1: lin1 , linREG2:  lin2\
*Params  :  id , ֡ ID
*Return  :  void
***********************************************************************************************/
void    LinSendHeader(linBASE_t *lin, uint8 id);

/******************************************************
*Name    :  Lin2Init
*Function:  Lin2  ��ʼ������
*Params  :
*Return  :  void
*******************************************************/
void    Lin2Init(void);

#endif /* USER_DRIVER_LIN_DRIVER_H_ */
