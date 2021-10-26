/*
 * Copyright (c) 2018, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/sensor.h>
#include <zephyr/pm/device.h>
#include <zephyr/drivers/pinctrl.h>
#include <soc.h>

#include <nrfx_qdec.h>
#include <hal/nrf_gpio.h>

#include <zephyr/logging/log.h>
#include <zephyr/irq.h>
LOG_MODULE_REGISTER(qdec_nrfx, CONFIG_SENSOR_LOG_LEVEL);

#define DT_DRV_COMPAT nordic_nrf_qdec

#define QDEC_NRFX_PIN_UNUSED UINT32_MAX
#define QDEC_NRFX_FULL_ANGLE 360

/* limit range to avoid overflow when converting steps to degrees */
#define QDEC_NRFX_ACC_MAX (INT_MAX / QDEC_NRFX_FULL_ANGLE)
#define QDEC_NRFX_ACC_MIN (INT_MIN / QDEC_NRFX_FULL_ANGLE)

struct qdec_nrfx_data {
	int32_t acc;
	sensor_trigger_handler_t data_ready_handler;
	const struct sensor_trigger *data_ready_trigger;
};

struct qdec_nrfx_config {
	nrfx_qdec_t qdec;                     /* QDEC instance. */
	const nrfx_qdec_config_t nrfx_config; /* nrfx configuration. */
	uint32_t enable_pin;
	uint32_t steps;
};

static inline struct qdec_nrfx_data *get_dev_data(const struct device *dev)
{
	return dev->data;
}

static inline const struct qdec_nrfx_config *get_dev_config(const struct device *dev)
{
	return dev->config;
}

PINCTRL_DT_DEFINE(DT_DRV_INST(0));
static const struct pinctrl_dev_config *qdec_nrfx_pcfg =
	PINCTRL_DT_DEV_CONFIG_GET(DT_DRV_INST(0));

static void accumulate(struct qdec_nrfx_data *data, int16_t acc)
{
	unsigned int key = irq_lock();

	bool overflow = ((acc > 0) && (QDEC_NRFX_ACC_MAX - acc < data->acc)) ||
			((acc < 0) && (QDEC_NRFX_ACC_MIN - acc > data->acc));

	if (!overflow) {
		data->acc += acc;
	}

	irq_unlock(key);
}

static int qdec_nrfx_sample_fetch(const struct device *dev,
				  enum sensor_channel chan)
{
	const nrfx_qdec_t *qdec = &get_dev_config(dev)->qdec;
	struct qdec_nrfx_data *data = get_dev_data(dev);
	int16_t acc;
	int8_t accdbl;

	if ((chan != SENSOR_CHAN_ALL) && (chan != SENSOR_CHAN_ROTATION)) {
		return -ENOTSUP;
	}

	nrfx_qdec_accumulators_read(qdec, &acc, &accdbl);

	accumulate(data, acc);

	return 0;
}

#define QDEC_STEPS DT_INST_PROP(0, steps)

static int qdec_nrfx_channel_get(const struct device *dev,
				 enum sensor_channel chan,
				 struct sensor_value *val)
{
	struct qdec_nrfx_data *data = get_dev_data(dev);
	const struct qdec_nrfx_config *config = get_dev_config(dev);

	unsigned int key;
	int32_t acc;

	if (chan != SENSOR_CHAN_ROTATION) {
		return -ENOTSUP;
	}

	key = irq_lock();
	acc = data->acc;
	data->acc = 0;
	irq_unlock(key);

	val->val1 = (acc * QDEC_NRFX_FULL_ANGLE) / config->steps;
	val->val2 = (acc * QDEC_NRFX_FULL_ANGLE) - (val->val1 * config->steps);
	if (val->val2 != 0) {
		val->val2 *= 1000000;
		val->val2 /= config->steps;
	}

	return 0;
}

static int qdec_nrfx_trigger_set(const struct device         *dev,
				 const struct sensor_trigger *trig,
				 sensor_trigger_handler_t    handler)
{
	struct qdec_nrfx_data *data = get_dev_data(dev);
	unsigned int key;

	if (trig->type != SENSOR_TRIG_DATA_READY) {
		return -ENOTSUP;
	}

	if ((trig->chan != SENSOR_CHAN_ALL) &&
	    (trig->chan != SENSOR_CHAN_ROTATION)) {
		return -ENOTSUP;
	}

	key = irq_lock();
	data->data_ready_handler = handler;
	data->data_ready_trigger = trig;
	irq_unlock(key);

	return 0;
}

