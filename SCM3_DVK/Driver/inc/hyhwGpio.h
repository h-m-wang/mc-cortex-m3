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

#ifndef HY_HW_GPIO_H_
#define HY_HW_GPIO_H_

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
	__IO uint32_t 				GpioDATA[256];       // @0x00-0x3FC
  __IO uint32_t 				GpioDIR;             // @0x400
  __IO uint32_t  				GpioIS;              // @0x404
  __IO uint32_t  				GpioIBE;             // @0x408
  __IO uint32_t  				GpioIEv;             // @0x40C
  __IO uint32_t  				GpioIE;              // @0x410
  __IO const uint32_t   GpioRIS;       			 // @0x414
  __IO const uint32_t   GpioMIS;       			 // @0x418
  __IO uint32_t  				GpioIC;              // @0x41C
  __IO uint32_t  				GpioAFSEL;           // @0x420
  
  const uint32_t fill0[119];      					 // @0x424-0x5FC

  __IO uint32_t  				GpioITCR;            // @0x600
  __IO uint32_t  				GpioITIP1;           // @0x604
  __IO uint32_t  				GpioITIP2;           // @0x608
  __IO uint32_t  				GpioITOP1;           // @0x60C
  __IO const uint32_t   GpioITOP2;     		   // @0x610
  __IO uint32_t  				GpioITOP3;           // @0x614
  
  const uint32_t fill1[622];       					 // @0x618-0xFCC
  
  __IO const uint32_t reservedID[4]; 				 // @0xFD0-0xFDC

  __IO const uint32_t GpioPeriphID0; 				 // @ 0xFE0
  __IO const uint32_t GpioPeriphID1;
  __IO const uint32_t GpioPeriphID2;
  __IO const uint32_t GpioPeriphID3;
  __IO const uint32_t GpioPCellID0;
  __IO const uint32_t GpioPCellID1;
  __IO const uint32_t GpioPCellID2;
  __IO const uint32_t GpioPCellID3;
} GPIO_TypeDef;

/*************************************************************************
 * DEFINES
 *************************************************************************/
/* Bit-defines for GPIO lines */
#define GPIO_0  (0x01)            
#define GPIO_1  (0x02)            
#define GPIO_2  (0x04)            
#define GPIO_3  (0x08)      
#define GPIO_4  (0x10)        
#define GPIO_5  (0x20)        
#define GPIO_6  (0x40)        
#define GPIO_7  (0x80)     
#define GPIO_MASK (0xFF)
/*************************************************************************
 * DEFINES GPIO INTTERRUPT MODE
 *************************************************************************/
#define GPIO_INTMODE_LOWLEVEL 	0x0
#define GPIO_INTMODE_HIGHLEVEL 	0x1
#define GPIO_INTMODE_FALLEDGE 	0x2
#define GPIO_INTMODE_RISEEDGE	  0x3
#define GPIO_INTMODE_BOTHEDGE	  0x4

/*************************************************************************
 * Function	: hyhwGpio_SetOut
 * Description	: This function sets the general purpose as an output
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetOut(GPIO_TypeDef *PORT, U8 Pin);

/*************************************************************************
 * Function 	: hyhwGpio_SetIn
 * Description	: This function sets the general purpose as an input
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetIn(GPIO_TypeDef *PORT, U8 Pin);


/*************************************************************************
 * Function	: hyhwGpio_SetHigh
 * Description	: This function sets the general purpose output pin high
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: none
  *************************************************************************/
void hyhwGpio_SetHigh(GPIO_TypeDef *PORT, U8 Pin);

/*************************************************************************
 * Function 	: hyhwGpio_SetLow
 * Description	: This function sets the general purpose output pin low
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: none
 *************************************************************************/
void hyhwGpio_SetLow(GPIO_TypeDef *PORT, U8 Pin);

/*************************************************************************
 * Function	: hyhwGpio_Read
 * Description	: This function reads a gpio
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: if the Gpio is high, return 1, else return 0
 *************************************************************************/
unsigned char hyhwGpio_Read(GPIO_TypeDef *PORT, U8 Pin);

/*************************************************************************
 * Function	: hyhwGpio_IntConfig
 * Description	: This function 设置IO中断模式，中断使能
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 									IntMode：
 									#define GPIO_INTMODE_LOWLEVEL 	0x0
									#define GPIO_INTMODE_HIGHLEVEL 	0x1
									#define GPIO_INTMODE_FALLEDGE 	0x2
									#define GPIO_INTMODE_RISEEDGE	  0x3
									#define GPIO_INTMODE_BOTHEDGE	  0x4
 									EnOrDis：
 										
 * Return		: none
 *************************************************************************/
void hyhwGpio_IntConfig(GPIO_TypeDef *PORT, U8 Pin, U8 IntMode,FunctionalState EnOrDis);

/*************************************************************************
 * Function	: hyhwGpio_IntClr
 * Description	: This function 清除中断标志位
 * Paramters	:   PORT:端口号（GPIOA,GPIOB,GPIOC)
 *                Pin: 某个端口下的某个IO口（GPIO0~7）
 * Return		: NONE
 *************************************************************************/
void hyhwGpio_IntClr(GPIO_TypeDef *PORT, U8 Pin);

/*************************************************************************
 * Function	: hyhwGpioA_IRQ
 * Description	: GPIOA中断服务处理函数，必须先要判断下面哪个端口
 * Return		: 无
 *************************************************************************/
void hyhwGpioA_IRQ(void);

/*************************************************************************
 * Function	: hyhwGpioB_IRQ
 * Description	: GPIOB中断服务处理函数，必须先要判断下面哪个端口
 * Return		: 无
 *************************************************************************/
void hyhwGpioB_IRQ(void);

/*************************************************************************
 * Function	: hyhwGpioB_IRQ
 * Description	: GPIOB中断服务处理函数，必须先要判断下面哪个端口
 * Return		: 无
 *************************************************************************/
void hyhwGpioC_IRQ(void);

#endif /* TM_LLIC_API_GPIO_H_ */
