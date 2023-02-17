/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRFX_CONFIG_LILIUMSOC1_GLOBAL_H__
#define NRFX_CONFIG_LILIUMSOC1_GLOBAL_H__

#include <zephyr/devicetree.h>

/* Nodes definitions. */
#define _IDX_TO_INSTANCE(node_id, prop, idx) DT_PROP_BY_IDX(node_id, prop, idx)
#define _INST_NUM_TO_INSTANCE(periph_name, inst_num) CONCAT(periph_name, inst_num)

// <h> nRF_Drivers

// <e> NRFX_CLOCK_ENABLED - nrfx_clock - CLOCK peripheral driver.
//==========================================================
#ifndef NRFX_CLOCK_ENABLED
#define NRFX_CLOCK_ENABLED 0
#endif

// <o> NRFX_CLOCK_CONFIG_FLLCLK_SRC  - FLLCLK source.

// <0=> FLL16M

#ifndef NRFX_CLOCK_CONFIG_FLLCLK_SRC
#define NRFX_CLOCK_CONFIG_FLLCLK_SRC 0
#endif

// <o> NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_CLOCK_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_CLOCK_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_CLOCK_CONFIG_LOG_ENABLED
#define NRFX_CLOCK_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_CLOCK_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_CLOCK_CONFIG_LOG_LEVEL
#define NRFX_CLOCK_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_CLOCK_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_CLOCK_CONFIG_INFO_COLOR
#define NRFX_CLOCK_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_CLOCK_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_CLOCK_CONFIG_DEBUG_COLOR
#define NRFX_CLOCK_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_COMP_ENABLED - nrfx_comp - COMP peripheral driver
//==========================================================
#ifndef NRFX_COMP_ENABLED
#define NRFX_COMP_ENABLED 0
#endif

// <o> NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_COMP_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_COMP_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_COMP_CONFIG_LOG_ENABLED
#define NRFX_COMP_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_COMP_CONFIG_LOG_LEVEL  - Default Severity level

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_COMP_CONFIG_LOG_LEVEL
#define NRFX_COMP_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_COMP_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_COMP_CONFIG_INFO_COLOR
#define NRFX_COMP_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_COMP_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_COMP_CONFIG_DEBUG_COLOR
#define NRFX_COMP_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_DPPI_ENABLED - nrfx_dppi - DPPI allocator.
//==========================================================
#ifndef NRFX_DPPI_ENABLED
#define NRFX_DPPI_ENABLED 1
#endif
// <e> NRFX_DPPI_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_DPPI_CONFIG_LOG_ENABLED
#define NRFX_DPPI_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_DPPI_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_DPPI_CONFIG_LOG_LEVEL
#define NRFX_DPPI_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_DPPI_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_DPPI_CONFIG_INFO_COLOR
#define NRFX_DPPI_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_DPPI_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_DPPI_CONFIG_DEBUG_COLOR
#define NRFX_DPPI_CONFIG_DEBUG_COLOR 0
#endif

/* source(publish) channels masks generation. */
#define _NRFX_DPPI_PUB_NUM_OF_OWNED_CHANNELS(node) DT_PROP_LEN(node, source_channels)
#define _NRFX_DPPI_PUB_SHIFT_OWNED(val, node) (1 << (DT_PROP_BY_IDX(node, source_channels, val)))
#define _NRFX_DPPI_PUB_CONFIG_ALLOWED_CHANNELS_MASK(node) \
		COND_CODE_1(DT_NODE_HAS_PROP(node, source_channels),	\
			(LISTIFY(_NRFX_DPPI_PUB_NUM_OF_OWNED_CHANNELS(node), \
				_NRFX_DPPI_PUB_SHIFT_OWNED, (|), node)), (0))

#define NRFX_DPPI_PUB_CONFIG_ALLOWED_CHANNELS_MASK_BY_INST_NUM(inst_num) \
		_NRFX_DPPI_PUB_CONFIG_ALLOWED_CHANNELS_MASK(DT_NODELABEL( \
				_INST_NUM_TO_INSTANCE(dppic, inst_num)))

/* sink(subscribe) channels masks generation. */
#define _NRFX_DPPI_SUB_NUM_OF_OWNED_CHANNELS(node) DT_PROP_LEN(node, sink_channels)
#define _NRFX_DPPI_SUB_SHIFT_OWNED(val, node) (1 << (DT_PROP_BY_IDX(node, sink_channels, val)))
#define _NRFX_DPPI_SUB_CONFIG_ALLOWED_CHANNELS_MASK(node) \
		COND_CODE_1(DT_NODE_HAS_PROP(node, sink_channels),	\
			(LISTIFY(_NRFX_DPPI_SUB_NUM_OF_OWNED_CHANNELS(node), \
				_NRFX_DPPI_SUB_SHIFT_OWNED, (|), node)), (0))

#define NRFX_DPPI_SUB_CONFIG_ALLOWED_CHANNELS_MASK_BY_INST_NUM(inst_num) \
		_NRFX_DPPI_SUB_CONFIG_ALLOWED_CHANNELS_MASK(DT_NODELABEL( \
				_INST_NUM_TO_INSTANCE(dppic, inst_num)))

