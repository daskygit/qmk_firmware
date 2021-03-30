#pragma once

#include "quantum.h"

#pragma pack(push)
#pragma pack(1)
typedef struct user_runtime_config {
    bool    oled_off_state : 1;
    bool    rgb_off_state : 1;
    uint8_t cpu_temp : 7;
    uint8_t cpu_load : 4;
    uint8_t gpu_temp : 7;
    uint8_t gpu_load : 4;
    bool blinking : 1;
    usbpd_allowance_t pd_setting : 2;
} user_runtime_config;

#pragma pack(pop)

_Static_assert(sizeof(user_runtime_config) == 4, "user_runtime_config wrong size");

user_runtime_config user_state;

enum layer_ids { _QWERTY, _COLEMAK, _GAMING, _LOWER, _RAISE, _ADJUST };

#define CTLNUBS MT(MOD_LCTL, KC_NUBS)
#define ALTSPC  MT(MOD_LALT, KC_SPC)
#define ALTNUHS MT(MOD_LALT, KC_NUHS)
#define CTALDEL LCA(KC_DEL)
#define LOWERL  LT(_LOWER, KC_TAB)
#define LOWERR  LT(_LOWER, KC_ENT)
#define RAISEL  LT(_RAISE, KC_LGUI)
#define ADJUSTR LT(_ADJUST, KC_ENT)
#define ADJUSTL MO(_ADJUST)
#define GAMETOG TG(_GAMING)
#define COLETOG TG(_COLEMAK)
#define UNDO    LCTL(KC_Z)
#define CUT     LCTL(KC_X)
#define COPY    LCTL(KC_C)
#define PASTE   LCTL(KC_V)
#define SAVE    LCTL(KC_S)
#define WINR    LGUI(KC_R)
