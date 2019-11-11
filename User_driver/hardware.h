/*
 * hardware.h
 *
 *  Created on: 2019年6月17日
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


void    HardwareInit(void);
//========================================================================
// 函数: void  delay_us(uint32 us)
// 描述: 延时函数。
// 参数: us,要延时的us数.
// 返回: none.
// 版本: VER1.0
// 备注:
//========================================================================
void  DelayUs(unsigned int us);
void  DelayNs(unsigned int  us);
void  Delayns(void);

#endif /* USER_DRIVER_HARDWARE_H_ */
