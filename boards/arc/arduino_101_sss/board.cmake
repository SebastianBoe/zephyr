if(DEFINED ENV{ZEPHYR_FLASH_OVER_DFU})
  set(BOARD_FLASH_RUNNER dfu-util)
else()
  set(BOARD_FLASH_RUNNER openocd)
endif()

set(BOARD_DEBUG_RUNNER openocd)

set(DFUUTIL_PID 8087:0aba)
set(DFUUTIL_ALT sensor_core)
set(DFUUTIL_IMG ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME})

set(OPENOCD_PRE_CMD    targets 1)
set(OPENOCD_LOAD_CMD   load_image   ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS})
set(OPENOCD_VERIFY_CMD verify_image ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_FLASH_BASE_ADDRESS})
set(OPENOCD_GDB_PORT 3334)

include($ENV{ZEPHYR_BASE}/boards/common/dfu-util.board.cmake)
include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)
