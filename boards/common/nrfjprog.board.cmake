set_ifndef(BOARD_FLASH_RUNNER nrfjprog)

assert(NRF_FAMILY "NRF_FAMILY is not set")

set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_nrfjprog "--nrf-family=${NRF_FAMILY}")
