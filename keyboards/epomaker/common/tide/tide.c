// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf8003a/rf_driver.h"
#include "lpm/lpm.h"
#include "lib/lib8tion/lib8tion.h"
#include "debug.h"
#include "print.h"

bool batt_check = false;

enum {
    BATT_CHECK = RF_SAFE,
} kb_keycodes;

typedef union {
    uint32_t raw;
    struct {
        rf_profiles_t saved_mode : 3;
    };
} kb_eeconfig_t;

kb_eeconfig_t kb_eeconfig;

void eeconfig_init_kb(void) {
    kb_eeconfig.raw        = 0;
    kb_eeconfig.saved_mode = rf_profile_dongle;
    eeconfig_update_kb(kb_eeconfig.raw);
}

void rf_profile_update_kb(rf_profiles_t profile) {
    if (profile != kb_eeconfig.saved_mode) {
        kb_eeconfig.saved_mode = profile;
        eeconfig_update_kb(kb_eeconfig.raw);
    }
};

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(RGB_POWER_PIN);
    gpio_write_pin_high(RGB_POWER_PIN);

    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    kb_eeconfig.raw = eeconfig_read_kb();
    keyboard_post_init_rf(kb_eeconfig.saved_mode);
    keyboard_post_init_user();
}

void protocol_keyboard_task(void) {
    rf_task();
    static bool idle = false;
    if (!is_rf_on()) {
        lpm_start();
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
    if (keycode == BATT_CHECK) {
        batt_check = record->event.pressed;
    }
    return process_record_rf(keycode, record);
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (is_battery_charging()) {
        uint8_t red   = (float)(100 - get_battery_level()) * 255 / 100;
        uint8_t green = (float)get_battery_level() * 255 / 100;
        rgb_matrix_set_color(FN_LED, red, green, 0);
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LOCK_LED, 255, 255, 255);
    }
    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (batt_check) {
        uint8_t led_cutoff_x = (float)get_battery_level() * 224 / 100;
        uprintf("CUTOFF: %d", led_cutoff_x);
        RGB led_colour = hsv_to_rgb((HSV){130, 255, rgb_matrix_get_val()});
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.point[i].x <= led_cutoff_x) {
                rgb_matrix_set_color(i, led_colour.r, led_colour.g, led_colour.b);
            } else {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
        return false;
    }
    return true;
}

void rf_status_update_kb(uint8_t status) {
    if (status != 0x23 && get_current_profile() != rf_profile_wired) {
        if (is_pairing() & !is_connected()) {
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
