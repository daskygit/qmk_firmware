/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Elliot Powell @e11i0t23

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qp.h"
#include "qp_comms.h"
#include "qp_lvgl.h"
#include "printf.h"
#include "display/display.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init board:
// - Draw logo

void keyboard_post_init_kb(void) {
    display_init();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    display_housekeeping_task();
}
