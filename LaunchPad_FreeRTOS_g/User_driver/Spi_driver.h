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
*Function:  ����SPI1�Ĵ���
*Params  :
*Return  :  void
*******************************************************/
void Spi1Init(void);

/******************************************************
*Name    :  Spi1Init
*Function:  ����SPI1�Ĵ���
*Params  :
*Return  :  void
*******************************************************/
void Spi2Init(void);

/******************************************************
*Name    :  SpiTrdy
*Function:  �жϷ��ͻ������Ƿ��
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Return  :  t ,���ط��ͻ�����״̬   =0 ���ͻ�������    =1 ���ͻ�������
*******************************************************/
uint8 SpiTrdy(spiBASE_t *spi);

/******************************************************
*Name    :  SpiRrdy
*Function:  �жϽ��ջ������Ƿ�������
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Return  :  t ,���ط��ͻ�����״̬   =0 ���ջ�������    =1 ���ջ�����������
*******************************************************/
uint8  SpiRrdy(spiBASE_t *spi);

/******************************************************
*Name    :  SpiSendWord
*Function:  ����һ���ֺ���
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : ����ͨ����������
*Params  :  srcbuf : ���ݻ�����
*Params  :  num : Ҫ���͵����ݸ���
*Return  :  ����״̬
*******************************************************/
uint32  SpiSend(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * srcbuf, uint16 num );

/******************************************************
*Name    :  SpiSendForm
*Function:  ����һ���ֺ���
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : ����ͨ����������
*Params  :  addrbuf : ��ַ���������
*Params  :  size    : ��ַ�������
*Params  :  srcbuf : ���ݻ�����
*Params  :  num : Ҫ���͵����ݸ���
*Return  :  ����״̬
*******************************************************/
uint32  SpiSendForm(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 *addrbuf, uint16 size, uint16 * srcbuf, uint16 num );

/******************************************************
*Name    :  SpiRecvWord
*Function:  ����һ���ֺ���
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : SPIͨ����������
*Params  :  destbuf : ���ݻ�����
*Params  :  num : Ҫ���յ����ݸ���
*Return  :  ����״̬
*******************************************************/
uint32 SpiRecv(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * destbuf, uint16 num );

/******************************************************
*Name    :  SpiWrite
*Function:  spi д����
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : ���ݻ�����
*Params  :  size : Ҫд�����ݸ���
*Return  :  ����״̬
*******************************************************/
uint32 SpiWrite(spiBASE_t *spi, uint16  *buf, uint16 size);

/******************************************************
*Name    :  SpiWriteData
*Function:  spi д����
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  addrbuf : ��ַ���������
*Params  :  size   : ��ַ���������ݳ���
*Params  :  srcbuf : ���ݻ�����
*Params  :  num : Ҫд�����ݸ���
*Return  :  ����״̬
*******************************************************/
uint32 SpiWriteData(spiBASE_t *spi, uint16 *addrbuf, uint16 size, uint16  *srcbuf, uint16 num);


/******************************************************
*Name    :  OnlyRead
*Function:  ֱ�Ӵ�SPI�����϶�����
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : ���ݻ�����
*Params  :  size : Ҫ�������ݸ���
*Return  :  ����״̬
*******************************************************/
uint32 OnlyRead(spiBASE_t *spi, uint16 *buf, uint16 size);

/******************************************************
*Name    :  SpiRead
*Function:  spi ������
*Params  :  spi SPI���߻���ַ �� spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  addrbuf : Ŀ���ַ���ݻ�����
*Params  :  num : Ҫд��Ŀ���ַ���ݸ���
*Params  :  buf : �������ݴ洢������
*Params  :  size: Ҫ�����ݵĸ���
*Return  :  ����״̬
*******************************************************/
uint32 SpiRead(spiBASE_t *spi, uint16 *addrbuf, uint16 num, uint16 *buf ,uint16 size);

/******************************************************
*Name    :  FreeRTOS_NetSwitchInit
*Function:  net switch ��ʼ������
*Params  :
*Return  :
*******************************************************/
void    FreeRTOS_NetSwitchInit();

uint32  SpiWriteRead(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * addrbuf,  uint16 * destbuf );

#endif /* USER_DRIVER_SPI_DRIVER_H_ */
