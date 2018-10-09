zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_ISL29035 isl29035.c)
zephyr_library_sources_ifdef(CONFIG_ISL29035_TRIGGER isl29035_trigger.c)
