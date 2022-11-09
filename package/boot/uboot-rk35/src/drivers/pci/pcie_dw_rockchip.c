// SPDX-License-Identifier: GPL-2.0+
/*
 * Rockchip DesignWare based PCIe host controller driver
 *
 * Copyright (c) 2021 Rockchip, Inc.
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <generic-phy.h>
#include <pci.h>
#include <power-domain.h>
#include <power/regulator.h>
#include <reset.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm-generic/gpio.h>
#include <asm/arch-rockchip/clock.h>
#include <linux/iopoll.h>

DECLARE_GLOBAL_DATA_PTR;

struct rk_pcie {
	struct udevice	*dev;
	struct udevice  *vpcie3v3;
	void		*dbi_base;
	void		*apb_base;
	void		*cfg_base;
	fdt_size_t	cfg_size;
	struct phy	phy;
	struct clk_bulk	clks;
	int		first_busno;
	struct reset_ctl_bulk	rsts;
	struct gpio_desc	rst_gpio;
	struct pci_region	io;
	struct pci_region	mem;
	bool		is_bifurcation;
	u32 gen;
};

enum {
	PCIBIOS_SUCCESSFUL = 0x0000,
	PCIBIOS_UNSUPPORTED = -ENODEV,
	PCIBIOS_NODEV = -ENODEV,
};

#define msleep(a)		udelay((a) * 1000)

/* Parameters for the waiting for iATU enabled routine */
#define PCIE_CLIENT_GENERAL_DEBUG	0x104
#define PCIE_CLIENT_HOT_RESET_CTRL	0x180
#define PCIE_LTSSM_ENABLE_ENHANCE	BIT(4)
#define PCIE_CLIENT_LTSSM_STATUS	0x300
#define SMLH_LINKUP			BIT(16)
#define RDLH_LINKUP			BIT(17)
#define PCIE_CLIENT_DBG_FIFO_MODE_CON	0x310
#define PCIE_CLIENT_DBG_FIFO_PTN_HIT_D0 0x320
#define PCIE_CLIENT_DBG_FIFO_PTN_HIT_D1 0x324
#define PCIE_CLIENT_DBG_FIFO_TRN_HIT_D0 0x328
#define PCIE_CLIENT_DBG_FIFO_TRN_HIT_D1 0x32c
#define PCIE_CLIENT_DBG_FIFO_STATUS	0x350
#define PCIE_CLIENT_DBG_TRANSITION_DATA	0xffff0000
#define PCIE_CLIENT_DBF_EN		0xffff0003
#define RK_PCIE_DBG			0

/* PCI DBICS registers */
#define PCIE_LINK_STATUS_REG		0x80
#define PCIE_LINK_STATUS_SPEED_OFF	16
#define PCIE_LINK_STATUS_SPEED_MASK	(0xf << PCIE_LINK_STATUS_SPEED_OFF)
#define PCIE_LINK_STATUS_WIDTH_OFF	20
#define PCIE_LINK_STATUS_WIDTH_MASK	(0xf << PCIE_LINK_STATUS_WIDTH_OFF)

#define PCIE_LINK_CAPABILITY		0x7c
#define PCIE_LINK_CTL_2			0xa0
#define TARGET_LINK_SPEED_MASK		0xf
#define LINK_SPEED_GEN_1		0x1
#define LINK_SPEED_GEN_2		0x2
#define LINK_SPEED_GEN_3		0x3

#define PCIE_MISC_CONTROL_1_OFF		0x8bc
#define PCIE_DBI_RO_WR_EN		BIT(0)

#define PCIE_LINK_WIDTH_SPEED_CONTROL	0x80c
#define PORT_LOGIC_SPEED_CHANGE		BIT(17)

/*
 * iATU Unroll-specific register definitions
 * From 4.80 core version the address translation will be made by unroll.
 * The registers are offset from atu_base
 */
#define PCIE_ATU_UNR_REGION_CTRL1	0x00
#define PCIE_ATU_UNR_REGION_CTRL2	0x04
#define PCIE_ATU_UNR_LOWER_BASE		0x08
#define PCIE_ATU_UNR_UPPER_BASE		0x0c
#define PCIE_ATU_UNR_LIMIT		0x10
#define PCIE_ATU_UNR_LOWER_TARGET	0x14
#define PCIE_ATU_UNR_UPPER_TARGET	0x18

