// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define EE_HANDS

#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS \
    { GP4, GP5, GP6, GP7 }

#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS \
    { GP29, GP28, GP27, GP26, GP22, GP20 }

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN GP1

#define SELECT_SOFT_SERIAL_SPEED 0

#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

#undef RGB_DI_PIN
#define RGB_DI_PIN GP0

#define OVERRIDE_DEBOUNCE 2

#define USB_VBUS_PIN GP23

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED RGB_DI_PIN
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define CIRQUE_PINNACLE_CURVED_OVERLAY
#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_LEFT
#define POINTING_DEVICE_ROTATION_180
#define CIRQUE_PINNACLE_DIAMETER_MM 35

#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define CIRQUE_PINNACLE_TAP_ENABLE