#define NRFX_DPPI_PUB_OR_SUB_MASK(inst_num) \
    NRFX_COND_CODE_0(DT_NODE_HAS_PROP(DT_NODELABEL(_INST_NUM_TO_INSTANCE(dppic, inst_num)), source_channels), \
        (NRFX_COND_CODE_0(DT_NODE_HAS_PROP(DT_NODELABEL(_INST_NUM_TO_INSTANCE(dppic, inst_num)), sink_channels), \
                          (0), (1))), (1))

/* Variables names generation. */
#define _NRFX_DPPIC_VAR_NAME_PREFIX(dppicx) CONCAT(m_, dppicx)
#define _NRFX_DPPIC_CHANNELS_ENTRY_VAR_NAME(dppicx) \
		CONCAT(_NRFX_DPPIC_VAR_NAME_PREFIX(dppicx), _channels)

/* Variables entries generation. */
#define _NRFX_DPPI_CHANNELS_ENTRY_BY_IDX(instance) \
		static nrfx_atomic_t \
		_NRFX_DPPIC_CHANNELS_ENTRY_VAR_NAME(instance) \
		__attribute__((used)) = \
		_NRFX_DPPI_PUB_CONFIG_ALLOWED_CHANNELS_MASK(instance) | \
		_NRFX_DPPI_SUB_CONFIG_ALLOWED_CHANNELS_MASK(instance);

#define NRFX_INTERCONNECT_APB_GLOBAL_DPPI_DEFINE \
		DT_FOREACH_STATUS_OKAY(nordic_nrf_dppic_global, _NRFX_DPPI_CHANNELS_ENTRY_BY_IDX)

#define NRFX_DPPI_CHANNELS_SINGLE_VAR_NAME_BY_INST_NUM(inst_num) \
        _NRFX_DPPIC_CHANNELS_ENTRY_VAR_NAME(DT_NODELABEL(_INST_NUM_TO_INSTANCE(dppic, inst_num)))

// </e>

// </e>

// <e> NRFX_MUTEX_ENABLED - nrfx_mutex - mutex peripheral driver.
//==========================================================
#ifndef NRFX_MUTEX_ENABLED
#define NRFX_MUTEX_ENABLED 0
#endif

// <o> NRFX_MUTEX_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_MUTEX_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_MUTEX_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>

// <e> NRFX_GPIOTE_ENABLED - nrfx_gpiote - GPIOTE peripheral driver.
//==========================================================
#ifndef NRFX_GPIOTE_ENABLED
#define NRFX_GPIOTE_ENABLED 0
#endif
// <o> NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS - Number of lower power input pins.
#ifndef NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS
#define NRFX_GPIOTE_CONFIG_NUM_OF_LOW_POWER_EVENTS 1
#endif

// <o> NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_GPIOTE_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_GPIOTE_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_GPIOTE_CONFIG_LOG_ENABLED
#define NRFX_GPIOTE_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_GPIOTE_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_GPIOTE_CONFIG_LOG_LEVEL
#define NRFX_GPIOTE_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_GPIOTE_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_GPIOTE_CONFIG_INFO_COLOR
#define NRFX_GPIOTE_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_GPIOTE_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_GPIOTE_CONFIG_DEBUG_COLOR
#define NRFX_GPIOTE_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_I2S_ENABLED - nrfx_i2s - I2S peripheral driver.
//==========================================================
#ifndef NRFX_I2S_ENABLED
#define NRFX_I2S_ENABLED 0
#endif

// <o> NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_I2S_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_I2S_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_I2S_CONFIG_LOG_ENABLED
#define NRFX_I2S_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_I2S_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_I2S_CONFIG_LOG_LEVEL
#define NRFX_I2S_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_I2S_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_I2S_CONFIG_INFO_COLOR
#define NRFX_I2S_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_I2S_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_I2S_CONFIG_DEBUG_COLOR
#define NRFX_I2S_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_IPC_ENABLED - nrfx_ipc - IPC peripheral driver
//==========================================================
#ifndef NRFX_IPC_ENABLED
#define NRFX_IPC_ENABLED 0
#endif

/* Channels masks generation. */
#define _NRFX_IPC_NUM_OF_OWNED_CHANNELS(node) DT_PROP_LEN(node, owned_channels)
#define _NRFX_IPC_SHIFT_OWNED(val, node) (1 << (DT_PROP_BY_IDX(node, owned_channels, val)))
#define _NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(node) \
		COND_CODE_1(DT_NODE_HAS_PROP(node, owned_channels),	\
			(LISTIFY(_NRFX_IPC_NUM_OF_OWNED_CHANNELS(node), \
				_NRFX_IPC_SHIFT_OWNED, (|), node)), \
			(COND_CODE_1(DT_NODE_HAS_COMPAT(node, nordic_nrf_ipct_local), \
				((1 << DT_PROP(node, channels)) - 1), \
				(0))))

#define NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(ipctx_node) \
		_NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(DT_NODELABEL(ipctx_node))

#define _NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK_BY_IDX(node_id, prop, idx) \
		_NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(_IDX_TO_INSTANCE(node_id, prop, idx))

#define NRFX_IPCTx_PUB_CONFIG_ALLOWED_CHANNELS_MASK_BY_INST_NUM(inst_num) \
		COND_CODE_1(IS_EMPTY(inst_num), \
			(NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(_INST_NUM_TO_INSTANCE(DT_LOCAL_IPCT_INSTANCE, ))), \
			(NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(_INST_NUM_TO_INSTANCE(ipct, inst_num))))

