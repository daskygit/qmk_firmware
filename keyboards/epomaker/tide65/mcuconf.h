// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_SPI_USE_SPIM2
#define WB32_SPI_USE_SPIM2 TRUE

#undef WB32_SERIAL_USE_UART3
#define WB32_SERIAL_USE_UART3 TRUE
