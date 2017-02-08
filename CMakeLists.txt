cmake_minimum_required(VERSION 3.7)

set(APPLICATION_SOURCE_DIR ${PROJECT_SOURCE_DIR} CACHE PATH "Application Source Directory")
set(APPLICATION_BINARY_DIR ${PROJECT_BINARY_DIR} CACHE PATH "Application Binary Directory")

project(Zephyr-Kernel VERSION 1.7.99)
enable_language(C CXX ASM)

# Do not generate make install target.
set(CMAKE_SKIP_INSTALL_RULES ON)
set(CMAKE_EXECUTABLE_SUFFIX .elf)

set(AUTOCONF_H ${PROJECT_BINARY_DIR}/include/generated/autoconf.h)
find_package(PythonInterp 3.4)

if(NOT PREBUILT_HOST_TOOLS)
  set(PREBUILT_HOST_TOOLS $ENV{PREBUILT_HOST_TOOLS} CACHE PATH "")
  if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
    set(PREBUILT_HOST_TOOLS ${PROJECT_SOURCE_DIR}/scripts/prebuilt)
  endif()
endif()

if(NOT PREBUILT_HOST_TOOLS)
  message(FATAL_ERROR "Building host tools not yet supported, please use PREBUILT_HOST_TOOLS")
endif()

include(cmake/kconfig.cmake)
include(cmake/extensions.cmake)

# set the variables VERSION_MAJOR, PATCHLEVEL and more
include(cmake/version.cmake)

set(SOC_NAME ${CONFIG_SOC})
set(SOC_SERIES ${CONFIG_SOC_SERIES})
set(SOC_FAMILY ${CONFIG_SOC_FAMILY})

if("${SOC_SERIES}" STREQUAL "")
  set(SOC_PATH ${SOC_NAME})
else()
  set(SOC_PATH ${SOC_FAMILY}/${SOC_SERIES})
endif()

set(ARCH ${CONFIG_ARCH})
set(BOARD_NAME ${CONFIG_BOARD})
set(KERNEL_NAME ${CONFIG_KERNEL_BIN_NAME})

set(KERNEL_ELF_NAME ${KERNEL_NAME}.elf)
set(KERNEL_BIN_NAME ${KERNEL_NAME}.bin)
set(KERNEL_HEX_NAME ${KERNEL_NAME}.hex)
set(KERNEL_STAT_NAME ${KERNEL_NAME}.stat)

include_directories(
  kernel/include
  arch/${ARCH}/include
  arch/${ARCH}/soc/${SOC_PATH}
  boards/${ARCH}/${BOARD_NAME}
  include
  lib/libc/minimal/include
  ${PROJECT_BINARY_DIR}/include/generated
  ${PROJECT_BINARY_DIR}
  ${USERINCLUDE}
  ${STDINCLUDE}
)

# TODO dependency of -include <file>.h not supported by makefile generator
# Possible workaround: (implies that autoconf.h cannot include other files)
# make it a configuration time dependency ... generate a hash of the file ...
# create a global preprocessor definition which uses the hash as a value
add_definitions(
  -DKERNEL
  -D__ZEPHYR__=1
  -include ${AUTOCONF_H}
  -D_FORTIFY_SOURCE=2
)

add_compile_options(
  -Os # TODO: allow config to override this
  -g # TODO: build configuration enough?
  -Wall
  -Wformat
  -Wformat-security
  -Wno-format-zero-length
  -Wno-main
  -ffreestanding
)

add_compile_options(
  $<$<COMPILE_LANGUAGE:C>:-std=c99>
)

add_compile_options(
  $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>
  $<$<COMPILE_LANGUAGE:CXX>:-fcheck-new>
  $<$<COMPILE_LANGUAGE:CXX>:-ffunction-sections>
  $<$<COMPILE_LANGUAGE:CXX>:-fdata-sections>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
  $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
)

add_compile_options(
  $<$<COMPILE_LANGUAGE:ASM>:-xassembler-with-cpp>
  $<$<COMPILE_LANGUAGE:ASM>:-D_ASMLANGUAGE>
)

ld_option(-nostartfiles)
ld_option(-nodefaultlibs)
ld_option(-nostdlib)
ld_option(-static)

