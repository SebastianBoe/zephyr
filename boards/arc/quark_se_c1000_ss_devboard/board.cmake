set(OPENOCD_PRE_CMD        targets 1)
set(OPENOCD_USE_LOAD_IMAGE y)

include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)
