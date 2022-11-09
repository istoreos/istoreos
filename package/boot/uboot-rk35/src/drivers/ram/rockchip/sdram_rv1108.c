// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <dm/root.h>
#include <dt-structs.h>
#include <regmap.h>
#include <asm/io.h>
#include <asm/types.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/sdram_rv1108.h>
#include <asm/arch-rockchip/timer.h>
#include <asm/arch-rockchip/sdram.h>

struct dram_info info;

struct rockchip_dmc_plat {
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	struct dtd_rockchip_rv1108_dmc dtplat;
#else
	struct sdram_params params;
#endif
	struct regmap *map;
};

void enable_ddr_io_ret(struct dram_info *priv)
{
	writel(DDR_IO_RET_EN, &priv->pmu->sft_con);
	rk_clrsetreg(&priv->pmu_grf->soc_con[0],
		     DDRPHY_BUFFEREN_CORE_MASK,
		     DDRPHY_BUFFEREN_CORE_EN);
}

void rkdclk_init(struct dram_info *priv,
		 struct sdram_params *params_priv)
{
	rk_clrsetreg(&priv->cru->pll[1].con3, WORK_MODE_MASK,
		     WORK_MODE_SLOW << WORK_MODE_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con3, GLOBAL_POWER_DOWN_MASK,
		     GLOBAL_POWER_DOWN << GLOBAL_POWER_DOWN_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con3, DSMPD_MASK,
		     INTEGER_MODE << DSMPD_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con0, FBDIV_MASK,
		     params_priv->dpll_init_cfg.fbdiv << FBDIV_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con1,
		     POSTDIV2_MASK | POSTDIV1_MASK | REFDIV_MASK,
		     params_priv->dpll_init_cfg.postdiv2 << POSTDIV2_SHIFT |
		     params_priv->dpll_init_cfg.postdiv1 << POSTDIV1_SHIFT |
		     params_priv->dpll_init_cfg.refdiv << REFDIV_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con3, GLOBAL_POWER_DOWN_MASK,
		     GLOBAL_POWER_UP << GLOBAL_POWER_DOWN_SHIFT);
	while (!(readl(&priv->cru->pll[1].con2) & (1u << LOCK_STA_SHIFT)))
		udelay(1);

	rk_clrsetreg(&priv->cru->clksel_con[4], CLK_DDR_PLL_SEL_MASK |
		     CLK_DDR_DIV_CON_MASK, 0 << CLK_DDR_PLL_SEL_SHIFT |
		     0 << CLK_DDR_DIV_CON_SHIFT);
	rk_clrsetreg(&priv->cru->pll[1].con3, WORK_MODE_MASK,
		     WORK_MODE_NORMAL << WORK_MODE_SHIFT);
}

void phy_pctrl_reset_cru(struct dram_info *priv)
{
	rk_clrsetreg(&priv->cru->softrst_con[2], DDRUPCTL_PSRSTN_REQ_MASK |
		     DDRUPCTL_NSRSTN_REQ_MASK,
		     DDRUPCTL_PSRSTN_REQ << DDRUPCTL_PSRSTN_REQ_SHIFT |
		     DDRUPCTL_NSRSTN_REQ << DDRUPCTL_NSRSTN_REQ_SHIFT);
	rk_clrsetreg(&priv->cru->softrst_con[1],
		     DDRPHY_SRSTN_CLKDIV_REQ_MASK | DDRPHY_SRSTN_REQ_MASK |
		     DDRPHY_PSRSTN_REQ_MASK,
		     DDRPHY_SRSTN_CLKDIV_REQ << DDRPHY_SRSTN_CLKDIV_REQ_SHIFT |
		     DDRPHY_SRSTN_REQ << DDRPHY_SRSTN_REQ_SHIFT |
		     DDRPHY_PSRSTN_REQ << DDRPHY_PSRSTN_REQ_SHIFT);

	udelay(10);

	rk_clrsetreg(&priv->cru->softrst_con[1],
		     DDRPHY_SRSTN_CLKDIV_REQ_MASK | DDRPHY_SRSTN_REQ_MASK |
		     DDRPHY_PSRSTN_REQ_MASK,
		     DDRPHY_SRSTN_CLKDIV_DIS << DDRPHY_SRSTN_CLKDIV_REQ_SHIFT |
		     DDRPHY_PSRSTN_DIS << DDRPHY_PSRSTN_REQ_SHIFT |
		     DDRPHY_SRSTN_DIS << DDRPHY_SRSTN_REQ_SHIFT);
	udelay(10);

	rk_clrsetreg(&priv->cru->softrst_con[2], DDRUPCTL_PSRSTN_REQ_MASK |
		     DDRUPCTL_NSRSTN_REQ_MASK,
		     DDRUPCTL_PSRSTN_DIS << DDRUPCTL_PSRSTN_REQ_SHIFT |
		     DDRUPCTL_NSRSTN_DIS << DDRUPCTL_NSRSTN_REQ_SHIFT);
	udelay(10);
}

void pctl_cfg_grf(struct dram_info *priv,
		  struct sdram_params *params_priv)
{
	writel(RK_SETBITS(MSCH_MAINDDR3 | MSCH_MAINPARTIALPOP),
	       &priv->grf->soc_con0);
}

