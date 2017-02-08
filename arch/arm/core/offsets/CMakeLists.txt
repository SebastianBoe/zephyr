add_library(offsets OBJECT offsets.c)
target_object_link_libraries(offsets zephyr)

add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/include/generated/offsets.h
  COMMAND ${PREBUILT_HOST_TOOLS}/gen_offset_header -i ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/offsets.dir/offsets.c.obj -o ${PROJECT_BINARY_DIR}/include/generated/offsets.h
  DEPENDS offsets
)

add_custom_target(offsets_h DEPENDS ${PROJECT_BINARY_DIR}/include/generated/offsets.h)
add_dependencies(zephyr offsets_h)