#define PCIE_ATU_REGION_INDEX1		(0x1 << 0)
#define PCIE_ATU_REGION_INDEX0		(0x0 << 0)
#define PCIE_ATU_TYPE_MEM		(0x0 << 0)
#define PCIE_ATU_TYPE_IO		(0x2 << 0)
#define PCIE_ATU_TYPE_CFG0		(0x4 << 0)
#define PCIE_ATU_TYPE_CFG1		(0x5 << 0)
#define PCIE_ATU_ENABLE			(0x1 << 31)
#define PCIE_ATU_BAR_MODE_ENABLE	(0x1 << 30)
#define PCIE_ATU_BUS(x)			(((x) & 0xff) << 24)
#define PCIE_ATU_DEV(x)			(((x) & 0x1f) << 19)
#define PCIE_ATU_FUNC(x)		(((x) & 0x7) << 16)

/* Register address builder */
#define PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(region)        \
	((0x3 << 20) | ((region) << 9))
#define PCIE_GET_ATU_INB_UNR_REG_OFFSET(region) \
	((0x3 << 20) | ((region) << 9) | (0x1 << 8))

/* Parameters for the waiting for iATU enabled routine */
#define LINK_WAIT_MAX_IATU_RETRIES	5
#define LINK_WAIT_IATU			10000

static int rk_pcie_read(void __iomem *addr, int size, u32 *val)
{
	if ((uintptr_t)addr & (size - 1)) {
		*val = 0;
		return PCIBIOS_UNSUPPORTED;
	}

	if (size == 4) {
		*val = readl(addr);
	} else if (size == 2) {
		*val = readw(addr);
	} else if (size == 1) {
		*val = readb(addr);
	} else {
		*val = 0;
		return PCIBIOS_NODEV;
	}

	return PCIBIOS_SUCCESSFUL;
}

static int rk_pcie_write(void __iomem *addr, int size, u32 val)
{
	if ((uintptr_t)addr & (size - 1))
		return PCIBIOS_UNSUPPORTED;

	if (size == 4)
		writel(val, addr);
	else if (size == 2)
		writew(val, addr);
	else if (size == 1)
		writeb(val, addr);
	else
		return PCIBIOS_NODEV;

	return PCIBIOS_SUCCESSFUL;
}

static u32 __rk_pcie_read_apb(struct rk_pcie *rk_pcie, void __iomem *base,
			      u32 reg, size_t size)
{
	int ret;
	u32 val;

	ret = rk_pcie_read(base + reg, size, &val);
	if (ret)
		dev_err(rk_pcie->pci->dev, "Read APB address failed\n");

	return val;
}

static void __rk_pcie_write_apb(struct rk_pcie *rk_pcie, void __iomem *base,
				u32 reg, size_t size, u32 val)
{
	int ret;

	ret = rk_pcie_write(base + reg, size, val);
	if (ret)
		dev_err(rk_pcie->pci->dev, "Write APB address failed\n");
}

static inline u32 rk_pcie_readl_apb(struct rk_pcie *rk_pcie, u32 reg)
{
	return __rk_pcie_read_apb(rk_pcie, rk_pcie->apb_base, reg, 0x4);
}

static inline void rk_pcie_writel_apb(struct rk_pcie *rk_pcie, u32 reg,
				      u32 val)
{
	__rk_pcie_write_apb(rk_pcie, rk_pcie->apb_base, reg, 0x4, val);
}

static int rk_pcie_get_link_speed(struct rk_pcie *rk_pcie)
{
	return (readl(rk_pcie->dbi_base + PCIE_LINK_STATUS_REG) &
		PCIE_LINK_STATUS_SPEED_MASK) >> PCIE_LINK_STATUS_SPEED_OFF;
}

static int rk_pcie_get_link_width(struct rk_pcie *rk_pcie)
{
	return (readl(rk_pcie->dbi_base + PCIE_LINK_STATUS_REG) &
		PCIE_LINK_STATUS_WIDTH_MASK) >> PCIE_LINK_STATUS_WIDTH_OFF;
}

