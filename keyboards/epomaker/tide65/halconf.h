// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_SERIAL TRUE
#define SERIAL_BUFFERS_SIZE 64

#define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#define HAL_USE_PAL TRUE
#define PAL_USE_WAIT TRUE

#include_next <halconf.h>
