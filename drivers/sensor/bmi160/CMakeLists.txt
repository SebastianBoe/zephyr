zephyr_library()
zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )
zephyr_library_sources_ifdef(CONFIG_BMI160 bmi160.c)
zephyr_library_sources_ifdef(CONFIG_BMI160_TRIGGER bmi160_trigger.c)