static void rk_pcie_writel_ob_unroll(struct rk_pcie *rk_pcie, u32 index,
				     u32 reg, u32 val)
{
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);
	void __iomem *base = rk_pcie->dbi_base;

	writel(val, base + offset + reg);
}

static u32 rk_pcie_readl_ob_unroll(struct rk_pcie *rk_pcie, u32 index, u32 reg)
{
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);
	void __iomem *base = rk_pcie->dbi_base;

	return readl(base + offset + reg);
}

static inline void rk_pcie_dbi_write_enable(struct rk_pcie *rk_pcie, bool en)
{
	u32 val;

	val = readl(rk_pcie->dbi_base + PCIE_MISC_CONTROL_1_OFF);

	if (en)
		val |= PCIE_DBI_RO_WR_EN;
	else
		val &= ~PCIE_DBI_RO_WR_EN;
	writel(val, rk_pcie->dbi_base + PCIE_MISC_CONTROL_1_OFF);
}

static void rk_pcie_setup_host(struct rk_pcie *rk_pcie)
{
	u32 val;

	rk_pcie_dbi_write_enable(rk_pcie, true);

	/* setup RC BARs */
	writel(PCI_BASE_ADDRESS_MEM_TYPE_64,
	       rk_pcie->dbi_base + PCI_BASE_ADDRESS_0);
	writel(0x0, rk_pcie->dbi_base + PCI_BASE_ADDRESS_1);

	/* setup interrupt pins */
	val = readl(rk_pcie->dbi_base + PCI_INTERRUPT_LINE);
	val &= 0xffff00ff;
	val |= 0x00000100;
	writel(val, rk_pcie->dbi_base + PCI_INTERRUPT_LINE);

	/* setup bus numbers */
	val = readl(rk_pcie->dbi_base + PCI_PRIMARY_BUS);
	val &= 0xff000000;
	val |= 0x00ff0100;
	writel(val, rk_pcie->dbi_base + PCI_PRIMARY_BUS);

	val = readl(rk_pcie->dbi_base + PCI_PRIMARY_BUS);

	/* setup command register */
	val = readl(rk_pcie->dbi_base + PCI_COMMAND);
	val &= 0xffff0000;
	val |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY |
		PCI_COMMAND_MASTER | PCI_COMMAND_SERR;
	writel(val, rk_pcie->dbi_base + PCI_COMMAND);

	/* program correct class for RC */
	writew(PCI_CLASS_BRIDGE_PCI, rk_pcie->dbi_base + PCI_CLASS_DEVICE);
	/* Better disable write permission right after the update */

	val = readl(rk_pcie->dbi_base + PCIE_LINK_WIDTH_SPEED_CONTROL);
	val |= PORT_LOGIC_SPEED_CHANGE;
	writel(val, rk_pcie->dbi_base + PCIE_LINK_WIDTH_SPEED_CONTROL);

	rk_pcie_dbi_write_enable(rk_pcie, false);
}

static void rk_pcie_configure(struct rk_pcie *pci, u32 cap_speed)
{
	u32 val;

	rk_pcie_dbi_write_enable(pci, true);

	val = readl(pci->dbi_base + PCIE_LINK_CAPABILITY);
	val &= ~TARGET_LINK_SPEED_MASK;
	val |= cap_speed;
	writel(val, pci->dbi_base + PCIE_LINK_CAPABILITY);

	val = readl(pci->dbi_base + PCIE_LINK_CTL_2);
	val &= ~TARGET_LINK_SPEED_MASK;
	val |= cap_speed;
	writel(val, pci->dbi_base + PCIE_LINK_CTL_2);

	rk_pcie_dbi_write_enable(pci, false);
}

