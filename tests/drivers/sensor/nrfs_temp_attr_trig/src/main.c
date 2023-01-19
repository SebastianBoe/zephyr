/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ztest_assert.h"
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <fff.h>
#include <nrfs_temp.h>
#include <ztest.h>
#include <ztest_mock.h>

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(nrfs_err_t, nrfs_temp_subscribe, uint16_t, int32_t, int32_t,
		void *);
FAKE_VALUE_FUNC(nrfs_err_t, nrfs_temp_unsubscribe);
FAKE_VALUE_FUNC(nrfs_err_t, nrfs_temp_init, nrfs_temp_evt_handler_t);
FAKE_VALUE_FUNC(nrfs_err_t, nrfs_temp_measure_request, void *)

static int sensor_trigger_handler_call_count = 0;
static int sensor_trigger_new_handler_call_count = 0;

static void sensor_trigger_handler(const struct device *dev,
				   const struct sensor_trigger *trigger)
{
	sensor_trigger_handler_call_count++;
}

static void sensor_trigger_new_handler(const struct device *dev,
				   const struct sensor_trigger *trigger)
{
	sensor_trigger_new_handler_call_count++;
}

void test_setup(void)
{
	sensor_trigger_handler_call_count = 0;
	sensor_trigger_new_handler_call_count = 0;
}

static void set_subscription(const struct device *dev, sensor_trigger_handler_t handler)
{
	zassert_not_null(dev, "Device object is NULL.");
	zassert_true(device_is_ready(dev), "Device is not ready.");
	nrfs_temp_subscribe_fake.return_val=0;
	zassert_equal(0,
		sensor_attr_set(dev, SENSOR_CHAN_DIE_TEMP,
				SENSOR_ATTR_SAMPLING_FREQUENCY,
				&(struct sensor_value){.val1 = 5, .val2 = 0}),
		"sensor_attr_set return error");
	zassert_equal(0,
		      sensor_attr_set(dev, SENSOR_CHAN_DIE_TEMP,
				      SENSOR_ATTR_UPPER_THRESH,
				      &(struct sensor_value){.val1 = 120,
							     .val2 = 250000}),
		      "sensor_attr_set return error");
	zassert_equal(0,
		      sensor_attr_set(dev, SENSOR_CHAN_DIE_TEMP,
				      SENSOR_ATTR_LOWER_THRESH,
				      &(struct sensor_value){.val1 = -30,
							     .val2 = 750000}),
		      "sensor_attr_set return error");

	struct sensor_trigger trig = {.type = SENSOR_TRIG_THRESHOLD,
				      .chan = SENSOR_CHAN_DIE_TEMP};

	zassert_equal(
		0, sensor_trigger_set(dev, &trig, handler),
		"sensor_trigger_set return error");
}

static void cancel_subscription(const struct device *dev)
{
	zassert_not_null(dev, "Device object is NULL.");
	zassert_true(device_is_ready(dev), "Device is not ready.");

	struct sensor_trigger trig = {.type = SENSOR_TRIG_THRESHOLD,
				      .chan = SENSOR_CHAN_DIE_TEMP};

	zassert_equal(
		0, sensor_trigger_set(dev, &trig, NULL),
		"sensor_trigger_set return error");
}

void test_temp_driver_subscribe_test_upper(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	set_subscription(temp_dev, sensor_trigger_handler);

	nrfs_temp_evt_handler_t handler = nrfs_temp_init_fake.arg0_val;
	zassert_not_null(handler, "nrfs handler can not be null");

	nrfs_temp_evt_t evt = {.type = NRFS_TEMP_EVT_CHANGE,
			       .raw_temp = nrfs_temp_to_raw(12050)};
	handler(&evt, temp_dev->data);
	zassert_true(sensor_trigger_handler_call_count == 1,
		     "trigger called invalid number of times");
}

void test_temp_driver_subscribe_test_lower(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	set_subscription(temp_dev, sensor_trigger_handler);

	nrfs_temp_evt_handler_t handler = nrfs_temp_init_fake.arg0_val;
	zassert_not_null(handler, "nrfs handler can not be null");

	nrfs_temp_evt_t evt = {.type = NRFS_TEMP_EVT_CHANGE,
			       .raw_temp = nrfs_temp_to_raw(-3150)};
	handler(&evt, temp_dev->data);
	zassert_true(sensor_trigger_handler_call_count == 1,
		     "trigger called invalid number of times");
}

