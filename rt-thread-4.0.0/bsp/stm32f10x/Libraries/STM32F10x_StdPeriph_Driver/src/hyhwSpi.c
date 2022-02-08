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
*  This source file contains the basic definition about spi   
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
#include "hyhwSpi.h"
#include "hyhwGpio.h"
#include "hyhwDma.h"

/*-----------------------------------------------------------------------------
* ����:	hyhwSPI_Init
* ����:	��ʼ��SPI,����SPI clk
* ����:	
* ����:	NONE
*----------------------------------------------------------------------------*/
void hyhwSPI_Init(void)
{
	U32 i;
	SPI_FLASH->SPCR  |= SPIF_RESET;
	for(i=0;i<1000;i++);
	SPI_FLASH->SPCR  &= ~SPIF_RESET;
	SPI_FLASH->SPCR = 
										TSC_CLK_DIV | 	// ��Ƶ
                    SPIF_LSB_EN;			//С��ģʽ    
  hyhwDMAC_Init();
}




/***************************************************************************
* ����:	hyhwDelayUS
* ����:	�����ʱnUs
*       ˵�����������Ƶ�йأ���Ƶ�仯ʱ��Ҫ����������
* ����:	��Ҫ��ʱ��uS����
* ����:	NONE
****************************************************************************/
void hyhwDelayUS(U32 nUs )
{
	U32 i,j;
	for(j=0;j<nUs;j++)
	{
		for(i= 8; i>0;i--)//����ʱ���50Mhz��Ƶ��5mSʱ��ʵ�ʲ���Ϊ4.9mS
		{
			__NOP();
		}
	}
}

