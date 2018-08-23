# Put functions and data in their own binary sections so that ld can
# garbage collect them
zephyr_cc_option(-ffunction-sections -fdata-sections)

if(CONFIG_GEN_ISR_TABLES)
  # The header might only be referenced by gen_isr_tables.py. The
  # linker is not aware of this and might optimize it away. To prevent
  # this we instruct the linker that there definitely is something
  # that is referencing _iheader.
  zephyr_link_libraries(-u_iheader)
endif()

zephyr_sources_ifdef(
  CONFIG_EXECUTION_BENCHMARKING
  timing_info_bench.c
  )
