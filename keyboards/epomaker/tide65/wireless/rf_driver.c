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
    .pairing             = false,
};

deferred_token rf_maintainence_task_token;

// void rf_set_leds(uint8_t leds) {
//     rf_runtime_config.keyboard_leds_state = leds;
// }

const char *rf_status_to_string(rf_status_ids_t status) {
    switch (status) {
        case RF_STATUS_ALIVE:
            return "Alive";
        case RF_STATUS_PAIRING:
            return "Pairing";
        case RF_STATUS_CONNECTED:
            return "Connected";
        case RF_STATUS_DISCONNECTED:
            return "Disconnected";
        case RF_STATUS_SWITCHING_PROFILE:
            return "Switching Profile";
        case RF_STATUS_NOT_CONNECTED:
            return "Not connected";
        case RF_STATUS_NOT_PAIRED:
            return "Not paired";
        case RF_STATUS_UNPAIRING:
            return "Unpairing";
        case RF_STATUS_UNKNOWN:
            return "0x42";
        default:
            return "Undefined";
    }
}

uint8_t rf_get_leds(void) {
    return rf_runtime_config.keyboard_leds_state;
}

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
        bool okay = rf_send_packet(&rf_packet_init_a, true);

        if (okay) {
            okay = rf_send_packet(&rf_packet_init_b, true);
        }
        if (okay) {
            okay = rf_send_packet(&rf_packet_init_c, true);
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
    rf_runtime_config.battery_charging = !gpio_read_pin(CHARGING_STATUS_PIN);
    rf_runtime_config.vbus_detected    = gpio_read_pin(USB_VBUS_PIN);

#ifdef RF_DEBUG
    rf_dprintf("RF Profile: ");
    switch (rf_runtime_config.current_profile) {
        case rf_profile_bt_1:
            rf_dprintf("BT1 ");
            break;
        case rf_profile_bt_2:
            rf_dprintf("BT2 ");
            break;
        case rf_profile_bt_3:
            rf_dprintf("BT3 ");
            break;
        case rf_profile_dongle:
            rf_dprintf("Dongle ");
            break;
        case rf_profile_wired:
            rf_dprintf("Wired ");
            break;
    }
    if (host_get_driver() == usb_host_driver) {
        rf_dprintf("Host: USB");
    }
    if (host_get_driver() == &rf_host_driver) {
        rf_dprintf(" - Host: RF");
        rf_dprintf(rf_runtime_config.rf_connected ? " Connnected" : " Disconnected");
        rf_dprintf(" - Last status: ");
        rf_dprintf(rf_status_to_string(rf_runtime_config.last_status));
    }
    rf_dprintf("\n");
#endif

    return rf_send_packet(&rf_packet_keep_alive, true) ? RF_MAINTAINENCE_MS : 100;
}

void rf_pair_bt(void) {
    if (rf_runtime_config.current_profile != rf_profile_wired && rf_runtime_config.current_profile != rf_profile_dongle) {
        // Select bt profile, send pair a, send bt product, send vid/pid, send pair b
        while (!rf_send_data((uint8_t *)&rf_packet_cmd_pair_a, sizeof(rf_packet_cmd_pair_a), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_bt_product, sizeof(rf_packet_bt_product), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_vidpid, sizeof(rf_packet_vidpid), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_cmd_pair_b, sizeof(rf_packet_cmd_pair_b), true))
            ;
    }
}

