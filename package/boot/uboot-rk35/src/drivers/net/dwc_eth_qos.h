/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2020
 */

#ifndef _DWC_ETH_QOS_H
#define _DWC_ETH_QOS_H

#include <asm/gpio.h>
#include <reset.h>

#define EQOS_MAC_RXQ_CTRL0_RXQ0EN_NOT_ENABLED		0
#define EQOS_MAC_RXQ_CTRL0_RXQ0EN_ENABLED_DCB		2
#define EQOS_MAC_RXQ_CTRL0_RXQ0EN_ENABLED_AV		1

#define EQOS_MAC_MDIO_ADDRESS_CR_100_150		1
#define EQOS_MAC_MDIO_ADDRESS_CR_20_35			2
#define EQOS_MAC_MDIO_ADDRESS_CR_250_300		5

struct eqos_config {
	bool reg_access_always_ok;
	int mdio_wait;
	int swr_wait;
	int config_mac;
	int config_mac_mdio;
	struct eqos_ops *ops;
};

struct eqos_ops {
	void (*eqos_inval_desc)(void *desc);
	void (*eqos_flush_desc)(void *desc);
	void (*eqos_inval_buffer)(void *buf, size_t size);
	void (*eqos_flush_buffer)(void *buf, size_t size);
	int (*eqos_probe_resources)(struct udevice *dev);
	int (*eqos_remove_resources)(struct udevice *dev);
	int (*eqos_stop_resets)(struct udevice *dev);
	int (*eqos_start_resets)(struct udevice *dev);
	void (*eqos_stop_clks)(struct udevice *dev);
	int (*eqos_start_clks)(struct udevice *dev);
	int (*eqos_calibrate_pads)(struct udevice *dev);
	int (*eqos_disable_calibration)(struct udevice *dev);
	int (*eqos_set_tx_clk_speed)(struct udevice *dev);
	ulong (*eqos_get_tick_clk_rate)(struct udevice *dev);
	phy_interface_t (*eqos_get_interface)(struct udevice *dev);
};

struct eqos_priv {
	struct udevice *dev;
	const struct eqos_config *config;
	fdt_addr_t regs;
	struct eqos_mac_regs *mac_regs;
	struct eqos_mtl_regs *mtl_regs;
	struct eqos_dma_regs *dma_regs;
	struct eqos_tegra186_regs *tegra186_regs;
	struct reset_ctl reset_ctl;
	struct gpio_desc phy_reset_gpio;
	u32 reset_delays[3];
	struct clk clk_master_bus;
	struct clk clk_rx;
	struct clk clk_ptp_ref;
	struct clk clk_tx;
	struct clk clk_ck;
	struct clk clk_slave_bus;
	struct mii_dev *mii;
	struct phy_device *phy;
	int phyaddr;
	u32 max_speed;
	void *descs;
	struct eqos_desc *tx_descs;
	struct eqos_desc *rx_descs;
	int tx_desc_idx, rx_desc_idx;
	void *tx_dma_buf;
	void *rx_dma_buf;
	void *rx_pkt;
	bool started;
	bool reg_access_ok;
	bool mii_reseted;
};

int eqos_init(struct udevice *dev);
void eqos_enable(struct udevice *dev);
int eqos_probe(struct udevice *dev);
void eqos_stop(struct udevice *dev);
int eqos_send(struct udevice *dev, void *packet, int length);
int eqos_recv(struct udevice *dev, int flags, uchar **packetp);
int eqos_free_pkt(struct udevice *dev, uchar *packet, int length);
int eqos_write_hwaddr(struct udevice *dev);

extern struct eqos_ops eqos_rockchip_ops;

#endif
