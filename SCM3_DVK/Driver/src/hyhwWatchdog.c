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
 * Description	: ��ʼ�����Ź�
 * Paramters	:   ��
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Init(void)
{
	WWDG->WdogLoad = HYHW_APB_CLOCK; //����1Sװ��ֵ
	WWDG->WdogControl = 0x03;					//int ,reset enable
	hyhwWatchdog_RegLocked();				 //��ס�Ĵ��������޸�
}


/*************************************************************************
 * Function	: hyhwWatchdog_Feed
 * Description	: ι���Ź�
 * Paramters	:   ��
 * Return		: none
  *************************************************************************/
void hyhwWatchdog_Feed(void)
{
	hyhwWatchdog_RegUnLocked();			//�����Ĵ���
	WWDG->WdogLoad = HYHW_APB_CLOCK; //����1Sװ��ֵ
	hyhwWatchdog_RegLocked();				 //��ס�Ĵ��������޸�
}
