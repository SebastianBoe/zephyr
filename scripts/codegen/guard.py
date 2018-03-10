# Copyright (c) 2018 Bobby Noelte.
#
# SPDX-License-Identifier: Apache-2.0

class GuardMixin(object):
    __slots__ = []


    def if_device_tree_controller_compatible(self, device_type_name, compatible):
        is_compatible = self.device_tree_controller_compatible(device_type_name, compatible)
        self.outl("/* Guard({}) {}-controller {} */".format(
            is_compatible, device_type_name.lower(), compatible))
        if not is_compatible:
            self.generator_globals['generate_code'] = False

    def outl_guard_device_tree_controller(self, device_type_name, compatible):
        is_compatible = self.device_tree_controller_compatible(device_type_name, compatible)
        self.outl("#if {} /* Guard({}) {}-controller {} */".format(
            is_compatible, is_compatible, device_type_name.lower(), compatible))

    def outl_unguard_device_tree_controller(self, device_type_name, compatible):
        is_compatible = self.device_tree_controller_compatible(device_type_name, compatible)
        self.outl("#endif /* Guard({}) {}-controller {} */".format(
            is_compatible, device_type_name.lower(), compatible))

    def outl_guard_config(self, property_name):
        is_config = self.config_property(property_name, 0)
        self.outl("#if {} /* Guard({}) {} */".format(
            is_config, is_config, property_name))

    def outl_unguard_config(self, property_name):
        is_config = self.config_property(property_name, 0)
        self.outl("#endif /* Guard({}) {} */".format(is_config, property_name))
