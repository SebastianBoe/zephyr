set(BUILD_LIBMETAL_AS_A_ZEPHYR_LIB 1)

if(BUILD_LIBMETAL_AS_A_ZEPHYR_LIB)
  set(WITH_ZEPHYR 1)
  set(WITH_DOC OFF)
endif()

add_subdirectory(src)
