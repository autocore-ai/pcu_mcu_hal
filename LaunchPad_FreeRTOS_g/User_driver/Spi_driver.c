/******************************************************************
FileName   :Spi_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-05
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_reg_spi.h"
#include "Spi_driver.h"
#include "HL_spi.h"

uint8 SPIDAT[5][4] = {
                /*      cshold    wdelay   dataformat       csnum      */
                      { 1,          0,          0,            0x1d, },
                      { 1,          0,          0,            2,    },
                      { 1,          0,          0,            1+1,  },
                      { 1,          0,          0,            1+1,  },
                      { 1,          0,          0,            1+1,  },
};

/******************************************************
*Name    :  Spi1Init
*Function:  配置SPI1寄存器
*Params  :
*Return  :  void
*******************************************************/
void Spi1Init(void)
{
    /** @b initialize @b SPI1 */

    /** bring SPI out of reset */
    spiREG1->GCR0 = 0U;
    spiREG1->GCR0 = 1U;

    /** SPI1 master mode and clock configuration */
    spiREG1->GCR1 = (spiREG1->GCR1 & 0xFeFeFeFcU) | ((uint32)((uint32)1U << 1U)     /* Disable lookback ,CLOKMOD */
                  | 1U);                                                            /* MASTER */

    /** SPI1 enable pin configuration */
    spiREG1->INT0 = (spiREG1->INT0 & 0xFEFFFFFFU)| (uint32)((uint32)1U << 24U);     /* ENABLE HIGHZ */

    /** - Delays */
    spiREG1->DELAY = (uint32)((uint32)4U << 24U)  /* C2TDELAY */
                   | (uint32)((uint32)5U << 16U)  /* T2CDELAY */
                   | (uint32)((uint32)0U << 8U)   /* T2EDELAY */
                   | (uint32)((uint32)0U << 0U);  /* C2EDELAY */

    /** - Data Format 0 */
    spiREG1->FMT0 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)14U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)16U << 0U);  /* data word length */

    /** - Data Format 1 */
    spiREG1->FMT1 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)14U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)16U << 0U);  /* data word length */

    /** - Data Format 2 */
    spiREG1->FMT2 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)14U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)16U << 0U);  /* data word length */

    /** - Data Format 3 */
    spiREG1->FMT3 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)14U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)16U << 0U);  /* data word length */

    /** - set interrupt levels */
    spiREG1->LVL = (uint32)((uint32)0U << 9U)  /* TXINT */
                 | (uint32)((uint32)0U << 8U)  /* RXINT */
                 | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                 | (uint32)((uint32)0U << 4U)  /* BITERR */
                 | (uint32)((uint32)0U << 3U)  /* DESYNC */
                 | (uint32)((uint32)0U << 2U)  /* PARERR */
                 | (uint32)((uint32)0U << 1U) /* TIMEOUT */
                 | (uint32)((uint32)0U << 0U);  /* DLENERR */

    /** - clear any pending interrupts */
    spiREG1->FLG |= 0xFFFFU;

    /** - enable interrupts */
    spiREG1->INT0 = (spiREG1->INT0 & 0xFFFF0000U)
                  | (uint32)((uint32)0U << 9U)  /* TXINT */
                  | (uint32)((uint32)0U << 8U)  /* RXINT */
                  | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                  | (uint32)((uint32)0U << 4U)  /* BITERR */
                  | (uint32)((uint32)0U << 3U)  /* DESYNC */
                  | (uint32)((uint32)0U << 2U)  /* PARERR */
                  | (uint32)((uint32)0U << 1U) /* TIMEOUT */
                  | (uint32)((uint32)0U << 0U);  /* DLENERR */

    /** @b initialize @b SPI1 @b Port */

    /** - SPI1 Port output values */
    spiREG1->PC3 =    (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)1U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)1U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)1U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)1U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)0U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)0U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)0U << 25U); /* SOMI[1] */

    /** - SPI1 Port direction */
    spiREG1->PC1  =   (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)1U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)0U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)0U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)0U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)0U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)0U << 25U); /* SOMI[1] */

    /** - SPI1 Port open drain enable */
    spiREG1->PC6  =   (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)0U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)0U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)0U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)0U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)0U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)0U << 25U); /* SOMI[1] */

    /** - SPI1 Port pullup / pulldown selection */
    spiREG1->PC8  =   (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)1U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)1U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)1U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)1U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)1U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)1U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)1U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)1U << 25U); /* SOMI[1] */

    /** - SPI1 Port pullup / pulldown enable*/
    spiREG1->PC7  =   (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)1U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)1U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)1U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)1U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)1U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)1U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)1U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)1U << 25U); /* SOMI[1] */

    /* SPI1 set all pins to functional */
    spiREG1->PC0  =   (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 2U)  /* SCS[2] */
                    | (uint32)((uint32)1U << 3U)  /* SCS[3] */
                    | (uint32)((uint32)0U << 4U)  /* SCS[4] */
                    | (uint32)((uint32)0U << 5U)  /* SCS[5] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO[0] */
                    | (uint32)((uint32)1U << 11U)  /* SOMI[0] */
                    | (uint32)((uint32)0U << 17U)  /* SIMO[1] */
                    | (uint32)((uint32)0U << 25U); /* SOMI[1] */

    /** - Finally start SPI1 */
    spiREG1->GCR1 = (spiREG1->GCR1 & 0xFEFFFFFFU) | 0x01000000U;
}

