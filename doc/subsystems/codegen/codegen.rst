..
    Copyright (c) 2004-2015 Ned Batchelder
    SPDX-License-Identifier: MIT
    Copyright (c) 2018 Bobby Noelte
    SPDX-License-Identifier: Apache-2.0

.. _codegen:

Inline Code Generation
######################

For some repetitive or parameterized coding tasks, it's convenient to
use a code generating tool to build C code fragments, instead of writing
(or editing) that source code by hand. Such a tool can also access CMake build
parameters and device tree information to generate source code automatically
tailored and tuned to a specific project configuration.

The Zephyr project supports a code generating tool that processes embedded
Python "snippets" inlined in your source files. It can be used, for example,
to generate source code that creates and fills data structures, adapts
programming logic, creates configuration-specific code fragments, and more.

.. contents::
   :depth: 2
   :local:
   :backlinks: top

Description
***********

Python snippets that are inlined in a source file are used as code generators.
The tool to scan the source file for the Python snippets and process them is
Codegen. Codegen and part of this documentation is based on
`Cog <https://nedbatchelder.com/code/cog/index.html>`_ from Ned Batchelder.

The processing of source files is controlled by the CMake extension functions:
zephyr_sources_codegen(..) or zephyr_library_sources_codegen(..). The generated
source files are added to the Zephyr sources. During build the source files are
processed by Codegen and the generated source files are written to the CMake
binary directory.

The inlined Python snippets can contain any Python code, they are regular
Python scripts. All Python snippets in a source file and all Python snippets of
included template files are treated as a python script with a common set of
global Python variables. Global data created in one snippet can be used in
another snippet that is processed later on. This feature is e.g. used to
customize included template files.

An inlined Python snippet can always access the codegen module. The codegen
module encapsulates and provides all the functions to retrieve information
(options, device tree properties, CMake variables, config properties) and to
put out the generated code.

Codegen transforms files in a very simple way: it finds chunks of Python code
embedded in them, executes the Python code, and inserts its output back into
the original file. The file can contain whatever text you like around the
Python code. It will usually be source code.

For example, if you run this file through Codegen:

::

    /* This is my C file. */
    ...
    /**
     * @code{.codegen}
     * fnames = ['DoSomething', 'DoAnotherThing', 'DoLastThing']
     * for fn in fnames:
     *     codegen.outl("void %s();" % fn)
     * @endcode{.codegen}
     */
    /** @code{.codeins}@endcode */
    ...

it will come out like this:

::

    /* This is my C file. */
    ...
    /**
     * @code{.codegen}
     * fnames = ['DoSomething', 'DoAnotherThing', 'DoLastThing']
     * for fn in fnames:
     *     codegen.outl("void %s();" % fn)
     * @endcode{.codegen}
     */
    void DoSomething();
    void DoAnotherThing();
    void DoLastThing();
    /** @code{.codeins}@endcode */
    ...

Lines with @code{.codegen} or @code{.codeins}@endcode are marker lines.
The lines between @code{.codegen} and @endcode{.codegen} are the generator
Python code. The lines between @endcode{.codegen} and
@code{.codeins}@endcode are the output from the generator.

When Codegen runs, it discards the last generated Python output, executes the
generator Python code, and writes its generated output into the file. All text
lines outside of the special markers are passed through unchanged.

The Codegen marker lines can contain any text in addition to the marker tokens.
This makes it possible to hide the generator Python code from the source file.

In the sample above, the entire chunk of Python code is a C comment, so the
Python code can be left in place while the file is treated as C code.

The codegen module
******************

A module called codegen provides the functions you call to produce output into
your file. The functions are:

.. function:: codegen.out(sOut=’’ [, dedent=False][, trimblanklines=False])

    Writes text to the output.

    :param sOut: The string to write to the output.
    :param dedent: If dedent is True, then common initial white space is
                   removed from the lines in sOut before adding them to the
                   output.
    :param trimblanklines: If trimblanklines is True,
                           then an initial and trailing blank line are removed
                           from sOut before adding them to the output.

    ``dedent`` and ``trimblanklines`` make it easier to use
    multi-line strings, and they are only are useful for multi-line strings:

    ::

        codegen.out("""
            These are lines I
            want to write into my source file.
        """, dedent=True, trimblanklines=True)

