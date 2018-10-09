zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_APDS9960 apds9960.c)
zephyr_library_sources_ifdef(CONFIG_APDS9960_TRIGGER apds9960_trigger.c)