/******************************************************
*Name    :  Spi1Init
*Function:  配置SPI1寄存器
*Params  :
*Return  :  void
*******************************************************/
void Spi2Init(void)
{
    /** @b initialize @b SPI2 */

    /** bring SPI out of reset */
    spiREG2->GCR0 = 0U;
    spiREG2->GCR0 = 1U;

    /** SPI2 master mode and clock configuration */
    spiREG2->GCR1 = (spiREG2->GCR1 & 0xFFFFFFFCU) | ((uint32)((uint32)1U << 1U)  /* CLOKMOD */
                  | 1U);  /* MASTER */

    /** SPI2 enable pin configuration */
    spiREG2->INT0 = (spiREG2->INT0 & 0xFEFFFFFFU)| (uint32)((uint32)0U << 24U);  /* ENABLE HIGHZ */

    /** - Delays */
    spiREG2->DELAY = (uint32)((uint32)0U << 24U)  /* C2TDELAY */
                   | (uint32)((uint32)0U << 16U)  /* T2CDELAY */
                   | (uint32)((uint32)0U << 8U)   /* T2EDELAY */
                   | (uint32)((uint32)0U << 0U);  /* C2EDELAY */

    /** - Data Format 0 */
    spiREG2->FMT0 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)2U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)8U << 0U);  /* data word length */
    /** - Data Format 1 */
    spiREG2->FMT1 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)2U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)8U << 0U);  /* data word length */

    /** - Data Format 2 */
    spiREG2->FMT2 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)2U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)8U << 0U);  /* data word length */

    /** - Data Format 3 */
    spiREG2->FMT3 = (uint32)((uint32)0U << 24U)  /* wdelay */
                  | (uint32)((uint32)0U << 23U)  /* parity Polarity */
                  | (uint32)((uint32)0U << 22U)  /* parity enable */
                  | (uint32)((uint32)0U << 21U)  /* wait on enable */
                  | (uint32)((uint32)0U << 20U)  /* shift direction */
                  | (uint32)((uint32)0U << 17U)  /* clock polarity */
                  | (uint32)((uint32)0U << 16U)  /* clock phase */
                  | (uint32)((uint32)2U << 8U) /* baudrate prescale */
                  | (uint32)((uint32)8U << 0U);  /* data word length */

    /** - set interrupt levels */
    spiREG2->LVL = (uint32)((uint32)0U << 9U)  /* TXINT */
                 | (uint32)((uint32)0U << 8U)  /* RXINT */
                 | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                 | (uint32)((uint32)0U << 4U)  /* BITERR */
                 | (uint32)((uint32)0U << 3U)  /* DESYNC */
                 | (uint32)((uint32)0U << 2U)  /* PARERR */
                 | (uint32)((uint32)0U << 1U) /* TIMEOUT */
                 | (uint32)((uint32)0U << 0U);  /* DLENERR */

    /** - clear any pending interrupts */
    spiREG2->FLG |= 0xFFFFU;

    /** - enable interrupts */
    spiREG2->INT0 = (spiREG2->INT0 & 0xFFFF0000U)
                  | (uint32)((uint32)0U << 9U)  /* TXINT */
                  | (uint32)((uint32)0U << 8U)  /* RXINT */
                  | (uint32)((uint32)0U << 6U)  /* OVRNINT */
                  | (uint32)((uint32)0U << 4U)  /* BITERR */
                  | (uint32)((uint32)0U << 3U)  /* DESYNC */
                  | (uint32)((uint32)0U << 2U)  /* PARERR */
                  | (uint32)((uint32)0U << 1U) /* TIMEOUT */
                  | (uint32)((uint32)0U << 0U);  /* DLENERR */

    /** @b initialize @b SPI2 @b Port */

    /** - SPI2 Port output values */
    spiREG2->PC3 =    (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /** - SPI2 Port direction */
    spiREG2->PC1  =   (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /** - SPI2 Port open drain enable */
    spiREG2->PC6  =   (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /** - SPI2 Port pullup / pulldown selection */
    spiREG2->PC8  =   (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)1U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)1U << 11U); /* SOMI */

    /** - SPI2 Port pullup / pulldown enable*/
    spiREG2->PC7  =   (uint32)((uint32)0U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)0U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)0U << 9U)  /* CLK */
                    | (uint32)((uint32)0U << 10U)  /* SIMO */
                    | (uint32)((uint32)0U << 11U); /* SOMI */

    /* SPI2 set all pins to functional */
    spiREG2->PC0  =   (uint32)((uint32)1U << 0U)  /* SCS[0] */
                    | (uint32)((uint32)1U << 1U)  /* SCS[1] */
                    | (uint32)((uint32)0U << 8U)  /* ENA */
                    | (uint32)((uint32)1U << 9U)  /* CLK */
                    | (uint32)((uint32)1U << 10U)  /* SIMO */
                    | (uint32)((uint32)1U << 11U); /* SOMI */

    /** - Finally start SPI2 */
    spiREG2->GCR1 = (spiREG2->GCR1 & 0xFEFFFFFFU) | 0x01000000U;
}




