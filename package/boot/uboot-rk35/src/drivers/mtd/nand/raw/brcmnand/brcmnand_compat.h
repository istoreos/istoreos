/* SPDX-License-Identifier: GPL-2.0+ */

#ifndef __BRCMNAND_COMPAT_H
#define __BRCMNAND_COMPAT_H

#include <clk.h>
#include <dm.h>

struct clk *devm_clk_get(struct udevice *dev, const char *id);
int clk_prepare_enable(struct clk *clk);
void clk_disable_unprepare(struct clk *clk);

char *devm_kasprintf(struct udevice *dev, gfp_t gfp, const char *fmt, ...);

#endif /* __BRCMNAND_COMPAT_H */
