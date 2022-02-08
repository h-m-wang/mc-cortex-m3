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
*  This source file contains the basic definition about Gpio   
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
#include "hyhwWatchdog.h"

/*------------------------------------------------------------------------------
  Local Types and defines:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
  Global variables:
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Static Variables:
------------------------------------------------------------------------------*/
/*************************************************************************
 * Function	: hyhwWatchdog_Init
 * Description	: 初始化看门狗
 * Paramters	:   无
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Init(void)
{
	WWDG->WdogLoad = HYHW_APB_CLOCK; //设置1S装载值
	WWDG->WdogControl = 0x03;					//int ,reset enable
	hyhwWatchdog_RegLocked();				 //锁住寄存器不让修改
}


/*************************************************************************
 * Function	: hyhwWatchdog_Feed
 * Description	: 喂看门狗
 * Paramters	:   无
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Feed(void)
{
	hyhwWatchdog_RegUnLocked();			//解锁寄存器
	WWDG->WdogLoad = HYHW_APB_CLOCK; //设置1S装载值
	hyhwWatchdog_RegLocked();				 //锁住寄存器不让修改
}
