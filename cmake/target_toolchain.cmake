# SPDX-License-Identifier: Apache-2.0

# No official documentation exists for the "Generic" value, except their wiki.
#
# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/CrossCompiling:
#   CMAKE_SYSTEM_NAME : this one is mandatory, it is the name of the target
#   system, i.e. the same as CMAKE_SYSTEM_NAME would have if CMake would run
#   on the target system.  Typical examples are "Linux" and "Windows". This
#   variable is used for constructing the file names of the platform files
#   like Linux.cmake or Windows-gcc.cmake. If your target is an embedded
#   system without OS set CMAKE_SYSTEM_NAME to "Generic".
set(CMAKE_SYSTEM_NAME Generic)

# https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_PROCESSOR.html:
#   The name of the CPU CMake is building for.
#
# https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/CrossCompiling:
#   CMAKE_SYSTEM_PROCESSOR : optional, processor (or hardware) of the
#   target system. This variable is not used very much except for one
#   purpose, it is used to load a
#   CMAKE_SYSTEM_NAME-compiler-CMAKE_SYSTEM_PROCESSOR.cmake file,
#   which can be used to modify settings like compiler flags etc. for
#   the target
set(CMAKE_SYSTEM_PROCESSOR ${ARCH})

# https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_VERSION.html:
#   When the CMAKE_SYSTEM_NAME variable is set explicitly to enable cross
#   compiling then the value of CMAKE_SYSTEM_VERSION must also be set
#   explicitly to specify the target system version.
set(CMAKE_SYSTEM_VERSION ${PROJECT_VERSION})

# We are not building dynamically loadable libraries
set(BUILD_SHARED_LIBS OFF)

if(NOT (COMPILER STREQUAL "host-gcc"))
  include(${TOOLCHAIN_ROOT}/cmake/toolchain/${ZEPHYR_TOOLCHAIN_VARIANT}/target.cmake)
endif()

# The 'generic' compiler and the 'target' compiler might be different,
# so we unset the 'generic' one and thereby force the 'target' to
# re-set it. This is only needed for the first boilerplate execution as
# the remaining boilerplate executions will use the same C compiler.
if (FIRST_BOILERPLATE_EXECUTION)
  unset(CMAKE_C_COMPILER)
  unset(CMAKE_C_COMPILER CACHE)
endif()

# A toolchain consist of a compiler and a linker.
# In Zephyr, toolchains require a port under cmake/toolchain/.
# Each toolchain port must set COMPILER and LINKER.
# E.g. toolchain/llvm may pick {clang, ld} or {clang, lld}.
include(${ZEPHYR_BASE}/cmake/compiler/${COMPILER}/target.cmake OPTIONAL)
include(${ZEPHYR_BASE}/cmake/linker/${LINKER}/target.cmake OPTIONAL)

# Uniquely identify the toolchain wrt. it's capabilities.
#
# What we are looking for, is a signature definition that is defined
# like this:
#  * Toolchains with the same signature will always support the same set
#    of flags.
# It is not clear how this signature should be constructed. The
# strategy chosen is to md5sum the CC binary.
file(MD5 ${CMAKE_C_COMPILER} CMAKE_C_COMPILER_MD5_SUM)
set(TOOLCHAIN_SIGNATURE ${CMAKE_C_COMPILER_MD5_SUM})

# TODO: Is it possible to know if we are doing a multi-toolchain build
# at this stage? I don't think so, so this code would need to be moved
# later in the build.
set(MULTI_TOOLCHAIN_BUILD 1)

# TODO: Have the toolchain build scripts set ZEPHYR_C_COMPILER instead
# of CMAKE_C_COMPILER.
if(FIRST_BOILERPLATE_EXECUTION)
  set(ZEPHYR_C_TOOLCHAIN ${CMAKE_C_COMPILER})
else()
  if(WIN32)
    set(${IMAGE}ZEPHYR_C_TOOLCHAIN C:/gnuarmemb_2/bin/arm-none-eabi-gcc.exe)
  else()
    set(${IMAGE}ZEPHYR_C_TOOLCHAIN /home/sebo/Downloads/gcc-arm-none-eabi-8-2018-q4-major/bin/arm-none-eabi-gcc)
  endif()
endif()

if(MULTI_TOOLCHAIN_BUILD)

  # Don't use PYTHON_EXECUTABLE on Linux, as it can use shebang.
  if(WIN32)
    set(MAYBE_PYTHON_EXECUTABLE ${PYTHON_EXECUTABLE})
    set(SPECIFY_COMPILER_OVERRIDE_WITH_ENV_VAR 0)
  else()
    set(MAYBE_PYTHON_EXECUTABLE)
    set(SPECIFY_COMPILER_OVERRIDE_WITH_ENV_VAR 1)
  endif()

  unset(CMAKE_C_COMPILER_LAUNCHER)

  if(SPECIFY_COMPILER_OVERRIDE_WITH_ENV_VAR)
    list(APPEND
      CMAKE_C_COMPILER_LAUNCHER
      COMPILER_DRIVER_OVERRIDE=${${IMAGE}ZEPHYR_C_TOOLCHAIN}
      )

    set(COMPILER_DRIVER_ARGS
      ${MAYBE_PYTHON_EXECUTABLE}
      ${ZEPHYR_BASE}/scripts/compiler_driver.py
      )
  else()
    set(COMPILER_DRIVER_ARGS
      ${MAYBE_PYTHON_EXECUTABLE}
      ${ZEPHYR_BASE}/scripts/compiler_driver.py
      --override=${${IMAGE}ZEPHYR_C_TOOLCHAIN}
      )

  endif()

  # Use ccache if it is installed, unless the user explicitly disables
  # it by setting USE_CCACHE=0.
  if(NOT (USE_CCACHE STREQUAL "0"))
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
      set(USING_CCACHE 1)
    endif()
  endif()

  if(USING_CCACHE)
    # TODO: Only use this for the non-app toolchain?
    # TODO: Support CXX, ASM
    set(ENV{CCACHE_PREFIX}
      ${COMPILER_DRIVER_ARGS}
      )

    list(APPEND
      CMAKE_C_COMPILER_LAUNCHER
      CCACHE_PREFIX=${COMPILER_DRIVER_ARGS}
      ${CCACHE_FOUND}
      )
  else()
    list(APPEND
      CMAKE_C_COMPILER_LAUNCHER
      ${COMPILER_DRIVER_ARGS}
      )
  endif()

endif()
