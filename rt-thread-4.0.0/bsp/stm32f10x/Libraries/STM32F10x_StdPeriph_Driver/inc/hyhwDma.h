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
*  This source file contains the basic definition about DMA   
*
****************************************************************/

#ifndef HY_HW_DMAC_H_
#define HY_HW_DMAC_H_

/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Project include files:
------------------------------------------------------------------------------*/
#include "SCM3.h"
#include "hyTypes.h"
/*------------------------------------------------------------------------------
Types and defines:
------------------------------------------------------------------------------*/
/** 
  * @brief Direct Memory Access
  */
#define DMA_NUM_RSRVD_WRDS_BEFORE_CHANNELS      ( (0x100 - 0x038) >> 2 )
#define DMA_NUM_RSRVD_WRDS_BEFORE_PERIPHERAL_ID ( (0xfe0 - 0x500) >> 2 )

typedef volatile struct DMA_xChannel
{
    __IO uint32_t     SrcAddr;
    __IO uint32_t     DestAddr;
    __IO uint32_t     LLI;
    __IO uint32_t     Control;
    __IO uint32_t     Configuration;
    __IO uint32_t     Reserved1;
    __IO uint32_t     Reserved2;
    __IO uint32_t     Reserved3;

} DMA_sChannel;

typedef volatile struct DMA_xPort
{
    __IO uint32_t         IntStatus;              /* 0x000 */
    __IO uint32_t         IntTCStatus;
    __IO uint32_t         IntTCClear;
    __IO uint32_t         IntErrorStatus;
    __IO uint32_t         IntErrorClear;          /* 0x010 */
    __IO uint32_t         RawIntTCStatus;
    __IO uint32_t         RawIntErrorStatus;
    __IO uint32_t         ActiveChannels;

    __IO uint32_t         SoftBReq;               /* 0x020 */
    __IO uint32_t         SoftSReq;               /* 0x024 */
    __IO uint32_t         SoftLBReq;              /* 0x028 */
    __IO uint32_t         SoftSBReq;              /* 0x02C */
    
    __IO uint32_t         Configuration;          /* 0x030 */
    __IO uint32_t         Sync;                   /* 0x034 */

    __IO uint32_t         Reserved1[ DMA_NUM_RSRVD_WRDS_BEFORE_CHANNELS ];

    DMA_sChannel    sDmaChannels[ 32 ];     /* 0x100 -  */

    __IO uint32_t         Reserved2[ DMA_NUM_RSRVD_WRDS_BEFORE_PERIPHERAL_ID ];

    __IO uint32_t         PeripheralId0;          /* 0xFE0 */
    __IO uint32_t         PeripheralId1;
    __IO uint32_t         PeripheralId2;
    __IO uint32_t         PeripheralId3;
    __IO uint32_t         CellId0;                /* 0xFF0 */
    __IO uint32_t         CellId1;
    __IO uint32_t         CellId2;
    __IO uint32_t         CellId3;

} DMAC_TypeDef;

/*
 * Description:
 * Burst Transfer Size
 * 
 */
typedef enum DMA_xBurstSize
{
    DMA_BURST_1       = 0,                              /* 1   transfer  per burst */
    DMA_BURST_4       = 1,                              /* 4   transfers per burst */
    DMA_BURST_8       = 2,                              /* 8   transfers per burst */
    DMA_BURST_16      = 3,                              /* 16  transfers per burst */
    DMA_BURST_32      = 4,                              /* 32  transfers per burst */
    DMA_BURST_64      = 5,                              /* 64  transfers per burst */
    DMA_BURST_128     = 6,                              /* 128 transfers per burst */
	  DMA_BURST_256     = 7
} DMA_eBurstSize;

/*
 * Description:
 * Transfer Width
 *
 * Implementation:
 * Do not specify a greater width than actual width of the AHB bus(es)
 * The DMA driver will reject such requests, or attempts to configure
 * an internal peripheral or virtual memory block with an invalid width.
 * 
 */
typedef enum DMA_xWidth
{
    DMA_WIDTH_8_BIT       = 0,    /* 8 Bits per transfer */
    DMA_WIDTH_16_BIT      = 1,    /* 16 Bits per transfer */
    DMA_WIDTH_32_BIT      = 2,    /* 32 Bits per transfer */
} DMA_eWidth;

/*
 * Description:
 * 源地址和目标地址是否自动加1
 *
 * Implementation:
 * Do not specify a greater width than actual width of the AHB bus(es)
 * The DMA driver will reject such requests, or attempts to configure
 * an internal peripheral or virtual memory block with an invalid width.
 * 
 */
