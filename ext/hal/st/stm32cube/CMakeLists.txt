# Makefile - STM32Cube SDK
#
# Copyright (c) 2016 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0

#add_library(STM32CUBE INTERFACE)
string(TOUPPER ${CONFIG_SOC} _STM32CUBE_CPU)
string(REPLACE "X" "x" STM32CUBE_CPU ${_STM32CUBE_CPU})

# STM32Cub uses the CPU name to expose SOC-specific attributes of a specific
# peripheral.
# It also requires USE_HAL_DRIVER to be define in order to benefit from
# STM32Cube HAL and LL APIs
zephyr_compile_definitions(
  -D${STM32CUBE_CPU}
  -DUSE_HAL_DRIVER
  -DUSE_FULL_LL_DRIVER
  )

set(stm_socs
  f0
  f1
  f3
  f4
  f7
  l4
  )

foreach(stm_soc_series ${stm_socs})
  set(stm_soc stm32${stm_soc_series}x)

  string(TOUPPER ${stm_soc_series} stm_soc_series_to_upper)
  string(TOUPPER ${stm_soc}                   soc_to_upper)

  if(CONFIG_SOC_SERIES_${soc_to_upper})

    # TODO: Fix
    include(${ZEPHYR_BASE}/cmake/DownloadProject.cmake)

    download_project(
      PROJ                stm32cube
      GIT_REPOSITORY      https://github.com/SebastianBoe/STM32cube${stm_soc_series_to_upper}.git
      GIT_TAG             2b5ee84f8cbb38c75246ff82d8426def29ea9e19
      UPDATE_DISCONNECTED 1
      )

    zephyr_include_directories(
      ${stm32cube_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32${stm_soc_series_to_upper}xx/Include/
      ${stm32cube_SOURCE_DIR}/Drivers/STM32${stm_soc_series_to_upper}xx_HAL_Driver/Inc/
      ${stm32cube_SOURCE_DIR}/Drivers/STM32${stm_soc_series_to_upper}xx_HAL_Driver/Inc/Legacy
	  )

    add_subdirectory(${stm_soc}x)
  endif()
endforeach()
