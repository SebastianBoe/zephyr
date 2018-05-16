set(BOARD lpcxpresso54114_m4)
include(ExternalProject)

ExternalProject_Add(
  ipm_mcux_remote
  SOURCE_DIR $ENV{ZEPHYR_BASE}/samples/subsys/ipc/ipm_mcux/remote/
  INSTALL_COMMAND ""      # This particular build system has no install command
)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

target_sources(app PRIVATE src/main_master.c)
add_dependencies(app ipm_mcux_remote)
