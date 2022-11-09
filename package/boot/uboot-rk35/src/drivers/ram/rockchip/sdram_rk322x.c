/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0
 */
#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dt-structs.h>
#include <errno.h>
#include <ram.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rk322x.h>
#include <asm/arch-rockchip/grf_rk322x.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/sdram_rk322x.h>
#include <asm/arch-rockchip/uart.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/types.h>
#include <linux/err.h>

DECLARE_GLOBAL_DATA_PTR;
struct chan_info {
	struct rk322x_ddr_pctl *pctl;
	struct rk322x_ddr_phy *phy;
	struct rk322x_service_sys *msch;
};

struct dram_info {
	struct chan_info chan[1];
	struct ram_info info;
	struct clk ddr_clk;
	struct rk322x_cru *cru;
	struct rk322x_grf *grf;
};

struct rk322x_sdram_params {
#if CONFIG_IS_ENABLED(OF_PLATDATA)
		struct dtd_rockchip_rk3228_dmc of_plat;
#endif
		struct rk322x_sdram_channel ch[1];
		struct rk322x_pctl_timing pctl_timing;
		struct rk322x_phy_timing phy_timing;
		struct rk322x_base_params base;
		int num_channels;
		struct regmap *map;
};

#ifdef CONFIG_TPL_BUILD
/*
 * [7:6]  bank(n:n bit bank)
 * [5:4]  row(13+n)
 * [3]    cs(0:1 cs, 1:2 cs)
 * [2:1]  bank(n:n bit bank)
 * [0]    col(10+n)
 */
const char ddr_cfg_2_rbc[] = {
	((0 << 6) | (0 << 4) | (0 << 3) | (1 << 2) | 1),
	((0 << 6) | (1 << 4) | (0 << 3) | (1 << 2) | 1),
	((0 << 6) | (2 << 4) | (0 << 3) | (1 << 2) | 1),
	((0 << 6) | (3 << 4) | (0 << 3) | (1 << 2) | 1),
	((0 << 6) | (1 << 4) | (0 << 3) | (1 << 2) | 2),
	((0 << 6) | (2 << 4) | (0 << 3) | (1 << 2) | 2),
	((0 << 6) | (3 << 4) | (0 << 3) | (1 << 2) | 2),
	((0 << 6) | (0 << 4) | (0 << 3) | (1 << 2) | 0),
	((0 << 6) | (1 << 4) | (0 << 3) | (1 << 2) | 0),
	((0 << 6) | (2 << 4) | (0 << 3) | (1 << 2) | 0),
	((0 << 6) | (3 << 4) | (0 << 3) | (1 << 2) | 0),
	((0 << 6) | (2 << 4) | (0 << 3) | (0 << 2) | 1),
	((1 << 6) | (1 << 4) | (0 << 3) | (0 << 2) | 2),
	((1 << 6) | (1 << 4) | (0 << 3) | (0 << 2) | 1),
	((0 << 6) | (3 << 4) | (1 << 3) | (1 << 2) | 1),
	((0 << 6) | (3 << 4) | (1 << 3) | (1 << 2) | 0),
};

static void copy_to_reg(u32 *dest, const u32 *src, u32 n)
{
	int i;

	for (i = 0; i < n / sizeof(u32); i++) {
		writel(*src, dest);
		src++;
		dest++;
	}
}

void phy_pctrl_reset(struct rk322x_cru *cru,
		     struct rk322x_ddr_phy *ddr_phy)
{
	rk_clrsetreg(&cru->cru_softrst_con[5], 1 << DDRCTRL_PSRST_SHIFT |
			1 << DDRCTRL_SRST_SHIFT | 1 << DDRPHY_PSRST_SHIFT |
			1 << DDRPHY_SRST_SHIFT,
			1 << DDRCTRL_PSRST_SHIFT | 1 << DDRCTRL_SRST_SHIFT |
			1 << DDRPHY_PSRST_SHIFT | 1 << DDRPHY_SRST_SHIFT);

	udelay(10);

	rk_clrreg(&cru->cru_softrst_con[5], 1 << DDRPHY_PSRST_SHIFT |
						  1 << DDRPHY_SRST_SHIFT);
	udelay(10);

