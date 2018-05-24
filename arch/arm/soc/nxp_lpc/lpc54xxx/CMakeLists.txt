#
# Copyright (c) 2017, NXP
#
# SPDX-License-Identifier: Apache-2.0
#
zephyr_library()

zephyr_library_sources(soc.c)

if(CONFIG_SLAVE_CORE_MCUX)
  if(CONFIG_SLAVE_APP_MCUX)
    string(CONFIGURE ${CONFIG_SLAVE_APP_MCUX}   CONFIGURED_CONFIG_SLAVE_APP_MCUX)

    include(ExternalProject)

    ExternalProject_Add(
      slave_project
      SOURCE_DIR ${CONFIGURED_CONFIG_SLAVE_APP_MCUX}
      INSTALL_COMMAND ""      # This particular build system has no install command
      )
    ExternalProject_Get_Property(slave_project BINARY_DIR)

    set(image_path ${BINARY_DIR}/zephyr/zephyr.bin)

  elseif(CONFIG_SLAVE_IMAGE_MCUX)
    string(CONFIGURE ${CONFIG_SLAVE_IMAGE_MCUX} formatted)

    set(image_path ${formatted})

  else()
    assert(0 "Unreachable code.")
  endif()

  set(core_m0_inc_path ${ZEPHYR_BINARY_DIR}/include/generated/core-m0.inc)

  add_custom_target(
    core_m0_inc_target
    DEPENDS
    ${core_m0_inc_path}
    slave_project
    )

  generate_inc_file_for_gen_target(
    ${ZEPHYR_CURRENT_LIBRARY}
	${image_path}
	${core_m0_inc_path}
	core_m0_inc_target
    )
endif()
