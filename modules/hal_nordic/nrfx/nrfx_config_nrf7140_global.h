/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRFX_CONFIG_NRF7140_GLOBAL_H__
#define NRFX_CONFIG_NRF7140_GLOBAL_H__

#include <zephyr/devicetree.h>

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
#define NRFX_COMP_ENABLED 1
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
#define NRFX_DPPI_ENABLED 0
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

// </e>

#if !defined(LILIUMSOC1_XXAA)
// <e> NRFX_EGU_ENABLED - nrfx_egu - EGU peripheral driver.
//==========================================================
#ifndef NRFX_EGU_ENABLED
#define NRFX_EGU_ENABLED 1
#endif

// <q> NRFX_EGU0_ENABLED  - Enable EGU0 instance.

#ifndef NRFX_EGU130_ENABLED
#define NRFX_EGU130_ENABLED 1
#endif

// <o> NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_EGU_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>
#endif

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

// <e> NRFX_GRTC_ENABLED - nrfx_grtc - GRTC peripheral driver.
//==========================================================
#ifndef NRFX_GRTC_ENABLED
#define NRFX_GRTC_ENABLED 0
#endif

// </e>

// <o> NRFX_GRTC_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_GRTC_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_GRTC_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// <e> NRFX_GRTC_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_GRTC_CONFIG_LOG_ENABLED
#define NRFX_GRTC_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_GRTC_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_GRTC_CONFIG_LOG_LEVEL
#define NRFX_GRTC_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_GRTC_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_GRTC_CONFIG_INFO_COLOR
#define NRFX_GRTC_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_GRTC_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_GRTC_CONFIG_DEBUG_COLOR
#define NRFX_GRTC_CONFIG_DEBUG_COLOR 0
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

// </e>

// </e>

// <e> NRFX_I2S_ENABLED - nrfx_i2s - I2S peripheral driver.
//==========================================================
#ifndef NRFX_I2S_ENABLED
#define NRFX_I2S_ENABLED 1
#endif

// <q> NRFX_I2S130_ENABLED  - Enable I2S130 instance.

#ifndef NRFX_I2S130_ENABLED
#define NRFX_I2S130_ENABLED 1
#endif

// <q> NRFX_I2S131_ENABLED  - Enable I2S131 instance.

#ifndef NRFX_I2S131_ENABLED
#define NRFX_I2S131_ENABLED 1
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

// </e>

// <e> NRFX_LPCOMP_ENABLED - nrfx_lpcomp - LPCOMP peripheral driver
//==========================================================
#ifndef NRFX_LPCOMP_ENABLED
#define NRFX_LPCOMP_ENABLED 1
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
// <e> NRFX_MEMCONF_ENABLED - nrfx_memconf - MEMCONF peripheral driver
//==========================================================
#ifndef NRFX_MEMCONF_ENABLED
#define NRFX_MEMCONF_ENABLED 0
#endif

// </e>

// <e> NRFX_PDM_ENABLED - nrfx_pdm - PDM peripheral driver.
//==========================================================
#ifndef NRFX_PDM_ENABLED
#define NRFX_PDM_ENABLED 1
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
#define NRFX_PRS_ENABLED 1
#endif
// <q> NRFX_PRS_BOX_0_ENABLED  - Enables box 0 in the module.

#ifndef NRFX_PRS_BOX_0_ENABLED
#define NRFX_PRS_BOX_0_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_1_ENABLED  - Enables box 1 in the module.

#ifndef NRFX_PRS_BOX_1_ENABLED
#define NRFX_PRS_BOX_1_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_2_ENABLED  - Enables box 2 in the module.

#ifndef NRFX_PRS_BOX_2_ENABLED
#define NRFX_PRS_BOX_2_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_3_ENABLED  - Enables box 3 in the module.

#ifndef NRFX_PRS_BOX_3_ENABLED
#define NRFX_PRS_BOX_3_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_4_ENABLED  - Enables box 4 in the module.

#ifndef NRFX_PRS_BOX_4_ENABLED
#define NRFX_PRS_BOX_4_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_5_ENABLED  - Enables box 5 in the module.

#ifndef NRFX_PRS_BOX_5_ENABLED
#define NRFX_PRS_BOX_5_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_6_ENABLED  - Enables box 6 in the module.

#ifndef NRFX_PRS_BOX_6_ENABLED
#define NRFX_PRS_BOX_6_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_7_ENABLED  - Enables box 7 in the module.

#ifndef NRFX_PRS_BOX_7_ENABLED
#define NRFX_PRS_BOX_7_ENABLED 1
#endif

// <q> NRFX_PRS_BOX_8_ENABLED  - Enables box 8 in the module.

#ifndef NRFX_PRS_BOX_8_ENABLED
#define NRFX_PRS_BOX_8_ENABLED 1
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
#define NRFX_PWM_ENABLED 1
#endif
// <q> NRFX_PWM120_ENABLED  - Enables PWM120 instance.

