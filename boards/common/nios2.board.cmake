set_ifndef(BOARD_FLASH_RUNNER nios2)
set_ifndef(BOARD_DEBUG_RUNNER nios2)

if($ENV{NIOS2_CPU_SOF})
  message(WARNING "Setting NIOS2_CPU_SOF in the environment is deprecated, use cmake -DNIIOS_CPU_SOF=... instead")
  set_ifndef(NIOS2_CPU_SOF $ENV{NIOS2_CPU_SOF})
endif()

# TODO: move this into nios2.py
set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_nios2 "--quartus-flash=$ENV{ZEPHYR_BASE}/scripts/support/quartus-flash.py")

if(DEFINED NIOS2_CPU_SOF)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_nios2 "--nios2-cpu-sof=${NIOS2_CPU_SOF}")
endif()

if(DEFINED NIOS2_TUI)
  set_property(GLOBAL APPEND PROPERTY BOARD_RUNNER_ARGS_nios2 "--tui")
endif()
