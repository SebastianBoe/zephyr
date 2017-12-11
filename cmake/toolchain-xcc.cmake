set_ifndef(XCC_TOOLCHAIN_PATH $ENV{XCC_TOOLCHAIN_PATH})
set(       XCC_TOOLCHAIN_PATH ${XCC_TOOLCHAIN_PATH} CACHE PATH "")
assert(    XCC_TOOLCHAIN_PATH "XCC_TOOLCHAIN_PATH is not set")

set(TOOLCHAIN_HOME ${XCC_TOOLCHAIN_PATH})


set(COMPILER gcc)

set(CMAKE_C_COMPILER xt-xcc)
set(CMAKE_CXX_COMPILER xt-xc++)
set(C_COMPILER_SUFFIX   xcc)
set(CXX_COMPILER_SUFFIX xc++)
set(XCC_INCLUDE_DIRS /usr)
# list(APPEND TOOLCHAIN_C_FLAGS ${XCC_FLAGS})

include_directories($ENV{XTENSA_SYSTEM}/../xtensa-elf/include)
include_directories($ENV{XTENSA_SYSTEM}/../xtensa-elf/arch/include)
include_directories($ENV{XCC_TOOLCHAIN_PATH}/xtensa-elf/include)
include_directories($ENV{XCC_TOOLCHAIN_PATH}/lib/xcc/include)


set(CROSS_COMPILE_TARGET xt)
set(SYSROOT_TARGET       xtensa-elf)

set(CROSS_COMPILE ${TOOLCHAIN_HOME}/bin/${CROSS_COMPILE_TARGET}-)
set(SYSROOT_DIR   ${TOOLCHAIN_HOME}/${SYSROOT_TARGET})

