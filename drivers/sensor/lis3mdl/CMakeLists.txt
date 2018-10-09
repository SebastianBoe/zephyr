zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_LIS3MDL lis3mdl.c)
zephyr_library_sources_ifdef(CONFIG_LIS3MDL_TRIGGER lis3mdl_trigger.c)
