include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

target_sources(app PRIVATE src/main.c)

add_library(
  app_lib
  src/app_lib.c
  )

# Link app_lib with app to ensure that the app_lib inherits the same
# build metadata that 'app' is using, e.g. include paths.
target_link_libraries(app_lib PUBLIC app kernel)

# Link 'app' with 'app_lib' to ensure that the linker will resolve
# app's link-time references into 'app_lib'.
target_link_libraries(app app_lib)
