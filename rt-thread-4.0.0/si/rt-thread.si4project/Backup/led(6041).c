/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include "hyhwGpio.h"
#include "stm32f10x_gpio.h"
#include <rtthread.h>
#include <SCM3.h>

// led define
#ifdef STM32_SIMULATOR
#define led1_rcc                    RCC_APB2Periph_GPIOA
#define led1_gpio                   GPIOA
#define led1_pin                    (GPIO_Pin_5)

#define led2_rcc                    RCC_APB2Periph_GPIOA
#define led2_gpio                   GPIOA
#define led2_pin                    (GPIO_Pin_6)

#else

#define led1_rcc                    RCC_APB2Periph_GPIOE
#define led1_gpio                   GPIOE
#define led1_pin                    (GPIO_Pin_2)

#define led2_rcc                    RCC_APB2Periph_GPIOE
#define led2_gpio                   GPIOE
#define led2_pin                    (GPIO_Pin_3)

#endif // led define #ifdef STM32_SIMULATOR

void rt_hw_led_init(void)
{
    hyhwGpio_SetOut(led1_gpio, led1_pin);
    hyhwGpio_SetOut(led2_gpio, led2_pin);
}

void rt_hw_led_on(rt_uint32_t n)
{
    switch (n)
    {
    case 0:
        hyhwGpio_SetHigh(led1_gpio, led1_pin);
        break;
    case 1:
        hyhwGpio_SetHigh(led2_gpio, led2_pin);
        break;
    default:
        break;
    }
}

void rt_hw_led_off(rt_uint32_t n)
{
    switch (n)
    {
    case 0:
        hyhwGpio_SetLow(led1_gpio, led1_pin);
        break;
    case 1:
        hyhwGpio_SetLow(led2_gpio, led2_pin);
        break;
    default:
        break;
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
static rt_uint8_t led_inited = 0;
void led(rt_uint32_t led, rt_uint32_t value)
{
    /* init led configuration if it's not inited. */
    if (!led_inited)
    {
        rt_hw_led_init();
        led_inited = 1;
    }

    if ( led == 0 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(0);
            break;
        case 1:
            rt_hw_led_on(0);
            break;
        default:
            break;
        }
    }

    if ( led == 1 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(1);
            break;
        case 1:
            rt_hw_led_on(1);
            break;
        default:
            break;
        }
    }
}
FINSH_FUNCTION_EXPORT(led, set led[0 - 1] on[1] or off[0].)
#endif

