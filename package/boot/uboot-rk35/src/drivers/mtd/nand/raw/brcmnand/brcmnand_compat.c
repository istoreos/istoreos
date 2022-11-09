// SPDX-License-Identifier: GPL-2.0+

#include <common.h>
#include "brcmnand_compat.h"

struct clk *devm_clk_get(struct udevice *dev, const char *id)
{
	struct clk *clk;
	int ret;

	clk = devm_kzalloc(dev, sizeof(*clk), GFP_KERNEL);
	if (!clk) {
		debug("%s: can't allocate clock\n", __func__);
		return ERR_PTR(-ENOMEM);
	}

	ret = clk_get_by_name(dev, id, clk);
	if (ret < 0) {
		debug("%s: can't get clock (ret = %d)!\n", __func__, ret);
		return ERR_PTR(ret);
	}

	return clk;
}

int clk_prepare_enable(struct clk *clk)
{
	return clk_enable(clk);
}

void clk_disable_unprepare(struct clk *clk)
{
	clk_disable(clk);
}

static char *devm_kvasprintf(struct udevice *dev, gfp_t gfp, const char *fmt,
			     va_list ap)
{
	unsigned int len;
	char *p;
	va_list aq;

	va_copy(aq, ap);
	len = vsnprintf(NULL, 0, fmt, aq);
	va_end(aq);

	p = devm_kmalloc(dev, len + 1, gfp);
	if (!p)
		return NULL;

	vsnprintf(p, len + 1, fmt, ap);

	return p;
}

char *devm_kasprintf(struct udevice *dev, gfp_t gfp, const char *fmt, ...)
{
	va_list ap;
	char *p;

	va_start(ap, fmt);
	p = devm_kvasprintf(dev, gfp, fmt, ap);
	va_end(ap);

	return p;
}
