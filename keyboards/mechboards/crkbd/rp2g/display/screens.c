#include "screens.h"
#include "styles.h"
#include "qp_lvgl.h"
#include "printf.h"
#include "transactions.h"

lv_obj_t          *chart;
lv_obj_t          *img_scr;
lv_chart_series_t *ser;

// Settings for full size screen image
LV_ATTRIBUTE_MEM_ALIGN uint8_t lv_scr[25604];

lv_img_dsc_t scr = {
    .header.cf          = LV_IMG_CF_TRUE_COLOR,
    .header.always_zero = 0,
    .header.reserved    = 0,
    .header.w           = 80,
    .header.h           = 160,
    .data_size          = 25604,
    .data               = lv_scr,
};

int                vals       = 20;

void wpm_layer_display_init(void) {
    /*WPM chart and Label*/
    label_wpm = lv_label_create(lv_scr_act());
    lv_label_set_text(label_wpm, "WPM:0");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label_wpm, LV_ALIGN_CENTER, 0, 5);

    chart = lv_chart_create(lv_scr_act());
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(chart, vals);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 150);
    lv_obj_set_style_pad_column(chart, 0.1, 0);
    lv_obj_set_size(chart, 80, 40);
    lv_obj_align(chart, LV_ALIGN_CENTER, 0, 40);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_X, 0, 0, 0, 0, 0, 0);
    lv_chart_set_axis_tick(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 0, 0, 0, 0, 0);

    ser = lv_chart_add_series(chart, lv_color_hex(0x30b1b6), LV_CHART_AXIS_PRIMARY_Y);
    lv_obj_set_style_size(chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_size(chart, 3, LV_PART_ITEMS);

    lv_obj_add_style(chart, &style_chart, LV_PART_MAIN);
}
