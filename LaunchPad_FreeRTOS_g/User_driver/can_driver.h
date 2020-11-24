/******************************************************************
FileName   :Can_driver.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2018-12-29
****************************************************************/

#ifndef USER_DRIVER_CAN_DRIVER_H_
#define USER_DRIVER_CAN_DRIVER_H_

#include "HL_hal_stdtypes.h"
#include "HL_reg_can.h"

#define CAN_Q_NUM    100


#define Ultra_ID1   0xD5
#define Ultra_ID2   0xD4
#define Ultra_ID3   0xD2

#define Can1_low_ch 29
#define Can2_low_ch 42
#define Can3_low_ch 55
#define Can4_low_ch 117

typedef struct _CanMsg{
    uint32 can_id;            //CANID
    uint8  dlc;               //数据长度，0---8，表示要发送或要接收多少个数据
    uint8  mask;              //IFCTL 的第22位，接受屏蔽使能位，=1使用相应的接受屏蔽； =0没有使用接受屏蔽，所有标识符位必须与接收消息相匹配
    uint8  ide;               //标识符扩展位,  =1收到的消息有扩展标识符。  =0收到的消息有一个标准标识符
    uint8  data[8];
}canMsg;


uint8       CanSendData(canBASE_t *node, uint32 messageBox, canMsg *msg,uint32_t mask_id);
canMsg      CanReadData(canBASE_t *node);
uint8_t     FreeRTOS_CanInit(void);


#endif /* USER_DRIVER_CAN_DRIVER_H_ */
