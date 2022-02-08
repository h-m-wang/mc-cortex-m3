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
*  ˵���� ��MCU�ڲ������鶨ʱ����A��B��ÿ��������������ʱTimer1��Timer2
*         ����ֻ֧��A,B��û��д��
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
*  @brief   ��ʼ����ʱ��A Timer1���ж�ʱ�䣬��uSΪ��λ��
*  @param	 IntTimeUs   	��ʱʱ����
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //�����ж�    
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
	hyhwTimerA_Timer1Start(); //������ʱ��
}


/*-------------------------------------------------------------------------
*  @brief   ��ʼ����ʱ��A Timer2���ж�ʱ�䣬��uSΪ��λ��
*  @param	 IntTimeUs   	��ʱʱ����
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //�����ж�    
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
	hyhwTimerA_Timer2Start(); //������ʱ��
}

/*-------------------------------------------------------------------------
*  @brief   hyhwTimer2_IRQ �жϴ�����
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
U8 gTest;
void hyhwTimerA_IRQ(void)
{
	if(TIMA->Timer1MIS)////����Ƕ�ʱ��1���ж�
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
	if(TIMA->Timer2MIS) //����Ƕ�ʱ��2���ж�
	{
		hyhwTimerA_Timer2IntClear();
	
	}
}
