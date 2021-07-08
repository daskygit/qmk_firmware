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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x444B
#define PRODUCT_ID   0x5342
#define DEVICE_VER   0x0001
#define MANUFACTURER Stelulu Technology Inc.
#define PRODUCT Stinky Footboard(QMK)

#define VIAL_KEYBOARD_UID {0x1B, 0xD0, 0xA9, 0x06, 0x22, 0x01, 0x00, 0x31}

#define USB_POLLING_INTERVAL_MS 1

#define MATRIX_ROWS 1
#define MATRIX_COLS 4

#define DIRECT_PINS {{C2, D0, D2, D1}}
#define UNUSED_PINS

#define TAPPING_TERM 300
#define LED_LEFT B7
#define LED_RIGHT C7

#ifdef BACKLIGHT_ENABLE
#define BACKLIGHT_PIN C6
#define BACKLIGHT_LEVELS 3
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 10
#define BACKLIGHT_ON_STATE 0
#else
#define LED_POWER C6
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable action features */
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#define LAYER_STATE_8BIT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
