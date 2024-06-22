// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "rf8003a/rf_driver.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT( /* Base */
        KC_ESC,   KC_1,       KC_2,       KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_MUTE,
        KC_TAB,   KC_Q,       KC_W,       KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   QK_BOOT,
        KC_CAPS,  KC_A,       KC_S,       KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    QK_REBOOT,
        KC_LSFT,  KC_Z,       KC_X,       KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,               KC_SLSH,  KC_RSFT,  KC_UP,     NK_TOGG,
        KC_LCTL,  KC_LGUI,    KC_LALT,    KC_SPC,   KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,              MO(1),    KC_LEFT,  KC_DOWN,   KC_RIGHT
        ),

    [1] = LAYOUT( /* Base */
        KC_GRV,   KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,   KC_F12,   RF_PR_CLEAR,   _______,
        _______,  RF_BT1,     RF_BT2,   RF_BT3,   _______,  RF_WIRE,  _______,  _______,  _______,  _______,  RF_DONG,    KC_HOME,  KC_SCRL,  _______,   QK_BOOT,
        _______,  RF_PR_1,    RF_PR_2,  RF_PR_3,  _______,  _______,  _______,  _______,  _______,  _______,  RF_PR_D,    KC_PSCR,            _______,   QK_DEBUG_TOGGLE,
        _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,              _______,  RGB_VAI,   _______,
        _______,  GU_TOGG,    _______,  EE_CLR,   EE_CLR,   EE_CLR,   EE_CLR,                       _______,              _______,    _______,RGB_VAD,   _______
        )
};

// clang-format on