static void qdec_nrfx_event_handler(nrfx_qdec_event_t event, void *p_context)
{
	const struct device *dev = (const struct device *)p_context;
	struct qdec_nrfx_data *data = get_dev_data(dev);
	sensor_trigger_handler_t handler;
	const struct sensor_trigger *trig;
	unsigned int key;

	switch (event.type) {
	case NRF_QDEC_EVENT_REPORTRDY:
		accumulate(data, event.data.report.acc);

		key = irq_lock();
		handler = data->data_ready_handler;
		trig = qdec_nrfx_data.data_ready_trigger;
		irq_unlock(key);

		if (handler) {
			handler(dev, trig);
		}
		break;

	default:
		LOG_ERR("unhandled event (0x%x)", event.type);
		break;
	}
}

static void qdec_nrfx_gpio_ctrl(const struct device *dev, bool enable)
{
	const struct qdec_nrfx_config *config = get_dev_config(dev);

	if (config->enable_pin != QDEC_NRFX_PIN_UNUSED) {
		nrf_gpio_pin_write(config->enable_pin, enable ? 0 : 1);
		nrf_gpio_cfg_output(config->enable_pin);
	}
}

NRF_DT_CHECK_NODE_HAS_PINCTRL_SLEEP(DT_DRV_INST(0));

static int qdec_nrfx_init(const struct device *dev)
{
	const struct qdec_nrfx_config *config = get_dev_config(dev);
	const nrfx_qdec_t *qdec = &get_dev_config(dev)->qdec;
	nrfx_err_t err;

	int ret = pinctrl_apply_state(qdec_nrfx_pcfg, PINCTRL_STATE_DEFAULT);

	if (ret < 0) {
		return ret;
	}

	err = nrfx_qdec_init(qdec, &config->nrfx_config, qdec_nrfx_event_handler, (void *)dev);
	if (err == NRFX_ERROR_INVALID_STATE) {
		LOG_ERR("QDEC already in use.");
		return -EBUSY;
	} else if (err != NRFX_SUCCESS) {
		LOG_ERR("Failed to initialize QDEC. NRFX error code: %d", err);
		return -EFAULT;
	}

	qdec_nrfx_gpio_ctrl(dev, true);
	nrfx_qdec_enable(qdec);

	return 0;
}

#ifdef CONFIG_PM_DEVICE
static int qdec_nrfx_pm_action(const struct device *dev,
				enum pm_device_action action)
{
	int ret = 0;
	ARG_UNUSED(dev);
	const nrfx_qdec_t *qdec = &get_dev_config(dev)->qdec;

	switch (action) {
	case PM_DEVICE_ACTION_RESUME:
		ret = pinctrl_apply_state(qdec_nrfx_pcfg,
					  PINCTRL_STATE_DEFAULT);
		if (ret < 0) {
			return ret;
		}

		qdec_nrfx_gpio_ctrl(dev, true);
		nrfx_qdec_enable(qdec);
		break;

	case PM_DEVICE_ACTION_TURN_OFF:
		/* device must be uninitialized */
		nrfx_qdec_uninit(qdec);

		ret = pinctrl_apply_state(qdec_nrfx_pcfg,
					  PINCTRL_STATE_SLEEP);
		if (ret < 0) {
			return ret;
		}
		break;

	case PM_DEVICE_ACTION_SUSPEND:
		/* device must be suspended */
		nrfx_qdec_disable(qdec);
		qdec_nrfx_gpio_ctrl(dev, false);

		ret = pinctrl_apply_state(qdec_nrfx_pcfg,
					  PINCTRL_STATE_SLEEP);
		if (ret < 0) {
			return ret;
		}
		break;
	default:
		return -ENOTSUP;
	}

	return ret;
}
#endif /* CONFIG_PM_DEVICE */


static const struct sensor_driver_api qdec_nrfx_driver_api = {
	.sample_fetch = qdec_nrfx_sample_fetch,
	.channel_get = qdec_nrfx_channel_get,
	.trigger_set = qdec_nrfx_trigger_set,
};

