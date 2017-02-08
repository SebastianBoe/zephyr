target_include_directories(zephyr PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/util
  ${CMAKE_CURRENT_SOURCE_DIR}/hal
  ${CMAKE_CURRENT_SOURCE_DIR}/ticker
  ${CMAKE_CURRENT_SOURCE_DIR}/ll
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(zephyr PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/util/mem.c
  ${CMAKE_CURRENT_SOURCE_DIR}/util/memq.c
  ${CMAKE_CURRENT_SOURCE_DIR}/util/mayfly.c
  ${CMAKE_CURRENT_SOURCE_DIR}/util/util.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hal/nrf5/cntr.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hal/nrf5/rand.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hal/nrf5/ecb.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hal/nrf5/radio.c
  ${CMAKE_CURRENT_SOURCE_DIR}/ticker/ticker.c
  ${CMAKE_CURRENT_SOURCE_DIR}/ll_sw/ctrl.c
  ${CMAKE_CURRENT_SOURCE_DIR}/ll_sw/crypto.c
  ${CMAKE_CURRENT_SOURCE_DIR}/ll_sw/ll.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hci/hci_driver.c
  ${CMAKE_CURRENT_SOURCE_DIR}/hci/hci.c
)