target_sources_ifdef(CONFIG_BLUETOOTH_H4  zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/h4.c)
target_sources_ifdef(CONFIG_BLUETOOTH_H5  zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/h5.c)
target_sources_ifdef(CONFIG_BLUETOOTH_SPI zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/spi.c)
