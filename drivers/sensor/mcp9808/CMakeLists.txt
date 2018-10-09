zephyr_library()

zephyr_library_compile_options_ifdef(CONFIG_COVERAGE_GCOV
  -ftest-coverage
  -fprofile-arcs
  )

zephyr_library_sources_ifdef(CONFIG_MCP9808 mcp9808.c)
zephyr_library_sources_ifdef(CONFIG_MCP9808_TRIGGER mcp9808_trigger.c)
