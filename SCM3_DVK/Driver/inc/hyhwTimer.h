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
*
****************************************************************/

#ifndef HY_HW_TIMER_H_
#define HY_HW_TIMER_H_

/*------------------------------------------------------------------------------
Standard include files:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Project include files:
------------------------------------------------------------------------------*/
#include "SCM3.h"
#include "hyTypes.h"	
	
/*************************************************************************
 * Timer control寄存器相关定义
 *************************************************************************/


/*******************  Bit definition for TIMER_CR register  ********************/
// TimerCtrl
#define TIMER_CTRL_DISABLE 	    		0x00
#define TIMER_CTRL_ENABLE 		    	0x80
#define TIMER_CTRL_PERIODIC 	    	0x40  //按指定周期计时
#define TIMER_CTRL_IE 							0x20
#define TIMER_CTRL_PRESCALE256     	0x08
#define TIMER_CTRL_PRESCALE16      	0x04
#define TIMER_CTRL_PRESCALE0       	0x00
#define TIMER_CTRL_SIZE32       		0x02
#define TIMER_CTRL_ONESHOT 	    		0x01

#define INTMODE_ONESHOT							0x01
#define INTMODE_WRAPPING						0x00  //连续中断



/*************************************************************************
 * Timer 寄存器定义
 *************************************************************************/

typedef struct
{
	__IO uint32_t  Timer1Load; // @ 0x00
  __IO uint32_t Timer1Value; 	// @ 0x04
  __IO uint32_t Timer1Ctrl;  	// @ 0x08
  __IO uint32_t Timer1IntClr;	// @ 0x0C
  __IO uint32_t Timer1RIS;   	// @ 0x10
  __IO uint32_t Timer1MIS;   	// @ 0x14
  __IO uint32_t Timer1BGL;   	// @ 0x18

  const uint32_t fill1[1];
  
  __IO uint32_t Timer2Load;  	// @ 0x20
  __IO uint32_t Timer2Value; 	// @ 0x24
  __IO uint32_t Timer2Ctrl;  	// @ 0x28
  __IO uint32_t Timer2IntClr;	// @ 0x2C
  __IO uint32_t Timer2RIS;   	// @ 0x30
  __IO uint32_t Timer2MIS;   	// @ 0x34
  __IO uint32_t Timer2BGL;   	// @ 0x38
  
  const uint32_t fill2[945];
  
  __IO uint32_t TimerITCR;   	// @ 0xF00
  __IO uint32_t TimerITOP;   	// @ 0xF04
  
  const uint32_t fill3[54];

  __IO const uint32_t TimerPeriphID0;  // @ 0xFE0
  __IO const uint32_t TimerPeriphID1;
  __IO const uint32_t TimerPeriphID2;
  __IO const uint32_t TimerPeriphID3;
  __IO const uint32_t TimerPCellID0;
  __IO const uint32_t TimerPCellID1;
  __IO const uint32_t TimerPCellID2;
  __IO const uint32_t TimerPCellID3;

} TIM_TypeDef;


/*************************************************************************
 * Function Prototypes:
 *************************************************************************/
/*-------------------------------------------------------------------------
*  @brief   初始化定时器A Timer1的中断时间，以uS为单位。
*  @param	 IntTimeUs   	定时时间间隔
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //连续中断    
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
void  hyhwTimerA_InitTimer1 (U32 IntTimeUs,U8 IntMode);
/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1Enable
* 功能:	启动TimerA Time1，开始计数
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer1Start()		TIMA->Timer1Ctrl|=TIMER_CTRL_ENABLE

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1Disable
* 功能:	启动TimerA Time1，停止计数
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer1Stop()		TIMA->Timer1Ctrl&=(~TIMER_CTRL_ENABLE)

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntEnable
* 功能:	启动TimerA Time1，使能中断
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer1IntEnable()		TIMA->Timer1Ctrl|=TIMER_CTRL_IE

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntDisable
* 功能:	启动TimerA Time1，禁止中断
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer1IntDisable()		TIMA->Timer1Ctrl&=(~TIMER_CTRL_IE)

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntClear
* 功能:	启动TimerA Time1，清除中断标志位
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer1IntClear()		TIMA->Timer1IntClr = 0x01

/*-------------------------------------------------------------------------
*  @brief   hyhwTimer1_IRQ 中断处理函数
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
void hyhwTimerA_IRQ(void);


///////////////Timer2////////////////////////////////////////////////////////



/*-------------------------------------------------------------------------
*  @brief   初始化定时器A Timer1的中断时间，以uS为单位。
*  @param	 IntTimeUs   	定时时间间隔
*  @param  IntMode  	
				#define INTMODE_ONESHOT							0x01
				#define INTMODE_WRAPPING						0x00  //连续中断    
*  @return non
*  NOTES:
*-------------------------------------------------------------------------*/
void  hyhwTimerA_InitTimer2 (U32 IntTimeUs,U8 IntMode);
/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1Enable
* 功能:	启动TimerA Time1，开始计数
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer2Start()		TIMA->Timer2Ctrl|=TIMER_CTRL_ENABLE

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1Disable
* 功能:	启动TimerA Time1，停止计数
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer2Stop()		TIMA->Timer2Ctrl&=(~TIMER_CTRL_ENABLE)

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntEnable
* 功能:	启动TimerA Time1，使能中断
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer2IntEnable()		TIMA->Timer2Ctrl|=TIMER_CTRL_IE

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntDisable
* 功能:	启动TimerA Time1，禁止中断
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer2IntDisable()		TIMA->Timer2Ctrl&=(~TIMER_CTRL_IE)

/*-----------------------------------------------------------------------------
* 函数:	hyhwTimerA_Timer1IntClear
* 功能:	启动TimerA Time1，清除中断标志位
*----------------------------------------------------------------------------*/
#define hyhwTimerA_Timer2IntClear()		TIMA->Timer2IntClr = 0x01



#endif /* TM_LLIC_API_UART_H_ */




