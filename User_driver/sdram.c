/*
 * sdran.c
 *
 *  Created on: 2019Äê9ÔÂ9ÈÕ
 *      Author: zhenh
 */
#include "HL_emif.h"
#include "hardware.h"

#define     RAM_SIZE    0x800000
uint16      *ExRamStart = (uint16 *)0x80000000;


void    sdram_test(void)
{
    uint32  i;
#if  (DEBUG)
    UartSendString(sciREG1," Sdram testing, please wait !!! \r\n\0");
#endif

    for(i = 0; i < RAM_SIZE/2; i++)
    {
        *(ExRamStart + i) = 0x5555;
        if(*(ExRamStart + i) != 0x5555)
        {
            while(1);
        }
    }

    for(i = 0; i < RAM_SIZE/2; i++)
    {
        *(ExRamStart + i) = 0xAAAA;
        if(*(ExRamStart + i) != 0xAAAA)
        {
            while(1);
        }
    }

    for(i = 0; i< RAM_SIZE/2; i++)
    {
        *(ExRamStart + i) = (uint16)i;
        if(*(ExRamStart + i) != (uint16)i)
        {
            while(1);
        }
    }
#if  (DEBUG)
    UartSendString(sciREG1," Sdram test :  sucess \r\n\0");
    UartSendString(sciREG1," Sdram size :  \0");

    UartSendHexU32(sciREG1,RAM_SIZE);
    UartSendString(sciREG1,"\r\n\0");
#endif

}
