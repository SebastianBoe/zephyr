#
# Copyright (c) 2020, STMicroelectronics
# Copyright (c) 2020 Nordic Semiconductor
#
# SPDX-License-Identifier: Apache-2.0
#

add_subdirectory(resource_table)
add_subdirectory(multi_instance)

zephyr_compile_definitions_ifdef(CONFIG_OPENAMP_WITH_DCACHE
				 WITH_DCACHE_VRINGS
				 WITH_DCACHE_BUFFERS)
