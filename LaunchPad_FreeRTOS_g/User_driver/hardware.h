/*
 * hardware.h
 *
 *  Created on: 2019��6��17��
 *      Author: zhenh
 */

#ifndef USER_DRIVER_HARDWARE_H_
#define USER_DRIVER_HARDWARE_H_
/*
#include "Udp_can.h"
#include "watchdog_driver.h"
#include "IIC_driver.h"
*/
#include    "Led.h"
#include    "Sci_driver.h"
#include    "can_driver.h"
#include    "Spi_driver.h"
#include    "sja1105s.h"
#include    "tja1102.h"
#include    "Gpio_driver.h"
#include    "sdram.h"
#include    "IIC_driver.h"
#include    "MX25L6406E.h"
#include    "Adc.h"
#include    "Lin_driver.h"
#include    "Can_init.h"


void    HardwareInit(void);
//========================================================================
// ����: void  delay_us(uint32 us)
// ����: ��ʱ������
// ����: us,Ҫ��ʱ��us��.
// ����: none.
// �汾: VER1.0
// ��ע:
//========================================================================
void  DelayUs(unsigned int us);
void  DelayNs(unsigned int  us);
void  Delayns(void);

#endif /* USER_DRIVER_HARDWARE_H_ */
