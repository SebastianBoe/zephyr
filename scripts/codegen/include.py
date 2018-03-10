# Copyright (c) 2018 Bobby Noelte.
#
# SPDX-License-Identifier: Apache-2.0

from pathlib import Path
import io

class IncludeMixin(object):
    __slots__ = []

    def out_include(self, include_file):
        saved_input_file = self.options.input_file
        self.options.input_file = include_file
        output_fd = io.StringIO()
        input_file = Path(include_file)
        self.processor.processFile(str(input_file), output_fd, globals=self.generator_globals)
        self.options.input_file = saved_input_file
        self.out(output_fd.getvalue())

