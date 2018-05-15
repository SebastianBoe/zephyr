#
# Copyright (c) 2017, NXP
#
# SPDX-License-Identifier: Apache-2.0
#
zephyr_library()

zephyr_library_sources(soc.c)

if (CONFIG_SLAVE_CORE_MCUX)
  set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

  generate_inc_file_for_target(${ZEPHYR_CURRENT_LIBRARY}
			       $ENV{ZEPHYR_BASE}/${CONFIG_SLAVE_IMAGE}
			       ${gen_dir}/core-m0.inc)
endif()
