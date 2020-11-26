/******************************************************************
FileName   :IIC_driver.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-04-30
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_i2c.h"
#include "HL_reg_i2c.h"
#include "HL_reg_system.h"
#include "hardware.h"

/******************************************************
*Name    :  I2CGpio
*Function:  ����i2c�ܽ�����
*Params  :  I2C :  IIC���߻���ַ ,������Ϊ i2cREG1�� i2cREG2;
*Return  :  void
*******************************************************/
void I2CGpio(i2cBASE_t *I2C)
{
    /** - set i2c pins functional mode */
    I2C->PFNC = (0U);
    /** - set i2c pins default output value */
    I2C->DOUT = (uint32)((uint32)0U << 1U)          /* sda pin */
                  | (uint32)(0U);                   /* scl pin */
    /** - set i2c pins output direction */
    I2C->DIR = (uint32)((uint32)0U << 1U)           /* sda pin */
                 | (uint32)(0U);                    /* scl pin */
    /** - set i2c pins open drain enable */
    I2C->PDR = (uint32)((uint32)0U << 1U)           /* sda pin */
                 | (uint32)(0U);                    /* scl pin */
    /** - set i2c pins pullup/pulldown enable */
    I2C->PDIS = (uint32)((uint32)0U << 1U)          /* sda pin */
                | (uint32)(0U);                     /* scl pin */
    /** - set i2c pins pullup/pulldown select */
    I2C->PSEL = (uint32)((uint32)1U << 1U)          /* sda pin */
                 | (uint32)(1U);                    /* scl pin */
    /** - set i2c pins Slew Rate Select Register */
    I2C->PSRS = (uint32)((uint32)1U << 1U)          /* sda pin */
                 | (uint32)(1U);                    /* scl pin */

}


/******************************************************
*Name    :  I2CInit
*Function:  ����i2c�Ĵ���
*Params  :  I2C :  IIC���߻���ַ ,������Ϊ i2cREG1�� i2cREG2;
*Params  :  speed : �����ٶȣ�kHz)��������Ϊ 100��200��400
*Return  :  void
*******************************************************/
void I2CInit(i2cBASE_t *I2C, uint16 speed)
{
    I2C->MDR = (uint32)((uint32)0U << 5U);;

    I2C->MDR =   (uint32)((uint32)0U << 15U)     /* nack mode  */
               | (uint32)((uint32)0U << 14U)     /* free running */
               | (uint32)((uint32)0U << 13U)     /* start condition - master mode only */
               | (uint32)((uint32)1U <<11U)     /* stop condition   */
               | (uint32)((uint32)1U <<10U)     /* Master/Slave mode  */
               | (uint32)((uint32)I2C_TRANSMITTER)     /* Transmitter/receiver */
               | (uint32)((uint32)I2C_7BIT_AMODE)     /* xpanded address */
               | (uint32)((uint32)0U << 7U)      /* repeat mode */
               | (uint32)((uint32)0U << 6U)     /* digital loopback */
               | (uint32)((uint32)0U << 4U)     /* start byte - master only */
               | (uint32)((uint32)0U << 3U)     /* free data format */
               | (uint32)((uint32)I2C_8_BIT);     /* bit count */

    I2C->EMDR =  0;

    I2C->DMACR = 0x00U;
    I2C->IMR = 0x00;

    I2C->PSC = 8U;
    switch(speed)
    {
        case 100:
            I2C->CKH = 37U;
            I2C->CKL = 37U;
            break;
        case 200:
            I2C->CKH = 16U;
            I2C->CKL = 16U;
            break;
        case 400:
            I2C->CKH = 5U;
            I2C->CKL = 5U;
            break;
        default:
            I2C->CKH = 5U;
            I2C->CKL = 5U;
            break;
    }

    I2CGpio(I2C);
    /** - set interrupt enable */
    i2cREG1->IMR    = (uint32)((uint32)0U << 6U)     /* Address as slave interrupt      */
                    | (uint32)((uint32)0U << 5U)     /* Stop Condition detect interrupt */
                    | (uint32)((uint32)0U << 4U)     /* Transmit data ready interrupt   */
                    | (uint32)((uint32)0U << 3U)     /* Receive data ready interrupt    */
                    | (uint32)((uint32)0U << 2U)     /* Register Access ready interrupt */
                    | (uint32)((uint32)0U << 1U)     /* No Acknowledgment interrupt    */
                    | (uint32)((uint32)0U);          /* Arbitration Lost interrupt      */

    I2C->MDR |= I2C_RESET_OUT; /* i2c out of reset */
}

