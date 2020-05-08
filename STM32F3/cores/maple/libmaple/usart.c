/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2013 OpenMusicKontrollers.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file libmaple/usart.c
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F3 USART.
 */

#include "usart.h"
#include "gpio.h"
#include "rcc.h"

/*
 * Devices
 */

/** USART1 device */
RING_BUFFER(usart1_rb, USART_RX_BUF_SIZE);
RING_BUFFER(usart1_wb, USART_TX_BUF_SIZE);
const usart_dev usart1 = {
    .regs     = USART1_BASE,
    .rb       = &usart1_rb,
    .wb       = &usart1_wb,
    .clk_id   = RCC_USART1,
    .irq_num  = NVIC_USART1,
};

/** USART2 device */
RING_BUFFER(usart2_rb, USART_RX_BUF_SIZE);
RING_BUFFER(usart2_wb, USART_TX_BUF_SIZE);
const usart_dev usart2 = {
    .regs     = USART2_BASE,
    .rb       = &usart2_rb,
    .wb       = &usart2_wb,
    .clk_id   = RCC_USART2,
    .irq_num  = NVIC_USART2,
};

/** USART3 device */
RING_BUFFER(usart3_rb, USART_RX_BUF_SIZE);
RING_BUFFER(usart3_wb, USART_TX_BUF_SIZE);
const usart_dev usart3 = {
    .regs     = USART3_BASE,
    .rb       = &usart3_rb,
    .wb       = &usart3_wb,
    .clk_id   = RCC_USART3,
    .irq_num  = NVIC_USART3,
};

#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
/** UART4 device */
static ring_buffer uart4_rb;
const usart_dev uart4 = {
    .regs     = UART4_BASE,
    .rb       = &uart4_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_UART4,
    .irq_num  = NVIC_UART4,
};

/** UART5 device */
static ring_buffer uart5_rb;
const usart_dev uart5 = {
    .regs     = UART5_BASE,
    .rb       = &uart5_rb,
    .max_baud = 2250000UL,
    .clk_id   = RCC_UART5,
    .irq_num  = NVIC_UART5,
};
#endif

/*
 * Routines
 */

void usart_config_gpios_async(const usart_dev *udev, uint8 rx_pin, uint8 tx_pin)
{
	(void)udev; // not ued. Currently only USART1..3 are available (LQFP48 pin device)
    gpio_set_mode(rx_pin, GPIO_AF_INPUT);
    gpio_set_mode(tx_pin, GPIO_AF_OUTPUT);
    gpio_set_af(rx_pin, GPIO_AF_USART1_2_3);
    gpio_set_af(tx_pin, GPIO_AF_USART1_2_3);
}

void usart_set_baud_rate(const usart_dev *dev, uint32 clock_speed, uint32 baud) {
    /* Figure out the clock speed, if the user doesn't give one. */
    if (clock_speed == 0) {
        clock_speed = _usart_clock_freq(dev);
    }
    ASSERT(clock_speed);

		uint32 divider = clock_speed / baud;
		uint32 tmpreg = clock_speed % baud;
		/* round divider : if fractional part i greater than 0.5 increment divider */
		if (tmpreg >= baud / 2)
			divider++;
		dev->regs->BRR = (uint16)divider;
}

uint32 usart_tx(const usart_dev *dev, const uint8 *buf, uint32 len) {
    usart_reg_map *regs = dev->regs;
    uint32 txed = 0;
    while ((regs->SR & USART_SR_TXE) && (txed < len)) {
        regs->TDR = buf[txed++] & USART_TDR_TDR;
    }
    return txed;
}


uint32 _usart_clock_freq(const usart_dev *dev) {
    rcc_clk_domain domain = rcc_dev_clk(dev->clk_id);
    return (domain == RCC_APB1 ? STM32_PCLK1 :
            (domain == RCC_APB2 ? STM32_PCLK2 : 0));
}

/**
 * @brief Call a function on each USART.
 * @param fn Function to call.
 */
void usart_foreach(void (*fn)(const usart_dev*)) {
    fn(USART1);
    fn(USART2);
    fn(USART3);
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    fn(UART4);
    fn(UART5);
#endif
}

/**
 * @brief Get GPIO alternate function mode for a USART.
 * @param dev USART whose gpio_af to get.
 * @return gpio_af corresponding to dev.
 */
