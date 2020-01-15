/******************************************************************
FileName   :tja1102.h
Copy Right :
System     :
Module     :
Author     :zhenhua.wang
Create Date:2019-05-28
****************************************************************/

#ifndef USER_DRIVER_TJA1102_H_
#define USER_DRIVER_TJA1102_H_



#ifdef __cplusplus
extern "C" {
#endif

/*
typedef enum phyTimeStamp
{
    Txtimestamp = 1,   // Transmit Timestamp
    Rxtimestamp = 2    // Receive Timestamp
}phyTimeStamp_t;
*/

#define FR_EN_PIN       0x04        //GPIOA4

#define PHY_RST_PIN     0x05        //GPIOB5
#define PHY_INT12_PIN   0x06        //GPIOB6
#define PHY_INT3_PIN    0x07        //GPIOB7
#define PHY_WAKE_PIN    0x03        //GPIOB3
#define PHY_WAKE3_PIN   0x02        //GPIOB2


#define PHY1_RMII_P0     0x04
#define PHY2_RMII_P0     0x06
#define PHY2_RMII_P1     0x07

#define PHY_BCR                           (0u)
#define PHY_BSR                           (1u)
#define PHY_ID1                           (2u)
#define PHY_ID2                           (3u)
#define PHY_ESR1                          (15u)
#define PHY_ID3                           (16u)
#define PHY_ECR                           (17u)
#define PHY_CR1                           (18u)
#define PHY_CR2                           (19u)
#define PHY_ERR                           (20u)
#define PHY_INTR                          (21u)
#define PHY_INT_EN                        (22u)
#define PHY_COM_SR                        (23u)
#define PHY_GEN_SR                        (24u)
#define PHY_ESR2                          (25u)
#define PHY_LCNTR                         (26u)
#define PHY_COM_CR                        (27u)
#define PHY_CR3                           (28u)

/* PHY ID. The LSB nibble will vary between different phy revisions */
#define NXP_PHY_ID_TJA1102P0      (0x0180DC81U)
#define NXP_PHY_ID_TJA1102P1      (0x00000000U)
#define NXP_PHY_ID_TJA1102S       (0x0180DC91U) /* only P0 is available */

#define PHY_ID_SHIFT                      (16u)

#ifdef __cplusplus
}
#endif

/******************************************************
*Name    :  FreeRTOS_Phyinit
*Function:  初始化函数所有 PHY
*Params  :
*Return  :  其它： 表示初始化失败， 2 表示成功
*******************************************************/
uint8   FreeRTOS_Phyinit(void);

/******************************************************
*Name    :  Phy_init
*Function:  PHY 初始化函数
*Params  :  phyAddr : PHY 地址
*Return  :  0 表示初始化失败， 1 表示成功
*******************************************************/
uint8 Phy_init(uint32 phyAddr);

/******************************************************
*Name    :  PHY3_IntISR
*Function:  PHY 中断服务程序，当网络链接状态改变时，产生中断
*Params  :
*Return  :
*******************************************************/
void    PHY3_IntISR();

/******************************************************
*Name    :  PHY_IntISR
*Function:  PHY 中断服务程序，当网络链接状态改变时，产生中断
*Params  :
*Return  :
*******************************************************/
void    PHY_IntISR();

#endif /* USER_DRIVER_TJA1102_H_ */
