zephyr_list(SOURCES
            OUTPUT PRIVATE_SOURCES
            IFDEF:${CONFIG_BT_DEBUG} log.c
            IFDEF:${CONFIG_BT_RPA}   rpa.c
)

target_sources(subsys_bluetooth PRIVATE ${PRIVATE_SOURCES})
