/*
 * Copyright (C) 2017 Rockchip Electronic Co.,Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#undef CONFIG_SPL_TEXT_BASE
#define CONFIG_SPL_TEXT_BASE CONFIG_TPL_TEXT_BASE

#undef CONFIG_SPL_MAX_SIZE
#define CONFIG_SPL_MAX_SIZE CONFIG_TPL_MAX_SIZE

#include "../cpu/u-boot-spl.lds"
