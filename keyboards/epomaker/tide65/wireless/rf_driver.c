// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "uart.h"

#include "rf_driver.h"
#include "rf_packets.h"
#include "rf_reports.h"
#include "rf_internal.h"

host_driver_t  rf_host_driver  = {rf_keyboard_leds, rf_send_keyboard, rf_send_nkro, rf_send_mouse, rf_send_extra};
host_driver_t *usb_host_driver = NULL;

rf_config_t rf_runtime_config = {
    .vbus_detected       = false,
    .keyboard_leds_state = 0,
    .battery_level       = 0,
    .battery_charging    = false,
    .current_profile     = rf_profile_wired,
};

deferred_token rf_maintainence_task_token;

void keyboard_post_init_rf(void) {
#ifdef RF_DEBUG
    debug_enable = true;
#endif
    gpio_set_pin_input(USB_VBUS_PIN);             // voltage divided VIN
    gpio_set_pin_input_high(CHARGING_STATUS_PIN); // output from LP4056 (OPEN DRAIN) LOW is charging

    rf_packet_bt_product.checksum          = rf_generate_checksum((uint8_t *)&rf_packet_bt_product, sizeof(rf_packet_product_t) - 1);
    rf_packet_dongle_product.checksum      = rf_generate_checksum((uint8_t *)&rf_packet_dongle_product, sizeof(rf_packet_product_t) - 1);
    rf_packet_dongle_manufacturer.checksum = rf_generate_checksum((uint8_t *)&rf_packet_dongle_manufacturer, sizeof(rf_packet_dongle_manufacturer_t) - 1);
    rf_packet_vidpid.checksum              = rf_generate_checksum((uint8_t *)&rf_packet_vidpid, sizeof(rf_packet_vidpid_t) - 1);

    wait_ms(200); // wait for RF MCU power up
    uart_init(115200);
}

void housekeeping_task_rf(void) {
    static bool init_done = false;
    if (!init_done) {
        bool okay = rf_send_packet(rf_packet_init_a, 3, true);

        if (okay) {
            okay = rf_send_packet(rf_packet_init_b, 3, true);
        }
        if (okay) {
            okay = rf_send_packet(rf_packet_init_c, 3, true);
        }
        if (okay) {
            rf_switch_profile(rf_profile_dongle);
            rf_maintainence_task_token = defer_exec(RF_MAINTAINENCE_MS, rf_maintainence_task, NULL);
        }
        init_done = okay;
    } else {
        rf_receive_check();
    }
}

bool process_record_rf(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RF_BT1:
                rf_switch_profile(rf_profile_bt_1);
                return false;
            case RF_BT2:
                rf_switch_profile(rf_profile_bt_2);
                return false;
            case RF_BT3:
                rf_switch_profile(rf_profile_bt_3);
                return false;
            case RF_DONG:
                rf_switch_profile(rf_profile_dongle);
                return false;
            case RF_WIRE:
                rf_switch_profile(rf_profile_wired);
                return false;
            case RF_PR_1:
                rf_switch_profile(rf_profile_bt_1);
                rf_pair_bt();
                return false;
            case RF_PR_2:
                rf_switch_profile(rf_profile_bt_2);
                rf_pair_bt();
                return false;
            case RF_PR_3:
                rf_switch_profile(rf_profile_bt_3);
                rf_pair_bt();
                return false;
            case RF_PR_D:
                rf_switch_profile(rf_profile_dongle);
                rf_pair_dongle();
                return false;
        }
    }
    return true;
}

uint32_t rf_maintainence_task(uint32_t trigger_time, void *cb_arg) {
    rf_runtime_config.battery_charging = gpio_read_pin(CHARGING_STATUS_PIN);
    rf_runtime_config.vbus_detected    = gpio_read_pin(USB_VBUS_PIN);

    // #ifdef RF_DEBUG
    //     rf_dprintf("RF - Profile: ");
    //     switch (rf_runtime_config.current_profile) {
    //         case rf_profile_bt_1:
    //             rf_dprintf("BT1 ");
    //             break;
    //         case rf_profile_bt_2:
    //             rf_dprintf("BT2 ");
    //             break;
    //         case rf_profile_bt_3:
    //             rf_dprintf("BT3 ");
    //             break;
    //         case rf_profile_dongle:
    //             rf_dprintf("Dongle ");
    //             break;
    //         case rf_profile_wired:
    //             rf_dprintf("Wired ");
    //             break;
    //     }
    //     if (host_get_driver() == usb_host_driver) {
    //         rf_dprintf("Host: USB");
    //     }
    //     if (host_get_driver() == &rf_host_driver) {
    //         rf_dprintf("Host: RF");
    //         rf_dprintf(rf_runtime_config.rf_connected ? " Connnected" : " Disconnected");
    //     }
    //     rf_dprintf("\n");
    // #endif

    return rf_send_packet(rf_packet_keep_alive, 3, true) ? RF_MAINTAINENCE_MS : 100;
}