if(CONFIG_READABLE_ASM)
  cc_option(-fno-reorder-blocks)
  cc_option(-fno-ipa-cp-clone)
  cc_option(-fno-partial-inlining)
endif()

cc_option(-fno-asynchronous-unwind-tables)

if(CONFIG_STACK_CANARIES)
  cc_option(-fstack-protector-all)
else()
  cc_option(-fno-stack-protector)
endif()

if(CONFIG_OVERRIDE_FRAME_POINTER_DEFAULT)
  if(CONFIG_OMIT_FRAME_POINTER)
    cc_option(-fomit-frame-pointer)
  else()
    cc_option(-fno-omit-frame-pointer)
  endif()
endif()

# TODO: Handle default to Os
add_compile_options(${CONFIG_COMPILER_OPT})

# TODO: Include arch compiler options at this point.

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
   cc_disable_warning(no-unknown-warning-option)
   cc_disable_warning(unused-variable)
   cc_disable_warning(format-invalid-specifier)
   cc_disable_warning(gnu)
   # comparison of unsigned expression < 0 is always false
   cc_disable_warning(tautological-compare)
else() # GCC assumed
  cc_disable_warning(unused-but-set-variable)
  cc_option(-fno-reorder-functions)
  if(NOT ${ZEPHYR_GCC_VARIANT} STREQUAL "xcc")
    cc_option(-fno-defer-pop)
  endif()
endif()

if(CONFIG_DEBUG_SECTION_MISMATCH)
  cc_option(-fno-linline-functions-called-once)
endif()

add_compile_options(-nostdinc)
include_directories(SYSTEM ${NOSTDINC})

cc_disable_warning(pointer-sign)
cc_option(-fno-strict-overflow)

if(CONFIG_STACK_USAGE)
  cc_option(-fstack-usage)
endif()

# disallow errors like 'EXPORT_GPL(foo);' with missing header
cc_option(-Werror=implicit-int)

# Prohibit date/time macros, which would make the build non-deterministic
# cc-option(-Werror=date-time)

# TODO: Archiver arguments
# ar_option(D)

set_ifndef(LINKERFLAGPREFIX -Wl)
# TODO are these options only for linking zephyr?
ld_option(${LINKERFLAGPREFIX},-X)
ld_option(${LINKERFLAGPREFIX},-N)
ld_option(${LINKERFLAGPREFIX},--gc-sections)
ld_option(${LINKERFLAGPREFIX},--build-id=none)

if(CONFIG_HAVE_CUSTOM_LINKER_SCRIPT)
  set(LINKER_SCRIPT ${PROJECT_BASE}/${CONFIG_CUSTOM_LINKER_SCRIPT})
  if(NOT EXISTS LINKER_SCRIPT)
    set(LINKER_SCRIPT ${CONFIG_CUSTOM_LINKER_SCRIPT})
  endif()
else()
  # Try a board specific linker file
  set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/boards/${ARCH}/${BOARD_NAME}/linker.ld)
  if(NOT EXISTS ${LINKER_SCRIPT})
    # If not available, try an SoC specific linker file
    set(LINKER_SCRIPT ${PROJECT_SOURCE_DIR}/arch/${ARCH}/soc/${SOC_PATH}/linker.ld)
  endif()
endif()

if(NOT EXISTS ${LINKER_SCRIPT})
  message(FATAL_ERROR "Could not find linker script ${LINKER_SCRIPT}")
endif()

configure_file(version.h.in ${PROJECT_BINARY_DIR}/include/generated/version.h)

add_library(zephyr STATIC "")
add_library(main OBJECT "")

add_subdirectory(lib)
add_subdirectory(misc)
# We use include instead of add_subdirectory to avoid creating a new directory scope.
# This is because source file properties are directory scoped, including the GENERATED
# property which is set implicitly for custom command outputs
include(misc/generated/CMakeLists.txt)
add_subdirectory(boards)
add_subdirectory(ext)
add_subdirectory(subsys)
add_subdirectory(arch)
add_subdirectory(drivers)

# Get ZEPHYR_INCLUDE for preprocessing, with cmake 3.8 this should be possible with generator expressions.
get_property(ZEPHYR_INCLUDES_LIST TARGET zephyr PROPERTY INCLUDE_DIRECTORIES)
foreach(INCLUDE ${ZEPHYR_INCLUDES_LIST})
  list(APPEND ZEPHYR_INCLUDES -I${INCLUDE})
