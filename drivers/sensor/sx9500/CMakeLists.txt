zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_SX9500 sx9500.c)
zephyr_library_sources_ifdef(CONFIG_SX9500_TRIGGER sx9500_trigger.c)
