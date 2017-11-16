set(BOARD_FLASH_RUNNER esp32)

set_ifndef(ESP_IDF_PATH $ENV{ESP_IDF_PATH})
assert(ESP_IDF_PATH "ESP_IDF_PATH is not set")

set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-idf-path=$ENV{ESP_IDF_PATH}")

if(DEFINED ESP_DEVICE)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-device=${ESP_DEVICE}")
endif()

if(DEFINED ESP_BAUD_RATE)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-baud-rate=${ESP_BAUD_RATE}")
endif()

if(DEFINED ESP_FLASH_SIZE)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-flash-size=${ESP_FLASH_SIZE}")
endif()

if(DEFINED ESP_FLASH_FREQ)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-flash-freq=${ESP_FLASH_FREQ}")
endif()

if(DEFINED ESP_FLASH_MODE)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-flash-mode=${ESP_FLASH_MODE}")
endif()

if(DEFINED ESP_TOOL)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_esp32 "--esp-tool=${ESP_TOOL}")
endif()
