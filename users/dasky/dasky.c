// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "autoshift.h"
#include "version.h"

#ifdef SPLIT_KEYBOARD
#    include "transactions.h"
#    include "user_sync.h"
#endif
#ifdef USBPD_ENABLE
#    include "usbpd_bits.h"
#endif
#ifdef CUSTOM_TAP_CODE_ENABLE
#    include "tap_codes.h"
#else
#    define tap_string send_string_P
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_bits.h"
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_is(_GAMING)) {
        combo_disable();
    } else {
        combo_enable();
    }
    return state;
}

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse    = true;

#ifdef SPLIT_KEYBOARD
    // Register keyboard state sync split transaction
    transaction_register_rpc(USER_SYNC_ID, user_sync_aux_handler);
#endif
    // Reset the initial shared data value between master and slave
    memset(&user_state, 0, sizeof(user_state));
#ifdef USBPD_ENABLE
    usbpd_allowance();
#endif
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_master()) {
        user_sync(true); // force initial update
    }
#endif
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_led_index_init();
#endif
#ifdef CUSTOM_TAP_CODE_ENABLE
    tap_code_buffer_init();
#endif
    keyboard_post_init_keymap();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
#ifdef TAP_DANCE_ENABLE
        case TDEVOL:
        case TDERGB:
            return ENCODER_TERM;
#endif
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            return MT_TERM;
        default:
            return TAPPING_TERM;
    }
}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t* record) {return true;}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

        if (!process_record_keymap(keycode, record)) {
        return false;
        }
        
#ifdef CUSTOM_TAP_CODE_ENABLE
    if (!process_record_taps(keycode, record)) {
        return false;
    }
#endif

    if (!process_record_autoshift(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case CUS_VER:
            if (record->event.pressed) {
                tap_string(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP ":" QMK_VERSION ":" QMK_BUILDDATE));
            }
            return false;
        case CUS_BLD:
            if (record->event.pressed) {
                tap_string(PSTR("qmk compile -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n"));
            }
            return false;
        case CUS_GEN:
            if (record->event.pressed) {
                tap_string(PSTR("qmk generate-compilation-database -kb " QMK_KEYBOARD " -km " QMK_KEYMAP "\n"));
            }
            return false;
        case CUS_FLH:
#if defined(BOOTLOADER_RP2040) || defined(BOOTLOADER_TINYUF2)
#    if defined(INIT_EE_HANDS_LEFT)
#        define BL_TARGET " -bl uf2-split-left"
#    elif defined(INIT_EE_HANDS_RIGHT)
#        define BL_TARGET " -bl uf2-split-right"
#    endif
#else
#    if defined(INIT_EE_HANDS_LEFT)
#        define BL_TARGET " -bl dfu-util-split-left"
#    elif defined(INIT_EE_HANDS_RIGHT)
#        define BL_TARGET " -bl dfu-util-split-right"
#    endif
#endif
#if !defined(BL_TARGET)
#    define BL_TARGET ""
#endif
            if (record->event.pressed) {
                tap_string(PSTR("qmk flash -kb " QMK_KEYBOARD " -km " QMK_KEYMAP BL_TARGET "\n"));
            }
            return false;
    }
    return true;
}

void housekeeping_task_throttled(void) {
#ifdef SPLIT_KEYBOARD
    bool force_update = false;
#endif
    if (last_input_activity_elapsed() > 5000) {
#ifdef OLED_ENABLE
        oled_off();
#endif
    } else {
#ifdef OLED_ENABLE
        if (!is_oled_on()) {
            oled_on();
        }
#endif
    }
    if (is_keyboard_master()) {
#ifdef USBPD_ENABLE
        force_update = usbpd_allowance() ? true : force_update;
#endif
#ifdef SPLIT_KEYBOARD
        user_sync(force_update);
#endif
#ifdef PROTOCOL_CHIBIOS
#    if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
        static uint8_t last_val = 0;
        static uint8_t low_val  = 0;
#    endif
        // Go into low-scan interrupt-based mode if we haven't had any matrix activity in the last 5 seconds
        if (last_input_activity_elapsed() > 15000) {
#    ifdef RGB_MATRIX_ENABLE
            if (rgb_matrix_is_enabled() && low_val == 0) {
                last_val                = rgb_matrix_get_val();
                rgb_matrix_config.hsv.v = low_val = (last_val * 0.25);
            }
#    endif
#    ifdef RGBLIGHT_ENABLE
            extern rgblight_config_t rgblight_config;
            if (rgblight_is_enabled() && low_val == 0) {
                last_val = rgblight_get_val();
                low_val  = (last_val * 0.25);
                rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, low_val);
            }
#    endif
        } else {
#    ifdef RGB_MATRIX_ENABLE
            if (rgb_matrix_is_enabled()) {
                if (rgb_matrix_get_val() == low_val) {
                    rgb_matrix_config.hsv.v = last_val;
                    low_val                 = 0;
                }
            }
#    endif
#    ifdef RGBLIGHT_ENABLE
            extern rgblight_config_t rgblight_config;
            if (rgblight_is_enabled()) {
                if (rgblight_get_val() == low_val) {
                    rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, last_val);
                    low_val = 0;
                }
            }
#    endif
        }
#endif
    }
}

void housekeeping_task_user(void) {
    static fast_timer_t throttle_timer = 0;
    if (timer_elapsed_fast(throttle_timer) >= USB_POLLING_INTERVAL_MS) {
        housekeeping_task_throttled();
        throttle_timer = timer_read_fast();
    }
}

void matrix_scan_user(void) {
#ifdef CUSTOM_TAP_CODE_ENABLE
    process_tap_code_buffer();
#endif
    process_pressed_autoshifts();
}