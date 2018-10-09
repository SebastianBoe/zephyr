zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_AMG88XX amg88xx.c)
zephyr_library_sources_ifdef(CONFIG_AMG88XX_TRIGGER amg88xx_trigger.c)
