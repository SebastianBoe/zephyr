board_runner_args_append(nrfjprog "--nrf-family=NRF52")

include($ENV{ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
