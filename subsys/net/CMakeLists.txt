target_sources_ifdef(CONFIG_NET_BUF zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/buf.c)

if(CONFIG_NETWORKING)
  if(CONFIG_NET_L2_RAW_CHANNEL)
    target_sources(zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ip/nbuf.c)
  else()
    add_subdirectory(ip)
  endif()
endif()

add_subdirectory(lib)
