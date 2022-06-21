// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"

uint8_t get_bar_bits(uint8_t load) {
    uint8_t temp = 0;
    if (load > 2 && load < 10) {
        temp = 0b1000;
    } else if (load >= 90) {
        temp = 0b1111;
    } else if (load >= 50) {
        temp = 0b0111;
    } else if (load >= 25) {
        temp = 0b0011;
    } else if (load >= 10) {
        temp = 0b0001;
    }
    return temp;
};

#ifdef VIA_ENABLE
/*
Stop sending hid data before opening VIA application on host. All hid data is sent back to the host
with via enabled. The VIA application will not work as expected.
    data[0] 0x03 (VIA id_set_keyboard_value) workaround via doesn't seem to pass id_unhandled onto _kb
    data[1] 0xFF (not valid command data for id_set_keyboard_value so will be passed onto *kb (no *user))
    data[2-4] h, s, v (will automatically set mode to static)
    data[5] 0x01 is RGB update
    data[6+] temperature, load etc
*/
void raw_hid_receive_kb(uint8_t* data, uint8_t length) {
#else

#    define RAW_HUE data[2]
#    define RAW_SAT data[3]
#    define RAW_VAL data[4]
#    define RAW_DORGB data[5]
#    define RAW_CPU_TEMP data[6]
#    define RAW_CPU_LOAD data[9]
#    define RAW_GPU_TEMP data[7]
#    define RAW_GPU_LOAD data[10]

void raw_hid_receive(uint8_t* data, uint8_t length) {
#endif
#ifdef RGB_MATRIX_ENABLE
    if (RAW_DORGB == 1) {
        static uint16_t old_hue      = 0;
        static bool     changed_mode = false;
        if (!changed_mode) {  // only change mode on first update
            changed_mode = true;
            rgb_matrix_mode_noeeprom(RGB_MATRIX_HUE_WAVE);
        }
        if (old_hue != RAW_HUE || old_hue == 0) {
            old_hue     = RAW_HUE;
            uint8_t val = rgb_matrix_get_val();
            rgb_matrix_sethsv_noeeprom(RAW_HUE, RAW_SAT, val);
        }
    }
#endif
    user_state.cpu_temp = data[6];
    user_state.cpu_load = get_bar_bits(data[9]);
    user_state.gpu_temp = data[7];
    user_state.gpu_load = get_bar_bits(data[10]);
}
