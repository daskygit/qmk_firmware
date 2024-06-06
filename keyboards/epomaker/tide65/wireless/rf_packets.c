// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rf_driver.h"
#include "rf_packets.h"
#include "rf_reports.h"
#include "rf_internal.h"

const rf_packet_generic_3_byte_t rf_packet_ack                = {RF_ID_ACK, 0x0D, 0x0A};
const rf_packet_generic_3_byte_t rf_packet_init_a             = {RF_ID_SETTING, RF_SETTING_INIT_A, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_INIT_A)};
const rf_packet_generic_3_byte_t rf_packet_init_b             = {RF_ID_SETTING, RF_SETTING_INIT_B, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_INIT_B)};
const rf_packet_generic_3_byte_t rf_packet_init_c             = {RF_ID_SETTING, RF_SETTING_INIT_C, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_INIT_C)};
const rf_packet_generic_3_byte_t rf_packet_profile_dongle_2_4 = {RF_ID_SETTING, RF_SETTING_PROFILE_DONGLE, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PROFILE_DONGLE)};
const rf_packet_generic_3_byte_t rf_packet_profile_bt_1       = {RF_ID_SETTING, RF_SETTING_PROFILE_BT_1, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PROFILE_BT_1)};
const rf_packet_generic_3_byte_t rf_packet_profile_bt_2       = {RF_ID_SETTING, RF_SETTING_PROFILE_BT_2, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PROFILE_BT_2)};
const rf_packet_generic_3_byte_t rf_packet_profile_bt_3       = {RF_ID_SETTING, RF_SETTING_PROFILE_BT_3, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PROFILE_BT_3)};
const rf_packet_generic_3_byte_t rf_packet_profile_wired      = {RF_ID_SETTING, RF_SETTING_WIRED, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_WIRED)};
const rf_packet_generic_3_byte_t rf_packet_keep_alive         = {RF_ID_SETTING, RF_SETTING_KEEP_ALIVE, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_KEEP_ALIVE)};
const rf_packet_generic_3_byte_t rf_packet_via_in             = {RF_ID_VIA, 0x60, 0x20};
const rf_packet_generic_3_byte_t rf_packet_cmd_pair_a         = {RF_ID_SETTING, RF_SETTING_PAIR_A, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PAIR_A)};
const rf_packet_generic_3_byte_t rf_packet_cmd_pair_b         = {RF_ID_SETTING, RF_SETTING_PAIR_B, RF_PACKET_CHECKSUM(RF_ID_SETTING, RF_SETTING_PAIR_B)};

rf_packet_product_t rf_packet_bt_product = {
    .cmd            = RF_ID_PRODUCT_BT,
    .string_length  = sizeof(PRODUCT),
    .product_string = PRODUCT,
};

rf_packet_product_t rf_packet_dongle_product = {
    .cmd            = RF_ID_PRODUCT_DONGLE,
    .string_length  = sizeof(PRODUCT),
    .product_string = PRODUCT,
};

rf_packet_dongle_manufacturer_t rf_packet_dongle_manufacturer = {
    .cmd                 = RF_ID_MANUFACTURER_DONGLE,
    .string_length       = sizeof(MANUFACTURER),
    .manufacturer_string = MANUFACTURER,
};

rf_packet_vidpid_t rf_packet_vidpid = {
    .cmd = RF_ID_VID_PID,
    .vid = VENDOR_ID,
    .pid = PRODUCT_ID,
};
