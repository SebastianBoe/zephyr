zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_LIS2DH lis2dh.c)
zephyr_library_sources_ifdef(CONFIG_LIS2DH_TRIGGER lis2dh_trigger.c)
