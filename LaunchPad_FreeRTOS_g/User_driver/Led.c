/******************************************************************
FileName   :Led.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-09-10
****************************************************************/
#include    "HL_het.h"
#include    "Led.h"
/******************************************************
*Name    :  LedInit
*Function:  led  ��ʼ������
*Params  :
*Return  :
*******************************************************/
void    LedInit(void)
{
    /** - Setup control register
     *     - Enable output buffers
     *     - Ignore software breakpoints
     *     - Master or Slave Clock Mode
     *     - Enable HET
     */
     hetREG1->GCR = ( 0x00000001U
                    | (uint32)((uint32)1U << 24U)
                    | (uint32)((uint32)1U << 16U)
                    | (0x00020000U));

     /** - PULL functinality is enabled */
    hetREG1->PULDIS = 0x00000000;

    /** - Set HET pins direction */
    hetREG1->DIR = (uint32) 0x00000000U
                 | (uint32) ((uint32)1U << 30U)
                 | (uint32) ((uint32)1U << 29U)
                 | (uint32) ((uint32)1U << 27U)
                 | (uint32) ((uint32)1U << 25U)
                 | (uint32) ((uint32)1U << 23U)
                 | (uint32) ((uint32)1U << 21U)
                 | (uint32) ((uint32)1U << 20U)
                 | (uint32) ((uint32)1U << 18U)
                 | (uint32) ((uint32)1U << 16U)
                 | (uint32) ((uint32)1U << 14U);

    /** - Set HET pins default output value */
    hetREG1->DOUT = (uint32) 0x00000000U;

}

/******************************************************
*Name    : LedRightTop_on
*Function: Right Top Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_on(void)
{
    hetREG1->DSET = (uint32)(1 << RIGHT_TOP);
}

/******************************************************
*Name    : LedRightTop_off
*Function: Right Top Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedRightTop_off(void)
{
    hetREG1->DCLR = (uint32)(1 << RIGHT_TOP);
}

/******************************************************
*Name    : LedRightBottom_on
*Function: Right bottom Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_on(void)
{
    hetREG1->DSET = (uint32)(1 << RIGHT_BOTTOM);
}

/******************************************************
*Name    : LedRightBottom_off
*Function: Right Bottom Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedRightBottom_off(void)
{
    hetREG1->DCLR = (uint32)(1 << RIGHT_BOTTOM);
}

/******************************************************
*Name    : LedLeftTop_on
*Function: Left Top Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_on(void)
{
    hetREG1->DSET = (uint32)(1 << LEFT_TOP);
}

/******************************************************
*Name    : LedLeftTop_off
*Function: Left Top Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedLeftTop_off(void)
{
    hetREG1->DCLR = (uint32)(1 << LEFT_TOP);
}

/******************************************************
*Name    : LedLeftBottom_on
*Function: Left bottom Led ��������
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_on(void)
{
    hetREG1->DSET = (uint32)(1 << LEFT_BOTTOM);
}

/******************************************************
*Name    : LedLeftBottom_off
*Function: Left Bottom Led Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedLeftBottom_off(void)
{
    hetREG1->DCLR = (uint32)(1 << LEFT_BOTTOM);
}

/******************************************************
*Name    : LedP1Status_on
*Function: AVB P1 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_on(void)
{
    hetREG1->DSET = (uint32)(1 << P1100M_STATUS);
}

/******************************************************
*Name    : LedP1Status_off
*Function: AVB P1 ��״̬��Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedP1Status_off(void)
{
    hetREG1->DCLR = (uint32)(1 << P1100M_STATUS);
}


/******************************************************
*Name    : LedP2Status_on
*Function: AVB P2 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_on(void)
{
    hetREG1->DSET = (uint32)(1 << P2100M_STATUS);
}

/******************************************************
*Name    : LedP2Status_off
*Function: AVB P2 ��״̬��Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedP2Status_off(void)
{
    hetREG1->DCLR = (uint32)(1 << P2100M_STATUS);
}

/******************************************************
*Name    : LedP3Status_on
*Function: AVB P3 ��״̬�Ƶ�������
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_on(void)
{
    hetREG1->DSET = (uint32)(1 << P3100M_STATUS);
}

/******************************************************
*Name    : LedP3Status_off
*Function: AVB P3 ��״̬��Ϩ����
*Params  :
*Return  :
*******************************************************/
void    LedP3Status_off(void)
{
    hetREG1->DCLR = (uint32)(1 << P3100M_STATUS);
}

/******************************************************
*Name    : Phy1En_on
*Function: PHY1  enable
*Params  :
*Return  :
*******************************************************/
void    Phy1En_on(void)
{
    hetREG1->DSET = (uint32)(1 << PHY1_EN);
}

/******************************************************
*Name    : Phy1En_off
*Function: PHY1  disable
*Params  :
*Return  :
*******************************************************/
void    Phy1En_off(void)
{
    hetREG1->DCLR = (uint32)(1 << PHY1_EN);
}
/******************************************************
*Name    : Phy2En_on
*Function: PHY2  enable
*Params  :
*Return  :
*******************************************************/
void    Phy2En_on(void)
{
    hetREG1->DSET = (uint32)(1 << PHY2_EN);
}

/******************************************************
*Name    : Phy2En_off
*Function: PHY2  disable
*Params  :
*Return  :
*******************************************************/
void    Phy2En_off(void)
{
    hetREG1->DCLR = (uint32)(1 << PHY2_EN);
}

/******************************************************
*Name    : LinEn_on
*Function: Lin1 and Lin2  enable
*Params  :
*Return  :
*******************************************************/
void    LinEn_on(void)
{
    hetREG1->DSET = (uint32)(1 << LIN_EN);
}

/******************************************************
*Name    : LinEn_off
*Function: Lin1 and Lin2  disable
*Params  :
*Return  :
*******************************************************/
void    LinEn_off(void)
{
    hetREG1->DCLR = (uint32)(1 << LIN_EN);
}
