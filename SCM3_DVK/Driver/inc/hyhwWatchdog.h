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
*  This source file contains the basic definition about GPIO   
*
****************************************************************/

#ifndef HY_HW_WATCHDOG_H_
#define HY_HW_WATCHDOG_H_

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
  * @brief General Purpose I/O
  */

typedef struct
{
	
  __IO uint32_t  				WdogLoad;           // 看门狗装载值
  __IO uint32_t  				WdogValue;          // 看门狗当前值
  __IO uint32_t  				WdogControl;				// 看门狗控制寄存器
	__IO uint32_t  				WdogIntClr;					//
	__IO uint32_t  				WdogRIS;						//
	__IO uint32_t  				WdogMIS;						//
	const uint32_t fill1[762];
	__IO uint32_t  				WdogLock;						//
  
} WWDG_TypeDef;


/*************************************************************************
 * DEFINES
 *************************************************************************/
#define hyhwWatchdog_RegLocked()		WWDG->WdogLock = 0
#define hyhwWatchdog_RegUnLocked()	WWDG->WdogLock = 0x1ACCE551

/*************************************************************************
 * Function	: hyhwWatchdog_Init
 * Description	: 初始化看门狗
 * Paramters	:   无
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Init(void);

/*************************************************************************
 * Function	: hyhwWatchdog_Feed
 * Description	: 喂看门狗
 * Paramters	:   无
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Feed(void);
#endif /* TM_LLIC_API_GPIO_H_ */
