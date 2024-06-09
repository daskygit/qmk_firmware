// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf_driver.h"
#include "lib/lib8tion/lib8tion.h"
#include "gpio.h"
#include "debug.h"
#include "print.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(RGB_POWER_PIN);
    gpio_write_pin_high(RGB_POWER_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_rf();
    keyboard_post_init_user();
}

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

    // for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
    //     gpio_set_pin_output(row_pins[i]);
    //     gpio_write_pin_high(row_pins[i]);
    // }
    // for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
    //     gpio_set_pin_input_low(col_pins[i]);
    //     palEnablePadEvent(PAL_PORT(col_pins[i]), PAL_PAD(col_pins[i]), PAL_EVENT_MODE_BOTH_EDGES);
    // }

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

    matrix_scan();
}

void protocol_keyboard_task(void) {
    rf_task();
    static bool idle = false;
    if (last_input_activity_elapsed() > DEEP_SLEEP_TIME_MS) {
        lpm_start();
        rf_task();
    }
    if (last_input_activity_elapsed() > RGB_SLEEP_TIME_MS) {
        if (!idle) {
            idle = true;
            gpio_write_pin_low(RGB_POWER_PIN);
            rgb_matrix_disable_noeeprom();
        }
    } else if (idle) {
        idle = false;
        gpio_write_pin_high(RGB_POWER_PIN);
        rgb_matrix_enable_noeeprom();
    }
    keyboard_task();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    return process_record_rf(keycode, record);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (is_battery_charging()) {
        uint8_t red   = 99 - scale8(255, get_battery_level());
        uint8_t green = scale8(255, get_battery_level());

        rgb_matrix_set_color(57, red, green, 0);
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(8, 255, 255, 255);
    }

    return true;
}
