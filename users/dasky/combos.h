// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define CB(name, action, ...) C_##name,
enum user_combos {
#include "combos.def"
    COMBO_LENGTH
};
#undef CB
uint16_t COMBO_LEN = COMBO_LENGTH;

#define CB(name, action, ...) const uint16_t PROGMEM name##_combo[] = {__VA_ARGS__, COMBO_END};
#include "combos.def"
#undef CB

combo_t key_combos[COMBO_LENGTH] = {
#define CB(name, action, ...) COMBO(name##_combo, action),
#include "combos.def"
#undef CB
};
