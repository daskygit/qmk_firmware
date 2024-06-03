// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum {
    RF_BT1 = QK_KB,
    RF_BT2,
    RF_BT3,
    RF_DONG,
    RF_WIRE,
    RF_PR_1,
    RF_PR_2,
    RF_PR_3,
    RF_PR_D,
    RF_SAFE,
} rf_keycodes;

typedef enum {
    rf_profile_bt_1,
    rf_profile_bt_2,
    rf_profile_bt_3,
    rf_profile_dongle,
    rf_profile_wired,
} rf_profiles_t;

typedef struct {
    bool          rf_connected;
    bool          vbus_detected;
    uint8_t       keyboard_leds_state;
    uint8_t       battery_level;
    uint8_t       battery_charging;
    rf_profiles_t current_profile;
} rf_config_t;

void housekeeping_task_rf(void);
void keyboard_post_init_rf(void);
bool process_record_rf(uint16_t keycode, keyrecord_t *record);

void rf_switch_profile(rf_profiles_t profile);

bool    is_battery_charging(void);
uint8_t battery_level(void);

void rf_pair_bt(void);
void rf_pair_dongle(void);
