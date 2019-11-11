/******************************************************************
FileName   :HL_reg_flexray.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-10-22
****************************************************************/

#ifndef USER_DRIVER_HL_REG_FLEXRAY_H_
#define USER_DRIVER_HL_REG_FLEXRAY_H_

#include "HL_sys_common.h"

struct  CSN0_BITS {           //   Global Static Number 0  bit  description
    uint16  data_a  ;         //   Data_A
    uint16  data_b  ;         //   Complement of Data_A

};

/* Allow access to the bit fields or entire register */
union   CSN0_REG {
    uint32              all;
    struct  CSN0_BITS   bit;
};

struct  CSN1_BITS {           //   Global Static Number 0  bit  description
    uint16  data_c  ;         //   Data_C
    uint16  data_d  ;         //   Complement of Data_C

};

/* Allow access to the bit fields or entire register */
union   CSN1_REG {
    uint32              all;
    struct  CSN1_BITS   bit;
};

struct  GCS_BITS {              //Global Control Set/Reset bit description
    uint32      ENDVBM  :   1;  //bit31
    uint32      ENDVBS  :   1;
    uint32      ENDDR   :   2;
    uint32      ENDH    :   2;
    uint32      ENDP    :   2;
    uint32      rsvd    :   2;
    uint32      PRIO    :   1;
    uint32      rsvd1   :   1;
    uint32      PEL     :   4;
    uint32      rsvd2   :   1;
    uint32      CETESM  :   1;
    uint32      CTTCC   :   1;
    uint32      CTTSM   :   1;
    uint32      rsvd3   :   3;
    uint32      ETSM    :   1;
    uint32      rsvd4   :   2;
    uint32      SILE    :   1;
    uint32      EILE    :   1;
    uint32      rsvd5   :   2;
    uint32      THU     :   1;
    uint32      TUE     :   1;  //bit0
};

union   GCS_REG {
    uint32              all;
    struct  GCS_BITS    bit;
};


struct  GCR_BITS {              //Global Control Reset bit description
    uint32      ENDVBM  :   1;  //bit31
    uint32      ENDVBS  :   1;
    uint32      ENDDR   :   2;
    uint32      ENDH    :   2;
    uint32      ENDP    :   2;
    uint32      rsvd    :   2;
    uint32      PRIO    :   1;
    uint32      rsvd1   :   1;
    uint32      PEL     :   4;
    uint32      rsvd2   :   1;
    uint32      CETESM  :   1;
    uint32      CTTCC   :   1;
    uint32      CTTSM   :   1;
    uint32      rsvd3   :   3;
    uint32      ETSM    :   1;
    uint32      rsvd4   :   2;
    uint32      SILE    :   1;
    uint32      EILE    :   1;
    uint32      rsvd5   :   2;
    uint32      THU     :   1;
    uint32      TUE     :   1;  //bit0
};

union   GCR_REG {
    uint32              all;
    struct  GCR_BITS    bit;
};

struct  TSCB_BITS {             //Transfer Status Current Buffer bit description
    uint8       rsvd;
    uint8       TSMS;
    uint8       STUH;
    uint8       BNUM;
};

union   TSCB_REG {
    uint32              all;
    struct  TSCB_BITS   bit;
};

struct  LTBCC_BITS {            //Last Transferred Buffer to Communication Controller
    uint32      rsvd    :   25;
    uint32      BNUM    :   7
};

union   LTBCC_REG {
    uint32              all;
    struct  LTBCC_BITS  bit;
};

struct  TBA_BITS {              //Transfer Base Address
    uint16      TBAH;
    uint16      RBAL;
};

union   TBA_REG {              //
    uint32              all;
    struct  TBA_BITS    bit;
};

struct  NTBA_BITS {             //Next Transfer Base Address
    uint16      NTBAH;
    uint16      NTBAL;
};

union   NTBA_REG {
    uint32              all;
    struct  NTBA_BITS   bit;
};

struct  BAMS_BITS {             //Base Address of Mirrored Status
    uint16      BAMSH;
    uint16      BAMSL;
};

union   BAMS_REG {
    uint32              all;
    struct  BAMS_BITS   bit;
};

struct  SAMP_BITS  {            //Start Address of Memory Protection
    uint16      SAMPH;
    uint16      SAMPL;
};

union   SAMP_REG  {
    uint32              all;
    struct  SAMP_BITS   bit;
};


struct  EAMP_BITS {             //End Address of Memory Protection
    uint16      EAMPH;
    uint16      EAMPL;
};

union   EAMP_REG {
    uint32              all;
    struct  EAMP_BITS   bit;
};

