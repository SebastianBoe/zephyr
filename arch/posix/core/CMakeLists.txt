zephyr_library()
zephyr_library_sources(
	cpuhalt.c
	fatal.c
	posix_core.c
	prep_c.c
	swap.c
	thread.c
	)
zephyr_library_compile_options(-nostdinc)
zephyr_library_include_directories(
  # TODO: Ask gcc where to find these perhaps, like we do with normal toolchains?
  "/usr/lib/gcc/x86_64-linux-gnu/5/include"
  "/usr/local/include"
  "/usr/lib/gcc/x86_64-linux-gnu/5/include-fixed"
  "/usr/include/x86_64-linux-gnu"
  "/usr/include"
  )
