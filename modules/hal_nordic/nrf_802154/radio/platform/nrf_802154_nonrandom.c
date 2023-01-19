/*
 * Copyright (c) 2019 - 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <platform/nrf_802154_temperature.h>
#include <zephyr/drivers/entropy.h>

static uint32_t state;

static uint32_t next(void)
{
	uint32_t num = state;

	state = 1664525 * num + 1013904223;
	return num;
}

void nrf_802154_random_init(void)
{
	state = 1;
}

void nrf_802154_random_deinit(void)
{
	/* Intentionally empty */
}

uint32_t nrf_802154_random_get(void)
{
	return next();
}
