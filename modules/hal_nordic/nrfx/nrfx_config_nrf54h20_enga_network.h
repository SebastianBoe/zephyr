/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#ifndef NRFX_CONFIG_LILIUMSOC1_NETWORK_H__
#define NRFX_CONFIG_LILIUMSOC1_NETWORK_H__

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

#define NRFX_INTERCONNECT_APB_LOCAL_DPPI_DEFINE \
		DT_FOREACH_STATUS_OKAY(nordic_nrf_dppic_local, _NRFX_DPPI_CHANNELS_ENTRY_BY_IDX)

#define DT_LOCAL_IPCT_INSTANCE cpurad_ipct

#define NRFX_INTERCONNECT_IPCT_LOCAL_DEFINE \
		DT_FOREACH_STATUS_OKAY(nordic_nrf_ipct_local, _NRFX_IPC_CHANNELS_ENTRY_BY_IDX)

// </e>

// </e>

#endif // NRFX_CONFIG_LILIUMSOC1_NETWORK_H__
