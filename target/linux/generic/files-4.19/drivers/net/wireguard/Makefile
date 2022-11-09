# SPDX-License-Identifier: GPL-2.0
#
# Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.

ccflags-y := -O3 -fvisibility=hidden
ccflags-$(CONFIG_WIREGUARD_DEBUG) += -DDEBUG -g
ccflags-y += -D'pr_fmt(fmt)=KBUILD_MODNAME ": " fmt'
ccflags-y += -Wframe-larger-than=2048
ccflags-$(if $(WIREGUARD_VERSION),y,) += -D'WIREGUARD_VERSION="$(WIREGUARD_VERSION)"'

wireguard-y := main.o noise.o device.o peer.o timers.o queueing.o send.o receive.o socket.o peerlookup.o allowedips.o ratelimiter.o cookie.o netlink.o

include $(src)/crypto/Kbuild.include
include $(src)/compat/Kbuild.include

obj-$(CONFIG_WIREGUARD) := wireguard.o
