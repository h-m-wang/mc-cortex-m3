/*******************************************************************************
*   All rights reserved              
*
*  This source code and any compilation or derivative thereof is the sole      
*  property of xxxx Technology Co., Ltd and is provided pursuant 
*  to a Software License Agreement.  This code is the proprietary information of      
*  xxxx and is confidential in nature.  Its use and dissemination by    
*  any party other than xxxx is strictly limited by the confidential information 
*  provisions of the Agreement referenced above.      
*
*******************************************************************************
*
* Rev   Date    Author          Comments
*      (yymmdd)
* -------------------------------------------------------------
* 001   160506  ICE WANG		Primary version 
* -------------------------------------------------------------
*
*  This source file contains the basic definition about SPI Controller   
*
****************************************************************/

#ifndef HY_HW_SPI_H_
#define HY_HW_SPI_H_

/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Project include files:
------------------------------------------------------------------------------*/
#include "SCM3.h"
#include "hyTypes.h"

/*---------------------------------------------------------------------------
   Defines : SPI??С??ģʽ
   --------------------------------------------------------------------------*/
#define SPI_LE_MODE		0x400
#define SPI_BE_MODE  	0x000
/******************************************************************************/
/*                                                                            */
/*                  FLASH Controller                                          */
/*                                                                            */
/******************************************************************************/
/***************** SPI control register ***************************************/
#define  SPIF_RESET                     ((uint32_t)0x80000000)        /*!< SPI controller soft reset            */
#define  SPIF_INT_EN                    ((uint32_t)0x00100000)        /*!< SPI controller interrupt enable      */
#define  SPIF_SCK_DIV_256               ((uint32_t)0x00000000)        /*!< SPI controller spi clk division 256  */
#define  SPIF_SCK_DIV_128               ((uint32_t)0x00080000)        /*!< SPI controller spi clk division 128  */
#define  SPIF_SCK_DIV_64                ((uint32_t)0x00040000)        /*!< SPI controller spi clk division 64   */
#define  SPIF_SCK_DIV_32                ((uint32_t)0x00020000)        /*!< SPI controller spi clk division 32   */
#define  SPIF_SCK_DIV_16                ((uint32_t)0x00010000)        /*!< SPI controller spi clk division 16   */
#define  SPIF_SCK_DIV_8                 ((uint32_t)0x00008000)        /*!< SPI controller spi clk division 8    */
#define  SPIF_SCK_DIV_4                 ((uint32_t)0x00004000)        /*!< SPI controller spi clk division 4    */
#define  SPIF_SCK_DIV_2                 ((uint32_t)0x00002000)        /*!< SPI controller spi clk division 2    */
//#define  SPIF_SCK_DIV_1                 ((uint32_t)0x00080000)        /*!< SPI controller spi clk division 1    */
#define  SPIF_LSB_EN                    ((uint32_t)0x00000400)        /*!< SPI controller LSB first enable      */
#define  SPIF_WP_EN                     ((uint32_t)0x00000200)        /*!< SPI controller Write protect enable  */
#define  SPIF_USE_DMA_EN                ((uint32_t)0x00000100)        /*!< SPI controller USE DMA enable        */
#define  SPIF_PHASE_CNT1                ((uint32_t)0x00000000)        /*!< SPI controller include 1 phase       */
#define  SPIF_PHASE_CNT2                ((uint32_t)0x00000010)        /*!< SPI controller include 2 phase       */
#define  SPIF_PHASE_CNT3                ((uint32_t)0x00000020)        /*!< SPI controller include 3 phase       */
#define  SPIF_PHASE_CNT4                ((uint32_t)0x00000030)        /*!< SPI controller include 4 phase       */
#define  SPIF_PHASE_CNT5                ((uint32_t)0x00000040)        /*!< SPI controller include 5 phase       */
#define  SPIF_PHASE_CNT6                ((uint32_t)0x00000050)        /*!< SPI controller include 6 phase       */
#define  SPIF_PHASE_CNT7                ((uint32_t)0x00000060)        /*!< SPI controller include 7 phase       */
#define  SPIF_PHASE_CNT8                ((uint32_t)0x00000070)        /*!< SPI controller include 8 phase       */
#define  SPIF_ERROR                     ((uint32_t)0x00000004)        /*!< SPI controller include 8 phase       */
#define  SPIF_DONE                      ((uint32_t)0x00000002)        /*!< SPI controller include 8 phase       */
#define  SPIF_STSRT                     ((uint32_t)0x00000001)        /*!< SPI controller include 8 phase       */

