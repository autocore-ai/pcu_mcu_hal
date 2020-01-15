/******************************************************************
FileName   :Fr.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-11-25
****************************************************************/
#include    "HL_reg_flexray.h"

// CMD constants (SUCC1)
//
#define CMD_command_not_accepted             0x0
#define CMD_CONFIG                           0x1
#define CMD_READY                            0x2
#define CMD_WAKEUP                           0x3
#define CMD_RUN                              0x4
#define CMD_ALL_SLOTS                        0x5
#define CMD_HALT                             0x6
#define CMD_FREEZE                           0x7
#define CMD_SEND_MTS                         0x8
#define CMD_ALLOW_COLDSTART                  0x9
#define CMD_RESET_STATUS_INDICATORS          0xA
#define CMD_MONITOR_MODE                     0xB
#define CMD_CLEAR_RAMS                       0xC
#define CMD_ASYNCHRONOUS_TRANSFER_MODE       0xE


#define FLEX_PAYLOAD        64

//**********************************************************
// Structure for initializing CC - Fr_Init - Fr_ConfigPtr
typedef volatile struct cfg
{
    int mrc;
    int prtc1;
    int prtc2;
    int mhdc;
    int gtu1;
    int gtu2;
    int gtu3;
    int gtu4;
    int gtu5;
    int gtu6;
    int gtu7;
    int gtu8;
    int gtu9;
    int gtu10;
    int gtu11;
    int succ2;
    int succ3;
} cfg;

// Structure for configuring buffers - Fr_PrepareLPdu - Fr_LPduPtr
typedef volatile struct wrhs
{
    int mbi;
    int txm;
    int ppit;
    int cfg;
    int chb;
    int cha;
    int cyc;
    int fid;
    int pl;
    int crc;
    int dp;
    int sync;
    int sfi;
} wrhs;

// Structure for initializing buffer - Fr_TransmitTxLPdu, Fr_ReceiveRxLPdu - Fr_LSduPtr
typedef volatile struct bc
{
    int ibrh;
    int stxrh;
    int ldsh;
    int lhsh;
    int ibsyh;
    int ibsys;
    int obrs;
    int rdss;
    int rhss;
} bc;


typedef volatile struct fray_ram_header
{
    union   WRHS1_REG   header1;
    union   WRHS2_REG   header2;
    union   WRHS3_REG   header3;
    union   MBS_REG     header4;
}Fray_ram_st;


typedef volatile struct
{
    Fray_ram_st Fray_header;
    uint8  Fray_data[FLEX_PAYLOAD];
}Flex_msg;

//**********************************************************
// Functions
int header_crc_calc(wrhs *Fr_LPduPtr);
void Fr_Init(Fray_St *Fray_PST, cfg *Fr_ConfigPtr);
int Fr_ControllerInit(Fray_St *Fray_PST);
void Fr_PrepareLPdu(Fray_St *Fray_PST, wrhs *Fr_LPduPtr);
int Fr_AllowColdStart(Fray_St *Fray_PST);
int Fr_StartCommunication(Fray_St *Fray_PST);
void Fr_TransmitTxLPdu(Fray_St *Fray_PST, bc *Fr_LSduPtr);
void Fr_ReceiveRxLPdu(Fray_St *Fray_PST, bc *Fr_LSduPtr);
void configure_initialize_node_a(Fray_St *Fray_PST);
void configure_initialize_node_b(Fray_St *Fray_PST);
int transmit_check_node_a(Fray_St *Fray_PST);
int transmit_check_node_b(Fray_St *Fray_PST);

