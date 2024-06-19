// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gpio.h"
#include "timer.h"
#include "debug.h"
#include "print.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void lpm_start(void) {
    uint32_t timer_before_lpm = timer_read32();

    DBGMCU->CR &= ~0xFFFFC0D8; // disable all debug during stop
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // keep DBP bit
    PWR->CR0 &= PWR_CR0_DBP;

    // // SP1
    // PWR->CR0 |= 0x900;
    // PWR->CFGR = 0x3F;

    // SP2
    // PWR->CR0 |= 0x22002;
    // PWR->CFGR = 0x3BE;

    // // SP3 -  this turns off 32k sram
    // PWR->CR0 |= 0x63004;
    // PWR->CFGR = 0x3BF;

    // // SP4 -  this turns off 32k sram
    // PWR->CR0 |= 0x7B004;
    // PWR->CFGR = 0x3B3;

    PWR->CR0 |= 0x3B004;
    PWR->CFGR = 0x3B3;

    // Set up row/col pins and attach callback
    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        gpio_set_pin_output(col_pins[i]);
        gpio_write_pin_low(col_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
        gpio_set_pin_input_high(row_pins[i]);
        palEnablePadEvent(PAL_PORT(row_pins[i]), PAL_PAD(row_pins[i]), PAL_EVENT_MODE_BOTH_EDGES);
    }

    // usb_disconnect(); // this causes increased power consumption during lpm

    //  Wait for an interrupt
    __WFI();
    //__NVIC_SystemReset();

    chSysLock();
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    if (PWR->SR1 & PWR_SR1_SPF) { // system was stopped
        PWR->CR1 |= PWR_CR1_CSPF;
        if (PWR->SR1 & PWR_SR1_CKF) { // clocks were reset
            PWR->CR1 |= PWR_CR1_CCKF;
            wb32_clock_init();
            rccEnableSPIM2();
            rccEnableQSPI();
            rccEnableUART3();
            rccEnableAPB1(RCC_APB1ENR_GPIOAEN);
            rccEnableAPB1(RCC_APB1ENR_GPIOBEN);
            rccEnableAPB1(RCC_APB1ENR_GPIOCEN);
            rccEnableAPB1(RCC_APB1ENR_GPIODEN);
            stInit();
            timer_reset(timer_before_lpm);
        }
    }

    void init_usb_driver(USBDriver * usbp);
    init_usb_driver(&USBD1);
    chSysUnlock();

    void last_matrix_activity_trigger(void);
    last_matrix_activity_trigger();

    // Now that the interrupt has woken us up, reset all the row / col pins back to defaults
    for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
        palDisablePadEvent(PAL_PORT(row_pins[i]), PAL_PAD(row_pins[i]));
        gpio_write_pin_high(row_pins[i]);
        gpio_set_pin_input_high(row_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        gpio_write_pin_high(col_pins[i]);
        gpio_set_pin_input_high(col_pins[i]);
    }
}