void rf_pair_bt(void) {
    if (rf_runtime_config.current_profile != rf_profile_wired && rf_runtime_config.current_profile != rf_profile_dongle) {
        // Select bt profile, send pair a, send bt product, send vid/pid, send pair b
        while (!rf_send_packet(rf_packet_cmd_pair_a, sizeof(rf_packet_cmd_pair_a), true))
            ;
        while (!rf_send_packet((uint8_t *)&rf_packet_bt_product, sizeof(rf_packet_bt_product), true))
            ;
        while (!rf_send_packet((uint8_t *)&rf_packet_vidpid, sizeof(rf_packet_vidpid), true))
            ;
        while (!rf_send_packet(rf_packet_cmd_pair_b, sizeof(rf_packet_cmd_pair_b), true))
            ;
    }
}

void rf_pair_dongle(void) {
    // Select dongle profile, send dongle manufacturer, send dongle product, send vid/pid, send pair a, send pair b
    if (rf_runtime_config.current_profile == rf_profile_dongle) {
        while (!rf_send_packet((uint8_t *)&rf_packet_dongle_manufacturer, sizeof(rf_packet_dongle_manufacturer), true))
            ;
        while (!rf_send_packet((uint8_t *)&rf_packet_dongle_product, sizeof(rf_packet_dongle_product), true))
            ;
        while (!rf_send_packet((uint8_t *)&rf_packet_vidpid, sizeof(rf_packet_vidpid), true))
            ;
        while (!rf_send_packet(rf_packet_cmd_pair_a, sizeof(rf_packet_cmd_pair_a), true))
            ;
        while (!rf_send_packet(rf_packet_cmd_pair_b, sizeof(rf_packet_cmd_pair_b), true))
            ;
    }
}

