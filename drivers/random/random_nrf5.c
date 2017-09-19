/*
 * Copyright (c) 2017 Exati Tecnologia Ltda.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <random.h>
#include <atomic.h>
#include <nrf_rng.h>

struct random_nrf5_dev_data {
	atomic_t user_count;
};

#define DEV_DATA(dev) \
	((struct random_nrf5_dev_data *)(dev)->driver_data)

static inline s16_t random_nrf5_get_u8(void)
{
	u8_t value;

	while (!nrf_rng_event_get(NRF_RNG_EVENT_VALRDY)) {
		__WFE();
		__SEV();
		__WFE();
	}

	value = nrf_rng_random_value_get();

	nrf_rng_event_clear(NRF_RNG_EVENT_VALRDY);

	return value;
}

static int random_nrf5_get_entropy(struct device *device, u8_t *buf, u16_t len)
{
	int ret = 0;

	/* Mark the peripheral as being used */
	atomic_inc(&DEV_DATA(device)->user_count);

	/* Disable the shortcut that stops the task after a byte is generated */
	nrf_rng_shorts_disable(NRF_RNG_SHORT_VALRDY_STOP_MASK);

	/* Start the RNG generator peripheral */
	nrf_rng_task_trigger(NRF_RNG_TASK_START);

	while (len) {
		s16_t value = random_nrf5_get_u8();

		if (value < 0) {
			ret = value;
			break;
		}

		*buf = (u8_t) value;
		buf++;
		len--;
	}

	/* Only stop the RNG generator peripheral if we're the last user */
	if (atomic_dec(&DEV_DATA(device)->user_count) == 1) {
		/* Disable the peripheral on the next VALRDY event */
		nrf_rng_shorts_enable(NRF_RNG_SHORT_VALRDY_STOP_MASK);

		if (atomic_get(&DEV_DATA(device)->user_count) != 0) {
			/* Race condition: another thread started to use
			 * the peripheral while we were disabling it.
			 * Enable the peripheral again
			 */
			nrf_rng_shorts_disable(NRF_RNG_SHORT_VALRDY_STOP_MASK);
			nrf_rng_task_trigger(NRF_RNG_TASK_START);
		}
	}

	return ret;
}

static int random_nrf5_init(struct device *device)
{
	/* Enable or disable bias correction */
	if (IS_ENABLED(CONFIG_RANDOM_NRF5_BIAS_CORRECTION)) {
		nrf_rng_error_correction_enable();
	} else {
		nrf_rng_error_correction_disable();
	}

	/* Initialize the user count with zero */
	atomic_clear(&DEV_DATA(device)->user_count);

	return 0;
}

static struct random_nrf5_dev_data random_nrf5_data;

static const struct random_driver_api random_nrf5_api_funcs = {
	.get_entropy = random_nrf5_get_entropy
};

DEVICE_AND_API_INIT(random_nrf5, CONFIG_RANDOM_NAME,
		    random_nrf5_init, &random_nrf5_data, NULL,
		    PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		    &random_nrf5_api_funcs);

u32_t sys_rand32_get(void)
{
	u32_t value;
	int rc;

	rc = random_nrf5_get_entropy(DEVICE_GET(random_nrf5), (u8_t *) &value,
				     sizeof(value));
	__ASSERT_NO_MSG(!rc);

	return value;
}
