// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_I2C TRUE

#define HAL_USE_PWM TRUE

#define HAL_USE_PAL TRUE
#define PAL_USE_CALLBACKS TRUE

#include_next <halconf.h>