/******************************************************
*Name    :  SpiSendWord
*Function:  发送一个字函数
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  srcbuf : 数据缓冲区
*Params  :  num : 要发送的数据个数
*Return  :  发送状态
*******************************************************/
uint32  SpiSend(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * srcbuf, uint16 num )
{
    volatile uint32_t SpiBuf;
    uint16 Tx_Data;

    uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
    uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
    uint8  DataFormat = dataconfig_t->DFSEL;
    uint8  ChipSelect = dataconfig_t->CSNR;

    while(num != 0U)
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
           break;
        }
        if(num == 1U)
        {
            Chip_Select_Hold = 0;
        }

        Tx_Data = *srcbuf;

        spi->DAT1 =  ((uint32)DataFormat << 24U) |
                     ((uint32)ChipSelect << 16U) |
                     (WDelay)           |
                     (Chip_Select_Hold) |
                     (uint32)Tx_Data;
        srcbuf++;
        while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } /* Wait */

        SpiBuf = spi->BUF;

        num--;
    }

    return spi->FLG & 0xFFU;
}

/******************************************************
*Name    :  SpiSendForm
*Function:  往 addr 地址中写入数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  addrbuf : 地址、命令缓冲区
*Params  :  size    : 地址、命令长度
*Params  :  srcbuf : 数据缓冲区
*Params  :  num : 要发送的数据个数
*Return  :  发送状态
*******************************************************/

uint32  SpiSendForm(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 *addrbuf, uint16 size, uint16 * srcbuf, uint16 num )
{
    volatile uint32_t SpiBuf;
    uint16 Tx_Data;

    uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
    uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
    uint8  DataFormat = dataconfig_t->DFSEL;
    uint8  ChipSelect = dataconfig_t->CSNR;

    while(size != 0U)
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
           break;
        }

        Tx_Data = *addrbuf & 0x00FF;

        spi->DAT1 =  ((uint32)DataFormat << 24U) |
                     ((uint32)ChipSelect << 16U) |
                     (WDelay)           |
                     (Chip_Select_Hold) |
                     (uint32)Tx_Data;
        addrbuf++;

        while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } // Wait

        SpiBuf = spi->BUF;

        size--;
    }

    while(num != 0U)
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
           break;
        }
        if(num == 1U)
        {
            Chip_Select_Hold = 0;
        }

        Tx_Data = *srcbuf & 0x00FF;

        spi->DAT1 =  ((uint32)DataFormat << 24U) |
                     ((uint32)ChipSelect << 16U) |
                     (WDelay)           |
                     (Chip_Select_Hold) |
                     (uint32)Tx_Data;
        srcbuf++;

        while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } // Wait

        SpiBuf = spi->BUF;

        num--;
    }

    return spi->FLG & 0xFFU;
}

