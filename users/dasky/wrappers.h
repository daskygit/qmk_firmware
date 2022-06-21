// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ortho_4x12_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)
#define LAYOUT_split_4x6_3_wrapper(...) LAYOUT_split_4x6_3(__VA_ARGS__)
// clang-format off
#define KEYS_36(k) crbkd_adapt(k)
#define crbkd_adapt( \
   k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b  \
) \
   k10, k11, k12, k13, k14, k15,    k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25,    k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35,    k36, k37, k38, k39, k3a, k3b, \
                  k42, k43, k44,    k47, k48, k49

#define KEYS_34(k) cradio_adapt(k)
#define cradio_adapt( \
   k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b  \
) \
   k11, k12, k13, k14, k15,    k16, k17, k18, k19, k1a, \
   k21, k22, k23, k24, k25,    k26, k27, k28, k29, k2a, \
   k31, k32, k33, k34, k35,    k36, k37, k38, k39, k3a, \
                  k43, k44,    k47, k48

#define GRANDICEPS(k) grandiceps_adapt(k)
#define grandiceps_adapt( \
   k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b  \
) \
   k00, k01, k02, k03, k04, k05,            k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15,            k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25,            k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k45,  k46, k36, k37, k38, k39, k3a, k3b, \
             k40, k41, k42, k43, k44,  k47, k48, k49, k4a, k4b \

#define KEYS_48(k) planck_adapt(k)
#define planck_adapt( \
   k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b  \
) \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k45, k42, k43, k44,  k47, k48, k49,k46, k4a, k4b

#define KEYS_54(k) reverb_adapt(k)
#define reverb_adapt( \
   k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
   k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b  \
) \
   k00, k01, k02, k03, k04, k05,            k06, k07, k08, k09, k0a, k0b, \
   k10, k11, k12, k13, k14, k15,            k16, k17, k18, k19, k1a, k1b, \
   k20, k21, k22, k23, k24, k25,            k26, k27, k28, k29, k2a, k2b, \
   k30, k31, k32, k33, k34, k35,            k36, k37, k38, k39, k3a, k3b, \
                       k42, k43, k44,  k47, k48, k49


#define CTLNUBS     MT(MOD_LCTL, KC_NUBS)
#define ALTSPC      MT(MOD_LALT, KC_SPC)
#define ALTNUHS     MT(MOD_LALT, KC_NUHS)
#define LOWERL      LT(_LOWER, KC_TAB)
#define LOWERR      LT(_LOWER, KC_ENT)
#define RAISEL      LT(_RAISE, KC_BSPC)
#define RAISER      LT(_RAISE, KC_SPC)
#define ADJUSTR     LT(_ADJUST, KC_ENT)
#define ADJUSTL     MO(_ADJUST)
#define GAMETOG     TG(_GAMING)
#define COLETOG     TG(_COLEMAK)
#define WINR        LGUI(KC_R)
#define CC_UNDS     S(KC_MINS)
#define CC_PLUS     S(KC_EQL)
#define CTALDEL     LCA(KC_DEL)

#ifdef TAP_DANCE_ENABLE
#   define TDGAME      TD(TD_GAME)
#   define TDQUOT      TD(TD_QUOT)
#   define TDEVOL      TD(TDE_VOL)
#   define TDERGB      TD(TDE_RGB)
#else
#   define TDGAME      TG(_GAMING)
#   define TDQUOT      KC_QUOT
#   define TDEVOL      KC_MUTE
#   define TDERGB      RGB_TOG
#endif

#define MT_Z        SFT_T(KC_Z)
#define MT_SLSH     SFT_T(KC_SLSH)
#define MT_A        CTL_T(KC_A)
#define MT_SCLN     CTL_T(KC_SCLN)
#define MT_S        ALT_T(KC_S)
#define MT_L        ALT_T(KC_L)
#define MT_D        GUI_T(KC_D)
#define MT_K        GUI_T(KC_K)



#define QWERTY_L_TB KC_LALT, LOWERL , RAISEL
#define QWERTY_L_EX KC_MINS, CC_UNDS
#define QWERTY_L_EC TDEVOL

