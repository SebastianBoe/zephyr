board_runner_args_append(nrfjprog "--nrf-family=NRF51")

include($ENV{ZEPHYR_BASE}/boards/common/nrfjprog.board.cmake)
