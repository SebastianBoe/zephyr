/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2019 Nordic Semiconductor
 *
 * Not a generated file. Feel free to modify.
 *
 * Poorly named for legacy compatibility reasons.
 */

#ifndef GENERATED_DTS_BOARD_H
#define GENERATED_DTS_BOARD_H

#include <generated_dts_board_unfixed.h>

#include <generated_dts_board_unfixed.h.deprecated>

/* The following definitions fixup the generated include */

#include <generated_dts_board_fixups.h>

#if USE_PARTITION_MANAGER

/* This header undefines unsupported DT symbols and translates others
   from DT to Partition Manager. */
#include "partition_manager_overrides.h"

#endif /* USE_PARTITION_MANAGER */

#endif /* GENERATED_DTS_BOARD_H */
