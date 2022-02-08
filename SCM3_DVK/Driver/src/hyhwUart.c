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
*  This source file contains the basic definition about uart   
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
#include "hyhwUart.h"

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
* 函数:	hyhwUart_Init
* 功能:	初始化UART, 应用层可以配置不同的UART参数
* 参数:	baudrate	-- UART的波特率
*		databits	-- 数据位数
*		stopbits	-- 停止位数
*		parity		-- 奇偶校验类型
* 返回:	HY_OK		-- 成功
*		HY_ERROR	-- 超时
*----------------------------------------------------------------------------*/
U32 hyhwUart_Init(hyhwUart_Baudrate_en baudrate,
                                  hyhwUart_DataBits_en databits,
                                  hyhwUart_StopBits_en stopbits,
                                  hyhwUart_Parity_en   parity)
{
	U32 div;

  USART->CR = 0x0;                                        /* disable UART */
  div = (int)((HYHW_APB_CLOCK/baudrate) * 1000) / 16;
	USART->IBRD = div/1000;                                 /* configure baud rate UARTFBRD */
	USART->FBRD = ((div%1000)*64+500)/1000;                 /* configure baud rate UARTFBRD */
	
	USART->LCR_H = databits|stopbits|parity;                /*这里把fifo  disable了 */
	
	USART->ICR = 0x0;                                       /* clear IRQ */
  
  USART->IMSC = 0 ;                            					 /* 默认关闭所有中断*/
  
  USART->CR = USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN|USART_CR_CTS_EN|USART_CR_RTS_EN;                                      /* enable UART */	 
	//USART->CR = USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN;                                      /* enable UART */	 
  USART->DMACR = 0x02; //DMA RX,TX enable.
  //hyhwUart__IntConfig(USART_IT_RX, ENABLE);								/* 只打开接收中断 */
  
	return(HY_OK);  
}

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_DeInit
* 功能:	disable RX and TX
* 
*----------------------------------------------------------------------------*/
void hyhwUart_DeInit(void)
{
	
  USART->CR = 0x0;                                        /* disable UART */
 	
	USART->ICR = 0x0;                                       /* clear IRQ */
  
  USART->IMSC = 0 ;                            					 /* 默认关闭所有中断*/
  
  USART->CR = 0;//USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN;                                      /* enable UART */	 
  USART->DMACR = 0x02; //DMA RX,TX enable.
  //hyhwUart__IntConfig(USART_IT_RX, ENABLE);								/* 只打开接收中断 */
  
	
}

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart__IntConfig
* 功能:	使能或者关闭串口中的某些中断
* 参数:	none
* 返回:	none
*----------------------------------------------------------------------------*/
void hyhwUart__IntConfig(U16 USART_IT, FunctionalState NewState)
{
  if (NewState == ENABLE)
    USART->IMSC |= USART_IT;
  else
    USART->IMSC &= ~USART_IT;
}

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_WriteFifo
* 功能:	向UART的fifo写入一个字节
* 参数:	写入的字节
* 返回:	HY_OK		-- 成功
*		HY_ERROR	-- 超时
*----------------------------------------------------------------------------*/
U32 hyhwUart_SendCh(unsigned char ch)
{
	
	while (!((USART->FR)&USART_FR_TRANSMIT_FIFO_EMPTY));                          // wait until the transmit FIFO is empty
	USART->DR = ch;	
	return(HY_OK);
}	

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_IRQ
* 功能:	串口中断函数
* 参数:	无
* 返回:	无
*----------------------------------------------------------------------------*/
void hyhwUart_IRQ(void)
{
	U8 ch;
	U16 reg_mis;
	reg_mis = USART->MIS;
	if (reg_mis & USART_IT_RX) 
  	{
    	ch = USART->DR;
    	hyhwUart_SendCh(ch);
    }
}	



















