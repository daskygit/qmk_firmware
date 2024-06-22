// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MAX_ABC(a, b, c) ((a > b) && (a > c)) ? a : ((b > a) && (b > c)) ? b : c
#ifdef VIA_ENABLE
#    define VIA_PACKET_SIZE 36
#else
#    define VIA_PACKET_SIZE 0
#endif
#define MAX_PACKET_SIZE MAX_ABC(sizeof(rf_packet_dongle_manufacturer_t), sizeof(rf_packet_product_t), VIA_PACKET_SIZE)

typedef struct PACKED {
    uint8_t cmd;
    uint8_t data;
    uint8_t checksum;
} rf_packet_generic_3_byte_t;

_Static_assert(sizeof(rf_packet_generic_3_byte_t) == 3, "packet should be 3 bytes");

typedef struct PACKED {
    uint8_t cmd;
    uint8_t string_length;
    uint8_t product_string[sizeof(PRODUCT)];
    uint8_t checksum;
} rf_packet_product_t;

typedef struct PACKED {
    uint8_t cmd;
    uint8_t string_length;
    uint8_t manufacturer_string[sizeof(MANUFACTURER)];
    uint8_t checksum;
} rf_packet_dongle_manufacturer_t;

typedef struct PACKED {
    uint8_t data[MAX_PACKET_SIZE];
    uint8_t length;
} rf_packet_buffer_t;

typedef struct PACKED {
    uint8_t  cmd;
    uint16_t vid;
    uint16_t pid;
    uint8_t  checksum;
} rf_packet_vidpid_t;

// The meaning of these status messages are best guess and likely incorrect.
typedef enum {
    RF_STATUS_ALIVE             = 0x23,
    RF_STATUS_UNKNOWN           = 0x2A,
    RF_STATUS_PAIRING           = 0x31, // last status after initiating pairing
    RF_STATUS_CONNECTED         = 0x32,
    RF_STATUS_DISCONNECTED      = 0x33,
    RF_STATUS_SWITCHING_PROFILE = 0x34, // happens after selecting another profile
    RF_STATUS_NOT_CONNECTED     = 0x35, // happens before connected
    RF_STATUS_NOT_PAIRED        = 0x37, // doesn't show when switched to already paired bluetooth profiles, always shows for dongle
    RF_STATUS_UNPAIRING         = 0x42, // only occurs when pairing a previous paired profile
} rf_status_ids_t;

typedef enum {
    RF_ID_LED_STATE           = 0x5A,
    RF_ID_STATUS              = 0x5B,
    RF_ID_BATTERY_LEVEL       = 0x5C,
    RF_ID_UNKNOWN_1           = 0x5D,
    RF_ID_UNKNOWN_2           = 0x60, //  had 0x00 and 0x01 as data e.g. (0x60 0x01 0x61)
    RF_ID_ACK                 = 0x61,
    RF_ID_6KRO                = 0xA1,
    RF_ID_NKRO                = 0xA2,
    RF_ID_CONSUMER            = 0xA3,
    RF_ID_SYSTEM              = 0xA4,
    RF_ID_SETTING             = 0xA6,
    RF_ID_MOUSE               = 0xA8,
    RF_ID_PRODUCT_BT          = 0xA9,
    RF_ID_MANUFACTURER_DONGLE = 0xAB,
    RF_ID_PRODUCT_DONGLE      = 0xAC,
    RF_ID_VID_PID             = 0xAD,
    RF_ID_VIA                 = 0xAF,
} rf_message_ids_t;

typedef enum {
    RF_SETTING_WIRED          = 0x11,
    RF_SETTING_PROFILE_DONGLE = 0x30,
    RF_SETTING_PROFILE_BT_1   = 0x31,
    RF_SETTING_PROFILE_BT_2   = 0x32,
    RF_SETTING_PROFILE_BT_3   = 0x33,
    RF_SETTING_PROFILE_BT_4   = 0x34,
    RF_SETTING_PROFILE_BT_5   = 0x35,
    RF_SETTING_PAIR_B         = 0x51,
    RF_SETTING_PAIR_A         = 0x52,
    RF_SETTING_KEEP_ALIVE     = 0x53,
    RF_SETTING_INIT_A         = 0x55,
    RF_SETTING_INIT_B         = 0x57,
    RF_SETTING_CLEAR_PAIRINGS = 0x62,
    RF_SETTING_INIT_C         = 0x70,
} rf_setting_cmds_t;

#define RF_PACKET_CHECKSUM(a, b) ((a + b) & 0xFF)

const rf_packet_generic_3_byte_t rf_packet_ack;
const rf_packet_generic_3_byte_t rf_packet_init_a;
const rf_packet_generic_3_byte_t rf_packet_init_b;
const rf_packet_generic_3_byte_t rf_packet_init_c;
const rf_packet_generic_3_byte_t rf_packet_profile_dongle_2_4;
const rf_packet_generic_3_byte_t rf_packet_profile_bt_1;
const rf_packet_generic_3_byte_t rf_packet_profile_bt_2;
const rf_packet_generic_3_byte_t rf_packet_profile_bt_3;
const rf_packet_generic_3_byte_t rf_packet_profile_bt_4;
const rf_packet_generic_3_byte_t rf_packet_profile_bt_5;
const rf_packet_generic_3_byte_t rf_packet_profile_wired;
const rf_packet_generic_3_byte_t rf_packet_keep_alive;
const rf_packet_generic_3_byte_t rf_packet_via_in;
const rf_packet_generic_3_byte_t rf_packet_cmd_pair_a;
const rf_packet_generic_3_byte_t rf_packet_cmd_pair_b;
const rf_packet_generic_3_byte_t rf_packet_clear_pairings;
rf_packet_product_t              rf_packet_bt_product;
rf_packet_product_t              rf_packet_dongle_product;
rf_packet_dongle_manufacturer_t  rf_packet_dongle_manufacturer;
rf_packet_vidpid_t               rf_packet_vidpid;
