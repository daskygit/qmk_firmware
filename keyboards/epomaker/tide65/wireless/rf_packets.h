// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

typedef struct {
    uint8_t cmd;
    uint8_t string_length;
    uint8_t product_string[sizeof(PRODUCT)];
    uint8_t checksum;
} PACKED rf_packet_product_t;

typedef struct {
    uint8_t cmd;
    uint8_t string_length;
    uint8_t manufacturer_string[sizeof(MANUFACTURER)];
    uint8_t checksum;
} PACKED rf_packet_dongle_manufacturer_t;

typedef struct {
    uint8_t  cmd;
    uint16_t vid;
    uint16_t pid;
    uint8_t  checksum;
} PACKED rf_packet_vidpid_t;

uint8_t rf_packet_ack[]                = {0x61, 0x0D, 0x0A};
uint8_t rf_packet_init_a[]             = {0xA6, 0x55, 0xFB};
uint8_t rf_packet_init_b[]             = {0xA6, 0x57, 0xFD};
uint8_t rf_packet_init_c[]             = {0xA6, 0x70, 0x16};
uint8_t rf_packet_profile_dongle_2_4[] = {0xA6, 0x30, 0xD6};
uint8_t rf_packet_profile_bt_1[]       = {0xA6, 0x31, 0xD7};
uint8_t rf_packet_profile_bt_2[]       = {0xA6, 0x32, 0xD8};
uint8_t rf_packet_profile_bt_3[]       = {0xA6, 0x33, 0xD9};
uint8_t rf_packet_profile_wired[]      = {0xA6, 0x11, 0xB7};
uint8_t rf_packet_keep_alive[]         = {0xA6, 0x53, 0xF9};
uint8_t rf_packet_via_in[]             = {0xAF, 0x60, 0x20};

uint8_t rf_packet_cmd_pair_a[] = {0xA6, 0x52, 0xF8};
uint8_t rf_packet_cmd_pair_b[] = {0xA6, 0x51, 0xF7};

rf_packet_product_t rf_packet_bt_product = {
    .cmd            = 0xA9,
    .string_length  = sizeof(PRODUCT),
    .product_string = PRODUCT,
};

rf_packet_product_t rf_packet_dongle_product = {
    .cmd            = 0xAC,
    .string_length  = sizeof(PRODUCT),
    .product_string = PRODUCT,
};

rf_packet_dongle_manufacturer_t rf_packet_dongle_manufacturer = {
    .cmd                 = 0xAB,
    .string_length       = sizeof(MANUFACTURER),
    .manufacturer_string = MANUFACTURER,
};

rf_packet_vidpid_t rf_packet_vidpid = {
    .cmd = 0xAD,
    .vid = VENDOR_ID,
    .pid = PRODUCT_ID,
};
