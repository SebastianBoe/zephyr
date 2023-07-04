/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_USB_DEVICE_USB_DC_DW_USBHS_H
#define ZEPHYR_DRIVERS_USB_DEVICE_USB_DC_DW_USBHS_H

#include <stdint.h>
#include <internal/nrfs_backend.h>
#include <internal/backends/nrfs_backend_ipc_service.h>
#include <nrfs_usb.h>

#include "usb_dw_registers.h"

static K_SEM_DEFINE(usbhs_enabled, 0, 1);

static void usbhs_periph_handler(nrfs_usb_evt_t const *p_evt, void *context)
{
	switch (p_evt->type) {
	case NRFS_USB_EVT_VBUS_STATUS_CHANGE:
		LOG_INF("USBHS new status, pll_ok = %d vreg_ok = %d vbus_detected = %d",
			p_evt->usbhspll_ok, p_evt->vregusb_ok, p_evt->vbus_detected);

		if (p_evt->usbhspll_ok && p_evt->vregusb_ok) {
			k_sem_give(&usbhs_enabled);
		}

		break;
	case NRFS_USB_EVT_REJECT:
		LOG_ERR("Request rejected");
		break;
	default:
		LOG_ERR("Unexpected event: 0x%x", p_evt->type);
		break;
	}
}

#define USBHS_DT_WRAPPER_REG_ADDR(n)						\
	COND_CODE_1(DT_NODE_HAS_COMPAT(DT_DRV_INST(n), nordic_nrf_usbhs),	\
		    (DT_INST_REG_ADDR_BY_NAME(n, wrapper)), (0))

static inline int clk_enable_nrf_usbhs(void)
{
	NRF_USBHS_Type *wrapper = UINT_TO_POINTER(USBHS_DT_WRAPPER_REG_ADDR(0));
	nrfs_err_t status;
	int ret;

	ret = nrfs_backend_wait_for_connection(K_MSEC(1000));
	if (ret) {
		LOG_INF("NRFS backend connection timeout");
		return ret;
	}

	status = nrfs_usb_init(usbhs_periph_handler);
	if (status != NRFS_SUCCESS) {
		LOG_ERR("Failed to init nrfs USB service: %d", status);
	}

	status = nrfs_usb_enable_request(NULL);
	if (status != NRFS_SUCCESS) {
		LOG_ERR("USBHS enable request failed: %d", status);
		return -EINVAL;
	}

	/*
	 * Bare minimum to get it working.
	 * This is a hack for now, more changes are needed in the driver
	 * itself to have some kind of event processing there.
	 */
	k_sem_take(&usbhs_enabled, K_FOREVER);

	LOG_INF("USBHS wrapper %p", wrapper);
	wrapper->ENABLE = USBHS_ENABLE_PHY_Msk | USBHS_ENABLE_CORE_Msk;
	wrapper->TASKS_START = 1UL;
	k_msleep(1);

	/* Check we have write/read access to the DWC2 IP */
	NRF_USBHSCORE0_S->GUID = 0x42424242UL;
	LOG_INF("GSNPSID: 0x%08x", NRF_USBHSCORE0_S->GSNPSID);
	LOG_INF("GUID: 0x%08x", NRF_USBHSCORE0_S->GUID);

	/* Enable interrupt */
	wrapper->INTENSET = 1UL;

	return 0;
}

static inline int pwr_on_nrf_usbhs(struct usb_dw_reg *const base)
{
	return 0;
}

#endif /* ZEPHYR_DRIVERS_USB_DEVICE_USB_DC_DW_USBHS_H */
