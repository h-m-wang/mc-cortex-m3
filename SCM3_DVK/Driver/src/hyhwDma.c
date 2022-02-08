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
* ����:	hyhwDMAC_Init
* ����:	��ʼ��DMAͨ��
* ����:	NONE
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
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												(2 << 6) |  //����ţ�SPI TXӦ��Ϊ2  �����������������Ҫ�޸�
                        //(2<<1) |  
                        DMA_CHANNEL_ENABLE; //channel enable
	}
	else if(TransType == DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL)
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (1<<25)|//Destination AHB master2 //ע�ⲻͬ�������͵�����
                        (0<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        (3<<1) |  //����ţ�SPI RXӦ��Ϊ3  �����������������Ҫ�޸�
                        DMA_CHANNEL_ENABLE; //channel enable
	}	
	else
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        //(2<<1) |  //����ţ�SPIӦ��Ϊ2  �����������������Ҫ�޸�
                        DMA_CHANNEL_ENABLE; //channel enable
	}
}

/*-----------------------------------------------------------------------------
* ����:	hyhwUartDma_Config
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
												(0 << 6) |  //UART TX�����Ϊ0
                        (0 << 1) |  
                        0;//DMA_CHANNEL_ENABLE; //channel enable
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount);/*len*/ //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												(0 << 6) |  //UART TX�����Ϊ0
                        (5 << 1) |  
                        DMA_CHANNEL_ENABLE; //channel enable
	}
	else if(TransType == DMA_PERIPHERAL_TO_MEM_PERIPHERAL_CTRL)
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (1<<25)|//Destination AHB master2 //ע�ⲻͬ�������͵�����
                        (0<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        (1<<1) |  //UART rx �����Ϊ1
                        DMA_CHANNEL_ENABLE; //channel enable
	}	
	else
	{
		DMAC->sDmaChannels[channel].Control =
                        0x80000000 | //�ж�ʹ��,0x80000000
                        (di<<27)| //Ŀ���ַ�Ƿ��Զ���1
                        (si<<26)| //Դ��ַ�Ƿ��Զ���1
                        (0<<25)|//Destination AHB master2
                        (1<<24)|//Source AHB master2
                        /*(width<<18)|*/ //source transfer width
												(dwidth<<21)| //Ŀ���ַ���ݿ��
												(swidth<<18)|//Դ��ַ���ݿ��
												(1<<15)| //Destination burst size 
												(1<<12)|  //source burst size
												(tcount)/*len*/; //transfer size	
		DMAC->sDmaChannels[channel].Configuration =
                        (1<<15) |
                        (TransType << 11) |
												//(2 << 6) |
                        //(2<<1) |  //����ţ�SPIӦ��Ϊ2  �����������������Ҫ�޸�
                        DMA_CHANNEL_ENABLE; //channel enable
	}
}

