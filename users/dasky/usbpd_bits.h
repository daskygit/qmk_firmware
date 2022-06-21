// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

const char* usbpd_str(usbpd_allowance_t allowance);
bool        usbpd_update(void);


#if defined(RGB_MATRIX_ENABLE) || defined (RGBLIGHT_ENABLE)
RGB rgb_matrix_hsv_to_rgb(HSV hsv);
#endif
