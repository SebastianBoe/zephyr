/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2020 Nordic Semiconductor
 *
 */

#ifndef PARTITION_MANAGER_OVERRIDES_H
#define PARTITION_MANAGER_OVERRIDES_H

// It appears that DT IMAGE x translates well to PM MCUBOOT y, so we
// translate accordingly. If it turns out that it does not translate
// we will have to simply undef all image symbols.

#include <pm_config.h>

#undef DT_FLASH_AREA_IMAGE_SCRATCH_ID
#undef DT_FLASH_AREA_IMAGE_0_NONSECURE_OFFSET_0
#undef DT_FLASH_AREA_IMAGE_0_NONSECURE_ID
#undef DT_FLASH_AREA_IMAGE_1_NONSECURE_ID
#undef DT_FLASH_AREA_IMAGE_0_ID
#undef DT_FLASH_AREA_IMAGE_1_ID
#undef DT_FLASH_AREA_IMAGE_2_ID
#undef DT_FLASH_AREA_IMAGE_3_ID

#define DT_FLASH_AREA_IMAGE_SCRATCH_ID				PM_MCUBOOT_SCRATCH_ID
#define DT_FLASH_AREA_IMAGE_0_NONSECURE_ID			PM_MCUBOOT_PRIMARY_ID
#define DT_FLASH_AREA_IMAGE_0_NONSECURE_OFFSET_0	PM_APP_ADDRESS
#define DT_FLASH_AREA_IMAGE_1_NONSECURE_ID			PM_MCUBOOT_SECONDARY_ID
#define DT_FLASH_AREA_IMAGE_0_ID					PM_MCUBOOT_PRIMARY_ID
#define DT_FLASH_AREA_IMAGE_1_ID					PM_MCUBOOT_SECONDARY_ID
#define DT_FLASH_AREA_IMAGE_2_ID					PM_MCUBOOT_PRIMARY_ID
#define DT_FLASH_AREA_IMAGE_3_ID					PM_MCUBOOT_SECONDARY_ID

// Undefine DT partitioning symbols that do not translate between DT
// and PM to ensure that DT partitioning symbols are not accidentally
// used simultaneously with PM partitioning information.

// NFFS, settings, and other systems all use the same 'storage'
// partition in DT, but in PM they all get their own partition, so
// this can not be translated.
#undef  DT_FLASH_AREA_STORAGE_ID
#undef  DT_FLASH_AREA_STORAGE_OFFSET
#undef  DT_FLASH_AREA_STORAGE_SIZE

#endif /* PARTITION_MANAGER_OVERRIDES_H */
