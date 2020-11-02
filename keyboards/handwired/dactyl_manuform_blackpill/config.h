/* Copyright 2020 Dasky <discord:dasky#0592>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x444b
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    dasky
#define PRODUCT         Dactyl Keyboard (Split Common)
#define DESCRIPTION     ARM Split 5x6

/* Set USB polling to 1000hz*/
#define USB_POLLING_INTERVAL_MS 1

/* key matrix size */
#define MATRIX_ROWS 12 // Rows are doubled-up
#define MATRIX_COLS 6

/* Keyboard Matrix Assignments */
#define MATRIX_COL_PINS { B4, B5, B3, B7, B8, B9 }
#define MATRIX_ROW_PINS { A2, A3, A4, A5, A6, A7 }
#define MATRIX_COL_PINS_RIGHT { B9, B8, B7, B3, B5, B4 }

/* Split Keyboard specific options */
#define SOFT_SERIAL_PIN B6
#define SERIAL_USART_SPEED 2800000

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5
#define WS2812_PWM_TARGET_PERIOD 800000

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Force NKRO */
#define FORCE_NKRO

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG
/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Bootmagic Lite key configuration */
/* Top Left and Top Right */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5


#define BUSY_WAIT_INSTRUCTIONS 20 // Increase if two rows are pressed at the same time.
#define GPIO_INPUT_PIN_DELAY 5
