/******************************************************************
FileName   :Can_init.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-29
****************************************************************/


#include "HL_can.h"
#include "HL_sys_vim.h"
#include "Can_init.h"

/******************************************************************
*Name    :  can_setup
*Function:  can 通道配置函数
*Params  :  canreg  can通道基地址指针
*Params  :  pmask   can通道配置参数指针
*Return  :  void
*******************************************************************/
void can_setup(canBASE_t *canreg, canMask  *pmask)
{
    uint32  temp = 0;
    uint8   i = 0;

    canreg->CTL  = (uint32)0x00000000U
                 | (uint32)0x00000000U
                 | (uint32)((uint32)0x00000005U  << 10U)
                 | (uint32)0x00020043U;

    /** - Clear all pending error flags and reset current status */
    canreg->ES |= 0xFFFFFFFFU;

    /** - Assign interrupt level for messages */
    canreg->INTMUXx[0U]  = (uint32)0x00000000U
                         | (uint32)0x00000000U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00040000U
                         | (uint32)0x00080000U
                         | (uint32)0x00100000U
                         | (uint32)0x00200000U
                         | (uint32)0x00400000U
                         | (uint32)0x00800000U
                         | (uint32)0x01000000U
                         | (uint32)0x02000000U
                         | (uint32)0x04000000U
                         | (uint32)0x08000000U
                         | (uint32)0x10000000U
                         | (uint32)0x20000000U
                         | (uint32)0x40000000U
                         | (uint32)0x80000000U;

    canreg->INTMUXx[1U]  = (uint32)0x00000001U
                         | (uint32)0x00000002U
                         | (uint32)0x00000004U
                         | (uint32)0x00000008U
                         | (uint32)0x00000010U
                         | (uint32)0x00000020U
                         | (uint32)0x00000040U
                         | (uint32)0x00000080U
                         | (uint32)0x00000100U
                         | (uint32)0x00000200U
                         | (uint32)0x00000400U
                         | (uint32)0x00000800U
                         | (uint32)0x00001000U
                         | (uint32)0x00002000U
                         | (uint32)0x00004000U
                         | (uint32)0x00008000U
                         | (uint32)0x00010000U
                         | (uint32)0x00020000U
                         | (uint32)0x00040000U
                         | (uint32)0x00080000U
                         | (uint32)0x00100000U
                         | (uint32)0x00200000U
                         | (uint32)0x00400000U
                         | (uint32)0x00800000U
                         | (uint32)0x01000000U
                         | (uint32)0x02000000U
                         | (uint32)0x04000000U
                         | (uint32)0x08000000U
                         | (uint32)0x10000000U
                         | (uint32)0x20000000U
                         | (uint32)0x40000000U
                         | (uint32)0x80000000U;

    /** - Setup auto bus on timer period */
    canreg->ABOTR = (uint32)0U;

    while ((canreg->IF1STAT & 0x80U) ==0x80U)  {      } /* Wait */
    temp =(uint32)(((uint32)(pmask->MXtd & 0x01)) << 31 );
    temp = temp | (uint32)(((uint32)(pmask->MDir & 0x01)) << 30 );
    if (pmask->Xtd & 0x1)
        temp = temp | (uint32)(pmask->MaskID & 0x1FFFFFFF);
    else
        temp = temp | (uint32)((uint32)((uint32)pmask->MaskID & (uint32)0x000007FFU) << (uint32)18U);
    canreg->IF1MSK = temp;

    temp = 0x80000000;
    temp = temp | (uint32)(((uint32)(pmask->Xtd & 0x01)) << 30);
    temp = temp | (uint32)(((uint32)(pmask->Dir & 0x01)) << 29);
    if (pmask->Xtd & 0x1)
        temp = temp | (uint32)(pmask->ArbID & 0x1FFFFFFF);
    else
        temp = temp | (uint32)((uint32)((uint32)pmask->ArbID & (uint32)0x000007FFU) << (uint32)18U);
    canreg->IF1ARB = temp;

    canreg->IF1MCTL = 0x00001000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canreg->IF1CMD  = (uint8) 0xF8U;
    canreg->IF1NO   = 1U;

    pmask++;

    while ((canREG1->IF2STAT & 0x80U) ==0x80U)  {     } /* Wait */
    temp =(uint32)(((uint32)(pmask->MXtd & 0x01)) << 31 );
    temp = temp | (uint32)(((uint32)(pmask->MDir & 0x01)) << 30 );
    if (pmask->Xtd & 0x1)
        temp = temp | (uint32)(pmask->MaskID & 0x1FFFFFFF);
    else
        temp = temp | (uint32)((uint32)((uint32)pmask->MaskID & (uint32)0x000007FFU) << (uint32)18U);
    canreg->IF2MSK = temp;

    temp = 0x80000000;
    temp = temp | (uint32)(((uint32)(pmask->Xtd & 0x01)) << 30);
    temp = temp | (uint32)(((uint32)(pmask->Dir & 0x01)) << 29);
    if (pmask->Xtd & 0x1)
        temp = temp | (uint32)(pmask->ArbID & 0x1FFFFFFF);
    else
        temp = temp | (uint32)((uint32)((uint32)pmask->ArbID & (uint32)0x000007FFU) << (uint32)18U);
    canreg->IF2ARB = temp;

    canreg->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;;
    canreg->IF2CMD  = (uint8) 0xF8U;
    canreg->IF2NO   = 2U;

    pmask++;

    for(i=0;i<31;i++)
    {
        while ((canreg->IF1STAT & 0x80U) ==0x80U)  {      }
        temp =(uint32)(((uint32)(pmask->MXtd & 0x01)) << 31 );
        temp = temp | (uint32)(((uint32)(pmask->MDir & 0x01)) << 30 );
        if (pmask->Xtd & 0x1)
            temp = temp | (uint32)(pmask->MaskID & 0x1FFFFFFF);
        else
            temp = temp | (uint32)((uint32)((uint32)pmask->MaskID & (uint32)0x000007FFU) << (uint32)18U);
        canreg->IF1MSK = temp;

        temp = 0x80000000;
        temp = temp | (uint32)(((uint32)(pmask->Xtd & 0x01)) << 30);
        temp = temp | (uint32)(((uint32)(pmask->Dir & 0x01)) << 29);
        if (pmask->Xtd & 0x1)
            temp = temp | (uint32)(pmask->ArbID & 0x1FFFFFFF);
        else
            temp = temp | (uint32)((uint32)((uint32)pmask->ArbID & (uint32)0x000007FFU) << (uint32)18U);
        canreg->IF1ARB = temp;

        canreg->IF1MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
        canreg->IF1CMD  = (uint8) 0xF8U;
        canreg->IF1NO   = (i+1)*2 + 1;

        pmask++;

        while ((canREG1->IF2STAT & 0x80U) ==0x80U)   {      }
        temp =(uint32)(((uint32)(pmask->MXtd & 0x01)) << 31 );
        temp = temp | (uint32)(((uint32)(pmask->MDir & 0x01)) << 30 );
        if (pmask->Xtd & 0x1)
            temp = temp | (uint32)(pmask->MaskID & 0x1FFFFFFF);
        else
            temp = temp | (uint32)((uint32)((uint32)pmask->MaskID & (uint32)0x000007FFU) << (uint32)18U);
        canreg->IF2MSK = temp;

        temp = 0x80000000;
        temp = temp | (uint32)(((uint32)(pmask->Xtd & 0x01)) << 30);
        temp = temp | (uint32)(((uint32)(pmask->Dir & 0x01)) << 29);
        if (pmask->Xtd & 0x1)
            temp = temp | (uint32)(pmask->ArbID & 0x1FFFFFFF);
        else
            temp = temp | (uint32)((uint32)((uint32)pmask->ArbID & (uint32)0x000007FFU) << (uint32)18U);
        canreg->IF2ARB = temp;

        canreg->IF2MCTL = 0x00001000U | (uint32)0x00000400U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;;
        canreg->IF2CMD  = (uint8) 0xF8U;
        canreg->IF2NO   = (i+1)*2 + 2;

        pmask++;
    }

    while ((canreg->IF1STAT & 0x80U) ==0x80U)   {       } /* Wait */
    canreg->IF1CMD  = 0x87U;

    while ((canREG2->IF2STAT & 0x80U) ==0x80U)  {       } /* Wait */
    canreg->IF2CMD = 0x17U;

    canreg->BTR  =  (uint32)((uint32)0U << 16U)
                 |  (uint32)((uint32)(4U - 1U) << 12U)
                 |  (uint32)((uint32)((6U + 4U) - 1U) << 8U)
                 |  (uint32)((uint32)(4U - 1U) << 6U)
                 |  (uint32)9U;


    canreg->TIOC   = (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )
                   | (uint32)((uint32)1U  << 3U )
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U  << 1U );

    canreg->RIOC   = (uint32)((uint32)1U  << 18U )
                   | (uint32)((uint32)0U  << 17U )
                   | (uint32)((uint32)0U  << 16U )
                   | (uint32)((uint32)1U  << 3U )
                   | (uint32)((uint32)0U  << 2U )
                   | (uint32)((uint32)0U  << 1U );

    /** - Leave configuration and initialization mode  */
    canreg->CTL &= ~(uint32)(0x00000041U);
}

/******************************************************************
*Name    :  can_init
*Function:  can 初始化函数
*Params  :  void
*Return  :  void
*******************************************************************/
void    can_init(void)
{
    canMask  canmask[4][64];
    uint8   i,j;

    for(i=0;i<4;i++)
    {
        canmask[i][0].MXtd = 0;
        canmask[i][0].MDir = 0;
        canmask[i][0].MaskID = 0x00000000;
        canmask[i][0].Xtd  = 0;
        canmask[i][0].Dir  = 1;
        canmask[i][0].ArbID =(uint32)i;
    }
    for(i=0;i<4;i++)
    {
        for(j=1;j<64;j++)
        {
            canmask[i][j].MXtd = 0;
            canmask[i][j].MDir = 0;
            canmask[i][j].MaskID = 0x00000000;
            canmask[i][j].Xtd  = 0;
            canmask[i][j].Dir  = 0;
            canmask[i][j].ArbID =(uint32)j;
        }
    }

    can_setup(canREG1, &canmask[0][0]);
    can_setup(canREG2, &canmask[1][0]);
    can_setup(canREG3, &canmask[2][0]);
    can_setup(canREG4, &canmask[3][0]);
}
