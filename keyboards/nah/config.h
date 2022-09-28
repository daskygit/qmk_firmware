// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEEE
#define PRODUCT_ID 0xEEED
#define DEVICE_VER 0x0001
#define MANUFACTURER "Dasky"
#define PRODUCT "Not A Hypergolic"

/* key matrix size */
#define MATRIX_ROWS 18
#define MATRIX_COLS 2

#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, B1, B3, B2, B6, B5 }

#define MATRIX_COL_PINS \
    { E6, C6 }

#define MATRIX_HAS_GHOST

#define SOFT_SERIAL_PIN D2
#define SPLIT_HAND_PIN D4

#define RGB_DI_PIN D7

#define DIODE_DIRECTION ROW2COL

#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM 36
#    define RGBLED_SPLIT \
        { 18, 18 }
#    define RGBLIGHT_SPLIT
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGBLED_NUM 36
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM
#    define RGB_MATRIX_SPLIT \
        { 18, 18 }
#    define SPLIT_TRANSPORT_MIRROR
#endif

/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT 0
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
#define POINTING_DEVICE_COMBINED
