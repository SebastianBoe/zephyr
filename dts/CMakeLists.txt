if(CONFIG_HAS_DTS)
  add_custom_command(OUTPUT ${BOARD_NAME}.dts.pre.tmp
    COMMAND ${CMAKE_C_COMPILER}
      -x assembler-with-cpp
      -nostdinc
      ${ZEPHYR_INCLUDES}
      -I${PROJECT_SOURCE_DIR}/arch/${ARCH}/source_group
      -I${PROJECT_SOURCE_DIR}/dts/common
      -I${PROJECT_SOURCE_DIR}/drivers/of/testcase-data
      -undef -D__DTS__
      -E ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}/${BOARD_NAME}.dts
      -o ${BOARD_NAME}.dts.pre.tmp
      DEPENDS ${ARCH}/${BOARD_NAME}.dts
  )
  add_custom_target(dts_pre DEPENDS ${BOARD_NAME}.dts.pre.tmp)
  # TODO add DEPFILE for commands
  add_custom_command(OUTPUT ${BOARD_NAME}.dts_compiled
    COMMAND ${DTC}
      -O dts
      -o ${BOARD_NAME}.dts_compiled
      -b 0
      -i ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}
      ${BOARD_NAME}.dts.pre.tmp
    DEPENDS dts_pre ${BOARD_NAME}.dts.pre.tmp
  )
  add_custom_target(dts_compiled DEPENDS ${BOARD_NAME}.dts_compiled)

  if(EXISTS ${ARCH}/${BOARD_NAME}.fixup)
    set(FIXUP -f ${ARCH}/${BOARD_NAME}.fixup)
    set(FIXUP_DEPENDS ${ARCH}/${BOARD_NAME}.fixup)
  endif()

  add_custom_command(OUTPUT ${PROJECT_BINARY_DIR}/include/generated/generated_dts_board.h
    COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/extract_dts_includes.py
      ${BOARD_NAME}.dts_compiled
      ${CMAKE_CURRENT_SOURCE_DIR}/${ARCH}/yaml
      ${FIXUP}
      -o ${PROJECT_BINARY_DIR}/include/generated/generated_dts_board.h
    DEPENDS dts_compiled ${BOARD_NAME}.dts_compiled ${FIXUP_DEPENDS}
  )

  add_custom_target(generated_dts_board_h DEPENDS ${PROJECT_BINARY_DIR}/include/generated/generated_dts_board.h)

  add_dependencies(zephyr generated_dts_board_h)
else()
  file(WRITE ${PROJECT_BINARY_DIR}/include/generated/generated_dts_board.h
    "/* WARNING. THIS FILE IS AUTO-GENERATED. DO NOT MODIFY! */"
  )
endif()
