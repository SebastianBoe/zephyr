/*
 * Copyright (c) 2020 - 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *   This file contains implementation of the nRF 802.15.4 GPIOTE abstraction.
 *
 * This implementation is intended to be used in bare-metal applications. Developer of such application can:
 * - use this implementation unmodified when GPIOTE peripheral is to be used only by the nRF 802.15.4 Radio Driver
 * - use this implementation as a reference for developing own platform port. In this case additional code can be put in GPIOTE_IRQHandler
 *   allowing handling interrupts coming from sources not related to nRF 802.15.4 driver.
 *
 */

#include "platform/nrf_802154_gpiote.h"

void nrf_802154_gpiote_init(void)
{

}

void nrf_802154_gpiote_deinit(void)
{

}

void GPIOTE_IRQHandler(void)
{

}
