// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf_driver.h"
#include "lib/lib8tion/lib8tion.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(RGB_POWER_PIN);
    gpio_write_pin_high(RGB_POWER_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_rf();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    housekeeping_task_rf();
    static bool idle = false;
    if (last_input_activity_elapsed() > 15000) {
        if (!idle) {
            idle = true;
            gpio_write_pin_low(RGB_POWER_PIN);
            rgb_matrix_disable_noeeprom();
        }
        __WFI();
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
