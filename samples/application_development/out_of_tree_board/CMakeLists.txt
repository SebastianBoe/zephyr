set(BOARD native_posix)
set(BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

target_sources(app PRIVATE src/main.c)
