// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include QMK_KEYBOARD_H

#include "wrappers.h"
#include <string.h>

enum custom_keycodes {
    CUS_VER = SAFE_RANGE,
    CUS_BLD,
    CUS_GEN,
    CUS_FLH,
    CUS_TST,
    NEW_SAFE_RANGE,
};

enum layers { _QWERTY, _COLEMAK, _GAMING, _LOWER, _RAISE, _ADJUST };
__attribute__((aligned(1))) typedef struct user_config {
#if defined(RGB_MATRIX_ENABLE) || defined (RGBLIGHT_ENABLE)
    bool rgb_off_state : 1;
    bool blinking : 1;
#endif
#if RAW_ENABLE
    uint8_t cpu_temp : 7;
    uint8_t cpu_load : 4;
    uint8_t gpu_temp : 7;
    uint8_t gpu_load : 4;
#endif
#if USBPD_ENABLE
    usbpd_allowance_t pd_setting : 2;
#endif
} user_config;

user_config user_state;

