# Copyright (c) 2018 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#
set(BOARD lpcxpresso54114_m4)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

enable_language(C ASM)

# Location of external dependencies:
set(PLATFORM_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/platform")

target_sources(app PRIVATE src/main_master.c ${PLATFORM_DIR}/platform.c
	       ${PLATFORM_DIR}/platform_ops.c ${PLATFORM_DIR}/resource_table.c)

target_include_directories(app PRIVATE ${PLATFORM_DIR})
