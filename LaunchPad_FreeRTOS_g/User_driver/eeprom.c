/******************************************************************
FileName   :eeprom.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2020-10-27
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "HL_i2c.h"
#include "HL_reg_i2c.h"
#include "HL_reg_system.h"
#include "HL_hal_stdtypes.h"
#include "IIC_driver.h"
#include "hardware.h"


uint8 FUNC_IIC(write)(uint8  data, uint16  RomAddr)
{
    uint8   id;
    uint8   tA8;

    if(RomAddr > 0x1FF)
        return  0;
    else
    {
        tA8 = (uint8)((RomAddr & 0x100) >> 8);
    }

    tA8 = tA8 & 0x01;

    id = EEPROM_ID + tA8;

    return I2cWrite(i2cREG1,id,RomAddr,data);
}

uint8 FUNC_IIC(page_write)(uint8  *pdat, uint16  pagenum, uint8 count)
{
    uint8   id;
    uint8   tA8;

    if(pagenum > 0x20)
        return 0;

    pagenum = pagenum << 4 ;

    if(pagenum > 0x1FF)
        return  0;
    else
    {
        tA8 = (uint8)((pagenum & 0x100) >> 8);
    }

    tA8 = tA8 & 0x01;

    id = EEPROM_ID + tA8;

    pagenum = pagenum & 0xFF;

    return I2cWriteData(i2cREG1, id, pdat, pagenum, count);

}

uint8  FUNC_IIC(read)(uint16  RomAddr)
{
    uint8   id;
    uint8   tA8;
    uint8   data;
    uint16  delay = 10000;
    i2cBASE_t *I2C = i2cREG1;

    if(RomAddr > 0x1FF)
        return  0;
    else
    {
        tA8 = (uint8)((RomAddr & 0x100) >> 8);
    }

    tA8 = tA8 & 0x01;

    id = EEPROM_ID + tA8;

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
    I2C->DXR = RomAddr & 0xFF;
    I2C->MDR = 0x6620;
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
       if(delay <= 10)
       {
           return 0;
       }
   }while(I2C->STR & 0x2);

    return data;

}

uint8  FUNC_IIC(page_read)(uint8 *pdat, uint16  pagenum, uint8 count)
{
    uint8   id;
    uint8   tA8;
    uint8   i,data;
    uint16  delay = 10000;
    i2cBASE_t *I2C = i2cREG1;

    if(pagenum > 0x20)
        return 0;

    pagenum = pagenum << 4 ;

    if(pagenum > 0x1FF)
        return  0;
    else
    {
        tA8 = (uint8)((pagenum & 0x100) >> 8);
    }

    tA8 = tA8 & 0x01;

    id = EEPROM_ID + tA8;

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
    I2C->DXR = pagenum & 0xFF;
    I2C->MDR = 0x6620;
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

       *pdat = data;
       pdat++;
    }
    return 1;
}


void  AT24C04_Test(void)
{
    uint8  dat[16] = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0x5a,0xa5 };
    uint8  dat1[16];
    uint8   i;

    for(i=0;i<16;i++)
    {
        FUNC_IIC(write)(dat[i],0xF8+i);
        DelayUs(100);
    }
    for(i=0;i<16;i++)
    {
        dat1[i] = FUNC_IIC(read)(0xF8+i);
        DelayUs(100);
    }

    FUNC_IIC(page_write)(dat,0x10,16);
    DelayUs(100);
    FUNC_IIC(page_read)(dat1,0x10,16);
    DelayUs(100);

    for(i=0;i<16;i++)
    {
        if(dat[i] != dat1[i])
            while(1);
    }
}
