/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT nordic_nrf_temp_nrfs

#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>
#include <hal/nrf_temp.h>
#include <nrfs_temp.h>

LOG_MODULE_REGISTER(temp_nrfs, CONFIG_SENSOR_LOG_LEVEL);

struct temp_nrfs_data {
	struct k_sem ipc_sync_sem;
	struct k_mutex mutex;
	int32_t raw_temp;
	int erc;
};

static void sensor_handler(nrfs_temp_evt_t const *p_evt, void *context)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)context;

	switch (p_evt->type) {
	case NRFS_TEMP_EVT_MEASURE_DONE:
		data->erc = 0;
		data->raw_temp = p_evt->raw_temp;
		LOG_DBG("Temperature Measurement done");
		break;
	default:
		data->erc = -ENOTSUP;
		LOG_DBG("Temperature handler - unsupported event: 0x%x", p_evt->type);
		break;
	}

	k_sem_give(&data->ipc_sync_sem);
}

static int temp_nrfs_sample_fetch(const struct device *dev,
				  enum sensor_channel chan)
{
	int erc = -EIO;
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;

	if (chan != SENSOR_CHAN_ALL && chan != SENSOR_CHAN_DIE_TEMP) {
		return -ENOTSUP;
	}

	k_mutex_lock(&data->mutex, K_FOREVER);

	if (NRFS_SUCCESS == nrfs_temp_measure_request((void *)data)) {

		k_sem_take(&data->ipc_sync_sem, K_FOREVER);

		erc = data->erc;
		LOG_DBG("Temperature sample: %d", data->raw_temp);

	} else {
		LOG_DBG("Request send failed");
	}

	k_mutex_unlock(&data->mutex);

	return erc;
}

static int temp_nrfs_channel_get(const struct device *dev,
				 enum sensor_channel chan,
				 struct sensor_value *val)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;

	if (chan != SENSOR_CHAN_DIE_TEMP) {
		return -ENOTSUP;
	}

	int32_t uval = nrfs_temp_from_raw(data->raw_temp);
	val->val1 = uval / 100;
	val->val2 = (uval % 100) * 10000;

	LOG_DBG("Temperature:%d.%d[C]", val->val1, val->val2);

	return 0;
}

static const struct sensor_driver_api temp_nrfs_driver_api = {
	.sample_fetch = temp_nrfs_sample_fetch,
	.channel_get = temp_nrfs_channel_get,
};

static int temp_nrfs_init(const struct device *dev)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;

	LOG_DBG("nrfs temp sensor init.");

	k_sem_init(&data->ipc_sync_sem, 0, K_SEM_MAX_LIMIT);
	k_mutex_init(&data->mutex);

	return nrfs_temp_init(sensor_handler);
}

static struct temp_nrfs_data temp_nrfs_driver;

DEVICE_DT_INST_DEFINE(0,
		      temp_nrfs_init,
		      NULL,
		      &temp_nrfs_driver,
		      NULL,
		      POST_KERNEL,
		      CONFIG_SENSOR_INIT_PRIORITY,
		      &temp_nrfs_driver_api);
