#
#  Copyright (c) 2018 Analog Devices Inc.
#
#  SPDX-License-Identifier: Apache-2.0
#
zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_ADXL372 adxl372.c)
zephyr_library_sources_ifdef(CONFIG_ADXL372_TRIGGER adxl372_trigger.c)