#define QDEC_NRFX_NODE(idx) DT_NODELABEL(qdec##idx)

#define QDEC_NRFX_DATA(idx) \
	static struct qdec_nrfx_data qdec_nrfx_##idx##_data

#define QDEC_NRFX_CONFIG_LED_PIN(idx)			     \
	COND_CODE_1(DT_INST_NODE_HAS_PROP(idx, led_pin),     \
		    (.led_pin = DT_INST_PROP(idx, led_pin)), \
		    (.led_pin = NRF_QDEC_LED_NOT_CONNECTED))

#define QDEC_NRFX_CONFIG_ENABLE_PIN(idx)			   \
	COND_CODE_1(DT_INST_NODE_HAS_PROP(idx, enable_pin),	   \
		    (.enable_pin = DT_INST_PROP(idx, enable_pin)), \
		    (.enable_pin = QDEC_NRFX_PIN_UNUSED))

#define QDEC_NRFX_CONFIG(idx)							     \
	static const struct qdec_nrfx_config qdec_nrfx_##idx##_config = {	     \
		.qdec = NRFX_QDEC_INSTANCE(idx),				     \
		.nrfx_config = {						     \
			.nrfy_config = {					     \
				.reportper = NRF_QDEC_REPORTPER_40,		     \
				.sampleper = NRF_QDEC_SAMPLEPER_2048us,		     \
				.pins = {					     \
					.a_pin = DT_INST_PROP(idx, a_pin),	     \
					.b_pin = DT_INST_PROP(idx, b_pin),	     \
					QDEC_NRFX_CONFIG_LED_PIN(idx),		     \
				},						     \
				.ledpre = DT_INST_PROP(idx, led_pre),		     \
				.ledpol = NRF_QDEC_LEPOL_ACTIVE_HIGH,		     \
				.dbfen = NRF_QDEC_DBFEN_DISABLE,		     \
				.skip_psel_cfg = true				     \
			},							     \
			.interrupt_priority = DT_IRQ(QDEC_NRFX_NODE(idx), priority), \
			.sample_inten = false,					     \
			.reportper_inten = true,				     \
			.skip_psel_cfg = true,					     \
			.skip_gpio_cfg = true					     \
		},								     \
		QDEC_NRFX_CONFIG_ENABLE_PIN(idx),				     \
		.steps = DT_INST_PROP(idx, steps),				     \
	}

#define QDEC_NRFX_INIT(idx)					    \
	static int qdec_nrfx_##idx##_init(const struct device *dev) \
	{							    \
		IRQ_CONNECT(DT_IRQN(QDEC_NRFX_NODE(idx)),	    \
			    DT_IRQ(QDEC_NRFX_NODE(idx), priority),  \
			    nrfx_isr,				    \
			    qdec_nrfx_event_handler,		    \
			    0);					    \
		irq_enable(DT_IRQN(QDEC_NRFX_NODE(idx)));	    \
		return qdec_nrfx_init(dev);			    \
	}

#define QDEC_NRFX_DT(idx)				   \
	SENSOR_DEVICE_DT_INST_DEFINE(idx,			   \
			      qdec_nrfx_##idx##_init,	   \
			      qdec_nrfx_pm_action,	   \
			      &qdec_nrfx_##idx##_data,	   \
			      &qdec_nrfx_##idx##_config,   \
			      POST_KERNEL,		   \
			      CONFIG_SENSOR_INIT_PRIORITY, \
			      &qdec_nrfx_driver_api)

#define QDEC_NRFX_ASSERT(idx)							  \
	BUILD_ASSERT(DT_INST_PROP(idx, steps) > 0, "Only positive number valid"); \
	BUILD_ASSERT(DT_INST_PROP(idx, steps) <= 2048, "Overflow possible")

#define QDEC_NRFX_DEVICE(idx)  \
	QDEC_NRFX_DATA(idx);   \
	QDEC_NRFX_CONFIG(idx); \
	QDEC_NRFX_INIT(idx);   \
	QDEC_NRFX_DT(idx);     \
	QDEC_NRFX_ASSERT(idx);

DT_INST_FOREACH_STATUS_OKAY(QDEC_NRFX_DEVICE)
