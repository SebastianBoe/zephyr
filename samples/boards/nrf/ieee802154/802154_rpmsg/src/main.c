/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/sys/__assert.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include <nrf_802154_serialization_error.h>

void nrf_802154_serialization_error(const nrf_802154_ser_err_data_t *err)
{
	(void)err;
	__ASSERT(false, "802.15.4 serialization error");
}

void nrf_802154_sl_fault_handler(uint32_t id, int32_t line, const char *err)
{
	__ASSERT(false, "module_id: %u, line: %d, %s", id, line, err);
}

#if IS_ENABLED(CONFIG_SOC_PLATFORM_HALTIUM)

int check_status_flag(const struct device *arg)
{
	volatile uint8_t *p = (volatile uint8_t *) DT_REG_ADDR(DT_NODELABEL(gram00));

	/*
	 * Resetting the emulator doesn't also clear the memory. This means
	 * that from one run to another, the synchronization flag in the shared
	 * memory used by OpenAMP retains the old value. This causes the remote
	 * endpoint to wrongfully think that the host has already started
	 * causing mayhem and desperation for the poor dev soul trying to debug
	 * this. Reset the flag and make the remote core waiting until this is
	 * correctly set again before starting the sample.
	 */

	while (*p != 0x0)
		;

	return 0;
}
SYS_INIT(check_status_flag, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

#endif