typedef enum DMA_xAddrInc
{
    DMA_SNI       = 0,    /* 源地址不变 */
    DMA_SI        = 1,    /* 源地址加1 */
    DMA_DNI       = 0,    /* 目标地址不变 */
	  DMA_DI        = 1			 /* 目标地址加1 */
} DMA_AddrInc;

/*
 * Description:
 * DMA通道号
 *
 * Implementation:
 * Do not specify a greater width than actual width of the AHB bus(es)
 * The DMA driver will reject such requests, or attempts to configure
 * an internal peripheral or virtual memory block with an invalid width.
 * 
 */
typedef enum DMA_xChannelNum
{
    DMA_CHANNEL0       = 0,    /* channel 0*/
    DMA_CHANNEL1       = 1,    /* channel 1 */
    DMA_CHANNEL2       = 2,    /* channel 2*/
	  DMA_CHANNEL3       = 3		 /* channel 3 */
} DMA_ChannelNum;


/*
 * Description:
 * Enum of possible DMA flow directions & flow controllers
 *
 * Implementation:
 * Each DMA transfer operation must indicate the types of source and destination
 * (memory or peripheral), and when a peripheral is involved, whether it or the
 * DMA controller is controlling the flow.
 */
typedef enum DMA_xFlowControl
{
    DMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    DMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
    DMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
    DMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
    DMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
    DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
    DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
    DMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7,
} DMA_eFlowControl;

//定义最大的DMA 通道数量
#define MAX_DMAC_CHANNELS			4
#define DMA_CHANNEL_ENABLE					1

/*---------------------------------------------------------------------------
   Defines : 大小端模式
   --------------------------------------------------------------------------*/
#define DMA_LE_MODE		0
#define DMA_BE_MODE  	1
#define DMA_DATA_MODE			DMA_LE_MODE

/*-----------------------------------------------------------------------------
* 函数:	hyhwDMAC_Init
* 功能:	初始化DMA通道
* 返回:	NONE
*----------------------------------------------------------------------------*/
void hyhwDMAC_Init(void);

/*-----------------------------------------------------------------------------
* 函数:	hyhwDma_Config
* 功能:	设置DMA
* 参数:
*   channel-通道号
*   sa------数据源地址
*		da------数据目的地址
*		tcount--需要传输单元的数目，
*		si------数据源地址是否增加（0：地址不变，1：传输完一个单元自动增加）
*		di------数据目的地址是否增加（同上）
*		swidth--数据源的端口宽度（DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT）
*		dwidth--数据目的端口宽度（DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT）
*		TransType-DMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    					DMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
					    DMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
					    DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
					    DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
					    DMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7,
* 返回:	NONE
*----------------------------------------------------------------------------*/
void hyhwDma_Config(
						U8 channel, //DMA 通道号，0～7
						U32 sa, 		// source address
						U32 da, 		// Destination address
						U32 tcount, 	// Transfer unit count. (Max = 16M bytes, Max bytes = tcount *twidth for shark)	(Min = 0x01)
						U8 si,		// Source Increment (0 no increment, 1 increment after each transfer)
						U8 di, 		// Destination Increment (0 no increment, 1 increment after each transfer) 
						U8 swidth,	// Source Width in bytes. Must be equal to dw
						U8 dwidth,	// Destination Width in bytes. Must be equal to sw
						U8 TransType //传输类型
					);

/*-----------------------------------------------------------------------------
* 函数:	hyhwDma_Config
* 功能:	设置DMA
* 参数:
*   channel-通道号
*   sa------数据源地址
*		da------数据目的地址
*		tcount--需要传输单元的数目，
*		si------数据源地址是否增加（0：地址不变，1：传输完一个单元自动增加）
*		di------数据目的地址是否增加（同上）
*		swidth--数据源的端口宽度（DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT）
*		dwidth--数据目的端口宽度（DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT）
*		TransType-DMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    					DMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
					    DMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
					    DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
					    DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
					    DMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7,
* 返回:	NONE
*----------------------------------------------------------------------------*/
void hyhwUartDma_Config(
						U8 channel, //DMA 通道号，0～7
						U32 sa, 		// source address
						U32 da, 		// Destination address
						U32 tcount, 	// Transfer unit count. (Max = 16M bytes, Max bytes = tcount *twidth for shark)	(Min = 0x01)
						U8 si,		// Source Increment (0 no increment, 1 increment after each transfer)
						U8 di, 		// Destination Increment (0 no increment, 1 increment after each transfer) 
						U8 swidth,	// Source Width in bytes. Must be equal to dw
						U8 dwidth,	// Destination Width in bytes. Must be equal to sw
						U8 TransType //传输类型
					);

#endif /* TM_LLIC_API_UART_H_ */




