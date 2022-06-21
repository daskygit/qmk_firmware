// Copyright 2021-2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "wrappers.h"
#include "tap_dances.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_bits.h"
#endif
#include "rgb_indicators.h"
#ifdef USBPD_ENABLE
#    include "usbpd_bits.h"
#else
#    define rgb_matrix_hsv_to_rgb hsv_to_rgb
#endif

#ifndef BLINK_DURATION
#    define BLINK_DURATION 150
#endif

uint16_t rgb_blink_timer = 0;

void rgb_check_blinking(uint8_t led_start, uint8_t led_end) {
    if (is_keyboard_master()) {
        if (rgb_blink_timer > 0) {
            if (timer_elapsed(rgb_blink_timer) > AUTO_SHIFT_TIMEOUT) {
                user_state.blinking = true;
                for (uint8_t i = led_start; i < led_end + 1; i++) {
#ifdef RGB_MATRIX_ENABLE
                    rgb_matrix_set_color(i, 0, 0, 0);
#endif
#ifdef RGBLIGHT_ENABLE
                    rgblight_setrgb_at(0, 0, 0, i);
#endif
                }
                if (timer_elapsed(rgb_blink_timer) - AUTO_SHIFT_TIMEOUT > BLINK_DURATION) {
                    rgb_blink_timer     = 0;
                    user_state.blinking = false;
                }
            }
        }
    } else {
        if (user_state.blinking) {
            for (uint8_t i = led_start; i < led_end + 1; i++) {
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_set_color(i, 0, 0, 0);
#endif
#ifdef RGBLIGHT_ENABLE
                rgblight_setrgb_at(0, 0, 0, i);
#endif
            }
        }
    }
}

#ifdef RGB_MATRIX_ENABLE
void rgb_show_layer(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _COLEMAK:
            return;
        default:
            break;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        if (rgb_matrix_led_index_has_pos(i)) {
            uint16_t kc  = keycode_at_keymap_location(get_highest_layer(layer_state), led_position[i].row, led_position[i].col);
            uint8_t  hue = 0;
            uint8_t  val = rgb_matrix_get_val();
            switch (get_highest_layer(layer_state)) {
                case _GAMING:
                    switch (kc) {
                        case KC_W:
                        case KC_A:
                        case KC_S:
                        case KC_D:
#    ifdef TAP_DANCE_ENABLE
                        case (QK_TAP_DANCE | ((TD_GAME)&0xFF)):
#    endif
                            continue;
                        default:
                            val = 0;
                            break;
                    }
                    break;
                default:
                    switch (kc) {
                        case KC_1 ... KC_0:
                            hue = ((kc - KC_1) * 28) % 255;
                            break;
                        case KC_F1 ... KC_F12:
                            hue = 0;
                            break;
                        case KC_RIGHT ... KC_UP:
                            hue = 201;
                            break;
                        case KC_MS_UP ... KC_MS_RIGHT:
                        case KC_MS_BTN1 ... KC_MS_BTN8:
                            hue = 148;
                            break;
                        case KC_MS_ACCEL0 ... KC_MS_ACCEL2:
                            hue = 169;
                            break;
                        case EH_LEFT:
                            hue = 169;
                            break;
                        case EH_RGHT:
                            hue = 0;
                            break;
                        case RGB_TOG ... RGB_SPD:
                            continue;
                        case WINR:
                            hue = 180;
                            break;
                        case CUS_VER:
                            hue = 222;
                            break;
                        case CUS_GEN:
                            hue = 148;
                            break;
                        case CUS_BLD:
                            hue = 64;
                            break;
                        case CUS_FLH:
                            hue = 21;
                            break;
                        case CUS_TST:
                            hue = 180;
                            break;
                        case KC_MPLY:
                            hue = 85;
                            break;
                        case KC_MNXT:
                            hue = 43;
                            break;
                        case CTALDEL:
                            hue = 201;
                            break;
                        case KC_PSCR:
                            hue = 180;
                            break;
                        case QK_BOOT:
                            hue = 64;
                            break;
                        case EEPROM_RESET:
                            hue = 0;
                            break;
                        case MAGIC_TOGGLE_NKRO:
                            hue = 222;
                            break;
                        default:
                            val = 0;
                            break;
                    }
                    break;
            }
            HSV hsv = {.h = hue, .s = 255, .v = val};
            RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
            rgb_matrix_set_color(g_led_config.matrix_co[led_position[i].row][led_position[i].col], rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_show_layer(led_min, led_max);
    rgb_check_blinking(led_min, led_max);
    return true;
}
#endif