endforeach()

add_subdirectory(dts)

# Run the pre-processor on the linker script
get_filename_component(BASE_NAME ${CMAKE_CURRENT_BINARY_DIR} NAME)
add_custom_command(
  OUTPUT linker.cmd
  DEPENDS ${LINKER_SCRIPT}
  DEPFILE ${PROJECT_BINARY_DIR}/linker.cmd.dep
  COMMAND ${CMAKE_C_COMPILER}
  -x assembler-with-cpp
  -MD -MF linker.cmd.dep -MT ${BASE_NAME}/linker.cmd
  ${ZEPHYR_INCLUDES}
  -D__GCC_LINKER_CMD__
  -E ${LINKER_SCRIPT} -P
  -o linker.cmd
  VERBATIM
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_custom_target(
  linker_script
  DEPENDS linker.cmd
)

if(TOOLCHAIN_DO_PASS2)
  include(${CMAKE_TOOLCHAIN_FILE})
endif()
add_subdirectory(kernel)

set(zephyr_lnk
  ${LINKERFLAGPREFIX},-Map=${PROJECT_BINARY_DIR}/${KERNEL_NAME}.map
  -u_OffsetAbsSyms
  -u_ConfigAbsSyms
  -e__start
  ${LINKERFLAGPREFIX},--start-group
  ${LINKERFLAGPREFIX},--whole-archive
  zephyr
  ${LINKERFLAGPREFIX},--end-group
  ${LINKERFLAGPREFIX},--start-group
  ${LINKERFLAGPREFIX},--no-whole-archive
  kernel
  ${LINKERFLAGPREFIX},--end-group
  ${LIB_INCLUDE_DIR}
  ${TOOLCHAIN_LIBS}
)

target_object_link_libraries(main zephyr)

add_executable(zephyr_prebuilt
  $<TARGET_OBJECTS:main>
  $<TARGET_OBJECTS:offsets>
)

target_link_libraries(zephyr_prebuilt
  -T${PROJECT_BINARY_DIR}/linker.cmd
  ${zephyr_lnk}
)

set_property(TARGET zephyr_prebuilt PROPERTY LINK_DEPENDS ${PROJECT_BINARY_DIR}/linker.cmd)
add_dependencies(zephyr_prebuilt linker_script)

if("${ARCH}" STREQUAL "riscv32")
  set(OUTPUT_FORMAT elf32-littleriscv)
else()
  set(OUTPUT_FORMAT elf32-little${ARCH})
endif()

add_custom_command(
  OUTPUT isr_tables.c
  COMMAND ${CMAKE_OBJCOPY} -I ${OUTPUT_FORMAT} -O binary --only-section=.intList $<TARGET_FILE:zephyr_prebuilt> isrList.bin
  COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/arch/common/gen_isr_tables.py --output-source isr_tables.c --intlist isrList.bin --debug --sw-isr-table --vector-table
  DEPENDS zephyr_prebuilt
)

add_executable(tmp
  $<TARGET_OBJECTS:main>
  $<TARGET_OBJECTS:offsets>
  isr_tables.c
)

target_link_libraries(tmp
  -T${CMAKE_CURRENT_BINARY_DIR}/linker.cmd
  ${zephyr_lnk}
)

add_custom_command(
  TARGET tmp POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -I elf32-littlearm -O elf32-littlearm --set-section-flags .intList=noload $<TARGET_FILE:tmp> ${KERNEL_ELF_NAME}
  COMMAND ${CMAKE_OBJCOPY} -S -Oihex   -R .comment -R COMMON -R .eh_frame ${KERNEL_ELF_NAME} ${KERNEL_HEX_NAME}
  COMMAND ${CMAKE_OBJCOPY} -S -Obinary -R .comment -R COMMON -R .eh_frame ${KERNEL_ELF_NAME} ${KERNEL_BIN_NAME}
  COMMAND ${CMAKE_OBJDUMP} -D ${KERNEL_ELF_NAME} > ${KERNEL_NAME}.lst
  DEPENDS zephyr_elf
)
