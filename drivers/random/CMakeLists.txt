target_sources_if_kconfig(zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/random_mcux_rnga.c)
target_sources_if_kconfig(zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/random_mcux_trng.c)
target_sources_ifdef(CONFIG_TIMER_RANDOM_GENERATOR zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/rand32_timer.c)
target_sources_ifdef(CONFIG_X86_TSC_RANDOM_GENERATOR zephyr PRIVATE ${CMAKE_CURRENT_LIST_DIR}/rand32_timestamp.c)