#define NRFX_IPCTx_SUB_CONFIG_ALLOWED_CHANNELS_MASK_BY_INST_NUM(inst_num) \
		COND_CODE_1(IS_EMPTY(inst_num), \
			(NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(_INST_NUM_TO_INSTANCE(DT_LOCAL_IPCT_INSTANCE, ))), \
			(NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(_INST_NUM_TO_INSTANCE(ipct, inst_num))))

#define NRFX_IPCT_PUB_OR_SUB_MASK(inst_num) \
		COND_CODE_1(IS_EMPTY(inst_num), \
			(COND_CODE_1(DT_NODE_HAS_STATUS(DT_NODELABEL(_INST_NUM_TO_INSTANCE(DT_LOCAL_IPCT_INSTANCE, )), okay), (1), (0))), \
			(COND_CODE_1(DT_NODE_HAS_PROP(DT_NODELABEL(_INST_NUM_TO_INSTANCE(ipct, inst_num)), owned_channels), (1), (0))))


/* Variables names generation. */
#define _NRFX_IPCT_VAR_NAME_PREFIX(ipctx) CONCAT(m_, ipctx)
#define _NRFX_IPCT_CHANNELS_ENTRY_VAR_NAME(ipctx) \
		CONCAT(_NRFX_IPCT_VAR_NAME_PREFIX(ipctx), _channels)

/* Variables entries generation. */
#define _NRFX_IPC_CHANNELS_ENTRY_BY_IDX(instance) \
			static nrfx_atomic_t \
			_NRFX_IPCT_CHANNELS_ENTRY_VAR_NAME(instance) \
			__attribute__((used)) = \
			_NRFX_IPC_CONFIG_ALLOWED_CHANNELS_MASK(instance);

#define NRFX_INTERCONNECT_IPCT_GLOBAL_DEFINE \
		DT_FOREACH_STATUS_OKAY(nordic_nrf_ipct_global, _NRFX_IPC_CHANNELS_ENTRY_BY_IDX)

#define NRFX_IPCTx_CHANNELS_SINGLE_VAR_NAME_BY_INST_NUM(inst_num) \
	COND_CODE_1(IS_EMPTY(inst_num), \
	(_NRFX_IPCT_CHANNELS_ENTRY_VAR_NAME(DT_NODELABEL( \
		_INST_NUM_TO_INSTANCE(DT_LOCAL_IPCT_INSTANCE, )))), \
	(_NRFX_IPCT_CHANNELS_ENTRY_VAR_NAME(DT_NODELABEL( \
		_INST_NUM_TO_INSTANCE(ipct, inst_num)))))

// </e>

// <e> NRFX_LPCOMP_ENABLED - nrfx_lpcomp - LPCOMP peripheral driver
//==========================================================
#ifndef NRFX_LPCOMP_ENABLED
#define NRFX_LPCOMP_ENABLED 0
#endif

// <o> NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_LPCOMP_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_LPCOMP_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_LPCOMP_CONFIG_LOG_ENABLED
#define NRFX_LPCOMP_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_LPCOMP_CONFIG_LOG_LEVEL  - Default Severity level

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_LPCOMP_CONFIG_LOG_LEVEL
#define NRFX_LPCOMP_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_LPCOMP_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_LPCOMP_CONFIG_INFO_COLOR
#define NRFX_LPCOMP_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_LPCOMP_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_LPCOMP_CONFIG_DEBUG_COLOR
#define NRFX_LPCOMP_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_NFCT_ENABLED - nrfx_nfct - NFCT peripheral driver
//==========================================================
#ifndef NRFX_NFCT_ENABLED
#define NRFX_NFCT_ENABLED 0
#endif
// <o> NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_NFCT_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <o> NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID - Timer instance used for workarounds in the driver.

// <0=> 0
// <1=> 1
// <2=> 2

#ifndef NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID
#define NRFX_NFCT_CONFIG_TIMER_INSTANCE_ID 2
#endif

// <e> NRFX_NFCT_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_NFCT_CONFIG_LOG_ENABLED
#define NRFX_NFCT_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_NFCT_CONFIG_LOG_LEVEL  - Default Severity level

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_NFCT_CONFIG_LOG_LEVEL
#define NRFX_NFCT_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_NFCT_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_NFCT_CONFIG_INFO_COLOR
#define NRFX_NFCT_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_NFCT_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_NFCT_CONFIG_DEBUG_COLOR
#define NRFX_NFCT_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_MEMCONF_ENABLED - nrfx_memconf - MEMCONF peripheral driver
//==========================================================
#ifndef NRFX_MEMCONF_ENABLED
#define NRFX_MEMCONF_ENABLED 0
#endif

// </e>

// <e> NRFX_PDM_ENABLED - nrfx_pdm - PDM peripheral driver.
//==========================================================
#ifndef NRFX_PDM_ENABLED
#define NRFX_PDM_ENABLED 0
#endif

// <o> NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_PDM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_PDM_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_PDM_CONFIG_LOG_ENABLED
#define NRFX_PDM_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_PDM_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_PDM_CONFIG_LOG_LEVEL
#define NRFX_PDM_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_PDM_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PDM_CONFIG_INFO_COLOR
#define NRFX_PDM_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_PDM_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PDM_CONFIG_DEBUG_COLOR
#define NRFX_PDM_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_EXMIF_ENABLED - nrfx_exmif - EXMIF peripheral driver.
//==========================================================
#ifndef NRFX_EXMIF_ENABLED
#define NRFX_EXMIF_ENABLED 0
#endif
// <o> NRFX_EXMIF_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_EXMIF_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_EXMIF_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>

