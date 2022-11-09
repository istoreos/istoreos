#
# SPDX-License-Identifier: GPL-2.0
#
#  Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
#

obj-$(CONFIG_$(SPL_TPL_)ROCKCHIP_CRYPTO_V1) += crypto_v1.o crypto_hash_cache.o
obj-$(CONFIG_$(SPL_TPL_)ROCKCHIP_CRYPTO_V2) += crypto_v2.o crypto_hash_cache.o

ifeq ($(CONFIG_$(SPL_TPL_)ROCKCHIP_CRYPTO_V2)$(CONFIG_$(SPL_TPL_)ROCKCHIP_RSA), yy)
obj-y += crypto_v2_pka.o crypto_v2_util.o
endif
