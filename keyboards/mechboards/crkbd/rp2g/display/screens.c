#include "screens.h"
#include "styles.h"
#include "qp_lvgl.h"
#include "printf.h"
#include "transactions.h"

lv_obj_t          *chart;
lv_obj_t          *img_scr;
lv_chart_series_t *ser;


int                vals       = 20;

void wpm_layer_display_init(void) {
    chart = lv_chart_create(lv_scr_act());
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, vals);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 150);
    lv_obj_set_size(chart, 80, 40);
    lv_obj_align(chart, LV_ALIGN_CENTER, 0, 40);

    ser = lv_chart_add_series(chart, lv_color_hex(0x30b1b6), LV_CHART_AXIS_PRIMARY_Y);
}
