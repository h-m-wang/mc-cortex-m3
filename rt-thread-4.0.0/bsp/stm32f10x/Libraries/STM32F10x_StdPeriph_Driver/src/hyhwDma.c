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
*  This source file contains the basic definition about DMAC   
*
****************************************************************/


/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/
#include "hyTypes.h"
#include "BoardSupportPackage.h"

/*------------------------------------------------------------------------------
  Project include files:
------------------------------------------------------------------------------*/
#include "hyhwDma.h"

/*------------------------------------------------------------------------------
  Local Types and defines:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  Global variables:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Static Variables:
------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
* 函数:	hyhwDMAC_Init
* 功能:	初始化DMA通道
* 返回:	NONE
*----------------------------------------------------------------------------*/
void hyhwDMAC_Init(void)
{
		U8 i;
    
    DMAC->Configuration = 0;
    for (i = 0; i < MAX_DMAC_CHANNELS; i++) 
    {
        DMAC->sDmaChannels[i].Configuration = 0;
		}
    DMAC->IntErrorClear   = 0xFFFFFFFF;
    DMAC->IntTCClear      = 0xFFFFFFFF;
    DMAC->Configuration   = DMA_DATA_MODE<<2
														| DMA_DATA_MODE<<1
														| 1;
}

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
					)
{
	DMAC->IntErrorClear|= 1<<channel;
	DMAC->IntTCClear |= 1<<channel;
	DMAC->sDmaChannels[channel].SrcAddr = (U32)sa;
	DMAC->sDmaChannels[channel].DestAddr = (U32)da;
	DMAC->sDmaChannels[channel].LLI = 0;//AHB master 1
	
  if(TransType == DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL)
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												(2 << 6) |  //外设号，SPI TX应该为2  ，如果其他的外设需要修改
                        //(2<<1) |  
                        DMA_CHANNEL_ENABLE; //channel enable
	}
	else if(TransType == DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL)
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (1<<25)|//Destination AHB master2 //注意不同传输类型的区别
                        (0<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        (3<<1) |  //外设号，SPI RX应该为3  ，如果其他的外设需要修改
                        DMA_CHANNEL_ENABLE; //channel enable
	}	
	else
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        //(2<<1) |  //外设号，SPI应该为2  ，如果其他的外设需要修改
                        DMA_CHANNEL_ENABLE; //channel enable
	}
}

/*-----------------------------------------------------------------------------
* 函数:	hyhwUartDma_Config
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
					)
{
	DMAC->IntErrorClear|= 1<<channel;
	DMAC->IntTCClear |= 1<<channel;
	DMAC->sDmaChannels[channel].SrcAddr = (U32)sa;
	DMAC->sDmaChannels[channel].DestAddr = (U32)da;
	DMAC->sDmaChannels[channel].LLI = 0;//AHB master 1
	
  if(TransType == DMA_MEM_TO_PERIPHERAL_PERIPHERAL_CTRL)
	{
				DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												(0 << 6) |  //UART TX外设号为0
                        (0 << 1) |  
                        0;//DMA_CHANNEL_ENABLE; //channel enable
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount);/*len*/ //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												(0 << 6) |  //UART TX外设号为0
                        (5 << 1) |  
                        DMA_CHANNEL_ENABLE; //channel enable
	}
	else if(TransType == DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL)
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (1<<25)|//Destination AHB master2 //注意不同传输类型的区别
                        (0<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        (1<<1) |  //UART rx 外设号为1
                        DMA_CHANNEL_ENABLE; //channel enable
	}	
	else
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //中断使能,0x80000000
                        (di<<27)| //目标地址是否自动加1
                        (si<<26)| //源地址是否自动加1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //目标地址数据宽度
												(swidth<<18)|//源地址数据宽度
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        //(2<<1) |  //外设号，SPI应该为2  ，如果其他的外设需要修改
                        DMA_CHANNEL_ENABLE; //channel enable
	}
}

