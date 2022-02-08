/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      first implementation
 * 2013-07-12     aozima       update for auto initial.
 */

#include <rthw.h>
#include <rtthread.h>

//#include "stm32f10x.h"
//#include "stm32f10x_fsmc.h"
#include "hyhw_SpiFlash.h"
#include "board.h"
#include "usart.h"

/**
 * @addtogroup STM32
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    //NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}

/* #define SYSCLK_FREQ_HSE    HSE_VALUE */
#define SYSCLK_FREQ_24MHz  24000000 
#define SYSCLK_FREQ_36MHz  36000000
#define SYSCLK_FREQ_48MHz  48000000
#define SYSCLK_FREQ_56MHz  56000000
#define SYSCLK_FREQ_72MHz  72000000
#define SYSCLK_FREQ_100MHz 100000000
#define SYSCLK_FREQ_200MHz 200000000

uint32_t SystemCoreClock = SYSCLK_FREQ_200MHz;        /*!< System Clock Frequency (Core Clock) */


/**
 * This is the timer interrupt service routine.
 *
 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial STM32 board.
 */
void rt_hw_board_init(void)
{
	  //使能AHB,这个很关键，否则HREADY不能用
		*((volatile unsigned int*)(0x40016000)) = 0x01;
	
		/*IO 初始化*/
		hyhwSpiFlash_Init();
	
    /* NVIC Configuration */
    //NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );

#if STM32_EXT_SRAM
    EXT_SRAM_Configuration();
#endif

    rt_hw_usart_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

/*@}*/