static void rk_pcie_prog_outbound_atu_unroll(struct rk_pcie *pci, int index,
					     int type, u64 cpu_addr,
					     u64 pci_addr, u32 size)
{
	u32 retries, val;

	dev_dbg(pci->dev, "ATU programmed with: index: %d, type: %d, cpu addr: %8llx, pci addr: %8llx, size: %8x\n",
		index, type, cpu_addr, pci_addr, size);

	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_BASE,
				 lower_32_bits(cpu_addr));
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_BASE,
				 upper_32_bits(cpu_addr));
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LIMIT,
				 lower_32_bits(cpu_addr + size - 1));
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
				 lower_32_bits(pci_addr));
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
				 upper_32_bits(pci_addr));
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1,
				 type);
	rk_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
				 PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = rk_pcie_readl_ob_unroll(pci, index,
					      PCIE_ATU_UNR_REGION_CTRL2);
		if (val & PCIE_ATU_ENABLE)
			return;

		udelay(LINK_WAIT_IATU);
	}
	dev_err(pci->dev, "outbound iATU is not being enabled\n");
}

static int rk_pcie_addr_valid(pci_dev_t d, int first_busno)
{
	if ((PCI_BUS(d) == first_busno) && (PCI_DEV(d) > 0))
		return 0;
	if ((PCI_BUS(d) == first_busno + 1) && (PCI_DEV(d) > 0))
		return 0;

	return 1;
}

static uintptr_t set_cfg_address(struct rk_pcie *pcie,
				 pci_dev_t d, uint where)
{
	int bus = PCI_BUS(d) - pcie->first_busno;
	uintptr_t va_address;
	u32 atu_type;

	/* Use dbi_base for own configuration read and write */
	if (!bus) {
		va_address = (uintptr_t)pcie->dbi_base;
		goto out;
	}

	if (bus == 1)
		/*
		 * For local bus whose primary bus number is root bridge,
		 * change TLP Type field to 4.
		 */
		atu_type = PCIE_ATU_TYPE_CFG0;
	else
		/* Otherwise, change TLP Type field to 5. */
		atu_type = PCIE_ATU_TYPE_CFG1;

	/*
	 * Not accessing root port configuration space?
	 * Region #0 is used for Outbound CFG space access.
	 * Direction = Outbound
	 * Region Index = 0
	 */
	d = PCI_MASK_BUS(d);
	d = PCI_ADD_BUS(bus, d);
	rk_pcie_prog_outbound_atu_unroll(pcie, PCIE_ATU_REGION_INDEX1,
					 atu_type, (u64)pcie->cfg_base,
					 d << 8, pcie->cfg_size);

	va_address = (uintptr_t)pcie->cfg_base;

out:
	va_address += where & ~0x3;

	return va_address;
}

static int rockchip_pcie_rd_conf(struct udevice *bus, pci_dev_t bdf,
				 uint offset, ulong *valuep,
				 enum pci_size_t size)
{
	struct rk_pcie *pcie = dev_get_priv(bus);
	uintptr_t va_address;
	ulong value;

	debug("PCIE CFG read: bdf=%2x:%2x:%2x\n",
	      PCI_BUS(bdf), PCI_DEV(bdf), PCI_FUNC(bdf));

	if (!rk_pcie_addr_valid(bdf, pcie->first_busno)) {
		debug("- out of range\n");
		*valuep = pci_get_ff(size);
		return 0;
	}

	va_address = set_cfg_address(pcie, bdf, offset);

	value = readl(va_address);

	debug("(addr,val)=(0x%04x, 0x%08lx)\n", offset, value);
	*valuep = pci_conv_32_to_size(value, offset, size);

	rk_pcie_prog_outbound_atu_unroll(pcie, PCIE_ATU_REGION_INDEX1,
					 PCIE_ATU_TYPE_IO, pcie->io.phys_start,
					 pcie->io.bus_start, pcie->io.size);

	return 0;
}

static int rockchip_pcie_wr_conf(struct udevice *bus, pci_dev_t bdf,
				 uint offset, ulong value,
				 enum pci_size_t size)
{
	struct rk_pcie *pcie = dev_get_priv(bus);
	uintptr_t va_address;
	ulong old;

	debug("PCIE CFG write: (b,d,f)=(%2d,%2d,%2d)\n",
	      PCI_BUS(bdf), PCI_DEV(bdf), PCI_FUNC(bdf));
	debug("(addr,val)=(0x%04x, 0x%08lx)\n", offset, value);

	if (!rk_pcie_addr_valid(bdf, pcie->first_busno)) {
		debug("- out of range\n");
		return 0;
	}

	va_address = set_cfg_address(pcie, bdf, offset);

