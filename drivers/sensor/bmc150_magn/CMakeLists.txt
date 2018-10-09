zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_BMC150_MAGN bmc150_magn.c)
zephyr_library_sources_ifdef(CONFIG_BMC150_MAGN_TRIGGER bmc150_magn_trigger.c)
