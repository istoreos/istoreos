# SPDX-License-Identifier: GPL-2.0

cdns3-y					:= core.o drd.o

obj-$(CONFIG_USB_CDNS3)			+= cdns3.o

cdns3-$(CONFIG_$(SPL_)USB_CDNS3_GADGET)	+= gadget.o ep0.o

cdns3-$(CONFIG_$(SPL_)USB_CDNS3_HOST)	+= host.o

obj-$(CONFIG_USB_CDNS3_TI)		+= cdns3-ti.o