/******************************************************
*Name    :  SpiRecv
*Function:  发送一个字函数
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : SPI通道参数设置
*Params  :  destbuf : 数据缓冲区
*Params  :  num : 要接收的数据个数
*Return  :  发送状态
*******************************************************/
uint32 SpiRecv(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * destbuf, uint16 num )
{
    uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
    uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
    uint8  DataFormat = dataconfig_t->DFSEL;
    uint8  ChipSelect = dataconfig_t->CSNR;


    while(num != 0U)
    {
        if((spi->FLG & 0x000000FFU) !=0U)
        {
          break;
        }
        if(num == 1U)
        {
            Chip_Select_Hold = 0U;
        }

        spi->DAT1 = ((uint32)DataFormat << 24U) |
                    ((uint32)ChipSelect << 16U) |
                    (WDelay)            |
                    (Chip_Select_Hold)  |
                    (0x00000000U);

        while((spi->FLG & 0x00000100U) != 0x00000100U) {        } /* Wait */

        *destbuf = (uint16)spi->BUF;
        destbuf++;
        num--;
    }

    return (spi->FLG & 0xFFU);
}

/******************************************************
*Name    :  SpiRecvFrom
*Function:  SPI从地址中读数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  addrbuf : 目标地址数据缓冲区
*Params  :  num : 要发送的目标地址数据个数
*Params  :  destbuf : 接收缓冲区
*Params  :  cnt  : 接收数据的个数
*Return  :  发送状态
*******************************************************/
uint32  SpiRecvFrom(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 * addrbuf, uint16 num, uint16 * destbuf, uint16 cnt )
{
     volatile uint32_t SpiBuf;
     uint16 Tx_Data;

     uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
     uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
     uint8  DataFormat = dataconfig_t->DFSEL;
     uint8  ChipSelect = dataconfig_t->CSNR;

     while(num != 0U)
     {
         if((spi->FLG & 0x000000FFU) !=0U)
         {
            break;
         }

         Tx_Data = *addrbuf;

         spi->DAT1 = ((uint32)DataFormat << 24U) |
                     ((uint32)ChipSelect << 16U) |
                     (WDelay)            |
                     (Chip_Select_Hold)  |
                     (uint32)Tx_Data;
         addrbuf++;
         while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } /* Wait */
         SpiBuf = spi->BUF;

         num--;
     }

     while(cnt != 0U)
     {
         if((spi->FLG & 0x000000FFU) !=0U)
         {
           break;
         }
         if(cnt == 1U)
         {
             Chip_Select_Hold = 0U;
         }

         spi->DAT1 = ((uint32)DataFormat << 24U) |
                     ((uint32)ChipSelect << 16U) |
                     (WDelay)            |
                     (Chip_Select_Hold)  |
                     (0x00000000U);

         while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } /* Wait */

         *destbuf = (uint16)spi->BUF;
         destbuf++;
         cnt--;
     }
     return (spi->FLG & 0xFFU);
}
/******************************************************
*Name    :  SpiWrite
*Function:  spi 写数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : 数据缓冲区
*Params  :  size : 要写的数据个数
*Return  :  发送状态
*******************************************************/
uint32 SpiWrite(spiBASE_t *spi, uint16  *buf, uint16 size)
{
    spiDAT1_t dataconfig_t;
    uint32 errors;
    uint8 index;
    index = (spi == spiREG1) ? 0U :((spi==spiREG2) ? 1U : ((spi==spiREG3) ? 2U:((spi==spiREG4) ? 3U:4U)));

    dataconfig_t.CS_HOLD = SPIDAT[index][0];
    dataconfig_t.WDEL = SPIDAT[index][1];
    dataconfig_t.DFSEL = SPIDAT[index][2];
    dataconfig_t.CSNR = SPIDAT[index][3];

    errors =  SpiSend(spi, &dataconfig_t, buf ,size);

    return (errors);
}


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

