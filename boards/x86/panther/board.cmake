set(OPENOCD_PRE_CMD    targets 1)
set(OPENOCD_LOAD_CMD   load_image   ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_PHYS_LOAD_ADDR})
set(OPENOCD_VERIFY_CMD verify_image ${PROJECT_BINARY_DIR}/${KERNEL_BIN_NAME} ${CONFIG_PHYS_LOAD_ADDR})

include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)