#ifndef NRFX_PWM120_ENABLED
#define NRFX_PWM120_ENABLED 1
#endif

// <q> NRFX_PWM130_ENABLED  - Enables PWM130 instance.

#ifndef NRFX_PWM130_ENABLED
#define NRFX_PWM130_ENABLED 1
#endif

// <q> NRFX_PWM131_ENABLED  - Enables PWM131 instance.

#ifndef NRFX_PWM131_ENABLED
#define NRFX_PWM131_ENABLED 1
#endif

// <q> NRFX_PWM132_ENABLED  - Enables PWM132 instance.

#ifndef NRFX_PWM132_ENABLED
#define NRFX_PWM132_ENABLED 1
#endif

// <q> NRFX_PWM133_ENABLED  - Enables PWM133 instance.

#ifndef NRFX_PWM133_ENABLED
#define NRFX_PWM133_ENABLED 1
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
#define NRFX_QDEC_ENABLED 1
#endif

// <q> NRFX_QDEC130_ENABLED  - Enable QDEC130 instance

#ifndef NRFX_QDEC130_ENABLED
#define NRFX_QDEC130_ENABLED 1
#endif

// <q> NRFX_QDEC131_ENABLED  - Enable QDEC131 instance

#ifndef NRFX_QDEC131_ENABLED
#define NRFX_QDEC131_ENABLED 1
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
#define NRFX_RTC_ENABLED 1
#endif
// <q> NRFX_RTC130_ENABLED  - Enables RTC130 instance.

#ifndef NRFX_RTC130_ENABLED
#define NRFX_RTC130_ENABLED 1
#endif

// <q> NRFX_RTC131_ENABLED  - Enables RTC131 instance.

#ifndef NRFX_RTC131_ENABLED
#define NRFX_RTC131_ENABLED 1
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
#define NRFX_SPIM_ENABLED 1
#endif
// <q> NRFX_SPIM120_ENABLED  - Enables SPIM120 instance.

#ifndef NRFX_SPIM120_ENABLED
#define NRFX_SPIM120_ENABLED 1
#endif

// <q> NRFX_SPIM121_ENABLED  - Enables SPIM121 instance.

#ifndef NRFX_SPIM121_ENABLED
#define NRFX_SPIM121_ENABLED 1
#endif

// <q> NRFX_SPIM130_ENABLED  - Enables SPIM130 instance.

#ifndef NRFX_SPIM130_ENABLED
#define NRFX_SPIM130_ENABLED 1
#endif

// <q> NRFX_SPIM131_ENABLED  - Enables SPIM131 instance.

#ifndef NRFX_SPIM131_ENABLED
#define NRFX_SPIM131_ENABLED 1
#endif

// <q> NRFX_SPIM132_ENABLED  - Enables SPIM132 instance.

#ifndef NRFX_SPIM132_ENABLED
#define NRFX_SPIM132_ENABLED 1
#endif

// <q> NRFX_SPIM133_ENABLED  - Enables SPIM133 instance.

#ifndef NRFX_SPIM133_ENABLED
#define NRFX_SPIM133_ENABLED 1
#endif

// <q> NRFX_SPIM134_ENABLED  - Enables SPIM134 instance.

#ifndef NRFX_SPIM134_ENABLED
#define NRFX_SPIM134_ENABLED 1
#endif

// <q> NRFX_SPIM135_ENABLED  - Enables SPIM135 instance.

#ifndef NRFX_SPIM135_ENABLED
#define NRFX_SPIM135_ENABLED 1
#endif

// <q> NRFX_SPIM136_ENABLED  - Enables SPIM136 instance.

#ifndef NRFX_SPIM136_ENABLED
#define NRFX_SPIM136_ENABLED 1
#endif

// <q> NRFX_SPIM137_ENABLED  - Enables SPIM137 instance.

#ifndef NRFX_SPIM137_ENABLED
#define NRFX_SPIM137_ENABLED 1
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
#define NRFX_SPIS_ENABLED 1
#endif

// <q> NRFX_SPIS120_ENABLED  - Enables SPIS120 instance.

#ifndef NRFX_SPIS120_ENABLED
#define NRFX_SPIS120_ENABLED 1
#endif

// <q> NRFX_SPIS130_ENABLED  - Enables SPIS130 instance.

#ifndef NRFX_SPIS130_ENABLED
#define NRFX_SPIS130_ENABLED 1
#endif

// <q> NRFX_SPIS131_ENABLED  - Enables SPIS131 instance.

#ifndef NRFX_SPIS131_ENABLED
#define NRFX_SPIS131_ENABLED 1
#endif

// <q> NRFX_SPIS132_ENABLED  - Enables SPIS132 instance.

