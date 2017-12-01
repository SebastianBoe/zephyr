set_ifndef(BOARD_FLASH_RUNNER openocd)
set_ifndef(BOARD_DEBUG_RUNNER openocd)

if(CONFIG_X86)
  set_ifndef(OPENOCD_USE_LOAD_IMAGE y)
endif()

# We can't use set_ifndef() here for a couple of reasons:
#
# - it bombs out with a syntax error if the second argument expands to
#   the empty string (as ${CONFIG_FLASH_BASE_ADDRESS} does on some targets)
# - it only expects a single value, and ignores additional ones (for
#   OPENOCD_LOAD_CMD, etc.)
set_ifndef(OPENOCD_LOAD_BINARY "${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME}")
if(NOT OPENOCD_LOAD_ADDRESS)
  set(OPENOCD_LOAD_ADDRESS ${CONFIG_FLASH_BASE_ADDRESS})
endif()
if(NOT OPENOCD_LOAD_CMD)
  if(OPENOCD_USE_LOAD_IMAGE)
    set(OPENOCD_LOAD_CMD load_image ${OPENOCD_LOAD_BINARY} ${OPENOCD_LOAD_ADDRESS})
  else()
    set(OPENOCD_LOAD_CMD flash write_image erase ${OPENOCD_LOAD_BINARY} ${OPENOCD_LOAD_ADDRESS})
  endif()
endif()
if(NOT OPENOCD_VERIFY_CMD)
  set(OPENOCD_VERIFY_CMD verify_image ${OPENOCD_LOAD_BINARY} ${OPENOCD_LOAD_ADDRESS})
endif()

set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd
  "--cmd-load=\"${OPENOCD_LOAD_CMD}\""
  "--cmd-verify=\"${OPENOCD_VERIFY_CMD}\""
  )

if(DEFINED OPENOCD_PRE_CMD)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--cmd-pre-load=\"${OPENOCD_PRE_CMD}\"")
endif()

if(DEFINED OPENOCD_POST_CMD)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--cmd-post-verify=\"${OPENOCD_POST_CMD}\"")
endif()

if(DEFINED OPENOCD_TUI)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--tui")
endif()

if(DEFINED OPENOCD_GDB_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--gdb-port=${OPENOCD_GDB_PORT}")
endif()

if(DEFINED OPENOCD_TCL_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--tcl-port=${OPENOCD_TCL_PORT}")
endif()

if(DEFINED OPENOCD_TELNET_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_openocd "--telnet-port=${OPENOCD_TELNET_PORT}")
endif()
