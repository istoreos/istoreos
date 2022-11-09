#
# Copyright (C) (C) Copyright 2016-2017 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-y += rknand.o
ifdef CONFIG_ARM64

ifdef CONFIG_ZFTL
ifdef CONFIG_SPL_BUILD
obj-y += rk_zftl_spl_arm_v8.o
else
obj-y += rk_zftl_arm_v8.o
endif
else
obj-y += rk_ftl_arm_v8.o
endif

else

ifdef CONFIG_ZFTL
obj-y += rk_zftl_arm_v7.o
else
obj-y += rk_ftl_arm_v7.o
endif

endif
