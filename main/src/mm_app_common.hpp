/*
 * Copyright 2023 Morse Micro
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void app_wlan_init(void);

void app_wlan_start(void);

void app_wlan_stop(void);

void app_wlan_arp_send(void);

#ifdef __cplusplus
}
#endif
