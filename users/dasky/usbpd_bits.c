// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"

const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        default:
        case USBPD_500MA:
            return "0.5A";
        case USBPD_1500MA:
            return "1.5A";
        case USBPD_3000MA:
            return "3.0A";
    }
}

bool usbpd_update(void) {
    switch (usbpd_get_allowance()) {
        case USBPD_500MA:
            if (user_state.pd_setting != USBPD_500MA) {
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_500MA));
                user_state.pd_setting = USBPD_500MA;
                return true;
            }
            break;
        case USBPD_1500MA:
            if (user_state.pd_setting != USBPD_1500MA) {
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_1500MA));
                user_state.pd_setting = USBPD_1500MA;
                return true;
            }
            break;
        case USBPD_3000MA:
            if (user_state.pd_setting != USBPD_3000MA) {
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_3000MA));
                user_state.pd_setting = USBPD_3000MA;
                return true;
            }
            break;
    }
    return false;
}

void board_init(void) { usbpd_init();}

#if defined(RGB_MATRIX_ENABLE) || defined (RGBLIGHT_ENABLE)
#define rgb_to_hsv_hook_func rgb_matrix_hsv_to_rgb
RGB rgb_to_hsv_hook_func(HSV hsv) {
    float scale;
    switch (user_state.pd_setting) {
        default:
        case USBPD_500MA:
            scale = 0.40f;
            break;
        case USBPD_1500MA:
            scale = 0.7f;
            break;
        case USBPD_3000MA:
            scale = 1.0f;
            break;
    }

    hsv.v = (uint8_t)(hsv.v * scale);
    return hsv_to_rgb(hsv);
}
#endif
