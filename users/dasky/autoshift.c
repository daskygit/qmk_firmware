// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "autoshift.h"

#ifdef CUSTOM_TAP_CODE_ENABLE
#    include "tap_codes.h"
#endif
#if defined(RGB_MATRIX_ENABLE) || defined (RGBLIGHT_ENABLE)
#    include "rgb_indicators.h"
#endif

uint16_t autoshift_array[MATRIX_ROWS][MATRIX_COLS] = {0};
#define AS_ARRAY autoshift_array[record->event.key.row][record->event.key.col]

bool process_record_autoshift(uint16_t keycode, keyrecord_t* record) {
    if (get_highest_layer(layer_state) == _LOWER) {
        switch (keycode) {
            case KC_MINS:
            case KC_EQL:
            case KC_NUHS:
            case KC_LBRC:
            case KC_RBRC:
            case KC_GRV:
            case KC_F1 ... KC_F12:
            case KC_1 ... KC_0:
                if (record->event.pressed) {
                    if (AS_ARRAY == 0) {
                        AS_ARRAY = timer_read();
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
                        if (!user_state.blinking) {
                            rgb_blink_timer = AS_ARRAY;
                        }
#endif
                    }
                } else {
                    if (AS_ARRAY == 0) {
                        return false;  // must have been processed already
                    } else {
                        AS_ARRAY = 0;
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
                        rgb_blink_timer = 0;
#endif
                        tap_code(keycode);
                    }
                }
                return false;
        }
    }
    return true;
}

#ifndef AS_PROCESS_LIMIT
#    define AS_PROCESS_LIMIT 1
#endif

void process_pressed_autoshifts(void) {
    static matrix_row_t r     = 0;
    static matrix_row_t c     = 0;
    uint16_t            count = 0;

    do {
        if (autoshift_array[r][c] == 0) {
            // ignore
        } else if (timer_elapsed(autoshift_array[r][c]) > AUTO_SHIFT_TIMEOUT) {
            keypos_t as_key = {.col = c, .row = r};
            tap_code16(S(keymap_key_to_keycode(_LOWER, as_key)));
            autoshift_array[r][c] = 0;
        }
        r++;
        if (r == MATRIX_ROWS) {
            r = 0;
            c++;
            if (c == MATRIX_COLS) {
                c = 0;
            }
        }
        count++;
    } while (count < AS_PROCESS_LIMIT);
}