.. function:: codegen.outl

    Same as codegen.out, but adds a trailing newline.

.. function:: codegen.msg(msg)

    Prints msg to stdout with a “Message: ” prefix.

.. function:: codegen.error(msg)

    Raises an exception with msg as the text. No traceback is included, so
    that non-Python programmers using your code generators won’t be scared.

.. attribute:: codegen.inFile

    An attribute, the path of the input file.

.. attribute:: codegen.outFile

    An attribute, the path of the output file.

.. attribute:: codegen.firstLineNum

    An attribute, the line number of the first line of Python code in the
    generator. This can be used to distinguish between two generators in the
    same input file, if needed.

.. attribute:: codegen.previous

    An attribute, the text output of the previous run of this generator. This
    can be used for whatever purpose you like, including outputting again with
    codegen.out()

The codegen module also provides a set of convenience functions:

Template file inclusion
-----------------------

.. function:: codegen.out_include(include_file)

    Write the text from include_file to the output. The include_file is processed
    by Codegen. Inline code generation in include_file can access the globals
    defined in the including source file before inclusion. The including source
    file can access the globals defined in the include_file (after inclusion).

Configuration property access
-----------------------------

.. function:: codegen.config_property(property_name [, default="<unset>"])

    Get the value of a configuration property from autoconf.h. If property_name
    is not given in autoconf.h the default value is returned.

CMake variable access
---------------------

.. function:: codegen.cmake_variable(variable_name [, default="<unset>"])

    Get the value of a CMake variable. If variable_name is not provided to
    Codegen by CMake the default value is returned. The following variables
    are provided to Codegen:

    - "PROJECT_NAME"
    - "PROJECT_SOURCE_DIR"
    - "PROJECT_BINARY_DIR"
    - "CMAKE_SOURCE_DIR"
    - "CMAKE_BINARY_DIR"
    - "CMAKE_CURRENT_SOURCE_DIR"
    - "CMAKE_CURRENT_BINARY_DIR"
    - "CMAKE_CURRENT_LIST_DIR"
    - "CMAKE_FILES_DIRECTORY"
    - "CMAKE_PROJECT_NAME"
    - "CMAKE_SYSTEM"
    - "CMAKE_SYSTEM_NAME"
    - "CMAKE_SYSTEM_VERSION"
    - "CMAKE_SYSTEM_PROCESSOR"
    - "CMAKE_C_COMPILER"
    - "CMAKE_CXX_COMPILER"
    - "CMAKE_COMPILER_IS_GNUCC"
    - "CMAKE_COMPILER_IS_GNUCXX"
    - "GENERATED_DTS_BOARD_H"
    - "GENERATED_DTS_BOARD_CONF"

.. function:: codegen.cmake_cache_variable(variable_name [, default="<unset>"])

    Get the value of a CMake variable from CMakeCache.txt. If variable_name
    is not given in CMakeCache.txt the default value is returned.

Device tree property access
---------------------------

.. function:: codegen.device_tree_controller_count(device_type_name [, default="<unset>"])

    Get the number of activated devices of given type.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :return: number of activated devices

.. function:: codegen.device_tree_controller_prefix(device_type_name, device_index [, default="<unset>"])

    Get the device tree prefix for the device of the given type and index.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :return: device tree prefix (e.g. ST_STM32_SPI_FIFO_4000000)

.. function:: codegen.device_tree_controller_property(device_type_name, device_index, property_name [, default="<unset>"])

    Get device tree property value for the device of the given type and index.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :param property_name: Property name of the device tree property
                          (e.g. 'BASE_ADDRESS', 'LABEL', 'IRQ_0', ...)
    :return: property value as given in generated_dts_board.conf

.. function:: codegen.device_tree_controller_property_indirect(device_type_name, device_index, property_name, property_name_indirect [, default="<unset>"])

    Get the property of another device given by a property.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :param property_name: Property that denotes the device tree prefix of the other device
    :param property_name_indirect: Property name of the other device property
                                   (e.g. 'BASE_ADDRESS', 'LABEL', 'IRQ_0', ...)
    :return: property value as given in generated_dts_board.conf

