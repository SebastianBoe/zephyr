/*
 * Copyright (c) 2022, Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NRFX_CONFIG_NRF9230_APPLICATION_H__
#define NRFX_CONFIG_NRF9230_APPLICATION_H__

// <h> nRF_Drivers

// <e> NRFX_IPC_ENABLED - nrfx_ipc - IPC peripheral driver
//==========================================================
#ifndef NRFX_IPC_ENABLED
#define NRFX_IPC_ENABLED 0
#endif

// </e>

// <e> NRFX_BELLBOARD_ENABLED - nrfx_bellbaord - BELLBOARD peripheral driver
//==========================================================
#ifndef NRFX_BELLBOARD_ENABLED
#define NRFX_BELLBOARD_ENABLED 0
#endif

// <q> NRFX_BELLBOARD0_ENABLED  - Enable BELLBOARD0 instance.

#ifndef NRFX_BELLBOARD0_ENABLED
#define NRFX_BELLBOARD0_ENABLED 0
#endif

// <q> NRFX_BELLBOARD1_ENABLED  - Enable BELLBOARD1 instance.

#ifndef NRFX_BELLBOARD1_ENABLED
#define NRFX_BELLBOARD1_ENABLED 0
#endif

// <q> NRFX_BELLBOARD2_ENABLED  - Enable BELLBOARD2 instance.

#ifndef NRFX_BELLBOARD2_ENABLED
#define NRFX_BELLBOARD2_ENABLED 0
#endif

// <q> NRFX_BELLBOARD3_ENABLED  - Enable BELLBOARD3 instance.

#ifndef NRFX_BELLBOARD3_ENABLED
#define NRFX_BELLBOARD3_ENABLED 0
#endif

// </e>

// <e> NRFX_WDT_ENABLED - nrfx_wdt - WDT peripheral driver.
//==========================================================
#ifndef NRFX_WDT_ENABLED
#define NRFX_WDT_ENABLED 0
#endif
// <q> NRFX_WDT0_ENABLED  - Enable WDT0 instance.


#ifndef NRFX_WDT0_ENABLED
#define NRFX_WDT0_ENABLED 0
#endif

// <q> NRFX_WDT1_ENABLED  - Enable WDT1 instance.


#ifndef NRFX_WDT1_ENABLED
#define NRFX_WDT1_ENABLED 0
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

// </h>

#endif // NRFX_CONFIG_NRF9230_APPLICATION_H__
