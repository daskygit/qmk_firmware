// Copyright 2023 Dasky (@Dasky)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define LED_LEFT B7
#define LED_RIGHT C7

#ifdef BACKLIGHT_ENABLE
#    define BACKLIGHT_PIN C6
#    define BACKLIGHT_LEVELS 3
#    define BACKLIGHT_BREATHING
#    define BREATHING_PERIOD 10
#    define BACKLIGHT_ON_STATE 0
#else
#    define LED_POWER C6
#endif