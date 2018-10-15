cmake_minimum_required(VERSION 3.8.2)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

target_sources(app PRIVATE src/main.c)

add_custom_command(
  OUTPUT log.txt
  COMMAND pwd
  DEPENDS zephyr_prebuilt
  )
add_custom_target(
  log_txt
  DEPENDS
  log.txt
  )
