if(CONFIG_SBL_FIXUP)
  set_ifndef(DTS_BOARD_FIXUP_FILE ${BOARD_DIR}/dts_fixup_sbl.h)
  message(STATUS "SBL specific dts configuration done")
endif()
