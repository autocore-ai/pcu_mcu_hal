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
#include "string.h"
#include "hardware.h"
#include "ff_time.h"
#include "ma_date_and_time.h"
#include <time.h>

extern volatile time_t xSysTimeSeconds;

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

#define     FOURYEARDAY     (365+365+365+366)   //4年一个周期内的总天数（1970~2038不存在2100这类年份，故暂不优化）
#define     TIMEZONE        (8)                 //北京时区调整

static  uint8_t     month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //平年
static  uint8_t     Leap_month_day[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //闰年

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
    Rtc_Timer  rtc;

    I2CInit(i2cREG1,400);
    DelayUs(500000);

    rtc = TimeGet();
    xSysTimeSeconds = Beijing2UnixTime(&rtc);
}

/******************************************************
*Name    :  RtcSetValue
*Function:  RTC 设置时间函数
*Params  :
*Return  :
*******************************************************/
void    RtcSetValue(Rtc_Timer  rtc)
{

    RtcWrite(RtcYearReg,rtc.ryear & 0xFF);
    DelayUs(100);
    RtcWrite(RtcMonthReg,rtc.rmonth);
    DelayUs(100);
    RtcWrite(RtcDayReg,rtc.rday);
    DelayUs(100);
    RtcWrite(RtcHourReg,rtc.rhour);
    DelayUs(100);
    RtcWrite(RtcMinuteReg,rtc.rminute);
    DelayUs(100);
    RtcWrite(RtcSecondReg,rtc.rsecond );
    DelayUs(100);
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

    rtc.rsecond = dat[0] & 0x7F;
    rtc.rminute = dat[1] & 0x7F;
    rtc.rhour   = dat[2] ;
    rtc.rday    = dat[3] & 0x3F;
    rtc.rmonth  = dat[5] & 0x1F;
    rtc.ryear   = dat[6];
    return(rtc);
}

/******************************************************
*Name    :  TimeGet
*Function:  Time 读取时间函数
*Params  :
*Return  :
*******************************************************/
Rtc_Timer   TimeGet(void)
{
    Rtc_Timer  rtc;
    uint8   dat[7];
    uint8   temp;
    I2cReadData(i2cREG1,RtcID,dat,RtcSecondReg,0x7);

    temp = dat[0] & 0x7F;
    rtc.rsecond = 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    temp = dat[1] & 0x7F;
    rtc.rminute = 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    temp = dat[2];
    rtc.rhour   = 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    temp = dat[3] & 0x3F;
    rtc.rday    = 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    temp = dat[5] & 0x1F;
    rtc.rmonth  = 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    temp = dat[6];
    rtc.ryear   = 2000 + 10 * ((temp >> 4) & 0x0F )  + (temp & 0x0F);
    return(rtc);
}

/******************************************************
*Name    :  isLeapYear
*Function:  判断是否是闰年
*Params  :  year: 需要判断的年
*Return  :  return：1：闰年   0: 平年
*******************************************************/
uint8_t isLeapYear(uint16_t year)
{
    uint8_t res = 0;
    if(year%4 == 0)             // 能够被4整除
    {
        if((year%100 == 0) && (year%400 != 0)) //能够被100整除，但是不能够被400整除
        {
            res = 0;
        }
        else
        {
            res =1;
        }
    }
    return res;
}

