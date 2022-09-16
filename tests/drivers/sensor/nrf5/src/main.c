/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <device.h>
#include <drivers/sensor.h>
#include <internal/backends/nrfs_backend_ipc_service.h>

void test_temp_driver_test(void)
{
	nrfs_backend_wait_for_connection(K_FOREVER);

	const struct device *temp_dev = DEVICE_DT_GET(DT_NODELABEL(temp_nrfs));

	zassert_not_null(temp_dev, "Device object is NULL.");
	zassert_true(device_is_ready(temp_dev), "Device is not ready.");

	int rc = sensor_sample_fetch(temp_dev);

	zassert_ok(rc, "Cannot fetch a sample from temperature sensor.");

	struct sensor_value val = { 0, 0 };
	rc = sensor_channel_get(temp_dev, SENSOR_CHAN_DIE_TEMP, &val);

	zassert_ok(rc, "Get temperature fail.");
	zassert_true(val.val1 > -40, "Temperature out of range %d.%d [C]", val.val1, val.val2);
}

void test_main(void)
{
	ztest_test_suite(test_temp_driver,
			 ztest_unit_test(test_temp_driver_test)
			 );
	ztest_run_test_suite(test_temp_driver);
}
