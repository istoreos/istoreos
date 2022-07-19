#
# (C) Copyright 2004-2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

# rtk bt init
ifdef CONFIG_CMD_RTKBT_INIT
obj-y += \
    cmd_bt_init.o \
    osi/src/bt_list.o \
    osi/src/bt_skbuff.o \
    osi/src/osi_function.o \
    osi/src/osi_userial.o \
    osi/src/osi_usb.o \
    src/boot_uart/bt_hci_h5.o \
    src/boot_uart/hardware_uart.o \
    src/boot_usb/hardware_usb.o

ccflags-y := $(call cc-option,-Wno-unused-variable) \
    $(call cc-option,-Wno-strict-aliasing) \
    $(call cc-option,-Wno-unused-but-set-variable) \
    $(call cc-option,-Wno-unused-function) \
    -I$(srctree)/common/rtk_bt_init/include \
    -I$(srctree)/common/rtk_bt_init/osi/include
endif