void rf_switch_profile(rf_profiles_t profile) {
    // if (rf_current_profile == profile) {
    //     return;
    // }

    if (profile == rf_profile_wired && !rf_runtime_config.vbus_detected) {
        return; // don't switch to usb if not connected
    }

    if (rf_runtime_config.current_profile == rf_profile_wired) {
        usb_host_driver = host_get_driver();
    }

    switch (profile) {
        case rf_profile_dongle:
            rf_send_packet(rf_packet_profile_dongle_2_4, 3, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_1:
            rf_send_packet(rf_packet_profile_bt_1, 3, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_2:
            rf_send_packet(rf_packet_profile_bt_2, 3, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_3:
            rf_send_packet(rf_packet_profile_bt_3, 3, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_wired:
            rf_send_packet(rf_packet_profile_wired, 3, true);
            host_set_driver(usb_host_driver);
            break;
    }
    rf_runtime_config.current_profile = profile;
}

uint8_t rf_keyboard_leds(void) {
    return rf_runtime_config.keyboard_leds_state;
}

void rf_send_keyboard(report_keyboard_t *report) {
    rf_report_keyboard_t rf_report = {
        .cmd      = 0xA1,
        .mods     = report->mods,
        .reserved = report->reserved,
        .keys     = {0},
    };
    memcpy(rf_report.keys, report->keys, RF_KEYBOARD_REPORT_KEYS);
    rf_report.checksum = rf_generate_checksum((uint8_t *)&rf_report, 9);
    rf_send_packet((uint8_t *)&rf_report, 10, true);
}

void rf_send_nkro(report_nkro_t *report) {
    static bool       sent_keyboard_last_report = false;
    uint8_t           top_key_count             = 0;
    report_nkro_t     temp_nkro                 = {0};
    report_keyboard_t temp_keyboard_report      = {0};

    rf_report_keyboard_t rf_report_keyboard = {
        .cmd      = 0xA1,
        .mods     = report->mods,
        .reserved = 0,
        .keys     = {0},
    };

    rf_report_nkro_t rf_nkro_report = {
        .cmd  = 0xA2,
        .bits = {0},
    };

    memcpy(temp_nkro.bits, report->bits, NKRO_REPORT_BITS);

    for (uint8_t i = RF_NKRO_REPORT_BYTES; i < NKRO_REPORT_BITS; i++) {
        top_key_count += __builtin_popcount(temp_nkro.bits[i]);
    }

    for (uint8_t i = 0; i < top_key_count; i++) {
        uint8_t temp_key;
        uint8_t n = RF_NKRO_REPORT_BYTES;

        for (; n < NKRO_REPORT_BITS && !temp_nkro.bits[n]; n++)
            ;
        temp_key = n << 3 | biton(temp_nkro.bits[n]);

        del_key_bit(&temp_nkro, temp_key);
        add_key_byte(&temp_keyboard_report, temp_key);
    }

    if (sent_keyboard_last_report || rf_report_keyboard.mods || top_key_count > 0) {
        if (sent_keyboard_last_report) {
            sent_keyboard_last_report = false;
        } else {
            sent_keyboard_last_report = true;
        }
        memcpy(rf_report_keyboard.keys, temp_keyboard_report.keys, RF_KEYBOARD_REPORT_KEYS);
        rf_report_keyboard.checksum = rf_generate_checksum((uint8_t *)&rf_report_keyboard, sizeof(rf_report_keyboard_t) - 1);
        rf_send_packet((uint8_t *)&rf_report_keyboard, sizeof(rf_report_keyboard_t), true);
    }

    memcpy(rf_nkro_report.bits, report->bits, RF_NKRO_REPORT_BYTES);
    rf_nkro_report.checksum = rf_generate_checksum((uint8_t *)&rf_nkro_report, sizeof(rf_report_nkro_t) - 1);
    rf_send_packet((uint8_t *)&rf_nkro_report, RF_NKRO_REPORT_BYTES + 2, true);
}

static inline uint8_t SYSTEM2RF(uint16_t usage) {
    switch (usage) {
        case SYSTEM_WAKE_UP:
            return 0x04;
        case SYSTEM_SLEEP:
            return 0x02;
        case SYSTEM_POWER_DOWN:
            return 0x01;
        default:
            return 0x00;
    }
}

void rf_send_extra(report_extra_t *report) {
    switch (report->report_id) {
        case REPORT_ID_CONSUMER:;
            rf_report_consumer_t consumer_report = {
                .cmd   = 0xA3,
                .usage = report->usage,
            };
            consumer_report.checksum = rf_generate_checksum((uint8_t *)&consumer_report, sizeof(rf_report_consumer_t) - 1);
            rf_send_packet((uint8_t *)&consumer_report, sizeof(rf_report_consumer_t), true);
            break;
        case REPORT_ID_SYSTEM:;
            rf_report_system_t system_report = {
                .cmd   = 0xA4,
                .usage = SYSTEM2RF(report->usage),
            };
            system_report.checksum = rf_generate_checksum((uint8_t *)&system_report, sizeof(rf_report_system_t) - 1);
            rf_send_packet((uint8_t *)&system_report, sizeof(rf_report_system_t), true);
            break;
    };
}

void rf_send_mouse(report_mouse_t *report) {
    rf_report_mouse_t mouse_report = {
        .cmd     = 0xA8,
        .buttons = report->buttons,
        .x       = report->x,
        .y       = report->y,
        .h       = report->h,
        .v       = report->v,
    };
    mouse_report.checksum = rf_generate_checksum((uint8_t *)&mouse_report, sizeof(rf_report_mouse_t) - 1);
    rf_send_packet((uint8_t *)&mouse_report, sizeof(rf_report_mouse_t), true);
}

bool rf_uart_look_for_ack(uint8_t packets_to_process) {
    for (uint8_t i = 0; i < packets_to_process; i++) {
        uint8_t receive_data[3] = {0};
        uart_receive_timeout(receive_data, 3, 10);
        if (rf_packet_is_ack(receive_data)) {
            return true;
        } else {
            rf_handle_packet(receive_data);
        }
    }
    return false;
}

void rf_handle_via(void) {
    uint8_t via_packet[36];
    via_packet[0] = rf_packet_via_in[0];
    via_packet[1] = rf_packet_via_in[1];
    via_packet[2] = rf_packet_via_in[2];
    uart_receive_timeout(&via_packet[3], 33, 10);
    if (rf_packet_is_valid(via_packet, 36)) {
    }
    // do something with this
    //
}

uint8_t uart_read_timeout(uint8_t timeout) {
    return (uint8_t)sdGetTimeout(&UART_DRIVER, TIME_MS2I(timeout));
}

void uart_receive_timeout(uint8_t *data, uint16_t length, uint8_t timeout) {
    sdReadTimeout(&UART_DRIVER, data, length, TIME_MS2I(timeout));
}

bool rf_send_packet(uint8_t *data, uint8_t length, bool check_for_ack) {
    uart_transmit(data, length);
    return check_for_ack ? rf_uart_look_for_ack(2) : true;
}

bool rf_packet_is_ack(uint8_t *data) {
    return data[0] == rf_packet_ack[0] && data[1] == rf_packet_ack[1] && data[2] == rf_packet_ack[2];
}

uint8_t rf_generate_checksum(uint8_t *data, uint8_t length) {
    uint16_t sum = 0;
    for (uint8_t i = 0; i < length; i++) {
        sum += data[i];
    }
    return sum & 0xFF;
}

bool rf_packet_is_valid(uint8_t *data, uint8_t length) {
    if (data[0] + data[1] + data[2] > 0) {
        return data[length - 1] == rf_generate_checksum(data, length - 1);
    }
    return false;
}

void rf_handle_packet(uint8_t *packet) {
    if (rf_packet_is_valid(packet, 3)) {
        switch (packet[0]) {
            case 0x5A: // LED State
                rf_dprintf("RF LED State Update\n");
                rf_runtime_config.keyboard_leds_state = packet[1];
                uart_transmit(rf_packet_ack, 3);
                break;
            case 0x5B: // Status
                rf_dprintf("RF Status: ");
                switch (packet[1]) {
                    case 0x23: // alive
                        rf_dprintf("Alive\n");
                        break;
                    case 0x31: // last status after initiating pairing
                        rf_dprintf("Pairing mode?\n");
                        break;
                    case 0x32: // connected
                        rf_runtime_config.rf_connected = true;
                        rf_dprintf("Connected\n");
                        break;
                    case 0x33: // Not connected?
                        rf_runtime_config.rf_connected = false;
                        rf_dprintf("Diconnected\n");
                        break;
                    case 0x34: // happens after selecting another profile
                        rf_dprintf("Switching Profile\n");
                        break;
                    case 0x35: // happens before connected
                        rf_dprintf("Not connected?\n");
                        break;
                    case 0x37: // doesn't show for paired bt profiles
                        rf_dprintf("Not paired?\n");
                        break;
                    case 0x42: // only occurs when pairing a previous paired profile
                        rf_dprintf("Unpairing?\n");
                        break;
                    default:
                        rf_dprintf("0x%x\n", packet[1]);
                        break;
                }
                uart_transmit(rf_packet_ack, 3);
                break;
            case 0x5C: // Battery Level
                rf_runtime_config.battery_level = packet[1];
                // rf_dprintf("RF Battery Level: %d\n", rf_runtime_config.battery_level);
                uart_transmit(rf_packet_ack, 3);
                break;
            default:
                rf_dprintf("RF Valid Unhandled Packet: 0x%x 0x%x 0x%x\n", packet[0], packet[1], packet[2]);
                uart_transmit(rf_packet_ack, 3);
                break;
        }
    } else if (packet[0] == 0xAF) {
        rf_handle_via();
    } else {
        rf_dprintf("RF Invalid Packet: 0x%x 0x%x 0x%x\n", packet[0], packet[1], packet[2]);
    }
}

void rf_receive_check(void) {
    uint8_t receive_buffer[3] = {0};
    while (uart_available()) {
        uart_receive_timeout(receive_buffer, 3, 10);
        rf_handle_packet(receive_buffer);
    }
}
