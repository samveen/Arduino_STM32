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
 * @file libmaple/stm32f3/include/series/syscfg.h
 * @author F3-port by Hanspeter Portner <dev@open-music-kontrollers.ch>
 * @brief System configuration controller (SYSCFG)
 */

#ifndef _LIBMAPLE_STM32F3_SYSCFG_H_
#define _LIBMAPLE_STM32F3_SYSCFG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libmaple/libmaple_types.h>

/*
 * Register map and base pointer
 */

/**
 * @brief SYSCFG register map type.
 */
typedef struct syscfg_reg_map {
    __IO uint32 CFGR1;    		/**< Configuration register 1*/
    __IO uint32 RCR;    			/**< CCM SRAM protection register */
    __IO uint32 EXTICR[4];    /**< External Interrupt configuration register */
    __IO uint32 CFGR2;    		/**< Configuration register 2 */
} syscfg_reg_map;

/** SYSCFG register map base pointer */
#define SYSCFG_BASE                     ((struct syscfg_reg_map*)0x40010000)

/*
 * Register bit definitions
 */

/* Configuration register 1 */

#define SYSCFG_CFGR1_FPU_IE_SHIFT						26
#define SYSCFG_CFGR1_ENCODE_MODE_SHIFT			22
#define SYSCFG_CFGR1_I2C2_FM_PLUS_BIT				21
#define SYSCFG_CFGR1_I2C1_FM_PLUS_BIT				20
#define SYSCFG_CFGR1_I2C_PB9_FM_PLUS_BIT		19
#define SYSCFG_CFGR1_I2C_PB8_FM_PLUS_BIT		18
#define SYSCFG_CFGR1_I2C_PB7_FM_PLUS_BIT		17
#define SYSCFG_CFGR1_I2C_PB6_FM_PLUS_BIT		16
#define SYSCFG_CFGR1_TIM7_DAC2_DMA_RMP_BIT	14
#define SYSCFG_CFGR1_TIM6_DAC1_DMA_RMP_BIT	13
#define SYSCFG_CFGR1_TIM17_DMA_RMP_BIT			12
#define SYSCFG_CFGR1_TIM16_DMA_RMP_BIT			11
#define SYSCFG_CFGR1_ADC24_DMA_RMP_BIT			8
#define SYSCFG_CFGR1_DAC_TRIG_RMP_BIT				7
#define SYSCFG_CFGR1_TIM1_ITR3_RMP_BIT			6
#define SYSCFG_CFGR1_USB_IT_RMP_BIT					5

//FIXME FPU_IE
//FIXME ENCODE_MODE
#define SYSCFG_CFGR1_I2C2_FM_PLUS					(1U << SYSCFG_CFGR1_I2C2_FM_PLUS_BIT)
#define SYSCFG_CFGR1_I2C1_FM_PLUS					(1U << SYSCFG_CFGR1_I2C1_FM_PLUS_BIT)
#define SYSCFG_CFGR1_I2C1_PB9_FM_PLUS			(1U << SYSCFG_CFGR1_I2C1_PB9_FM_PLUS_BIT)
#define SYSCFG_CFGR1_I2C1_PB8_FM_PLUS			(1U << SYSCFG_CFGR1_I2C1_PB8_FM_PLUS_BIT)
#define SYSCFG_CFGR1_I2C1_PB7_FM_PLUS			(1U << SYSCFG_CFGR1_I2C1_PB7_FM_PLUS_BIT)
#define SYSCFG_CFGR1_I2C1_PB6_FM_PLUS			(1U << SYSCFG_CFGR1_I2C1_PB6_FM_PLUS_BIT)
#define SYSCFG_CFGR1_TIM7_DAC2_DMA_RMP		(1U << SYSCFG_CFGR1_TIM7_DAC2_DMA_RMP_BIT)
#define SYSCFG_CFGR1_TIM6_DAC1_DMA_RMP		(1U << SYSCFG_CFGR1_TIM6_DAC1_DMA_RMP_BIT)
#define SYSCFG_CFGR1_TIM17_DMA_RMP				(1U << SYSCFG_CFGR1_TIM17_DMA_RMP_BIT)
#define SYSCFG_CFGR1_TIM16_DMA_RMP				(1U << SYSCFG_CFGR1_TIM16_DMA_RMP_BIT)
#define SYSCFG_CFGR1_ADC23_DMA_RMP				(1U << SYSCFG_CFGR1_ADC23_DMA_RMP_BIT)
#define SYSCFG_CFGR1_DAC_TRIG_RMP					(1U << SYSCFG_CFGR1_DAC_TRIG_RMP_BIT)
#define SYSCFG_CFGR1_TIM1_ITR3_RMP				(1U << SYSCFG_CFGR1_TIM1_ITR3_RMP_BIT)
#define SYSCFG_CFGR1_USB_IT_RMP						(1U << SYSCFG_CFGR1_USB_IT_RMP_BIT)
#define SYSCFG_CFGR1_MEM_MODE							0X3

/* CCM SRAM protection register */

