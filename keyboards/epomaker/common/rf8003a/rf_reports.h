// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RF_KEYBOARD_REPORT_KEYS 6
#define RF_NKRO_REPORT_BYTES 14

typedef struct {
    uint8_t cmd;
    uint8_t mods;
    uint8_t reserved;
    uint8_t keys[RF_KEYBOARD_REPORT_KEYS];
    uint8_t checksum;
} PACKED rf_report_keyboard_t;

typedef struct {
    uint8_t cmd;
    uint8_t bits[RF_NKRO_REPORT_BYTES];
    uint8_t checksum;
} PACKED rf_report_nkro_t;

typedef struct {
    uint8_t  cmd;
    uint16_t usage;
    uint8_t  checksum;
} PACKED rf_report_consumer_t;

typedef struct {
    uint8_t cmd;
    uint8_t usage;
    uint8_t checksum;
} PACKED rf_report_system_t;

typedef struct {
    uint8_t           cmd;
    uint8_t           buttons;
    mouse_xy_report_t x;
    mouse_xy_report_t y;
    int8_t            h;
    int8_t            v;
    uint8_t           checksum;
} PACKED rf_report_mouse_t;

uint8_t rf_keyboard_leds(void);
void    rf_send_mouse(report_mouse_t *report);
void    rf_send_extra(report_extra_t *report);
void    rf_send_keyboard(report_keyboard_t *report);
void    rf_send_nkro(report_nkro_t *report);
