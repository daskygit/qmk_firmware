// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#ifdef USBPD_ENABLE
#    include "usbpd_bits.h"
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

#ifdef DEBUG_MATRIX_SCAN_RATE
void render_matrix_rate(void) {
    char buffer[10];

    oled_write_ln((char*)itoa(get_matrix_scan_rate(), buffer, 10), false);
    if (get_matrix_scan_rate() < 10000) {
        oled_advance_page(true);
    }
}
#endif

void render_mod_status(uint8_t modifiers) {
    static const char PROGMEM gui_alt[4][11] = {
        {0x85, 0x86, 0x20, 0xcf, 0xcd, 0xa5, 0xa6, 0x20, 0x20, 0xce, 0},  // off
        {0x8d, 0x8e, 0x20, 0xc5, 0xc6, 0xad, 0xae, 0x20, 0xc7, 0xc8, 0},  // on
        {0x8d, 0x8e, 0x20, 0xcf, 0xcd, 0xad, 0xae, 0x20, 0x20, 0xce, 0},  // on off
        {0x85, 0x86, 0x20, 0xc5, 0xc6, 0xa5, 0xa6, 0x20, 0xc7, 0xc8, 0}   // off on
    };
    static const char PROGMEM shift_ctrl[4][11] = {
        {0x87, 0x88, 0x20, 0x89, 0x8a, 0xa7, 0xa8, 0x20, 0x20, 0x20, 0},  // off
        {0x8b, 0x8c, 0x20, 0xc9, 0xca, 0xab, 0xac, 0x20, 0xcb, 0xcc, 0},  // on
        {0x8b, 0x8c, 0x20, 0x89, 0x8a, 0xab, 0xac, 0x20, 0x20, 0x20, 0},  // on off
        {0x87, 0x88, 0x20, 0xc9, 0xca, 0xa7, 0xa8, 0x20, 0xcb, 0xcc, 0}   // off on
    };

    if ((modifiers & MOD_MASK_ALT) && (modifiers & MOD_MASK_GUI)) {
        oled_write_P(gui_alt[1], false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_alt[2], false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_P(gui_alt[3], false);
    } else {
        oled_write_P(gui_alt[0], false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(shift_ctrl[1], false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_ctrl[2], false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_P(shift_ctrl[3], false);
    } else {
        oled_write_P(shift_ctrl[0], false);
    }
}

void render_logo(void) {
    static const char PROGMEM kb_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(kb_logo, false);
}

void render_layer_state(void) {
    static const char PROGMEM oled_layers[6][16] = {
        {0x20, 0x94, 0x95, 0x96, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0},  // qwerty
        {0x20, 0x94, 0x90, 0x91, 0x20, 0x20, 0xb4, 0xb0, 0xb1, 0x20, 0x20, 0xd4, 0xd0, 0xd1, 0x20, 0},  // colemak
        {0x20, 0x94, 0x92, 0x93, 0x20, 0x20, 0xb4, 0xb2, 0xb3, 0x20, 0x20, 0xd4, 0xd2, 0xd3, 0x20, 0},  // gaming
        {0x20, 0x97, 0x98, 0x99, 0x20, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0},  // lower
        {0x20, 0x9a, 0x9b, 0x9c, 0x20, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0},  // raise
        {0x20, 0x9d, 0x9e, 0x9f, 0x20, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0}   // adjust
    };
    oled_write_P(oled_layers[get_highest_layer(layer_state)], false);
}

void render_status_main(void) {
    oled_advance_page(true);
    render_layer_state();
    oled_advance_page(true);
    oled_advance_page(true);
    render_mod_status(get_mods() | get_oneshot_mods());
    oled_advance_page(true);
#ifdef DEBUG_MATRIX_SCAN_RATE
    render_matrix_rate();
#endif
    render_logo();
}

#ifdef USBPD_ENABLE
void render_pd_allowance(void) {
    oled_write(PSTR("USB  "), false);
    oled_write(PSTR(" "), false);
    oled_write(usbpd_str(user_state.pd_setting), false);
}
#endif

#ifdef RAW_ENABLE
void render_hostinfo(const char* data, uint8_t value) {
    char buffer[3];
    oled_write_P(data, false);
    oled_advance_page(true);
    oled_advance_char();
    if (value < 100) {
        oled_advance_char();
        if (value < 10) {
            oled_advance_char();
        }
    }
    oled_write_ln((char*)itoa(value, buffer, 10), false);
}

void render_hostinfo_bar(uint8_t value) {
    if (value == 0b1000) {
        oled_write_char(0xa9, false);
    } else {
        if (value & (0b0001)) {
            oled_write_char(0xaa, false);
            if (value & 0b0010) {
                oled_write_char(0xaa, false);
                if (value & 0b0100) {
                    oled_write_char(0xaa, false);
                    if (value & 0b1000) {
                        oled_write_char(0xaa, false);
                    }
                }
            }
        }
    }
    oled_advance_page(true);
}
#endif

void render_status_secondary(void) {
    oled_advance_page(true);
#ifdef RAW_ENABLE
    render_hostinfo(PSTR("CPU"), user_state.cpu_temp);
    render_hostinfo_bar(user_state.cpu_load);
    oled_advance_page(true);
    render_hostinfo(PSTR("GFX"), user_state.gpu_temp);
    render_hostinfo_bar(user_state.gpu_load);
#endif
#ifdef USBPD_ENABLE
    oled_advance_page(true);
    render_pd_allowance();
#endif
    oled_advance_page(true);
    render_logo();
}

bool oled_task_user(void) {
    if (is_oled_on()) {
        if (is_keyboard_master()) {
            render_status_main();
        } else {
            render_status_secondary();
        }
    }
    return false;
}