// <e> NRFX_EXMEE_ENABLED - nrfx_exmee - EXMEE peripheral driver.
//==========================================================
#ifndef NRFX_EXMEE_ENABLED
#define NRFX_EXMEE_ENABLED 0
#endif
// <o> NRFX_EXMEE_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_EXMEE_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_EXMEE_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>

// <e> NRFX_PRS_ENABLED - nrfx_prs - Peripheral Resource Sharing (PRS) module.
//==========================================================
#ifndef NRFX_PRS_ENABLED
#define NRFX_PRS_ENABLED 0
#endif
// <q> NRFX_PRS_BOX_0_ENABLED  - Enables box 0 in the module.

#ifndef NRFX_PRS_BOX_0_ENABLED
#define NRFX_PRS_BOX_0_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_1_ENABLED  - Enables box 1 in the module.

#ifndef NRFX_PRS_BOX_1_ENABLED
#define NRFX_PRS_BOX_1_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_2_ENABLED  - Enables box 2 in the module.

#ifndef NRFX_PRS_BOX_2_ENABLED
#define NRFX_PRS_BOX_2_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_3_ENABLED  - Enables box 3 in the module.

#ifndef NRFX_PRS_BOX_3_ENABLED
#define NRFX_PRS_BOX_3_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_4_ENABLED  - Enables box 4 in the module.

#ifndef NRFX_PRS_BOX_4_ENABLED
#define NRFX_PRS_BOX_4_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_5_ENABLED  - Enables box 5 in the module.

#ifndef NRFX_PRS_BOX_5_ENABLED
#define NRFX_PRS_BOX_5_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_6_ENABLED  - Enables box 6 in the module.

#ifndef NRFX_PRS_BOX_6_ENABLED
#define NRFX_PRS_BOX_6_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_7_ENABLED  - Enables box 7 in the module.

#ifndef NRFX_PRS_BOX_7_ENABLED
#define NRFX_PRS_BOX_7_ENABLED 0
#endif

// <q> NRFX_PRS_BOX_8_ENABLED  - Enables box 8 in the module.

#ifndef NRFX_PRS_BOX_8_ENABLED
#define NRFX_PRS_BOX_8_ENABLED 0
#endif

// <e> NRFX_PRS_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_PRS_CONFIG_LOG_ENABLED
#define NRFX_PRS_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_PRS_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_PRS_CONFIG_LOG_LEVEL
#define NRFX_PRS_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_PRS_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PRS_CONFIG_INFO_COLOR
#define NRFX_PRS_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_PRS_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PRS_CONFIG_DEBUG_COLOR
#define NRFX_PRS_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_PWM_ENABLED - nrfx_pwm - PWM peripheral driver.
//==========================================================
#ifndef NRFX_PWM_ENABLED
#define NRFX_PWM_ENABLED 0
#endif
// <q> NRFX_PWM0_ENABLED  - Enables PWM0 instance.

#ifndef NRFX_PWM0_ENABLED
#define NRFX_PWM0_ENABLED 0
#endif

// <q> NRFX_PWM1_ENABLED  - Enables PWM1 instance.

#ifndef NRFX_PWM1_ENABLED
#define NRFX_PWM1_ENABLED 0
#endif

// <q> NRFX_PWM2_ENABLED  - Enables PWM2 instance.

#ifndef NRFX_PWM2_ENABLED
#define NRFX_PWM2_ENABLED 0
#endif

// <q> NRFX_PWM3_ENABLED  - Enables PWM3 instance.

#ifndef NRFX_PWM3_ENABLED
#define NRFX_PWM3_ENABLED 0
#endif

// <q> NRFX_PWM3_ENABLED  - Enables PWM4 instance.

#ifndef NRFX_PWM4_ENABLED
#define NRFX_PWM4_ENABLED 0
#endif

// <o> NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_PWM_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_PWM_CONFIG_LOG_ENABLED
#define NRFX_PWM_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_PWM_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_PWM_CONFIG_LOG_LEVEL
#define NRFX_PWM_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_PWM_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PWM_CONFIG_INFO_COLOR
#define NRFX_PWM_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_PWM_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_PWM_CONFIG_DEBUG_COLOR
#define NRFX_PWM_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_QDEC_ENABLED - nrfx_qdec - QDEC peripheral driver
//==========================================================
#ifndef NRFX_QDEC_ENABLED
#define NRFX_QDEC_ENABLED 0
#endif

// <q> NRFX_QDEC130_ENABLED - Enable QDEC130 instance
#ifndef NRFX_QDEC130_ENABLED
#define NRFX_QDEC130_ENABLED 0
#endif

// <q> NRFX_QDEC131_ENABLED - Enable QDEC131 instance
#ifndef NRFX_QDEC131_ENABLED
#define NRFX_QDEC131_ENABLED 0
#endif

// <o> NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_QDEC_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_QDEC_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_QDEC_CONFIG_LOG_ENABLED
#define NRFX_QDEC_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_QDEC_CONFIG_LOG_LEVEL  - Default Severity level

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_QDEC_CONFIG_LOG_LEVEL
#define NRFX_QDEC_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_QDEC_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_QDEC_CONFIG_INFO_COLOR
#define NRFX_QDEC_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_QDEC_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_QDEC_CONFIG_DEBUG_COLOR
#define NRFX_QDEC_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_RTC_ENABLED - nrfx_rtc - RTC peripheral driver.
//==========================================================
#ifndef NRFX_RTC_ENABLED
#define NRFX_RTC_ENABLED 0
#endif
// <q> NRFX_RTC0_ENABLED  - Enables RTC0 instance.

