# SPDX-License-Identifier: Apache-2.0

function(vhx_convert)
  # Convert a hex image into a vhx image
  #
  # Arguments:
  # HEX_FILE_IN - (required) Target hex file
  # VHX_FILE_NAME_PREFIX - (required) Prefix for the vhx file
  # VHX_FILE_OUT - (required) VHX file output
  # DEPENDS - (optional) One or more dependencies for the VHX generation

  set(one_value_args HEX_FILE_IN VHX_FILE_NAME_PREFIX VHX_FILE_OUT)
  set(multi_value_args DEPENDS)
  cmake_parse_arguments(VHX_CONVERT_ARG "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  if (NOT DEFINED VHX_CONVERT_ARG_HEX_FILE_IN
      OR NOT DEFINED VHX_CONVERT_ARG_VHX_FILE_NAME_PREFIX
      OR NOT DEFINED VHX_CONVERT_ARG_VHX_FILE_OUT
      )
    message(FATAL_ERROR "Missing parameter, required: HEX_FILE_IN VHX_FILE_NAME_PREFIX VHX_FILE_OUT")
  endif()

  set(converted_vhx ${VHX_CONVERT_ARG_VHX_FILE_NAME_PREFIX}.vhx)
  set(${VHX_CONVERT_ARG_VHX_FILE_OUT} ${converted_vhx} PARENT_SCOPE)
  get_filename_component(hex_filename ${VHX_CONVERT_ARG_HEX_FILE_IN} NAME)
  get_filename_component(vhx_filename ${converted_vhx} NAME)

  set(vhx_cmd
    ${PYTHON_EXECUTABLE}
    ${ZEPHYR_BASE}/scripts/vhx_convert.py
    )

  add_custom_command(
    OUTPUT
    ${converted_vhx}

    COMMAND
    ${vhx_cmd}
    ${VHX_CONVERT_ARG_HEX_FILE_IN}
    -f hex
    -o ${converted_vhx}

    WORKING_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}

    DEPENDS
    ${VHX_CONVERT_ARG_DEPENDS}

    COMMENT
    "Converting ${hex_filename} to ${vhx_filename}"
    )
endfunction()
