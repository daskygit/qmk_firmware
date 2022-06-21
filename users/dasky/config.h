// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define FORCE_NKRO
#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define AUTO_SHIFT_TIMEOUT 160
#define IGNORE_MOD_TAP_INTERRUPT
#define HOLD_ON_OTHER_KEY_PRESS
#define COMBO_TERM 15
#define MT_TERM 150
#define ENCODER_TERM 300
#ifdef TAP_CODE_DELAY
#    undef TAP_CODE_DELAY
#endif
#define TAP_CODE_DELAY 5
#ifdef OVERRIDE_DEBOUNCE
#    undef DEBOUNCE
#    define DEBOUNCE OVERRIDE_DEBOUNCE
#endif
#define LAYER_STATE_8BIT
#define USB_POLLING_INTERVAL_MS 1
#define DEBUG_MATRIX_SCAN_RATE

#ifdef SPLIT_KEYBOARD
#    define CRC8_OPTIMIZE_SPEED
#    define CRC8_USE_TABLE
#    define FORCED_SYNC_THROTTLE_MS 100
#    define SPLIT_TRANSACTION_IDS_USER USER_SYNC_ID, EEPROM_SYNC_ID, MOUSE_SYNC_ID
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_OLED_ENABLE
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_HUE_WAVE
#    ifdef OVERRIDE_RGB_MATRIX_BRIGHTNESS
#        undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS OVERRIDE_RGB_MATRIX_BRIGHTNESS
#    endif
#    ifdef USER_MINIMAL
#        define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_HUE_WAVE
#        define ENABLE_RGB_MATRIX_HUE_WAVE
#        undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#        undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#        undef ENABLE_RGB_MATRIX_BREATHING
#        undef ENABLE_RGB_MATRIX_BAND_SAT
#        undef ENABLE_RGB_MATRIX_BAND_VAL
#        undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        undef ENABLE_RGB_MATRIX_CYCLE_ALL
#        undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#        undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#        undef ENABLE_RGB_MATRIX_DUAL_BEACON
#        undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#        undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        undef ENABLE_RGB_MATRIX_RAINDROPS
#        undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#        undef ENABLE_RGB_MATRIX_HUE_BREATHING
#        undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#        undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#        undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#        undef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#        undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#        undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#        undef RGB_MATRIX_KEYPRESSES
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        undef ENABLE_RGB_MATRIX_SPLASH
#        undef ENABLE_RGB_MATRIX_MULTISPLASH
#        undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#        undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    else
#        define ENABLE_RGB_MATRIX_ALPHAS_MODS
#        define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_BREATHING
#        define ENABLE_RGB_MATRIX_BAND_SAT
#        define ENABLE_RGB_MATRIX_BAND_VAL
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        define ENABLE_RGB_MATRIX_CYCLE_ALL
#        define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#        define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define ENABLE_RGB_MATRIX_DUAL_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#        define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        define ENABLE_RGB_MATRIX_RAINDROPS
#        define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#        define ENABLE_RGB_MATRIX_HUE_BREATHING
#        define ENABLE_RGB_MATRIX_HUE_PENDULUM
#        define ENABLE_RGB_MATRIX_HUE_WAVE
#        define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#        define ENABLE_RGB_MATRIX_PIXEL_RAIN
#        define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#        define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#        define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#        define RGB_MATRIX_KEYPRESSES
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define ENABLE_RGB_MATRIX_SPLASH
#        define ENABLE_RGB_MATRIX_MULTISPLASH
#        define ENABLE_RGB_MATRIX_SOLID_SPLASH
#        define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    endif
#endif

#ifdef OLED_ENABLE
#    define OLED_UPDATE_INTERVAL 100
#    define OLED_TIMEOUT 0
#    define OLED_FONT_H "oled_font.h"
#endif
