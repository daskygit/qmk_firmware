// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"

void enc_rgb_hue(bool clockwise) {
#ifdef RGB_MATRIX_ENABLE
    clockwise ? rgb_matrix_increase_hue_noeeprom() : rgb_matrix_decrease_hue_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    clockwise ? rgblight_increase_hue_noeeprom() : rgblight_decrease_hue_noeeprom();
#endif
}
void enc_rgb_speed(bool clockwise) {
#ifdef RGB_MATRIX_ENABLE
    clockwise ? rgb_matrix_increase_speed_noeeprom() : rgb_matrix_decrease_speed_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    clockwise ? rgblight_increase_speed_noeeprom() : rgblight_decrease_speed_noeeprom();
#endif
}
void enc_rgb_val(bool clockwise) {
#ifdef RGB_MATRIX_ENABLE
    clockwise ? rgb_matrix_increase_val_noeeprom() : rgb_matrix_decrease_val_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    clockwise ? rgblight_increase_val_noeeprom() : rgblight_decrease_val_noeeprom();
#endif
}
void enc_rgb_sat(bool clockwise) {
#ifdef RGB_MATRIX_ENABLE
    clockwise ? rgb_matrix_increase_sat_noeeprom() : rgb_matrix_decrease_sat_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
    clockwise ? rgblight_increase_sat_noeeprom() : rgblight_decrease_sat_noeeprom();
#endif
}

void rgb_enc_handler(uint8_t mods, bool clockwise) {
    if (mods & MOD_MASK_CTRL) {
        enc_rgb_speed(clockwise);
    } else if (mods & MOD_MASK_SHIFT) {
        enc_rgb_val(clockwise);
    } else if (mods & MOD_MASK_ALT) {
        enc_rgb_sat(clockwise);
    } else {
        enc_rgb_hue(clockwise);
    }
}

void mouse_scroll(bool horizontal, bool clockwise) {
#ifndef MOUSEKEY_ENABLE
    clockwise ? tap_code(KC_PGDOWN) : tap_code(KC_PGUP);
#else
    if (horizontal) {
        clockwise ? tap_code(KC_MS_WH_RIGHT) : tap_code(KC_MS_WH_LEFT);
    } else {
        clockwise ? tap_code(KC_MS_WH_DOWN) : tap_code(KC_MS_WH_UP);
    }
#endif
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        default:
        case 0:
            switch (get_highest_layer(layer_state)) {
                default:
                    tap_code(clockwise ? KC_VOLU : KC_VOLD);
                    break;
                case _RAISE:
                    mouse_scroll(false, clockwise);
                    break;
                case _LOWER:
                case _ADJUST:
                    rgb_enc_handler(get_mods(), clockwise);
                    break;
            }
            break;
        case 1:
            switch (get_highest_layer(layer_state)) {
                default:
                    rgb_enc_handler(get_mods(), clockwise);
                    break;
                case _RAISE:
                    mouse_scroll(true, clockwise);
                    break;
            }
            break;
    }
    return false;
}
