/*
 * Sci_driver.h
 *
 *  Created on: 2018Äê12ÔÂ27ÈÕ
 *      Author: zhenh
 */

#ifndef USER_DRIVER_SCI_DRIVER_H_
#define USER_DRIVER_SCI_DRIVER_H_

#include "HL_reg_sci.h"

#define  DEBUG         1

#define UART1_Q_NUM    1
#define UART1_Q_LEN    64


#define Uart1_low_ch        27
#define Uart3_low_ch        74
#define Uart4_low_ch        119


uint8_t FreeRTOS_UartInit(void);
void    UartSendString(sciBASE_t *sci, uint8 *msg);
void    Uart1_RecvTask(void *pvParameters);
void    Uart2_RecvTask(void *pvParameters);
void    Uart3_RecvTask(void *pvParameters);
void    Uart4_RecvTask(void *pvParameters);
void    UartSendHexU32(sciBASE_t *sci,uint32 data);
void    UartSendHexU16(sciBASE_t *sci,uint16 data);
void    UartSendMac(sciBASE_t *sci,uint8 data);
void    UartSendRtc(sciBASE_t *sci,uint8 data);
void    UartSendByte(sciBASE_t *sci,uint8 data);


#endif /* USER_DRIVER_SCI_DRIVER_H_ */
