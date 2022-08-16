/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <string.h>
#include <logging/log.h>

#include <openthread/platform/entropy.h>

#if defined(CONFIG_ENTROPY_HAS_DRIVER)
#include <drivers/entropy.h>
#include "platform-zephyr.h"

#else
#warning OpenThread uses NOT SAFE random generator due to lack of Entropy Driver on the device!
	/* This is temporary fix to allow working nRF54 FPGA devices with OpenThread samples.
	 * It should be removed after adding a pseudo-entropy device
	 * like for the net-core in ic-next.
	 */
#include <random/rand32.h>
#endif

LOG_MODULE_REGISTER(net_otPlat_entropy, CONFIG_OPENTHREAD_L2_LOG_LEVEL);

static const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_entropy));

otError otPlatEntropyGet(uint8_t *aOutput, uint16_t aOutputLength)
{
#if defined(CONFIG_ENTROPY_HAS_DRIVER)
	int err;

	if ((aOutput == NULL) || (aOutputLength == 0)) {
		return OT_ERROR_INVALID_ARGS;
	}

	if (!device_is_ready(dev)) {
		LOG_ERR("Entropy device not ready");
		return OT_ERROR_FAILED;
	}

	err = entropy_get_entropy(dev, aOutput, aOutputLength);
	if (err != 0) {
		LOG_ERR("Failed to obtain entropy, err %d", err);
		return OT_ERROR_FAILED;
	}
#else
	sys_rand_get(aOutput, aOutputLength);
#endif
	return OT_ERROR_NONE;
}