#define SYSCFG_RCR_PAGE7_WP_BIT		7
#define SYSCFG_RCR_PAGE6_WP_BIT		6
#define SYSCFG_RCR_PAGE5_WP_BIT		5
#define SYSCFG_RCR_PAGE4_WP_BIT		4
#define SYSCFG_RCR_PAGE3_WP_BIT		3
#define SYSCFG_RCR_PAGE2_WP_BIT		2
#define SYSCFG_RCR_PAGE1_WP_BIT		1
#define SYSCFG_RCR_PAGE0_WP_BIT		0

#define SYSCFG_RCR_PAGE_7					(1U << SYSCFG_RCR_PAGE7_WP_BIT)
#define SYSCFG_RCR_PAGE_6					(1U << SYSCFG_RCR_PAGE6_WP_BIT)
#define SYSCFG_RCR_PAGE_5					(1U << SYSCFG_RCR_PAGE5_WP_BIT)
#define SYSCFG_RCR_PAGE_4					(1U << SYSCFG_RCR_PAGE4_WP_BIT)
#define SYSCFG_RCR_PAGE_3					(1U << SYSCFG_RCR_PAGE3_WP_BIT)
#define SYSCFG_RCR_PAGE_2					(1U << SYSCFG_RCR_PAGE2_WP_BIT)
#define SYSCFG_RCR_PAGE_1					(1U << SYSCFG_RCR_PAGE1_WP_BIT)
#define SYSCFG_RCR_PAGE_0					(1U << SYSCFG_RCR_PAGE0_WP_BIT)

/* Configuration register 2 */

#define SYSCFG_CFGR2_SRAM_PEF_BIT					8
#define SYSCFG_CFGR2_BYP_ADDR_PAR_BIT			4
#define SYSCFG_CFGR2_PVD_LOCK_BIT					2
#define SYSCFG_CFGR2_SRAM_PARITY_LOCK_BIT	1
#define SYSCFG_CFGR2_LOCKUP_LOCK_BIT			0

#define SYSCFG_CFGR2_SRAM_PEF							(1U << SYSCFG_CFGR2_SRAM_PEF_BIT)
#define SYSCFG_CFGR2_BYP_ADDR_PAR					(1U << SYSCFG_CFGR2_BYP_ADDR_PAR_BIT)
#define SYSCFG_CFGR2_PVD_LOCK							(1U << SYSCFG_CFGR2_PVD_LOCK_BIT)
#define SYSCFG_CFGR2_SRAM_PARITY_LOCK			(1U << SYSCFG_CFGR2_SRAM_PARITY_LOCK_BIT)
#define SYSCFG_CFGR2_LOCKUP_LOCK					(1U << SYSCFG_CFGR2_LOCKUP_LOCK_BIT)


#include <libmaple/rcc.h>

/* External interrupt configuration register 1 */

#define SYSCFG_EXTICR1_EXTI0            0xF
#define SYSCFG_EXTICR1_EXTI1            0xF0
#define SYSCFG_EXTICR1_EXTI2            0xF00
#define SYSCFG_EXTICR1_EXTI3            0xF000

/* External interrupt configuration register 2 */

#define SYSCFG_EXTICR2_EXTI4            0xF
#define SYSCFG_EXTICR2_EXTI5            0xF0
#define SYSCFG_EXTICR2_EXTI6            0xF00
#define SYSCFG_EXTICR2_EXTI7            0xF000

/* External interrupt configuration register 3 */

#define SYSCFG_EXTICR3_EXTI8            0xF
#define SYSCFG_EXTICR3_EXTI9            0xF0
#define SYSCFG_EXTICR3_EXTI10           0xF00
#define SYSCFG_EXTICR3_EXTI11           0xF000

/* External interrupt configuration register 4 */

#define SYSCFG_EXTICR4_EXTI12           0xF
#define SYSCFG_EXTICR4_EXTI13           0xF0
#define SYSCFG_EXTICR4_EXTI14           0xF00
#define SYSCFG_EXTICR4_EXTI15           0xF000

/*
 * Routines
 */

/**
 * @brief Initialize the SYSCFG peripheral.
 */
void syscfg_init(void);

/**
 * @brief System memory mode
 * These values specify what memory to map to address 0x00000000.
 * @see syscfg_set_mem_mode
 */
typedef enum syscfg_mem_mode {
    /** Main flash memory is mapped at 0x0. */
    SYSCFG_MEM_MODE_FLASH        = 0x0,
    /** System flash (i.e. ST's baked-in bootloader) is mapped at 0x0. */
    SYSCFG_MEM_MODE_SYSTEM_FLASH = 0x1,
    /** FSMC bank 1 (NOR/PSRAM 1 and 2) is mapped at 0x0. */
    SYSCFG_MEM_MODE_FSMC_BANK_1  = 0x2,
    /** Embedded SRAM (i.e., not backup SRAM) is mapped at 0x0. */
    SYSCFG_MEM_MODE_SRAM         = 0x3,
} syscfg_mem_mode;


/**
 * @brief Set the memory to be mapped at address 0x00000000.
 *
 * This function can be used to override the BOOT pin
 * configuration. Some restrictions apply; see your chip's reference
 * manual for the details.
 *
 * @param mode Mode to set
 * @see syscfg_mem_mode
 */
void syscfg_set_mem_mode(syscfg_mem_mode);



#ifdef __cplusplus
}
#endif

#endif
