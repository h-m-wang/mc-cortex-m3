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
*  This source file contains the basic definition about uart   
*
****************************************************************/

#ifndef HY_HW_UART_H_
#define HY_HW_UART_H_

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
 * @brief UART IP3106 baud rate enumeration
 *
 * The UART IP3106 can be configured for different baud rates.
 */
typedef enum hyhwUart_Baudrate_en
{
  hyhwUart_Baudrate_115200 = 115200,
  hyhwUart_Baudrate_57600  = 57600,
  hyhwUart_Baudrate_38400  = 38400,
  hyhwUart_Baudrate_19200  = 19200,
  hyhwUart_Baudrate_9600   = 9600,
  hyhwUart_Baudrate_4800   = 4800,
  hyhwUart_Baudrate_3600   = 3600,
  hyhwUart_Baudrate_2400   = 2400
 
} hyhwUart_Baudrate_en;

/**
 * @brief UART IP3106 data bits enumeration
 *
 * The UART IP3106 can be configured for different data bits length.
 */
typedef enum hyhwUart_DataBits_en
{
  hyhwUart_DataBits_5 = 0x00, 
  hyhwUart_DataBits_6 = 0x20, 
  hyhwUart_DataBits_7 = 0x40, 
  hyhwUart_DataBits_8 = 0x60
} hyhwUart_DataBits_en;

/**
 * @brief UART IP3106 stop bits enumeration
 *
 * The UART IP3106 can be configured for different stop bit length.
 */
typedef enum hyhwUart_StopBits_en
{
  hyhwUart_StopBits_1 = 0x00, 
  hyhwUart_StopBits_2 = 0x08 
} hyhwUart_StopBits_en;

/**
 * @brief UART IP3106 parity enumeration
 *
 * The UART IP3106 has the ability to configure parity checking.
 */
typedef enum hyhwUart_Parity_en
{
  hyhwUart_Parity_Non      = 0x00, /* parity checking disabled */
  hyhwUart_Parity_Odd      = 0x02, /* data+parity bit will have and odd  numer of 1s.*/
  hyhwUart_Parity_Even     = 0x06, /* data+parity bit will have and even numer of 1s.*/
} hyhwUart_Parity_en;


/** @defgroup USART_Interrupt_definition 
  * @{
  */

#define USART_IT_RIM                          ((U16)0x0001)
#define USART_IT_CTSM                         ((U16)0x0002)
#define USART_IT_DCDM                         ((U16)0x0004)
#define USART_IT_DSRM                         ((U16)0x0008)
#define USART_IT_RX                           ((U16)0x0010)
#define USART_IT_TX                           ((U16)0x0020)
#define USART_IT_RT                           ((U16)0x0040)
#define USART_IT_FE                           ((U16)0x0080)
#define USART_IT_PE                           ((U16)0x0100)
#define USART_IT_BE                           ((U16)0x0200)
#define USART_IT_OE                           ((U16)0x0400)

/** @defgroup USART_CR 
  * @{
  */
#define USART_CR_CTS_EN						  ((U16)0x8000)
#define USART_CR_RTS_EN                       ((U16)0x4000)
#define USART_CR_RECEIVE_EN                   ((U16)0x0200)
#define USART_CR_TRANSMIT_EN                  ((U16)0x0100)
#define USART_CR_UART_EN                  	  ((U16)0x0001)

/** @defgroup USART_FR  FLAG Register
  * @{
  */

#define USART_FR_TRANSMIT_FIFO_EMPTY          ((U16)0x0080)
#define USART_FR_RECEIVE_FIFO_FULL            ((U16)0x0040)
#define USART_FR_TRANSMIT_FIFO_FULL        		((U16)0x0020)
#define USART_FR_RECEIVE_FIFO_EMPTY           ((U16)0x0010)


/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
typedef  struct 
{
	__IO uint32_t     DR;
	__IO uint32_t     RSR_ECR;
	__IO uint32_t     RESERVED[(0x018-0x08)/4];
	__IO uint32_t     FR;
	__IO uint32_t     RESERVED1;
	__IO uint32_t     ILPR;
	__IO uint32_t     IBRD;
	__IO uint32_t     FBRD;
	__IO uint32_t     LCR_H;
	__IO uint32_t     CR;
	__IO uint32_t     IFLS;
	__IO uint32_t     IMSC;
	__IO uint32_t     RIS;
	__IO uint32_t     MIS;
	__IO uint32_t     ICR;
	__IO uint32_t     DMACR;
}  USART_TypeDef ;
/*------------------------------------------------------------------------------
Exported Function protoypes:
------------------------------------------------------------------------------*/

/**
* @brief The UART hyhwUart_Init service function. (IC driver layer)
*
* This function is used to initialise the UART IP3106. The application
* programmer has the ability to setup the UART IP3106 for different
* configurations.
*
* @see                   hyhwUart_Baudrate_en_t
* @see                   hyhwUart_DataBits_en_t
* @see                   hyhwUart_StopBits_en_t
* @see                   hyhwUart_Parity_en_t
* @param 	               baudrate : baud rate parameter
* @param 	               databits : the number of data bits
* @param 	               stopbits : the number of stop bits
* @param 	               parity : parity type
* @returns               Returns an error status code
* @retval                TM_OK : in case of success
* @retval                TM_ERR_RESOURCE_OWNED : resource already owned
* @retval                TM_LLIC_UART_ERR_OSAL : OSAL error
*/
U32 hyhwUart_Init(hyhwUart_Baudrate_en baudrate,
                                    hyhwUart_DataBits_en databits,
                                    hyhwUart_StopBits_en stopbits,
                                    hyhwUart_Parity_en   parity);

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart__IntConfig
* 功能:	使能或者关闭串口中的某些中断
* 参数:	none
* 返回:	none
*----------------------------------------------------------------------------*/
void hyhwUart__IntConfig(U16 USART_IT, FunctionalState NewState);

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_WriteFifo
* 功能:	向UART的fifo写入一个字节
* 参数:	写入的字节
* 返回:	HY_OK		-- 成功
*		HY_ERROR	-- 超时
*----------------------------------------------------------------------------*/
U32 hyhwUart_SendCh(unsigned char ch);

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_IRQ
* 功能:	串口中断函数
* 参数:	无
* 返回:	无
*----------------------------------------------------------------------------*/
void hyhwUart_IRQ(void);

/*-----------------------------------------------------------------------------
* 函数:	hyhwUart_DeInit
* 功能:	disable RX and TX
* 
*----------------------------------------------------------------------------*/
void hyhwUart_DeInit(void);


#endif /* TM_LLIC_API_UART_H_ */




