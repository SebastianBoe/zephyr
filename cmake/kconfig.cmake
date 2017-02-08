file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/include/generated)
# Folders needed for conf/mconf files (kconfig has no method of redirecting all output files).
# conf/mconf needs to be run from a different directory because of: ZEP-1963
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig/include/generated)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig/include/config)

set(BOARD_DEFCONFIG ${PROJECT_SOURCE_DIR}/boards/${ARCH}/${BOARD}/${BOARD}_defconfig)
set(KERNEL_CONFIG   ${PROJECT_SOURCE_DIR}/kernel/configs/kernel.config)
set(APP_CONFIG      ${APPLICATION_SOURCE_DIR}/prj.conf)
set(DOTCONFIG       ${PROJECT_BINARY_DIR}/.config)

set(ENV{srctree}            ${PROJECT_SOURCE_DIR})
set(ENV{KERNELVERSION}      ${PROJECT_VERSION})
set(ENV{KCONFIG_CONFIG}     ${DOTCONFIG})
set(ENV{KCONFIG_AUTOHEADER} ${AUTOCONF_H})

# Create new .config if the file does not exists, or the user has edited one of the configuration files.
if(NOT EXISTS ${DOTCONFIG}
   OR ${BOARD_DEFCONFIG} IS_NEWER_THAN ${DOTCONFIG}
   OR ${KERNEL_CONFIG}   IS_NEWER_THAN ${DOTCONFIG}
   OR ${APP_CONFIG}      IS_NEWER_THAN ${DOTCONFIG}
  )
  execute_process(
    COMMAND ${PYTHON_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/kconfig/merge_config.py -m -q
      -O ${PROJECT_BINARY_DIR}
      ${BOARD_DEFCONFIG} ${KERNEL_CONFIG} ${APP_CONFIG}
  )
  execute_process(
    COMMAND ${PREBUILT_HOST_TOOLS}/kconfig/conf
      --olddefconfig
      ${PROJECT_SOURCE_DIR}/Kconfig
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig
  )
endif()

# Force CMAKE configure when the configuration files changes.
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${BOARD_DEFCONFIG})
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${KERNEL_CONFIG})
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${APP_CONFIG})
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${DOTCONFIG})

execute_process(
  COMMAND ${PREBUILT_HOST_TOOLS}/kconfig/conf
    --silentoldconfig
    ${PROJECT_SOURCE_DIR}/Kconfig
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig
)

add_custom_target(menuconfig
  COMMAND
    ${CMAKE_COMMAND} -E env srctree=${PROJECT_SOURCE_DIR}
    ${CMAKE_COMMAND} -E env KERNELVERSION=${PROJECT_VERSION}
    ${CMAKE_COMMAND} -E env KCONFIG_CONFIG=${DOTCONFIG}
    ${CMAKE_COMMAND} -E env KCONFIG_AUTOHEADER=${AUTOCONF_H}
    ${PREBUILT_HOST_TOOLS}/kconfig/mconf
      ${PROJECT_SOURCE_DIR}/Kconfig
  WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/kconfig
  USES_TERMINAL
)

# Parse the lines prefixed with CONFIG_ in the .config file from Kconfig
file(
  STRINGS
  ${DOTCONFIG}
  DOT_CONFIG_LIST
  REGEX "^CONFIG_"
)

foreach (CONFIG ${DOT_CONFIG_LIST})
  # CONFIG looks like: CONFIG_NET_BUF=y

  # Match the first part, the variable name
  string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})

  # Match the second part, variable value
  string(REGEX MATCH "=(.+$)" CONF_VARIABLE_VALUE ${CONFIG})
  # The variable name match included the '=' symbol. To just get the
  # part on the RHS we use match group 1
  set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})

  if("${CONF_VARIABLE_VALUE}" MATCHES "^\"(.*)\"$") # Is surrounded by quotes
    set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})
  endif()

  set("${CONF_VARIABLE_NAME}" "${CONF_VARIABLE_VALUE}")
endforeach()
