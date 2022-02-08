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
*  This source file contains the basic definition about Timer   
*  说明： 该MCU内部有两组定时器：A和B，每组里面有两个定时Timer1和Timer2
*         驱动只支持A,B还没有写。
****************************************************************/


/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/
#include "hyTypes.h"
#include "BoardSupportPackage.h"

/*------------------------------------------------------------------------------
  Project include files:
------------------------------------------------------------------------------*/
#include "hyhwTimer.h"
#include "hyhwGpio.h"
/*------------------------------------------------------------------------------
  Local Types and defines:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  Global variables:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Static Variables:
------------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------
*  @brief   初始化定时器A Timer1的中断时间，以uS为单位。
*  @param	 IntTimeUs   	定时时间间隔
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //连续中断    
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
void  hyhwTimerA_InitTimer1 (U32 IntTimeUs,U8 IntMode)
{
	U32 count;
	
	count = (HYHW_APB_CLOCK/1000000)*IntTimeUs;
	
	TIMA->Timer1Ctrl = TIMER_CTRL_PERIODIC|TIMER_CTRL_SIZE32|IntMode;
	TIMA->Timer1BGL  = count;
	TIMA->Timer1Load = count;
	hyhwTimerA_Timer1IntEnable();
	hyhwTimerA_Timer1Start(); //启动定时器
}


/*-------------------------------------------------------------------------
*  @brief   初始化定时器A Timer2的中断时间，以uS为单位。
*  @param	 IntTimeUs   	定时时间间隔
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //连续中断    
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
void  hyhwTimerA_InitTimer2 (U32 IntTimeUs,U8 IntMode)
{
	U32 count;
	
	count = (HYHW_APB_CLOCK/1000000)*IntTimeUs;
	
	TIMA->Timer2Ctrl = TIMER_CTRL_PERIODIC|TIMER_CTRL_SIZE32|IntMode;
	TIMA->Timer2BGL  = count;
	TIMA->Timer2Load = count;
	hyhwTimerA_Timer2IntEnable();
	hyhwTimerA_Timer2Start(); //启动定时器
}

/*-------------------------------------------------------------------------
*  @brief   hyhwTimer2_IRQ 中断处理函数
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
U8 gTest;
void hyhwTimerA_IRQ(void)
{
	if(TIMA->Timer1MIS)////如果是定时器1的中断
	{
		hyhwTimerA_Timer1IntClear();
	
		if(gTest)
		{
		  /* OUT0 LOW */
			hyhwGpio_SetLow(GPIOA,GPIO_0);
			gTest = 0;
		}
		else
		{
			/* OUT0 HIGH */
			hyhwGpio_SetHigh(GPIOA,GPIO_0);
			gTest = 1;
		}
	}
	if(TIMA->Timer2MIS) //如果是定时器2的中断
	{
		hyhwTimerA_Timer2IntClear();
	
	}
}
