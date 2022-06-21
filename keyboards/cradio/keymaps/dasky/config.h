/* Copyright 2018-2021
 * ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
 * David Philip Barr <@davidphilipbarr>
 * Pierre Chevalier <pierrechevalier83@gmail.com>
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

// Improved mouse key defaults
// Delay between pressing a key and cursor movement
#define MOUSEKEY_DELAY 16
// Time between cursor movements in milliseconds
#define MOUSEKEY_INTERVAL 16
// Step size for acceleration
#define MOUSEKEY_MOVE_DELTA 9
#define MOUSEKEY_MAX_SPEED 12
#define MOUSEKEY_TIME_TO_MAX 70
#define MOUSEKEY_WHEEL_DELAY 16
#define MOUSEKEY_WHEEL_INTERVAL 30
#define MOUSEKEY_WHEEL_MAX_SPEED 10
#define MOUSEKEY_WHEEL_TIME_TO_MAX 95

#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO C14

#define USB_VBUS_PIN B5
#define SPLIT_HAND_PIN B9
#undef EE_HANDS

#undef DIRECT_PINS
#define DIRECT_PINS { \
    { F0, B11, B12, B13, B14 }, \
    { B3, A6, A7, B2,  A2}, \
    { B7, A15, C15, F1, A1}, \
    { A0, A4, NO_PIN, NO_PIN, NO_PIN } \
}


#undef DIRECT_PINS_RIGHT
#define DIRECT_PINS_RIGHT { \
    { B14, B13, B12, B11, F0}, \
    { A2, B2, A7, A6, B3 }, \
    { A1, F1, C15, A15,  B7}, \
    { A4, A0, NO_PIN, NO_PIN, NO_PIN } \
}

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN B10
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_SPEED 2000000
#define SERIAL_USART_TIMEOUT 10

#define WS2812_PWM_DRIVER PWMD5
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 1
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM5_UP

#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 15U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 123U
#define I2C1_TIMINGR_SCLL 255U

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN A15
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PIN B7
#define I2C1_SDA_PAL_MODE 4

#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 16
#define EXTERNAL_EEPROM_ADDRESS_SIZE 1

#define OVERRIDE_RGB_MATRIX_BRIGHTNESS 255
#define OVERRIDE_DEBOUNCE 2
