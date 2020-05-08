/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file libmaple/stm32f3/include/series/nvic.h
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief STM32F3 Nested Vectored Interrupt Controller (NVIC) support.
 */

#ifndef _LIBMAPLE_STM32F3_NVIC_H_
#define _LIBMAPLE_STM32F3_NVIC_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <libmaple/libmaple_types.h>
#include <libmaple/stm32.h>
#include <libmaple/util.h>

/**
 * @brief STM32F1 interrupt vector table interrupt numbers.
 * @see <libmaple/scb.h>
 */
typedef enum nvic_irq_num {
    NVIC_NMI            = -14,  /**< Non-maskable interrupt */
    NVIC_HARDFAULT      = -13,  /**< Hard fault (all class of fault) */
    NVIC_MEM_MANAGE     = -12,  /**< Memory management */
    NVIC_BUS_FAULT      = -11,  /**< Bus fault: prefetch fault, memory
                                     access fault. */
    NVIC_USAGE_FAULT    = -10,  /**< Usage fault: Undefined instruction or
                                     illegal state. */
    NVIC_SVC            = -5,   /**< System service call via SWI insruction */
    NVIC_DEBUG_MON      = -4,   /**< Debug monitor */
    NVIC_PEND_SVC       = -2,   /**< Pendable request for system service */
    NVIC_SYSTICK        = -1,   /**< System tick timer */

    NVIC_WWDG           = 0,    /**< Window watchdog interrupt */
    NVIC_PVD            = 1,    /**< PVD through EXTI line detection */
    NVIC_TAMP_STAMP     = 2,    /**< Tamper */
    NVIC_RTC_WKUP       = 3,    /**< Real-time clock */
    NVIC_FLASH          = 4,    /**< Flash */
    NVIC_RCC            = 5,    /**< Reset and clock control */
    NVIC_EXTI0          = 6,    /**< EXTI line 0 */
    NVIC_EXTI1          = 7,    /**< EXTI line 1 */
    NVIC_EXTI2          = 8,    /**< EXTI line 2 */ //FIXME capacitive touch
    NVIC_EXTI3          = 9,    /**< EXTI line 3 */
    NVIC_EXTI4          = 10,   /**< EXTI line 4 */
    NVIC_DMA_CH1        = 11,   /**< DMA1 channel 1 */
    NVIC_DMA_CH2        = 12,   /**< DMA1 channel 2 */
    NVIC_DMA_CH3        = 13,   /**< DMA1 channel 3 */
    NVIC_DMA_CH4        = 14,   /**< DMA1 channel 4 */
    NVIC_DMA_CH5        = 15,   /**< DMA1 channel 5 */
    NVIC_DMA_CH6        = 16,   /**< DMA1 channel 6 */
    NVIC_DMA_CH7        = 17,   /**< DMA1 channel 7 */
    NVIC_ADC1_2         = 18,   /**< ADC1 and ADC2 */
    NVIC_USB_HP_CAN_TX  = 19,   /**< USB high priority or CAN TX */
    NVIC_USB_LP_CAN_RX0 = 20,   /**< USB low priority or CAN RX0 */
    NVIC_CAN_RX1        = 21,   /**< CAN RX1 */
    NVIC_CAN_SCE        = 22,   /**< CAN SCE */
    NVIC_EXTI_9_5       = 23,   /**< EXTI line [9:5] */
		//NVIC_TIMER1_BRK_TIMER15 = 24, // FIXME hack
    NVIC_TIMER1_BRK_TIMER9 = 24, /**< Timer 1 break, Timer 9. */ // FIXME rm
		//NVIC_TIMER1_UP_TIMER16 = 25, // FIXME hack
    NVIC_TIMER1_UP_TIMER10  = 25, /**< Timer 1 update, Timer 10. */ //FIXME rm
		//NVIC_TIMER1_TRG_COM_TIMER17 = 26, // FIXME hack
    NVIC_TIMER1_TRG_COM_TIMER11 = 26, /**<
                                       * Timer 1 trigger and commutation,
                                       * Timer 11. */ // FIXME rm
    NVIC_TIMER1_CC        = 27,   /**< Timer 1 capture/compare */
    NVIC_TIMER2           = 28,   /**< Timer 2 */
    NVIC_TIMER3           = 29,   /**< Timer 3 */
    NVIC_TIMER4           = 30,   /**< Timer 4 */
    NVIC_I2C1_EV          = 31,   /**< I2C1 event */
    NVIC_I2C1_ER          = 32,   /**< I2C1 error */
    NVIC_I2C2_EV          = 33,   /**< I2C2 event */
    NVIC_I2C2_ER          = 34,   /**< I2C2 error */
    NVIC_SPI1             = 35,   /**< SPI1 */
    NVIC_SPI2             = 36,   /**< SPI2 */
    NVIC_USART1           = 37,   /**< USART1 */
    NVIC_USART2           = 38,   /**< USART2 */
    NVIC_USART3           = 39,   /**< USART3 */
    NVIC_EXTI_15_10       = 40,   /**< EXTI line [15:10] */
    NVIC_RTC_ALARM        = 41,   /**< RTC alarm through EXTI line */
    NVIC_USB_WKUP         = 42,   /**< USB wakeup from suspend through
                                     EXTI line */
    NVIC_TIMER8_BRK_TIMER12       = 43, /**< Timer 8 break, timer 12  */ //TODO rm TIMER12
    NVIC_TIMER8_UP_TIMER13        = 44, /**< Timer 8 update, timer 13 */ // TODO rm TIMER13
    NVIC_TIMER8_TRG_COM_TIMER14  = 45, /**<
                                       * Timer 8 trigger and commutation,
                                       * Timer 14. */ //TODO rm TIMER14
    NVIC_TIMER8_CC      = 46,   /**< Timer 8 capture/compare */
    NVIC_ADC3           = 47,   /**< ADC3 */

    NVIC_SPI3           = 51,   /**< SPI3 */
    NVIC_UART4          = 52,   /**< UART4 */
    NVIC_UART5          = 53,   /**< UART5 */
    //NVIC_TIMER6_DAC     = 54,   // TODO hack
    NVIC_TIMER6	        = 54,   /**< Timer 6 */ //TODO add DAC
    NVIC_TIMER7         = 55,   /**< Timer 7 */
    NVIC_DMA2_CH1       = 56,   /**< DMA2 channel 1 */
    NVIC_DMA2_CH2       = 57,   /**< DMA2 channel 2 */
    NVIC_DMA2_CH3       = 58,   /**< DMA2 channel 3 */
    NVIC_DMA2_CH4		    = 59,   /**< DMA2 channel 4 */
    NVIC_DMA2_CH5       = 60,   /**< DMA2 channel 5 */

    NVIC_ADC4           = 61,   /**< DMA2 channels 4 and 5 */

    NVIC_COMP123        = 64,   /**< DMA2 channels 4 and 5 */
    NVIC_COMP456        = 65,   /**< DMA2 channels 4 and 5 */
    NVIC_COMP7          = 66,   /**< DMA2 channels 4 and 5 */

    NVIC_USB_HP         = 74,   /**< DMA2 channels 4 and 5 */
    NVIC_USB_LP         = 75,   /**< DMA2 channels 4 and 5 */
    NVIC_USB_WKUP2      = 76,   /**< DMA2 channels 4 and 5 */

    NVIC_FPU            = 81,   /**< DMA2 channels 4 and 5 */
} nvic_irq_num;

