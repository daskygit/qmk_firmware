// Copyright 2022 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "reverb.h"
#include "test.qgf.h"

painter_device_t       reverb_display;
painter_image_handle_t avatar_image;

void keyboard_post_init_kb(void) {
    reverb_display = qp_gc9a01_make_spi_device(240, 240, DISPLAY_CS, DISPLAY_DC, DISPLAY_RST, 8, 0);
    qp_init(reverb_display, QP_ROTATION_0);
    avatar_image = qp_load_image_mem(gfx_test);
    qp_drawimage(reverb_display, 0, 0, avatar_image);
    qp_flush(reverb_display);
    keyboard_post_init_user();
}