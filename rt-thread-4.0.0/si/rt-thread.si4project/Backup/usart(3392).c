/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2013-05-13     aozima       update for kehong-lingtai.
 * 2015-01-31     armink       make sure the serial transmit complete in putc()
 * 2016-05-13     armink       add DMA Rx mode
 * 2017-01-19     aubr.cool    add interrupt Tx mode
 * 2017-04-13     aubr.cool    correct Rx parity err
 */

//#include "stm32f10x.h"
#include "hyhwUart.h"
#include "hyhwDma.h"
#include "usart.h"
#include "board.h"
#include <rtdevice.h>

/* USART1 */
#define UART1_GPIO_TX        GPIO_0
#define UART1_GPIO_RX        GPIO_1
#define UART1_GPIO           GPIOA

/* USART2 */
#define UART2_GPIO_TX        GPIO_2
#define UART2_GPIO_RX        GPIO_3
#define UART2_GPIO           GPIOA


/* uart driver */
struct cm3_uart
{
    USART_TypeDef *uart_device;
    IRQn_Type irq;
#ifdef RT_SERIAL_USING_DMA    
    struct cm3_uart_dma
    {
        /* dma channel */
        //DMA_Channel_TypeDef *rx_ch;
        DMAC_TypeDef *rx_ch;
        /* dma global flag */
        uint32_t rx_gl_flag;
        /* dma irq channel */
        uint8_t rx_irq_ch;
        /* setting receive len */
        rt_size_t setting_recv_len;
        /* last receive index */
        rt_size_t last_recv_index;
    } dma;
#endif /* RT_SERIAL_USING_DMA */    
};

#ifdef RT_SERIAL_USING_DMA
static void DMA_Configuration(struct rt_serial_device *serial);
#endif /* RT_SERIAL_USING_DMA */ 

static rt_err_t stm32_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{
    RT_ASSERT(serial != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);
		//struct cm3_uart *uart = (struct cm3_uart *)serial->parent.user_data;

    hyhwUart_Baudrate_en baudrate = (hyhwUart_Baudrate_en)cfg->baud_rate;
    hyhwUart_DataBits_en databits = (hyhwUart_DataBits_en)cfg->data_bits;
    hyhwUart_StopBits_en stopbits = (hyhwUart_StopBits_en)cfg->stop_bits;
    hyhwUart_Parity_en   parity = (hyhwUart_Parity_en)cfg->parity;
    hyhwUart_Init(baudrate, databits, stopbits, parity);
    hyhwUart__IntConfig(USART_IT_RX, ENABLE);
    hyhwUart__IntConfig(USART_IT_TX, ENABLE);

    return RT_EOK;
}

static rt_err_t stm32_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct cm3_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct cm3_uart *)serial->parent.user_data;

    switch (cmd)
    {
        /* disable interrupt */
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable rx irq */
        hyhwUart__IntConfig(uart->irq, DISABLE);
        /* disable interrupt */
        //USART_ITConfig(uart->uart_device, USART_IT_RXNE, DISABLE);
        break;
        /* enable interrupt */
    case RT_DEVICE_CTRL_SET_INT:
        /* enable rx irq */
        hyhwUart__IntConfig(uart->irq, ENABLE);
        /* enable interrupt */
        //USART_ITConfig(uart->uart_device, USART_IT_RXNE, ENABLE);
        break;
#ifdef RT_SERIAL_USING_DMA
        /* USART config */
    case RT_DEVICE_CTRL_CONFIG :
        if ((rt_uint32_t)(arg) == RT_DEVICE_FLAG_DMA_RX) {
            //DMA_Configuration(serial);
        }
        break;
#endif /* RT_SERIAL_USING_DMA */    
    }
    return RT_EOK;
}

static int stm32_putc(struct rt_serial_device *serial, char c)
{
    RT_ASSERT(serial != RT_NULL);
    //struct cm3_uart *uart = (struct cm3_uart *)serial->parent.user_data;
    
    return hyhwUart_SendCh(c);
}

