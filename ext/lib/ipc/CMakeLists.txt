# Copyright (c) 2018 Linaro Limited
#
# SPDX-License-Identifier: Apache-2.0
#

if (CONFIG_OPENAMP)
  set(WITH_ZEPHYR 1)
  set(WITH_ZEPHYR_LIB 1)
  set(WITH_LIBMETAL_FIND OFF CACHE BOOL "" FORCE)
  set(LIBMETAL_INCLUDE_DIR ${ZEPHYR_BINARY_DIR}/ext/hal/libmetal/lib/include)
  set(LIBMETAL_LIB ${ZEPHYR_BINARY_DIR}/ext/hal/libmetal/lib)
endif(CONFIG_OPENAMP)

add_subdirectory_ifdef(CONFIG_OPENAMP open-amp)