	old = readl(va_address);
	value = pci_conv_size_to_32(old, value, offset, size);
	writel(value, va_address);

	rk_pcie_prog_outbound_atu_unroll(pcie, PCIE_ATU_REGION_INDEX1,
					 PCIE_ATU_TYPE_IO, pcie->io.phys_start,
					 pcie->io.bus_start, pcie->io.size);

	return 0;
}

static void rk_pcie_enable_debug(struct rk_pcie *rk_pcie)
{
#if RK_PCIE_DBG
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_PTN_HIT_D0,
			   PCIE_CLIENT_DBG_TRANSITION_DATA);
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_PTN_HIT_D1,
			   PCIE_CLIENT_DBG_TRANSITION_DATA);
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_TRN_HIT_D0,
			   PCIE_CLIENT_DBG_TRANSITION_DATA);
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_TRN_HIT_D1,
			   PCIE_CLIENT_DBG_TRANSITION_DATA);
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_MODE_CON,
			   PCIE_CLIENT_DBF_EN);
#endif
}

static void rk_pcie_debug_dump(struct rk_pcie *rk_pcie)
{
#if RK_PCIE_DBG
	u32 loop;

	dev_info(rk_pcie->dev, "ltssm = 0x%x\n",
		 rk_pcie_readl_apb(rk_pcie, PCIE_CLIENT_LTSSM_STATUS));
	for (loop = 0; loop < 64; loop++)
		dev_info(rk_pcie->dev, "fifo_status = 0x%x\n",
			 rk_pcie_readl_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_STATUS));
#endif
}

static inline void rk_pcie_link_status_clear(struct rk_pcie *rk_pcie)
{
	rk_pcie_writel_apb(rk_pcie, PCIE_CLIENT_GENERAL_DEBUG, 0x0);
}

static inline void rk_pcie_disable_ltssm(struct rk_pcie *rk_pcie)
{
	rk_pcie_writel_apb(rk_pcie, 0x0, 0xc0008);
}

static inline void rk_pcie_enable_ltssm(struct rk_pcie *rk_pcie)
{
	rk_pcie_writel_apb(rk_pcie, 0x0, 0xc000c);
}

static int is_link_up(struct rk_pcie *priv)
{
	u32 val;

	val = rk_pcie_readl_apb(priv, PCIE_CLIENT_LTSSM_STATUS);
	if ((val & (RDLH_LINKUP | SMLH_LINKUP)) == 0x30000 &&
	    (val & GENMASK(5, 0)) == 0x11)
		return 1;

	return 0;
}

static int rk_pcie_link_up(struct rk_pcie *priv, u32 cap_speed)
{
	int retries;

	if (is_link_up(priv)) {
		printf("PCI Link already up before configuration!\n");
		return 1;
	}

	/* DW pre link configurations */
	rk_pcie_configure(priv, cap_speed);

	/* Rest the device */
	if (dm_gpio_is_valid(&priv->rst_gpio)) {
		dm_gpio_set_value(&priv->rst_gpio, 0);
		msleep(1000);
		dm_gpio_set_value(&priv->rst_gpio, 1);
	}

	rk_pcie_disable_ltssm(priv);
	rk_pcie_link_status_clear(priv);
	rk_pcie_enable_debug(priv);

	/* Enable LTSSM */
	rk_pcie_enable_ltssm(priv);

	for (retries = 0; retries < 50; retries++) {
		if (is_link_up(priv)) {
			dev_info(priv->dev, "PCIe Link up, LTSSM is 0x%x\n",
				 rk_pcie_readl_apb(priv, PCIE_CLIENT_LTSSM_STATUS));
			rk_pcie_debug_dump(priv);
			/* Link maybe in Gen switch recovery but we need to wait more 1s */
			msleep(1000);
			return 0;
		}

		dev_info(priv->dev, "PCIe Linking... LTSSM is 0x%x\n",
			 rk_pcie_readl_apb(priv, PCIE_CLIENT_LTSSM_STATUS));
		rk_pcie_debug_dump(priv);
		msleep(100);
	}

	dev_err(priv->dev, "PCIe-%d Link Fail\n", priv->dev->seq);
	return -EINVAL;
}

