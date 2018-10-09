zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_AIO_COMPARATOR_QMSI aio_comparator_qmsi.c)
zephyr_library_sources_ifdef(CONFIG_USERSPACE           aio_comparator_handlers.c)
