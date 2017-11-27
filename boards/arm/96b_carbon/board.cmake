set(DFUUTIL_PID 0483:df11)
set(DFUUTIL_ALT 0)
set(DFUUTIL_IMG ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME})
set(DFUUTIL_DFUSE y)

include($ENV{ZEPHYR_BASE}/boards/common/dfu-util.board.cmake)
