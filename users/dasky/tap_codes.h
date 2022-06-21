// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

void tap_code_register(uint8_t code, uint8_t mods, uint16_t delay, bool register_tap);

bool process_record_taps(uint16_t keycode, keyrecord_t* record);

void process_tap_code_buffer(void);

void tap_code_buffer_init(void);

void tap_string(const char* str);
