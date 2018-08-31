zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources(
  vector_table.S
  reset.S
  nmi_on_reset.S
  prep_c.c
  scb.c
  nmi.c
  exc_manage.c
  )