gpio_af usart_get_af(const usart_dev *dev) {
    switch (dev->clk_id) {
    case RCC_USART1:
    case RCC_USART2:
    case RCC_USART3:
        return GPIO_AF_USART1_2_3;
#if defined(STM32_HIGH_DENSITY) || defined(STM32_XL_DENSITY)
    case RCC_UART4:
    case RCC_UART5:
        return GPIO_AF_5;
#endif
    default:
        return (gpio_af)-1;
    }
}

/**
 * @brief Initialize a serial port.
 * @param dev         Serial port to be initialized
 */
void usart_init(const usart_dev *dev) {
    rb_reset(dev->rb);
    rb_reset(dev->wb);
    rcc_clk_enable(dev->clk_id);
    nvic_irq_enable(dev->irq_num);
}

/**
 * @brief Enable a serial port.
 *
 * USART is enabled in single buffer transmission mode, multibuffer
 * receiver mode, 8n1.
 *
 * Serial port must have a baud rate configured to work properly.
 *
 * @param dev Serial port to enable.
 * @see usart_set_baud_rate()
 */
void usart_enable(const usart_dev *dev) {
    usart_reg_map *regs = dev->regs;
    regs->CR1 = (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE |
                 USART_CR1_M_8N1);
    regs->CR1 |= USART_CR1_UE;
}

/**
 * @brief Turn off a serial port.
 * @param dev Serial port to be disabled
 */
void usart_disable(const usart_dev *dev) {
    /* FIXME this misbehaves (on F1) if you try to use PWM on TX afterwards */
    usart_reg_map *regs = dev->regs;

    /* TC bit must be high before disabling the USART */
    while((regs->CR1 & USART_CR1_UE) && !(regs->SR & USART_SR_TC))
        ;

    /* Disable UE */
    regs->CR1 &= ~USART_CR1_UE;

    /* Clean up buffer */
    usart_reset_rx(dev);
}

/**
 * @brief Nonblocking USART receive.
 * @param dev Serial port to receive bytes from
 * @param buf Buffer to store received bytes into
 * @param len Maximum number of bytes to store
 * @return Number of bytes received
 */
uint32 usart_rx(const usart_dev *dev, uint8 *buf, uint32 len) {
    uint32 rxed = 0;
    while (usart_read_available(dev) && rxed < len) {
        *buf++ = usart_getc(dev);
        rxed++;
    }
    return rxed;
}

/**
 * @brief Transmit an unsigned integer to the specified serial port in
 *        decimal format.
 *
 * This function blocks until the integer's digits have been
 * completely transmitted.
 *
 * @param dev Serial port to send on
 * @param val Number to print
 */
void usart_putudec(const usart_dev *dev, uint32 val) {
    char digits[12];
    int i = 0;

    do {
        digits[i++] = val % 10 + '0';
        val /= 10;
    } while (val > 0);

    while (--i >= 0) {
        usart_putc(dev, digits[i]);
    }
}

/*
 * Interrupt handlers.
 */

static inline void usart_irq(const usart_dev * udev)
{
    /* Handling RXNEIE and TXEIE interrupts.
	 * See table 198 (sec 27.4, p809) in STM document RM0008 rev 15.
	 * We enable RXNEIE. */

	register usart_reg_map * regs = udev->regs;

	// Receive part.. RXNE signifies availability of a byte in DR.
	if (regs->CR1 & USART_CR1_RXNEIE)
	{ // check error flags
		if ( regs->SR & (USART_SR_ORE | USART_SR_FE | USART_SR_PE) )
		{ // overrun, framing or parity error: clear the error flags
			regs->ICR = (USART_ICR_ORECF | USART_ICR_FECF | USART_ICR_PECF);
		}
		if (regs->SR & USART_SR_RXNE)
		{ // push bytes around in the ring buffer
			rb_write_safe(udev->rb, (uint8) regs->RDR);
		}
	}
	// Transmit part. TXE signifies readiness to send a byte to DR
	if ((regs->CR1 & USART_CR1_TXEIE) && (regs->SR & USART_SR_TXE))
	{
		register int val = rb_read_safe(udev->wb);
		if (val!=-1)
			regs->TDR = (uint8_t)val;
		else
			regs->CR1 &= ~((uint32)USART_CR1_TXEIE); // disable TXEIE
	}
}

void __irq_usart1(void) {
    usart_irq(USART1);
}

void __irq_usart2(void) {
    usart_irq(USART2);
}

void __irq_usart3(void) {
    usart_irq(USART3);
}

#ifdef STM32_HIGH_DENSITY
void __irq_uart4(void) {
    usart_irq(&uart4_rb, UART4_BASE);
}

void __irq_uart5(void) {
    usart_irq(&uart5_rb, UART5_BASE);
}
#endif