/** NVIC register map type. */
typedef struct nvic_reg_map {
    __IO uint32 ISER[8];      /**< Interrupt Set Enable Registers */
    /** Reserved */
    uint32 RESERVED0[24];

    __IO uint32 ICER[8];      /**< Interrupt Clear Enable Registers */
    /** Reserved */
    uint32 RESERVED1[24];

    __IO uint32 ISPR[8];      /**< Interrupt Set Pending Registers */
    /** Reserved */
    uint32 RESERVED2[24];

    __IO uint32 ICPR[8];      /**< Interrupt Clear Pending Registers */
    /** Reserved */
    uint32 RESERVED3[24];

    __IO uint32 IABR[8];      /**< Interrupt Active bit Registers */
    /** Reserved */
    uint32 RESERVED4[56];

    __IO uint8  IP[240];      /**< Interrupt Priority Registers */
    /** Reserved */
    uint32 RESERVED5[644];

    __IO uint32 STIR;         /**< Software Trigger Interrupt Registers */
} nvic_reg_map;

/** NVIC register map base pointer. */
#define NVIC_BASE                       ((struct nvic_reg_map*)0xE000E100)

/*
 * Note: The series header must define enum nvic_irq_num, which gives
 * descriptive names to the interrupts and exceptions from NMI (-14)
 * to the largest interrupt available in the series, where the value
 * for nonnegative enumerators corresponds to its position in the
 * vector table.
 *
 * It also must define a static inline nvic_irq_disable_all(), which
 * writes 0xFFFFFFFF to all ICE registers available in the series. (We
 * place the include here to give the series header access to
 * NVIC_BASE, in order to let it do so).
 */

void nvic_init(uint32 address, uint32 offset);
void nvic_set_vector_table(uint32 address, uint32 offset);
void nvic_irq_set_priority(nvic_irq_num irqn, uint8 priority);
void nvic_sys_reset();

/**
 * Enables interrupts and configurable fault handlers (clear PRIMASK).
 */
static inline void nvic_globalirq_enable() {
    asm volatile("cpsie i");
}
/**
 * Re-enable interrupts.
 *
 * Call this after noInterrupts() to re-enable interrupt handling,
 * after you have finished with a timing-critical section of code.
 *
 * @see noInterrupts()
 */
static inline void interrupts() {
    nvic_globalirq_enable();
}


/**
 * Disable interrupts and configurable fault handlers (set PRIMASK).
 */
static inline void nvic_globalirq_disable() {
    asm volatile("cpsid i");
}
/**
 * Disable interrupts.
 *
 * After calling this function, all user-programmable interrupts will
 * be disabled.  You can call this function before a timing-critical
 * section of code, then call interrupts() to re-enable interrupt
 * handling.
 *
 * @see interrupts()
 */
static inline void noInterrupts() {
    nvic_globalirq_disable();
}


/**
 * @brief Enable interrupt irq_num
 * @param irq_num Interrupt to enable
 */
static inline void nvic_irq_enable(nvic_irq_num irq_num) {
    if (irq_num < 0) {
        return;
    }
    NVIC_BASE->ISER[irq_num / 32] = BIT(irq_num % 32);
}

/**
 * @brief Disable interrupt irq_num
 * @param irq_num Interrupt to disable
 */
static inline void nvic_irq_disable(nvic_irq_num irq_num) {
    if (irq_num < 0) {
        return;
    }
    NVIC_BASE->ICER[irq_num / 32] = BIT(irq_num % 32);
}

/**
 * @brief Quickly disable all interrupts.
 *
 * Calling this function is significantly faster than calling
 * nvic_irq_disable() in a loop.
 */
static inline void nvic_irq_disable_all(void) {
    NVIC_BASE->ICER[0] = 0xFFFFFFFF;
    NVIC_BASE->ICER[1] = 0xFFFFFFFF;
    NVIC_BASE->ICER[2] = 0xFFFFFFFF;
}

#ifdef __cplusplus
}
#endif

#endif
