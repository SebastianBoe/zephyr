#
# Copyright (c) 2022 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: Apache-2.0
#

if(CONFIG_TEMP_NRF5 AND NOT CONFIG_TEMP_NRF5_FORCE_ALT)
  zephyr_library()
  if(CONFIG_HAS_NRF_TEMP_NRFS)
    zephyr_library_sources(temp_nrfs.c)
  elseif(CONFIG_HAS_HW_NRF_TEMP)
    zephyr_library_sources(temp_nrf5.c)
  endif()
endif()
