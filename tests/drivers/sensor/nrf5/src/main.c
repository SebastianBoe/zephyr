/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#if defined(CONFIG_HAS_NRF_TEMP_NRFS)
#define TEMP_SENSOR_NODE_ID       DT_NODELABEL(temp_nrfs)
#else
#define TEMP_SENSOR_NODE_ID       DT_NODELABEL(temp)
#endif

void test_temp_driver_test(void)
{
	const struct device *temp_dev = DEVICE_DT_GET(TEMP_SENSOR_NODE_ID);

	zassert_not_null(temp_dev, "Device object is NULL.");
	zassert_true(device_is_ready(temp_dev), "Device is not ready.");

	int rc = 0;
	int retry_cnt = 0;
	while ((rc = sensor_sample_fetch(temp_dev)) == -ENOTCONN) {
		k_sleep(K_MSEC(1000));
		retry_cnt++;
		zassert_false(retry_cnt >= 3, "Backend connection fail.");
	}

	zassert_ok(rc, "Cannot fetch a sample from temperature sensor.");

	struct sensor_value val;
	sensor_value_from_double(&val, 0);
	zassert_ok(sensor_channel_get(temp_dev, SENSOR_CHAN_DIE_TEMP, &val), "Get temperature fail.");
#if !defined(CONFIG_NO_ANALOG_PART)
	double temp_val = sensor_value_to_double(&val);
	zassert_true(temp_val > -40, "Temperature out of range %d [C]", temp_val);
#endif

	zassert_ok(sensor_sample_fetch(temp_dev), "Cannot fetch a sample from temperature sensor.");

	sensor_value_from_double(&val, 0);
	zassert_ok(sensor_channel_get(temp_dev, SENSOR_CHAN_DIE_TEMP, &val), "Get temperature fail.");
#if !defined(CONFIG_NO_ANALOG_PART)
	temp_val = sensor_value_to_double(&val);
	zassert_true(temp_val > -40, "Temperature out of range %d [C]", temp_val);
#endif
}

void test_main(void)
{
	ztest_test_suite(test_temp_driver,
			 ztest_unit_test(test_temp_driver_test)
			 );
	ztest_run_test_suite(test_temp_driver);
}
