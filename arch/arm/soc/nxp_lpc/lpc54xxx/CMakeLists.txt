#
# Copyright (c) 2017, NXP
#
# SPDX-License-Identifier: Apache-2.0
#
zephyr_library()

zephyr_library_sources(soc.c)

if (CONFIG_SLAVE_CORE_MCUX)
  set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

  set(generated_file ${gen_dir}/core-m0.inc)
  set(source_file ${ZEPHYR_BASE}/${CONFIG_SLAVE_IMAGE})

  add_custom_command(
    OUTPUT ${generated_file}
    COMMAND
    ${PYTHON_EXECUTABLE}
    ${ZEPHYR_BASE}/scripts/file2hex.py
    ${ARGN} # Extra arguments are passed to file2hex.py
    --file ${source_file}
    > ${generated_file} # Does pipe redirection work on Windows?
    DEPENDS ${source_file} ipm_mcux_remote
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

  # Ensure 'generated_file' is generated before 'target' by creating a
  # 'custom_target' for it and setting up a dependency between the two
  # targets

  # But first create a unique name for the custom target
  string(
    RANDOM
    LENGTH 8
    random_chars
    )

  get_filename_component(basename ${generated_file} NAME)
  string(REPLACE "." "_" basename ${basename})
  string(REPLACE "@" "_" basename ${basename})

  set(generated_target_name "gen_${basename}_${random_chars}")

  add_custom_target(${generated_target_name} DEPENDS ${generated_file})
  add_dependencies(${target} ${generated_target_name})
endif()
