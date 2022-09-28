// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "rgb_bits.h"

void rgb_matrix_led_index_init(void) {
    memset(&led_position, 0, sizeof(led_position));

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            led_to_matrix_pos temp;
            temp.row = MATRIX_ROWS;
            temp.col = MATRIX_COLS;
            if (g_led_config.matrix_co[row][col] < 255) {
                temp.row                                       = row;
                temp.col                                       = col;
                led_position[g_led_config.matrix_co[row][col]] = temp;
            }
        }
    }
}

bool rgb_matrix_led_index_has_pos(uint8_t led_index) {
#ifdef SPLIT_KEYBOARD
    if (is_keyboard_left() && (led_index >= RGB_MATRIX_LED_COUNT / 2)) {
        return false;
    } else if (!is_keyboard_left() && (led_index < RGB_MATRIX_LED_COUNT / 2)) {
        return false;
    }
#endif
    if (led_position[led_index].row < MATRIX_ROWS) {
        return true;
    }
    return false;
}
