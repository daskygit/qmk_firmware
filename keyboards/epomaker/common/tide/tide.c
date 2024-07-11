// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf8003a/rf_driver.h"
#include "lpm/lpm.h"
#include "lib/lib8tion/lib8tion.h"
#include "debug.h"
#include "print.h"
#include "keymap_introspection.h"

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

bool         batt_check        = false;
uint8_t      bt_1_led          = NO_LED;
uint8_t      bt_2_led          = NO_LED;
uint8_t      bt_3_led          = NO_LED;
uint8_t      bt_4_led          = NO_LED;
uint8_t      bt_5_led          = NO_LED;
uint8_t      rf_led            = NO_LED;
fast_timer_t bt_led_start_time = 0;

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

uint8_t bt_led_location_from_profile(rf_profiles_t profile) {
    switch (profile) {
        case rf_profile_dongle:
            return rf_led;
        case rf_profile_bt_1:
            return bt_1_led;
        case rf_profile_bt_2:
            return bt_2_led;
        case rf_profile_bt_3:
            return bt_3_led;
        case rf_profile_bt_4:
            return bt_4_led;
        case rf_profile_bt_5:
            return bt_5_led;
        default:
            return NO_LED;
    }
}

void bt_led_locations_init(void) {
    // uint8_t leds_found = 0;
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        // if (leds_found == 6) {
        //     break;
        // }
        for (uint8_t layer = 0; layer < keymap_layer_count(); layer++) {
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    switch (keycode_at_keymap_location(layer, row, col)) {
                        case RF_BT1:
                            bt_1_led = g_led_config.matrix_co[row][col];
                            break;
                        case RF_BT2:
                            bt_2_led = g_led_config.matrix_co[row][col];
                            break;
                        case RF_BT3:
                            bt_3_led = g_led_config.matrix_co[row][col];
                            break;
                        case RF_BT4:
                            bt_4_led = g_led_config.matrix_co[row][col];
                            break;
                        case RF_BT5:
                            bt_5_led = g_led_config.matrix_co[row][col];
                            break;
                        case RF_DONG:
                            rf_led = g_led_config.matrix_co[row][col];
                            break;
                    }
                }
            }
        }
    }
}

void keyboard_post_init_kb(void) {
    kb_eeconfig.raw = eeconfig_read_kb();
    keyboard_post_init_rf(kb_eeconfig.saved_mode);
    bt_led_locations_init();
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
    __WFI();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    if (keycode == BATT_CHECK) {
        batt_check = record->event.pressed;
    }
    if (record->event.pressed) {
        switch (keycode) {
            case RF_BT1:
            case RF_BT2:
            case RF_BT3:
            case RF_BT4:
            case RF_BT5:
            case RF_DONG:
            case RF_WIRE:
            case RF_PR_1:
            case RF_PR_2:
            case RF_PR_3:
            case RF_PR_4:
            case RF_PR_5:
            case RF_PR_D:
                bt_led_start_time = timer_read_fast();
                break;
        }
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

    uint8_t bt_led = bt_led_location_from_profile(get_current_profile());

    if ((get_current_profile() != rf_profile_wired && bt_led != NO_LED)) {
        static fast_timer_t led_timer = 0;
        static bool         led_on    = false;

        if (is_pairing()) {
            if (timer_elapsed_fast(led_timer) > 250) {
                led_timer = timer_read_fast();
                led_on    = !led_on;
            }
            rgb_matrix_set_color(bt_led, 0, 0, led_on ? 255 : 0);

        } else if (!is_connected()) {
            if (timer_elapsed_fast(led_timer) > 700) {
                led_timer = timer_read_fast();
                led_on    = !led_on;
            }
            rgb_matrix_set_color(bt_led, 0, 0, led_on ? 255 : 0);
        } else if (is_connected()) {
            if (timer_elapsed_fast(bt_led_start_time) < 3100) {
                if (timer_elapsed_fast(led_timer) > 700) {
                    led_timer = timer_read_fast();
                    led_on    = !led_on;
                }
                rgb_matrix_set_color(bt_led, 0, 0, led_on ? 255 : 0);
            }
        }
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

void rf_status_update_kb(uint8_t status) {}

#ifdef VIA_ENABLE
#    include "usb_main.h"
#    include "usb_descriptor.h"
void replaced_hid_send(uint8_t *data, uint8_t length) {
    if (length != RAW_EPSIZE) {
        return;
    }

    if (get_current_profile() == rf_profile_wired) {
        send_report(USB_ENDPOINT_IN_RAW, data, length);
    } else if (get_current_profile() == rf_profile_dongle) {
        rf_send_via(data, length);
    }
}
#endif
