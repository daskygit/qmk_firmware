#include "styles.h"
#include "qp_lvgl.h"

// WPM Chart
lv_style_t style_chart;

void init_styles(void) {
    // WPM Chart
    lv_style_init(&style_chart);
    lv_style_set_bg_color(&style_chart, lv_color_hex(0x000000));
    lv_style_set_line_width(&style_chart, 0);
    lv_style_set_border_width(&style_chart, 0);
}