#ifndef NRFX_RTC0_ENABLED
#define NRFX_RTC0_ENABLED 0
#endif

// <q> NRFX_RTC1_ENABLED  - Enables RTC1 instance.

#ifndef NRFX_RTC1_ENABLED
#define NRFX_RTC1_ENABLED 0
#endif

// <o> NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_RTC_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_RTC_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_RTC_CONFIG_LOG_ENABLED
#define NRFX_RTC_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_RTC_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_RTC_CONFIG_LOG_LEVEL
#define NRFX_RTC_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_RTC_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_RTC_CONFIG_INFO_COLOR
#define NRFX_RTC_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_RTC_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_RTC_CONFIG_DEBUG_COLOR
#define NRFX_RTC_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_SAADC_ENABLED - nrfx_saadc - SAADC peripheral driver.
//==========================================================
#ifndef NRFX_SAADC_ENABLED
#define NRFX_SAADC_ENABLED 0
#endif

// <o> NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SAADC_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_SAADC_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_SAADC_CONFIG_LOG_ENABLED
#define NRFX_SAADC_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_SAADC_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_SAADC_CONFIG_LOG_LEVEL
#define NRFX_SAADC_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_SAADC_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SAADC_CONFIG_INFO_COLOR
#define NRFX_SAADC_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_SAADC_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SAADC_CONFIG_DEBUG_COLOR
#define NRFX_SAADC_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_SPIM_ENABLED - nrfx_spim - SPIM peripheral driver.
//==========================================================
#ifndef NRFX_SPIM_ENABLED
#define NRFX_SPIM_ENABLED 0
#endif
// <q> NRFX_SPIM0_ENABLED  - Enables SPIM0 instance.

#ifndef NRFX_SPIM0_ENABLED
#define NRFX_SPIM0_ENABLED 0
#endif

// <q> NRFX_SPIM1_ENABLED  - Enables SPIM1 instance.

#ifndef NRFX_SPIM1_ENABLED
#define NRFX_SPIM1_ENABLED 0
#endif

// <q> NRFX_SPIM2_ENABLED  - Enables SPIM2 instance.

#ifndef NRFX_SPIM2_ENABLED
#define NRFX_SPIM2_ENABLED 0
#endif

// <q> NRFX_SPIM3_ENABLED  - Enables SPIM3 instance.

#ifndef NRFX_SPIM3_ENABLED
#define NRFX_SPIM3_ENABLED 0
#endif

// <q> NRFX_SPIM4_ENABLED  - Enables SPIM4 instance.

#ifndef NRFX_SPIM4_ENABLED
#define NRFX_SPIM4_ENABLED 0
#endif

// <q> NRFX_SPIM5_ENABLED  - Enables SPIM5 instance.

#ifndef NRFX_SPIM5_ENABLED
#define NRFX_SPIM5_ENABLED 0
#endif

// <q> NRFX_SPIM6_ENABLED  - Enables SPIM6 instance.

#ifndef NRFX_SPIM6_ENABLED
#define NRFX_SPIM6_ENABLED 0
#endif

// <q> NRFX_SPIM7_ENABLED  - Enables SPIM7 instance.

#ifndef NRFX_SPIM7_ENABLED
#define NRFX_SPIM7_ENABLED 0
#endif

// <q> NRFX_SPIM8_ENABLED  - Enables SPIM8 instance.

#ifndef NRFX_SPIM8_ENABLED
#define NRFX_SPIM8_ENABLED 0
#endif

// <q> NRFX_SPIM_EXTENDED_ENABLED  - Enable extended SPIM features

#ifndef NRFX_SPIM_EXTENDED_ENABLED
#define NRFX_SPIM_EXTENDED_ENABLED 0
#endif

// <o> NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_SPIM_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_SPIM_CONFIG_LOG_ENABLED
#define NRFX_SPIM_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_SPIM_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_SPIM_CONFIG_LOG_LEVEL
#define NRFX_SPIM_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_SPIM_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SPIM_CONFIG_INFO_COLOR
#define NRFX_SPIM_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_SPIM_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SPIM_CONFIG_DEBUG_COLOR
#define NRFX_SPIM_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_SPIS_ENABLED - nrfx_spis - SPIS peripheral driver.
//==========================================================
#ifndef NRFX_SPIS_ENABLED
#define NRFX_SPIS_ENABLED 0
#endif
// <q> NRFX_SPIS0_ENABLED  - Enables SPIS0 instance.

#ifndef NRFX_SPIS0_ENABLED
#define NRFX_SPIS0_ENABLED 0
#endif

// <q> NRFX_SPIS1_ENABLED  - Enables SPIS1 instance.

#ifndef NRFX_SPIS1_ENABLED
#define NRFX_SPIS1_ENABLED 0
#endif

// <q> NRFX_SPIS2_ENABLED  - Enables SPIS2 instance.

#ifndef NRFX_SPIS2_ENABLED
#define NRFX_SPIS2_ENABLED 0
#endif

// <q> NRFX_SPIS3_ENABLED  - Enables SPIS3 instance.

