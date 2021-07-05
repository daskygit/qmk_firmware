#pragma once

#define LEFT_FIRST_UNDERGLOW 0
#define LEFT_LAST_UNDERGLOW 5
#define LEFT_FIRST_RGB 6
#define LEFT_LAST_RGB 26

#define RIGHT_FIRST_UNDERGLOW 27
#define RIGHT_LAST_UNDERGLOW 32
#define RIGHT_FIRST_RGB 33
#define RIGHT_LAST_RGB 53

const uint8_t PROGMEM gaming_left[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 255, 0, 0, 255, 0, 0, 0, 0};

const uint8_t PROGMEM gaming_right[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 255, 255};

const uint8_t PROGMEM lower_left[] = {0, 0, 44, 44, 44, 44, 0, 0, 0, 0, 44, 44, 44, 44, 0, 0, 44, 44, 0, 0, 0};

const uint8_t PROGMEM lower_right[] = {0, 1, 1, 1, 1, 1, 1, 0, 0, 85, 1, 1, 1, 1, 43, 201, 1, 1, 0, 180, 0};

const uint8_t PROGMEM raise_left[] = {0, 0, 0, 0, 180, 0, 0, 0, 0, 0, 169, 85, 169, 169, 0, 0, 169, 1, 0, 0, 0};

const uint8_t PROGMEM raise_right[] = {169, 127, 127, 127, 0, 0, 0, 0, 169, 85, 169, 0, 169, 169, 43, 201, 169, 0, 0, 180, 0};

#ifdef HELLO
// clang-format off
const uint8_t PROGMEM hue_indicators[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
    CTLNUBS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    TDLSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDRSFT ,
                                        RAISEL , LOWERL , KC_BSPC,      KC_SPC , LOWERR , ALTNUHS
),

[_COLEMAK] = LAYOUT_split_3x6_3(
    _______, KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,                        KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, _______,
    _______, KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,                        KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , _______,
    _______, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_K   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                                        _______, _______, _______,      _______, _______, _______
),

[_GAMING] = LAYOUT_split_3x6_3(
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                        KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
    KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                        KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, TDQUOT ,
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                        KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDGAME ,
                                        KC_LALT, KC_TAB , KC_SPC ,      KC_SPC , KC_ENT , KC_NUHS
),

[_LOWER] = LAYOUT_split_3x6_3(
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                        KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , _______ ,
    _______, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,                        KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_PSCR,
    _______, KC_MINS, KC_EQL , KC_NUHS, KC_LBRC, KC_RBRC,                        KC_F11 , KC_F12 , KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT,
                                        ADJUSTL, ADJUSTL, _______,      _______, ADJUSTR, _______
),

[_RAISE] = LAYOUT_split_3x6_3(
    KC_ESC , KC_BSPC, KC_UP  , KC_ENT , WINR   , XXXXXXX,                        KC_ACL0, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,                        KC_ACL1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_PSCR,
    _______, UNDO   , CUT    , COPY   , PASTE  , SAVE   ,                        KC_ACL2, XXXXXXX, KC_MPLY, KC_MNXT, CTALDEL, KC_RSFT,
                                        _______, XXXXXXX, XXXXXXX,      KC_BTN1, ADJUSTR, KC_BTN2
),

[_ADJUST] = LAYOUT_split_3x6_3(
    RESET  , EEP_RST, XXXXXXX, XXXXXXX, XXXXXXX, NK_TOGG,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, EH_LEFT,                        EH_LEFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, COLETOG,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, EH_RGHT,                        EH_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAMETOG,
                                        XXXXXXX, _______, XXXXXXX,      XXXXXXX, _______, XXXXXXX
)
}
// clang-format on

#endif
// 19,18,13,12, 5, 4           4, 5,12,13,18,19
// 20,17,14,11, 6, 3           3, 6,11,14,17,20
// 21,16,15,10, 7, 2           2, 7,10,15,16,21
//             9, 8, 1     1, 8, 9

_Static_assert(sizeof(gaming_left) == 21, "gaming_left wrong size");
_Static_assert(sizeof(gaming_right) == 21, "gaming_right wrong size");
_Static_assert(sizeof(lower_left) == 21, "lower_left wrong size");
_Static_assert(sizeof(lower_right) == 21, "lower_right wrong size");
_Static_assert(sizeof(raise_left) == 21, "raise_left wrong size");
_Static_assert(sizeof(raise_right) == 21, "raise_right wrong size");
