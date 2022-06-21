// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "nah.h"
#include "sensors/pimoroni_trackball.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
        {  0,  1 }, \
        {  3,  2 }, \
        {  4,  5 }, \
        {  7,  6 }, \
        {  8,  9 }, \
        { 10, 11 }, \
        { 13, 12 }, \
        { 16, 15 }, \
        { 14, 17 }, \
        { 18, 19 }, \
        { 21, 20 }, \
        { 22, 23 }, \
        { 25, 24 }, \
        { 26, 27 }, \
        { 28, 29 }, \
        { 31, 30 }, \
        { 34, 33 }, \
        { 32, 35 }
}, {
  {  84, 10 }, {  67,  8 }, {  50,  4 }, {  29,  8 }, {   9, 19 },
  {  13, 31 }, {  31, 20 }, {  50, 16 }, {  67, 21 }, {  84, 23 },
  {  84, 35 }, {  67, 33 }, {  50, 28 }, {  33, 33 }, {  17, 43 },
  {  80, 50 }, {  99, 52 }, {  60, 53 },
  { 139, 10 }, { 156,  8 }, { 173,  4 }, { 194,  8 }, { 214, 19 },
  { 210, 31 }, { 193, 20 }, { 173, 16 }, { 156, 21 }, { 139, 23 },
  { 139, 35 }, { 156, 33 }, { 173, 28 }, { 191, 33 }, { 207, 43 },
  { 143, 50 }, { 124, 52 }, { 163, 52 }
}, {
  4,4,4,4,4,
  4,4,4,4,4,
  4,4,4,4,4,
  1,1,1,
  4,4,4,4,4,
  4,4,4,4,4,
  4,4,4,4,4,
  1,1,1
} };
#endif
// clang-format on

#ifdef RGB_MATRIX_ENABLE
extern LED_TYPE rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];

void rgb_matrix_indicators_kb(void) { pimoroni_trackball_set_rgbw(rgb_matrix_ws2812_array[17].r, rgb_matrix_ws2812_array[17].g, rgb_matrix_ws2812_array[17].b, 0); }
#endif

#if defined(RGBLIGHT_ENABLE)
void rgblight_call_driver(LED_TYPE* start_led, uint8_t num_leds) {
    pimoroni_trackball_set_rgbw(start_led[1].r, start_led[1].g, start_led[1].b, 0);

    ws2812_setleds(start_led, num_leds);
}
#endif
