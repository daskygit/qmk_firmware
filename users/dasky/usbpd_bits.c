// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"

bool usbpd_allowance(void) {
    static usbpd_allowance_t last_allowance    = 0;
    usbpd_allowance_t        current_allowance = usbpd_get_allowance();
    bool update = false;
    if (current_allowance != last_allowance) {
        update = true;
        dprintf("USBPD Allowance: ");
        switch (current_allowance) {
            case USBPD_500MA:
                dprintf("0.5A\n");
                break;
            case USBPD_1500MA:
                dprintf("1.5A\n");
                break;
            case USBPD_3000MA:
                dprintf("3.0A\n");
                break;
            default:
                dprintf("?A\n");
                break;
        }
#if defined(SPLIT_KEYBOARD)
        user_state.pd_setting = current_allowance;
#endif
        last_allowance = current_allowance;
    }
    return update;
}

void board_init(void) {
    usbpd_init();
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
#    define rgb_to_hsv_hook_func rgb_matrix_hsv_to_rgb
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
