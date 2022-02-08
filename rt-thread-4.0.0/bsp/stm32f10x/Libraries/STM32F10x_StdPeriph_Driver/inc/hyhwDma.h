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
 * Դ��ַ��Ŀ���ַ�Ƿ��Զ���1
 *
 * Implementation:
 * Do not specify a greater width than actual width of the AHB bus(es)
 * The DMA driver will reject such requests, or attempts to configure
 * an internal peripheral or virtual memory block with an invalid width.
 * 
 */
typedef enum DMA_xAddrInc
{
    DMA_SNI       = 0,    /* Դ��ַ���� */
    DMA_SI        = 1,    /* Դ��ַ��1 */
    DMA_DNI       = 0,    /* Ŀ���ַ���� */
	  DMA_DI        = 1			 /* Ŀ���ַ��1 */
} DMA_AddrInc;

/*
 * Description:
 * DMAͨ����
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

//��������DMA ͨ������
#define MAX_DMAC_CHANNELS			4
#define DMA_CHANNEL_ENABLE					1

/*---------------------------------------------------------------------------
   Defines : ��С��ģʽ
   --------------------------------------------------------------------------*/
#define DMA_LE_MODE		0
#define DMA_BE_MODE  	1
#define DMA_DATA_MODE			DMA_LE_MODE

/*-----------------------------------------------------------------------------
* ����:	hyhwDMAC_Init
* ����:	��ʼ��DMAͨ��
* ����:	NONE
*----------------------------------------------------------------------------*/
void hyhwDMAC_Init(void);

/*-----------------------------------------------------------------------------
* ����:	hyhwDma_Config
* ����:	����DMA
* ����:
*   channel-ͨ����
*   sa------����Դ��ַ
*		da------����Ŀ�ĵ�ַ
*		tcount--��Ҫ���䵥Ԫ����Ŀ��
*		si------����Դ��ַ�Ƿ����ӣ�0����ַ���䣬1��������һ����Ԫ�Զ����ӣ�
*		di------����Ŀ�ĵ�ַ�Ƿ����ӣ�ͬ�ϣ�
*		swidth--����Դ�Ķ˿ڿ�ȣ�DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT��
*		dwidth--����Ŀ�Ķ˿ڿ�ȣ�DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT��
*		TransType-DMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    					DMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
					    DMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
					    DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
					    DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
					    DMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7,
* ����:	NONE
*----------------------------------------------------------------------------*/
void hyhwDma_Config(
						U8 channel, //DMA ͨ���ţ�0��7
						U32 sa, 		// source address
						U32 da, 		// Destination address
						U32 tcount, 	// Transfer unit count. (Max = 16M bytes, Max bytes = tcount *twidth for shark)	(Min = 0x01)
						U8 si,		// Source Increment (0 no increment, 1 increment after each transfer)
						U8 di, 		// Destination Increment (0 no increment, 1 increment after each transfer) 
						U8 swidth,	// Source Width in bytes. Must be equal to dw
						U8 dwidth,	// Destination Width in bytes. Must be equal to sw
						U8 TransType //��������
					);

/*-----------------------------------------------------------------------------
* ����:	hyhwDma_Config
* ����:	����DMA
* ����:
*   channel-ͨ����
*   sa------����Դ��ַ
*		da------����Ŀ�ĵ�ַ
*		tcount--��Ҫ���䵥Ԫ����Ŀ��
*		si------����Դ��ַ�Ƿ����ӣ�0����ַ���䣬1��������һ����Ԫ�Զ����ӣ�
*		di------����Ŀ�ĵ�ַ�Ƿ����ӣ�ͬ�ϣ�
*		swidth--����Դ�Ķ˿ڿ�ȣ�DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT��
*		dwidth--����Ŀ�Ķ˿ڿ�ȣ�DMA_WIDTH_8_BIT,DMA_WIDTH_16_BIT,DMA_WIDTH_32_BIT��
*		TransType-DMA_MEM_TO_MEM_DMA_CTRL                            = 0,
    					DMA_MEM_TO_PERIPHERAL_DMA_CTRL                     = 1,
					    DMA_PERIPHERAL_TO_MEM_DMA_CTRL                     = 2,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DMA_CTRL              = 3,
					    DMA_PERIPHERAL_TO_PERIPHERAL_DEST_PERIPHERAL_CTRL  = 4,
					    DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL              = 5,
					    DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL              = 6,
					    DMA_PERIPHERAL_TO_PERIPHERAL_SRC_PERIPHERAL_CTRL   = 7,
* ����:	NONE
*----------------------------------------------------------------------------*/
void hyhwUartDma_Config(
						U8 channel, //DMA ͨ���ţ�0��7
						U32 sa, 		// source address
						U32 da, 		// Destination address
						U32 tcount, 	// Transfer unit count. (Max = 16M bytes, Max bytes = tcount *twidth for shark)	(Min = 0x01)
						U8 si,		// Source Increment (0 no increment, 1 increment after each transfer)
						U8 di, 		// Destination Increment (0 no increment, 1 increment after each transfer) 
						U8 swidth,	// Source Width in bytes. Must be equal to dw
						U8 dwidth,	// Destination Width in bytes. Must be equal to sw
						U8 TransType //��������
					);

#endif /* TM_LLIC_API_UART_H_ */




