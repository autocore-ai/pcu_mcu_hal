/******************************************************************
FileName   :mx25L6406e.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-31
****************************************************************/

#ifndef USER_DRIVER_MX25L6406E_H_
#define USER_DRIVER_MX25L6406E_H_

#define     WEL         0x02
#define     WIP         0x01
#define     PAGESIZE    0x100
#define     SECTORSIZE  0x1000
#define     BLOCKSIZE   0x10000
#define     CHIPSIZE    0x100000
#define     NORBUFSIZE  256

#define     SST25VF080B 0xBF258E
#define     SST25VF080B_ID  0xBF8E

#define     WREN        0x0006
#define     WRDI        0x0004
#define     RDSR        0x0005
#define     WRSR        0x0001

/******************************************************
*Name    :  FreeRTOS_NorInit
*Function:  Nor Flash  初始化函数
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/
uint8    FreeRTOS_NorInit(void);

/******************************************************
*Name    :  NorReadID
*Function:  read  id
*Params  :
*Return  :  DEVICE ID
*******************************************************/
uint32    NorReadID(void);

/******************************************************
*Name    :  NorReadID
*Function:  read  id
*Params  :
*Return  :  状态值
*******************************************************/
uint32    NorReadMID(void);

/******************************************************
*Name    : NorReadByte
*Function: nor flash 读字节函数（从addr地址读一个字节数据）
*Params  :
*Return  : 字节内容
*******************************************************/
uint8   NorReadByte(uint32 addr);

/******************************************************
*Name    : NorFastRead
*Function: nor flash 读字节函数（从addr地址读size字节数据,放到 buf中）
*Params  : addr : flash 地址
*Params  : buf  : 数据缓冲区
*Params  : size : 要读取数据的大小
*Return  :
*******************************************************/
uint8   NorFastRead(uint32 addr,uint16 *buf, uint16 size);

/******************************************************
*Name    : NorSectorErase
*Function: nor flash 扇区擦除函数
*Params  : sector : flash 扇区号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorSectorErase(uint16 sector);

/******************************************************
*Name    : NorBlockErase
*Function: nor flash 块擦除函数
*Params  : block : flash 块号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorBlockErase(uint8 block);

/******************************************************
*Name    : NorChipErase
*Function: nor flash 擦除函数
*Params  : block : flash 块号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorChipErase(void);

/******************************************************
*Name    : NorChipErase
*Function: nor flash 擦除函数
*Params  : block : flash 块号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorPageWrite(uint16 page, uint16 *buf);

/******************************************************
*Name    : NorWriteAuto
*Function: nor flash 连续写数据函数
*Params  : addr : flash 地址
*Params  : buf  数据缓冲区
*Params  : len 数据长度
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorWriteAuto(uint32 addr, uint16 *buf,uint16 len);

/******************************************************
*Name    : NorWriteByte
*Function: nor flash 写字节函数
*Params  : addr : 地址
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorWriteByte(uint32 addr, uint16 data);

void    NorTest(void);

#endif /* USER_DRIVER_MX25L6406E_H_ */
