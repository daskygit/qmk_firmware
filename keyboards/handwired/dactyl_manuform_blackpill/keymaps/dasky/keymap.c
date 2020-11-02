#include QMK_KEYBOARD_H
#include "tapdances.h"

enum layers { _QWERTY, _OTHER, _ADJUST };
enum custom_keycodes { PRTRATE = SAFE_RANGE };

#define CTLNUBS MT(MOD_LCTL, KC_NUBS)
#define ALTNUHS MT(MOD_RALT, KC_NUHS)
#define CTALDEL LCA(KC_DEL)
#define OTHERL LT(_OTHER, KC_BSPC)
#define OTHERR LT(_OTHER, KC_SPC)
#define ADJUST MO(_ADJUST)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
    KC_ESC  ,KC_1   ,KC_2   ,KC_3   ,KC_4  ,KC_5   ,                    KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_DEL ,
    KC_TAB  ,KC_Q   ,KC_W   ,KC_E   ,KC_R  ,KC_T   ,                    KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_MINS,
    CTLNUBS ,KC_A   ,KC_S   ,KC_D   ,KC_F  ,KC_G   ,                    KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
    TDLSFT  ,KC_Z   ,KC_X   ,KC_C   ,KC_V  ,KC_B   ,                    KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,TDRSFT ,
                     KC_LBRC,KC_RBRC,                                                   KC_PLUS,KC_EQL ,
                                    OTHERL ,KC_LGUI,                    KC_ENT ,OTHERR ,
                                             COPY   ,XXXXXXX,   XXXXXXX,ALTNUHS,
                                             PASTE  ,XXXXXXX,   XXXXXXX,KC_PSCR
  ),

  [_OTHER] = LAYOUT_5x6(
    KC_GRV,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,                    _______,_______,_______,_______,_______,_______,
    _______,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,                    KC_ACL0,_______,_______,_______,_______,_______,
    _______,_______,KC_BSPC,KC_UP  ,KC_ENT ,_______,                    KC_ACL1,_______,KC_MS_U,_______,_______,_______,
    _______,_______,KC_LEFT,KC_DOWN,KC_RGHT,_______,                    KC_ACL2,KC_MS_L,KC_MS_D,KC_MS_R,CTALDEL,_______,
                    KC_F11 ,KC_F12 ,                                                    KC_MPLY,KC_MNXT,
                                    ADJUST ,_______,                    KC_BTN1,ADJUST ,
                                            _______,_______,    _______,KC_BTN2,
                                            _______,_______,    _______,_______
  ),

  [_ADJUST] = LAYOUT_5x6(
    RESET  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                    PRTRATE,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,XXXXXXX,XXXXXXX,                    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,XXXXXXX,XXXXXXX,                    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                    XXXXXXX,XXXXXXX,                                                    XXXXXXX,XXXXXXX,
                                    _______,XXXXXXX,                    XXXXXXX,_______,
                                            XXXXXXX,XXXXXXX,    XXXXXXX,XXXXXXX,
                                            XXXXXXX,XXXXXXX,    XXXXXXX,XXXXXXX
  )

};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PRTRATE:
            if (record->event.pressed) {
                char buffer[5];
                itoa(get_matrix_scan_rate(), buffer, 10);
                send_string(buffer);
            }
            return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
