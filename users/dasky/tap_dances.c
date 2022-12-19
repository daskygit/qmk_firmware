// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "tap_dances.h"

void vol_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            if (!state->pressed || state->interrupted) {
                tap_code_delay(KC_MPLY, 100);
            }
            break;
        case 2:
            tap_code_delay(KC_MNXT, 100);
            break;
        default:
            break;
    }

    if (state->pressed && !state->interrupted) {
        tap_code_delay(KC_MUTE, 100);
    }
}


void rgb_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        default:
        case 1:
            if (!state->pressed || state->interrupted) {
#ifdef RGB_MATRIX_ENABLE
                if (get_mods()) {
                    rgb_matrix_step_noeeprom();
                } else {
                    rgb_matrix_step_reverse_noeeprom();
                }
#endif
#ifdef RGBLIGHT_ENABLE
                if (get_mods()) {
                    rgblight_step_reverse_noeeprom();
                } else {
                    rgblight_step_noeeprom();
                }
#endif
            }
            break;
        case 2:
            // rgb_save();
            break;
    }

    if (state->pressed && !state->interrupted) {
#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_toggle_noeeprom();
#endif
#ifdef RGBLIGHT_ENABLE
        rgblight_toggle_noeeprom();
#endif
    }
}


// clang-format off
tap_dance_action_t tap_dance_actions[] = {
    [TD_GAME] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RSFT, _GAMING),
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_F12),
    [TDE_VOL] = ACTION_TAP_DANCE_FN(vol_finished),
    [TDE_RGB] = ACTION_TAP_DANCE_FN(rgb_finished)
};
// clang-format on
