#
# (C) Copyright 2017 Rockchip Electronics Co., Ltd.
#
# SPDX-License-Identifier:     GPL-2.0+
#

obj-y += irq-gic.o

ifdef CONFIG_ROCKCHIP_GPIO_V2
obj-y += irq-gpio-v2.o
else
obj-y += irq-gpio.o
endif
obj-y += irq-generic.o
obj-y += irq-gpio-switch.o
obj-y += virq.o
