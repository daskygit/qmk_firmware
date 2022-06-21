// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM5
#define STM32_PWM_USE_TIM5 TRUE

#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
