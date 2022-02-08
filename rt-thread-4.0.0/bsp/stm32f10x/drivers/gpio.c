/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2015-03-24     Bright            the first version
 * 2016-05-23     Margguo@gmail.com Add  48 pins IC define
 * 2018-07-23     jiezhi320         Add GPIO Out_OD mode config
 */

#include <hyhwGpio.h>
#include <rthw.h>
#include <rtdevice.h>
#include <board.h>

#ifdef RT_USING_PIN

#define STM32F10X_PIN_NUMBERS 24 //[48, 64, 100, 144 ]

#define __STM32_PIN(index, gpio, gpio_index) { 0, 0, GPIO##gpio, GPIO_##gpio_index, GPIO_##gpio_index, GPIO_##gpio_index}
#define __STM32_PIN_DEFAULT {-1, 0, 0, 0, 0, 0}

/* STM32 GPIO driver */
struct pin_index
{
    int index;
    uint32_t rcc;
    GPIO_TypeDef *gpio;
    uint32_t pin;
    uint8_t port_source;
    uint8_t pin_source;
};

static const struct pin_index pins[] =
{
#if (STM32F10X_PIN_NUMBERS == 24)
    __STM32_PIN_DEFAULT,
    __STM32_PIN_DEFAULT,
    __STM32_PIN(2, A, 0),
    __STM32_PIN(3, B, 0),
    __STM32_PIN(4, C, 0),
#endif
};

struct pin_irq_map
{
    rt_uint16_t            pinbit;
    rt_uint32_t            irqbit;
    enum IRQn              irqno;
};
static const  struct pin_irq_map pin_irq_map[] =
{
   {GPIO_0,  0, GPIOA_IRQn }, //EXTI_Line0,  EXTI0_IRQn    },
   {GPIO_1,  1, GPIOA_IRQn }, //EXTI_Line1,  EXTI1_IRQn    },
   {GPIO_2,  2, GPIOA_IRQn }, //EXTI_Line2,  EXTI2_IRQn    },
   {GPIO_3,  3, GPIOA_IRQn }, //EXTI_Line3,  EXTI3_IRQn    },
   {GPIO_4,  4, GPIOA_IRQn }, //EXTI_Line4,  EXTI4_IRQn    },
   {GPIO_5,  5, GPIOA_IRQn }, //EXTI_Line5,  EXTI9_5_IRQn  },
   {GPIO_6,  6, GPIOA_IRQn }, //EXTI_Line6,  EXTI9_5_IRQn  },
   {GPIO_7,  7, GPIOA_IRQn }, //EXTI_Line7,  EXTI9_5_IRQn  },
};
struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},                  
};

#define ITEM_NUM(items) sizeof(items)/sizeof(items[0])
const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
};

void stm32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    if (value == PIN_LOW)
    {
        hyhwGpio_SetLow(index->gpio, index->pin);
    }
    else
    {
        hyhwGpio_SetHigh(index->gpio, index->pin);
    }
}

int stm32_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    if (hyhwGpio_Read(index->gpio, index->pin) == Bit_RESET)
    {
        value = PIN_LOW;
    }
    else
    {
        value = PIN_HIGH;
    }

    return value;
}

void stm32_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        hyhwGpio_SetOut(index->gpio, index->pin);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        hyhwGpio_SetIn(index->gpio, index->pin);
    }
    else {
        /* no such setting */
    }
}

rt_inline rt_int32_t bit2bitno(rt_uint32_t bit)
{
    int i;
    for(i = 0; i < 32; i++)
    {
        if((0x01 << i) == bit)
        {
            return i;
        }
    }
    return -1;
}
#if 0
rt_inline const struct pin_irq_map *get_pin_irq_map(uint32_t pinbit)
{
    rt_int32_t mapindex = bit2bitno(pinbit);
    if(mapindex < 0 || mapindex >= ITEM_NUM(pin_irq_map))
    {
        return RT_NULL;
    }
    return &pin_irq_map[mapindex];
};
#endif
rt_err_t stm32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                  rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if(irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if(pin_irq_hdr_tab[irqindex].pin == pin   &&
       pin_irq_hdr_tab[irqindex].hdr == hdr   &&
       pin_irq_hdr_tab[irqindex].mode == mode &&
       pin_irq_hdr_tab[irqindex].args == args
    )
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if(pin_irq_hdr_tab[irqindex].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;
    rt_hw_interrupt_enable(level);
 
    return RT_EOK;
}
rt_err_t stm32_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    rt_int32_t irqindex = -1;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
    }
    irqindex = bit2bitno(index->pin);
    if(irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if(pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    pin_irq_hdr_tab[irqindex].pin = -1;
    pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
    pin_irq_hdr_tab[irqindex].mode = 0;
    pin_irq_hdr_tab[irqindex].args = RT_NULL;
    rt_hw_interrupt_enable(level);
 
    return RT_EOK;
}
rt_err_t stm32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                                  rt_uint32_t enabled)
{
    const struct pin_index *index;
    //const struct pin_irq_map *irqmap;
    rt_base_t level;
    rt_int32_t irqindex = -1;   

    if (enabled != DISABLE && enabled != ENABLE)
    {
        return -RT_ENOSYS;
    }

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return -RT_ENOSYS;
		}
    irqindex = bit2bitno(index->pin);
    if(irqindex < 0 || irqindex >= ITEM_NUM(pin_irq_map))
    {
        return -RT_ENOSYS;
    }
    level = rt_hw_interrupt_disable();
    if(pin_irq_hdr_tab[irqindex].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_ENOSYS;
    }
    //irqmap = &pin_irq_map[irqindex];

    GPIO_TypeDef *port = index->gpio;
    U8 pinNo = index->pin;
    U8 intMode = pin_irq_hdr_tab[irqindex].mode; // GPIO_INTMODE_LOWLEVEL
    FunctionalState enOrDis = (FunctionalState)enabled;
    hyhwGpio_IntConfig(port, pinNo, intMode, enOrDis);
    
    rt_hw_interrupt_enable(level);
    
    return RT_EOK;
}
const static struct rt_pin_ops _stm32_pin_ops =
{
    stm32_pin_mode,
    stm32_pin_write,
    stm32_pin_read,
    stm32_pin_attach_irq,
    stm32_pin_detach_irq,
    stm32_pin_irq_enable,
};

int stm32_hw_pin_init(void)
{
    int result;

    result = rt_device_pin_register("pin", &_stm32_pin_ops, RT_NULL);
    return result;
}
INIT_BOARD_EXPORT(stm32_hw_pin_init);

rt_inline void pin_irq_hdr(int irqno)
{
    hyhwGpio_IntClr(GPIOA, pin_irq_map[irqno].irqbit);
    if(pin_irq_hdr_tab[irqno].hdr)
    {
       pin_irq_hdr_tab[irqno].hdr(pin_irq_hdr_tab[irqno].args);
    }
}
void EXTI0_IRQHandler(void)
{
     /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(0);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI1_IRQHandler(void)
{
     /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(1);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI2_IRQHandler(void)
{
     /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(2);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI3_IRQHandler(void)
{
     /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(3);
    /* leave interrupt */
    rt_interrupt_leave();
}
void EXTI4_IRQHandler(void)
{
     /* enter interrupt */
    rt_interrupt_enter();
    pin_irq_hdr(4);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif
