// Copyright 2021 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "dasky.h"
#include "transactions.h"
#include "user_sync.h"
#include <string.h>

void user_sync(bool force) {
    static user_config last_user_state;
    static bool        needs_sync = false;
    // Check if the state values are different
    if (memcmp(&user_state, &last_user_state, sizeof(user_config))) {
        needs_sync = true;
        memcpy(&last_user_state, &user_state, sizeof(user_config));
    }

    if (force) {
        needs_sync = true;
    }
    // Perform the sync if requested
    if (needs_sync) {
        needs_sync = !transaction_rpc_send(USER_SYNC_ID, sizeof(user_config), &user_state);
    }
}

void user_sync_aux_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, sizeof(user_config));
    }
}
