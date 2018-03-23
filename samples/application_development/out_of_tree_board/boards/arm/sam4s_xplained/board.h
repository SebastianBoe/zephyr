/*
 * Copyright (c) Justin Watson 2018
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __INC_BOARD_H
#define __INC_BOARD_H

#include <soc.h>

#define BOARD_YELLOW_LED1_GPIO_PORT  CONFIG_GPIO_SAM_PORTC_LABEL
#define BOARD_YELLOW_LED1_GPIO_PIN   10

#define BOARD_YELLOW_LED2_GPIO_PORT  CONFIG_GPIO_SAM_PORTC_LABEL
#define BOARD_YELLOW_LED2_GPIO_PIN   17

#define BOARD_USER_PB2_GPIO_PORT     CONFIG_GPIO_SAM_PORTA_LABEL
#define BOARD_USER_PB2_GPIO_PIN      5

/* Aliases to make the basic samples work. */
#define LED0_GPIO_PORT		BOARD_YELLOW_LED1_GPIO_PORT
#define LED0_GPIO_PIN		BOARD_YELLOW_LED1_GPIO_PIN
#define LED1_GPIO_PORT		BOARD_YELLOW_LED2_GPIO_PORT
#define LED1_GPIO_PIN		BOARD_YELLOW_LED2_GPIO_PIN
#define SW0_GPIO_NAME		BOARD_USER_PB2_GPIO_PORT
#define SW0_GPIO_PIN		BOARD_USER_PB2_GPIO_PIN
#define SW0_GPIO_PIN_PUD	GPIO_PUD_PULL_UP

#endif /* __INC_BOARD_H */