/******************************************************
*Name    :  UnixTime2Beijing
*Function:  将Unix时间戳转换为北京时间
*Params  :  unixTime: 需要判断的Unix时间戳      *tempBeijing : 返回的北京时间
*Return  :  return：none
*Note    :  没对输入参数正确性做判断
*******************************************************/
void UnixTime2Beijing(uint32_t unixTime, Rtc_Timer *tempBeijing)
{
    uint32_t totleDayNum=0, totleSecNum=0;
    uint16_t remainDayofYear=0, tempYear=0;
    uint8_t *pr=NULL;
    totleDayNum = unixTime/(24*60*60); //总天数(注意加括号)
    totleSecNum = unixTime%(24*60*60); //当天剩余的秒速
    memset(tempBeijing, 0x00, sizeof(Rtc_Timer));
    // 1.先计算时间 HH:MM:SS
    tempBeijing->rhour      = totleSecNum/3600;
    tempBeijing->rminute    = (totleSecNum%3600)/60;
    tempBeijing->rsecond    = (totleSecNum%3600)%60;
    // 2.对时间进行时区调整（注意：这里可能造成日期 +1）
    tempBeijing->rhour +=TIMEZONE;
    if(tempBeijing->rhour > 23)
    {
        tempBeijing->rhour -= 24;
        remainDayofYear++; // 日期+1
    }
    // 3.计算哪一年
    tempBeijing->ryear = 1970 + (totleDayNum / FOURYEARDAY) * 4; // 4年为一个周期
    remainDayofYear += totleDayNum % FOURYEARDAY;
    tempYear = isLeapYear(tempBeijing->ryear) ? 366 : 365;
    while(remainDayofYear >= tempYear) // 计算4年整数倍外的年。
    {
        tempBeijing->ryear++;
        remainDayofYear -= tempYear;
        tempYear = isLeapYear(tempBeijing->ryear) ? 366 : 365;
    }
    // 4.计算哪一月的哪一天
    pr = isLeapYear(tempBeijing->ryear) ? Leap_month_day : month_day;
    remainDayofYear++;                          // 这里开始计算具体日期。remainDayofYear为 0 时其实是 1 号，所以这里要 +1
    while(remainDayofYear > *(pr + tempBeijing->rmonth))
    {
        remainDayofYear -= *(pr+tempBeijing->rmonth);
        tempBeijing->rmonth++;
    }
    tempBeijing->rmonth++; //month
    tempBeijing->rday = remainDayofYear; //day
}


/******************************************************
*Name    :  Beijing2UnixTime
*Function:  将北京时间转换为Unix时间戳
*Params  :  *BeijingTime : 当前的北京时间
*Return  :  return：Unix时间戳（从1970/1/1 00:00:00 到现在的秒数)
*Note    :  没对输入参数正确性做判断
*******************************************************/
uint32_t Beijing2UnixTime(Rtc_Timer *beijingTime)
{
    uint32_t daynum=0, SecNum=0; //保存北京时间到起始时间的天数
    uint16_t tempYear=1970, tempMonth=0;

    //1.年的天数
    while(tempYear < beijingTime->ryear)
    {
        if(isLeapYear(tempYear))
        {
            daynum += 366;
        }
        else
        {
            daynum += 365;
        }
        tempYear++;
    }

    //2.月的天数
    while(tempMonth < beijingTime->rmonth-1)
    {
        if(isLeapYear(beijingTime->ryear)) //闰年
        {
            daynum += Leap_month_day[tempMonth];
        }
        else
        {
            daynum += month_day[tempMonth];
        }
        tempMonth++;
    }

    //3.天数
    daynum += (beijingTime->rday - 1);

    //4.时分秒
    SecNum = daynum*24*60*60; //s
    SecNum += beijingTime->rhour*60*60;
    SecNum += beijingTime->rminute*60;
    SecNum += beijingTime->rsecond;

    //5.时区调整
    SecNum -= TIMEZONE*60*60;
    return SecNum;
}


/******************************************************
*Name    :  Char2Bcd
*Function:  系统时间转成BCD码
*Params  :  i_cHexData
*Return  :  return：BCD
*Note    :  没对输入参数正确性做判断
*******************************************************/
uint8 Char2Bcd(uint8 i_cHexData)
{
    uint8 i;
    i=((i_cHexData%100)/10)*16+(i_cHexData%10);
    return i;
}

/******************************************************
*Name    :  Utc2Rtc
*Function:  将UTC时间转换成 RTC格式的BCD码
*Params  :
*Return  :  return：none
*Note    :  没对输入参数正确性做判断
*******************************************************/
void Utc2Rtc(void)
{

    Rtc_Timer   rtc;
    uint8       temp;

    UnixTime2Beijing(xSysTimeSeconds, &rtc);
    temp = rtc.ryear % 1000 ;
    rtc.ryear =  Char2Bcd(temp);

    temp = Char2Bcd(rtc.rmonth);
    rtc.rmonth = temp;

    temp = Char2Bcd(rtc.rday);
    rtc.rday = temp;

    temp = Char2Bcd(rtc.rhour);
    rtc.rhour = temp;

    temp = Char2Bcd(rtc.rminute);
    rtc.rminute = temp;

    temp = Char2Bcd(rtc.rsecond);
    rtc.rsecond = temp;
    RtcSetValue(rtc);
}


