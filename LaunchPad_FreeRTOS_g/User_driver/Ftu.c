/******************************************************************
FileName   :ERay.c
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-12-3
****************************************************************/

#include    "Fr.h"

uint8   ConfFlexHdr(Flex_msg * msg, uint16 DataPtr, uint16 FrameID, uint8 length)
{
    if ((FrameID > 2048) | (DataPtr > 2048) | (length > 127))
    {
        return 1;
    }
    msg->Fray_header.header1.bit.FID = FrameID;
    msg->Fray_header.header3.bit.DP  = DataPtr;
    msg->Fray_header.header2.bit.PLC = length;
    return 0;
}

void    ConfFtuRam(FlexTu_ST   *Ftu_pst)
{
    Ftu_pst->SAMP.all = 0x08001000;
    Ftu_pst->EAMP.all = 0x08002000;
}

void    ConfTuBase(FlexTu_ST   *Ftu_pst,Flex_msg * fram)
{
    Ftu_pst->TBA.all = (uint32)fram;
}

/*--------------------------------------------------------------------------*/
/* TCR transfer initialization */
/* int TCR_Init(int channel, int header, int payload, int offset, int dir) */
/* */
/* int channel:FTU channel */
/* int header: 1: transfers header */
/* 0: no header transfer */
/* int payload: 1: transfers payload */
/* 0: no payload transfer */
/* int offset: transfer start offset */
/* int dir: 1: transfer direction is to SM */
/* 0: transfer direction is to CC */
/* */
/* returns 0 */
/*--------------------------------------------------------------------------*/
int TCR_Init(int channel, int header, int payload, int offset, int dir)
{
    int value = 0;
    if (dir != 0) // if direction is other than to CC
    dir = 2; // direction will be SM
    value = value + (header << (15 + dir));
    value = value + (payload << (14 + dir));
    value = value + offset;
//    TCR_Ptr->FTUTCR_ST[channel].TCR_UN.TCR_UL = value;
    return(0);
}

void    TU_enable(FlexTu_ST   *Ftu_pst)
{
    Ftu_pst->GCS.bit.TUE = 1;
}
