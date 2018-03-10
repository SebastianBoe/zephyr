# Copyright (c) 2018 Bobby Noelte.
#
# SPDX-License-Identifier: Apache-2.0

import os
import sys
import shlex
from pathlib import Path


class ConfigMixin(object):
    __slots__ = []

    _autoconf = None
    _autoconf_filename = None

    def config_property(self, property_name, default="<unset>"):
        if self._autoconf is None:
            autoconf_file = self.cmake_variable("PROJECT_BINARY_DIR", None)
            if autoconf_file is None:
                if default == "<unset>":
                    default = \
                    "CMake variable PROJECT_BINARY_DIR not defined to codegen."
                return default
            autoconf_file = Path(autoconf_file).joinpath('include/generated/autoconf.h')
            if not autoconf_file.is_file():
                if default == "<unset>":
                    default = \
                    "Generated configuration {} not found/ no access.".format(autoconf_file)
                return default
            autoconf = {}
            with open(str(autoconf_file)) as autoconf_fd:
                for line in autoconf_fd:
                    if not line.startswith('#'):
                        continue
                    if " " not in line:
                        continue
                    key, value = shlex.split(line)[1:]
                    autoconf[key] = value
            self._autoconf = autoconf
            self._autoconf_filename = str(autoconf_file)
        if default == "<unset>":
            default = \
            "Config property {} not defined in {}.".format(
                property_name, self._autoconf_filename)
        property_value = self._autoconf.get(property_name, default)
        return property_value

