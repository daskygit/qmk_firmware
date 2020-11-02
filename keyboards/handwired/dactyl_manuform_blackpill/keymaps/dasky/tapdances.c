
#include "tapdances.h"


void lsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed) {
        switch (state->count) {
            case 1:
                register_code(KC_LSFT);
                tap_code(KC_9);
                break;
            case 2:
                register_code(KC_LSFT);
                tap_code(KC_LBRC);
                break;
            default:
                break;
        }
    } else {
        if (state->count >= 2) {
            tap_code(KC_LBRC);
        }
        register_code(KC_LSFT);
    }
}

void lsft_reset(qk_tap_dance_state_t *state, void *user_data) { unregister_code(KC_LSFT); }

void rsft_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (!state->pressed) {
        switch (state->count) {
            case 1:
                register_code(KC_RSFT);
                tap_code(KC_0);
                break;
            case 2:
                register_code(KC_RSFT);
                tap_code(KC_RBRC);
                break;
            default:
                break;
        }
    } else {
        if (state->count >= 2) {
            tap_code(KC_RBRC);
        }
        register_code(KC_RSFT);
    }
}

void rsft_reset(qk_tap_dance_state_t *state, void *user_data) { unregister_code(KC_RSFT); }

// clang-format off
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lsft_finished, lsft_reset),
    [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rsft_finished, rsft_reset)
};