#ifndef NRFX_SPIS132_ENABLED
#define NRFX_SPIS132_ENABLED 1
#endif

// <q> NRFX_SPIS133_ENABLED  - Enables SPIS133 instance.

#ifndef NRFX_SPIS133_ENABLED
#define NRFX_SPIS133_ENABLED 1
#endif

// <q> NRFX_SPIS134_ENABLED  - Enables SPIS134 instance.

#ifndef NRFX_SPIS134_ENABLED
#define NRFX_SPIS134_ENABLED 1
#endif

// <q> NRFX_SPIS135_ENABLED  - Enables SPIS135 instance.

#ifndef NRFX_SPIS135_ENABLED
#define NRFX_SPIS135_ENABLED 1
#endif

// <q> NRFX_SPIS136_ENABLED  - Enables SPIS136 instance.

#ifndef NRFX_SPIS136_ENABLED
#define NRFX_SPIS136_ENABLED 1
#endif

// <q> NRFX_SPIS137_ENABLED  - Enables SPIS137 instance.

#ifndef NRFX_SPIS137_ENABLED
#define NRFX_SPIS137_ENABLED 1
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
#define NRFX_TIMER_ENABLED 1
#endif

// <q> NRFX_TIMER120_ENABLED  - Enables TIMER120 instance.

#ifndef NRFX_TIMER120_ENABLED
#define NRFX_TIMER120_ENABLED 1
#endif

// <q> NRFX_TIMER121_ENABLED  - Enables TIMER121 instance.

#ifndef NRFX_TIMER121_ENABLED
#define NRFX_TIMER121_ENABLED 1
#endif

// <q> NRFX_TIMER130_ENABLED  - Enables TIMER130 instance.

#ifndef NRFX_TIMER130_ENABLED
#define NRFX_TIMER130_ENABLED 1
#endif

// <q> NRFX_TIMER131_ENABLED  - Enables TIMER131 instance.

#ifndef NRFX_TIMER131_ENABLED
#define NRFX_TIMER131_ENABLED 1
#endif

// <q> NRFX_TIMER132_ENABLED  - Enables TIMER132 instance.

#ifndef NRFX_TIMER132_ENABLED
#define NRFX_TIMER132_ENABLED 1
#endif

// <q> NRFX_TIMER133_ENABLED  - Enables TIMER133 instance.

#ifndef NRFX_TIMER133_ENABLED
#define NRFX_TIMER133_ENABLED 1
#endif

// <q> NRFX_TIMER134_ENABLED  - Enables TIMER134 instance.

#ifndef NRFX_TIMER134_ENABLED
#define NRFX_TIMER134_ENABLED 1
#endif

// <q> NRFX_TIMER135_ENABLED  - Enables TIMER135 instance.

#ifndef NRFX_TIMER135_ENABLED
#define NRFX_TIMER135_ENABLED 1
#endif

// <q> NRFX_TIMER136_ENABLED  - Enables TIMER136 instance.

#ifndef NRFX_TIMER136_ENABLED
#define NRFX_TIMER136_ENABLED 1
#endif

// <q> NRFX_TIMER137_ENABLED  - Enables TIMER137 instance.

#ifndef NRFX_TIMER137_ENABLED
#define NRFX_TIMER137_ENABLED 1
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
#define NRFX_TWIM_ENABLED 1
#endif

// <q> NRFX_TWIM130_ENABLED  - Enables TWIM130 instance.

#ifndef NRFX_TWIM130_ENABLED
#define NRFX_TWIM130_ENABLED 1
#endif

// <q> NRFX_TWIM131_ENABLED  - Enables TWIM131 instance.

#ifndef NRFX_TWIM131_ENABLED
#define NRFX_TWIM131_ENABLED 1
#endif

// <q> NRFX_TWIM132_ENABLED  - Enables TWIM132 instance.

#ifndef NRFX_TWIM132_ENABLED
#define NRFX_TWIM132_ENABLED 1
#endif

// <q> NRFX_TWIM133_ENABLED  - Enables TWIM133 instance.

#ifndef NRFX_TWIM133_ENABLED
#define NRFX_TWIM133_ENABLED 1
#endif

// <q> NRFX_TWIM134_ENABLED  - Enables TWIM134 instance.

#ifndef NRFX_TWIM134_ENABLED
#define NRFX_TWIM134_ENABLED 1
#endif

// <q> NRFX_TWIM135_ENABLED  - Enables TWIM135 instance.

#ifndef NRFX_TWIM135_ENABLED
#define NRFX_TWIM135_ENABLED 1
#endif

// <q> NRFX_TWIM136_ENABLED  - Enables TWIM136 instance.

#ifndef NRFX_TWIM136_ENABLED
#define NRFX_TWIM136_ENABLED 1
#endif

// <q> NRFX_TWIM137_ENABLED  - Enables TWIM137 instance.

