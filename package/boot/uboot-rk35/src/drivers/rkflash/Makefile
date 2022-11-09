#
# Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier:	GPL-2.0
#

obj-y += rkflash_blk.o rkflash_debug.o
obj-$(CONFIG_RKNANDC_NAND) += rksftl.o rknandc_base.o rkflash_api.o flash.o nandc.o
obj-$(CONFIG_RKSFC_NAND) += rksftl.o rksfc_base.o  rkflash_api.o sfc_nand.o sfc.o
obj-$(CONFIG_RKSFC_NOR) += rksfc_base.o rkflash_api.o sfc_nor.o sfc.o

ifneq (, $(CONFIG_RKNANDC_NAND)$(CONFIG_RKSFC_NAND))

ifdef CONFIG_ARM64
rksftl-y += rk_sftl_arm_v8.o
else
rksftl-y += rk_sftl_arm_v7.o
endif

endif