	rk_clrreg(&cru->cru_softrst_con[5], 1 << DDRCTRL_PSRST_SHIFT |
						  1 << DDRCTRL_SRST_SHIFT);
	udelay(10);

	clrbits_le32(&ddr_phy->ddrphy_reg[0],
		     SOFT_RESET_MASK << SOFT_RESET_SHIFT);
	udelay(10);
	setbits_le32(&ddr_phy->ddrphy_reg[0],
		     SOFT_DERESET_ANALOG);
	udelay(5);
	setbits_le32(&ddr_phy->ddrphy_reg[0],
		     SOFT_DERESET_DIGITAL);

	udelay(1);
}

void phy_dll_bypass_set(struct rk322x_ddr_phy *ddr_phy, u32 freq)
{
	u32 tmp;

	setbits_le32(&ddr_phy->ddrphy_reg[0x13], 0x10);
	setbits_le32(&ddr_phy->ddrphy_reg[0x26], 0x10);
	setbits_le32(&ddr_phy->ddrphy_reg[0x36], 0x10);
	setbits_le32(&ddr_phy->ddrphy_reg[0x46], 0x10);
	setbits_le32(&ddr_phy->ddrphy_reg[0x56], 0x10);

	clrbits_le32(&ddr_phy->ddrphy_reg[0x14], 0x8);
	clrbits_le32(&ddr_phy->ddrphy_reg[0x27], 0x8);
	clrbits_le32(&ddr_phy->ddrphy_reg[0x37], 0x8);
	clrbits_le32(&ddr_phy->ddrphy_reg[0x47], 0x8);
	clrbits_le32(&ddr_phy->ddrphy_reg[0x57], 0x8);

	if (freq <= 400)
		setbits_le32(&ddr_phy->ddrphy_reg[0xa4], 0x1f);
	else
		clrbits_le32(&ddr_phy->ddrphy_reg[0xa4], 0x1f);

	if (freq <= 680)
		tmp = 3;
	else
		tmp = 2;

	writel(tmp, &ddr_phy->ddrphy_reg[0x28]);
	writel(tmp, &ddr_phy->ddrphy_reg[0x38]);
	writel(tmp, &ddr_phy->ddrphy_reg[0x48]);
	writel(tmp, &ddr_phy->ddrphy_reg[0x58]);
}

static void send_command(struct rk322x_ddr_pctl *pctl,
			 u32 rank, u32 cmd, u32 arg)
{
	writel((START_CMD | (rank << 20) | arg | cmd), &pctl->mcmd);
	udelay(1);
	while (readl(&pctl->mcmd) & START_CMD)
		;
}

static void memory_init(struct chan_info *chan,
			struct rk322x_sdram_params *sdram_params)
{
	struct rk322x_ddr_pctl *pctl = chan->pctl;
	u32 dramtype = sdram_params->base.dramtype;