.. function:: codegen.device_tree_controller_compatible_x(device_type_name, device_index, compatible [, default="<unset>"])

    Check compatibility to device given by type and index.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :param compatible: driver compatibility string (e.g. st,stm32-spi-fifo)
    :return: 1 if compatible, 0 otherwise

.. function:: codegen.device_tree_controller_compatible(device_type_name, compatible)

    Check compatibility to at least one activated device of given type.

    The compatible parameter is checked against the compatible property of
    all activated devices of given type.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param compatible: driver compatibility string (e.g. st,stm32-spi-fifo)
    :return: 1 if there is compatibility to at least one activated device,
             0 otherwise

.. function:: codegen.device_tree_controller_data_name(device_type_name, device_index, data)

    Get the name of the driver data.

    Generates an unique name for driver data.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :param data: suffix for data (e.g. 'config')
    :return: controller data name (e.g. ST_STM32_SPI_FIFO_4000000_config)

.. function:: codegen.device_tree_controller_device_name(device_type_name, device_index)

    Get the device name.

    The device tree prefix of the device is used as the device name.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :return: device name (e.g. ST_STM32_SPI_FIFO_4000000)

.. function:: codegen.device_tree_controller_driver_name(device_type_name, device_index)

    Get the driver name.

    This is a convenience function for:

    - codegen.device_tree_controller_property(device_type_name, device_index, 'LABEL')

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :return: driver name (e.g. "SPI_0")

.. function:: codegen.device_tree_controller_driver_name_indirect(device_type_name, device_index, property_name)

     Get the driver name of another device given by the property.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param device_index: Index of device
    :param property_name: Property that denotes the device tree prefix of the other device
    :return: driver name of other device (e.g. "GPIOA")

Guarding chunks of source code
------------------------------

.. function:: codegen.if_device_tree_controller_compatible(device_type_name, compatible)

    Stop code generation if there is no activated device that is compatible.

    Code generation stops right before the generator end marker @code{.codeins}@endcode.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param compatible: driver compatibility string (e.g. st,stm32-spi-fifo)

.. function:: codegen.outl_guard_device_tree_controller(device_type_name, compatible)

    Write a guard (#if [guard]) C preprocessor directive to output.

    If there is an activated device that is compatible the guard value is set to 1,
    otherwise it is set to 0.

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param compatible: driver compatibility string (e.g. st,stm32-spi-fifo)

.. function:: codegen.outl_unguard_device_tree_controller(device_type_name, compatible)

    Write an unguard (#endif) C preprocessor directive to output.

    This is the closing command for codegen.outl_guard_device_tree_controller().

    :param device_type_name: Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    :param compatible: driver compatibility string (e.g. st,stm32-spi-fifo)

.. function:: codegen.outl_guard_config(property_name)

    Write a guard (#if [guard]) C preprocessor directive to output.

    If there is a configuration property of the given name the property value
    is used as guard value, otherwise it is set to 0.

    :param property_name: Name of the configuration property.

.. function:: codegen.outl_unguard_config(property_name)

    Write an unguard (#endif) C preprocessor directive to output.

    This is the closing command for codegen.outl_guard_config().

    :param property_name: Name of the configuration property.

Logging
-------

.. function:: codegen.log(message [, message_type=None] [, end="\n"] [, logonly=True])

.. function:: codegen.msg(s)

.. function:: codegen.error(msg='Error raised by codegen.')

    The codegen.error function.

    Instead of raising standard python errors, codegen generators can use
    this function.  It will display the error without a scary Python
    traceback.

.. function:: codegen.prout(s [, end="\n"])

.. function:: codegen.prerr(s [, end="\n"])

Code generation in the build process
************************************

Code generation has to be invoked as part of the build process. Zephyr uses
`CMake <https://cmake.org/>`_ as the tool to manage building the project.

A file that contains inline code generation has to be added to the project
by one of the following commands in a :file:`CMakeList.txt` file.

::

    zephyr_sources_codegen(codegen_file.c)
    zephyr_sources_codegen_ifdef(ifguard codegen_file.c)
    zephyr_library_sources_codegen(codegen_file.c)
    zephyr_library_sources_codegen_ifdef(ifguard codegen_file.c)

