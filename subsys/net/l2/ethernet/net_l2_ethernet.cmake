zephyr_list(SOURCES
    OUTPUT PRIVATE_SOURCES
    IFDEF:${CONFIG_NET_ARP}                 arp.c
    IFDEF:${CONFIG_NET_L2_ETHERNET}         ethernet.c
    IFDEF:${CONFIG_NET_L2_ETHERNET_MGMT}    ethernet_mgmt.c
    IFDEF:${CONFIG_NET_STATISTICS_ETHERNET} ethernet_stats.c
)
target_sources(subsys_net PRIVATE ${PRIVATE_SOURCES})
target_include_directories(subsys_net PRIVATE ${CMAKE_CURRENT_LIST_DIR})

if(CONFIG_NET_GPTP)
  include(${CMAKE_CURRENT_LIST_DIR}/gptp/ethernet_gptp.cmake)
endif()