void test_temp_driver_subscribe_test_upper_lower(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	set_subscription(temp_dev, sensor_trigger_handler);

	nrfs_temp_evt_handler_t handler = nrfs_temp_init_fake.arg0_val;
	zassert_not_null(handler, "nrfs handler can not be null");

	nrfs_temp_evt_t evt_up = {.type = NRFS_TEMP_EVT_CHANGE,
				  .raw_temp = nrfs_temp_to_raw(12050)};
	handler(&evt_up, temp_dev->data);

	nrfs_temp_evt_t evt_low = {.type = NRFS_TEMP_EVT_CHANGE,
				   .raw_temp = nrfs_temp_to_raw(-3100)};
	handler(&evt_low, temp_dev->data);
	zassert_true(sensor_trigger_handler_call_count == 2,
		     "trigger called invalid number of times");
}

void test_temp_driver_cancel_subscription(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	set_subscription(temp_dev, sensor_trigger_handler);
	zassert_true(sensor_trigger_handler_call_count == 0,
		     "trigger called invalid number of times");
	cancel_subscription(temp_dev);

	nrfs_temp_evt_handler_t handler = nrfs_temp_init_fake.arg0_val;
	zassert_not_null(handler, "nrfs handler can not be null");

	nrfs_temp_evt_t evt_up = {.type = NRFS_TEMP_EVT_CHANGE,
				  .raw_temp = nrfs_temp_to_raw(12050)};
	handler(&evt_up, temp_dev->data);

	nrfs_temp_evt_t evt_low = {.type = NRFS_TEMP_EVT_CHANGE,
				   .raw_temp = nrfs_temp_to_raw(-3100)};
	handler(&evt_low, temp_dev->data);
	zassert_true(sensor_trigger_handler_call_count == 0,
		     "trigger called invalid number of times");
}

void test_temp_driver_update_subscription(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	set_subscription(temp_dev, sensor_trigger_handler);
	zassert_true(sensor_trigger_handler_call_count == 0,
		     "trigger called invalid number of times");

	struct sensor_trigger trig = {.type = SENSOR_TRIG_THRESHOLD,
				      .chan = SENSOR_CHAN_DIE_TEMP};

	zassert_equal(
		-EBUSY, sensor_trigger_set(temp_dev, &trig, sensor_trigger_new_handler),
		"sensor_trigger_set return error");

	cancel_subscription(temp_dev);

	zassert_equal(
		0, sensor_trigger_set(temp_dev, &trig, sensor_trigger_new_handler),
		"sensor_trigger_set return error");

	nrfs_temp_evt_handler_t handler = nrfs_temp_init_fake.arg0_val;
	zassert_not_null(handler, "nrfs handler can not be null");

	nrfs_temp_evt_t evt_up = {.type = NRFS_TEMP_EVT_CHANGE,
				  .raw_temp = nrfs_temp_to_raw(12050)};
	handler(&evt_up, temp_dev->data);

	nrfs_temp_evt_t evt_low = {.type = NRFS_TEMP_EVT_CHANGE,
				   .raw_temp = nrfs_temp_to_raw(-3100)};
	handler(&evt_low, temp_dev->data);
	zassert_true(sensor_trigger_handler_call_count == 0,
		     "trigger called invalid number of times");
	zassert_true(sensor_trigger_new_handler_call_count == 2,
		     "trigger called invalid number of times");
}

void test_main(void)
{
	ztest_test_suite(
		test_temp_driver,
		ztest_unit_test_setup_teardown(test_temp_driver_subscribe_test_upper, test_setup, unit_test_noop),
		ztest_unit_test_setup_teardown(test_temp_driver_subscribe_test_upper, test_setup, unit_test_noop),
		ztest_unit_test_setup_teardown(test_temp_driver_subscribe_test_lower, test_setup, unit_test_noop),
		ztest_unit_test_setup_teardown(test_temp_driver_subscribe_test_upper_lower, test_setup, unit_test_noop),
		ztest_unit_test_setup_teardown(test_temp_driver_cancel_subscription, test_setup, unit_test_noop),
		ztest_unit_test_setup_teardown(test_temp_driver_update_subscription, test_setup, unit_test_noop));
	ztest_run_test_suite(test_temp_driver);
}
