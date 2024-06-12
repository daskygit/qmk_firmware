// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf_driver.h"
#include "rf_packets.h"
#include "rf_reports.h"
#include "rf_internal.h"

void rf_send_keyboard(report_keyboard_t *report) {
    rf_report_keyboard_t rf_report = {
        .cmd      = 0xA1,
        .mods     = report->mods,
        .reserved = report->reserved,
        .keys     = {0},
    };
    memcpy(rf_report.keys, report->keys, RF_KEYBOARD_REPORT_KEYS);
    rf_report.checksum = rf_generate_checksum((uint8_t *)&rf_report, 9);
    rf_send_data((uint8_t *)&rf_report, 10, true, true);
}

uint8_t rf_keyboard_leds(void) {
    return rf_get_leds();
}

void rf_send_nkro(report_nkro_t *report) {
    static bool       sent_keyboard_last_report = false;
    uint8_t           top_key_count             = 0;
    report_nkro_t     temp_nkro                 = {0};
    report_keyboard_t temp_keyboard_report      = {0};

    rf_report_keyboard_t rf_report_keyboard = {
        .cmd      = RF_ID_6KRO,
        .mods     = report->mods,
        .reserved = 0,
        .keys     = {0},
    };

    rf_report_nkro_t rf_nkro_report = {
        .cmd  = RF_ID_NKRO,
        .bits = {0},
    };

    memcpy(temp_nkro.bits, report->bits, NKRO_REPORT_BITS);

    for (uint8_t i = RF_NKRO_REPORT_BYTES; i < NKRO_REPORT_BITS; i++) {
        top_key_count += __builtin_popcount(temp_nkro.bits[i]);
    }

    for (uint8_t i = 0; i < top_key_count; i++) {
        uint8_t temp_key;
        uint8_t n = RF_NKRO_REPORT_BYTES;

        for (; n < NKRO_REPORT_BITS && !temp_nkro.bits[n]; n++)
            ;
        temp_key = n << 3 | biton(temp_nkro.bits[n]);

        del_key_bit(&temp_nkro, temp_key);
        add_key_byte(&temp_keyboard_report, temp_key);
    }

    if (sent_keyboard_last_report || rf_report_keyboard.mods || top_key_count > 0) {
        if (sent_keyboard_last_report) {
            sent_keyboard_last_report = false;
        } else {
            sent_keyboard_last_report = true;
        }
        memcpy(rf_report_keyboard.keys, temp_keyboard_report.keys, RF_KEYBOARD_REPORT_KEYS);
        rf_report_keyboard.checksum = rf_generate_checksum((uint8_t *)&rf_report_keyboard, sizeof(rf_report_keyboard_t) - 1);
        rf_send_data((uint8_t *)&rf_report_keyboard, sizeof(rf_report_keyboard_t), true, true);
    }

    memcpy(rf_nkro_report.bits, report->bits, RF_NKRO_REPORT_BYTES);
    rf_nkro_report.checksum = rf_generate_checksum((uint8_t *)&rf_nkro_report, sizeof(rf_report_nkro_t) - 1);
    rf_send_data((uint8_t *)&rf_nkro_report, RF_NKRO_REPORT_BYTES + 2, true, true);
}

static inline uint8_t SYSTEM2RF(uint16_t usage) {
    switch (usage) {
        case SYSTEM_WAKE_UP:
            return 0x04;
        case SYSTEM_SLEEP:
            return 0x02;
        case SYSTEM_POWER_DOWN:
            return 0x01;
        default:
            return 0x00;
    }
}

void rf_send_extra(report_extra_t *report) {
    switch (report->report_id) {
        case REPORT_ID_CONSUMER:;
            rf_report_consumer_t consumer_report = {
                .cmd   = RF_ID_CONSUMER,
                .usage = report->usage,
            };
            consumer_report.checksum = rf_generate_checksum((uint8_t *)&consumer_report, sizeof(rf_report_consumer_t) - 1);
            rf_send_data((uint8_t *)&consumer_report, sizeof(rf_report_consumer_t), true, true);
            break;
        case REPORT_ID_SYSTEM:;
            rf_report_system_t system_report = {
                .cmd   = RF_ID_SYSTEM,
                .usage = SYSTEM2RF(report->usage),
            };
            system_report.checksum = rf_generate_checksum((uint8_t *)&system_report, sizeof(rf_report_system_t) - 1);
            rf_send_data((uint8_t *)&system_report, sizeof(rf_report_system_t), true, true);
            break;
    };
}

void rf_send_mouse(report_mouse_t *report) {
    rf_report_mouse_t mouse_report = {
        .cmd     = RF_ID_MOUSE,
        .buttons = report->buttons,
        .x       = report->x,
        .y       = report->y,
        .h       = report->h,
        .v       = report->v,
    };
    mouse_report.checksum = rf_generate_checksum((uint8_t *)&mouse_report, sizeof(rf_report_mouse_t) - 1);
    rf_send_data((uint8_t *)&mouse_report, sizeof(rf_report_mouse_t), true, true);
}
