zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_SHT3XD sht3xd.c)
zephyr_library_sources_ifdef(CONFIG_SHT3XD_TRIGGER sht3xd_trigger.c)