#ifndef NRFX_TWIM137_ENABLED
#define NRFX_TWIM137_ENABLED 1
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
#define NRFX_TWIS_ENABLED 1
#endif

// <q> NRFX_TWIS130_ENABLED  - Enables TWIS130 instance.

#ifndef NRFX_TWIS130_ENABLED
#define NRFX_TWIS130_ENABLED 1
#endif

// <q> NRFX_TWIS131_ENABLED  - Enables TWIS131 instance.

#ifndef NRFX_TWIS131_ENABLED
#define NRFX_TWIS131_ENABLED 1
#endif

// <q> NRFX_TWIS132_ENABLED  - Enables TWIS132 instance.

#ifndef NRFX_TWIS132_ENABLED
#define NRFX_TWIS132_ENABLED 1
#endif

// <q> NRFX_TWIS133_ENABLED  - Enables TWIS133 instance.

#ifndef NRFX_TWIS133_ENABLED
#define NRFX_TWIS133_ENABLED 1
#endif

// <q> NRFX_TWIS134_ENABLED  - Enables TWIS134 instance.

#ifndef NRFX_TWIS134_ENABLED
#define NRFX_TWIS134_ENABLED 1
#endif

// <q> NRFX_TWIS135_ENABLED  - Enables TWIS135 instance.

#ifndef NRFX_TWIS135_ENABLED
#define NRFX_TWIS135_ENABLED 1
#endif

// <q> NRFX_TWIS136_ENABLED  - Enables TWIS136 instance.

#ifndef NRFX_TWIS136_ENABLED
#define NRFX_TWIS136_ENABLED 1
#endif

// <q> NRFX_TWIS137_ENABLED  - Enables TWIS137 instance.

#ifndef NRFX_TWIS137_ENABLED
#define NRFX_TWIS137_ENABLED 1
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
#define NRFX_UARTE_ENABLED 1
#endif

// <q> NRFX_UARTE120_ENABLED  - Enables UARTE120 instance.

#ifndef NRFX_UARTE120_ENABLED
#define NRFX_UARTE120_ENABLED 1
#endif

// <q> NRFX_UARTE130_ENABLED  - Enables UARTE130 instance.

#ifndef NRFX_UARTE130_ENABLED
#define NRFX_UARTE130_ENABLED 1
#endif

// <q> NRFX_UARTE131_ENABLED  - Enables UARTE131 instance.

#ifndef NRFX_UARTE131_ENABLED
#define NRFX_UARTE131_ENABLED 1
#endif

// <q> NRFX_UARTE132_ENABLED  - Enables UARTE132 instance.

#ifndef NRFX_UARTE132_ENABLED
#define NRFX_UARTE132_ENABLED 1
#endif

// <q> NRFX_UARTE133_ENABLED  - Enables UARTE133 instance.

#ifndef NRFX_UARTE133_ENABLED
#define NRFX_UARTE133_ENABLED 1
#endif

// <q> NRFX_UARTE134_ENABLED  - Enables UARTE134 instance.

#ifndef NRFX_UARTE134_ENABLED
#define NRFX_UARTE134_ENABLED 1
#endif

// <q> NRFX_UARTE135_ENABLED  - Enables UARTE135 instance.

#ifndef NRFX_UARTE135_ENABLED
#define NRFX_UARTE135_ENABLED 1
#endif

// <q> NRFX_UARTE136_ENABLED  - Enables UARTE136 instance.

#ifndef NRFX_UARTE136_ENABLED
#define NRFX_UARTE136_ENABLED 1
#endif

// <q> NRFX_UARTE137_ENABLED  - Enables UARTE137 instance.

#ifndef NRFX_UARTE137_ENABLED
#define NRFX_UARTE137_ENABLED 1
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

// <e> NRFX_WDT_ENABLED - nrfx_wdt - WDT peripheral driver.
//==========================================================
#ifndef NRFX_WDT_ENABLED
#define NRFX_WDT_ENABLED 1
#endif

// <q> NRFX_WDT131_ENABLED  - Enables WDT131 instance.

#ifndef NRFX_WDT131_ENABLED
#define NRFX_WDT131_ENABLED 1
#endif

// <q> NRFX_WDT132_ENABLED  - Enables WDT132 instance.

#ifndef NRFX_WDT132_ENABLED
#define NRFX_WDT132_ENABLED 0
#endif

// <o> NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_WDT_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>

// </h>

#ifndef NRFX_NFCT_ENABLED
#define NRFX_NFCT_ENABLED 1
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

#if defined(NRF_SYSCTRL)
#define NRFX_MVDMA110_ENABLED 1
#undef NRFX_MVDMA_ENABLED
#define NRFX_MVDMA_ENABLED 0
#endif

#endif // NRFX_CONFIG_NRF7140_GLOBAL_H__
