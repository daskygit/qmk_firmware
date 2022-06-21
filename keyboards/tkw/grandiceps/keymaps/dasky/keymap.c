// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "drivers/sensors/pimoroni_trackball.h"
#include "report.h"
#include "transactions.h"
#include "timer.h"
#include <string.h>

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_wrapper(GRANDICEPS(QWERTY)),
    [_COLEMAK]  = LAYOUT_wrapper(GRANDICEPS(COLEMAK)),
    [_GAMING]   = LAYOUT_wrapper(GRANDICEPS(GAMING)),
    [_LOWER]    = LAYOUT_wrapper(GRANDICEPS(LOWER)),
    [_RAISE]    = LAYOUT_wrapper(GRANDICEPS(RAISE)),
    [_ADJUST]   = LAYOUT_wrapper(GRANDICEPS(ADJUST))
};
// clang-format on

bool usb_vbus_state(void) {
    setPinInputLow(USB_VBUS_PIN);
    wait_us(5);
    return readPin(USB_VBUS_PIN);
}

static const pin_t col_pins[MATRIX_COLS]     = MATRIX_COL_PINS;
static const pin_t row_pins[MATRIX_ROWS / 2] = MATRIX_ROW_PINS;

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

    // Col      B0,                     A7,                         A3,                         A5,                     A4,                 A2
    matrix_row_t cols = ~((portb & 1) | ((porta & (1 << 7)) >> 6) | ((porta & (1 << 3)) >> 1) | ((porta & (1 << 5)) >> 2) | (porta & (1 << 4)) | ((porta & (1 << 2)) << 3));

    current_matrix[current_row] = cols;

    if (cols == 0) {
        return;
    }

    for (size_t i = 0; i < MATRIX_COLS; i++) {
        while (readPin(col_pins[i]) != 1)
            ;
    }
}

