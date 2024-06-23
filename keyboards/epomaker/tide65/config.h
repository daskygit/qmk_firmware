// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDQ
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_SCK_PIN B3

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define EXTERNAL_FLASH_SIZE (1024 * 1024)

#define UART_DRIVER SD3
// #define UART_WRDLEN 1

#define SERIAL_DEFAULT_BITRATE 115200
#define UART_TX_PIN C10
#define UART_RX_PIN C11

#define USB_VBUS_PIN A7
#define RGB_POWER_PIN A5
#define CHARGING_STATUS_PIN A15

#define DEBUG_MATRIX_SCAN_RATE

#define WS2812_SPI_DRIVER SPIDM2
#define WS2812_SPI_MOSI_PAL_MODE 5
#define WS2812_SPI_DIVISOR 32

#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB

#define RF_DEBUG
#define RF_MAINTAINENCE_MS 1000
#define RF_SLEEP_TIME_MS 60000

#define RGB_SLEEP_TIME_MS 30000

#define CAPS_LOCK_LED 8
#define FN_LED 57

#define RENAME_WITH_LINE(A, B) COMBINE(A, B)
#define COMBINE(A, B) A##B
#define raw_hid_send(a, b) RENAME_WITH_LINE(_temp_rhs_, __LINE__)(a, b)
#define _temp_rhs_29 replaced_hid_send  // raw_hid.h
#define _temp_rhs_461 replaced_hid_send // via.c
