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

#define     PAGESIZE        0x100
#define     SECTORSIZE_4K   0x1000
#define     BLOCKSIZE_32K   0x8000
#define     BLOCKSIZE_64K   0x10000

#define     CHIPSIZE    0x100000
#define     NORBUFSIZE  256

#define     DATASECTOR  0
#define     NORFLAGPAGE 0
#define     NORDATAPAGE 1
#define     IPOFFSET    0
#define     MACOFFSET   10
#define     IPMASK      0x58535901
#define     MACMASK     0x58535902

#define     SST25VF080B 0xBF258E
#define     SST25VF080B_ID  0xBF8E

typedef enum {

    SST_BUSY    =    0x01,        //设备忙状态标志位， 1：忙    0：不忙   （R)
    SST_WEL     =    0x02,        //设备内部写使能状态，1：写使能   0：写禁止  （R)
    SST_BP0     =    0x04,        //受保护的内存地址范围   （R/W)
    SST_BP1     =    0x08,        //受保护的内存地址范围   （R/W)
    SST_BP2     =    0x10,        //受保护的内存地址范围   （R/W)
    SST_BP3     =    0x20,        //受保护的内存地址范围   （R/W)
    SST_AAI     =    0x40,        //地址自动增加状态标志     1： AAI programming mode  0： Byte-Program mode (R)
    SST_BPL     =    0x80,        //BP0-BP3写控制位  （R/W)
}State_Mask_TypeDef;

typedef enum {
    READ            =   (uint8)(0x03),
    HIGH_SPEED_READ =   (uint8)(0x0B),
    SECTOR_ERASE_4K =   (uint8)(0x20),
    BLOCK_ERASE_32K =   (uint8)(0x52),
    BLOCK_ERASE_64K =   (uint8)(0xD8),
    CHIP_ERASE      =   (uint8)(0x60),
    BYTE_PROGRAM    =   (uint8)(0x02),
    AAI_WORD_PROGRAM=   (uint8)(0xAD),
    RDSR            =   (uint8)(0x05),
    EWSR            =   (uint8)(0x50),
    WRSR            =   (uint8)(0x01),
    WREN            =   (uint8)(0x06),
    WRDI            =   (uint8)(0x04),
    RDID            =   (uint8)(0x90),
    JEDEC_ID        =   (uint8)(0x9F),
    EBSY            =   (uint8)(0x70),
    DBSY            =   (uint8)(0x80),
}Instruct_TypeDef;

/******************************************************
*Name    :  FreeRTOS_NorInit
*Function:  Nor Flash  初始化函数
*Params  :
*Return  :  1 = init success   0 = init fail
*******************************************************/
uint8    FreeRTOS_NorInit(void);

/******************************************************
*Name    :  NorWriteStatus
*Function:  Write status reg
*Params  :  val : 要写人状态寄存器的值
*Return  :  void
*******************************************************/
void    NorWriteStatus(uint16 val);

/******************************************************
*Name    :  NorReadStatus
*Function:  read status reg
*Params  :
*Return  :  状态值
*******************************************************/
uint8    NorReadStatus(void);

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
*Name    : NorPageRead
*Function: nor flash 页读
*Params  : page : flash 页号
*Return  : 擦除状态    0---失败    1---成功
*******************************************************/
uint8   NorPageRead(uint16 page, uint16 *buf);

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

/******************************************************
*Name    : SetIpMac
*Function: 设置MCU IP地址和MAC地址
*******************************************************/
void    SetIpMac(void);

void    NorTest(void);

#endif /* USER_DRIVER_MX25L6406E_H_ */
