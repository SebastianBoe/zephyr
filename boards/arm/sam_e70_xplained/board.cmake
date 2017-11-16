set(OPENOCD_POST_CMD atsamv gpnvm set 1)

include($ENV{ZEPHYR_BASE}/boards/common/openocd.board.cmake)
