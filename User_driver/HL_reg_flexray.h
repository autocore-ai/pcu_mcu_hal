/******************************************************************
FileName   :HL_reg_flexray.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-11-25
****************************************************************/

#ifndef USER_DRIVER_HL_REG_FLEXRAY_H_
#define USER_DRIVER_HL_REG_FLEXRAY_H_

#include "HL_hal_stdtypes.h"


struct  GSN0_BITS {           //   Global Static Number 0  bit  description
    uint16  data_a  ;         //   Data_A
    uint16  data_b  ;         //   Complement of Data_A

};

/* Allow access to the bit fields or entire register */
union   GSN0_REG {
    uint32              all;
    struct  GSN0_BITS   bit;
};

struct  GSN1_BITS {           //   Global Static Number 0  bit  description
    uint16  data_c  ;         //   Data_C
    uint16  data_d  ;         //   Complement of Data_C

};

/* Allow access to the bit fields or entire register */
union   GSN1_REG {
    uint32              all;
    struct  GSN1_BITS   bit;
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
    uint32      BN      :   7;
};

union   LTBCC_REG {
    uint32              all;
    struct  LTBCC_BITS  bit;
};

struct  LTBSM_BITS {            //Last Transferred Buffer to Communication Controller
    uint32      rsvd    :   25;
    uint32      BN      :   7;
};

union   LTBSM_REG {
    uint32              all;
    struct  LTBSM_BITS  bit;
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
    uint32      rsvd2   :   2;
    uint32      TNRE    :   1;
    uint32      FACE    :   1;
};

union   TEIRES_REG  {
    uint32              all;
    struct  TEIRES_BITS bit;
};

struct  TEIRER_BITS {           //Transfer Error Interrupt Enable Reset
    uint32      rsvd    :   21;
    uint32      RSTATE  :   3;
    uint32      rsvd1   :   1;
    uint32      WSTATE  :   3;
    uint32      rsvd2   :   2;
    uint32      TNRE    :   1;
    uint32      FACE    :   1;
};