uint32 SpiWriteData(spiBASE_t *spi, uint16 *addrbuf, uint16 size, uint16  *srcbuf, uint16 num)
{
    spiDAT1_t dataconfig_t;
    uint32 errors;
    uint8 index;
    index = (spi == spiREG1) ? 0U :((spi==spiREG2) ? 1U : ((spi==spiREG3) ? 2U:((spi==spiREG4) ? 3U:4U)));

    dataconfig_t.CS_HOLD = SPIDAT[index][0];
    dataconfig_t.WDEL = SPIDAT[index][1];
    dataconfig_t.DFSEL = SPIDAT[index][2];
    dataconfig_t.CSNR = SPIDAT[index][3];

    errors =  SpiSendForm(spi, &dataconfig_t, addrbuf, size, srcbuf ,num);

    return (errors);
}

/******************************************************
*Name    :  OnlyRead
*Function:  直接从SPI总线上读数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  buf : 数据缓冲区
*Params  :  size : 要读的数据个数
*Return  :  发送状态
*******************************************************/

uint32 OnlyRead(spiBASE_t *spi, uint16 *buf, uint16 size)
{
    spiDAT1_t dataconfig_t;
    uint32_t errors;

    uint8 index;
    index = (spi == spiREG1) ? 0U :((spi==spiREG2) ? 1U : ((spi==spiREG3) ? 2U:((spi==spiREG4) ? 3U:4U)));

    dataconfig_t.CS_HOLD = SPIDAT[index][0];
    dataconfig_t.WDEL = SPIDAT[index][1];
    dataconfig_t.DFSEL = SPIDAT[index][2];
    dataconfig_t.CSNR = SPIDAT[index][3];

    errors = SpiRecv(spi, &dataconfig_t, buf, size);

    return (errors);
}

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
uint32 SpiRead(spiBASE_t *spi, uint16 *addrbuf, uint16 num, uint16 *buf ,uint16 size)
{
    spiDAT1_t dataconfig_t;
    uint32_t errors;

    uint8 index;
    index = (spi == spiREG1) ? 0U :((spi==spiREG2) ? 1U : ((spi==spiREG3) ? 2U:((spi==spiREG4) ? 3U:4U)));

    dataconfig_t.CS_HOLD = SPIDAT[index][0];
    dataconfig_t.WDEL = SPIDAT[index][1];
    dataconfig_t.DFSEL = SPIDAT[index][2];
    dataconfig_t.CSNR = SPIDAT[index][3];

    errors = SpiRecvFrom(spi, &dataconfig_t, addrbuf,num,buf, size);
    return (errors);
}

/******************************************************
*Name    :  SpiRecvFrom
*Function:  SPI从地址中读数据
*Params  :  spi SPI总线基地址 ： spiREG1  spiREG2 spiREG3 spiREG4 spiREG5
*Params  :  dataconfig_t : 发送通道参数设置
*Params  :  addrbuf : 目标地址数据缓冲区
*Params  :  num : 要发送的目标地址数据个数
*Params  :  destbuf : 接收缓冲区
*Params  :  cnt  : 接收数据的个数
*Return  :  发送状态
*******************************************************/
uint32  SpiWriteRead(spiBASE_t *spi,spiDAT1_t *dataconfig_t, uint16 *addrbuf,  uint16 * destbuf )
{
     volatile uint32_t SpiBuf;
     uint16 Tx_Data;

     uint32 Chip_Select_Hold = (dataconfig_t->CS_HOLD) ? 0x10000000U : 0U;
     uint32 WDelay = (dataconfig_t->WDEL) ? 0x04000000U : 0U;
     uint8  DataFormat = dataconfig_t->DFSEL;
     uint8  ChipSelect = dataconfig_t->CSNR;

     if((spi->FLG & 0x000000FFU) !=0U)
     {
        ;
     }

     Tx_Data = *addrbuf;

     spi->DAT1 = ((uint32)DataFormat << 24U) |
                 ((uint32)ChipSelect << 16U) |
                 (WDelay)            |
                 (Chip_Select_Hold)  |
                 (uint32)Tx_Data;
     while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } /* Wait */
     SpiBuf = spi->BUF;


     if((spi->FLG & 0x000000FFU) !=0U)
     {
       ;
     }

     Chip_Select_Hold = 0U;

     spi->DAT1 = ((uint32)DataFormat << 24U) |
                 ((uint32)ChipSelect << 16U) |
                 (WDelay)            |
                 (Chip_Select_Hold)  |
                 (0x00000000U);

     while((spi->FLG & 0x00000100U) != 0x00000100U)  {    } /* Wait */

     *destbuf = (uint16)spi->BUF;

     return (spi->FLG & 0xFFU);
}
