target_include_directories(zephyr PUBLIC ${PROJECT_SOURCE_DIR}/include/drivers)

target_sources_ifdef(CONFIG_BLUETOOTH_HCI_HOST zephyr PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/uuid.c
  ${CMAKE_CURRENT_LIST_DIR}/hci_core.c
)

target_sources_ifdef(CONFIG_BLUETOOTH_HCI_RAW zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/hci_raw.c)

target_sources_ifdef(CONFIG_BLUETOOTH_DEBUG zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/log.c)

target_sources_ifdef(CONFIG_BLUETOOTH_DEBUG_MONITOR zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/monitor.c)

target_sources_ifdef(CONFIG_BLUETOOTH_TINYCRYPT_ECC zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/hci_ecc.c)

target_sources_ifdef(CONFIG_BLUETOOTH_INTERNAL_STORAGE zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/storage.c)

if(CONFIG_BLUETOOTH_CONN)
  target_sources(zephyr PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/conn.c
    ${CMAKE_CURRENT_LIST_DIR}/l2cap.c
    ${CMAKE_CURRENT_LIST_DIR}/att.c
    ${CMAKE_CURRENT_LIST_DIR}/gatt.c
  )

  if(CONFIG_BLUETOOTH_SMP)
    target_sources(zephyr PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/smp.c
      ${CMAKE_CURRENT_LIST_DIR}/keys.c
    )
  else()
    target_sources(zephyr PRIVATE
      ${CMAKE_CURRENT_LIST_DIR}/smp_null.c
    )
  endif()

  target_sources_ifdef(CONFIG_BLUETOOTH_BREDR zephyr PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/keys_br.c
    ${CMAKE_CURRENT_LIST_DIR}/l2cap_br.c
    ${CMAKE_CURRENT_LIST_DIR}/avdtp.c
    ${CMAKE_CURRENT_LIST_DIR}/sdp.c
  )

  target_sources_ifdef(CONFIG_BLUETOOTH_RFCOMM zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/rfcomm.c)
  target_sources_ifdef(CONFIG_BLUETOOTH_HFP_HF zephyr PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/at.c
    ${CMAKE_CURRENT_LIST_DIR}/hfp_hf.c
  )
  target_sources_ifdef(CONFIG_BLUETOOTH_RFCOMM zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/avdtp.c)

  target_sources_ifdef(CONFIG_BLUETOOTH_RFCOMM zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/a2dp.c)

endif()
