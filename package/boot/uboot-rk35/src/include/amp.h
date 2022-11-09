/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _AMP_H_
#define _AMP_H_

#include <dm.h>
#include <image.h>

#define AMP_I(fmt, args...)	printf("AMP: "fmt, ##args)
#define AMP_E(fmt, args...)	printf("AMP Error: "fmt, ##args)

#define MAP_AARCH(aarch64)	((aarch64) ? 1 : 0)
#define MAP_HYP(hyp)		((hyp) ? 1 : 0)
#define MAP_THUMB(thumb)	((thumb) ? 1 : 0)
#define MAP_SECURE(secure)	((secure) ? 0 : 1)

#define	MODE_AARCH64_SHIFT	1
#define	MODE_HYP_SHIFT		2
#define	MODE_THUMB_SHIFT	3
#define	MODE_SECURE_SHIFT	4

#define PE_STATE(aarch64, hyp, thumb, secure)				\
	       (((MAP_AARCH(aarch64) & 0x1) << MODE_AARCH64_SHIFT) |	\
		((MAP_HYP(hyp) & 0x1) << MODE_HYP_SHIFT) |		\
		((MAP_THUMB(thumb) & 0x1) << MODE_THUMB_SHIFT) |	\
		((MAP_SECURE(secure) & 0x1) << MODE_SECURE_SHIFT))

int amp_cpus_on(void);
int arm64_switch_amp_pe(bootm_headers_t *images);

#endif	/* _AMP_H_ */

