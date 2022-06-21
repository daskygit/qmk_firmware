// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_wrapper(KEYS_36(QWERTY)),
    [_COLEMAK]  = LAYOUT_wrapper(KEYS_36(COLEMAK)),
    [_GAMING]   = LAYOUT_wrapper(KEYS_36(GAMING)),
    [_LOWER]    = LAYOUT_wrapper(KEYS_36(LOWER)),
    [_RAISE]    = LAYOUT_wrapper(KEYS_36(RAISE)),
    [_ADJUST]   = LAYOUT_wrapper(KEYS_36(ADJUST))
};
// clang-format on

static const pin_t row_pins[MATRIX_ROWS / 2] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS]     = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS / 2; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    writePinLow(row_pins[current_row]);

    while (readPin(row_pins[current_row]) != 0)
        ;

    uint16_t portb = palReadPort(GPIOB);
    uint16_t porta = palReadPort(GPIOA);
    writePinHigh(row_pins[current_row]);
    matrix_row_t cols;
    // Col      B14, B13, B12, B11,             B3,                     A6
    //              00111100         |        00000010      |        00000001
    cols = ~(((portb & 0x7800) >> 9) | ((portb & 0x8) >> 2) | ((porta & 0x40) >> 6));

    uint32_t temp = cols; // 0000 0000 0000 0000 0000 0000 0011 1111
    __asm__("rbit %0, %1" : "=r"(temp) : "r"(temp)); // 1111 1100 0000 0000 0000 0000 0000 0000 (A6, B3, B11, B12, B13, B14)
    current_matrix[current_row] = temp >> 26; // 0011 1111 (A6, B3, B11, B12, B13, B14)

    if (cols == 0) {
        return;
    }

    for (size_t i = 0; i < MATRIX_COLS; i++) {
        while (readPin(col_pins[i]) != 1)
            ;
    }
}