#define QWERTY_R_TB RAISER , LOWERR , ALTNUHS
#define QWERTY_R_EX CC_PLUS, KC_EQL
#define QWERTY_R_EC TDERGB

#define QWERTY \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,           KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_PSCR, \
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL , \
    CTLNUBS, MT_A   , MT_S   , MT_D   , KC_F   , KC_G   ,           KC_H   , KC_J   , MT_K   , MT_L   , MT_SCLN, KC_QUOT, \
    KC_LSFT, MT_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,           KC_N   , KC_M   , KC_COMM, KC_DOT , MT_SLSH, KC_RSFT , \
    QWERTY_L_EX     , QWERTY_L_TB     , QWERTY_L_EC     ,           QWERTY_R_EC     , QWERTY_R_TB     , QWERTY_R_EX

#define COLEMAK \
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, \
    _______, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,           KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______, \
    _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,           KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______, \
    _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,           KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______, \
    QWERTY_L_EX     , QWERTY_L_TB     , QWERTY_L_EC     ,           QWERTY_R_EC     , QWERTY_R_TB     , QWERTY_R_EX



#define GAMING_L_TB KC_LALT, KC_TAB , KC_BSPC
#define GAMING_L_EX _______, _______
#define GAMING_L_EC _______

#define GAMING_R_TB _______, _______, _______
#define GAMING_R_EX _______, _______
#define GAMING_R_EC _______

#define GAMING \
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, \
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,           KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL , \
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,           KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, TDQUOT , \
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,           KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDGAME , \
    GAMING_L_EX     , GAMING_L_TB     , GAMING_L_EC     ,           GAMING_R_EC     , GAMING_R_TB     , GAMING_R_EX



#define LOWER_L_TB ADJUSTL, ADJUSTL, _______
#define LOWER_L_EX _______, _______
#define LOWER_L_EC TDERGB

#define LOWER_R_TB _______, ADJUSTR, _______
#define LOWER_R_EX _______, _______
#define LOWER_R_EC _______

#define LOWER \
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, \
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,           KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______, \
    _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,           KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_PSCR, \
    _______, KC_MINS, KC_EQL , KC_NUHS, KC_LBRC, KC_RBRC,           KC_F11 , KC_F12 , KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT, \
    LOWER_L_EX     , LOWER_L_TB       , LOWER_L_EC      ,           LOWER_R_EC      , LOWER_R_TB      , LOWER_R_EX



#define RAISE_L_TB _______, XXXXXXX, XXXXXXX
#define RAISE_L_EX _______, _______
#define RAISE_L_EC KC_HOME

#define RAISE_R_TB KC_BTN1, ADJUSTR, KC_BTN2
#define RAISE_R_EX _______, _______
#define RAISE_R_EC KC_HOME

#define RAISE \
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, \
    KC_ESC , XXXXXXX, KC_BSPC, KC_UP  , KC_ENT , WINR   ,           KC_ACL0, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, _______, \
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX,           KC_ACL1, KC_MS_L, KC_MS_D, KC_MS_R, KC_PSCR, XXXXXXX, \
    _______, _______, _______, _______, _______, _______,           KC_ACL2, XXXXXXX, KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT, \
    RAISE_L_EX     , RAISE_L_TB       , RAISE_L_EC      ,           RAISE_R_EC      , RAISE_R_TB      , RAISE_R_EX



#define ADJUST_L_TB XXXXXXX, _______, XXXXXXX
#define ADJUST_L_EX _______, _______
#define ADJUST_L_EC TDERGB

#define ADJUST_R_TB XXXXXXX, _______, XXXXXXX
#define ADJUST_R_EX _______, _______
#define ADJUST_R_EC _______

#define ADJUST \
    _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, \
    XXXXXXX, QK_BOOT, EE_CLR , EH_LEFT, EH_RGHT, NK_TOGG,           CUS_VER, CUS_FLH, CUS_BLD, CUS_GEN, XXXXXXX, XXXXXXX, \
    XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,           EH_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, COLETOG, XXXXXXX, \
    XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,           EH_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, GAMETOG, XXXXXXX, \
    ADJUST_L_EX     , ADJUST_L_TB     , ADJUST_L_EC     ,           ADJUST_R_EC     , ADJUST_R_TB     , ADJUST_R_EX

// clang-format on
