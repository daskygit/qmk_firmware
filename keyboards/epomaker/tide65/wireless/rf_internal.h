// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef RF_DEBUG
#    include "debug.h"
#    include "print.h"
#    define rf_dprintf(...) dprintf(__VA_ARGS__)
#else
#    define rf_dprintf(...) \
        do {                \
        } while (0)
#endif

#ifndef RF_MAINTAINENCE_MS
#    define RF_MAINTAINENCE_MS 1000
#endif

uint32_t rf_maintainence_task(uint32_t trigger_time, void *cb_arg);
bool     rf_send_packet(const rf_packet_generic_3_byte_t *packet, bool check_for_ack, bool retry);
bool     rf_send_data(uint8_t *data, uint8_t length, bool check_for_ack, bool retry);
void     rf_handle_packet(rf_packet_generic_3_byte_t *packet);
void     rf_receive_check(void);
uint8_t  rf_generate_checksum(uint8_t *data, uint8_t length);
bool     rf_packet_is_valid(uint8_t *data, uint8_t length);
bool     rf_packet_is_ack(rf_packet_generic_3_byte_t *data);

uint8_t uart_read_timeout(uint8_t timeout);
void    uart_receive_timeout(uint8_t *data, uint16_t length, uint8_t timeout);

uint8_t rf_get_leds(void);
