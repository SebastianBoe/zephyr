/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <flash.h>

#include "platform-zephyr.h"

static struct device *flash_dev;
static size_t ot_flash_size;
static size_t ot_flash_offset;

static inline uint32_t mapAddress(uint32_t aAddress)
{
	return aAddress + ot_flash_offset;
}

otError utilsFlashInit(void)
{
	int i;
	struct flash_pages_info info;
	size_t pages_count;

	flash_dev = device_get_binding(
			CONFIG_OT_PLAT_FLASH_DEVICE_NAME);

	if (!flash_dev) {
		return OT_ERROR_NOT_IMPLEMENTED;
	}
	
	pages_count = flash_get_page_count(flash_dev);

	if (flash_get_page_info_by_idx(flash_dev,
		pages_count - CONFIG_OT_PLAT_FLASH_PAGES_COUNT - 1, &info)) {

		return OT_ERROR_FAILED;
	}

	ot_flash_offset = info.start_offset;
	ot_flash_size = 0;

	for (i = 0; i < CONFIG_OT_PLAT_FLASH_PAGES_COUNT; i++) {
		if (flash_get_page_info_by_idx(flash_dev,
			pages_count - i - 1, &info)) {
	
			return OT_ERROR_FAILED;
		}
		ot_flash_size += info.size;
	}

	return OT_ERROR_NONE;
}

uint32_t utilsFlashGetSize(void)
{
	return ot_flash_size;
}

otError utilsFlashErasePage(uint32_t aAddress)
{
	struct flash_pages_info info;
	uint32_t address;
	
	address = mapAddress(aAddress);
	if (flash_get_page_info_by_offs(flash_dev, address, &info)) {
		return OT_ERROR_FAILED;
	}

	if (flash_erase(flash_dev, address, info.size)) {
		return OT_ERROR_FAILED;
	}

	return OT_ERROR_NONE;
}

otError utilsFlashStatusWait(uint32_t aTimeout)
{
	ARG_UNUSED(aTimeout);

	return OT_ERROR_NONE;
}

uint32_t utilsFlashWrite(uint32_t aAddress, uint8_t *aData, uint32_t aSize)
{
	uint32_t index = 0;

	flash_write_protection_set(flash_dev, false);
	if (!flash_write(flash_dev, mapAddress(aAddress), aData, aSize)) {
		index = aSize;
	}
	flash_write_protection_set(flash_dev, true);

	return index;
}

uint32_t utilsFlashRead(uint32_t aAddress, uint8_t *aData, uint32_t aSize)
{
	uint32_t index = 0;

	if (!flash_read(flash_dev, mapAddress(aAddress), aData, aSize)) {
		index = aSize;
	}

	return index;
}
