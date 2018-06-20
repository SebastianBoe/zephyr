/**
 * @file dummy.c
 * Static compilation checks.
 */

/*
 * Copyright (c) 2017 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>

#if defined(CONFIG_BT_CTLR)
/* The Bluetooth Controller's priority receive thread priority shall be higher
 * than the Bluetooth Host's Tx and the Controller's receive thread priority.
 * This is required in order to dispatch Number of Completed Packets event
 * before any new data arrives on a connection to the Host threads.
 */
BUILD_ASSERT(CONFIG_BT_CTLR_RX_PRIO < CONFIG_BT_HCI_TX_PRIO);
#endif /* CONFIG_BT_CTLR */
