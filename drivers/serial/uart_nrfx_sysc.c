/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/uart.h>
#include <hal/nrf_uarte.h>

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
#error "NO SUPPORT FOR IRQ DRIVEN"
#endif

struct sysc_nrfx_config {
	NRF_UARTE_Type *reg;
};

static char dma_buf;

static inline const struct sysc_nrfx_config *get_dev_config(const struct device *dev)
{
	return dev->config;
}

static inline NRF_UARTE_Type *get_uarte_instance(const struct device *dev)
{
	const struct sysc_nrfx_config *config = get_dev_config(dev);

	return config->reg;
}

static void sysc_poll_out(const struct device *dev, unsigned char c)
{
	NRF_UARTE_Type *uarte = get_uarte_instance(dev);

	dma_buf = c;
	nrf_uarte_tx_buffer_set(uarte, &dma_buf, 1);

	nrf_uarte_event_clear(uarte, NRF_UARTE_EVENT_ENDTX);

	nrf_uarte_task_trigger(uarte, NRF_UARTE_TASK_STARTTX);

	while(!nrf_uarte_event_check(uarte, NRF_UARTE_EVENT_ENDTX))
	{}

	nrf_uarte_event_clear(uarte, NRF_UARTE_EVENT_ENDTX);
}

static int sysc_poll_in(const struct device *dev, unsigned char *c)
{
        return -1;
}

static const struct uart_driver_api sysc_driver_api = {
	.poll_in	= sysc_poll_in,
	.poll_out	= sysc_poll_out,
	.err_check	= NULL,
};

static int sysc_init(const struct device *dev)
{
	NRF_UARTE_Type *uarte = get_uarte_instance(dev);
	nrf_uarte_enable(uarte);
	return 0;
}

#define UARTE(idx)	DT_NODELABEL(uart##idx)

#define UART_NRF_SYSC_DEVICE(idx)				      \
	static const struct  sysc_nrfx_config sysc_##idx##_config = { \
		.reg = (NRF_UARTE_Type *)DT_REG_ADDR(UARTE(idx)),     \
	};							      \
	DEVICE_DT_DEFINE(UARTE(idx),				      \
			 sysc_init,				      \
			 NULL,					      \
			 NULL,					      \
			 &sysc_##idx##_config,			      \
			 PRE_KERNEL_1,				      \
			 CONFIG_KERNEL_INIT_PRIORITY_DEVICE,	      \
			 &sysc_driver_api);

#ifdef CONFIG_UART_00_NRF_UARTE
UART_NRF_SYSC_DEVICE(00);
#endif

#ifdef CONFIG_UART_20_NRF_UARTE
UART_NRF_SYSC_DEVICE(20);
#endif

#ifdef CONFIG_UART_21_NRF_UARTE
UART_NRF_SYSC_DEVICE(21);
#endif

#ifdef CONFIG_UART_22_NRF_UARTE
UART_NRF_SYSC_DEVICE(22);
#endif

#ifdef CONFIG_UART_30_NRF_UARTE
UART_NRF_SYSC_DEVICE(30);
#endif

#ifdef CONFIG_UART_130_NRF_UARTE
UART_NRF_SYSC_DEVICE(130);
#endif

#ifdef CONFIG_UART_131_NRF_UARTE
UART_NRF_SYSC_DEVICE(131);
#endif

#ifdef CONFIG_UART_132_NRF_UARTE
UART_NRF_SYSC_DEVICE(132);
#endif

#ifdef CONFIG_UART_133_NRF_UARTE
UART_NRF_SYSC_DEVICE(133);
#endif

#ifdef CONFIG_UART_134_NRF_UARTE
UART_NRF_SYSC_DEVICE(134);
#endif

#ifdef CONFIG_UART_135_NRF_UARTE
UART_NRF_SYSC_DEVICE(135);
#endif

#ifdef CONFIG_UART_136_NRF_UARTE
UART_NRF_SYSC_DEVICE(136);
#endif

#ifdef CONFIG_UART_137_NRF_UARTE
UART_NRF_SYSC_DEVICE(137);
#endif