#ifndef NRFX_SPIS3_ENABLED
#define NRFX_SPIS3_ENABLED 0
#endif

// <q> NRFX_SPIS4_ENABLED  - Enables SPIS4 instance.

#ifndef NRFX_SPIS4_ENABLED
#define NRFX_SPIS4_ENABLED 0
#endif

// <q> NRFX_SPIS5_ENABLED  - Enables SPIS5 instance.

#ifndef NRFX_SPIS5_ENABLED
#define NRFX_SPIS5_ENABLED 0
#endif

// <q> NRFX_SPIS6_ENABLED  - Enables SPIS6 instance.

#ifndef NRFX_SPIS6_ENABLED
#define NRFX_SPIS6_ENABLED 0
#endif

// <q> NRFX_SPIS7_ENABLED  - Enables SPIS7 instance.

#ifndef NRFX_SPIS7_ENABLED
#define NRFX_SPIS7_ENABLED 0
#endif

// <q> NRFX_SPIS8_ENABLED  - Enables SPIS8 instance.

#ifndef NRFX_SPIS8_ENABLED
#define NRFX_SPIS8_ENABLED 0
#endif

// <o> NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_SPIS_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_SPIS_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_SPIS_CONFIG_LOG_ENABLED
#define NRFX_SPIS_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_SPIS_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_SPIS_CONFIG_LOG_LEVEL
#define NRFX_SPIS_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_SPIS_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SPIS_CONFIG_INFO_COLOR
#define NRFX_SPIS_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_SPIS_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_SPIS_CONFIG_DEBUG_COLOR
#define NRFX_SPIS_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <q> NRFX_SYSTICK_ENABLED  - nrfx_systick - ARM(R) SysTick driver.

#ifndef NRFX_SYSTICK_ENABLED
#define NRFX_SYSTICK_ENABLED 0
#endif

// <e> NRFX_TIMER_ENABLED - nrfx_timer - TIMER periperal driver.
//==========================================================
#ifndef NRFX_TIMER_ENABLED
#define NRFX_TIMER_ENABLED 0
#endif
// <q> NRFX_TIMER0_ENABLED  - Enables TIMER0 instance.

#ifndef NRFX_TIMER0_ENABLED
#define NRFX_TIMER0_ENABLED 0
#endif

// <q> NRFX_TIMER1_ENABLED  - Enables TIMER1 instance.

#ifndef NRFX_TIMER1_ENABLED
#define NRFX_TIMER1_ENABLED 0
#endif

// <q> NRFX_TIMER2_ENABLED  - Enables TIMER2 instance.

#ifndef NRFX_TIMER2_ENABLED
#define NRFX_TIMER2_ENABLED 0
#endif

// <q> NRFX_TIMER3_ENABLED  - Enables TIMER3 instance.

#ifndef NRFX_TIMER3_ENABLED
#define NRFX_TIMER3_ENABLED 0
#endif

// <q> NRFX_TIMER4_ENABLED  - Enables TIMER4 instance.

#ifndef NRFX_TIMER4_ENABLED
#define NRFX_TIMER4_ENABLED 0
#endif

// <q> NRFX_TIMER5_ENABLED  - Enables TIMER5 instance.

#ifndef NRFX_TIMER5_ENABLED
#define NRFX_TIMER5_ENABLED 0
#endif

// <q> NRFX_TIMER6_ENABLED  - Enables TIMER6 instance.

#ifndef NRFX_TIMER6_ENABLED
#define NRFX_TIMER6_ENABLED 0
#endif

// <q> NRFX_TIMER7_ENABLED  - Enables TIMER7 instance.

#ifndef NRFX_TIMER7_ENABLED
#define NRFX_TIMER7_ENABLED 0
#endif

// <q> NRFX_TIMER8_ENABLED  - Enables TIMER8 instance.

#ifndef NRFX_TIMER8_ENABLED
#define NRFX_TIMER8_ENABLED 0
#endif

// <q> NRFX_TIMER9_ENABLED  - Enables TIMER9 instance.

#ifndef NRFX_TIMER9_ENABLED
#define NRFX_TIMER9_ENABLED 0
#endif

// <o> NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_TIMER_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_TIMER_CONFIG_LOG_ENABLED
#define NRFX_TIMER_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_TIMER_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_TIMER_CONFIG_LOG_LEVEL
#define NRFX_TIMER_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_TIMER_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TIMER_CONFIG_INFO_COLOR
#define NRFX_TIMER_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_TIMER_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TIMER_CONFIG_DEBUG_COLOR
#define NRFX_TIMER_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_TWIM_ENABLED - nrfx_twim - TWIM peripheral driver.
//==========================================================
#ifndef NRFX_TWIM_ENABLED
#define NRFX_TWIM_ENABLED 0
#endif
// <q> NRFX_TWIM0_ENABLED  - Enables TWIM0 instance.

#ifndef NRFX_TWIM0_ENABLED
#define NRFX_TWIM0_ENABLED 0
#endif

// <q> NRFX_TWIM1_ENABLED  - Enables TWIM1 instance.

#ifndef NRFX_TWIM1_ENABLED
#define NRFX_TWIM1_ENABLED 0
#endif

// <q> NRFX_TWIM2_ENABLED  - Enables TWIM2 instance.

#ifndef NRFX_TWIM2_ENABLED
#define NRFX_TWIM2_ENABLED 0
#endif

