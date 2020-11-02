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

#define SPLIT_HAND_PIN B0
#define SPLIT_PLUG_DETECT_PIN B10 //enables vbus detection using an external voltage divider - high = master
#define QMK_KEYS_PER_SCAN 8
#define RGB_DI_PIN B1
#define RGBLED_NUM 6
#define RGBLED_SPLIT {3, 3}
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define USE_RBIT
#define DEBUG_MATRIX_SCAN_RATE

#define DISABLE_SYNC_TIMER
#define CRC8_OPTIMIZE_SPEED
#define CRC8_USE_TABLE