void ddr_msch_cfg(struct dram_info *priv,
		  struct sdram_params *params_priv)
{
	writel((readl(&priv->service_msch->ddrtiming) & BWRATIO_HALF_BW) |
	       params_priv->ddr_timing_t.noc_timing.d32,
	       &priv->service_msch->ddrtiming);
	writel(params_priv->ddr_timing_t.readlatency,
	       &priv->service_msch->readlatency);
	writel(params_priv->ddr_timing_t.activate.d32,
	       &priv->service_msch->activate);
	writel(params_priv->ddr_timing_t.devtodev,
	       &priv->service_msch->devtodev);
}

void ddr_msch_cfg_rbc(struct sdram_params *params_priv,
		      struct dram_info *priv)
{
	int i = 0;

	if (params_priv->ddr_config_t.col == 10)
		i = 2;
	else
		i = 3;
	writel(i, &priv->service_msch->ddrconf);
}

void ddr_phy_skew_cfg(struct dram_info *priv)
{
}

void set_ds_odt(struct dram_info *priv,
		struct sdram_params *params_priv)
{
	/* set phy drive impedance */
	writel(PHY_RON_RTT_34OHM, &priv->phy->phy_reg11);
	clrsetbits_le32(&priv->phy->phy_reg12, CMD_PRCOMP_MASK,
			PHY_RON_RTT_34OHM << CMD_PRCOMP_SHIFT);

	writel(PHY_RON_RTT_45OHM, &priv->phy->phy_reg16);
	writel(PHY_RON_RTT_45OHM, &priv->phy->phy_reg18);
	writel(PHY_RON_RTT_34OHM, &priv->phy->phy_reg20);
	writel(PHY_RON_RTT_34OHM, &priv->phy->phy_reg2f);
	writel(PHY_RON_RTT_34OHM, &priv->phy->phy_reg30);
	writel(PHY_RON_RTT_34OHM, &priv->phy->phy_reg3f);

	/*set phy odt*/
	writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg21);
	writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg2e);
	writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg31);
	writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg3e);
}

void ddr_phy_dqs_rx_dll_cfg(struct dram_info *priv, u32 freq)
{
	/* 45 degree delay */
	writel(LEFT_CHN_A_READ_DQS_45_DELAY, &priv->phy->phy_reg28);
	writel(RIGHT_CHN_A_READ_DQS_45_DELAY, &priv->phy->phy_reg38);
}

void ddr_msch_get_max_col(struct dram_info *priv,
			  struct ddr_schedule *sch_priv)
{
	writel(1, &priv->service_msch->ddrconf);
	sch_priv->col = 11;
	sch_priv->bank = 3;
}

void ddr_msch_get_max_row(struct dram_info *priv,
			  struct ddr_schedule *sch_priv)
{
	writel(1, &priv->service_msch->ddrconf);
	sch_priv->row = 16;
	sch_priv->col = 11;
	sch_priv->bank = 3;
}

void *get_base_addr(unsigned int *reg, unsigned int offset)
{
	u32 p = *(reg + 2 * offset);

	return (void *)p;
}

void modify_data_training(struct dram_info *priv,
			  struct sdram_params *params_priv)
{
	printascii("REGFB: 0x");
	printhex8(readl(&priv->phy->phy_regfb));
	printascii(", 0x");
	printhex8(readl(&priv->phy->phy_regfc));
	printascii("\n");
}

int check_rd_gate(struct dram_info *priv)
{
	return 0;
}

void enable_low_power(struct dram_info *priv,
		      struct sdram_params *params_priv)
{
	move_to_config_state(priv);

	clrsetbits_le32(&priv->pctl->mcfg, PD_IDLE_MASK,
			PD_IDLE << PD_IDLE_SHIFT);
	clrsetbits_le32(&priv->pctl->mcfg1,
			SR_IDLE_MASK | HW_EXIT_IDLE_EN_MASK,
			SR_IDLE | HW_EXIT_IDLE_EN);

	/* uPCTL in low_power status because of auto self-refresh */
	writel(GO_STATE, &priv->pctl->sctl);
}

void get_ddr_param(struct dram_info *sdram_priv,
		   struct ddr_param *ddr_param)
{
	size_t ram_size =
		rockchip_sdram_size((phys_addr_t)&sdram_priv->grf->os_reg2);

	ddr_param->count = 1;
	ddr_param->para[0] = CONFIG_SYS_SDRAM_BASE;
	ddr_param->para[1] = ram_size;
}

int sdram_init(void)
{
	int ret;
	struct ddr_param ddr_param;
	struct dram_info *sdram_priv = &info;
	struct driver_info *info =
		ll_entry_start(struct driver_info, driver_info);
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	struct dtd_rockchip_rv1108_dmc *dtplat = (void *)info->platdata;
	struct sdram_params *params = (void *)dtplat->rockchip_sdram_params;

	sdram_priv->pctl = get_base_addr((void *)dtplat->reg, 0);
	sdram_priv->phy = get_base_addr((void *)dtplat->reg, 1);
	sdram_priv->service_msch = get_base_addr((void *)dtplat->reg, 2);
	sdram_priv->grf = get_base_addr((void *)dtplat->reg, 3);
	sdram_priv->pmu_grf = get_base_addr((void *)dtplat->reg, 4);
	sdram_priv->cru = get_base_addr((void *)dtplat->reg, 5);
	sdram_priv->pmu = get_base_addr((void *)dtplat->reg, 6);
#else
	struct sdram_params *params = (void *)info->platdata;
#endif
	ret = rv1108_sdram_init(sdram_priv, params);
	if (ret)
		debug("rv1108_sdram_init() fail!");

	get_ddr_param(sdram_priv, &ddr_param);
	rockchip_setup_ddr_param(&ddr_param);

	return ret;
}
