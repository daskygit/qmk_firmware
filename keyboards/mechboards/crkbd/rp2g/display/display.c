
#include "display.h"
#include "qp.h"
#include "qp_comms.h"
#include "qp_st77xx_opcodes.h"
#include "qp_lvgl.h"
#include "printf.h"
#include "transactions.h"
#include "screens.h"
#include "styles.h"

painter_device_t lcd;

bool    master;
int     timer        = 0;
int     count        = 0;

void display_housekeeping_task(void) {
    if (timer_elapsed(timer) > 1000) {
        timer = timer_read();
        lv_chart_set_next_value(chart, ser, 15);
    }
}

// This function is called when the master sends data to the slave, which is then processed with processes_command
void screen_sync_slave_handler(uint8_t length, const void *in_data, uint8_t out_buflen, void *out_data) {

}

void display_init(void) {
    master = is_keyboard_master();
    transaction_register_rpc(SCR_SLV_SYNC, screen_sync_slave_handler);
    timer = timer_read();
    uprintf("Post Init\n");
    wait_ms(LCD_WAIT_TIME);
    // Initialise the LCD
    lcd = qp_st7735_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, LCD_SPI_MODE);
    qp_init(lcd, LCD_ROTATION);

    // Apply Offset
    qp_set_viewport_offsets(lcd, LCD_OFFSET_X, LCD_OFFSET_Y);

// Invert Colour
#ifdef LCD_INVERT_COLOUR
    qp_comms_start(lcd);
    qp_comms_command(lcd, ST77XX_CMD_INVERT_ON);
    qp_comms_stop(lcd);
#endif

    if (!qp_lvgl_attach(lcd)) return;

    init_styles();

    lv_obj_clean(lv_scr_act());

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

    wpm_layer_display_init();

    img_scr = lv_img_create(lv_scr_act());
}
