zephyr_library()
zephyr_library_compile_definitions(_POSIX_CHEATS_H)
zephyr_library_sources(
	hw_models_top.c
	timer_model.c
	irq_handler.c
	irq_ctrl.c
	main.c
	tracing.c
	)

set(SIM_LIB_PATH "/usr/lib/libftd2xx.so")

add_library(                sim_lib STATIC IMPORTED GLOBAL)
set_target_properties(      sim_lib PROPERTIES IMPORTED_LOCATION             ${SIM_LIB_PATH})
zephyr_append_cmake_library(sim_lib)

