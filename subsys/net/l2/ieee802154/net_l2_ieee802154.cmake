zephyr_list(SOURCES
  OUTPUT PRIVATE_SOURCES
  ieee802154.c
  ieee802154_frame.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_FRAGMENT}      ieee802154_fragment.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_MGMT}          ieee802154_mgmt.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_RADIO_ALOHA}   ieee802154_radio_aloha.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_RADIO_CSMA_CA} ieee802154_radio_csma_ca.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_SECURITY}      ieee802154_security.c
  IFDEF:${CONFIG_NET_L2_IEEE802154_SHELL}         ieee802154_shell.c
)

target_sources(subsys_net PRIVATE ${PRIVATE_SOURCES})
target_include_directories(subsys_net PRIVATE ${CMAKE_CURRENT_LIST_DIR})
