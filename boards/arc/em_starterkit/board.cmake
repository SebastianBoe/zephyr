# TODO: can this board just use the usual openocd runner?
set(BOARD_FLASH_RUNNER em-starterkit)
set(BOARD_DEBUG_RUNNER em-starterkit)

if(DEFINED EM_STARTERKIT_TUI)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_em_starterkit
    "--tui"
    )
endif()

if(DEFINED EM_STARTERKIT_GDB_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_em_starterkit
    "--gdb-port=${EM_STARTERKIT_GDB_PORT}"
    )
endif()

if(DEFINED EM_STARTERKIT_TCL_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_em_starterkit
    "--tcl-port=${EM_STARTERKIT_TCL_PORT}"
    )
endif()

if(DEFINED EM_STARTERKIT_TELNET_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_em_starterkit
    "--telnet-port=${EM_STARTERKIT_TELNET_PORT}"
    )
endif()
