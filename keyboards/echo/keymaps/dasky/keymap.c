// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dasky.h"
#include "gpio.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_ortho_4x12_wrapper(KEYS_48(QWERTY)),
    [_COLEMAK]  = LAYOUT_ortho_4x12_wrapper(KEYS_48(COLEMAK)),
    [_GAMING]   = LAYOUT_ortho_4x12_wrapper(KEYS_48(GAMING)),
    [_LOWER]    = LAYOUT_ortho_4x12_wrapper(KEYS_48(LOWER)),
    [_RAISE]    = LAYOUT_ortho_4x12_wrapper(KEYS_48(RAISE)),
    [_ADJUST]   = LAYOUT_ortho_4x12_wrapper(KEYS_48(ADJUST))
};

static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    writePinLow(col_pins[current_col]); // select col

    while (readPin(col_pins[current_col]) != 0)
        ;

    uint16_t porta = palReadPort(GPIOA);

    writePinHigh(col_pins[current_col]);

    matrix_row_t rows = ~(porta);
    uint32_t     temp = rows;
    __asm__("rbit %0, %1" : "=r"(temp) : "r"(temp));
    temp = (temp >> 24);
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        if (temp & (1 << i)) {
            current_matrix[i] |= (1ul << current_col);
        } else {
            current_matrix[i] &= ~(1ul << current_col);
        }
    }

    if (rows == 0) {
        return;
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        while (readPin(row_pins[i]) != 1)
            ;
    }
}
