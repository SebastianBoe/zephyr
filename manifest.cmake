# This manifest file is a CMakeList.txt-formatted file that defines in
# a central place where external dependencies are taken from.

# Currently it is supported to satisfy external dependencies through
# the use of either remote or local git repositories.

# NB: This format is currently in beta and backwards-compatibility
# should not be assumed.

# Header guard
if(ZEPHYR_MANIFEST_CMAKE_GUARD)
  return()
else()
  set(ZEPHYR_MANIFEST_CMAKE_GUARD 1)
endif()

# set(manifest_openthread_type_local 1)
# set(manifest_openthread_type_local_path ${ZEPHYR_BASE}/ext/lib/net/openthread)

# TODO: Point to a Zephyr fork
# Nov. 7
set(manifest_openthread_type_download 1)
set(manifest_openthread_type_download_repo https://github.com/openthread/openthread.git)
set(manifest_openthread_type_download_tag  a89eb887488dcbab7f5e9237e2bbcaad38140690)

if(USE_NRFX_FROM_ZEPHYR_REPO)
  set(manifest_nrfx_type_local 1)
  set(manifest_nrfx_type_local_path ${ZEPHYR_BASE}/ext/hal/nordic/nrfx)
else()
  set(manifest_nrfx_type_download 1)
  set(manifest_nrfx_type_download_repo https://github.com/NordicSemiconductor/nrfx)
  set(manifest_nrfx_type_download_tag  v0.8.0)
endif()