static int rockchip_pcie_init_port(struct udevice *dev)
{
	int ret;
	u32 val;
	struct rk_pcie *priv = dev_get_priv(dev);
	union phy_configure_opts phy_cfg;

	/* Set power and maybe external ref clk input */
	if (priv->vpcie3v3) {
		ret = regulator_set_enable(priv->vpcie3v3, true);
		if (ret) {
			dev_err(priv->dev, "failed to enable vpcie3v3 (ret=%d)\n",
				ret);
			return ret;
		}
	}

	msleep(1000);

	if (priv->is_bifurcation) {
		phy_cfg.pcie.is_bifurcation = true;
		ret = generic_phy_configure(&priv->phy, &phy_cfg);
		if (ret)
			dev_err(dev, "failed to set bifurcation for phy (ret=%d)\n", ret);
	}

	ret = generic_phy_init(&priv->phy);
	if (ret) {
		dev_err(dev, "failed to init phy (ret=%d)\n", ret);
		return ret;
	}

	ret = generic_phy_power_on(&priv->phy);
	if (ret) {
		dev_err(dev, "failed to power on phy (ret=%d)\n", ret);
		goto err_exit_phy;
	}

	ret = reset_deassert_bulk(&priv->rsts);
	if (ret) {
		dev_err(dev, "failed to deassert resets (ret=%d)\n", ret);
		goto err_power_off_phy;
	}

	ret = clk_enable_bulk(&priv->clks);
	if (ret) {
		dev_err(dev, "failed to enable clks (ret=%d)\n", ret);
		goto err_deassert_bulk;
	}

	/* LTSSM EN ctrl mode */
	val = rk_pcie_readl_apb(priv, PCIE_CLIENT_HOT_RESET_CTRL);
	val |= PCIE_LTSSM_ENABLE_ENHANCE | (PCIE_LTSSM_ENABLE_ENHANCE << 16);
	rk_pcie_writel_apb(priv, PCIE_CLIENT_HOT_RESET_CTRL, val);

	/* Set RC mode */
	rk_pcie_writel_apb(priv, 0x0, 0xf00040);
	rk_pcie_setup_host(priv);

	ret = rk_pcie_link_up(priv, priv->gen);
	if (ret < 0)
		goto err_link_up;

	return 0;
err_link_up:
	clk_disable_bulk(&priv->clks);
err_deassert_bulk:
	reset_assert_bulk(&priv->rsts);
err_power_off_phy:
	generic_phy_power_off(&priv->phy);
err_exit_phy:
	generic_phy_exit(&priv->phy);
	return ret;
}

static int rockchip_pcie_parse_dt(struct udevice *dev)
{
	struct rk_pcie *priv = dev_get_priv(dev);
	u32 max_link_speed;
	int ret;

	priv->dbi_base = (void *)dev_read_addr_index(dev, 0);
	if (!priv->dbi_base)
		return -ENODEV;

	dev_dbg(dev, "DBI address is 0x%p\n", priv->dbi_base);

	priv->apb_base = (void *)dev_read_addr_index(dev, 1);
	if (!priv->apb_base)
		return -ENODEV;

	dev_dbg(dev, "APB address is 0x%p\n", priv->apb_base);

	ret = gpio_request_by_name(dev, "reset-gpios", 0,
				   &priv->rst_gpio, GPIOD_IS_OUT);
	if (ret) {
		dev_err(dev, "failed to find reset-gpios property\n");
		return ret;
	}

	ret = reset_get_bulk(dev, &priv->rsts);
	if (ret) {
		dev_err(dev, "Can't get reset: %d\n", ret);
		return ret;
	}

	ret = clk_get_bulk(dev, &priv->clks);
	if (ret) {
		dev_err(dev, "Can't get clock: %d\n", ret);
		return ret;
	}

	ret = device_get_supply_regulator(dev, "vpcie3v3-supply",
					  &priv->vpcie3v3);
	if (ret && ret != -ENOENT) {
		dev_err(dev, "failed to get vpcie3v3 supply (ret=%d)\n", ret);
		return ret;
	}

	ret = generic_phy_get_by_index(dev, 0, &priv->phy);
	if (ret) {
		dev_err(dev, "failed to get pcie phy (ret=%d)\n", ret);
		return ret;
	}

	if (dev_read_bool(dev, "rockchip,bifurcation"))
		priv->is_bifurcation = true;

	ret = ofnode_read_u32(dev->node, "max-link-speed", &max_link_speed);
	if (ret < 0 || max_link_speed > 4)
		priv->gen = 0;
	else
		priv->gen = max_link_speed;

	return 0;
}

