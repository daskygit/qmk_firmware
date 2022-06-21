// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "tap_codes.h"

#define TAP_CODE_BUFFER_SIZE 32
#if (TAP_CODE_BUFFER_SIZE & (TAP_CODE_BUFFER_SIZE - 1)) == 0
#    define NEXT_TAP_CODE_POSITION(p) p = ((p + 1) & (TAP_CODE_BUFFER_SIZE - 1))
#else // a simple if else might be faster on ARM vs Modulus needs testing
#    define NEXT_TAP_CODE_POSITION(p) p = ((p + 1) % TAP_CODE_BUFFER_SIZE)
#    pragma message("Using a power of 2 for TAP_CODE_BUFFER_SIZE is faster.")
#endif

_Static_assert(TAP_CODE_BUFFER_SIZE < UINT16_MAX, "Tap code buffer should be less than unint16_max");

extern uint8_t extract_mod_bits(uint16_t code);
typedef struct tap_code_buffer {
    uint8_t  code;
    uint8_t  mods;
    uint16_t delay;
    bool     register_tap;
} tap_code_buffer;

tap_code_buffer tap_codes[TAP_CODE_BUFFER_SIZE] = {0};

static uint16_t     process_position = 0;
static uint16_t     queue_position   = 0;
static fast_timer_t process_timer    = 0;

void tap_code_buffer_init(void) {
    memset(&tap_codes, 0, sizeof(tap_codes));
}

void tap_code_register(uint8_t code, uint8_t mods, uint16_t delay, bool register_tap) {
    if (code && !delay) { // skip buffering if no delay.
        if (mods) {
            register_mods(mods);
        }
        register_code(code);
        // host_keyboard_send(keyboard_report);
        unregister_code(code);
        if (mods) {
            unregister_mods(mods);
        }
        return;
    }

    if (tap_codes[queue_position].code != 0) { // buffer full clear a spot. (blocking)
        uprintf("Full tap code buffer clearing at position: %d\n", queue_position);
        if (process_timer == 0) {
            process_tap_code_buffer();
        }
        while (timer_elapsed_fast(process_timer) < tap_codes[process_position].delay) {
            wait_ms(1);
        }
        process_tap_code_buffer();
    }

    tap_codes[queue_position].code         = code;
    tap_codes[queue_position].mods         = mods;
    tap_codes[queue_position].delay        = delay;
    tap_codes[queue_position].register_tap = register_tap;
    uprintf("Queued tap code at position: %d\n", queue_position);
    NEXT_TAP_CODE_POSITION(queue_position);
}

void process_tap_code_buffer(void) {
    if (tap_codes[process_position].code) {
        if (process_timer == 0) {
            if (tap_codes[process_position].register_tap) {
                if (tap_codes[process_position].mods) {
                    add_weak_mods(tap_codes[process_position].mods);
                }
                register_code(tap_codes[process_position].code);
            }
            process_timer = timer_read_fast();
        } else if (timer_elapsed_fast(process_timer) >= tap_codes[process_position].delay) {
            del_weak_mods(tap_codes[process_position].mods);
            unregister_code(tap_codes[process_position].code);
            tap_codes[process_position].code         = 0;
            tap_codes[process_position].mods         = 0;
            tap_codes[queue_position].delay          = 0;
            tap_codes[process_position].register_tap = false;
            process_timer                            = 0;
            uprintf("Processed tap code at position: %d\n", process_position);
            NEXT_TAP_CODE_POSITION(process_position);
        }
    }
}

void tap_code(uint8_t code) {
    tap_code_register(code, 0, TAP_CODE_DELAY, true);
}

void tap_code_chord(uint8_t code) {
    register_code(code);
    tap_code_register(code, 0, TAP_CODE_DELAY, false);
}

void tap_code_delay(uint8_t code, uint16_t delay) {
    tap_code_register(code, 0, delay, true);
}

void tap_code16(uint16_t code) {
    tap_code_register((uint8_t)code, extract_mod_bits(code), TAP_CODE_DELAY, true);
}

#define CHECK_FOR_REGISTERED_MT(keycode) (keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX && (get_mods() & ((keycode & 0x0F00) >> 8)))

bool process_record_taps(uint16_t keycode, keyrecord_t* record) {
    static fast_timer_t last_interrupted = 0;
    static fast_timer_t last_key_down    = 0;
    switch (keycode) {
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            if (record->event.pressed && ((timer_elapsed_fast(last_interrupted) < TAPPING_TERM) || (timer_elapsed_fast(last_key_down) < 200) || CHECK_FOR_REGISTERED_MT(keycode))) {
                tap_code_chord(keycode & 0xFF);
                record->tap.count = 0xF;
                last_interrupted  = timer_read_fast();
                return false;
            }
            if (record->tap.count == 0xF) {
                return false;
            }
            if (record->tap.count > 1 && (keycode == RAISER || keycode == RAISEL)) {
                if (record->event.pressed) {
                    register_code(keycode & 0xFF);
                    return false;
                } else {
                    unregister_code(keycode & 0xFF);
                    return false;
                }
            }
            if (record->tap.count && record->event.pressed) {
                if (keycode >= QK_MOD_TAP || keycode == RAISER || keycode == RAISEL) {
                    tap_code_chord(keycode & 0xFF);
                } else {
                    tap_code(keycode & 0xFF);
                }
                return false;
            } else if (record->tap.interrupted && (keycode >= QK_MOD_TAP || keycode == RAISER || keycode == RAISEL)) {
                tap_code_chord(keycode & 0xFF);
                last_interrupted = timer_read_fast();
                return false;
            }
        default:
            if (record->event.pressed) {
                last_key_down = timer_read_fast();
            }
            break;
    }
    return true;
}

// Use send_string tables
#define PGM_LOADBIT(mem, pos) ((pgm_read_byte(&((mem)[(pos) / 8])) >> ((pos) % 8)) & 0x01)

extern const uint8_t ascii_to_shift_lut[16];
extern const uint8_t ascii_to_keycode_lut[128];

void tap_char(char ascii_code) {
    uint8_t keycode    = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
    bool    is_shifted = PGM_LOADBIT(ascii_to_shift_lut, (uint8_t)ascii_code);
    tap_code_register(keycode, is_shifted ? MOD_BIT(KC_LSFT) : 0, TAP_CODE_DELAY, true);
}

void tap_string(const char* str) {
    while (1) {
        char ascii_code = pgm_read_byte(str);
        if (!ascii_code) break;
        tap_char(ascii_code);
        ++str;
    }
}