struct  TSMO1_BITS {            //Transfer to System Memory Occurred
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TSMO1_REG {
    uint32              all;
    struct  TSMO1_BITS  bit;
};

struct  TSMO2_BITS {            //Transfer to System Memory Occurred
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TSMO2_REG {
    uint32              all;
    struct  TSMO2_BITS  bit;
};

struct  TSMO3_BITS {            //Transfer to System Memory Occurred
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TSMO3_REG {
    uint32              all;
    struct  TSMO3_BITS  bit;
};

struct  TSMO4_BITS {            //Transfer to System Memory Occurred
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TSMO4_REG {
    uint32              all;
    struct  TSMO4_BITS  bit;
};


struct  TCCO1_BITS {            //Transfer to Communication Controller Occurred
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TCCO1_REG {
    uint32              all;
    struct  TCCO1_BITS  bit;
};

struct  TCCO2_BITS {            //Transfer to Communication Controller Occurred
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TCCO2_REG {
    uint32              all;
    struct  TCCO2_BITS  bit;
};

struct  TCCO3_BITS {            //Transfer to Communication Controller Occurred
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TCCO3_REG {
    uint32              all;
    struct  TCCO3_BITS  bit;
};

struct  TCCO4_BITS {            //Transfer to Communication Controller Occurred
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TCCO4_REG {
    uint32              all;
    struct  TCCO4_BITS  bit;
};

struct  TOOFF_BITS  {           //Transfer Occurred Offset
    uint32      rsvd    :   23;
    uint32      TDIR    :   1;
    uint32      OFFSET  :   8;
};

union   TOOFF_REG {
    uint32              all;
    struct  TOOFF_BITS  bit;
};

struct  TSBESTAT_BITS  {        //TCR Single-Bit Error Status
    uint32      SE      :   1;
    uint32      rsvd    :   22;
    uint32      ADR     :   9;
};

union   TSBESTAT_REG  {
    uint32                  all;
    struct  TSBESTAT_BITS   bit;
};

struct  PEADR_BITS  {           //ECC Error Address
    uint32      rsvd    :   23;
    uint32      ADR     :   9;
};

union   PEADR_REG {
    uint32              all;
    struct  PEADR_BITS  bit;
};

struct  TEIF_BITS  {            //Transfer Error Interrupt Flag
    uint32      rsvd    :   14;
    uint32      MPV     :   1;
    uint32      PE      :   1;
    uint32      rsvd1   :   5;
    uint32      RSTAT   :   3;
    uint32      rsvd2   :   1;
    uint32      WSTAT   :   3;
    uint32      rsvd3   :   2;
    uint32      TNR     :   1;
    uint32      FAC     :   1;
};

union   TEIF_REG  {
    uint32              all;
    struct  TEIF_BITS   bit;
};

struct  TEIRES_BITS {           //Transfer Error Interrupt Enable Set
    uint32      rsvd    :   21;
    uint32      RSTATE  :   3;
    uint32      rsvd1   :   1;
    uint32      WSTATE  :   3;
    uint32      rsvd    :   2;
    uint32      TNRE    :   1;
    uint32      FACE    :   1;
};

union   FEIRES_REG  {
    uint32              all;
    struct  TEIRES_BITS bit;
};

struct  TEIRER_BITS {           //Transfer Error Interrupt Enable Reset
    uint32      rsvd    :   21;
    uint32      RSTATE  :   3;
    uint32      rsvd1   :   1;
    uint32      WSTATE  :   3;
    uint32      rsvd    :   2;
    uint32      TNRE    :   1;
    uint32      FACE    :   1;
};

union   FEIRER_REG  {
    uint32              all;
    struct  TEIRER_BITS bit;
};

struct  TTSMS1_BITS {            //Trigger Transfer to System Memory Set 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TTSMS1_REG {
    uint32                  all;
    struct  TTSMS1_BITS     bit;
};

struct  TTSMS2_BITS {            //Trigger Transfer to System Memory Set 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TTSMS2_REG {
    uint32                  all;
    struct  TTSMS2_BITS     bit;
};

struct  TTSMS3_BITS {            //Trigger Transfer to System Memory Set 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TTSMS3_REG {
    uint32                  all;
    struct  TTSMS3_BITS     bit;
};

struct  TTSMS4_BITS {            //Trigger Transfer to System Memory Set 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TTSMS4_REG {
    uint32                  all;
    struct  TTSMS4_BITS     bit;
};


struct  TTSMR1_BITS {            //Trigger Transfer to System Memory Reset 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TTSMR1_REG {
    uint32                  all;
    struct  TTSMR1_BITS     bit;
};

struct  TTSMR2_BITS {            //Trigger Transfer to System Memory Reset 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TTSMR2_REG {
    uint32                  all;
    struct  TTSMR2_BITS     bit;
};

struct  TTSMR3_BITS {            //Trigger Transfer to System Memory Reset 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TTSMR3_REG {
    uint32                  all;
    struct  TTSMR3_BITS     bit;
};

struct  TTSMR4_BITS {            //Trigger Transfer to System Memory Reset 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TTSMR4_REG {
    uint32                  all;
    struct  TTSMR4_BITS     bit;
};

struct  TTCCS1_BITS {            //Trigger Transfer to Communication Controller Set 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TTCCS1_REG {
    uint32                  all;
    struct  TTCCS1_BITS     bit;
};

struct  TTCCS2_BITS {            //Trigger Transfer to Communication Controller Set 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TTCCS2_REG {
    uint32                  all;
    struct  TTCCS2_BITS     bit;
};

struct  TTCCS3_BITS {            //Trigger Transfer to Communication Controller Set 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TTCCS3_REG {
    uint32                  all;
    struct  TTCCS3_BITS     bit;
};

struct  TTCCS4_BITS {            //Trigger Transfer to System Memory Set 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TTCCS4_REG {
    uint32                  all;
    struct  TTCCS4_BITS     bit;
};

struct  TTCCR1_BITS {            //Trigger Transfer to Communication Controller Reset 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   TTCCR1_REG {
    uint32                  all;
    struct  TTCCR1_BITS     bit;
};

struct  TTCCR2_BITS {            //Trigger Transfer to Communication Controller Reset 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   TTCCR2_REG {
    uint32                  all;
    struct  TTCCR2_BITS     bit;
};

struct  TTCCR3_BITS {            //Trigger Transfer to Communication Controller Reset 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   TTCCR3_REG {
    uint32                  all;
    struct  TTCCR3_BITS     bit;
};

struct  TTCCR4_BITS {            //Trigger Transfer to System Memory Reset 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   TTCCR4_REG {
    uint32                  all;
    struct  TTCCR4_BITS     bit;
};


struct  ETESMS1_BITS {           // Enable Transfer on Event to System Memory Set 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   ETESMS1_REG {
    uint32                  all;
    struct  ETESMS1_BITS    bit;
};

struct  ETESMS2_BITS {            // Enable Transfer on Event to System Memory Set 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   ETESMS2_REG {
    uint32                  all;
    struct  ETESMS2_BITS    bit;
};

struct  ETESMS3_BITS {            // Enable Transfer on Event to System Memory Set 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   ETESMS3_REG {
    uint32                  all;
    struct  ETESMS3_BITS    bit;
};

struct  ETESMS4_BITS {            // Enable Transfer on Event to System Memory Set 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   ETESMS4_REG {
    uint32                  all;
    struct  ETESMS4_BITS    bit;
};

struct  ETESMR1_BITS {           // Enable Transfer on Event to System Memory Reset 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   ETESMR1_REG {
    uint32                  all;
    struct  ETESMR1_BITS    bit;
};

struct  ETESMR2_BITS {            // Enable Transfer on Event to System Memory Reset 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   ETESMR2_REG {
    uint32                  all;
    struct  ETESMR2_BITS    bit;
};

struct  ETESMR3_BITS {            // Enable Transfer on Event to System Memory Reset 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   ETESMR3_REG {
    uint32                  all;
    struct  ETESMR3_BITS    bit;
};

struct  ETESMR4_BITS {            // Enable Transfer on Event to System Memory Reset 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   ETESMR4_REG {
    uint32                  all;
    struct  ETESMR4_BITS    bit;
};

struct  CESMS1_BITS {           //  Clear on Event to System Memory Set 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   CESMS1_REG {
    uint32                  all;
    struct  CESMS1_BITS     bit;
};

struct  CESMS2_BITS {            //  Clear on Event to System Memory Set 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   CESMS2_REG {
    uint32                  all;
    struct  CESMS2_BITS     bit;
};

struct  CESMS3_BITS {            //  Clear on Event to System Memory Set 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   CESMS3_REG {
    uint32                  all;
    struct  CESMS3_BITS     bit;
};

struct  CESMS4_BITS {            //  Clear on Event to System Memory Set 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   CESMS4_REG {
    uint32                  all;
    struct  CESMS4_BITS     bit;
};

struct  CESMR1_BITS {           //  Clear on Event to System Memory Reset 1
    uint32      bit31   :   1;
    uint32      bit30   :   1;
    uint32      bit29   :   1;
    uint32      bit28   :   1;
    uint32      bit27   :   1;
    uint32      bit26   :   1;
    uint32      bit25   :   1;
    uint32      bit24   :   1;
    uint32      bit23   :   1;
    uint32      bit22   :   1;
    uint32      bit21   :   1;
    uint32      bit20   :   1;
    uint32      bit19   :   1;
    uint32      bit18   :   1;
    uint32      bit17   :   1;
    uint32      bit16   :   1;
    uint32      bit15   :   1;
    uint32      bit14   :   1;
    uint32      bit13   :   1;
    uint32      bit12   :   1;
    uint32      bit11   :   1;
    uint32      bit10   :   1;
    uint32      bit9    :   1;
    uint32      bit8    :   1;
    uint32      bit7    :   1;
    uint32      bit6    :   1;
    uint32      bit5    :   1;
    uint32      bit4    :   1;
    uint32      bit3    :   1;
    uint32      bit2    :   1;
    uint32      bit1    :   1;
    uint32      bit0    :   1;
};

union   CESMR1_REG {
    uint32                  all;
    struct  CESMR1_BITS     bit;
};

struct  CESMR2_BITS {            //  Clear on Event to System Memory Reset 2
    uint32      bit63   :   1;
    uint32      bit62   :   1;
    uint32      bit61   :   1;
    uint32      bit60   :   1;
    uint32      bit59   :   1;
    uint32      bit58   :   1;
    uint32      bit57   :   1;
    uint32      bit56   :   1;
    uint32      bit55   :   1;
    uint32      bit54   :   1;
    uint32      bit53   :   1;
    uint32      bit52   :   1;
    uint32      bit51   :   1;
    uint32      bit50   :   1;
    uint32      bit49   :   1;
    uint32      bit48   :   1;
    uint32      bit47   :   1;
    uint32      bit46   :   1;
    uint32      bit45   :   1;
    uint32      bit44   :   1;
    uint32      bit43   :   1;
    uint32      bit42   :   1;
    uint32      bit41   :   1;
    uint32      bit40   :   1;
    uint32      bit39   :   1;
    uint32      bit38   :   1;
    uint32      bit37   :   1;
    uint32      bit36   :   1;
    uint32      bit35   :   1;
    uint32      bit34   :   1;
    uint32      bit33   :   1;
    uint32      bit32   :   1;
};

union   CESMR2_REG {
    uint32                  all;
    struct  CESMR2_BITS     bit;
};

struct  CESMR3_BITS {            //  Clear on Event to System Memory Reset 3
    uint32      bit95   :   1;
    uint32      bit94   :   1;
    uint32      bit93   :   1;
    uint32      bit92   :   1;
    uint32      bit91   :   1;
    uint32      bit90   :   1;
    uint32      bit89   :   1;
    uint32      bit88   :   1;
    uint32      bit87   :   1;
    uint32      bit86   :   1;
    uint32      bit85   :   1;
    uint32      bit84   :   1;
    uint32      bit83   :   1;
    uint32      bit82   :   1;
    uint32      bit81   :   1;
    uint32      bit80   :   1;
    uint32      bit79   :   1;
    uint32      bit78   :   1;
    uint32      bit77   :   1;
    uint32      bit76   :   1;
    uint32      bit75   :   1;
    uint32      bit74   :   1;
    uint32      bit73   :   1;
    uint32      bit72   :   1;
    uint32      bit71   :   1;
    uint32      bit70   :   1;
    uint32      bit69   :   1;
    uint32      bit68   :   1;
    uint32      bit67   :   1;
    uint32      bit66   :   1;
    uint32      bit65   :   1;
    uint32      bit64   :   1;
};

union   CESMR3_REG {
    uint32                  all;
    struct  CESMR3_BITS     bit;
};

struct  CESMR4_BITS {            //  Clear on Event to System Memory Reset 4
    uint32      bit127  :   1;
    uint32      bit126  :   1;
    uint32      bit125  :   1;
    uint32      bit124  :   1;
    uint32      bit123  :   1;
    uint32      bit122  :   1;
    uint32      bit121  :   1;
    uint32      bit120  :   1;
    uint32      bit119  :   1;
    uint32      bit118  :   1;
    uint32      bit117  :   1;
    uint32      bit116  :   1;
    uint32      bit115  :   1;
    uint32      bit114  :   1;
    uint32      bit113  :   1;
    uint32      bit112  :   1;
    uint32      bit111  :   1;
    uint32      bit110  :   1;
    uint32      bit109  :   1;
    uint32      bit108  :   1;
    uint32      bit107  :   1;
    uint32      bit106  :   1;
    uint32      bit105  :   1;
    uint32      bit104  :   1;
    uint32      bit103  :   1;
    uint32      bit102  :   1;
    uint32      bit101  :   1;
    uint32      bit100  :   1;
    uint32      bit99   :   1;
    uint32      bit98   :   1;
    uint32      bit97   :   1;
    uint32      bit96   :   1;
};

union   CESMR4_REG {
    uint32                  all;
    struct  CESMR4_BITS     bit;
};

#endif /* USER_DRIVER_HL_REG_FLEXRAY_H_ */
