
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
int     currwpm      = 0;
int     lastwpm      = 0;
int     timer        = 0;
int     count        = 0;
bool    updating_wpm = true;
int     currlay      = 0;
int     lastlay      = 0;
uint8_t currScreen   = 0xFF;

// button style is going to be no background and no border, with individual buttons on a grey background with padding and rounded edges, mb_col if checked, equally spaced with white text across our 80*25

void display_housekeeping_task(void) {
    // Update WPM every 5 seconds
    if (timer_elapsed(timer) > 1000) {
        updating_wpm = true;
        timer        = timer_read();
        lastwpm      = currwpm;
        currwpm      = get_current_wpm();
        // If current WPM is the same as the last WPM, we will update the chart with the same value.
        // Once we have the chart filled completly with the same one we stop updating it.
        if (currwpm == lastwpm) {
            count++;
            if (count < vals) {
                lv_chart_set_next_value(chart, ser, currwpm);
            }
        } else {
            count = 0;
            lv_label_set_text_fmt(label_wpm, "WPM:%d", currwpm);

            lv_chart_set_next_value(chart, ser, currwpm);
        }
        updating_wpm = false;
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

    if (master)
        draw_screen(0);
    else
        draw_screen(0);
}

void draw_screen(uint8_t screen) {
    lv_obj_clean(lv_scr_act());

    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);

    wpm_layer_display_init();

    img_scr = lv_img_create(lv_scr_act());
}
