/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT nordic_nrf_temp_nrfs

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <hal/nrf_temp.h>
#include <zephyr/logging/log.h>
#include <nrfs_temp.h>
#include <zephyr/sys/__assert.h>

LOG_MODULE_REGISTER(temp_nrfs, CONFIG_SENSOR_LOG_LEVEL);

#ifdef CONFIG_TEMP_NRF5_TRIGGER

#define HZ_TO_TICK_DELAY_MS(frequency_hz) (MSEC_PER_SEC / frequency_hz)

#define DEFAULT_SENSOR_ATTRIBUTES	   \
	(struct sensor_attributes)	   \
	{				   \
		.sampling_freq = { 1, 0 }, \
		.up_threshold = { 25, 0 }, \
		.low_threshold = { 0, 0 }  \
	}

struct sensor_attributes {
	struct sensor_value sampling_freq;
	struct sensor_value up_threshold;
	struct sensor_value low_threshold;
};

#endif /* CONFIG_TEMP_NRF5_TRIGGER */

struct temp_nrfs_data {
	struct k_sem nrfs_measure_done_sem;
	struct k_mutex mutex;
	int32_t raw_temp;
	int erc;
#ifdef CONFIG_TEMP_NRF5_TRIGGER
	struct device *dev;
	K_KERNEL_STACK_MEMBER(thread_stack, CONFIG_TEMP_NRF5_TRIGGER_THREAD_STACK_SIZE);
	struct sensor_trigger trigger;
	sensor_trigger_handler_t handler;

	struct k_thread thread;
	struct k_sem nrfs_event_change_sem;

	struct sensor_attributes attr;
#endif /* CONFIG_TEMP_NRF5_TRIGGER */
};

static struct temp_nrfs_data temp_nrfs_driver;

#ifdef CONFIG_TEMP_NRF5_TRIGGER
static int32_t sensor_value_to_raw_temp(struct sensor_value *value)
{
	const uint8_t decimal_places_offset = 100;

	return nrfs_temp_to_raw((sensor_value_to_double(value) * decimal_places_offset));
}

static void nrfs_temp_thread_cb(const struct device *dev)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;

	k_mutex_lock(&data->mutex, K_FOREVER);
	if (data->handler) {
		data->handler(dev, &data->trigger);
	}
	k_mutex_unlock(&data->mutex);
}

static void nrfs_temp_thread(void *drv_data, void *p2, void *p3)
{
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	struct temp_nrfs_data *data = (struct temp_nrfs_data *)drv_data;
	while (true) {
		k_sem_take(&data->nrfs_event_change_sem, K_FOREVER);
		nrfs_temp_thread_cb(data->dev);
	}
}

static int temp_nrfs_sensor_trigger_set(const struct device *dev,
					const struct sensor_trigger *trig,
					sensor_trigger_handler_t handler)
{
	struct temp_nrfs_data *data = (struct temp_nrfs_data *)dev->data;
	struct sensor_attributes *attr = &data->attr;

	if (!trig || (trig->chan != SENSOR_CHAN_ALL &&
		      trig->chan != SENSOR_CHAN_DIE_TEMP)) {
		return -ENOTSUP;
	}

	if (data->handler && (data->handler != handler) && handler) {
		return -EBUSY;
	}

	switch (trig->type) {
	case SENSOR_TRIG_THRESHOLD: {
		k_mutex_lock(&data->mutex, K_FOREVER);
		data->trigger = *trig;
		data->handler = handler;
		k_mutex_unlock(&data->mutex);

		nrfs_err_t err;
		if (handler) {
			uint16_t measure_rate_ms = CLAMP(
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

	if (!val) {
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

#endif /* CONFIG_TEMP_NRF5_TRIGGER */

static void sensor_handler(nrfs_temp_evt_t const *p_evt, void *context)
{
	ARG_UNUSED(context);

	struct temp_nrfs_data *data = &temp_nrfs_driver;

	switch (p_evt->type) {
	case NRFS_TEMP_EVT_MEASURE_DONE:
		data->erc = 0;
		data->raw_temp = p_evt->raw_temp;
		k_sem_give(&data->nrfs_measure_done_sem);
		break;
#ifdef CONFIG_TEMP_NRF5_TRIGGER
	case NRFS_TEMP_EVT_CHANGE:
		data->erc = 0;
		data->raw_temp = p_evt->raw_temp;
		k_sem_give(&data->nrfs_event_change_sem);
		break;
#endif /* CONFIG_TEMP_NRF5_TRIGGER */
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
	int nrfs_erc = nrfs_temp_measure_request(NULL);
	switch (nrfs_erc) {
	case NRFS_SUCCESS:
		k_sem_take(&data->nrfs_measure_done_sem, K_FOREVER);

		erc = data->erc;
		LOG_DBG("Temperature sample: %d", data->raw_temp);
		break;
	case NRFS_ERR_INVALID_STATE:
		LOG_DBG("Backend is not ready, try again.");
		erc = -ENOTCONN;
		break;
	case NRFS_ERR_IPC:
		LOG_DBG("Measure request failed.");
		erc = -EIO;
		break;
	default:
		LOG_DBG("Measure request failed, %d", nrfs_erc);
		erc = -ENOTSUP;
		break;
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

	LOG_DBG("Temperature: %d.%d[C]", val->val1, val->val2);

	return 0;
}

static const struct sensor_driver_api temp_nrfs_driver_api = {
#ifdef CONFIG_TEMP_NRF5_TRIGGER
	.attr_set = temp_nrfs_sensor_attr_set,
	.trigger_set = temp_nrfs_sensor_trigger_set,
#endif /* CONFIG_TEMP_NRF5_TRIGGER */
	.sample_fetch = temp_nrfs_sample_fetch,
	.channel_get = temp_nrfs_channel_get
};

static int temp_nrfs_init(const struct device *dev)
{
	struct temp_nrfs_data *dev_data = (struct temp_nrfs_data *)dev->data;

	LOG_DBG("nrfs temp sensor init.");

	k_sem_init(&dev_data->nrfs_measure_done_sem, 0, K_SEM_MAX_LIMIT);
	k_mutex_init(&dev_data->mutex);

#ifdef CONFIG_TEMP_NRF5_TRIGGER
	k_sem_init(&dev_data->nrfs_event_change_sem, 0, K_SEM_MAX_LIMIT);
	dev_data->attr = DEFAULT_SENSOR_ATTRIBUTES;
	dev_data->dev = (struct device *)dev;

	k_thread_create(&dev_data->thread, dev_data->thread_stack,
			CONFIG_TEMP_NRF5_TRIGGER_THREAD_STACK_SIZE,
			nrfs_temp_thread,
			dev_data, NULL, NULL,
			K_PRIO_COOP(CONFIG_TEMP_NRF5_TRIGGER_THREAD_PRIO),
			0, K_NO_WAIT);
#endif /* CONFIG_TEMP_NRF5_TRIGGER */
	return nrfs_temp_init(sensor_handler);
}

DEVICE_DT_INST_DEFINE(0, temp_nrfs_init, NULL, &temp_nrfs_driver, NULL,
		      POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		      &temp_nrfs_driver_api);
