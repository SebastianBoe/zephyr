# This manifest file is a CMakeList.txt-formatted file that defines in
# a central place where external dependencies are taken from.

# Currently it is supported to satisfy external dependencies through
# the use of either remote git repositories or the local file
# system. When the local file system is used it may contain git
# repositories that are again managed by a multi-repository technology
# like "Google repo" or "git submodules", but the manifest will be
# blissfully unaware of this.

# When specifying a remote git repository revision it is recommended
# to use "git tag"'s over "git SHA"'s for network performance reasons
# (git does not support downloading a single SHA but it does support
# downloading a single tag).
#
# Also, it is recommended to use "git tag"'s/SHA's over "git branch"'s
# for traceability and reproducability reasons.
#
# For maximum performance and traceability it is recommended to both
# specify a "git tag" and a SHA.
#
# Sometimes a little copying is better than a little dependency and a
# local path within this repository should be used (perhaps together
# with the option of using a remote).

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
set(manifest_openthread_type_download_sha  a89eb887488dcbab7f5e9237e2bbcaad38140690)

if(USE_NRFX_FROM_ZEPHYR_REPO)
  set(manifest_nrfx_type_local 1)
  set(manifest_nrfx_type_local_path ${ZEPHYR_BASE}/ext/hal/nordic/nrfx)
else()
  set(manifest_nrfx_type_download 1)
  set(manifest_nrfx_type_download_repo https://github.com/NordicSemiconductor/nrfx)
  set(manifest_nrfx_type_download_ref  v0.8.0)
  set(manifest_nrfx_type_download_sha  b7cfe970b45ad7cc9c36b62ee620508e9e2c7fb5)
endif()
