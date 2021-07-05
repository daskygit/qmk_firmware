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

#define FORCE_NKRO
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAP_CODE_DELAY 5
#undef DEBOUNCE
#define DEBOUNCE 5
#define QMK_KEYS_PER_SCAN 4
#define CRC8_OPTIMIZE_SPEED
#define CRC8_USE_TABLE

#define OLED_FADE_OUT

#define OLED_UPDATE_INTERVAL 100
#define OLED_TIMEOUT 0             // disable built in timeout
#define OLED_TIMEOUT_SYNCED 15000  // custom timeout using state synced from master
#define OLED_FONT_H "keyboards/crkbd/keymaps/dasky/glcdfont.c"

#define DEBUG_MATRIX_SCAN_RATE

#define USB_POLLING_INTERVAL_MS 1

// top left and top right
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW_RIGHT 4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 0

#define LAYER_STATE_8BIT
#define FORCED_SYNC_THROTTLE_MS 100
#define SPLIT_TRANSACTION_IDS_USER USER_STATE_SYNC
#define SPLIT_LAYER_STATE_ENABLE

#define BLINK_DURATION 100
#define AS_TIMEOUT 170

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#endif

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN B10
#define SERIAL_USART_DRIVER SD3
#define SERIAL_USART_SPEED 1500000
#define SERIAL_USART_TIMEOUT 10

#undef RGB_DI_PIN
#define RGB_DI_PIN A2

#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { C15, F1, A1, F0 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { B14, B13, B12, B11, B3, A6}
#define BUSY_WAIT_INSTRUCTIONS 35

#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO B0

#define USB_VBUS_PIN C13

#define SPLIT_HAND_PIN B9

// Current limiter configuration
#define POWER_ENABLE_PIN B1  // should be B5
#define POWER_1500MA_PIN B15
#define POWER_3000MA_PIN A8

// EEPROM Configuration
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C14
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 8           // (160MHz/8) => 20MHz
#define EXTERNAL_FLASH_BYTE_COUNT (4 * 1024 * 1024)  // 32Mb/4MB capacity
#define EXTERNAL_FLASH_PAGE_SIZE (4 * 1024)          // 4kB pages

// I2C Configuration
#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 15U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 123U
#define I2C1_TIMINGR_SCLL 255U

#define I2C_DRIVER I2CD1
#define I2C1_SCL_BANK GPIOA
#define I2C1_SCL 15
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_BANK GPIOB
#define I2C1_SDA 7
#define I2C1_SDA_PAL_MODE 4

// SPI Configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5

//#define NOP_FUDGE 0.4

#define WS2812_PWM_DRIVER PWMD5
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 1
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM5_UP
