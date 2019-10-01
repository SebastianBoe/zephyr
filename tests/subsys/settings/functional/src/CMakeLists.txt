zephyr_library_named(  settings_basic_test)
zephyr_library_sources(settings_basic_test.c)
add_dependencies(      settings_basic_test offsets_h)
