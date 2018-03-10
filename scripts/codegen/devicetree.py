# Copyright (c) 2018 Bobby Noelte.
#
# SPDX-License-Identifier: Apache-2.0

from pathlib import Path

class DeviceTreeMixin(object):
    __slots__ = []

    _device_tree = None

    @staticmethod
    def _device_tree_label(s):
        # Transmute ,- to _
        s = s.replace("-", "_")
        s = s.replace(",", "_")
        s = s.replace("@", "_")
        return s.upper()

    def _device_tree_property(self, property_name, default="<unset>"):
        if self._device_tree is None:
            dts_file = self.cmake_variable("GENERATED_DTS_BOARD_CONF", None)
            if dts_file is None:
                return \
                "CMake variable GENERATED_DTS_BOARD_CONF not defined to codegen."
            dts_file = Path(dts_file)
            if not dts_file.is_file():
                return \
                "Generated device tree board configuration {} not found/ no access.".format(dts_file)
            dts = {}
            with open(str(dts_file)) as dts_fd:
                for line in dts_fd:
                    if line.startswith('#'):
                        continue
                    if "=" not in line:
                        continue
                    key, value = line.partition("=")[::2]
                    dts[key.strip()] = value.strip()
            self._device_tree = dts
        if default == "<unset>":
            default = \
                "Device tree property {} not defined.".format(property_name)
        property_value = self._device_tree.get(property_name, default)
        return property_value

    ##
    # @brief Get the number of activated devices of given type.
    #
    # @attention The SOC_[type]_CONTROLLER_COUNT key shall be defined in
    #            generated_dts_board.conf. This is achieved by a [type]-controller
    #            directive in the device tree.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @return number of activated devices
    #
    def device_tree_controller_count(self, device_type_name, default="<unset>"):
        controller_count_property_name = "SOC_{}_CONTROLLER_COUNT".format(device_type_name)
        return self._device_tree_property(controller_count_property_name, default)

    ##
    # @brief Get the device tree prefix for the device of the given type and idx.
    #
    # @attention The SOC_[type]_CONTROLLER_COUNT key shall be defined in
    #            generated_dts_board.conf. This is achieved by a [type]-controller
    #            directive in the device tree.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @return device tree prefix (e.g. ST_STM32_SPI_FIFO_4000000)
    #
    def device_tree_controller_prefix(self, device_type_name, device_index, default="<unset>"):
        controller_prefix_property_name = "SOC_{}_CONTROLLER_{}".format(device_type_name, device_index)
        return self._device_tree_property(controller_prefix_property_name, default)

    ##
    # @brief Get device tree property value for the device of the given type and idx.
    #
    # @attention The SOC_[type]_CONTROLLER_[idx] key shall be defined in
    #            generated_dts_board.conf. This is achieved by a [type]-controller
    #            directive in the device tree.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @param property_name Property name of the device tree property define
    #                      (e.g. 'BASE_ADDRESS', 'LABEL', 'IRQ_0', ...)
    # @return property value as given in generated_dts_board.conf
    #
    def device_tree_controller_property(self, device_type_name, device_index, property_name, default="<unset>"):
        controller_prefix = self.device_tree_controller_prefix(device_type_name, device_index, None)
        if controller_prefix is None:
            if default == "<unset>":
                default = \
                "Device tree property SOC_{}_CONTROLLER_{} not defined.".format(device_type_name, device_index)
            return default
        property_name = "{}_{}".format(controller_prefix, property_name)
        return self._device_tree_property(property_name, default)

    ##
    # @brief Get the property of another device given by a property.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @param property_name Property that denotes the dts prefix of the other device
    # @param property_indirect property of the other device
    # @return property value of the other device
    #
    def device_tree_controller_property_indirect(self, device_type_name, device_index,
                                                 property_name, property_name_indirect,
                                                 default="<unset>"):
        controller_prefix = self.device_tree_controller_property(
                                device_type_name, device_index, property_name, None)
        if controller_prefix is None:
            if default == "<unset>":
                controller_prefix = self.device_tree_controller_prefix(device_type_name, device_index)
                default = \
                "Device tree property {}_{} not defined.".format(controller_prefix, property_name)
            return default
        property_name = "{}_{}".format(controller_prefix, property_name_indirect)
        return self._device_tree_property(property_name, default)

    ##
    # @brief Check compatibility to device given by type and idx.
    #
    # The @p compatible parameter is checked against the compatible property of
    # the device given by @p device_type_name and @p device_index.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @param compatible driver compatibility string (e.g. st,stm32-spi-fifo)
    # @return 1 if compatible, 0 otherwise
    #
    def device_tree_controller_compatible_x(self, device_type_name,
                                            device_index, compatible,
                                            default="<unset>"):
        compatible_count = self.device_tree_controller_property(device_type_name, device_index,
                                                                'COMPATIBLE_COUNT', None)
        if compatible_count is None or int(compatible_count) == 0:
            return 0
        compatible_count = int(compatible_count)
        # sanitize for label usage
        compatible = self._device_tree_label(compatible)
        compatible_id_property_name = "COMPATIBLE_ID_{}".format(compatible)
        compatible_id = self._device_tree_property(compatible_id_property_name, None)
        if compatible_id is None:
            if default == "<unset>":
                default = \
                "Device tree property COMPATIBLE_ID_{} not defined.".format(compatible)
            return default
        for x in range(0, compatible_count):
            controller_compatibe_id_property_label = "COMPATIBLE_{}_ID".format(x)
            controller_compatibe_id = self.device_tree_controller_property(
                device_type_name, device_index, controller_compatibe_id_property_label, None)
            if controller_compatibe_id == compatible_id:
                return 1
        return 0

    ##
    # @brief Check compatibility to at least one activated device of given type.
    #
    # The @p compatible parameter is checked against the compatible property of
    # all activated devices of given @p type.
    #
    # @param device_type_name Type of device controller (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param compatible driver compatibility string (e.g. 'st,stm32-spi-fifo')
    # @return 1 if there is compatibility to at least one activated device,
    #         0 otherwise
    #
    def device_tree_controller_compatible(self, device_type_name, compatible):
        controller_count = self.device_tree_controller_count(device_type_name, None)
        if controller_count is None or int(controller_count) == 0:
            return 0
        controller_count = int(controller_count)
        for x in range(0, controller_count):
            if self.device_tree_controller_compatible_x(device_type_name, x, compatible, None) == 1:
                return 1
        return 0

    ##
    # @brief Get the name of the driver data.
    #
    # Generates an unique name for driver data.
    #
    # @attention The SOC_[type]_CONTROLLER_[idx] key shall be defined in
    #            generated_dts_board.conf. This is achieved by a
    #            [type]-controller directive in the device tree.
    #
    # @param device_type_name Type of device controller
    #                         (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @param data suffix for data
    # @return controller data name (e.g. ST_STM32_SPI_FIFO_4000000_config)
    #
    def device_tree_controller_data_name(self, device_type_name, device_index,
                                         data):
        data_name = "{}_{}".format(
            self.device_tree_controller_prefix(device_type_name, device_index),
            data)
        return data_name

    ##
    # @brief Get the device name.
    #
    # The device tree prefix is used as the device name.
    #
    # @attention The SOC_[type]_CONTROLLER_[idx] key shall be defined in
    #            generated_dts_board.conf. This is achieved by a [type]-controller
    #            directive in the device tree.
    #
    # @param device_type_name Type of device controller
    #                         (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @return device name (e.g. ST_STM32_SPI_FIFO_4000000)
    #
    def device_tree_controller_device_name(self, device_type_name,
                                           device_index):
        return self.device_tree_controller_prefix(device_type_name,
                                                  device_index)

    ##
    # @brief Get the driver name.
    #
    # This is a convenience function for:
    #   - device_tree_controller_property(device_type_name, device_index, 'LABEL')
    #
    # @attention The SOC_[type]_CONTROLLER_[idx] key shall be defined in
    #            generated_dts_board.conf. This is achieved by a [type]-controller
    #            directive in the device tree.
    #
    # @param device_type_name Type of device controller
    #                         (e.g. 'SPI', 'GPIO', 'PIN', ...)
    # @param device_index Index of device
    # @return driver name (e.g. "SPI_0")
    #
    def device_tree_controller_driver_name(self, device_type_name,
                                           device_index):
        return self.device_tree_controller_property(device_type_name,
                                                    device_index,
                                                    'LABEL')

    def device_tree_controller_driver_name_indirect(self, device_type_name,
                                                    device_index, property_name):
        return self.device_tree_controller_property_indirect(
            device_type_name, device_index, property_name, 'LABEL')
