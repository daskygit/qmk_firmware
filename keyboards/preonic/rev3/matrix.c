#include "quantum.h"
#include <hal.h>
#include <string.h>

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_custom(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinOutput(col_pins[i]);
        writePinLow(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinInputLow(row_pins[i]);
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t raw_matrix[MATRIX_ROWS];

    for (size_t col_idx = 0; col_idx < MATRIX_COLS; col_idx++) {
        ATOMIC_BLOCK_FORCEON { writePinHigh(col_pins[col_idx]); }
        matrix_output_select_delay();

        for (size_t row_idx = 0; row_idx < MATRIX_ROWS; row_idx++) {
            raw_matrix[row_idx] |= readPin(row_pins[row_idx]) ? (MATRIX_ROW_SHIFTER << col_idx) : 0;
        }

        ATOMIC_BLOCK_FORCEON { writePinLow(col_pins[col_idx]); }
        matrix_output_unselect_delay();

        if (memcmp(current_matrix, raw_matrix, sizeof(raw_matrix)) != 0) {
            memcpy(current_matrix, raw_matrix, sizeof(raw_matrix));
            return true;
        }
    }
    return false;
}
