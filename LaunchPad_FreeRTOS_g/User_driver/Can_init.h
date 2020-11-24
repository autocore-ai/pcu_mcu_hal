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
    uint8   MDir;       //0 ：mask无效   1：mask有效
    uint32  MaskID;     // filtering ID
    uint8   Xtd;        //0: 标准帧      1：扩展帧
    uint8   Dir;        //0: Receive  1: Transmit
    uint32  ArbID;      //Message ID
}canMask;

/******************************************************************
*Name    :  can_init
*Function:  can 初始化函数
*Params  :  void
*Return  :  void
*******************************************************************/

void    can_init(void);
/******************************************************************
*Name    :  can_setup
*Function:  can 通道配置函数
*Params  :  canreg  can通道基地址指针
*Params  :  pmask   can通道配置参数指针
*Return  :  void
*******************************************************************/
void can_setup(canBASE_t *canreg, canMask  *pmask);

#endif /* USER_DRIVER_CAN_INIT_H_ */
