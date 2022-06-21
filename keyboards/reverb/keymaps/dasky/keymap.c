// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dasky.h"
#include <lib/lib8tion/lib8tion.h>
#include "logo.qgf.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(QWERTY)),
    [_COLEMAK]  = LAYOUT_split_4x6_3_wrapper(KEYS_54(COLEMAK)),
    [_GAMING]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(GAMING)),
    [_LOWER]    = LAYOUT_split_4x6_3_wrapper(KEYS_54(LOWER)),
    [_RAISE]    = LAYOUT_split_4x6_3_wrapper(KEYS_54(RAISE)),
    [_ADJUST]   = LAYOUT_split_4x6_3_wrapper(KEYS_54(ADJUST))
};
// clang-format off


const char* magic_reponses[] = {
"It is certain",
"Without a doubt",
"You may rely on it",
"Yes definitely",
"It is decidedly so",
"As I see it, yes",
"Most likely",
"Yes",
"Outlook good",
"Signs point to yes",

"Reply hazy try again",
"Better not tell you now",
"Ask again later",
"Cannot predict now",
"Concentrate and ask again",

"Don’t count on it",
"Outlook not so good",
"My sources say no",
"Very doubtful",
"My reply is no"};

extern painter_device_t       reverb_display;
extern painter_image_handle_t avatar_image;

void show_avatar(void) {
    qp_drawimage(reverb_display, 0, 0, avatar_image);
    qp_flush(reverb_display);
}

uint32_t delayed_show_avatar(uint32_t trigger_time, void *cb_arg) {
    rgb_matrix_reload_from_eeprom();
    show_avatar();
    return 0;
}

void keyboard_post_init_keymap(void) {
    avatar_image = qp_load_image_mem(gfx_logo);
    // reverb_display = qp_gc9a01_make_spi_device(240, 240, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST, 4, 0);
    // qp_init(reverb_display, QP_ROTATION_0);
    defer_exec(5000,delayed_show_avatar,NULL);
}
 
deferred_token token_lvgl_detach =  INVALID_DEFERRED_TOKEN;

void reset_keyboard_status(void){
    lv_obj_clean(lv_scr_act());
    qp_lvgl_detach();
    show_avatar();
    rgb_matrix_reload_from_eeprom();
}

uint32_t delayed_display_detatch(uint32_t trigger_time, void *cb_arg) {
reset_keyboard_status();
    token_lvgl_detach = INVALID_DEFERRED_TOKEN;
    return 0;
}

void show_magicball(void)
{
    if (qp_lvgl_attach(reverb_display)){
        lv_obj_t * label;
        lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_PART_MAIN);
        lv_obj_t * btn1 = lv_btn_create(lv_scr_act());

        lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 0);
        label = lv_label_create(btn1);
        uint8_t random = random8_max(20);
        rgb_matrix_mode_noeeprom(1);
        switch (random){
            case 0 ... 9:
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                break;
            case 10 ... 14:
                rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
                break;
            default:
                rgb_matrix_sethsv_noeeprom(HSV_RED);
                break;
        }
        lv_label_set_text(label, magic_reponses[random]);
        lv_obj_center(label);
         lv_obj_set_style_bg_color(btn1, lv_color_white(), LV_PART_MAIN);
        lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
        token_lvgl_detach = defer_exec(2000,delayed_display_detatch,NULL);
        if (token_lvgl_detach == INVALID_DEFERRED_TOKEN){
reset_keyboard_status();
        }
    }
}

bool process_record_keymap(uint16_t keycode, keyrecord_t* record){
    switch (keycode) {
        case CUS_8BA:
            if (record->event.pressed){
                random16_add_entropy(timer_read());
                if (token_lvgl_detach == INVALID_DEFERRED_TOKEN ){
                show_magicball();
                }
                return false;
            }
    }
    return true;
}