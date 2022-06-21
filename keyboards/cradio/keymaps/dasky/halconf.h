// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define HAL_USE_SERIAL TRUE
#define HAL_USE_I2C TRUE

#define HAL_USE_PAL TRUE
#define PAL_USE_CALLBACKS TRUE
#define PAL_USE_WAIT TRUE

#define SERIAL_BUFFERS_SIZE 256

#include_next <halconf.h>
