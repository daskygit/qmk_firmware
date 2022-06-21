// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dasky.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(QWERTY)),
    [_COLEMAK]  = LAYOUT_split_4x6_3_wrapper(KEYS_54(COLEMAK)),
    [_GAMING]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(GAMING)),
    [_LOWER]    = LAYOUT_split_4x6_3_wrapper(KEYS_54(LOWER)),
    [_RAISE]    = LAYOUT_split_4x6_3_wrapper(KEYS_54(RAISE)),
    [_ADJUST]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(ADJUST))
};
// clang-format off