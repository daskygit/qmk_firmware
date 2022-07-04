// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "pico/bootrom.h"

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
