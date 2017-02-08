add_subdirectory(hci)
add_subdirectory_ifdef(CONFIG_NBLE nble)
target_sources_ifdef(CONFIG_BLUETOOTH_NRF51_PM zephyr PRIVATE nrf51_pm.c)