/******************************************************************
*Name    :  FreeRTOS_I2CInit
*Function:  IIC ���߳�ʼ��
*Params  :  void
*Return  :  void
******************************************************************/
void FreeRTOS_I2CInit(void)
{
    I2CInit(i2cREG1,400);
    I2CInit(i2cREG2,200);
}
/******************************************************
*Name    :  I2CXrdy
*Function:  �жϵ�ǰ�Ƿ��ڷ���׼��״̬
*Params  :  I2C IIC���߻���ַ �� i2cREG1  i2cREG2
*Return  :  t ,��������״̬��=0 ����û׼����  =1 �����Ѿ���
*******************************************************/
uint16 I2CXrdy(i2cBASE_t *I2C)
{
    uint16  t;
    t = I2C->STR & 0x0010;
    t = t >> 4;
    return t;
}
/******************************************************
*Name    :  I2CRrdy
*Function:  �жϵ�ǰ�Ƿ��ڽ���׼��״̬
*Params  :  I2C IIC���߻���ַ �� i2cREG1  i2cREG2
*Return  :  t ,��������״̬��=0 ����û׼����  =1 �����Ѿ���
*******************************************************/
uint16 I2CRrdy(i2cBASE_t *I2C)
{
    uint16  t;
    t = I2C->STR & 0x0008;
    t = t >> 3;
    return t;
}

/******************************************************
*Name    :  I2CBusy
*Function:  �ж������Ƿ�æ
*Params  :  I2C IIC���߻���ַ �� i2cREG1  i2cREG2
*Return  :  t ,��������״̬��=0 ���߿���  =1 ����æ
*******************************************************/
uint16 I2CBusy(i2cBASE_t *I2C)
{
    uint16  t;
    t = I2C->STR & 0x1000;
    t = t >> 12;
    return t;
}

/******************************************************
*Name    :  I2cWrite
*Function:  i2cд���ܺ���
*Params  :  id��uint8��:�豸id
*Params  :  reg_addr(uint16):�Ĵ�����ַ
*Params  :  data��uint8��:����
*Return  :  ERR��ʧ��         NOERR���ɹ�
*******************************************************/
uint8 I2cWrite(i2cBASE_t *I2C,uint8 id,uint16 reg_addr,uint8 data)
{
    uint16  delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    } while(I2CBusy(I2C));     //Bus busy

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            UartSendString(sciREG4," First Txrdy  overtime : \r\n\0");
            systemREG1->SYSECR |= 0x0000C000;
            return 0;
        }
    }while(!I2CXrdy(I2C));

    I2C->SAR = id;
    I2C->CNT = 2;
    I2C->DXR = reg_addr & 0xFF;
    I2C->MDR = 0x6E20;

    delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            UartSendString(sciREG4," Second Txrdy  overtime : \r\n\0");
            systemREG1->SYSECR |= 0x0000C000;
            return 0;
        }
    }while(!I2CXrdy(I2C));

    I2C->DXR = data & 0xFF;

    delay = 10000;
    do{
        delay--;
        if(delay == 0)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);

    return 1;
}

/******************************************************
*Name    :  I2cRead
*Function:  i2c�����ܺ���
*Params  :  id��uint8��:�豸id
*Params  :  reg_addr(uint16):�Ĵ�����ַ
*Return  :  data����ȡ����          ERR��ʧ��
*******************************************************/
uint8  I2cRead(i2cBASE_t *I2C,uint8 id,uint16 reg_addr)
{
    uint8   data;
    uint16  delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    } while(I2CBusy(I2C));     //Bus busy

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(!I2CXrdy(I2C));

    I2C->SAR = id;
    I2C->CNT = 1;
    I2C->DXR = reg_addr & 0xFF;
    I2C->MDR = 0x6e20;

    delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);


    DelayUs(100);

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(!I2CXrdy(I2C));

    I2C->SAR = id;
    I2C->CNT = 1;
    I2C->MDR = 0x6C20;

    delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(!I2CRrdy(I2C));

    data = I2C->DRR & 0xFF;
    delay = 10000;
    do{
        delay--;
        if(delay == 0)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);

    return data;
}

