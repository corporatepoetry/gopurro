/*
 * Copyright 2021-2023 Morse Micro
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstring>
#include <cstdio>
#include "mmwlan.h"
#include "mmipal.h"
#include "mmosal.h"
#include "mm_app_loadconfig.hpp"
#include "mmwlan_regdb.def"

#define COUNTRY_CODE "US"
#ifndef COUNTRY_CODE
#error COUNTRY_CODE must be defined to the appropriate 2 character country code. \
       See mmwlan_regdb.def for valid options.
#endif
#ifndef COUNTRY_CODE
#define COUNTRY_CODE "??"
#endif
#ifndef SSID
#define SSID InterzoneAH
#endif
#ifndef SAE_PASSPHRASE
#define SAE_PASSPHRASE 187killa
#endif
#ifndef SECURITY_TYPE
#define SECURITY_TYPE MMWLAN_SAE
#endif
#define ENABLE_DHCP (1)
#ifndef STATIC_LOCAL_IP
#define STATIC_LOCAL_IP "192.168.1.2"
#endif
#ifndef STATIC_GATEWAY
#define STATIC_GATEWAY "192.168.1.1"
#endif
#ifndef STATIC_NETMASK
#define STATIC_NETMASK "255.255.255.0"
#endif
#ifndef STATIC_LOCAL_IP6
#define STATIC_LOCAL_IP6 "FE80::2"
#endif
#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

extern "C" void load_mmipal_init_args(struct mmipal_init_args *args) {
    (void) mmosal_safer_strcpy(args->ip_addr, STATIC_LOCAL_IP, sizeof(args->ip_addr));
    (void) mmosal_safer_strcpy(args->netmask, STATIC_NETMASK, sizeof(args->netmask));
    (void) mmosal_safer_strcpy(args->gateway_addr, STATIC_GATEWAY, sizeof(args->gateway_addr));
#ifdef ENABLE_DHCP
    args->mode = MMIPAL_DHCP;
#else
    args->mode = MMIPAL_STATIC;
#endif
    if (args->mode == MMIPAL_DHCP) {
        printf("Initialize IPv4 using DHCP...\n");
    } else if (args->mode == 4) {
        printf("Initialize IPv4 using DHCP offload...\n");
    } else {
        printf("Initialize IPv4 with static IP: %s...\n", args->ip_addr);
    }
    (void) mmosal_safer_strcpy(args->ip6_addr, STATIC_LOCAL_IP6, sizeof(args->ip6_addr));
    args->ip6_mode = MMIPAL_IP6_AUTOCONFIG;
    if (args->ip6_mode == MMIPAL_IP6_AUTOCONFIG) {
        printf("Initialize IPv6 using Autoconfig...\n");
    } else {
        printf("Initialize IPv6 with static IP %s\n", args->ip6_addr);
    }
}

extern "C" const struct mmwlan_s1g_channel_list *load_channel_list(void) {
    char strval[16];
    const struct mmwlan_s1g_channel_list *channel_list;
    (void) mmosal_safer_strcpy(strval, COUNTRY_CODE, sizeof(strval));
    channel_list = mmwlan_lookup_regulatory_domain(get_regulatory_db(), strval);
    if (channel_list == nullptr) {
        printf("Could not find specified regulatory domain matching country code %s\n", strval);
        printf("Please set the configuration key wlan.country_code to the correct country code.\n");
        MMOSAL_ASSERT(false);
    }
    return channel_list;
}

extern "C" void load_mmwlan_sta_args(struct mmwlan_sta_args *sta_config) {
    (void) mmosal_safer_strcpy((char *) sta_config->ssid, STRINGIFY(SSID), sizeof(sta_config->ssid));
    sta_config->ssid_len = strlen((char *) sta_config->ssid);
    (void) mmosal_safer_strcpy(sta_config->passphrase, STRINGIFY(SAE_PASSPHRASE), sizeof(sta_config->passphrase));
    sta_config->passphrase_len = strlen(sta_config->passphrase);
    sta_config->security_type = SECURITY_TYPE;
}

extern "C" void load_mmwlan_settings(void) {
    // Implementation as in the original C file
}
