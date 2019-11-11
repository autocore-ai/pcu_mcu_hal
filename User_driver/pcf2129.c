/******************************************************************
FileName   :pcf2129.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-15
****************************************************************/
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"

#include "hardware.h"

#define     RtcID       0x51

#define     RtcContrl1Reg   0x00
#define     RtcContrl2Reg   0x01
#define     RtcContrl3Reg   0x02
#define     RtcSecondReg    0x03
#define     RtcMinuteReg    0x04
#define     RtcHourReg      0x05
#define     RtcDayReg       0x06
#define     RtcWeekReg      0x07
#define     RtcMonthReg     0x08
#define     RtcYearReg      0x09
#define     AlarmMiute      0x0A
#define     AlarmHour       0x0B
#define     AlarmDay        0x0C
#define     AlarmWeek       0x0D
#define     Clockout        0x0E


/******************************************************
*Name    :  RtcWrite
*Function:  RTC写功能函数
*Params  :  reg(uint8):寄存器地址
*Params  :  data（uint8）:数据
*Return  :
*******************************************************/

void    RtcWrite(uint8 reg, uint8 data)
{
    I2cWrite(i2cREG1,RtcID,reg,data);
}

/******************************************************
*Name    :  RtcRead
*Function:  RTC读功能函数
*Params  :  reg(uint16):寄存器地址
*Return  :  data：获取数据          ERR：失败
*******************************************************/
uint8   RtcRead(uint8 reg)
{
   return ( I2cRead(i2cREG1,RtcID,reg));
}

/******************************************************
*Name    :  RtcInit
*Function:  RTC初始化函数
*Params  :
*Return  :
*******************************************************/
void    RtcInit(void)
{
//    uint8   dat[10] = {0x00,0x00,0x00,0x34,0x23,0x05,0x15,0x03,0x05,0x19 };

    I2CInit(i2cREG1,400);
    DelayUs(50);
//    I2cWriteData(i2cREG1,RtcID,dat,RtcContrl1Reg,0x0a);

    RtcWrite(RtcContrl1Reg,0x00);
    DelayUs(50);
    RtcWrite(RtcContrl2Reg,0x00);
    DelayUs(50);
    RtcWrite(RtcContrl3Reg,0x00);
    DelayUs(50);

    RtcWrite(RtcYearReg,0x19);
    DelayUs(50);
    RtcWrite(RtcMonthReg,0x05);
    DelayUs(50);
    RtcWrite(RtcWeekReg,0x03);
    DelayUs(50);
    RtcWrite(RtcDayReg,0x15);
    DelayUs(50);
    RtcWrite(RtcHourReg,0x05);
    DelayUs(50);
    RtcWrite(RtcMinuteReg,0x23);
    DelayUs(50);
    RtcWrite(RtcSecondReg,0x34);
    DelayUs(50);

}

/******************************************************
*Name    :  RtcSetValue
*Function:  RTC 设置时间函数
*Params  :
*Return  :
*******************************************************/
void    RtcSetValue(Rtc_Timer  rtc)
{

    RtcWrite(RtcYearReg,rtc.ryear);
    RtcWrite(RtcMonthReg,rtc.rmouth);
    RtcWrite(RtcDayReg,rtc.rday);
    RtcWrite(RtcHourReg,rtc.rhour);
    RtcWrite(RtcMinuteReg,rtc.rminute);
    RtcWrite(RtcSecondReg,rtc.rsecond);

}

/******************************************************
*Name    :  RtcGetValue
*Function:  RTC 读取时间函数
*Params  :
*Return  :
*******************************************************/
Rtc_Timer   RtcGetValue(void)
{
    Rtc_Timer  rtc;
    uint8   dat[7];
    I2cReadData(i2cREG1,RtcID,dat,RtcSecondReg,0x7);

    rtc.rsecond = dat[0];
    rtc.rminute = dat[1];
    rtc.rhour   = dat[2];
    rtc.rday    = dat[3];
    rtc.rmouth  = dat[5];
    rtc.ryear   = dat[6];
/*
    rtc.rsecond = RtcRead(RtcSecondReg) & 0x7F;
    DelayUs(50);
    rtc.rminute = RtcRead(RtcMinuteReg) & 0x7F;
    DelayUs(50);
    rtc.rhour   = RtcRead(RtcHourReg);
    DelayUs(50);
    rtc.rday    = RtcRead(RtcDayReg);
    DelayUs(50);
    rtc.rmouth  = RtcRead(RtcMonthReg);
    DelayUs(50);
    rtc.ryear   = RtcRead(RtcYearReg);
    DelayUs(50);
*/
    return(rtc);
}

