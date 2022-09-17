// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"
#include "string.h"

const pin_t matrix_read_pins[] = {B3, B4, B5, B6, B7, B8};
const pin_t matrix_out_pins[]  = {B12, B13, B14, B15, A8};

#define PORTB_BITMASK (1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8)

void matrix_all_pins_high(void) {
    for (uint8_t i = 0; i < 5; i++) {
        setPinInputHigh(matrix_out_pins[i]);
    }
    for (uint8_t i = 0; i < 6; i++) {
        setPinInputHigh(matrix_read_pins[i]);
    }
}

void matrix_all_pins_low(void) {
    for (uint8_t i = 0; i < 5; i++) {
        setPinInputLow(matrix_out_pins[i]);
    }
    for (uint8_t i = 0; i < 6; i++) {
        setPinInputLow(matrix_read_pins[i]);
    }
}

void matrix_init_custom(void) {
    matrix_all_pins_high();
}

void matrix_scan_high(matrix_row_t current_matrix[], matrix_row_t temp_matrix[]) {
    for (uint8_t current_row = 0; current_row < 5; current_row++) {
        pin_t output_pin = matrix_out_pins[current_row];
        setPinOutput(output_pin);
        writePinLow(output_pin);
        while (readPin(matrix_out_pins[current_row]) != 0)
            ;
        uint16_t port_b = palReadPort(GPIOB);
        setPinInputHigh(output_pin);
        temp_matrix[current_row] = ~((port_b & PORTB_BITMASK) >> 3);
    }
}

void matrix_scan_low(matrix_row_t current_matrix[], matrix_row_t temp_matrix[]) {
    for (uint8_t current_row = 0; current_row < 5; current_row++) {
        pin_t output_pin = matrix_out_pins[current_row];
        setPinOutput(output_pin);
        writePinHigh(output_pin);
        while (readPin(matrix_out_pins[current_row]) != 1)
            ;
        uint16_t port_b = palReadPort(GPIOB);
        setPinInputLow(output_pin);
        temp_matrix[current_row + 5] = ((port_b & PORTB_BITMASK) >> 3);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool                matrix_has_changed           = false;
    static matrix_row_t temp_matrix[MATRIX_ROWS]     = {0};
    static enum { UNKNOWN, LOW, HIGH } next_scan_dir = UNKNOWN;

    switch (next_scan_dir) {
        case UNKNOWN:
            matrix_all_pins_high();
        case HIGH:
            matrix_scan_high(current_matrix, temp_matrix);
            matrix_all_pins_low();
            matrix_scan_low(current_matrix, temp_matrix);
            next_scan_dir = LOW;
            break;
        case LOW:
            matrix_scan_low(current_matrix, temp_matrix);
            matrix_all_pins_high();
            matrix_scan_high(current_matrix, temp_matrix);
            next_scan_dir = HIGH;
            break;
    }

    if (memcmp(temp_matrix, current_matrix, sizeof(temp_matrix))) {
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
        matrix_has_changed = true;
    }

    return matrix_has_changed;
}