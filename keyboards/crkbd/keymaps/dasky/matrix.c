/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "split_util.h"
#include "config.h"
#include "transactions.h"
#include "quantum.h"
#include <string.h>

#if defined(BUSY_WAIT_INSTRUCTIONS)
void matrix_output_unselect_delay(void) {
    for (int32_t i = 0; i < BUSY_WAIT_INSTRUCTIONS; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
#endif

#define ERROR_DISCONNECT_COUNT 5

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#ifdef DIRECT_PINS
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
static pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

// row offsets for each hand
uint8_t thisHand, thatHand;

// user-defined overridable functions
__attribute__((weak)) void matrix_slave_scan_kb(void) { matrix_slave_scan_user(); }
__attribute__((weak)) void matrix_slave_scan_user(void) {}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

void matrix_init(void) {
    split_pre_init();

    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
    thatHand = ROWS_PER_HAND - thisHand;

    // initialize key pins
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(ROWS_PER_HAND);

    matrix_init_quantum();

    split_post_init();
}

bool matrix_post_scan(void) {
    bool changed = false;
    if (is_keyboard_master()) {
        static uint8_t error_count;

        matrix_row_t slave_matrix[ROWS_PER_HAND] = {0};
        if (!transport_master(matrix + thisHand, slave_matrix)) {
            error_count++;

            if (error_count > ERROR_DISCONNECT_COUNT) {
                // reset other half if disconnected
                for (int i = 0; i < ROWS_PER_HAND; ++i) {
                    matrix[thatHand + i] = 0;
                    slave_matrix[i]      = 0;
                }

                changed = true;
            }
        } else {
            error_count = 0;

            for (int i = 0; i < ROWS_PER_HAND; ++i) {
                if (matrix[thatHand + i] != slave_matrix[i]) {
                    matrix[thatHand + i] = slave_matrix[i];
                    changed              = true;
                }
            }
        }

        matrix_scan_quantum();
    } else {
        transport_slave(matrix + thatHand, matrix + thisHand);

        matrix_slave_scan_kb();
    }

    return changed;
}

uint8_t matrix_scan(void) {
    bool         local_changed = false;
    matrix_row_t current_matrix[ROWS_PER_HAND];

    for (size_t row_idx = 0; row_idx < ROWS_PER_HAND; row_idx++) {
        writePinLow(row_pins[row_idx]);
        // matrix_output_select_delay();
        while (readPin(row_pins[row_idx]) != 0)
            ;

        uint16_t portb = palReadPort(GPIOB);
        uint16_t porta = palReadPort(GPIOA);
        writePinHigh(row_pins[row_idx]);
        matrix_row_t cols;

        cols = ~(((portb & 0x7800) >> 9) | ((portb & 0x8) >> 2) | ((porta & 0x40) >> 6));

        uint32_t temp = cols;
        __asm__("rbit %0, %1" : "=r"(temp) : "r"(temp));
        current_matrix[row_idx] = temp >> 26;

        // /* Wait until col pins are high again. */
        // size_t counter = 0xFF;
        // while (((palReadGroup(GPIOB, 0x7808, 0) != 0x7808) || (palReadGroup(GPIOA, 0x40, 0) != 0x40)) && counter != 0) {
        //     counter--;
        // }

        for (size_t i = 0; i < MATRIX_COLS; i++) {
            while (readPin(col_pins[i]) != 1)
                ;
        }

        // matrix_output_unselect_delay();
    }

    if (memcmp(raw_matrix, current_matrix, sizeof(current_matrix)) != 0) {
        memcpy(raw_matrix, current_matrix, sizeof(current_matrix));
        local_changed = true;
    }

    debounce(raw_matrix, matrix + thisHand, ROWS_PER_HAND, local_changed);

    bool remote_changed = matrix_post_scan();
    return (uint8_t)(local_changed || remote_changed);
}