void rf_pair_dongle(void) {
    // Select dongle profile, send dongle manufacturer, send dongle product, send vid/pid, send pair a, send pair b
    if (rf_runtime_config.current_profile == rf_profile_dongle) {
        while (!rf_send_data((uint8_t *)&rf_packet_dongle_manufacturer, sizeof(rf_packet_dongle_manufacturer), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_dongle_product, sizeof(rf_packet_dongle_product), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_vidpid, sizeof(rf_packet_vidpid), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_cmd_pair_a, sizeof(rf_packet_cmd_pair_a), true))
            ;
        while (!rf_send_data((uint8_t *)&rf_packet_cmd_pair_b, sizeof(rf_packet_cmd_pair_b), true))
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
            rf_send_packet(&rf_packet_profile_dongle_2_4, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_1:
            rf_send_packet(&rf_packet_profile_bt_1, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_2:
            rf_send_packet(&rf_packet_profile_bt_2, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_bt_3:
            rf_send_packet(&rf_packet_profile_bt_3, true);
            host_set_driver(&rf_host_driver);
            rf_runtime_config.rf_connected = false;
            break;
        case rf_profile_wired:
            rf_send_packet(&rf_packet_profile_wired, true);
            host_set_driver(usb_host_driver);
            break;
    }
    rf_runtime_config.current_profile = profile;
}

bool rf_uart_look_for_ack(uint8_t packets_to_process) {
    for (uint8_t i = 0; i < packets_to_process; i++) {
        rf_packet_generic_3_byte_t packet = {0};
        uart_receive_timeout((uint8_t *)&packet, 3, 10);
        if (rf_packet_is_ack(&packet)) {
            return true;
        } else {
            rf_handle_packet(&packet);
        }
    }
    return false;
}

void rf_handle_via(void) {
    uint8_t via_packet[36];
    via_packet[0] = rf_packet_via_in.cmd;
    via_packet[1] = rf_packet_via_in.data;
    via_packet[2] = rf_packet_via_in.checksum; // not actually checksum for via
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

bool rf_send_packet(const rf_packet_generic_3_byte_t *packet, bool check_for_ack) {
    uart_transmit((uint8_t *)packet, sizeof(rf_packet_generic_3_byte_t));
    return check_for_ack ? rf_uart_look_for_ack(2) : true;
}

bool rf_send_data(uint8_t *data, uint8_t length, bool check_for_ack) {
    uart_transmit(data, length);
    return check_for_ack ? rf_uart_look_for_ack(2) : true;
}

bool rf_packet_is_ack(rf_packet_generic_3_byte_t *packet) {
    return packet->cmd == rf_packet_ack.cmd && packet->data == rf_packet_ack.data && packet->checksum == rf_packet_ack.checksum;
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

void rf_handle_packet(rf_packet_generic_3_byte_t *packet) {
    if (rf_packet_is_valid((uint8_t *)packet, 3)) {
        switch ((rf_message_ids_t)packet->cmd) {
            case RF_ID_LED_STATE:
                rf_dprintf("RF LED State Update\n");
                rf_runtime_config.keyboard_leds_state = packet->data;
                rf_send_packet(&rf_packet_ack, false);
                break;
            case RF_ID_STATUS:
                if (packet->data != RF_STATUS_ALIVE) {
                    rf_runtime_config.last_status = packet->data;
                    rf_dprintf("RF Received Status: ");
                    rf_dprintf(rf_status_to_string((rf_status_ids_t)packet->data));
                    rf_dprintf("\n");
                }
                switch ((rf_status_ids_t)packet->data) {
                    case RF_STATUS_ALIVE:
                        // rf_dprintf(rf_status_to_string((rf_status_ids_t)packet->data));
                        break;
                    case RF_STATUS_PAIRING:
                        rf_runtime_config.pairing = true;
                        break;
                    case RF_STATUS_CONNECTED:
                        rf_runtime_config.pairing      = false;
                        rf_runtime_config.rf_connected = true;
                        break;
                    case RF_STATUS_DISCONNECTED:
                        rf_runtime_config.rf_connected = false;
                        break;
                    case RF_STATUS_SWITCHING_PROFILE:
                        rf_runtime_config.pairing = true;
                        break;
                    case RF_STATUS_NOT_CONNECTED:
                        rf_runtime_config.rf_connected = false;
                        break;
                    case RF_STATUS_NOT_PAIRED:
                        break;
                    case RF_STATUS_UNPAIRING:
                        rf_runtime_config.pairing = true;
                        break;
                    case RF_STATUS_UNKNOWN:
                        break;
                    default:
                        break;
                }
                rf_send_packet(&rf_packet_ack, false);
                break;
            case RF_ID_BATTERY_LEVEL: // Battery Level
                rf_runtime_config.battery_level = packet->data;
                rf_dprintf("RF Battery Level: %d Charging: ", rf_runtime_config.battery_level);
                rf_dprintf(rf_runtime_config.battery_charging ? "Yes\n" : "No\n");
                rf_send_packet(&rf_packet_ack, false);
                break;
            default:
                rf_dprintf("RF Valid Unhandled Packet: 0x%x 0x%x 0x%x\n", packet->cmd, packet->data, packet->checksum);
                rf_send_packet(&rf_packet_ack, false);
                break;
        }
    } else if (packet->cmd == RF_ID_VIA) {
        rf_handle_via();
    } else {
        rf_dprintf("RF Invalid Packet: 0x%x 0x%x 0x%x\n", packet->cmd, packet->data, packet->checksum);
    }
}

void rf_receive_check(void) {
    rf_packet_generic_3_byte_t packet = {0};
    while (uart_available()) {
        uart_receive_timeout((uint8_t *)&packet, sizeof(rf_packet_generic_3_byte_t), 10);
        rf_handle_packet(&packet);
    }
}
