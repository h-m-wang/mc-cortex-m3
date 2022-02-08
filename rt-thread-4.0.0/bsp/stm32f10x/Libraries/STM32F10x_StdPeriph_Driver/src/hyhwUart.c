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
* ����:	hyhwUart_Init
* ����:	��ʼ��UART, Ӧ�ò�������ò�ͬ��UART����
* ����:	baudrate	-- UART�Ĳ�����
*		databits	-- ����λ��
*		stopbits	-- ֹͣλ��
*		parity		-- ��żУ������
* ����:	HY_OK		-- �ɹ�
*		HY_ERROR	-- ��ʱ
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
	
	USART->LCR_H = databits|stopbits|parity;                /*�����fifo  disable�� */
	
	USART->ICR = 0x0;                                       /* clear IRQ */
  
  USART->IMSC = 0 ;                            					 /* Ĭ�Ϲر������ж�*/
  
  USART->CR = USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN|USART_CR_CTS_EN|USART_CR_RTS_EN;                                      /* enable UART */	 
	//USART->CR = USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN;                                      /* enable UART */	 
  USART->DMACR = 0x02; //DMA RX,TX enable.
  //hyhwUart__IntConfig(USART_IT_RX, ENABLE);								/* ֻ�򿪽����ж� */
  
	return(HY_OK);  
}

/*-----------------------------------------------------------------------------
* ����:	hyhwUart_DeInit
* ����:	disable RX and TX
* 
*----------------------------------------------------------------------------*/
void hyhwUart_DeInit(void)
{
	
  USART->CR = 0x0;                                        /* disable UART */
 	
	USART->ICR = 0x0;                                       /* clear IRQ */
  
  USART->IMSC = 0 ;                            					 /* Ĭ�Ϲر������ж�*/
  
  USART->CR = 0;//USART_CR_RECEIVE_EN|USART_CR_TRANSMIT_EN|USART_CR_UART_EN;                                      /* enable UART */	 
  USART->DMACR = 0x02; //DMA RX,TX enable.
  //hyhwUart__IntConfig(USART_IT_RX, ENABLE);								/* ֻ�򿪽����ж� */
  
	
}

/*-----------------------------------------------------------------------------
* ����:	hyhwUart__IntConfig
* ����:	ʹ�ܻ��߹رմ����е�ĳЩ�ж�
* ����:	none
* ����:	none
*----------------------------------------------------------------------------*/
void hyhwUart__IntConfig(U16 USART_IT, FunctionalState NewState)
{
  if (NewState == ENABLE)
    USART->IMSC |= USART_IT;
  else
    USART->IMSC &= ~USART_IT;
}

/*-----------------------------------------------------------------------------
* ����:	hyhwUart_WriteFifo
* ����:	��UART��fifoд��һ���ֽ�
* ����:	д����ֽ�
* ����:	HY_OK		-- �ɹ�
*		HY_ERROR	-- ��ʱ
*----------------------------------------------------------------------------*/
U32 hyhwUart_SendCh(unsigned char ch)
{
	
	while (!((USART->FR)&USART_FR_TRANSMIT_FIFO_EMPTY));                          // wait until the transmit FIFO is empty
	USART->DR = ch;	
	return(HY_OK);
}	

/*-----------------------------------------------------------------------------
* ����:	hyhwUart_IRQ
* ����:	�����жϺ���
* ����:	��
* ����:	��
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



















