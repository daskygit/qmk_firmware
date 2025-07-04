#include "qp.h"
#include "qp_lvgl.h"

void spotify_display_init(void);
void gif_display_init(void);
void pc_layer_wpm_display_init(void);
void clock_display_init(void);
void wpm_layer_display_init(void);

lv_obj_t *label_wpm;
lv_obj_t *label_time;
lv_obj_t *label_cpu;
lv_obj_t *bar_cpu;
lv_obj_t *label_gpu;
lv_obj_t *bar_gpu;
lv_obj_t *label_ram;
lv_obj_t *bar_ram;

lv_obj_t *label_layer;
lv_obj_t *label_layer_now;
lv_obj_t *label_track;
lv_obj_t *chart;
lv_obj_t *album_art;
lv_obj_t *progress;
lv_obj_t *layer_btn_matrix;
lv_obj_t *gif;

lv_chart_series_t *ser;

uint8_t LV_ATTRIBUTE_MEM_ALIGN lv_scr[25604];
uint8_t LV_ATTRIBUTE_MEM_ALIGN lv_mb_map[8192];

lv_img_dsc_t scr;
lv_img_dsc_t mb;

int vals;
