#
# Copyright (c) 2023 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

# This check is needed to avoid infinite recursion. This module code will
# be executed for all images in the build, also for the child image being
# added below.
if (CONFIG_APP_BUILD_MULTICORE)
  add_child_image(
    NAME remote_rad
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../remote
    DOMAIN remote_rad
    BOARD ${CONFIG_APP_REMOTE_BOARD}
    )
endif()

if (CONFIG_APP_BUILD_MULTICORE AND
    CONFIG_BOARD_NRF54H20DK_NRF54H20_CPUAPP AND
    (CONFIG_COREMARK_THREADS_NUMBER EQUAL 1))
  add_child_image(
    NAME remote_ppr
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../remote
    DOMAIN remote_ppr
    BOARD "nrf54h20dk_nrf54h20_cpuppr@soc1"
    )
endif()
