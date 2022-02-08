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
* 函数:	hyhwSPI_Init
* 功能:	初始化SPI,设置SPI clk
* 参数:	
* 返回:	NONE
*----------------------------------------------------------------------------*/
void hyhwSPI_Init(void)
{
	U32 i;
	SPI_FLASH->SPCR  |= SPIF_RESET;
	for(i=0;i<1000;i++);
	SPI_FLASH->SPCR  &= ~SPIF_RESET;
	SPI_FLASH->SPCR = 
										TSC_CLK_DIV | 	// 分频
                    SPIF_LSB_EN;			//小端模式    
  hyhwDMAC_Init();
}




/***************************************************************************
* 函数:	hyhwDelayUS
* 功能:	软件延时nUs
*       说明：这个与主频有关，主频变化时需要调整参数。
* 参数:	需要延时的uS数。
* 返回:	NONE
****************************************************************************/
void hyhwDelayUS(U32 nUs )
{
	U32 i,j;
	for(j=0;j<nUs;j++)
	{
		for(i= 8; i>0;i--)//此延时针对50Mhz主频，5mS时，实际测量为4.9mS
		{
			__NOP();
		}
	}
}

