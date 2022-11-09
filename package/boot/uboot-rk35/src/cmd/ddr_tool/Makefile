#
# (C) Copyright 2018 Rockchip Electronics Co., Ltd.
#
# SPDX-License-Identifier:	GPL-2.0+
#

# We don't want the bootrom-helper present in a full U-Boot build, as
# this may have entered from ATF with the stack-pointer pointing to
# inaccessible/protected memory (and the bootrom-helper assumes that
# the stack-pointer is valid before switching to the U-Boot stack).
ifdef CONFIG_ROCKCHIP_PX30
obj-$(CONFIG_CMD_DDR_TEST_TOOL) = ddr_test_px30.o
endif
ifdef CONFIG_ROCKCHIP_RK3328
obj-$(CONFIG_CMD_DDR_TEST_TOOL) = ddr_test_rk3328.o
endif
ifdef CONFIG_ROCKCHIP_RK1808
obj-$(CONFIG_CMD_DDR_TEST_TOOL) = ddr_test_rk1808.o
endif
ifndef CONFIG_CMD_MEMTESTER
obj-$(CONFIG_CMD_DDR_TEST_TOOL) += ../memtester/ddr_tester_common.o
obj-$(CONFIG_CMD_DDR_TEST_TOOL) += ../memtester/io_map.o
endif
obj-$(CONFIG_CMD_DDR_TEST_TOOL) += ddr_dq_eye.o