// <q> NRFX_TWIM3_ENABLED  - Enables TWIM3 instance.

#ifndef NRFX_TWIM3_ENABLED
#define NRFX_TWIM3_ENABLED 0
#endif

// <q> NRFX_TWIM4_ENABLED  - Enables TWIM4 instance.

#ifndef NRFX_TWIM4_ENABLED
#define NRFX_TWIM4_ENABLED 0
#endif

// <q> NRFX_TWIM5_ENABLED  - Enables TWIM5 instance.

#ifndef NRFX_TWIM5_ENABLED
#define NRFX_TWIM5_ENABLED 0
#endif

// <q> NRFX_TWIM6_ENABLED  - Enables TWIM6 instance.

#ifndef NRFX_TWIM6_ENABLED
#define NRFX_TWIM6_ENABLED 0
#endif

// <q> NRFX_TWIM7_ENABLED  - Enables TWIM7 instance.

#ifndef NRFX_TWIM7_ENABLED
#define NRFX_TWIM7_ENABLED 0
#endif

// <q> NRFX_TWIM8_ENABLED  - Enables TWIM8 instance.

#ifndef NRFX_TWIM8_ENABLED
#define NRFX_TWIM8_ENABLED 0
#endif

// <o> NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TWIM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_TWIM_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_TWIM_CONFIG_LOG_ENABLED
#define NRFX_TWIM_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_TWIM_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_TWIM_CONFIG_LOG_LEVEL
#define NRFX_TWIM_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_TWIM_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TWIM_CONFIG_INFO_COLOR
#define NRFX_TWIM_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_TWIM_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TWIM_CONFIG_DEBUG_COLOR
#define NRFX_TWIM_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_TWIS_ENABLED - nrfx_twis - TWIS peripheral driver.
//==========================================================
#ifndef NRFX_TWIS_ENABLED
#define NRFX_TWIS_ENABLED 0
#endif

// <q> NRFX_TWIS0_ENABLED  - Enables TWIS0 instance.

#ifndef NRFX_TWIS0_ENABLED
#define NRFX_TWIS0_ENABLED 0
#endif

// <q> NRFX_TWIS1_ENABLED  - Enables TWIS1 instance.

#ifndef NRFX_TWIS1_ENABLED
#define NRFX_TWIS1_ENABLED 0
#endif

// <q> NRFX_TWIS2_ENABLED  - Enables TWIS2 instance.

#ifndef NRFX_TWIS2_ENABLED
#define NRFX_TWIS2_ENABLED 0
#endif

// <q> NRFX_TWIS3_ENABLED  - Enables TWIS3 instance.

#ifndef NRFX_TWIS3_ENABLED
#define NRFX_TWIS3_ENABLED 0
#endif

// <q> NRFX_TWIS4_ENABLED  - Enables TWIS4 instance.

#ifndef NRFX_TWIS4_ENABLED
#define NRFX_TWIS4_ENABLED 0
#endif

// <q> NRFX_TWIS5_ENABLED  - Enables TWIS5 instance.

#ifndef NRFX_TWIS5_ENABLED
#define NRFX_TWIS5_ENABLED 0
#endif

// <q> NRFX_TWIS6_ENABLED  - Enables TWIS6 instance.

#ifndef NRFX_TWIS6_ENABLED
#define NRFX_TWIS6_ENABLED 0
#endif

// <q> NRFX_TWIS7_ENABLED  - Enables TWIS7 instance.

#ifndef NRFX_TWIS7_ENABLED
#define NRFX_TWIS7_ENABLED 0
#endif

// <q> NRFX_TWIS8_ENABLED  - Enables TWIS8 instance.

#ifndef NRFX_TWIS8_ENABLED
#define NRFX_TWIS8_ENABLED 0
#endif

// <q> NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY  - Assumes that any instance would be initialized only once.

// <i> Optimization flag. Registers used by TWIS are shared by other peripherals. Normally, during initialization driver tries to clear all registers to known state before doing the initialization itself. This gives initialization safe procedure, no matter when it would be called. If you activate TWIS only once and do never uninitialize it - set this flag to 1 what gives more optimal code.

#ifndef NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY
#define NRFX_TWIS_ASSUME_INIT_AFTER_RESET_ONLY 0
#endif

// <q> NRFX_TWIS_NO_SYNC_MODE  - Removes support for synchronous mode.

// <i> Synchronous mode would be used in specific situations. And it uses some additional code and data memory to safely process state machine by polling it in status functions. If this functionality is not required it may be disabled to free some resources.

#ifndef NRFX_TWIS_NO_SYNC_MODE
#define NRFX_TWIS_NO_SYNC_MODE 0
#endif

// <o> NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TWIS_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_TWIS_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_TWIS_CONFIG_LOG_ENABLED
#define NRFX_TWIS_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_TWIS_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_TWIS_CONFIG_LOG_LEVEL
#define NRFX_TWIS_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_TWIS_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TWIS_CONFIG_INFO_COLOR
#define NRFX_TWIS_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_TWIS_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_TWIS_CONFIG_DEBUG_COLOR
#define NRFX_TWIS_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <e> NRFX_UARTE_ENABLED - nrfx_uarte - UARTE peripheral driver.
//==========================================================
#ifndef NRFX_UARTE_ENABLED
#define NRFX_UARTE_ENABLED 0
#endif
// <q> NRFX_UARTE0_ENABLED  - Enables UARTE0 instance.

