/* Copyright 2020 Dasky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum {
    _BASE,
};

enum {
    CT_FLSH
};

void dance_flsh_each(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            led_left_on();
            break;
        case 2:
            led_left_off();
            led_right_on();
            break;
        case 3:
            led_left_on();
            wait_ms(50);
            led_right_on();
    }
}

// On the fourth tap, set the keyboard on flash state
void dance_flsh_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count >= 4) {
        reset_keyboard();
    }
}

// If the flash state didn't happen, then turn off LEDs, left to right
void dance_flsh_reset(qk_tap_dance_state_t *state, void *user_data) {
    led_left_off();
    wait_ms(50);
    led_right_off();
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_FLSH] = ACTION_TAP_DANCE_FN_ADVANCED(dance_flsh_each, dance_flsh_finished, dance_flsh_reset)
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
            KC_MPLY, 
        KC_Q,   KC_E,
            TD(CT_FLSH)
    )
};
// clang-format on