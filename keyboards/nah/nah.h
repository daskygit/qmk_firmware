// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

// clang-format off


#define LAYOUT( \
        L20, L10, L11, L01, L00, R00, R01, R11, R10, R20, \
        L21, L31, L30, L40, L41, R41, R40, R30, R31, R21, \
        L80, L60, L61, L51, L50, R50, R51, R61, R60, R80, \
                       L71, L70, R70, R71                 \
    ) \
    { \
        { L00, L01 }, \
        { L10, L11 }, \
        { L20, L21 }, \
        { L30, L31 }, \
        { L40, L41 }, \
        { L50, L51 }, \
        { L60, L61 }, \
        { L70, L71 }, \
        { L80, KC_NO }, \
        { R00, R01 }, \
        { R10, R11 }, \
        { R20, R21 }, \
        { R30, R31 }, \
        { R40, R41 }, \
        { R50, R51 }, \
        { R60, R61 }, \
        { R70, R71 }, \
        { R80, KC_NO }, \
    }
// clang-format on
