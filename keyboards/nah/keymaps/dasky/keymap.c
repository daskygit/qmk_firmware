// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "lib/lib8tion/lib8tion.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_wrapper(KEYS_34(QWERTY)),
    [_COLEMAK]  = LAYOUT_wrapper(KEYS_34(COLEMAK)),
    [_GAMING]   = LAYOUT_wrapper(KEYS_34(GAMING)),
    [_LOWER]    = LAYOUT_wrapper(KEYS_34(LOWER)),
    [_RAISE]    = LAYOUT_wrapper(KEYS_34(RAISE)),
    [_ADJUST]   = LAYOUT_wrapper(KEYS_34(ADJUST))
};
// clang-format on

#ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    left_report.h = left_report.x;
    left_report.v = left_report.y;
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
#endif

void keyboard_post_init_kb(void) {
#ifdef POINTING_DEVICE_COMBINED
    pointing_device_set_cpi_on_side(true, 2000);
#endif
    keyboard_post_init_user();
}
