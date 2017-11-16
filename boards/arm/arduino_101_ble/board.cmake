set(DFUUTIL_PID 8087:0aba)
set(DFUUTIL_ALT ble_core)
set(DFUUTIL_IMG ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME})

include($ENV{ZEPHYR_BASE}/boards/common/dfu-util.board.cmake)
