# SPDX-License-Identifier: Apache-2.0

set_ifndef(${IMAGE}BOARD_FLASH_RUNNER jlink)
set_ifndef(${IMAGE}BOARD_DEBUG_RUNNER jlink)
board_finalize_runner_args(jlink "--dt-flash=y")
