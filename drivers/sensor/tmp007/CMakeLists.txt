zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_TMP007 tmp007.c)
zephyr_library_sources_ifdef(CONFIG_TMP007_TRIGGER tmp007_trigger.c)
