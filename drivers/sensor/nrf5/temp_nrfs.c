/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "kernel.h"
#define DT_DRV_COMPAT nordic_nrf_temp_nrfs

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <hal/nrf_temp.h>
#include <zephyr/logging/log.h>
#include <nrfs_temp.h>
#include <zephyr/sys/__assert.h>

LOG_MODULE_REGISTER(temp_nrfs, CONFIG_SENSOR_LOG_LEVEL);

#if CONFIG_TEMP_NRF5_TRIGGER

#define MS_IN_SECOND			  1000
#define HZ_TO_TICK_DELAY_MS(frequency_hz) (MS_IN_SECOND / frequency_hz)
#define CLIP_TO_RANGE(x, low, high)                                            \
	(((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define DEFAULT_SENSOR_ATTRIBUTES                                              \
	(struct sensor_attributes)                                             \
	{                                                                      \
		.sampling_freq = {10, 0},                                      \
                .up_threshold = {INT32_MAX, 0},                                \
		.low_threshold = {INT32_MIN, 0}                                \
	}

struct sensor_attributes {
	struct sensor_value sampling_freq;
	struct sensor_value up_threshold;
	struct sensor_value low_threshold;
};

struct temp_trigger {
	struct device *dev;
	struct sensor_trigger *trigger;
	sensor_trigger_handler_t handler;
	struct k_work work;
	struct k_work_q workq;
	K_KERNEL_STACK_MEMBER(stack,
			      CONFIG_TEMP_NRF5_TRIGGER_THREAD_STACK_SIZE);
};

#endif // CONFIG_TEMP_NRF5_TRIGGER

struct temp_nrfs_data {
	struct k_sem ipc_sync_sem;
	struct k_mutex mutex;
	int32_t raw_temp;
	int erc;
#if CONFIG_TEMP_NRF5_TRIGGER
	struct sensor_attributes attr;
	struct temp_trigger trigger;
#endif
};

static struct temp_nrfs_data temp_nrfs_driver;

static int32_t sensor_value_to_raw_temp(struct sensor_value *value)
{
	const uint8_t decimal_places_offset = 100;
	return (int32_t)(sensor_value_to_double(value) * decimal_places_offset);
}

#if CONFIG_TEMP_NRF5_TRIGGER
static void sensor_trigger_work(struct k_work *work)
{
	struct temp_trigger *trig = CONTAINER_OF(work, struct temp_trigger, work);
	trig->handler(trig->dev, trig->trigger);
}

static int temp_nrfs_sensor_trigger_set(const struct device *dev,
					const struct sensor_trigger *trig,
					sensor_trigger_handler_t handler)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;
	struct sensor_attributes *attr = &data->attr;

	if (trig == NULL || (trig->chan != SENSOR_CHAN_ALL &&
			     trig->chan != SENSOR_CHAN_DIE_TEMP)) {
		return -ENOTSUP;
	}

	if (data->trigger.handler && (data->trigger.handler != handler) && (handler != NULL)) {
		return -EBUSY;
	}

	switch (trig->type) {
	case SENSOR_TRIG_THRESHOLD: {
		k_mutex_lock(&data->mutex, K_FOREVER);
		k_work_cancel(&data->trigger.work);
		data->trigger.trigger = (struct sensor_trigger *)trig;
		data->trigger.handler = handler;
		k_mutex_unlock(&data->mutex);

		data->trigger.dev = (struct device *)dev;

		nrfs_err_t err;
		if (handler) {
			uint16_t measure_rate_ms = CLIP_TO_RANGE(
				HZ_TO_TICK_DELAY_MS(
					sensor_value_to_double(&attr->sampling_freq)),
				0, UINT16_MAX);

			err = nrfs_temp_subscribe(
				measure_rate_ms,
				sensor_value_to_raw_temp(&attr->low_threshold),
				sensor_value_to_raw_temp(&attr->up_threshold),
				NULL);
		} else {
			err = nrfs_temp_unsubscribe();
		}

		switch (err) {
			case NRFS_SUCCESS: return 0;
			case NRFS_ERR_INVALID_STATE: return -ENOTCONN;
			case NRFS_ERR_IPC: return -EIO;
			default:
				return -ENOTSUP;
		}
		break;
	}
	default:
		LOG_ERR("Unsupported trigger type");
		return -ENOTSUP;
	}
	return 0;
}

static int temp_nrfs_sensor_attr_set(const struct device *dev,
				     enum sensor_channel chan,
				     enum sensor_attribute attr,
				     const struct sensor_value *val)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;
	if (chan != SENSOR_CHAN_ALL && chan != SENSOR_CHAN_DIE_TEMP) {
		return -ENOTSUP;
	}

	if (val == NULL) {
		LOG_ERR("Invalid sensor value passed to attribute");
		return -ENOTSUP;
	}

	switch (attr) {
	case SENSOR_ATTR_SAMPLING_FREQUENCY:
		if (sensor_value_to_double(val) <= 0) {
			LOG_ERR("Invalid value for sampling frequency "
				"attribute - value has to be greater than 0");
			return -ENOTSUP;
		} else {
			data->attr.sampling_freq = *val;
		}
		break;
	case SENSOR_ATTR_UPPER_THRESH:
		data->attr.up_threshold = *val;
		break;
	case SENSOR_ATTR_LOWER_THRESH:
		data->attr.low_threshold = *val;
		break;
	default:
		LOG_ERR("Unsupported attribute passed!");
		return -ENOTSUP;
	}
	return 0;
}
#endif // CONFIG_TEMP_NRF5_TRIGGER

static void sensor_handler(nrfs_temp_evt_t const *p_evt, void *context)
{
	ARG_UNUSED(context);

	struct temp_nrfs_data *data = &temp_nrfs_driver;

	switch (p_evt->type) {
	case NRFS_TEMP_EVT_MEASURE_DONE:
		k_mutex_lock(&data->mutex, K_FOREVER);
		data->erc = 0;
		data->raw_temp = p_evt->raw_temp;
		k_mutex_unlock(&data->mutex);
		LOG_DBG("Temperature Measurement done");
		k_sem_give(&data->ipc_sync_sem);
		break;
#if CONFIG_TEMP_NRF5_TRIGGER
	case NRFS_TEMP_EVT_CHANGE:
		k_mutex_lock(&data->mutex, K_FOREVER);
		data->erc = 0;
		data->raw_temp = p_evt->raw_temp;
		if (data->trigger.trigger && data->trigger.handler) {
			k_work_submit_to_queue(
				&data->trigger.workq,
				&data->trigger.work);
		}
		k_mutex_unlock(&data->mutex);
		break;
#endif // CONFIG_TEMP_NRF5_TRIGGER
	default:
		LOG_DBG("Temperature handler - unsupported event: 0x%x",
			p_evt->type);
		break;
	}
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

	if (nrfs_temp_measure_request(NULL) == NRFS_SUCCESS) {
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
#if CONFIG_TEMP_NRF5_TRIGGER
	.attr_set = temp_nrfs_sensor_attr_set,
	.trigger_set = temp_nrfs_sensor_trigger_set,
#endif // CONFIG_TEMP_NRF5_TRIGGER
	.sample_fetch = temp_nrfs_sample_fetch,
	.channel_get = temp_nrfs_channel_get
};

static int temp_nrfs_init(const struct device *dev)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;

	LOG_DBG("nrfs temp sensor init.");

	k_sem_init(&data->ipc_sync_sem, 0, 1);
	k_mutex_init(&data->mutex);

#if CONFIG_TEMP_NRF5_TRIGGER
	data->attr = DEFAULT_SENSOR_ATTRIBUTES;

	k_work_queue_init(&data->trigger.workq);
	k_work_queue_start(
		&data->trigger.workq,
		data->trigger.stack,
		K_THREAD_STACK_SIZEOF(data->trigger.stack),
		CONFIG_TEMP_NRF5_TRIGGER_THREAD_PRIO, NULL);
	k_thread_name_set(&data->trigger.workq.thread,
			  "TEMP_NRF5_trigger");
	k_work_init(&data->trigger.work, sensor_trigger_work);
#endif // CONFIG_TEMP_NRF5_TRIGGER
	return nrfs_temp_init(sensor_handler);
}

DEVICE_DT_INST_DEFINE(0, temp_nrfs_init, NULL, &temp_nrfs_driver, NULL,
		      POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		      &temp_nrfs_driver_api);
