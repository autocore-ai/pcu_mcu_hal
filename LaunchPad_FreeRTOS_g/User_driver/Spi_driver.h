/******************************************************************
FileName   :Spi_driver.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-05
****************************************************************/

#ifndef USER_DRIVER_SPI_DRIVER_H_
#define USER_DRIVER_SPI_DRIVER_H_

#include "HL_spi.h"

/******************************************************
*Name    :  Spi1Init
*Function:  配置SPI1寄存器
*Params  :
*Return  :  void
*******************************************************/
void Spi1Init(void);

/******************************************************
*Name    :  Spi1Init
*Function:  配置SPI1寄存器
*Params  :
*Return  :  void
*******************************************************/
void Spi2Init(void);

/******************************************************
*Name    :  SpiTrdy
*Function:  判断发送缓冲区是否空
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Return  :  t ,返回发送缓冲区状态   =0 发送缓冲区满    =1 发送缓冲区空
*******************************************************/
uint8 SpiTrdy(spiBASE_t *spi);

/******************************************************
*Name    :  SpiRrdy
*Function:  判断接收缓冲区是否有数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Return  :  t ,返回发送缓冲区状态   =0 接收缓冲区空    =1 接收缓冲区有数据
*******************************************************/
uint8  SpiRrdy(spiBASE_t *spi);

/******************************************************
*Name    :  SpiSendWord
*Function:  发送一个字函数
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  srcbuf : 数据缓冲区
*Params  :  num : 要发送的数据个数
*Return  :  发送状态
*******************************************************/
uint32  SpiSend(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * srcbuf, uint16 num );

/******************************************************
*Name    :  SpiSendForm
*Function:  发送一个字函数
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  addrbuf : 地址、命令缓冲区
*Params  :  size    : 地址、命令长度
*Params  :  srcbuf : 数据缓冲区
*Params  :  num : 要发送的数据个数
*Return  :  发送状态
*******************************************************/
uint32  SpiSendForm(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 *addrbuf, uint16 size, uint16 * srcbuf, uint16 num );

/******************************************************
*Name    :  SpiRecvWord
*Function:  发送一个字函数
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : SPI通道参数设置
*Params  :  destbuf : 数据缓冲区
*Params  :  num : 要接收的数据个数
*Return  :  发送状态
*******************************************************/
uint32 SpiRecv(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * destbuf, uint16 num );

/******************************************************
*Name    :  SpiWrite
*Function:  spi 写数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : 数据缓冲区
*Params  :  size : 要写的数据个数
*Return  :  发送状态
*******************************************************/
uint32 SpiWrite(spiBASE_t *spi, uint16  *buf, uint16 size);

/******************************************************
*Name    :  SpiWriteData
*Function:  spi 写数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  addrbuf : 地址、命令缓冲区
*Params  :  size   : 地址、命令数据长度
*Params  :  srcbuf : 数据缓冲区
*Params  :  num : 要写的数据个数
*Return  :  发送状态
*******************************************************/
uint32 SpiWriteData(spiBASE_t *spi, uint16 *addrbuf, uint16 size, uint16  *srcbuf, uint16 num);


/******************************************************
*Name    :  OnlyRead
*Function:  直接从SPI总线上读数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : 数据缓冲区
*Params  :  size : 要读的数据个数
*Return  :  发送状态
*******************************************************/
uint32 OnlyRead(spiBASE_t *spi, uint16 *buf, uint16 size);

/******************************************************
*Name    :  SpiRead
*Function:  spi 读数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  addrbuf : 目标地址数据缓冲区
*Params  :  num : 要写的目标地址数据个数
*Params  :  buf : 读出数据存储缓冲区
*Params  :  size: 要读数据的个数
*Return  :  发送状态
*******************************************************/
uint32 SpiRead(spiBASE_t *spi, uint16 *addrbuf, uint16 num, uint16 *buf ,uint16 size);

/******************************************************
*Name    :  FreeRTOS_NetSwitchInit
*Function:  net switch 初始化函数
*Params  :
*Return  :
*******************************************************/
void    FreeRTOS_NetSwitchInit();

uint32  SpiWriteRead(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * addrbuf,  uint16 * destbuf );

#endif /* USER_DRIVER_SPI_DRIVER_H_ */
