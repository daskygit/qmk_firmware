// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf8003a/rf_driver.h"
#include "lpm/lpm.h"
#include "lib/lib8tion/lib8tion.h"
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

void protocol_keyboard_task(void) {
    rf_task();
    static bool idle = false;
    if (!is_rf_on()) {
        lpm_start();
        rf_task();
        matrix_scan();
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

        rgb_matrix_set_color(2, red, green, 0);
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(54, 255, 255, 255);
    }

    return true;
}

void rf_status_update_kb(uint8_t status) {
    if (status != 0x23) {
        if (is_pairing()) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_BREATHING);
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
        } else if (!is_connected()) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
        } else if (is_connected()) {
            rgb_matrix_reload_from_eeprom();
        }
    }
}
