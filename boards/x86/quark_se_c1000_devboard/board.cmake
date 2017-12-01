set(OPENOCD_PRE_CMD  targets 1)
set(OPENOCD_LOAD_ADDRESS ${CONFIG_PHYS_LOAD_ADDR})

include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)
