// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf_driver.h"
#include "lib/lib8tion/lib8tion.h"
#include "gpio.h"

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

void deep_sleep(void) {
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    // keep DBP bit
    PWR->CR0 &= PWR_CR0_DBP;

    // Stop mode - SP2
    PWR->CR0 |= 0x22002;
    PWR->CFGR = 0x3BE;

    // Set up row/col pins and attach callback
    for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
        gpio_set_pin_output(col_pins[i]);
        gpio_write_pin_low(col_pins[i]);
    }
    for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
        gpio_set_pin_input_high(row_pins[i]);
        palEnablePadEvent(PAL_PORT(row_pins[i]), PAL_PAD(row_pins[i]), PAL_EVENT_MODE_BOTH_EDGES);
    }

    // Wait for an interrupt
    __WFI();
    __NVIC_SystemReset();

    // Investigate bring back up without reset

    // Now that the interrupt has woken us up, reset all the row/col pins back to defaults
    // for (int i = 0; i < ARRAY_SIZE(row_pins); ++i) {
    //     palDisablePadEvent(PAL_PORT(row_pins[i]), PAL_PAD(row_pins[i]));
    //     gpio_write_pin_high(row_pins[i]);
    //     gpio_set_pin_input_high(row_pins[i]);
    // }
    // for (int i = 0; i < ARRAY_SIZE(col_pins); ++i) {
    //     gpio_write_pin_high(col_pins[i]);
    //     gpio_set_pin_input_high(col_pins[i]);
    // }
}

void housekeeping_task_kb(void) {
    housekeeping_task_rf();
    static bool idle = false;
    if (last_input_activity_elapsed() > DEEP_SLEEP_TIME_MS) {
        deep_sleep();
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
