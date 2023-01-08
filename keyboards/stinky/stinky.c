// Copyright 2023 Dasky (@Dasky)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void led_left_off(void) {
    writePinHigh(LED_LEFT);
}

void led_left_on(void) {
    writePinLow(LED_LEFT);
}

void led_right_off(void) {
    writePinHigh(LED_RIGHT);
}

void led_right_on(void) {
    writePinLow(LED_RIGHT);
}

#ifndef BACKLIGHT_ENABLE
void led_power_on(void) {
    writePinLow(LED_POWER);
}

void led_power_off(void) {
    writePinHigh(LED_POWER);
}
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

void bootloader_jump(void) {
    cli();
    UDCON  = 1;
    USBCON = (1 << FRZCLK); // disable USB
    UCSR1B = 0;
    _delay_ms(5);
    EIMSK  = 0;
    PCICR  = 0;
    SPCR   = 0;
    ACSR   = 0;
    EECR   = 0;
    TIMSK0 = 0;
    TIMSK1 = 0;
    UCSR1B = 0;
    DDRB   = 0;
    DDRC   = 0;
    DDRD   = 0;
    PORTB  = 0;
    PORTC  = 0;
    PORTD  = 0;
    asm volatile("jmp 0x38be");
}
