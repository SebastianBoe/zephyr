set_ifndef(BOARD_FLASH_RUNNER dfu-util)

# We have to use DEFINED here, because the values could be "false-y",
# e.g. DFUUTIL_ALT can be 0.
if(NOT DEFINED DFUUTIL_PID)
  message(FATAL_ERROR "DFUUTIL_PID is not set")
endif()
if(NOT DEFINED DFUUTIL_ALT)
  message(FATAL_ERROR "DFUUTIL_ALT is not set")
endif()
if(NOT DEFINED DFUUTIL_IMG)
  message(FATAL_ERROR "DFUUTIL_IMG is not set")
endif()

set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_dfu_util
  "--pid=${DFUUTIL_PID}"
  "--alt=${DFUUTIL_ALT}"
  "--img=${DFUUTIL_IMG}"
  )

if(DEFINED DFUUTIL_DFUSE_ADDR)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_dfu_util "--dfuse-addr=${DFUUTIL_DFUSE_ADDR}")
endif()