	if (dramtype == DDR3) {
		send_command(pctl, 3, DESELECT_CMD, 0);
		udelay(1);
		send_command(pctl, 3, PREA_CMD, 0);
		send_command(pctl, 3, MRS_CMD,
			     (0x02 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (sdram_params->phy_timing.mr[2] & CMD_ADDR_MASK) <<
			     CMD_ADDR_SHIFT);

		send_command(pctl, 3, MRS_CMD,
			     (0x03 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (sdram_params->phy_timing.mr[3] & CMD_ADDR_MASK) <<
			     CMD_ADDR_SHIFT);

		send_command(pctl, 3, MRS_CMD,
			     (0x01 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (sdram_params->phy_timing.mr[1] & CMD_ADDR_MASK) <<
			     CMD_ADDR_SHIFT);

		send_command(pctl, 3, MRS_CMD,
			     (0x00 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     ((sdram_params->phy_timing.mr[0] |
			       DDR3_DLL_RESET) &
			     CMD_ADDR_MASK) << CMD_ADDR_SHIFT);

		send_command(pctl, 3, ZQCL_CMD, 0);
	} else {
		send_command(pctl, 3, MRS_CMD,
			     (0x63 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0 & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		udelay(10);
		send_command(pctl, 3, MRS_CMD,
			     (0x10 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0xff & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		udelay(1);
		send_command(pctl, 3, MRS_CMD,
			     (0x10 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0xff & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		udelay(1);
		send_command(pctl, 3, MRS_CMD,
			     (1 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (sdram_params->phy_timing.mr[1] &
			      LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
		send_command(pctl, 3, MRS_CMD,
			     (2 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (sdram_params->phy_timing.mr[2] &
			      LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
		send_command(pctl, 3, MRS_CMD,
			     (3 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (sdram_params->phy_timing.mr[3] &
			      LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
		if (dramtype == LPDDR3)
			send_command(pctl, 3, MRS_CMD, (11 & LPDDR23_MA_MASK) <<
				     LPDDR23_MA_SHIFT |
				     (sdram_params->phy_timing.mr11 &
				      LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
	}
}

static u32 data_training(struct chan_info *chan)
{
	struct rk322x_ddr_phy *ddr_phy = chan->phy;
	struct rk322x_ddr_pctl *pctl = chan->pctl;
	u32 value;
	u32 bw = (readl(&ddr_phy->ddrphy_reg[0]) >> 4) & 0xf;
	u32 ret;

	/* disable auto refresh */
	value = readl(&pctl->trefi) | (1 << 31);
	writel(1 << 31, &pctl->trefi);

	clrsetbits_le32(&ddr_phy->ddrphy_reg[2], 0x30,
			DQS_SQU_CAL_SEL_CS0);
	setbits_le32(&ddr_phy->ddrphy_reg[2], DQS_SQU_CAL_START);

	udelay(30);
	ret = readl(&ddr_phy->ddrphy_reg[0xff]);

	clrbits_le32(&ddr_phy->ddrphy_reg[2],
		     DQS_SQU_CAL_START);

	/*
	 * since data training will take about 20us, so send some auto
	 * refresh(about 7.8us) to complement the lost time
	 */
	send_command(pctl, 3, PREA_CMD, 0);
	send_command(pctl, 3, REF_CMD, 0);

	writel(value, &pctl->trefi);

	if (ret & 0x10) {
		ret = -1;
	} else {
		ret = (ret & 0xf) ^ bw;
		ret = (ret == 0) ? 0 : -1;
	}
	return ret;
}

static void move_to_config_state(struct rk322x_ddr_pctl *pctl)
{
	unsigned int state;

	while (1) {
		state = readl(&pctl->stat) & PCTL_STAT_MASK;
		switch (state) {
		case LOW_POWER:
			writel(WAKEUP_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK)
				!= ACCESS)
				;
			/*
			 * If at low power state, need wakeup first, and then
			 * enter the config, so fallthrough
			 */
		case ACCESS:
			/* fallthrough */
		case INIT_MEM:
			writel(CFG_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != CONFIG)
				;
			break;
		case CONFIG:
			return;
		default:
			break;
		}
	}
}

static void move_to_access_state(struct rk322x_ddr_pctl *pctl)
{
	unsigned int state;

	while (1) {
		state = readl(&pctl->stat) & PCTL_STAT_MASK;
		switch (state) {
		case LOW_POWER:
			writel(WAKEUP_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != ACCESS)
				;
			break;
		case INIT_MEM:
			writel(CFG_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != CONFIG)
				;
			/* fallthrough */
		case CONFIG:
			writel(GO_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != ACCESS)
				;
			break;
		case ACCESS:
			return;
		default:
			break;
		}
	}
}

static void move_to_lowpower_state(struct rk322x_ddr_pctl *pctl)
{
	unsigned int state;

	while (1) {
		state = readl(&pctl->stat) & PCTL_STAT_MASK;
		switch (state) {
		case INIT_MEM:
			writel(CFG_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != CONFIG)
				;
			/* fallthrough */
		case CONFIG:
			writel(GO_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) != ACCESS)
				;
			break;
		case ACCESS:
			writel(SLEEP_STATE, &pctl->sctl);
			while ((readl(&pctl->stat) & PCTL_STAT_MASK) !=
			       LOW_POWER)
				;
			break;
		case LOW_POWER:
			return;
		default:
			break;
		}
	}
}

/* pctl should in low power mode when call this function */
static void phy_softreset(struct dram_info *dram)
{
	struct rk322x_ddr_phy *ddr_phy = dram->chan[0].phy;
	struct rk322x_grf *grf = dram->grf;

	writel(GRF_DDRPHY_BUFFEREN_CORE_EN, &grf->soc_con[0]);
	clrbits_le32(&ddr_phy->ddrphy_reg[0], 0x3 << 2);
	udelay(1);
	setbits_le32(&ddr_phy->ddrphy_reg[0], 1 << 2);
	udelay(5);
	setbits_le32(&ddr_phy->ddrphy_reg[0], 1 << 3);
	writel(GRF_DDRPHY_BUFFEREN_CORE_DIS, &grf->soc_con[0]);
}

/* bw: 2: 32bit, 1:16bit */
static void set_bw(struct dram_info *dram, u32 bw)
{
	struct rk322x_ddr_pctl *pctl = dram->chan[0].pctl;
	struct rk322x_ddr_phy *ddr_phy = dram->chan[0].phy;
	struct rk322x_grf *grf = dram->grf;

	if (bw == 1) {
		setbits_le32(&pctl->ppcfg, 1);
		clrbits_le32(&ddr_phy->ddrphy_reg[0], 0xc << 4);
		writel(GRF_MSCH_NOC_16BIT_EN, &grf->soc_con[0]);
		clrbits_le32(&ddr_phy->ddrphy_reg[0x46], 0x8);
		clrbits_le32(&ddr_phy->ddrphy_reg[0x56], 0x8);
	} else {
		clrbits_le32(&pctl->ppcfg, 1);
		setbits_le32(&ddr_phy->ddrphy_reg[0], 0xf << 4);
		writel(GRF_DDR_32BIT_EN | GRF_MSCH_NOC_32BIT_EN,
		       &grf->soc_con[0]);
		setbits_le32(&ddr_phy->ddrphy_reg[0x46], 0x8);
		setbits_le32(&ddr_phy->ddrphy_reg[0x56], 0x8);
	}
}

static void pctl_cfg(struct rk322x_ddr_pctl *pctl,
		     struct rk322x_sdram_params *sdram_params,
		     struct rk322x_grf *grf)
{
	u32 burst_len;
	u32 bw;
	u32 dramtype = sdram_params->base.dramtype;

	if (sdram_params->ch[0].bw == 2)
		bw = GRF_DDR_32BIT_EN | GRF_MSCH_NOC_32BIT_EN;
	else
		bw = GRF_MSCH_NOC_16BIT_EN;

	writel(DFI_INIT_START | DFI_DATA_BYTE_DISABLE_EN, &pctl->dfistcfg0);
	writel(DFI_DRAM_CLK_SR_EN | DFI_DRAM_CLK_DPD_EN, &pctl->dfistcfg1);
	writel(DFI_PARITY_INTR_EN | DFI_PARITY_EN, &pctl->dfistcfg2);
	writel(0x51010, &pctl->dfilpcfg0);

	writel(1, &pctl->dfitphyupdtype0);
	writel(0x0d, &pctl->dfitphyrdlat);
	writel(0, &pctl->dfitphywrdata);

	writel(0, &pctl->dfiupdcfg);
	copy_to_reg(&pctl->togcnt1u, &sdram_params->pctl_timing.togcnt1u,
		    sizeof(struct rk322x_pctl_timing));
	if (dramtype == DDR3) {
		writel((1 << 3) | (1 << 11),
		       &pctl->dfiodtcfg);
		writel(7 << 16, &pctl->dfiodtcfg1);
		writel((readl(&pctl->tcl) - 1) / 2 - 1, &pctl->dfitrddataen);
		writel((readl(&pctl->tcwl) - 1) / 2 - 1, &pctl->dfitphywrlat);
		writel(500, &pctl->trsth);
		writel(0 << MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT | DDR3_EN |
		       DDR2_DDR3_BL_8 | (6 - 4) << TFAW_SHIFT | PD_EXIT_SLOW |
		       1 << PD_TYPE_SHIFT | 0 << PD_IDLE_SHIFT,
		       &pctl->mcfg);
		writel(bw | GRF_DDR3_EN, &grf->soc_con[0]);
	} else {
		if (sdram_params->phy_timing.bl & PHT_BL_8)
			burst_len = MDDR_LPDDR2_BL_8;
		else
			burst_len = MDDR_LPDDR2_BL_4;

		writel(readl(&pctl->tcl) / 2 - 1, &pctl->dfitrddataen);
		writel(readl(&pctl->tcwl) / 2 - 1, &pctl->dfitphywrlat);
		writel(0, &pctl->trsth);
		if (dramtype == LPDDR2) {
			writel(0 << MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT |
			       LPDDR2_S4 | LPDDR2_EN | burst_len |
			       (6 - 4) << TFAW_SHIFT | PD_EXIT_FAST |
			       1 << PD_TYPE_SHIFT | 0 << PD_IDLE_SHIFT,
			       &pctl->mcfg);
			writel(0, &pctl->dfiodtcfg);
			writel(0, &pctl->dfiodtcfg1);
		} else {
			writel(0 << MDDR_LPDDR2_CLK_STOP_IDLE_SHIFT |
			       LPDDR2_S4 | LPDDR3_EN | burst_len |
			       (6 - 4) << TFAW_SHIFT | PD_EXIT_FAST |
			       1 << PD_TYPE_SHIFT | 0 << PD_IDLE_SHIFT,
			       &pctl->mcfg);
			writel((1 << 3) | (1 << 2), &pctl->dfiodtcfg);
			writel((7 << 16) | 4, &pctl->dfiodtcfg1);
		}
		writel(bw | GRF_LPDDR2_3_EN, &grf->soc_con[0]);
	}
	setbits_le32(&pctl->scfg, 1);
}

static void phy_cfg(struct chan_info *chan,
		    struct rk322x_sdram_params *sdram_params)
{
	struct rk322x_ddr_phy *ddr_phy = chan->phy;
	struct rk322x_service_sys *axi_bus = chan->msch;
	struct rk322x_msch_timings *noc_timing = &sdram_params->base.noc_timing;
	struct rk322x_phy_timing *phy_timing = &sdram_params->phy_timing;
	struct rk322x_pctl_timing *pctl_timing = &sdram_params->pctl_timing;
	u32 cmd_drv, clk_drv, dqs_drv, dqs_odt;

	writel(noc_timing->ddrtiming, &axi_bus->ddrtiming);
	writel(noc_timing->ddrmode, &axi_bus->ddrmode);
	writel(noc_timing->readlatency, &axi_bus->readlatency);
	writel(noc_timing->activate, &axi_bus->activate);
	writel(noc_timing->devtodev, &axi_bus->devtodev);

	switch (sdram_params->base.dramtype) {
	case DDR3:
		writel(PHY_DDR3 | phy_timing->bl, &ddr_phy->ddrphy_reg[1]);
		break;
	case LPDDR2:
		writel(PHY_LPDDR2 | phy_timing->bl, &ddr_phy->ddrphy_reg[1]);
		break;
	default:
		writel(PHY_LPDDR2 | phy_timing->bl, &ddr_phy->ddrphy_reg[1]);
		break;
	}

	writel(phy_timing->cl_al, &ddr_phy->ddrphy_reg[0xb]);
	writel(pctl_timing->tcwl, &ddr_phy->ddrphy_reg[0xc]);

	cmd_drv = PHY_RON_RTT_34OHM;
	clk_drv = PHY_RON_RTT_45OHM;
	dqs_drv = PHY_RON_RTT_34OHM;
	if (sdram_params->base.dramtype == LPDDR2)
		dqs_odt = PHY_RON_RTT_DISABLE;
	else
		dqs_odt = PHY_RON_RTT_225OHM;

	writel(cmd_drv, &ddr_phy->ddrphy_reg[0x11]);
	clrsetbits_le32(&ddr_phy->ddrphy_reg[0x12], (0x1f << 3), cmd_drv << 3);
	writel(clk_drv, &ddr_phy->ddrphy_reg[0x16]);
	writel(clk_drv, &ddr_phy->ddrphy_reg[0x18]);

	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x20]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x2f]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x30]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x3f]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x40]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x4f]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x50]);
	writel(dqs_drv, &ddr_phy->ddrphy_reg[0x5f]);

	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x21]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x2e]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x31]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x3e]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x41]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x4e]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x51]);
	writel(dqs_odt, &ddr_phy->ddrphy_reg[0x5e]);
}

void dram_cfg_rbc(struct chan_info *chan,
		  struct rk322x_sdram_params *sdram_params)
{
	char noc_config;
	int i = 0;
	struct rk322x_sdram_channel *config = &sdram_params->ch[0];
	struct rk322x_service_sys *axi_bus = chan->msch;

	move_to_config_state(chan->pctl);

	if ((config->rank == 2) && (config->cs1_row == config->cs0_row)) {
		if ((config->col + config->bw) == 12) {
			i = 14;
			goto finish;
		} else if ((config->col + config->bw) == 11) {
			i = 15;
			goto finish;
		}
	}
	noc_config = ((config->cs0_row - 13) << 4) | ((config->bk - 2) << 2) |
				(config->col + config->bw - 11);
	for (i = 0; i < 11; i++) {
		if (noc_config == ddr_cfg_2_rbc[i])
			break;
	}

	if (i < 11)
		goto finish;

	noc_config = ((config->bk - 2) << 6) | ((config->cs0_row - 13) << 4) |
				(config->col + config->bw - 11);

	for (i = 11; i < 14; i++) {
		if (noc_config == ddr_cfg_2_rbc[i])
			break;
	}
	if (i < 14)
		goto finish;
	else
		i = 0;

finish:
	writel(i, &axi_bus->ddrconf);
	move_to_access_state(chan->pctl);
}

static void dram_all_config(const struct dram_info *dram,
			    struct rk322x_sdram_params *sdram_params)
{
	struct rk322x_sdram_channel *info = &sdram_params->ch[0];
	u32 sys_reg = 0;

	sys_reg |= sdram_params->base.dramtype << SYS_REG_DDRTYPE_SHIFT;
	sys_reg |= (1 - 1) << SYS_REG_NUM_CH_SHIFT;
	sys_reg |= info->row_3_4 << SYS_REG_ROW_3_4_SHIFT(0);
	sys_reg |= 1 << SYS_REG_CHINFO_SHIFT(0);
	sys_reg |= (info->rank - 1) << SYS_REG_RANK_SHIFT(0);
	sys_reg |= (info->col - 9) << SYS_REG_COL_SHIFT(0);
	sys_reg |= info->bk == 3 ? 0 : 1 << SYS_REG_BK_SHIFT(0);
	sys_reg |= (info->cs0_row - 13) << SYS_REG_CS0_ROW_SHIFT(0);
	sys_reg |= (info->cs1_row - 13) << SYS_REG_CS1_ROW_SHIFT(0);
	sys_reg |= (2 >> info->bw) << SYS_REG_BW_SHIFT(0);
	sys_reg |= (2 >> info->dbw) << SYS_REG_DBW_SHIFT(0);

	writel(sys_reg, &dram->grf->os_reg[2]);
}

#define TEST_PATTEN	0x5aa5f00f

static int dram_cap_detect(struct dram_info *dram,
			   struct rk322x_sdram_params *sdram_params)
{
	u32 bw, row, col, addr;
	u32 ret = 0;
	struct rk322x_service_sys *axi_bus = dram->chan[0].msch;

	if (sdram_params->base.dramtype == DDR3)
		sdram_params->ch[0].dbw = 1;
	else
		sdram_params->ch[0].dbw = 2;

	move_to_config_state(dram->chan[0].pctl);
	/* bw detect */
	set_bw(dram, 2);
	if (data_training(&dram->chan[0]) == 0) {
		bw = 2;
	} else {
		bw = 1;
		set_bw(dram, 1);
		move_to_lowpower_state(dram->chan[0].pctl);
		phy_softreset(dram);
		move_to_config_state(dram->chan[0].pctl);
		if (data_training(&dram->chan[0])) {
			printf("BW detect error\n");
			ret = -EINVAL;
		}
	}
	sdram_params->ch[0].bw = bw;
	sdram_params->ch[0].bk = 3;

	if (bw == 2)
		writel(6, &axi_bus->ddrconf);
	else
		writel(3, &axi_bus->ddrconf);
	move_to_access_state(dram->chan[0].pctl);
	for (col = 11; col >= 9; col--) {
		writel(0, CONFIG_SYS_SDRAM_BASE);
		addr = CONFIG_SYS_SDRAM_BASE +
			(1 << (col + bw - 1));
		writel(TEST_PATTEN, addr);
		if ((readl(addr) == TEST_PATTEN) &&
		    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
			break;
	}
	if (col == 8) {
		printf("Col detect error\n");
		ret = -EINVAL;
		goto out;
	} else {
		sdram_params->ch[0].col = col;
	}

	writel(10, &axi_bus->ddrconf);

	/* Detect row*/
	for (row = 16; row >= 12; row--) {
		writel(0, CONFIG_SYS_SDRAM_BASE);
		addr = CONFIG_SYS_SDRAM_BASE + (1u << (row + 11 + 3 - 1));
		writel(TEST_PATTEN, addr);
		if ((readl(addr) == TEST_PATTEN) &&
		    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
			break;
	}
	if (row == 11) {
		printf("Row detect error\n");
		ret = -EINVAL;
	} else {
		sdram_params->ch[0].cs1_row = row;
		sdram_params->ch[0].row_3_4 = 0;
		sdram_params->ch[0].cs0_row = row;
	}
	/* cs detect */
	writel(0, CONFIG_SYS_SDRAM_BASE);
	writel(TEST_PATTEN, CONFIG_SYS_SDRAM_BASE + (1u << 30));
	writel(~TEST_PATTEN, CONFIG_SYS_SDRAM_BASE + (1u << 30) + 4);
	if ((readl(CONFIG_SYS_SDRAM_BASE + (1u << 30)) == TEST_PATTEN) &&
	    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
		sdram_params->ch[0].rank = 2;
	else
		sdram_params->ch[0].rank = 1;
out:
	return ret;
}

static int sdram_init(struct dram_info *dram,
		      struct rk322x_sdram_params *sdram_params)
{
	int ret;

	ret = clk_set_rate(&dram->ddr_clk,
			   sdram_params->base.ddr_freq * MHz * 2);
	if (ret < 0) {
		printf("Could not set DDR clock\n");
		return ret;
	}

	phy_pctrl_reset(dram->cru, dram->chan[0].phy);
	phy_dll_bypass_set(dram->chan[0].phy, sdram_params->base.ddr_freq);
	pctl_cfg(dram->chan[0].pctl, sdram_params, dram->grf);
	phy_cfg(&dram->chan[0], sdram_params);
	writel(POWER_UP_START, &dram->chan[0].pctl->powctl);
	while (!(readl(&dram->chan[0].pctl->powstat) & POWER_UP_DONE))
		;
	memory_init(&dram->chan[0], sdram_params);
	move_to_access_state(dram->chan[0].pctl);
	ret = dram_cap_detect(dram, sdram_params);
	if (ret)
		goto out;
	dram_cfg_rbc(&dram->chan[0], sdram_params);
	dram_all_config(dram, sdram_params);
out:
	return ret;
}

static int rk322x_dmc_ofdata_to_platdata(struct udevice *dev)
{
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	struct rk322x_sdram_params *params = dev_get_platdata(dev);
	int ret;

	params->num_channels = 1;

	ret = dev_read_u32_array(dev, "rockchip,pctl-timing",
				   (u32 *)&params->pctl_timing,
				   sizeof(params->pctl_timing) / sizeof(u32));
	if (ret) {
		printf("%s: Cannot read rockchip,pctl-timing\n", __func__);
		return -EINVAL;
	}
	ret = dev_read_u32_array(dev, "rockchip,phy-timing",
				   (u32 *)&params->phy_timing,
				   sizeof(params->phy_timing) / sizeof(u32));
	if (ret) {
		printf("%s: Cannot read rockchip,phy-timing\n", __func__);
		return -EINVAL;
	}
	ret = dev_read_u32_array(dev, "rockchip,sdram-params",
				   (u32 *)&params->base,
				   sizeof(params->base) / sizeof(u32));
	if (ret) {
		printf("%s: Cannot read rockchip,sdram-params\n", __func__);
		return -EINVAL;
	}
	ret = regmap_init_mem(dev, &params->map);
	if (ret)
		return ret;
#endif

	return 0;
}
#endif /* CONFIG_TPL_BUILD */

#if CONFIG_IS_ENABLED(OF_PLATDATA)
static int conv_of_platdata(struct udevice *dev)
{
	struct rk322x_sdram_params *plat = dev_get_platdata(dev);
	struct dtd_rockchip_rk322x_dmc *of_plat = &plat->of_plat;
	int ret;

	memcpy(&plat->pctl_timing, of_plat->rockchip_pctl_timing,
	       sizeof(plat->pctl_timing));
	memcpy(&plat->phy_timing, of_plat->rockchip_phy_timing,
	       sizeof(plat->phy_timing));
	memcpy(&plat->base, of_plat->rockchip_sdram_params, sizeof(plat->base));

	plat->num_channels = 1;
	ret = regmap_init_mem_platdata(dev, of_plat->reg,
				       ARRAY_SIZE(of_plat->reg) / 2,
				       &plat->map);
	if (ret)
		return ret;

	return 0;
}
#endif

static int rk322x_dmc_probe(struct udevice *dev)
{
#ifdef CONFIG_TPL_BUILD
	struct rk322x_sdram_params *plat = dev_get_platdata(dev);
	int ret;
	struct udevice *dev_clk;
#endif
	struct dram_info *priv = dev_get_priv(dev);

	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
#ifdef CONFIG_TPL_BUILD
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	ret = conv_of_platdata(dev);
	if (ret)
		return ret;
#endif

	priv->chan[0].msch = syscon_get_first_range(ROCKCHIP_SYSCON_MSCH);
	priv->chan[0].pctl = regmap_get_range(plat->map, 0);
	priv->chan[0].phy = regmap_get_range(plat->map, 1);
	ret = rockchip_get_clk(&dev_clk);
	if (ret)
		return ret;
	priv->ddr_clk.id = CLK_DDR;
	ret = clk_request(dev_clk, &priv->ddr_clk);
	if (ret)
		return ret;

	priv->cru = rockchip_get_cru();
	if (IS_ERR(priv->cru))
		return PTR_ERR(priv->cru);
	ret = sdram_init(priv, plat);
	if (ret)
		return ret;
#else
	priv->info.base = CONFIG_SYS_SDRAM_BASE;
	priv->info.size = rockchip_sdram_size(
			(phys_addr_t)&priv->grf->os_reg[2]);
#endif

	return 0;
}

static int rk322x_dmc_get_info(struct udevice *dev, struct ram_info *info)
{
	struct dram_info *priv = dev_get_priv(dev);

	*info = priv->info;

	return 0;
}

static struct ram_ops rk322x_dmc_ops = {
	.get_info = rk322x_dmc_get_info,
};

static const struct udevice_id rk322x_dmc_ids[] = {
	{ .compatible = "rockchip,rk3228-dmc" },
	{ }
};

U_BOOT_DRIVER(dmc_rk322x) = {
	.name = "rockchip_rk322x_dmc",
	.id = UCLASS_RAM,
	.of_match = rk322x_dmc_ids,
	.ops = &rk322x_dmc_ops,
#ifdef CONFIG_TPL_BUILD
	.ofdata_to_platdata = rk322x_dmc_ofdata_to_platdata,
#endif
	.probe = rk322x_dmc_probe,
	.priv_auto_alloc_size = sizeof(struct dram_info),
#ifdef CONFIG_TPL_BUILD
	.platdata_auto_alloc_size = sizeof(struct rk322x_sdram_params),
#endif
};

