set_ifndef(BOARD_FLASH_RUNNER bossac)

if(DEFINED BOSSAC)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_bossac "--bossac=${BOSSAC}")
endif()

if(DEFINED BOSSAC_PORT)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_bossac "--bossac-port=${BOSSAC_PORT}")
endif()
