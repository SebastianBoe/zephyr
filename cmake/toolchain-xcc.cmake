# Path to base directory for installed Xtensa SDK. This should be the
# parent directory of all the individual toolchain versions.
set_ifndef(XTENSA_SDK $ENV{XTENSA_SDK})
set_ifndef(XTENSA_SDK "/opt/xtensa")
set(       XTENSA_SDK ${XTENSA_SDK} CACHE PATH "")
if(NOT EXISTS ${XTENSA_SDK})
  message(FATAL_ERROR "Please set XTENSA_SDK, not found in ${XTENSA_SDK}")
endif()

set(COMPILER gcc)

# List of paths to base directories for xtensa builds.  Can have
# multiple paths here; for example the base path for the installed
# xtensa SDK plus paths to vendor-supplied builds.  It's expected that
# each of these paths is a base directory with children of the form
# <toolchain version>/<build name>/ where the build name corresponds
# to CONFIG_SOC.  By default, we append all the builds included in the
# SDK
set(SDK_INCLUDED_BUILDS ${XTENSA_SDK}/XtDevTools/install/builds)
list(APPEND
  XTENSA_BUILD_PATHS
  ${SDK_INCLUDED_BUILDS}
  )

# Legacy; make sure this is un-set. The compiler actually uses this
# value if set to find command line tools, and we would rather it
# automatically derive this.
if(DEFINED ENV{XTENSA_TOOLS_PATH})
  message(FATAL_ERROR "Please leave XTENSA_TOOLS_PATH unset")
endif()

# Every Zephyr Xtensa SOC configuration should have CONFIG_SOC match
# the name of the build, and have CONFIG_TOOLCHAIN_VARIANT match the
# intended toolchain release.
set(TOOLCHAIN_VER ${CONFIG_TOOLCHAIN_VARIANT})
set(BUILD_NAME    ${CONFIG_SOC})

set(XCC_BUILD ${SDK_INCLUDED_BUILDS}/${TOOLCHAIN_VER}/${BUILD_NAME})
if(NOT EXISTS ${XCC_BUILD})
  message(FATAL_ERROR "Unable to find build ${BUILD_NAME} \
for ${TOOLCHAIN_VER} in ${XTENSA_BUILD_PATHS}, you may need to set XTENSA_BUILD_PATHS)")
endif()

# Strip quotes from cross compiler anme prefix
set(CROSS_COMPILE_${ARCH} ${CONFIG_CROSS_COMPILE})

# Use default name prefix if no cross compiler name prefix is set
set_ifndef(CROSS_COMPILE_${ARCH} xt-)

set(XCC_TOOLS ${XTENSA_SDK}/XtDevTools/install/tools/${TOOLCHAIN_VER}/XtensaTools)

set(TOOLCHAIN_HOME ${XCC_TOOLS})

set(XCC_FLAGS --xtensa-core=${CONFIG_SOC})
list(APPEND TOOLCHAIN_C_FLAGS ${XCC_FLAGS})

set(C_COMPILER_SUFFIX   xcc)
set(CXX_COMPILER_SUFFIX xc++)

set(CROSS_COMPILE_TARGET ${CROSS_COMPILE_${ARCH}})

set(SYSROOT_TARGET xtensa-elf)

set(CROSS_COMPILE ${TOOLCHAIN_HOME}/bin/${CROSS_COMPILE_TARGET}-)
set(SYSROOT_DIR   ${TOOLCHAIN_HOME}/${SYSROOT_TARGET})

# Can either pass --xtensa-system to every single tool in the toolchain (and
# force redefinition of OBJCOPY, READELF, etc) or just export to environment
# (simpler)
# TODO
set(XTENSA_SYSTEM ${XCC_BUILD}/config)

# TODO
# XTSC_INC = $(realpath $(call unquote,${CONFIG_XTENSA_XTSC_INC}))
# ifeq (${XTSC_INC},)
# XTSC_INC = $(realpath ../$(call unquote,${CONFIG_XTENSA_XTSC_INC}))
# endif
# XTSC_WORK_DIR = $(dir ${XTSC_INC})
# XTSC_INC_FILE = $(notdir ${XTSC_INC})

# # Include XCC standard libraries so that users used to Xplorer IDE can port
# # their code easily
# TOOLCHAIN_LIBS += gcc hal
# LIB_INCLUDE_DIR += -L${XCC_BUILD}/xtensa-elf/lib/xcc \
#                    -L${XCC_BUILD}/xtensa-elf/lib \
#                    -L${XCC_BUILD}/xtensa-elf/arch/lib

# KBUILD_CPPFLAGS += -I$(XCC_TOOLS)/lib/xcc/include \
#                    -I$(XCC_TOOLS)/xtensa-elf/include \
#                    -I${XCC_BUILD}/xtensa-elf/arch/include \
#                    -I${XCC_BUILD}/xtensa-elf/include \
#                    -D'__builtin_unreachable()=while(1);'

# # xt-xcc does not support -Og, replace with -O0
# KBUILD_CFLAGS_OPTIMIZE:=$(patsubst -Og,-O0,${KBUILD_CFLAGS_OPTIMIZE})
# KBUILD_CXXFLAGS:=$(filter-out \
# 			-std=c++11 \
# 			-fno-reorder-functions \
# 			-fno-asynchronous-unwind-tables \
# 			-fno-defer-pop \
# 			-Wno-unused-but-set-variable \
# 			-fno-omit-frame-pointer \
# 			,${KBUILD_CXXFLAGS})

# # Support for Xtensa simulator from Cadence Design Systems, Inc.
# XTRUN = ${CROSS_COMPILE}run
# XTRUN_FLAGS += --turbo --cc_none

# export CROSS_COMPILE XTENSA_SYSTEM LIB_INCLUDE_DIR XCC_TOOLS
