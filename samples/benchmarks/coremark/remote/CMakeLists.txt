#
# Copyright (c) 2023 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

set(CONF_FILE "../prj.conf")

if (${BOARD} MATCHES "nrf54h20dk.*")
  set(OVERLAY_CONFIG "boards/${BOARD}.conf")
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(${IMAGE_NAME})

target_sources(app PRIVATE ../src/main.c)
