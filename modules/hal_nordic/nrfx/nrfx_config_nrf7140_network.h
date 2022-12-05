/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRFX_CONFIG_NRF7140_NETWORK_H__
#define NRFX_CONFIG_NRF7140_NETWORK_H__

// <h> nRF_Drivers

// <q> NRFX_SYSTICK_ENABLED  - nrfx_systick - ARM(R) SysTick driver

#ifndef NRFX_SYSTICK_ENABLED
#define NRFX_SYSTICK_ENABLED 1
#endif

// <e> NRFX_BELLBOARD_ENABLED - nrfx_bellboard - BELLBOARD peripheral driver
//==========================================================
#ifndef NRFX_BELLBOARD_ENABLED
#define NRFX_BELLBOARD_ENABLED 1
#endif
// <q> NRFX_BELLBOARD0_ENABLED  - Enable BELLBOARD0 instance
#ifndef NRFX_BELLBOARD0_ENABLED
#define NRFX_BELLBOARD0_ENABLED 1
#endif
// <q> NRFX_BELLBOARD1_ENABLED  - Enable BELLBOARD1 instance
#ifndef NRFX_BELLBOARD1_ENABLED
#define NRFX_BELLBOARD1_ENABLED 1
#endif
// <q> NRFX_BELLBOARD2_ENABLED  - Enable BELLBOARD2 instance
#ifndef NRFX_BELLBOARD2_ENABLED
#define NRFX_BELLBOARD2_ENABLED 1
#endif
// <q> NRFX_BELLBOARD3_ENABLED  - Enable BELLBOARD3 instance
#ifndef NRFX_BELLBOARD3_ENABLED
#define NRFX_BELLBOARD3_ENABLED 1
#endif

// <o> NRFX_BELLBOARD_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority
// <0=> 0 (highest)
// <1=> 1
// <2=> 2
// <3=> 3
// <4=> 4
// <5=> 5
// <6=> 6
// <7=> 7
#ifndef NRFX_BELLBOARD_DEFAULT_CONFIG_IRQ_PRIORITY
#define NRFX_BELLBOARD_DEFAULT_CONFIG_IRQ_PRIORITY 7
#endif

// </e>

// <e> NRFX_EGU_ENABLED - nrfx_egu - EGU peripheral driver.
//==========================================================
#ifndef NRFX_EGU_ENABLED
#define NRFX_EGU_ENABLED 1
#endif

// <q> NRFX_EGU020_ENABLED  - Enable EGU020 instance.

#ifndef NRFX_EGU020_ENABLED
#define NRFX_EGU020_ENABLED 1
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

// <e> NRFX_GPIOTE_ENABLED - nrfx_gpiote - GPIOTE peripheral driver.
//==========================================================
#ifndef NRFX_GPIOTE_ENABLED
#define NRFX_GPIOTE_ENABLED 1
#endif

// </e>

// <e> NRFX_MVDMA_ENABLED - nrfx_mvdma - MVDMA peripheral driver
//==========================================================
#ifndef NRFX_MVDMA_ENABLED
#define NRFX_MVDMA_ENABLED 1
#endif

// </e>

// <e> NRFX_TIMER_ENABLED - nrfx_timer - TIMER periperal driver
//==========================================================
#ifndef NRFX_TIMER_ENABLED
#define NRFX_TIMER_ENABLED 1
#endif

// <q> NRFX_TIMER020_ENABLED  - Enables TIMER020 instance.

#ifndef NRFX_TIMER020_ENABLED
#define NRFX_TIMER020_ENABLED 1
#endif

// <q> NRFX_TIMER021_ENABLED  - Enables TIMER021 instance.

#ifndef NRFX_TIMER021_ENABLED
#define NRFX_TIMER021_ENABLED 1
#endif

// <q> NRFX_TIMER022_ENABLED  - Enables TIMER022 instance.

#ifndef NRFX_TIMER022_ENABLED
#define NRFX_TIMER022_ENABLED 1
#endif

// <o> NRFX_TIMER_DEFAULT_CONFIG_IRQ_PRIORITY  - Interrupt priority

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
// <o> NRFX_TIMER_CONFIG_LOG_LEVEL  - Default Severity level

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

// <e> NRFX_WDT_ENABLED - nrfx_wdt - WDT peripheral driver.
//==========================================================
#ifndef NRFX_WDT_ENABLED
#define NRFX_WDT_ENABLED 1
#endif
// <q> NRFX_WDT010_ENABLED  - Enable WDT010 instance.


#ifndef NRFX_WDT010_ENABLED
#define NRFX_WDT010_ENABLED 0
#endif

// <q> NRFX_WDT011_ENABLED  - Enable WDT011 instance.


#ifndef NRFX_WDT011_ENABLED
#define NRFX_WDT011_ENABLED 0
#endif

// <o> NRFX_WDT_CONFIG_NO_IRQ  - Remove WDT IRQ handling from WDT driver.

// <0=> Include WDT IRQ handling
// <1=> Remove WDT IRQ handling

#ifndef NRFX_WDT_CONFIG_NO_IRQ
#define NRFX_WDT_CONFIG_NO_IRQ 0
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

// <e> NRFX_WDT_CONFIG_LOG_ENABLED - Enables logging in the module.
//==========================================================
#ifndef NRFX_WDT_CONFIG_LOG_ENABLED
#define NRFX_WDT_CONFIG_LOG_ENABLED 0
#endif
// <o> NRFX_WDT_CONFIG_LOG_LEVEL  - Default severity level.

// <0=> Off
// <1=> Error
// <2=> Warning
// <3=> Info
// <4=> Debug

#ifndef NRFX_WDT_CONFIG_LOG_LEVEL
#define NRFX_WDT_CONFIG_LOG_LEVEL 3
#endif

// <o> NRFX_WDT_CONFIG_INFO_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_WDT_CONFIG_INFO_COLOR
#define NRFX_WDT_CONFIG_INFO_COLOR 0
#endif

// <o> NRFX_WDT_CONFIG_DEBUG_COLOR  - ANSI escape code prefix.

// <0=> Default
// <1=> Black
// <2=> Red
// <3=> Green
// <4=> Yellow
// <5=> Blue
// <6=> Magenta
// <7=> Cyan
// <8=> White

#ifndef NRFX_WDT_CONFIG_DEBUG_COLOR
#define NRFX_WDT_CONFIG_DEBUG_COLOR 0
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
#define NRFX_GRTC_CONFIG_ALLOWED_CC_CHANNELS_MASK 0x00000F00
#endif

// <o> NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS - GRTC number of assigned CC channels.
#ifndef NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS
#define NRFX_GRTC_CONFIG_NUM_OF_CC_CHANNELS 4
#endif

// </e>

// </h>

#endif // NRFX_CONFIG_NRF7140_NETWORK_H__