static int stm32_getc(struct rt_serial_device *serial)
{
    int ch;
    struct cm3_uart* uart;

    RT_ASSERT(serial != RT_NULL);
    uart = (struct cm3_uart *)serial->parent.user_data;

    ch = -1;
    if (uart->uart_device->MIS & USART_IT_RX)
    {
        ch = uart->uart_device->DR & 0xff;
    }

    return ch;
}

#ifdef RT_SERIAL_USING_DMA
/**
 * Serial port receive idle process. This need add to uart idle ISR.
 *
 * @param serial serial device
 */
static void dma_uart_rx_idle_isr(struct rt_serial_device *serial) {
    struct cm3_uart *uart = (struct cm3_uart *) serial->parent.user_data;
    rt_size_t recv_total_index, recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_total_index = uart->dma.setting_recv_len; // - DMA_GetCurrDataCounter(uart->dma.rx_ch);
    recv_len = recv_total_index - uart->dma.last_recv_index;
    uart->dma.last_recv_index = recv_total_index;
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len) rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));

    /* read a data for clear receive idle interrupt flag */
    //USART_ReceiveData(uart->uart_device);
    //DMA_ClearFlag(uart->dma.rx_gl_flag);
}

/**
 * DMA receive done process. This need add to DMA receive done ISR.
 *
 * @param serial serial device
 */
static void dma_rx_done_isr(struct rt_serial_device *serial) {
    struct cm3_uart *uart = (struct cm3_uart *) serial->parent.user_data;
    rt_size_t recv_len;
    rt_base_t level;

    /* disable interrupt */
    level = rt_hw_interrupt_disable();

    recv_len = uart->dma.setting_recv_len - uart->dma.last_recv_index;
    /* reset last recv index */
    uart->dma.last_recv_index = 0;
    /* enable interrupt */
    rt_hw_interrupt_enable(level);

    if (recv_len) rt_hw_serial_isr(serial, RT_SERIAL_EVENT_RX_DMADONE | (recv_len << 8));

    //DMA_ClearFlag(uart->dma.rx_gl_flag);
}
#endif /* RT_SERIAL_USING_DMA */ 

/**
 * Uart common interrupt process. This need add to uart ISR.
 *
 * @param serial serial device
 */
static void uart_isr(struct rt_serial_device *serial) {
    struct cm3_uart *uart = (struct cm3_uart *) serial->parent.user_data;

    RT_ASSERT(uart != RT_NULL);
    hyhwUart_IRQ();
}

static const struct rt_uart_ops cm3_uart_ops =
{
    stm32_configure,
    stm32_control,
    stm32_putc,
    stm32_getc,
};

#if defined(RT_USING_UART1)
/* UART1 device driver structure */
struct cm3_uart uart1 =
{
    USART,
    UART_IRQn,
#ifdef RT_SERIAL_USING_DMA
    {
        DMA_CHANNEL1,
        0,
        DMAC_IRQn + 1,
        0,
    },
#endif /* RT_SERIAL_USING_DMA */       
};
struct rt_serial_device serial1;

void USART1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    uart_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}

#ifdef RT_SERIAL_USING_DMA
void DMA1_Channel5_IRQHandler(void) {
    /* enter interrupt */
    rt_interrupt_enter();

    dma_rx_done_isr(&serial1);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* RT_SERIAL_USING_DMA */   

#endif /* RT_USING_UART1 */  

void rt_hw_usart_init(void)
{
    struct cm3_uart *uart = &uart1;
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    config.baud_rate = BAUD_RATE_115200;

    serial1.ops    = &cm3_uart_ops;
    serial1.config = config;

    struct rt_serial_rx_fifo *rx_fifo = (struct rt_serial_rx_fifo *)serial1->serial_rx;
    hyhwUartDma_Config(0, uart->uart_device->DR, rx_fifo->buffer, serial1->config.bufsz, 
        0, 1, DMA_WIDTH_32_BIT, DMA_WIDTH_32_BIT, DMA_PERIPHERAL_TO_MEM_DMA_CTRL);

    NVIC_EnableIRQ(UART_IRQn | DMAC_IRQn);

    /* register UART1 device */
    rt_hw_serial_register(&serial1, "uart1",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX |
                          RT_DEVICE_FLAG_INT_TX |   RT_DEVICE_FLAG_DMA_RX | RT_DEVICE_FLAG_DMA_TX,
                          uart);
}
