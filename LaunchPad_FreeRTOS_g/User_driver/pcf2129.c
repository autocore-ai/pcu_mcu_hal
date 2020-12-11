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

#define     FOURYEARDAY     (365+365+365+366)   //4��һ�������ڵ���������1970~2038������2100������ݣ����ݲ��Ż���
#define     TIMEZONE        (8)                 //����ʱ������

static  uint8_t     month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //ƽ��
static  uint8_t     Leap_month_day[12]={31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //����

/******************************************************
*Name    :  RtcWrite
*Function:  RTCд���ܺ���
*Params  :  reg(uint8):�Ĵ�����ַ
*Params  :  data��uint8��:����
*Return  :
*******************************************************/

void    RtcWrite(uint8 reg, uint8 data)
{
    I2cWrite(i2cREG1,RtcID,reg,data);
}

/******************************************************
*Name    :  RtcRead
*Function:  RTC�����ܺ���
*Params  :  reg(uint16):�Ĵ�����ַ
*Return  :  data����ȡ����          ERR��ʧ��
*******************************************************/
uint8   RtcRead(uint8 reg)
{
   return ( I2cRead(i2cREG1,RtcID,reg));
}

/******************************************************
*Name    :  RtcInit
*Function:  RTC��ʼ������
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
*Function:  RTC ����ʱ�亯��
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
*Function:  RTC ��ȡʱ�亯��
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
*Function:  Time ��ȡʱ�亯��
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
*Function:  �ж��Ƿ�������
*Params  :  year: ��Ҫ�жϵ���
*Return  :  return��1������   0: ƽ��
*******************************************************/
uint8_t isLeapYear(uint16_t year)
{
    uint8_t res = 0;
    if(year%4 == 0)             // �ܹ���4����
    {
        if((year%100 == 0) && (year%400 != 0)) //�ܹ���100���������ǲ��ܹ���400����
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
*Function:  ��Unixʱ���ת��Ϊ����ʱ��
*Params  :  unixTime: ��Ҫ�жϵ�Unixʱ���      *tempBeijing : ���صı���ʱ��
*Return  :  return��none
*Note    :  û�����������ȷ�����ж�
*******************************************************/
void UnixTime2Beijing(uint32_t unixTime, Rtc_Timer *tempBeijing)
{
    uint32_t totleDayNum=0, totleSecNum=0;
    uint16_t remainDayofYear=0, tempYear=0;
    uint8_t *pr=NULL;
    totleDayNum = unixTime/(24*60*60); //������(ע�������)
    totleSecNum = unixTime%(24*60*60); //����ʣ�������
    memset(tempBeijing, 0x00, sizeof(Rtc_Timer));
    // 1.�ȼ���ʱ�� HH:MM:SS
    tempBeijing->rhour      = totleSecNum/3600;
    tempBeijing->rminute    = (totleSecNum%3600)/60;
    tempBeijing->rsecond    = (totleSecNum%3600)%60;
    // 2.��ʱ�����ʱ��������ע�⣺�������������� +1��
    tempBeijing->rhour +=TIMEZONE;
    if(tempBeijing->rhour > 23)
    {
        tempBeijing->rhour -= 24;
        remainDayofYear++; // ����+1
    }
    // 3.������һ��
    tempBeijing->ryear = 1970 + (totleDayNum / FOURYEARDAY) * 4; // 4��Ϊһ������
    remainDayofYear += totleDayNum % FOURYEARDAY;
    tempYear = isLeapYear(tempBeijing->ryear) ? 366 : 365;
    while(remainDayofYear >= tempYear) // ����4������������ꡣ
    {
        tempBeijing->ryear++;
        remainDayofYear -= tempYear;
        tempYear = isLeapYear(tempBeijing->ryear) ? 366 : 365;
    }
    // 4.������һ�µ���һ��
    pr = isLeapYear(tempBeijing->ryear) ? Leap_month_day : month_day;
    remainDayofYear++;                          // ���￪ʼ����������ڡ�remainDayofYearΪ 0 ʱ��ʵ�� 1 �ţ���������Ҫ +1
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
*Function:  ������ʱ��ת��ΪUnixʱ���
*Params  :  *BeijingTime : ��ǰ�ı���ʱ��
*Return  :  return��Unixʱ�������1970/1/1 00:00:00 �����ڵ�����)
*Note    :  û�����������ȷ�����ж�
*******************************************************/
uint32_t Beijing2UnixTime(Rtc_Timer *beijingTime)
{
    uint32_t daynum=0, SecNum=0; //���汱��ʱ�䵽��ʼʱ�������
    uint16_t tempYear=1970, tempMonth=0;

    //1.�������
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

    //2.�µ�����
    while(tempMonth < beijingTime->rmonth-1)
    {
        if(isLeapYear(beijingTime->ryear)) //����
        {
            daynum += Leap_month_day[tempMonth];
        }
        else
        {
            daynum += month_day[tempMonth];
        }
        tempMonth++;
    }

    //3.����
    daynum += (beijingTime->rday - 1);

    //4.ʱ����
    SecNum = daynum*24*60*60; //s
    SecNum += beijingTime->rhour*60*60;
    SecNum += beijingTime->rminute*60;
    SecNum += beijingTime->rsecond;

    //5.ʱ������
    SecNum -= TIMEZONE*60*60;
    return SecNum;
}


/******************************************************
*Name    :  Char2Bcd
*Function:  ϵͳʱ��ת��BCD��
*Params  :  i_cHexData
*Return  :  return��BCD
*Note    :  û�����������ȷ�����ж�
*******************************************************/
uint8 Char2Bcd(uint8 i_cHexData)
{
    uint8 i;
    i=((i_cHexData%100)/10)*16+(i_cHexData%10);
    return i;
}

/******************************************************
*Name    :  Utc2Rtc
*Function:  ��UTCʱ��ת���� RTC��ʽ��BCD��
*Params  :
*Return  :  return��none
*Note    :  û�����������ȷ�����ж�
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