/******************************************************
*Name    :  I2cWriteData
*Function:  i2c ������ݺ���
*Params  :  id��uint8��:�豸id
*Params  :  RamAddr  д���ݻ�����
*Params  :  RomAddress ���ĸ���ַ��ʼд��
*Params  :  number  ��ȡ���ݵĸ���
*Params  :  reg_addr(uint16):�Ĵ�����ַ
*Return  :  data����ȡ����          ERR��ʧ��
*******************************************************/
uint8 I2cWriteData(i2cBASE_t *I2C,uint8 id,uint8  *RamAddr, uint16    RomAddress, uint8 count)
{
    uint8   i;
    uint16  delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    } while(I2CBusy(I2C));     //Bus busy

    delay = 50000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(!I2CXrdy(I2C));

    I2C->SAR = id;
    I2C->CNT = count+1;
    I2C->DXR = RomAddress;
    I2C->MDR = 0x6E20;

    delay = 10000;
    do{
        delay--;
        if(delay <= 10)
        {
            return 0;
        }
    }while(I2C->STR & 0x2);

    for(i=0;i<count;i++)
    {
        delay = 50000;
        do{
            delay--;
            if(delay <= 10)
            {
                return 0;
            }
        }while(!I2CXrdy(I2C));

        I2C->DXR = *RamAddr;
        RamAddr++;

        delay = 10000;
        do{
            delay--;
            if(delay == 0)
            {
                return 0;
            }
        }while(I2C->STR & 0x2);
    }
    return 1;
}

/******************************************************
*Name    :  I2cReadData
*Function:  i2c ������ݺ���
*Params  :  id��uint8��:�豸id
*Params  :  RamAddr  ���������ݴ��ַ
*Params  :  RomAddress ���ĸ���ַ��ʼ��
*Params  :  number  ��ȡ���ݵĸ���
*Params  :  reg_addr(uint16):�Ĵ�����ַ
*Return  :  data����ȡ����          ERR��ʧ��
*******************************************************/
uint8 I2cReadData(i2cBASE_t *I2C,uint8 id,uint8 *RamAddr, uint16 RomAddress, uint8 count)
{
   uint8  i,data;
   uint16   delay = 10000;
   do{
       delay--;
       if(delay <= 10)
       {
           return 0;
       }
   }while(I2CBusy(I2C));

   delay = 50000;
   do{
       delay--;
       if(delay <= 10)
       {
           return 0;
       }
   }while(!I2CXrdy(I2C));

   I2C->SAR = id;
   I2C->CNT = 1;
   I2C->DXR = RomAddress;
   I2C->MDR = 0x6e20;
   delay = 10000;
   do{
       delay--;
       if(delay <= 10)
       {
           return 0;
       }
   }while(I2C->STR & 0x2);

   DelayUs(100);
   delay = 50000;
   do{
       delay--;
       if(delay <= 10)
       {
           return 0;
       }
   }while(!I2CXrdy(I2C));

   I2C->SAR = id;
   I2C->CNT = count;
   I2C->MDR = 0x6C20;
   delay = 10000;
   do{
       delay--;
       if(delay <= 10)
       {
           return 0;
       }
   }while(I2C->STR & 0x2);

   for(i=0;i<count;i++)
   {
       delay = 50000;
       do{
           delay--;
           if(delay <= 10)
           {
               return 0;
           }
       }while(!I2CRrdy(I2C));

      data = I2C->DRR & 0xFF;
      delay = 10000;
      do{
          delay--;
          if(delay <= 10)
          {
              return 0;
          }
      }while(I2C->STR & 0x2);

      *RamAddr = data;
      RamAddr++;
   }
   return 1;
}
