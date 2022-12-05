/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRFX_CONFIG_NRF7140_LMAC_H__
#define NRFX_CONFIG_NRF7140_LMAC_H__

// <h> nRF_Drivers

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

// <o> NRFX_DPPIC_CONFIG_ALLOWED_CHANNELS_MASK - DPPI channels ownership mask.
#define NRFX_DPPIC120_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000000
#define NRFX_DPPIC130_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000FF
#define NRFX_DPPIC131_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000000
#define NRFX_DPPIC132_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000000
#define NRFX_DPPIC133_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x0000001E
#define NRFX_DPPIC134_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000020
#define NRFX_DPPIC135_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000040
#define NRFX_DPPIC136_PUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000081
#define NRFX_DPPIC120_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000000
#define NRFX_DPPIC130_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000FF
#define NRFX_DPPIC131_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000FF
#define NRFX_DPPIC132_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x00000000
#define NRFX_DPPIC133_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000E1
#define NRFX_DPPIC134_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000DF
#define NRFX_DPPIC135_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x000000BF
#define NRFX_DPPIC136_SUB_CONFIG_ALLOWED_CHANNELS_MASK 0x0000007E

// </e>

// </e>

// <e> NRFX_GRTC_ENABLED - nrfx_grtc - GRTC peripheral driver
//==========================================================
#ifndef NRFX_GRTC_ENABLED
#define NRFX_GRTC_ENABLED 1
#endif

// <o> NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK - GRTC CC channels ownership mask.
#ifndef NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK
#define NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK 0x000000C0
#endif

// <o> NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS - GRTC number of assigned CC channels.
#ifndef NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS
#define NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS 2
#endif

// </e>

// <e> NRFX_GPIOTE_ENABLED - nrfx_gpiote - GPIOTE peripheral driver.
//==========================================================
#ifndef NRFX_GPIOTE_ENABLED
#define NRFX_GPIOTE_ENABLED 1
#endif

// </e>

// <e> NRFX_VEVIF_ENABLED - nrfx_vevif - VEVIF mechanism driver
//==========================================================
#ifndef NRFX_VEVIF_ENABLED
#define NRFX_VEVIF_ENABLED 1
#endif

// </e>


// <e> NRFX_TBM_ENABLED - nrfx_tbm - TBM (Trace Buffer Monitor) driver
//==========================================================
#ifndef NRFX_TBM_ENABLED
#define NRFX_TBM_ENABLED 1
#endif

// <o> NRFX_TBM_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority.

// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7

#ifndef NRFX_TBM_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_TBM_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif
// </e>

// </h>

#endif // NRFX_CONFIG_NRF7140_LMAC_H__
