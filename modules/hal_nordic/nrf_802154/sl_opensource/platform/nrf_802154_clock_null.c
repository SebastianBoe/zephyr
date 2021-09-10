/*
 * Copyright (c) 2020 - 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Temporary clock platform for nRF54 */

#include <platform/nrf_802154_clock.h>

#include <stdint.h>

void nrf_802154_clock_init(void)
{
	/* Intentionally empty. */
}

void nrf_802154_clock_deinit(void)
{
	/* Intentionally empty. */
}

void nrf_802154_clock_hfclk_start(void)
{
	nrf_802154_clock_hfclk_ready();
}

void nrf_802154_clock_hfclk_stop(void)
{

}

bool nrf_802154_clock_hfclk_is_running(void)
{
	return true;
}

void nrf_802154_clock_lfclk_start(void)
{
	nrf_802154_clock_lfclk_ready();
}

void nrf_802154_clock_lfclk_stop(void)
{

}

bool nrf_802154_clock_lfclk_is_running(void)
{
	return true;
}