#ifndef NRFX_UARTE0_ENABLED
#define NRFX_UARTE0_ENABLED 0
#endif

// <q> NRFX_UARTE1_ENABLED  - Enables UARTE1 instance.

#ifndef NRFX_UARTE1_ENABLED
#define NRFX_UARTE1_ENABLED 0
#endif

// <q> NRFX_UARTE2_ENABLED  - Enables UARTE2 instance.

#ifndef NRFX_UARTE2_ENABLED
#define NRFX_UARTE2_ENABLED 0
#endif

// <q> NRFX_UARTE3_ENABLED  - Enables UARTE3 instance.

#ifndef NRFX_UARTE3_ENABLED
#define NRFX_UARTE3_ENABLED 0
#endif

// <q> NRFX_UARTE4_ENABLED  - Enables UARTE4 instance.

#ifndef NRFX_UARTE4_ENABLED
#define NRFX_UARTE4_ENABLED 0
#endif

// <q> NRFX_UARTE5_ENABLED  - Enables UARTE5 instance.

#ifndef NRFX_UARTE5_ENABLED
#define NRFX_UARTE5_ENABLED 0
#endif

// <q> NRFX_UARTE6_ENABLED  - Enables UARTE6 instance.

#ifndef NRFX_UARTE6_ENABLED
#define NRFX_UARTE6_ENABLED 0
#endif

// <q> NRFX_UARTE7_ENABLED  - Enables UARTE7 instance.

#ifndef NRFX_UARTE7_ENABLED
#define NRFX_UARTE7_ENABLED 0
#endif

// <q> NRFX_UARTE8_ENABLED  - Enables UARTE8 instance.

#ifndef NRFX_UARTE8_ENABLED
#define NRFX_UARTE8_ENABLED 0
#endif

// <o> NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_UARTE_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_UARTE_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_UARTE_CONFIG_LOG_ENABLED
#define NRFX_UARTE_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_UARTE_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_UARTE_CONFIG_LOG_LEVEL
#define NRFX_UARTE_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_UARTE_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_UARTE_CONFIG_INFO_COLOR
#define NRFX_UARTE_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_UARTE_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_UARTE_CONFIG_DEBUG_COLOR
#define NRFX_UARTE_CONFIG_DEBUG_COLOR 0
#endif

// </e>

// </e>

// <o> NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK - GRTC CC channels ownership mask.
#ifndef NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK

/* TODO: Remove `child-owned-channels` property when it will be possible determine
 *       which channels should be owned by child core.
 *	 Then the `NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK` parameter should equal:
 *	 - for APP: `owned-channels-by-app` & ~`owned-channels-by-child-core`
 *	 - for child-core: `owned-channels-by-child-core`
 */

#define _NRFX_GRTC_NUM_OF_OWNED_CHANNELS DT_PROP_LEN(DT_INST(0, \
			nordic_nrf_grtc), owned_channels)
#define _NRFX_GRTC_SHIFT_OWNED(val, _) (1 << (DT_PROP_BY_IDX(DT_INST(0, \
			nordic_nrf_grtc), owned_channels, val)))
#define _NRFX_GRTC_OWNED_CHANNEL_MASK \
			(LISTIFY(_NRFX_GRTC_NUM_OF_OWNED_CHANNELS, _NRFX_GRTC_SHIFT_OWNED, (|)))

#if DT_NODE_HAS_PROP(DT_INST(0, nordic_nrf_grtc), child_owned_channels)
#define _NRFX_GRTC_SHIFT_FORBIDDEN(val, _) (1 << (DT_PROP_BY_IDX(DT_INST(0, \
			nordic_nrf_grtc), child_owned_channels, val)))
#define _NRFX_GRTC_NUM_OF_FORBIDDEN_CHANNELS DT_PROP_LEN(DT_INST(0, \
			nordic_nrf_grtc), child_owned_channels)
#define NRFX_GRTC_CONFIG_FORBIDDEN_CC_CHANNEL_MASK \
			(LISTIFY(_NRFX_GRTC_NUM_OF_FORBIDDEN_CHANNELS, _NRFX_GRTC_SHIFT_FORBIDDEN, (|)))
#else
#define _NRFX_GRTC_NUM_OF_FORBIDDEN_CHANNELS 0
#define NRFX_GRTC_CONFIG_FORBIDDEN_CC_CHANNEL_MASK 0
#endif

#define NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS \
			(_NRFX_GRTC_NUM_OF_OWNED_CHANNELS - _NRFX_GRTC_NUM_OF_FORBIDDEN_CHANNELS)
#define NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK \
			(_NRFX_GRTC_OWNED_CHANNEL_MASK &~ NRFX_GRTC_CONFIG_FORBIDDEN_CC_CHANNEL_MASK)

#if((_NRFX_GRTC_OWNED_CHANNEL_MASK | NRFX_GRTC_CONFIG_FORBIDDEN_CC_CHANNEL_MASK) != \
		_NRFX_GRTC_OWNED_CHANNEL_MASK)
#error `child-owned-channels` parameter must be a subset of `owned-channels` parameter.
#endif

#endif /* NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK */
// </h>

#ifndef NRFX_TBM_ENABLED
#define NRFX_TBM_ENABLED 1
#endif

#ifndef NRFX_TBM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TBM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

#endif // NRFX_CONFIG_LILIUMSOC1_GLOBAL_H__
