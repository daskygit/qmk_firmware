/* Copyright 2020 Dasky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stinky.h"

void led_left_off(void) { writePinHigh(LED_LEFT); }

void led_left_on(void) { writePinLow(LED_LEFT); }

void led_right_off(void) { writePinHigh(LED_RIGHT); }

void led_right_on(void) { writePinLow(LED_RIGHT); }

#ifndef BACKLIGHT_ENABLE
void led_power_on(void) { writePinLow(LED_POWER); }

void led_power_off(void) { writePinHigh(LED_POWER); }
#endif

void keyboard_pre_init_kb(void) {
// Set the LED pins as output
#ifndef BACKLIGHT_ENABLE
    setPinOutput(LED_POWER);
    led_power_on();
#endif
    setPinOutput(LED_LEFT);
    setPinOutput(LED_RIGHT);
    led_left_off();
    led_right_off();
}

#ifdef BACKLIGHT_ENABLE
void keyboard_post_init_kb(void) {
    backlight_enable();
#    ifdef BACKLIGHT_ENABLE
    breathing_enable();
#    endif
}
#endif