static int rockchip_pcie_probe(struct udevice *dev)
{
	struct rk_pcie *priv = dev_get_priv(dev);
	struct udevice *ctlr = pci_get_controller(dev);
	struct pci_controller *hose = dev_get_uclass_priv(ctlr);
	int ret;

	priv->first_busno = dev->seq;
	priv->dev = dev;

	ret = rockchip_pcie_parse_dt(dev);
	if (ret)
		return ret;

	ret = rockchip_pcie_init_port(dev);
	if (ret)
		return ret;

	dev_info(dev, "PCIE-%d: Link up (Gen%d-x%d, Bus%d)\n",
		 dev->seq, rk_pcie_get_link_speed(priv),
		 rk_pcie_get_link_width(priv),
		 hose->first_busno);

	for (ret = 0; ret < hose->region_count; ret++) {
		if (hose->regions[ret].flags == PCI_REGION_IO) {
			priv->io.phys_start = hose->regions[ret].phys_start; /* IO base */
			priv->io.bus_start  = hose->regions[ret].bus_start;  /* IO_bus_addr */
			priv->io.size       = hose->regions[ret].size;      /* IO size */
		} else if (hose->regions[ret].flags == PCI_REGION_MEM) {
			priv->mem.phys_start = hose->regions[ret].phys_start; /* MEM base */
			priv->mem.bus_start  = hose->regions[ret].bus_start;  /* MEM_bus_addr */
			priv->mem.size	     = hose->regions[ret].size;	    /* MEM size */
		} else if (hose->regions[ret].flags == PCI_REGION_SYS_MEMORY) {
			priv->cfg_base = (void *)(priv->io.phys_start - priv->io.size);
			priv->cfg_size = priv->io.size;
		} else {
			dev_err(dev, "invalid flags type!\n");
		}
	}

	dev_dbg(dev, "Config space: [0x%p - 0x%p, size 0x%llx]\n",
		priv->cfg_base, priv->cfg_base + priv->cfg_size,
		priv->cfg_size);

	dev_dbg(dev, "IO space: [0x%llx - 0x%llx, size 0x%x]\n",
		priv->io.phys_start, priv->io.phys_start + priv->io.size,
		priv->io.size);

	dev_dbg(dev, "IO bus:   [0x%x - 0x%x, size 0x%x]\n",
		priv->io.bus_start, priv->io.bus_start + priv->io.size,
		priv->io.size);

	dev_dbg(dev, "MEM space: [0x%llx - 0x%llx, size 0x%x]\n",
		priv->mem.phys_start, priv->mem.phys_start + priv->mem.size,
		priv->mem.size);

	dev_dbg(dev, "MEM bus:   [0x%x - 0x%x, size 0x%x]\n",
		priv->mem.bus_start, priv->mem.bus_start + priv->mem.size,
		priv->mem.size);

	rk_pcie_prog_outbound_atu_unroll(priv, PCIE_ATU_REGION_INDEX0,
					 PCIE_ATU_TYPE_MEM,
					 priv->mem.phys_start,
					 priv->mem.bus_start, priv->mem.size);
	return 0;
}

static const struct dm_pci_ops rockchip_pcie_ops = {
	.read_config	= rockchip_pcie_rd_conf,
	.write_config	= rockchip_pcie_wr_conf,
};

static const struct udevice_id rockchip_pcie_ids[] = {
	{ .compatible = "rockchip,rk3568-pcie" },
	{ .compatible = "rockchip,rk3588-pcie" },
	{ }
};

U_BOOT_DRIVER(rockchip_pcie) = {
	.name			= "pcie_dw_rockchip",
	.id			= UCLASS_PCI,
	.of_match		= rockchip_pcie_ids,
	.ops			= &rockchip_pcie_ops,
	.probe			= rockchip_pcie_probe,
	.priv_auto_alloc_size	= sizeof(struct rk_pcie),
};
