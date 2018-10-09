zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_HMC5883L hmc5883l.c)
zephyr_library_sources_ifdef(CONFIG_HMC5883L_TRIGGER hmc5883l_trigger.c)
