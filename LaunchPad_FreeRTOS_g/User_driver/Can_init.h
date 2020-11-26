/******************************************************************
FileName   :Can_driver.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-29
****************************************************************/

#ifndef USER_DRIVER_CAN_INIT_H_
#define USER_DRIVER_CAN_INIT_H_

typedef struct _Msk{
    uint8   MXtd;       //
    uint8   MDir;       //0 ��mask��Ч   1��mask��Ч
    uint32  MaskID;     // filtering ID
    uint8   Xtd;        //0: ��׼֡      1����չ֡
    uint8   Dir;        //0: Receive  1: Transmit
    uint32  ArbID;      //Message ID
}canMask;

/******************************************************************
*Name    :  can_init
*Function:  can ��ʼ������
*Params  :  void
*Return  :  void
*******************************************************************/

void    can_init(void);
/******************************************************************
*Name    :  can_setup
*Function:  can ͨ�����ú���
*Params  :  canreg  canͨ������ַָ��
*Params  :  pmask   canͨ�����ò���ָ��
*Return  :  void
*******************************************************************/
void can_setup(canBASE_t *canreg, canMask  *pmask);

#endif /* USER_DRIVER_CAN_INIT_H_ */
