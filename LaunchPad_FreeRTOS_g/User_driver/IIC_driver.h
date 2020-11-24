/******************************************************************
FileName   :IIC_driver.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-04-30
****************************************************************/

#ifndef USER_DRIVER_IIC_DRIVER_H_
#define USER_DRIVER_IIC_DRIVER_H_

#include "HL_reg_i2c.h"

#define     FUNC_IIC(x)     eeprom_##x
#define     EEPROM_ID       0x52

typedef struct  _Rtc_Timer {
    uint8   ryear;
    uint8   rmouth;
    uint8   rday;
    uint8   rhour;
    uint8   rminute;
    uint8   rsecond;
}Rtc_Timer;

/******************************************************
*Name    :  I2CXrdy
*Function:  判断当前是否处于发送准备状态
*Params  :  I2C IIC总线基地址 ： i2cREG1  i2cREG2
*Return  :  t ,返回总线状态，=0 总线没准备好  =1 总线已就绪
*******************************************************/
uint16 I2CXrdy(i2cBASE_t *I2C);

/******************************************************
*Name    :  I2CRrdy
*Function:  判断当前是否处于接收准备状态
*Params  :  I2C IIC总线基地址 ： i2cREG1  i2cREG2
*Return  :  t ,返回总线状态，=0 总线没准备好  =1 总线已就绪
*******************************************************/
uint16 I2CRrdy(i2cBASE_t *I2C);

/******************************************************
*Name    :  I2CBusy
*Function:  判断总线是否忙
*Params  :  I2C IIC总线基地址 ： i2cREG1  i2cREG2
*Return  :  t ,返回总线状态，=0 总线空闲  =1 总线忙
*******************************************************/
uint16 I2CBusy(i2cBASE_t *I2C);


/******************************************************
*Name    :  I2CInit
*Function:  配置i2c寄存器
*Params  :  I2C :  IIC总线基地址 ,可设置为 i2cREG1， i2cREG2;
*Params  :  speed : 总线速度（kHz)，可设置为 100，200，400
*Return  :  void
*******************************************************/
void I2CInit(i2cBASE_t *I2C, uint16 speed);

/******************************************************************
*Name    :  FreeRTOS_I2CInit
*Function:  IIC 总线初始化
*Params  :  void
*Return  :  void
******************************************************************/
void FreeRTOS_I2CInit(void);

/******************************************************
*Name    :  I2cWrite
*Function:  i2c写功能函数
*Params  :  id（uint8）:设备id
*Params  :  reg_addr(uint16):寄存器地址
*Params  :  data（uint8）:数据
*Return  :  ERR：失败         NOERR：成功
*******************************************************/
uint8 I2cWrite(i2cBASE_t *I2C,uint8 id,uint16 reg_addr,uint8 data);

/******************************************************
*Name    :  I2cRead
*Function:  i2c读功能函数
*Params  :  id（uint8）:设备id
*Params  :  reg_addr(uint16):寄存器地址
*Return  :  data：获取数据          ERR：失败
*******************************************************/
uint8  I2cRead(i2cBASE_t *I2C,uint8 id,uint16 reg_addr);

/******************************************************
*Name    :  I2cWriteData
*Function:  i2c 多个数据函数
*Params  :  id（uint8）:设备id
*Params  :  RamAddr  写数据缓冲区
*Params  :  RomAddress 从哪个地址开始写入
*Params  :  number  读取数据的个数
*Params  :  reg_addr(uint16):寄存器地址
*Return  :  data：获取数据          ERR：失败
*******************************************************/
uint8 I2cWriteData(i2cBASE_t *I2C,uint8 id,uint8  *RamAddr, uint16    RomAddress, uint8 count);

/******************************************************
*Name    :  I2cReadData
*Function:  i2c 多个数据函数
*Params  :  id（uint8）:设备id
*Params  :  RamAddr  读出数据暂存地址
*Params  :  RomAddress 从哪个地址开始读
*Params  :  number  读取数据的个数
*Params  :  reg_addr(uint16):寄存器地址
*Return  :  data：获取数据          ERR：失败
*******************************************************/
uint8 I2cReadData(i2cBASE_t *I2C,uint8 id,uint8  *RamAddr, uint16 RomAddress, uint8 count);

/******************************************************
*Name    :  RtcInit
*Function:  RTC初始化函数
*Params  :
*Return  :
*******************************************************/
void    RtcInit(void);

/******************************************************
*Name    :  RtcGetValue
*Function:  RTC 读取时间函数
*Params  :
*Return  :
*******************************************************/
Rtc_Timer   RtcGetValue(void);

/******************************************************
*Name    :  eeprom_write
*Function:  eeprom 写数据函数
*Params  :
*Return  :
*******************************************************/
uint8 FUNC_IIC(write)(uint8  data, uint16  RomAddr);

/******************************************************
*Name    :  eeprom_pagewrite
*Function:  eeprom 页写函数
*Params  :
*Return  :
*******************************************************/
uint8 FUNC_IIC(page_write)(uint8  *pdat, uint16  pagenum, uint8 count);

/******************************************************
*Name    :  eeprom_read
*Function:  eeprom 读数据函数
*Params  :
*Return  :
*******************************************************/
uint8  FUNC_IIC(read)(uint16  RomAddr);

/******************************************************
*Name    :  eeprom_pagewrite
*Function:  eeprom 页写函数
*Params  :
*Return  :
*******************************************************/
uint8  FUNC_IIC(page_read)(uint8 *pdat, uint16  pagenum, uint8 count);


void  AT24C04_Test(void);

#endif /* USER_DRIVER_IIC_DRIVER_H_ */
