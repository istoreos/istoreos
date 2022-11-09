/* SPDX-License-Identifier: GPL-2.0+ */

#ifndef __BRCMNAND_H__
#define __BRCMNAND_H__

#include <linux/types.h>
#include <linux/io.h>

struct brcmnand_soc {
	bool (*ctlrdy_ack)(struct brcmnand_soc *soc);
	void (*ctlrdy_set_enabled)(struct brcmnand_soc *soc, bool en);
	void (*prepare_data_bus)(struct brcmnand_soc *soc, bool prepare,
				 bool is_param);
	void *ctrl;
};

static inline void brcmnand_soc_data_bus_prepare(struct brcmnand_soc *soc,
						 bool is_param)
{
	if (soc && soc->prepare_data_bus)
		soc->prepare_data_bus(soc, true, is_param);
}

static inline void brcmnand_soc_data_bus_unprepare(struct brcmnand_soc *soc,
						   bool is_param)
{
	if (soc && soc->prepare_data_bus)
		soc->prepare_data_bus(soc, false, is_param);
}

static inline u32 brcmnand_readl(void __iomem *addr)
{
	/*
	 * MIPS endianness is configured by boot strap, which also reverses all
	 * bus endianness (i.e., big-endian CPU + big endian bus ==> native
	 * endian I/O).
	 *
	 * Other architectures (e.g., ARM) either do not support big endian, or
	 * else leave I/O in little endian mode.
	 */
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_SYS_BIG_ENDIAN))
		return __raw_readl(addr);
	else
		return readl_relaxed(addr);
}

static inline void brcmnand_writel(u32 val, void __iomem *addr)
{
	/* See brcmnand_readl() comments */
	if (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_SYS_BIG_ENDIAN))
		__raw_writel(val, addr);
	else
		writel_relaxed(val, addr);
}

int brcmnand_probe(struct udevice *dev, struct brcmnand_soc *soc);
int brcmnand_remove(struct udevice *dev);

#ifndef __UBOOT__
extern const struct dev_pm_ops brcmnand_pm_ops;
#endif /* __UBOOT__ */

#endif /* __BRCMNAND_H__ */