union   TEIRER_REG  {
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

struct  TSMIES1_BITS {           //  Transfer to System Memory Interrupt Enable Set 1
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

union   TSMIES1_REG {
    uint32                  all;
    struct  TSMIES1_BITS    bit;
};

struct  TSMIES2_BITS {           //  Transfer to System Memory Interrupt Enable Set 2
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

union   TSMIES2_REG {
    uint32                  all;
    struct  TSMIES2_BITS    bit;
};

struct  TSMIES3_BITS {           //  Transfer to System Memory Interrupt Enable Set 3
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

union   TSMIES3_REG {
    uint32                  all;
    struct  TSMIES3_BITS    bit;
};

struct  TSMIES4_BITS {           //  Transfer to System Memory Interrupt Enable Set 4
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

union   TSMIES4_REG {
    uint32                  all;
    struct  TSMIES4_BITS    bit;
};

struct  TSMIER1_BITS {           //  Transfer to System Memory Interrupt Enable ReSet 1
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

union   TSMIER1_REG {
    uint32                  all;
    struct  TSMIER1_BITS    bit;
};

struct  TSMIER2_BITS {           //  Transfer to System Memory Interrupt Enable ReSet 2
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

union   TSMIER2_REG {
    uint32                  all;
    struct  TSMIER2_BITS    bit;
};

struct  TSMIER3_BITS {           //  Transfer to System Memory Interrupt Enable ReSet 3
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

union   TSMIER3_REG {
    uint32                  all;
    struct  TSMIER3_BITS    bit;
};

struct  TSMIER4_BITS {           //  Transfer to System Memory Interrupt Enable ReSet 4
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

union   TSMIER4_REG {
    uint32                  all;
    struct  TSMIER4_BITS    bit;
};

struct  TCCIES1_BITS {           //  Transfer to Communication Controller Interrupt Enable Set 1
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

union   TCCIES1_REG {
    uint32                  all;
    struct  TCCIES1_BITS    bit;
};

struct  TCCIES2_BITS {            //Transfer to Communication Controller Interrupt Enable Set 2
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

union   TCCIES2_REG {
    uint32                  all;
    struct  TCCIES2_BITS    bit;
};

struct  TCCIES3_BITS {            //Transfer to Communication Controller Interrupt Enable Set 3
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

union   TCCIES3_REG {
    uint32                  all;
    struct  TCCIES3_BITS    bit;
};

struct  TCCIES4_BITS {            // Transfer to Communication Controller Interrupt Enable Set 4
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

union   TCCIES4_REG {
    uint32                  all;
    struct  TCCIES4_BITS    bit;
};

struct  TCCIER1_BITS {           //  Transfer to Communication Controller Interrupt Enable ReSet 1
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

union   TCCIER1_REG {
    uint32                  all;
    struct  TCCIER1_BITS    bit;
};

struct  TCCIER2_BITS {            //Transfer to Communication Controller Interrupt Enable ReSet 2
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

union   TCCIER2_REG {
    uint32                  all;
    struct  TCCIER2_BITS    bit;
};

struct  TCCIER3_BITS {            //Transfer to Communication Controller Interrupt Enable RESet 3
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

union   TCCIER3_REG {
    uint32                  all;
    struct  TCCIER3_BITS    bit;
};

struct  TCCIER4_BITS {            // Transfer to Communication Controller Interrupt Enable Set 4
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

union   TCCIER4_REG {
    uint32                  all;
    struct  TCCIER4_BITS    bit;
};

struct  TCR_BITS {           //Transfer Configuration RAM
    uint32      rsvd    :   13;
    uint32      STXR    :   1;
    uint32      THTSM   :   1;
    uint32      TPTSM   :   1;
    uint32      THTCC   :   1;
    uint32      TPTCC   :   1;
    uint32      TSO     :   14;
};

union   TCR_REG  {
    uint32              all;
    struct  TCR_BITS    bit;
};

struct  TCRECC_BITS {           //TCR ECC Test Mode
    uint32      rsvd    :   26;
    uint32      ECCINF  :   6;
};

union   TCRECC_REG  {
    uint32              all;
    struct  TCRECC_BITS bit;
};

struct  ECC_CTRL_BITS {           // ECC Control Register
    uint32      rsvd        :   4;
    uint32      SBE_EVT_EN  :   4;
    uint32      rsvd1       :   4;
    uint32      SBEL        :   4;
    uint32      rsvd2       :   12;
    uint32      DIAGSEL     :   4;
};

union   ECC_CTRL_REG  {
    uint32                  all;
    struct  ECC_CTRL_BITS   bit;
};

struct  ECCDSTAT_BITS {           // ECC Diagnostic Status Register
    uint32      rsvd1       :   8;
    uint32      DEFH        :   1;
    uint32      DEFG        :   1;
    uint32      DEFF        :   1;
    uint32      DEFE        :   1;
    uint32      DEFD        :   1;
    uint32      DEFC        :   1;
    uint32      DEFB        :   1;
    uint32      DEFA        :   1;
    uint32      rsvd2       :   8;
    uint32      SEFH        :   1;
    uint32      SEFG        :   1;
    uint32      SEFF        :   1;
    uint32      SEFE        :   1;
    uint32      SEFD        :   1;
    uint32      SEFC        :   1;
    uint32      SEFB        :   1;
    uint32      SEFA        :   1;
};

union   ECCDSTAT_REG  {
    uint32                  all;
    struct  ECCDSTAT_BITS   bit;
};

struct  ECCTEST_BITS {           // ECC Test Register
    uint32      rsvd1       :   9;
    uint32      RDECC       :   7;
    uint32      rsvd2       :   9;
    uint32      WRECC       :   7;
};

union   ECCTEST_REG  {
    uint32                  all;
    struct  ECCTEST_BITS    bit;
};

struct  SBESTAT_BITS {           // Single-Bit Error Status Register
    uint32      SBE         :   1;
    uint32      rsvd1       :   16;
    uint32      FMB         :   7;
    uint32      rsvd2       :   1;
    uint32      MFMB        :   1;
    uint32      MFMD        :   1;
    uint32      STBF2       :   1;
    uint32      STBF1       :   1;
    uint32      SMR         :   1;
    uint32      SOBF        :   1;
    uint32      SIBF        :   1;
};

union   SBESTAT_REG  {
    uint32                  all;
    struct  SBESTAT_BITS    bit;
};

struct  TEST1_BITS {           // Test Register 1
    uint32      CERB        :   4;
    uint32      CERA        :   4;
    uint32      rsvd1       :   2;
    uint32      TXENB       :   1;
    uint32      TXENA       :   1;
    uint32      TXB         :   1;
    uint32      TXA         :   1;
    uint32      RXB         :   1;
    uint32      RXA         :   1;
    uint32      rsvd2       :   6;
    uint32      AOB         :   1;
    uint32      AOA         :   1;
    uint32      rsvd3       :   2;
    uint32      TMC         :   2;
    uint32      rsvd4       :   2;
    uint32      ELBE        :   1;
    uint32      WRTEN       :   1;
};

union   TEST1_REG  {
    uint32                  all;
    struct  TEST1_BITS      bit;
};

struct  TEST2_BITS {           // Test Register 2
    uint32      rsvd1       :   16;
    uint32      RDPB        :   1;
    uint32      WRPB        :   1;
    uint32      rsvd2       :   7;
    uint32      SSEL        :   3;
    uint32      rsvd3       :   1;
    uint32      RS          :   3;
};

union   TEST2_REG  {
    uint32                  all;
    struct  TEST2_BITS      bit;
};

struct  LCK_BITS {           // Test Register 2
    uint32      rsvd1       :   16;
    uint32      TMK         :   8;
    uint32      CLK         :   8;
};

union   LCK_REG  {
    uint32                  all;
    struct  LCK_BITS        bit;
};

struct  EIR_BITS {                // Error Interrupt Register
    uint32      rsvd1       :   5;
    uint32      TABB        :   1;
    uint32      LTVB        :   1;
    uint32      EDB         :   1;
    uint32      rsvd2       :   5;
    uint32      TABA        :   1;
    uint32      LTVA        :   1;
    uint32      EDA         :   1;
    uint32      rsvd3       :   4;
    uint32      MHF         :   1;
    uint32      IOBA        :   1;
    uint32      IIBA        :   1;
    uint32      EFA         :   1;
    uint32      RFO         :   1;
    uint32      PERR        :   1;
    uint32      CCL         :   1;
    uint32      CCF         :   1;
    uint32      SFO         :   1;
    uint32      SFBM        :   1;
    uint32      CNA         :   1;
    uint32      PEMC        :   1;
};

union   EIR_REG  {
    uint32                  all;
    struct  EIR_BITS        bit;
};

struct  SIR_BITS {                // Status Interrupt Register
    uint32      rsvd1       :   6;
    uint32      MTSB        :   1;
    uint32      WUPB        :   1;
    uint32      rsvd2       :   6;
    uint32      MTSA        :   1;
    uint32      WUPA        :   1;
    uint32      SDS         :   1;
    uint32      MBSI        :   1;
    uint32      SUCS        :   1;
    uint32      SWE         :   1;
    uint32      TOBC        :   1;
    uint32      TIBC        :   1;
    uint32      TI1         :   1;
    uint32      TI0         :   1;
    uint32      NMVC        :   1;
    uint32      RFCL        :   1;
    uint32      RFNE        :   1;
    uint32      RXI         :   1;
    uint32      TXI         :   1;
    uint32      CYCS        :   1;
    uint32      CAS         :   1;
    uint32      WST         :   1;
};

union   SIR_REG  {
    uint32                  all;
    struct  SIR_BITS        bit;
};


struct  EILS_BITS {                //Error Interrupt Line Select
    uint32      rsvd1       :   5;
    uint32      TABBL       :   1;
    uint32      LTVBL       :   1;
    uint32      EDBL        :   1;
    uint32      rsvd2       :   5;
    uint32      TABAL       :   1;
    uint32      LTVAL       :   1;
    uint32      EDAL        :   1;
    uint32      rsvd3       :   4;
    uint32      MHFL        :   1;
    uint32      IOBAL       :   1;
    uint32      IIBAL       :   1;
    uint32      EFAL        :   1;
    uint32      RFOL        :   1;
    uint32      UCREL       :   1;
    uint32      CCLL        :   1;
    uint32      CCFL        :   1;
    uint32      SFOL        :   1;
    uint32      SFBML       :   1;
    uint32      CNAL        :   1;
    uint32      PEMCL       :   1;
};

union   EILS_REG  {
    uint32                  all;
    struct  EILS_BITS       bit;
};

struct  SILS_BITS {                //Status Interrupt Line Select
    uint32      rsvd1       :   6;
    uint32      MTSBL       :   1;
    uint32      WUPBL       :   1;
    uint32      rsvd2       :   6;
    uint32      MTSAL       :   1;
    uint32      WUPAL       :   1;
    uint32      SDSL        :   1;
    uint32      MBSIL       :   1;
    uint32      SUCSL       :   1;
    uint32      SWEL        :   1;
    uint32      TOBCL       :   1;
    uint32      TIBCL       :   1;
    uint32      TI1L        :   1;
    uint32      TI0L        :   1;
    uint32      NMVCL       :   1;
    uint32      RFFL        :   1;
    uint32      RFNEL       :   1;
    uint32      RXIL        :   1;
    uint32      TXIL        :   1;
    uint32      CYCSL       :   1;
    uint32      CASL        :   1;
    uint32      WSTL        :   1;
};
union   SILS_REG  {
    uint32                  all;
    struct  SILS_BITS       bit;
};


struct  SIES_BITS {                //Status Interrupt Enable Set / Reset Register
    uint32      rsvd1       :   6;
    uint32      MTSBE       :   1;
    uint32      WUPBE       :   1;
    uint32      rsvd2       :   6;
    uint32      MTSAE       :   1;
    uint32      WUPAE       :   1;
    uint32      SDSE        :   1;
    uint32      MBSIE       :   1;
    uint32      SUCSE       :   1;
    uint32      SWEE        :   1;
    uint32      TOBCE       :   1;
    uint32      TIBCE       :   1;
    uint32      TI1E        :   1;
    uint32      TI0E        :   1;
    uint32      NMVCE       :   1;
    uint32      RFFE        :   1;
    uint32      RFNEE       :   1;
    uint32      RXIE        :   1;
    uint32      TXIE        :   1;
    uint32      CYCSE       :   1;
    uint32      CASE        :   1;
    uint32      WSTE        :   1;
};

union   SIES_REG  {
    uint32                  all;
    struct  SIES_BITS       bit;
};
union   SIER_REG  {               //Status Interrupt Enable Set / Reset Register
    uint32                  all;
    struct  SIES_BITS       bit;
};


struct  EIES_BITS {                // Error Interrupt Enable Set
    uint32      rsvd1       :   5;
    uint32      TABBE       :   1;
    uint32      LTVBE       :   1;
    uint32      EDBE        :   1;
    uint32      rsvd2       :   5;
    uint32      TABAE       :   1;
    uint32      LTVAE       :   1;
    uint32      EDAE        :   1;
    uint32      rsvd3       :   4;
    uint32      MHFE        :   1;
    uint32      IOBAE       :   1;
    uint32      IIBAE       :   1;
    uint32      EFAE        :   1;
    uint32      RFOE        :   1;
    uint32      UCREE       :   1;
    uint32      CCLE        :   1;
    uint32      CCFE        :   1;
    uint32      SFOE        :   1;
    uint32      SFBME       :   1;
    uint32      CNAE        :   1;
    uint32      PEMCE       :   1;
};

union   EIES_REG  {
    uint32                  all;
    struct  EIES_BITS       bit;
};

struct  EIER_BITS {                // Error Interrupt Enable Reset
    uint32      rsvd1       :   5;
    uint32      TABBE       :   1;
    uint32      LTVBE       :   1;
    uint32      EDBE        :   1;
    uint32      rsvd2       :   5;
    uint32      TABAE       :   1;
    uint32      LTVAE       :   1;
    uint32      EDAE        :   1;
    uint32      rsvd3       :   4;
    uint32      MHFE        :   1;
    uint32      IOBAE       :   1;
    uint32      IIBAE       :   1;
    uint32      EFAE        :   1;
    uint32      RFOE        :   1;
    uint32      UCREE       :   1;
    uint32      CCLE        :   1;
    uint32      CCFE        :   1;
    uint32      SFOE        :   1;
    uint32      SFBME       :   1;
    uint32      CNAE        :   1;
    uint32      PEMCE       :   1;
};

union   EIER_REG  {
    uint32                  all;
    struct  EIER_BITS       bit;
};

struct  ILE_BITS {                // Interrupt Line Enable Register
    uint32      rsvd1       :   30;
    uint32      EINT        :   2;
};

union   ILE_REG  {
    uint32                  all;
    struct  ILE_BITS        bit;
};

struct  T0C_BITS {                // Timer 0 Configuration Register
    uint32      rsvd1       :   2;
    uint32      TOMO        :   14;
    uint32      rsvd2       :   1;
    uint32      TOCC        :   7;
    uint32      rsvd3       :   6;
    uint32      TOMS        :   1;
    uint32      TORC        :   1;
};

union   T0C_REG  {
    uint32                  all;
    struct  T0C_BITS        bit;
};

struct  T1C_BITS {                // Timer 1 Configuration Register
    uint32      rsvd1       :   2;
    uint32      TIMC        :   14;
    uint32      rsvd2       :   14;
    uint32      TIMS        :   1;
    uint32      T1RC        :   1;
};

union   T1C_REG  {
    uint32                  all;
    struct  T1C_BITS        bit;
};

struct  STPW1_BITS {                // Stop Watch Register 1 Register
    uint32      rsvd1       :   2;
    uint32      SMTV        :   14;
    uint32      rsvd2       :   2;
    uint32      SCCV        :   6;
    uint32      rsvd3       :   1;
    uint32      EINT1       :   1;
    uint32      EINT0       :   1;
    uint32      EETP        :   1;
    uint32      SSWT        :   1;
    uint32      EDGE        :   1;
    uint32      SWMS        :   1;
    uint32      ESWT        :   1;
};

union   STPW1_REG  {
    uint32                  all;
    struct  STPW1_BITS      bit;
};

struct  STPW2_BITS {                // Stop Watch Register 2 Register
    uint32      rsvd1       :   5;
    uint32      SSCVB       :   11;
    uint32      rsvd2       :   5;
    uint32      SSCVA       :   11;
};

union   STPW2_REG  {
    uint32                  all;
    struct  STPW2_BITS      bit;
};

struct  SUCC1_BITS {                // SUC Configuration Register 1
    uint32      rsvd1       :   4;
    uint32      CCHB        :   1;
    uint32      CCHA        :   1;
    uint32      MTSB        :   1;
    uint32      MTSA        :   1;
    uint32      HCSE        :   1;
    uint32      TSM         :   1;
    uint32      WUCS        :   1;
    uint32      PTA         :   5;
    uint32      CSA         :   5;
    uint32      rsvd2       :   1;
    uint32      TXSY        :   1;
    uint32      TXST        :   1;
    uint32      PBSY        :   1;
    uint32      rsvd        :   3;
    uint32      CMD         :   4;
};

union   SUCC1_REG  {
    uint32                  all;
    struct  SUCC1_BITS      bit;
};

struct  SUCC2_BITS {                // SUC Configuration Register 2
    uint32      rsvd1       :   4;
    uint32      LTN         :   4;
    uint32      rsvd2       :   3;
    uint32      LT          :   21;
};

union   SUCC2_REG  {
    uint32                  all;
    struct  SUCC2_BITS      bit;
};

struct  SUCC3_BITS {                // SUC Configuration Register 3
    uint32      rsvd1       :   24;
    uint32      WCF         :   4;
    uint32      WCP         :   4;
};

union   SUCC3_REG  {
    uint32                  all;
    struct  SUCC3_BITS      bit;
};

struct  NEMC_BITS {                // NEM Configuration Register
    uint32      rsvd1       :   28;
    uint32      NML         :   4;
};

union   NEMC_REG  {
    uint32                  all;
    struct  NEMC_BITS       bit;
};

struct  PRTC1_BITS {                // PRT Configuration Register 1
    uint32      RPW         :   6;
    uint32      rsvd1       :   1;
    uint32      RXW         :   9;
    uint32      BRP         :   2;
    uint32      SSP         :   2;
    uint32      rsvd2       :   1;
    uint32      CASM        :   7;
    uint32      TSST        :   4;
};

union   PRTC1_REG  {
    uint32                  all;
    struct  PRTC1_BITS      bit;
};

struct  PRTC2_BITS {                // PRT Configuration Register 2
    uint32      rsvd1       :   2;
    uint32      TXL         :   6;
    uint32      TXI         :   8;
    uint32      rsvd2       :   2;
    uint32      RXL         :   6;
    uint32      rsvd3       :   2;
    uint32      RXI         :   6;
};

union   PRTC2_REG  {
    uint32                  all;
    struct  PRTC2_BITS      bit;
};

struct  MHDC_BITS {                // MHD Configuration Register
    uint32      rsvd1       :   3;
    uint32      SLT         :   13;
    uint32      rsvd2       :   9;
    uint32      SFDL        :   7;
};

union   MHDC_REG  {
    uint32                  all;
    struct  MHDC_BITS       bit;
};

struct  GTUC1_BITS {                // GTU Configuration Register 1
    uint32      rsvd1       :   12;
    uint32      UT          :   20;
};

union   GTUC1_REG  {
    uint32                  all;
    struct  GTUC1_BITS      bit;
};

struct  GTUC2_BITS {                // GTU Configuration Register 2
    uint32      rsvd1       :   12;
    uint32      SNM         :   4;
    uint32      rsvd2       :   2;
    uint32      MPC         :   14;
};

union   GTUC2_REG  {
    uint32                  all;
    struct  GTUC2_BITS      bit;
};

struct  GTUC3_BITS {                // GTU Configuration Register 3
    uint32      rsvd1       :   1;
    uint32      MIOB        :   7;
    uint32      rsvd2       :   1;
    uint32      MIOA        :   7;
    uint32      UIOB        :   8;
    uint32      UIOA        :   8;
};

union   GTUC3_REG  {
    uint32                  all;
    struct  GTUC3_BITS      bit;
};


struct  GTUC4_BITS {                // GTU Configuration Register 4
    uint32      rsvd1       :   2;
    uint32      OCS         :   14;
    uint32      rsvd2       :   2;
    uint32      NIT         :   14;
};

union   GTUC4_REG  {
    uint32                  all;
    struct  GTUC4_BITS      bit;
};

struct  GTUC5_BITS {                // GTU Configuration Register 5
    uint32      DEC         :   8;
    uint32      rsvd1       :   3;
    uint32      CDD         :   5;
    uint32      DCB         :   8;
    uint32      DCA         :   8;
};

union   GTUC5_REG  {
    uint32                  all;
    struct  GTUC5_BITS      bit;
};


struct  GTUC6_BITS {                // GTU Configuration Register 6
    uint32      rsvd1       :   5;
    uint32      MOD         :   11;
    uint32      rsvd2       :   5;
    uint32      ASR         :   11;
};

union   GTUC6_REG  {
    uint32                  all;
    struct  GTUC6_BITS      bit;
};

struct  GTUC7_BITS {                // GTU Configuration Register 7
    uint32      rsvd1       :   6;
    uint32      NSS         :   10;
    uint32      rsvd2       :   6;
    uint32      SSL         :   10;
};

union   GTUC7_REG  {
    uint32                  all;
    struct  GTUC7_BITS      bit;
};

struct  GTUC8_BITS {                // GTU Configuration Register 8
    uint32      rsvd1       :   3;
    uint32      NMS         :   13;
    uint32      rsvd2       :   10;
    uint32      MSL         :   6;
};

union   GTUC8_REG  {
    uint32                  all;
    struct  GTUC8_BITS      bit;
};

struct  GTUC9_BITS {                // GTU Configuration Register 9
    uint32      rsvd1       :   14;
    uint32      DSI         :   2;
    uint32      rsvd2       :   3;
    uint32      MAPO        :   5;
    uint32      rsvd3       :   2;
    uint32      APO         :   6;
};

union   GTUC9_REG  {
    uint32                  all;
    struct  GTUC9_BITS      bit;
};

struct  GTUC10_BITS {                // GTU Configuration Register 10
    uint32      rsvd1       :   5;
    uint32      MRC         :   11;
    uint32      rsvd2       :   2;
    uint32      MOC         :   14;
};

union   GTUC10_REG  {
    uint32                  all;
    struct  GTUC10_BITS     bit;
};

struct  GTUC11_BITS {                // GTU Configuration Register 11
    uint32      rsvd1       :   5;
    uint32      ERC         :   3;
    uint32      rsvd2       :   5;
    uint32      EOC         :   3;
    uint32      rsvd3       :   6;
    uint32      ERCC        :   2;
    uint32      rsvd4       :   6;
    uint32      EOCC        :   2;
};

union   GTUC11_REG  {
    uint32                  all;
    struct  GTUC11_BITS     bit;
};

struct  CCSV_BITS {                // Communication Controller Status Vector
    uint32      rsvd1       :   2;
    uint32      PSL         :   6;
    uint32      RCA         :   5;
    uint32      WSV         :   3;
    uint32      rsvd2       :   1;
    uint32      CSI         :   1;
    uint32      CSAI        :   1;
    uint32      CSNI        :   1;
    uint32      rsvd3       :   2;
    uint32      SLM         :   2;
    uint32      HQR         :   1;
    uint32      FSI         :   1;
    uint32      POCS        :   6;
};

union   CCSV_REG  {
    uint32                  all;
    struct    CCSV_BITS     bit;
};

struct  CCEV_BITS {                // Communication Controller Error Vector
    uint32      rsvd1       :   19;
    uint32      PTAC        :   5;
    uint32      ERRM        :   2;
    uint32      rsvd2       :   2;
    uint32      CCFC        :   4;
};

union   CCEV_REG  {
    uint32                  all;
    struct    CCEV_BITS     bit;
};

struct  SCV_BITS {                // Communication Controller Error Vector
    uint32      rsvd1       :   5;
    uint32      SCCB        :   11;
    uint32      rsvd2       :   5;
    uint32      SCCA        :   11;
};

union   SCV_REG  {
    uint32                  all;
    struct    SCV_BITS      bit;
};

struct  MTCCV_BITS {                // Macrotick and Cycle Counter Value
    uint32      rsvd1       :   10;
    uint32      CCV         :   6;
    uint32      rsvd2       :   2;
    uint32      MTV         :   14;
};

union   MTCCV_REG  {
    uint32                  all;
    struct    MTCCV_BITS    bit;
};

struct  RCV_BITS {                // Rate Correction Value
    uint32      rsvd1       :   20;
    uint32      RCV         :   12;
};

union   RCV_REG  {
    uint32                  all;
    struct    RCV_BITS      bit;
};

struct  OCV_BITS {                // Offset Correction Value
    uint32      rsvd1       :   12;
    uint32      OCV         :   20;
};

union   OCV_REG  {
    uint32                  all;
    struct    OCV_BITS      bit;
};

struct  SFS_BITS {                // Sync Frame Status
    uint32      rsvd1       :   12;
    uint32      RCLR        :   1;
    uint32      MRCS        :   1;
    uint32      OCLR        :   1;
    uint32      MOCS        :   1;
    uint32      VSBO        :   4;
    uint32      VSBE        :   4;
    uint32      VSAO        :   4;
    uint32      VSAE        :   4;

};

union   SFS_REG  {
    uint32                  all;
    struct    SFS_BITS      bit;
};

struct  SWNIT_BITS {                // Symbol Window and NIT Status
    uint32      rsvd1       :   20;
    uint32      SBNB        :   1;
    uint32      SENB        :   1;
    uint32      SBNA        :   1;
    uint32      SENA        :   1;
    uint32      MTSB        :   1;
    uint32      MTSA        :   1;
    uint32      TCSB        :   1;
    uint32      SBSB        :   1;
    uint32      SESB        :   1;
    uint32      TCSA        :   1;
    uint32      SBSA        :   1;
    uint32      SESA        :   1;

};

union   SWNIT_REG  {
    uint32                  all;
    struct    SWNIT_BITS    bit;
};

struct  ACS_BITS {                // Symbol Window and NIT Status
    uint32      rsvd1       :   19;
    uint32      SBVB        :   1;
    uint32      CIB         :   1;
    uint32      CEDB        :   1;
    uint32      SEDB        :   1;
    uint32      VFRB        :   1;
    uint32      rsvd2       :   3;
    uint32      SBVA        :   1;
    uint32      CIA         :   1;
    uint32      CEDA        :   1;
    uint32      SEDA        :   1;
    uint32      VFRA        :   1;

};

union   ACS_REG  {
    uint32                  all;
    struct    ACS_BITS      bit;
};

struct  ESID_BITS {                // Even Sync ID Registers
    uint32      rsvd1       :   16;
    uint32      RXEB        :   1;
    uint32      RXEA        :   1;
    uint32      rsvd2       :   4;
    uint32      EID         :   10;

};

union   ESID_REG  {
    uint32                  all;
    struct    ESID_BITS     bit;
};

struct  OSID_BITS {                // Odd Sync ID Registers
    uint32      rsvd1       :   16;
    uint32      RXOB        :   1;
    uint32      RXOA        :   1;
    uint32      rsvd2       :   4;
    uint32      OID         :   10;

};

union   OSID_REG  {
    uint32                  all;
    struct    OSID_BITS     bit;
};

struct  NMV1_BITS {                // Network Management Vector Registers
    uint32      DATA3       :   8;
    uint32      DATA2       :   8;
    uint32      DATA1       :   8;
    uint32      DATA0       :   8;

};

union   NMV1_REG  {
    uint32                  all;
    struct    NMV1_BITS     bit;
};

struct  NMV2_BITS {                // Network Management Vector Registers
    uint32      DATA7       :   8;
    uint32      DATA6       :   8;
    uint32      DATA5       :   8;
    uint32      DATA4       :   8;

};

union   NMV2_REG  {
    uint32                  all;
    struct    NMV2_BITS     bit;
};


struct  NMV3_BITS {                // Network Management Vector Registers
    uint32      DATA11      :   8;
    uint32      DATA10      :   8;
    uint32      DATA9       :   8;
    uint32      DATA8       :   8;

};

union   NMV3_REG  {
    uint32                  all;
    struct    NMV3_BITS     bit;
};


struct  MRC_BITS {                // Network Management Vector Registers
    uint32      rsvd1       :   5;
    uint32      SPLM        :   1;
    uint32      SEC         :   2;
    uint32      LCB         :   8;
    uint32      FFB         :   8;
    uint32      FDB         :   8;
};

union   MRC_REG  {
    uint32                  all;
    struct    MRC_BITS      bit;
};


struct  FRF_BITS {                //FIFO Rejection Filter
    uint32      rsvd1       :   7;
    uint32      RNF         :   1;
    uint32      RSS         :   1;
    uint32      CYF         :   7;
    uint32      rsvd2       :   3;
    uint32      FID         :   11;
    uint32      CH          :   2;
};

union   FRF_REG  {
    uint32                  all;
    struct    FRF_BITS      bit;
};

struct  FRFM_BITS {                // FIFO Rejection Filter Mask
    uint32      rsvd1       :   19;
    uint32      MFID        :   11;
    uint32      rsvd2       :   2;
};

union   FRFM_REG  {
    uint32                  all;
    struct    FRFM_BITS     bit;
};

struct  FCL_BITS {                // FIFO Rejection Filter Mask
    uint32      rsvd1       :   24;
    uint32      CL          :   8;
};

union   FCL_REG  {
    uint32                  all;
    struct    FCL_BITS      bit;
};


struct  MHDS_BITS {                // Message Handler Status
    uint32      rsvd1       :   1;
    uint32      MBU         :   7;
    uint32      rsvd2       :   1;
    uint32      MBT         :   7;
    uint32      rsvd3       :   1;
    uint32      FMB         :   7;
    uint32      CRAM        :   1;
    uint32      MFMB        :   1;
    uint32      FMBD        :   1;
    uint32      PTFB2       :   1;
    uint32      PTFB1       :   1;
    uint32      PMR         :   1;
    uint32      POBF        :   1;
    uint32      PIBF        :   1;
};

union   MHDS_REG  {
    uint32                  all;
    struct    MHDS_BITS     bit;
};

struct  LDTS_BITS {                //Last Dynamic Transmit Slot
    uint32      rsvd1       :   5;
    uint32      LDTB        :   11;
    uint32      rsvd2       :   5;
    uint32      LDTA        :   11;
};

union   LDTS_REG  {
    uint32                  all;
    struct    LDTS_BITS     bit;
};


struct  FSR_BITS {                // FIFO Status Register
    uint32      rsvd1       :   16;
    uint32      RFFL        :   8;
    uint32      rsvd2       :   5;
    uint32      RFO         :   1;
    uint32      RFCL        :   1;
    uint32      RFNE        :   1;
};

union   FSR_REG  {
    uint32                  all;
    struct    FSR_BITS      bit;
};

struct  MHDF_BITS {                // FIFO Status Register
    uint32      rsvd1       :   23;
    uint32      WAHP        :   1;
    uint32      TNSA        :   1;
    uint32      TNSB        :   1;
    uint32      TBFB        :   1;
    uint32      TBFA        :   1;
    uint32      FNFB        :   1;
    uint32      FNFA        :   1;
    uint32      SNUB        :   1;
    uint32      SNUA        :   1;
};

union   MHDF_REG  {
    uint32                  all;
    struct    MHDF_BITS     bit;
};


struct  TXRQ1_BITS {           //  Transmission Request Registers
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

union   TXRQ1_REG {
    uint32                  all;
    struct  TXRQ1_BITS      bit;
};

struct  TXRQ2_BITS {            // Transmission Request Registers 2
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

union   TXRQ2_REG {
    uint32                  all;
    struct  TXRQ2_BITS      bit;
};

struct  TXRQ3_BITS {            //Transmission Request Registers 3
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

union   TXRQ3_REG {
    uint32                  all;
    struct  TXRQ3_BITS      bit;
};

struct  TXRQ4_BITS {            // Transmission Request Registers 4
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

union   TXRQ4_REG {
    uint32                  all;
    struct  TXRQ4_BITS      bit;
};

struct  NDAT1_BITS {           //  New Data Registers 1
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

union   NDAT1_REG {
    uint32                  all;
    struct  NDAT1_BITS      bit;
};

struct  NDAT2_BITS {            // New Data Registers 2
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

union   NDAT2_REG {
    uint32                  all;
    struct  NDAT2_BITS      bit;
};

struct  NDAT3_BITS {            //New Data Registers 3
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

union   NDAT3_REG {
    uint32                  all;
    struct  NDAT3_BITS      bit;
};

struct  NDAT4_BITS {            // New Data Registers 4
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

union   NDAT4_REG {
    uint32                  all;
    struct  NDAT4_BITS      bit;
};

struct  MBSC1_BITS {           // Message Buffer Status Changed Registers  1
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

union   MBSC1_REG {
    uint32                  all;
    struct  MBSC1_BITS      bit;
};

struct  MBSC2_BITS {            // Message Buffer Status Changed Registers  2
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

union   MBSC2_REG {
    uint32                  all;
    struct  MBSC2_BITS      bit;
};

struct  MBSC3_BITS {            //Message Buffer Status Changed Registers  3
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

union   MBSC3_REG {
    uint32                  all;
    struct  MBSC3_BITS      bit;
};

struct  MBSC4_BITS {            // Message Buffer Status Changed Registers  4
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

union   MBSC4_REG {
    uint32                  all;
    struct  MBSC4_BITS      bit;
};

struct  CREL_BITS {       //Core Release Register
    uint32      CREL    :   4;
    uint32      STEP    :   8;
    uint32      YEAR    :   4;
    uint32      MON     :   8;
    uint32      DAY     :   8;
};

union   CREL_REG {
    uint32              all;
    struct  CREL_BITS   bit;
};


struct  WRHS1_BITS {       //Write Header Section Register
    uint32      rsvd1   :   2;
    uint32      MBI     :   1;
    uint32      TXM     :   1;
    uint32      PPIT    :   1;
    uint32      CFG     :   1;
    uint32      CHB     :   1;
    uint32      CHA     :   1;
    uint32      rsvd2   :   1;
    uint32      CYC     :   7;
    uint32      rsvd3   :   5;
    uint32      FID     :   11;
};

union   WRHS1_REG {
    uint32              all;
    struct  WRHS1_BITS  bit;
};


struct  WRHS2_BITS {       //Write Header Section Register
    uint32      rsvd1   :   9;
    uint32      PLC     :   6;
    uint32      rsvd2   :   5;
    uint32      CRC     :   11;
};

union   WRHS2_REG {
    uint32              all;
    struct  WRHS2_BITS  bit;
};

struct  WRHS3_BITS {       //Write Header Section Register
    uint32      rsvd1   :   21;
    uint32      DP      :   11;
};

union   WRHS3_REG {
    uint32              all;
    struct  WRHS3_BITS  bit;
};


struct  IBCM_BITS {       //Input Buffer Command Mask Register
    uint32      rsvd1   :   13;
    uint32      STXRS   :   1;
    uint32      LDSS    :   1;
    uint32      LHSS    :   11;
    uint32      rsvd2   :   13;
    uint32      STXRH   :   1;
    uint32      LDSH    :   1;
    uint32      LHSH    :   11;
};

union   IBCM_REG {
    uint32              all;
    struct  IBCM_BITS   bit;
};

struct  IBCR_BITS {       //Input Buffer Command Mask Register
    uint32      IBSYS   :   1;
    uint32      rsvd1   :   8;
    uint32      IBRS    :   7;
    uint32      IBSYH   :   1;
    uint32      rsvd2   :   8;
    uint32      IBRH    :   7;
};

union   IBCR_REG {
    uint32              all;
    struct  IBCR_BITS   bit;
};

struct  RDHS1_BITS {       //Read Header Section Register
    uint32      rsvd1   :   2;
    uint32      MBI     :   1;
    uint32      TXM     :   1;
    uint32      PPIT    :   1;
    uint32      CFG     :   1;
    uint32      CHB     :   1;
    uint32      CHA     :   1;
    uint32      rsvd2   :   1;
    uint32      CYC     :   7;
    uint32      rsvd3   :   5;
    uint32      FID     :   11;
};

union   RDHS1_REG {
    uint32              all;
    struct  RDHS1_BITS  bit;
};


struct  RDHS2_BITS {       //Read Header Section Register
    uint32      rsvd1   :   1;
    uint32      PLR     :   7;
    uint32      rsvd2   :   1;
    uint32      PLC     :   7;
    uint32      rsvd3   :   5;
    uint32      CRC     :   11;
};

union   RDHS2_REG {
    uint32              all;
    struct  RDHS2_BITS  bit;
};

struct  RDHS3_BITS {       //Read Header Section Register
    uint32      rsvd1   :   2;
    uint32      RES     :   1;
    uint32      PPI     :   1;
    uint32      NFI     :   1;
    uint32      SYN     :   1;
    uint32      SFI     :   1;
    uint32      RCI     :   1;
    uint32      rsvd2   :   2;
    uint32      RCC     :   6;
    uint32      rsvd3   :   5;
    uint32      DP      :   11;
};

union   RDHS3_REG {
    uint32              all;
    struct  RDHS3_BITS  bit;
};

struct  MBS_BITS {       //Message Buffer Status Register
    uint32      rsvd1   :   2;
    uint32      RESS    :   1;
    uint32      PPIS    :   1;
    uint32      NFIS    :   1;
    uint32      SYNS    :   1;
    uint32      SFIS    :   1;
    uint32      RCIS    :   1;
    uint32      rsvd2   :   2;
    uint32      CCS     :   6;
    uint32      FTB     :   1;
    uint32      FTA     :   1;
    uint32      rsvd3   :   1;
    uint32      MLST    :   1;
    uint32      ESB     :   1;
    uint32      ESA     :   1;
    uint32      TCIB    :   1;
    uint32      TCIA    :   1;
    uint32      SVOB    :   1;
    uint32      SVOA    :   1;
    uint32      CEOB    :   1;
    uint32      CEOA    :   1;
    uint32      SEOB    :   1;
    uint32      SEOA    :   1;
    uint32      VFRB    :   1;
    uint32      VFRA    :   1;
};

union   MBS_REG {
    uint32              all;
    struct  MBS_BITS    bit;
};

struct  OBCM_BITS {       //Output Buffer Command Mask Register
    uint32      rsvd1   :   14;
    uint32      RDSH    :   1;
    uint32      RHSH    :   1;
    uint32      rsvd2   :   14;
    uint32      RDSS    :   1;
    uint32      RHSS    :   1;
};

union   OBCM_REG {
    uint32              all;
    struct  OBCM_BITS   bit;
};

struct  OBCR_BITS {       //Output Buffer Command Mask Register
    uint32      rsvd1   :   9;
    uint32      OBRH    :   7;
    uint32      OBSYS   :   1;
    uint32      rsvd2   :   5;
    uint32      REQ     :   1;
    uint32      VIEW    :   1;
    uint32      rsvd3   :   1;
    uint32      OBRS    :   7;
};

union   OBCR_REG {
    uint32              all;
    struct  OBCR_BITS   bit;
};


typedef volatile struct FlexRayTU_REGS {                 //0xFFF7 A000
    union   GSN0_REG    GSN0;           //000
    union   GSN1_REG    GSN1;
    uint32              rsvd1[2];

    union   GCS_REG     GCS;            //010
    union   GCR_REG     GCR;
    union   TSCB_REG    TSCB;
    union   LTBCC_REG   LTBCC;

    union   LTBSM_REG   LTBSM;          //020
    union   TBA_REG     TBA;
    union   NTBA_REG    NTBA;
    union   BAMS_REG    BAMS;

    union   SAMP_REG    SAMP;           //030
    union   EAMP_REG    EAMP;
    uint32              rsvd2[2];

    union   TSMO1_REG   TSMO1;          //040
    union   TSMO2_REG   TSMO2;
    union   TSMO3_REG   TSMO3;
    union   TSMO4_REG   TSMO4;

    union   TCCO1_REG   TCCO1;          //050
    union   TCCO2_REG   TCCO2;
    union   TCCO3_REG   TCCO3;
    union   TCCO4_REG   TCCO4;

    union   TOOFF_REG   TOOFF;          //060
    uint32              rsvd3[2];
    union   TSBESTAT_REG    TSBESTAT;

    union   PEADR_REG   PEADR;          //070
    union   TEIF_REG    TEIF;
    union   TEIRES_REG  TEIRES;
    union   TEIRER_REG  TEIRER;

    union   TTSMS1_REG  TTSMS1;         //080
    union   TTSMR1_REG  TTSMR1;
    union   TTSMS2_REG  TTSMS2;
    union   TTSMR2_REG  TTSMR2;

    union   TTSMS3_REG  TTSMS3;         //090
    union   TTSMR3_REG  TTSMR3;
    union   TTSMS4_REG  TTSMS4;
    union   TTSMR4_REG  TTSMR4;

    union   TTCCS1_REG  TTCCS1;         //0A0
    union   TTCCR1_REG  TTCCR1;
    union   TTCCS2_REG  TTCCS2;
    union   TTCCR2_REG  TTCCR2;

    union   TTCCS3_REG  TTCCS3;         //0B0
    union   TTCCR3_REG  TTCCR3;
    union   TTCCS4_REG  TTCCS4;
    union   TTCCR4_REG  TTCCR4;

    union   ETESMS1_REG ETESMS1;        //0C0
    union   ETESMR1_REG ETESMR1;
    union   ETESMS2_REG ETESMS2;
    union   ETESMR2_REG ETESMR2;

    union   ETESMS3_REG ETESMS3;        //0D0
    union   ETESMR3_REG ETESMR3;
    union   ETESMS4_REG ETESMS4;
    union   ETESMR4_REG ETESMR4;

    union   CESMS1_REG  CESMS1;         //0E0
    union   CESMR1_REG  CESMR1;
    union   CESMS2_REG  CESMS2;
    union   CESMR2_REG  CESMR2;

    union   CESMS3_REG  CESMS3;         //0F0
    union   CESMR3_REG  CESMR3;
    union   CESMS4_REG  CESMS4;
    union   CESMR4_REG  CESMR4;

    union   TSMIES1_REG TSMIES1;        //100
    union   TSMIER1_REG TSMIER1;
    union   TSMIES2_REG TSMIES2;
    union   TSMIER2_REG TSMIER2;

    union   TSMIES3_REG TSMIES3;        //110
    union   TSMIER3_REG TSMIER3;
    union   TSMIES4_REG TSMIES4;
    union   TSMIER4_REG TSMIER4;

    union   TCCIES1_REG TCCIES1;        //120
    union   TCCIER1_REG TCCIER1;
    union   TCCIES2_REG TCCIES2;
    union   TCCIER2_REG TCCIER2;

    union   TCCIES3_REG TCCIES3;        //130
    union   TCCIER3_REG TCCIER3;
    union   TCCIES4_REG TCCIES4;
    union   TCCIER4_REG TCCIER4;
}FlexTu_ST;

typedef volatile struct FlexRaySpe_REGS {                //FFF7 C800
    union   ECC_CTRL_REG    ECC_CTRL;   //00
    union   ECCDSTAT_REG    ECCDSTAT;
    union   ECCTEST_REG     ECCTEST;
    union   SBESTAT_REG     SBESTAT;

    union   TEST1_REG       TEST1;      //10
    union   TEST1_REG       TEST2;
    uint32                  rsvd1;
    union   LCK_REG         LCK;
}FlexRaySpe_t;

typedef volatile struct  FlexRayInt_REG  {
    union   EIR_REG         EIR;        //020
    union   SIR_REG         SIR;
    union   EILS_REG        EILS;
    union   SILS_REG        SILS;

    union   EIES_REG        EIES;       //030
    union   EIER_REG        EIER;
    union   SIES_REG        SIES;
    union   SIER_REG        SIER;

    union   ILE_REG         ILE;        //040
    union   T0C_REG         T0C;
    union   T1C_REG         T1C;
    union   STPW1_REG       STPW1;

    union   STPW2_REG       STPW2;      //050
    uint32                  rsvd[3];
}FlexRayInt_t;

typedef volatile struct  FlexRayCtr_REG  {               //FFF7 C880
    union   SUCC1_REG       SUCC1;      //00
    union   SUCC2_REG       SUCC2;
    union   SUCC3_REG       SUCC3;
    union   NEMC_REG        NEMC;

    union   PRTC1_REG       PRTC1;      //10
    union   PRTC1_REG       PRTC2;
    union   MHDC_REG        MHDC;
    uint32                  rsvd1;

    union   GTUC1_REG       GTUC1;      //20
    union   GTUC2_REG       GTUC2;
    union   GTUC3_REG       GTUC3;
    union   GTUC4_REG       GTUC4;

    union   GTUC5_REG       GTUC5;      //30
    union   GTUC6_REG       GTUC6;
    union   GTUC7_REG       GTUC7;
    union   GTUC8_REG       GTUC8;

    union   GTUC9_REG       GTUC9;      //40
    union   GTUC10_REG      GTUC10;
    union   GTUC11_REG      GTUC11;
}FlexRayCtr_t;

typedef volatile struct  FlexRayStat_REG {               //FFF7 C900
    union   CCSV_REG        CCSV;       //00
    union   CCEV_REG        CCEV;
    uint32                  rsvd1[2];

    union   SCV_REG         SCV;        //10
    union   MTCCV_REG       MTCCV;
    union   RCV_REG         RCV;
    union   OCV_REG         OCV;

    union   SFS_REG         SFS;        //20
    union   SWNIT_REG       SWNIT;
    union   ACS_REG         ACS;
    uint32                  rsvd2;

    union   ESID_REG        ESID[15];   //30
    uint32                  rsvd3;

    union   OSID_REG        OSID[15];   //70
    uint32                  rsvd4;

    union   NMV1_REG        NMV1;       //B0
    union   NMV2_REG        NMV2;
    union   NMV3_REG        NMV3;
}FlexRayStat_t;

typedef volatile struct  FlexRayMsegCtr_REG  {           //FFF7 C800 + 300
    union   MRC_REG         MRC;
    union   FRF_REG         FRF;
    union   FRFM_REG        FRFM;
    union   FCL_REG         FCL;
}FlexRayMsegCtr_t;

typedef volatile struct  FlexRayMsegStat_REG {           //FFF7 C800 +310
    union   MHDS_REG        MHDS;       //00
    union   LDTS_REG        LDTS;
    union   FSR_REG         FSR;
    union   MHDF_REG        MHDF;

    union   TXRQ1_REG       TXRQ1;      //10
    union   TXRQ2_REG       TXRQ2;
    union   TXRQ3_REG       TXRQ3;
    union   TXRQ4_REG       TXRQ4;

    union   NDAT1_REG       NDAT1;      //20
    union   NDAT2_REG       NDAT2;
    union   NDAT3_REG       NDAT3;
    union   NDAT4_REG       NDAT4;

    union   MBSC1_REG       MBSC1;
    union   MBSC2_REG       MBSC2;
    union   MBSC3_REG       MBSC3;
    union   MBSC4_REG       MBSC4;
}FlexRayMsegStat_t;

typedef volatile struct  FlexRayId_REG   {               // FFF7 C800 + 3F0
    union   CREL_REG        CREL;
    uint32                  EVT;
} FlexRayId_t;

typedef volatile struct  FlexRayIn_REG   {               // FFF7 C800 + 400
    uint32                  WRDS[64];

    union   WRHS1_REG       WRHS1;
    union   WRHS2_REG       WRHS2;
    union   WRHS3_REG       WRHS3;
    uint32                  rsvd1;

    union   IBCM_REG        IBCM;
    union   IBCR_REG        IBCR;
}FlexRayIn_t;

typedef volatile struct  FlexRayOut_REG   {              // FFF7 C800 + 600
    uint32                  RDDS[64];   //00

    union   RDHS1_REG       RDHS1;
    union   RDHS2_REG       RDHS2;
    union   RDHS3_REG       RDHS3;
    union   MBS_REG         MBS;

    union   OBCM_REG        OBCM;
    union   OBCR_REG        OBCR;
}FlexRayOut_t;

typedef volatile struct FlexRay_REG {

    union   ECC_CTRL_REG    ECC_CTRL;   //00
    union   ECCDSTAT_REG    ECCDSTAT;
    union   ECCTEST_REG     ECCTEST;
    union   SBESTAT_REG     SBESTAT;

    union   TEST1_REG       TEST1;      //10
    union   TEST1_REG       TEST2;
    uint32                  rsvd1;
    union   LCK_REG         LCK;

    union   EIR_REG         EIR;        //020
    union   SIR_REG         SIR;
    union   EILS_REG        EILS;
    union   SILS_REG        SILS;

    union   EIES_REG        EIES;       //030
    union   EIER_REG        EIER;
    union   SIES_REG        SIES;
    union   SIER_REG        SIER;

    union   ILE_REG         ILE;        //040
    union   T0C_REG         T0C;
    union   T1C_REG         T1C;
    union   STPW1_REG       STPW1;

    union   STPW2_REG       STPW2;      //050
    uint32                  rsvd2[11];

    union   SUCC1_REG       SUCC1;      //080
    union   SUCC2_REG       SUCC2;
    union   SUCC3_REG       SUCC3;
    union   NEMC_REG        NEMC;

    union   PRTC1_REG       PRTC1;      //090
    union   PRTC1_REG       PRTC2;
    union   MHDC_REG        MHDC;
    uint32                  rsvd3;

    union   GTUC1_REG       GTUC1;      //0A0
    union   GTUC2_REG       GTUC2;
    union   GTUC3_REG       GTUC3;
    union   GTUC4_REG       GTUC4;

    union   GTUC5_REG       GTUC5;      //0B0
    union   GTUC6_REG       GTUC6;
    union   GTUC7_REG       GTUC7;
    union   GTUC8_REG       GTUC8;

    union   GTUC9_REG       GTUC9;      //0C0
    union   GTUC10_REG      GTUC10;
    union   GTUC11_REG      GTUC11;
    uint32                  rsvd4[13];

    union   CCSV_REG        CCSV;       //100
    union   CCEV_REG        CCEV;
    uint32                  rsvd5[2];

    union   SCV_REG         SCV;        //110
    union   MTCCV_REG       MTCCV;
    union   RCV_REG         RCV;
    union   OCV_REG         OCV;

    union   SFS_REG         SFS;        //120
    union   SWNIT_REG       SWNIT;
    union   ACS_REG         ACS;
    uint32                  rsvd6;

    union   ESID_REG        ESID[15];   //130
    uint32                  rsvd7;

    union   OSID_REG        OSID[15];   //170
    uint32                  rsvd8;

    union   NMV1_REG        NMV1;       //1B0
    union   NMV2_REG        NMV2;
    union   NMV3_REG        NMV3;
    uint32                  rsvd9[81];

    union   MRC_REG         MRC;        //300
    union   FRF_REG         FRF;
    union   FRFM_REG        FRFM;
    union   FCL_REG         FCL;

    union   MHDS_REG        MHDS;       //310
    union   LDTS_REG        LDTS;
    union   FSR_REG         FSR;
    union   MHDF_REG        MHDF;

    union   TXRQ1_REG       TXRQ1;      //320
    union   TXRQ2_REG       TXRQ2;
    union   TXRQ3_REG       TXRQ3;
    union   TXRQ4_REG       TXRQ4;

    union   NDAT1_REG       NDAT1;      //330
    union   NDAT2_REG       NDAT2;
    union   NDAT3_REG       NDAT3;
    union   NDAT4_REG       NDAT4;

    union   MBSC1_REG       MBSC1;      //340
    union   MBSC2_REG       MBSC2;
    union   MBSC3_REG       MBSC3;
    union   MBSC4_REG       MBSC4;

    uint32                  rsvd10[40]; //
    union   CREL_REG        CREL;       //3f0
    uint32                  EVT;
    uint32                  rsvd11[2];

    uint32                  WRDS[64];

    union   WRHS1_REG       WRHS1;
    union   WRHS2_REG       WRHS2;
    union   WRHS3_REG       WRHS3;
    uint32                  rsvd12;

    union   IBCM_REG        IBCM;
    union   IBCR_REG        IBCR;
    uint32                  rsvd13[58];

    uint32                  RDDS[64];   //600

    union   RDHS1_REG       RDHS1;
    union   RDHS2_REG       RDHS2;
    union   RDHS3_REG       RDHS3;
    union   MBS_REG         MBS;

    union   OBCM_REG        OBCM;
    union   OBCR_REG        OBCR;
}Fray_St;

typedef volatile struct  FlexFtuTcr_REG
{
    union   TCR_REG         TCR[128];
}FTUTCR_ST;

#define TcrReg          ((FTUTCR_ST *)0xFF500000)

#define Fray1Reg        ((Fray_St *)0xFFF7C800U)

#define FrTuReg         ((FlexTu_ST *)0xFFF7A000)

#define FrSpeReg        ((FlexRaySpe_t *)0xFFF7C800)

#define FrIntReg        ((FlexRayInt_t *)0xFFF7C820)

#define FrCtrReg        ((FlexRayCtr_t *)0xFFF7C880)

#define FrStatReg       ((FlexRayStat_t *)0xFFF7C900)

#define FrMsegCtrReg    ((FlexRayMsegCtr_t *)0xFFF7CB00)

#define FrMsegStatReg   ((FlexRayMsegStat *)0xFFF7CB10)

#define FrIdReg         ((FlexRayId_t *)0xFFF7CBF0)

#define FrInReg         ((FlexRayIn_t *)0xFFF7CC00)

#define FrOutReg        ((FlexRayOut_t *)0xFFF7CE00)

#endif /* USER_DRIVER_HL_REG_FLEXRAY_H_ */

