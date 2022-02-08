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
/*************************************************************************
 * Function	: hyhwGpio_SetOut
 * Description	: This function sets the general purpose as an output
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetOut(GPIO_TypeDef *PORT, U8 Pin)
{
	PORT->GpioDIR |= Pin;
}

/*************************************************************************
 * Function 	: hyhwGpio_SetIn
 * Description	: This function sets the general purpose as an input
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetIn(GPIO_TypeDef *PORT, U8 Pin)
{
	PORT->GpioDIR &= ~Pin;
}

/*************************************************************************
 * Function	: hyhwGpio_SetHigh
 * Description	: This function sets the general purpose output pin high
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetHigh(GPIO_TypeDef *PORT, U8 Pin)
{
	PORT->GpioDATA[255] |= Pin;

}

/*************************************************************************
 * Function 	: hyhwGpio_SetLow
 * Description	: This function sets the general purpose output pin low
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: none
 *************************************************************************/
void hyhwGpio_SetLow(GPIO_TypeDef *PORT, U8 Pin)
{
	PORT->GpioDATA[255] &= ~Pin;
}

/*************************************************************************
 * Function	: hyhwGpio_Read
 * Description	: This function reads a gpio
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: if the Gpio is high, return 1, else return 0
 *************************************************************************/
unsigned char hyhwGpio_Read(GPIO_TypeDef *PORT, U8 Pin)
{
	if(PORT->GpioDATA[255] & Pin)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*************************************************************************
 * Function	: hyhwGpio_IntConfig
 * Description	: This function ����IO�ж�ģʽ���ж�ʹ��
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 									IntMode��
 									#define GPIO_INTMODE_LOWLEVEL 	0x0
									#define GPIO_INTMODE_HIGHLEVEL 	0x1
									#define GPIO_INTMODE_FALLEDGE 	0x2
									#define GPIO_INTMODE_RISEEDGE	  0x3
									#define GPIO_INTMODE_BOTHEDGE	  0x4
 									EnOrDis��
 										
 * Return		: none
 *************************************************************************/
void hyhwGpio_IntConfig(GPIO_TypeDef *PORT, U8 Pin, U8 IntMode,FunctionalState EnOrDis)
{
	switch (IntMode)
  {
    case GPIO_INTMODE_LOWLEVEL:
    	PORT->GpioIS 	|=  Pin;
    	PORT->GpioIEv	&=	~Pin;
      break;
    case GPIO_INTMODE_HIGHLEVEL:
    	PORT->GpioIS 	|=  Pin;
    	PORT->GpioIEv	|=	Pin;
      break;
    case GPIO_INTMODE_FALLEDGE:
    	PORT->GpioIS 	&=  ~Pin;
    	PORT->GpioIEv	&=	~Pin;
    	PORT->GpioIBE &=  ~Pin;
      break;
    case GPIO_INTMODE_RISEEDGE:
    	PORT->GpioIS 	&=  ~Pin;
    	PORT->GpioIEv	|=	Pin;
    	PORT->GpioIBE &=  ~Pin;
      break;
    case GPIO_INTMODE_BOTHEDGE:
    	PORT->GpioIS 	&=  ~Pin;
    	PORT->GpioIBE |=  Pin;
      break;
    default:
      break;
  }
  if(EnOrDis)
  {
  		PORT->GpioIE |= Pin;
  }
  else
  {
  		PORT->GpioIE &= ~Pin;
  }
}

/*************************************************************************
 * Function	: hyhwGpio_IntClr
 * Description	: This function ����жϱ�־λ
 * Paramters	:   PORT:�˿ںţ�GPIOA,GPIOB,GPIOC)
 *                Pin: ĳ���˿��µ�ĳ��IO�ڣ�GPIO0~7��
 * Return		: NONE
 *************************************************************************/
void hyhwGpio_IntClr(GPIO_TypeDef *PORT, U8 Pin)
{
	PORT->GpioIC |= Pin;
}

/*************************************************************************
 * Function	: hyhwGpioA_IRQ
 * Description	: GPIOA�жϷ���������������Ҫ�ж������ĸ��˿�
 * Return		: ��
 *************************************************************************/
void hyhwGpioA_IRQ(void) 
{
	if(GPIOA->GpioMIS&KEY2_PIN)
	{
			hyhwGpio_IntClr(KEY2_PORT,KEY2_PIN);
	}
}

/*************************************************************************
 * Function	: hyhwGpioB_IRQ
 * Description	: GPIOB�жϷ���������������Ҫ�ж������ĸ��˿�
 * Return		: ��
 *************************************************************************/
void hyhwGpioB_IRQ(void) 
{
	if(GPIOB->GpioMIS&KEY1_PIN)
	{
			hyhwGpio_IntClr(GPIOB,KEY1_PIN);
	}
}

/*************************************************************************
 * Function	: hyhwGpioC_IRQ
 * Description	: GPIOC�жϷ���������������Ҫ�ж������ĸ��˿�
 * Return		: ��
 *************************************************************************/
void hyhwGpioC_IRQ(void) 
{
	
}