/***************** SPI Phase controller register ***************************************/
#define  SPIF_MODE_SINGLE               ((uint32_t)0x00000000)        /*!< SPI bus single                       */
#define  SPIF_MODE_DUAL                 ((uint32_t)0x00010000)        /*!< SPI bus dual                         */
#define  SPIF_MODE_QUAD                 ((uint32_t)0x00020000)        /*!< SPI bus quad                         */
#define  SPIF_PHASE_ACTION_TX           ((uint32_t)0x00000000)        /*!< SPI PHASE_ACTION TX                  */
#define  SPIF_PHASE_ACTION_DUMMY_TX     ((uint32_t)0x00000010)        /*!< SPI PHASE_ACTION TX DUMMY            */
#define  SPIF_PHASE_ACTION_RX           ((uint32_t)0x00000020)        /*!< SPI PHASE_ACTION Rx                  */    
#define  SPIF_PHASE_ACTION_POLL         ((uint32_t)0x00000030)        /*!< SPI PHASE_ACTION POLL                */
#define  SPIF_PHASE_ERROR               ((uint32_t)0x00000004)        /*!< SPI PHASE ERROR                      */
#define  SPIF_PHASE_DONE                ((uint32_t)0x00000002)        /*!< SPI PHASE DONE                       */
#define  SPIF_PHASE_STSRT               ((uint32_t)0x00000001)        /*!< SPI PHASE STSRT                      */

/***************** SPI Status Register ***************************************/
#define SPIF_SR_SRP                     ((uint8_t)0x80)                 /*!< The Status Register Protect */
#define SPIF_SR_REV                     ((uint8_t)0x40)                 /*!< Reserved Bits */
#define SPIF_SR_BP3                     ((uint8_t)0x20)                 /*!< Block Protect Bits3 */
#define SPIF_SR_BP2                     ((uint8_t)0x10)                 /*!< Block Protect Bits2 */
#define SPIF_SR_BP1                     ((uint8_t)0x08)                 /*!< Block Protect Bits1 */
#define SPIF_SR_BP0                     ((uint8_t)0x04)                 /*!< Block Protect Bits0 */
#define SPIF_SR_WEL                     ((uint8_t)0x02)                 /*!< Write Enable Latch */
#define SPIF_SR_WIP                     ((uint8_t)0x01)                 /*!< Write in Progress */

/** 
  * @brief Serial Peripheral Interface FLASH
  */

typedef struct 
{
    __IO uint32_t     SPCR;
    __IO uint32_t     RESV[3];
    __IO uint32_t     PHASE_CTRL[8];
    __IO uint32_t     PHASE_DATA[8];
} SPI_FLASH_TypeDef;


/*-----------------------------------------------------------------------------
* ????:	hyhwSPI_Init
* ????:	??ʼ??SPI,????SPI clk
* ????:	
* ????:	NONE
*----------------------------------------------------------------------------*/
void hyhwSPI_Init(void);

/*-----------------------------------------------------------------------------
* ????:	hyhwTSC_Init
* ????:	??ʼ??TSC
* ????:	
* ????:	NONE
*----------------------------------------------------------------------------*/
void hyhwTSC_Init(void);

/*-----------------------------------------------------------------------------
* ????:	?????Ƿ??д???
* ????:	??ʼ??TSC
* ????:	
* ????:	NONE
*----------------------------------------------------------------------------*/
U8 hyhwTSC_PenDet(void);

/*-----------------------------------------------------------------------------
* ????:	?ȴ?busy????
* ????:	??ʼ??TSC
* ????:	
* ????:	NONE
*----------------------------------------------------------------------------*/
void hyhwTSC_WaitBusy(void);

/*-----------------------------------------------------------------------------
* ????:	hyhwTSC_Det
* ????:	??????λ???ж?
* ????:	
* ????:	NONE
*----------------------------------------------------------------------------*/
void hyhwTSC_Det(void);



/***************************************************************************
* ????:	hyhwDelayUS
* ????:	??????ʱnUs
*       ˵????????????Ƶ?йأ???Ƶ?仯ʱ??Ҫ??????????
* ????:	??Ҫ??ʱ??uS????
* ????:	NONE
****************************************************************************/
void hyhwDelayUS(U32 nUs );

#endif /* TM_LLIC_API_UART_H_ */




