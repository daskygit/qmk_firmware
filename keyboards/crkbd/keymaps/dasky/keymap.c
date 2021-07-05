/*
Copyright 2020 Dasky

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "tapdances.h"
#include "transactions.h"
#include <string.h>
#include "rgbmatrix_indicators.h"
#include <hal.h>

static uint8_t start_key_led, end_key_led, start_under_led, end_under_led;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
    CTLNUBS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    TDLSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDRSFT ,
                                        RAISEL , LOWERL , KC_BSPC,      KC_SPC , LOWERR , ALTNUHS
),

[_COLEMAK] = LAYOUT_split_3x6_3(
    _______, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,                        KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______,
    _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,                        KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______,
    _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                                        _______, _______, _______,      _______, _______, _______
),

[_GAMING] = LAYOUT_split_3x6_3(
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, TDQUOT ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDGAME ,
                                        KC_LALT, KC_TAB , KC_SPC ,      KC_SPC , KC_ENT , KC_NUHS
),

[_LOWER] = LAYOUT_split_3x6_3(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______ ,
    _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_PSCR,
    _______, KC_MINS, KC_EQL , KC_NUHS, KC_LBRC, KC_RBRC,                        KC_F11 , KC_F12 , KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT,
                                        ADJUSTL, ADJUSTL, _______,      _______, ADJUSTR, _______
),

[_RAISE] = LAYOUT_split_3x6_3(
    KC_ESC , KC_BSPC, KC_UP  , KC_ENT , WINR   , XXXXXXX,                        KC_ACL0, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                        KC_ACL1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_PSCR,
    _______, UNDO   , CUT    , COPY   , PASTE  , SAVE   ,                        KC_ACL2, XXXXXXX, KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT,
                                        _______, XXXXXXX, XXXXXXX,      KC_BTN1, ADJUSTR, KC_BTN2
),

[_ADJUST] = LAYOUT_split_3x6_3(
    RESET  , EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, EH_LEFT,                        EH_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, COLETOG,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, EH_RGHT,                        EH_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAMETOG,
                                        XXXXXXX, _______, XXXXXXX,      XXXXXXX, _______, XXXXXXX
)

};
// clang-format on

void user_state_sync(bool force) {
    if (is_keyboard_master()) {
        static user_runtime_config last_user_state;
        static bool                needs_sync = false;
        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_runtime_config))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_runtime_config));
        }

        if (force) {
            needs_sync = true;
        }
        // Perform the sync if requested
        if (needs_sync) {
            needs_sync = !transaction_rpc_send(USER_STATE_SYNC, sizeof(user_runtime_config), &user_state);
        }
    }
}

const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        case USBPD_500MA:
            return "0.5A";
        case USBPD_1500MA:
            return "1.5A";
        case USBPD_3000MA:
            return "3.0A";
        default:
            return "0.5A";
    }
}

void usbpd_update(void) {
    static usbpd_allowance_t last_pd_setting;
    last_pd_setting = user_state.pd_setting;
    switch (usbpd_get_allowance()) {
        case USBPD_500MA:
            if (user_state.pd_setting != USBPD_500MA) {
                setPinInput(POWER_1500MA_PIN);
                setPinInput(POWER_3000MA_PIN);
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_500MA));
                user_state.pd_setting = USBPD_500MA;
            }
            break;
        case USBPD_1500MA:
            if (user_state.pd_setting != USBPD_1500MA) {
                setPinInput(POWER_3000MA_PIN);
                setPinOutput(POWER_1500MA_PIN);
                writePinLow(POWER_1500MA_PIN);
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_1500MA));
                user_state.pd_setting = USBPD_1500MA;
            }
            break;
        case USBPD_3000MA:
            if (user_state.pd_setting != USBPD_3000MA) {
                setPinOutput(POWER_1500MA_PIN);
                writePinLow(POWER_1500MA_PIN);
                setPinOutput(POWER_3000MA_PIN);
                writePinLow(POWER_3000MA_PIN);
                dprintf("Transitioning UCPD1 %s -> %s\n", usbpd_str(user_state.pd_setting), usbpd_str(USBPD_3000MA));
                user_state.pd_setting = USBPD_3000MA;
            }
            break;
    }
    if (user_state.pd_setting != last_pd_setting) {
        writePinLow(POWER_ENABLE_PIN);
        wait_ms(10);
        writePinHigh(POWER_ENABLE_PIN);
    }
}

void board_init(void) { usbpd_init(); }

#define rgb_to_hsv_hook_func rgb_matrix_hsv_to_rgb
RGB rgb_to_hsv_hook_func(HSV hsv) {
    float scale;
    switch (user_state.pd_setting) {
        default:
        case USBPD_500MA:
            scale = 0.40f;  // 370ma white
            break;
        case USBPD_1500MA:
            scale = 0.60f;
            break;
        case USBPD_3000MA:
            scale = 0.95f;
            break;
    }

    hsv.v = (uint8_t)(hsv.v * scale);
    return hsv_to_rgb(hsv);
}

void rpc_user_sync_callback(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, sizeof(user_runtime_config));
    }
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;

    // Ensure increased current limits are off
    setPinInput(POWER_1500MA_PIN);
    setPinInput(POWER_3000MA_PIN);
    // Enable 5V output at 500mA
    if (is_keyboard_master()) {
        setPinOutput(POWER_ENABLE_PIN);
        writePinHigh(POWER_ENABLE_PIN);
    }

    // Register keyboard state sync split transaction
    transaction_register_rpc(USER_STATE_SYNC, rpc_user_sync_callback);

    // Reset the initial shared data value between master and slave
    memset(&user_state, 0, sizeof(user_state));
    if (is_keyboard_left()) {
        start_key_led   = LEFT_FIRST_RGB;
        end_key_led     = LEFT_LAST_RGB;
        start_under_led = LEFT_FIRST_UNDERGLOW;
        end_under_led   = LEFT_LAST_UNDERGLOW;
    } else {
        start_key_led   = RIGHT_FIRST_RGB;
        end_key_led     = RIGHT_LAST_RGB;
        start_under_led = RIGHT_FIRST_UNDERGLOW;
        end_under_led   = RIGHT_LAST_UNDERGLOW;
    }

    usbpd_update();
    user_state_sync(true);  // force initial update
}

void suspend_power_down_user(void) {
#ifdef OLED_DRIVER_ENABLE
    user_state.oled_off_state = 1;
    oled_off();
#endif
}

uint32_t blink_timer = 0;

void rgb_check_blinking(uint8_t led_start, uint8_t led_end) {
    if (is_keyboard_master()) {
        if (blink_timer > 0) {
            if (timer_elapsed(blink_timer) > AS_TIMEOUT) {
                user_state.blinking = true;
                for (uint8_t i = led_start; i < led_end + 1; i++) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
                if (timer_elapsed(blink_timer) - AS_TIMEOUT > BLINK_DURATION) {
                    blink_timer         = 0;
                    user_state.blinking = false;
                }
            }
        }
    } else {
        if (user_state.blinking) {
            for (uint8_t i = led_start; i < led_end + 1; i++) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
}

void rgb_show_layer(uint8_t led_start, uint8_t led_end) {
    const uint8_t* selected_theme = NULL;
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            selected_theme = is_keyboard_left() ? lower_left : lower_right;
            break;
        case _RAISE:
            selected_theme = is_keyboard_left() ? raise_left : raise_right;
            break;
        case _GAMING:
            selected_theme = is_keyboard_left() ? gaming_left : gaming_right;
            break;

        default:
            break;
    }

    if (selected_theme) {
        for (uint8_t i = led_start; i <= led_end; i++) {
            uint8_t hue = pgm_read_byte(selected_theme);
            selected_theme++;
            if (hue == 255) {
                continue;
            };
            uint8_t val = (hue != 0) ? rgb_matrix_get_val() : 0;
            HSV     hsv = {.h = hue, .s = 255, .v = val};
            RGB     rgb = rgb_to_hsv_hook_func(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    // if (!user_state.blinking) {
    rgb_show_layer(start_key_led, end_key_led);
    //}
    rgb_check_blinking(start_key_led, end_key_led);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static uint16_t autoshift_array[MATRIX_ROWS][MATRIX_COLS] = {0};

#define AS_ARRAY autoshift_array[record->event.key.row][record->event.key.col]

    if (get_highest_layer(layer_state) == _LOWER) {
        switch (keycode) {
            case KC_MINS:
            case KC_EQL:
            case KC_NUHS:
            case KC_LBRC:
            case KC_RBRC:
            case KC_GRV:
            case KC_F1 ... KC_F12:
            case KC_1 ... KC_0:
                if (record->event.pressed) {
                    if (AS_ARRAY == 0) {
                        AS_ARRAY = record->event.time;
                        if (!user_state.blinking) {
                            blink_timer = record->event.time;
                        }
                    }
                } else {
                    if (AS_ARRAY > 0) {
                        if (timer_elapsed(AS_ARRAY) > AS_TIMEOUT) {
                            tap_code16(S(keycode));
                        } else {
                            tap_code(keycode);
                            if (!user_state.blinking) {
                                blink_timer = 0;
                            }
                        }
                        AS_ARRAY = 0;
                    }
                }
                return false;
        }
    }

    return true;
}

#ifdef RAW_ENABLE
#    ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_pd_allowance(void) {
    oled_write(PSTR("USB  "), false);
    oled_write(PSTR(" "), false);
    oled_write(usbpd_str(user_state.pd_setting), false);
}

#        ifdef DEBUG_MATRIX_SCAN_RATE
void render_matrix_rate(void) {
    char buffer[10];

    oled_write_ln(itoa(get_matrix_scan_rate(), buffer, 10), false);
    if (get_matrix_scan_rate() < 10000) {
        oled_advance_page(true);
    }
}
#        endif

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
#        ifdef DEBUG_MATRIX_SCAN_RATE
    render_matrix_rate();
#        endif
    render_logo();
}

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
    oled_write_ln(itoa(value, buffer, 10), false);
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

void render_status_secondary(void) {
    oled_advance_page(true);
    render_hostinfo(PSTR("CPU"), user_state.cpu_temp);
    render_hostinfo_bar(user_state.cpu_load);
    oled_advance_page(true);
    render_hostinfo(PSTR("GFX"), user_state.gpu_temp);
    render_hostinfo_bar(user_state.gpu_load);
    oled_advance_page(true);
    render_pd_allowance();
    oled_advance_page(true);
    render_logo();
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        if (is_oled_on() && last_matrix_activity_elapsed() >= OLED_TIMEOUT_SYNCED) {
            user_state.oled_off_state = 1;
            oled_off();
        } else if (last_matrix_activity_elapsed() < OLED_TIMEOUT_SYNCED) {
            oled_on();
            user_state.oled_off_state = 0;
            render_status_main();
        }
    } else {
        if (user_state.oled_off_state == 0) {
            oled_on();
            render_status_secondary();
        } else if (is_oled_on()) {
            oled_off();
        }
    }
}

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

#        ifdef VIA_ENABLE
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
#        else

#            define RAW_HUE data[2]
#            define RAW_SAT data[3]
#            define RAW_VAL data[4]
#            define RAW_DORGB data[5]
#            define RAW_CPU_TEMP data[6]
#            define RAW_CPU_LOAD data[9]
#            define RAW_GPU_TEMP data[7]
#            define RAW_GPU_LOAD data[10]

void raw_hid_receive(uint8_t* data, uint8_t length) {
#        endif
#        ifdef RGB_MATRIX_ENABLE
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
#        endif
    user_state.cpu_temp = data[6];
    user_state.cpu_load = get_bar_bits(data[9]);
    user_state.gpu_temp = data[7];
    user_state.gpu_load = get_bar_bits(data[10]);
}
#    endif
#endif

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_read  = 0;
        static uint32_t last_read2 = 0;
        if (timer_elapsed32(last_read2) > 10000) {
            last_read2 = timer_read32();
            dprintf("UCPD1 current allowance %s\n", usbpd_str(usbpd_get_allowance()));
        }
        if (timer_elapsed32(last_read) > 250) {
            last_read = timer_read32();
            usbpd_update();
            user_state_sync(true);
        } else {
            user_state_sync(false);
        }
    }

    static bool oled_started = false;
    if (!oled_started) {
        oled_started = oled_init(OLED_ROTATION_270);
    }
}

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_pins(void) {
    for (size_t i = 0; i < MATRIX_COLS; i++) {
        setPinInputHigh(col_pins[i]);
    }
    for (size_t i = 0; i < MATRIX_ROWS; i++) {
        setPinOutput(row_pins[i]);
        writePinHigh(row_pins[i]);
    }
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    writePinLow(row_pins[current_row]);

    // matrix_output_select_delay();
    while (readPin(row_pins[current_row]) != 0)
        ;

    uint16_t portb = palReadPort(GPIOB);
    uint16_t porta = palReadPort(GPIOA);
    writePinHigh(row_pins[current_row]);
    matrix_row_t cols;

    cols = ~(((portb & 0x7800) >> 9) | ((portb & 0x8) >> 2) | ((porta & 0x40) >> 6));

    uint32_t temp = cols;
    __asm__("rbit %0, %1" : "=r"(temp) : "r"(temp));
    current_matrix[current_row] = temp >> 26;

    // /* Wait until col pins are high again. */
    // size_t counter = 0xFF;
    // while (((palReadGroup(GPIOB, 0x7808, 0) != 0x7808) || (palReadGroup(GPIOA, 0x40, 0) != 0x40)) && counter != 0) {
    //     counter--;
    // }

    for (size_t i = 0; i < MATRIX_COLS; i++) {
        while (readPin(col_pins[i]) != 1)
            ;
    }
}
