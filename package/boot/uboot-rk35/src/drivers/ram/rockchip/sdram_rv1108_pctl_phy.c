// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <dm/root.h>
#include <dt-structs.h>
#include <ram.h>
#include <regmap.h>
#include <asm/io.h>
#include <asm/types.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/sdram_rv1108_pctl_phy.h>
#include <asm/arch-rockchip/timer.h>
#include <asm/arch-rockchip/sdram.h>

#if defined(CONFIG_ROCKCHIP_RV1108)
#include <asm/arch-rockchip/sdram_rv1108.h>
#elif defined(CONFIG_ROCKCHIP_RK3308)
#include <asm/arch-rockchip/sdram_rk3308.h>
#endif

/*
 * we can not fit the code to access the device tree in SPL
 * (due to 6K SRAM size limits), so these are hard-coded
 */

void copy_to_reg(u32 *dest, const u32 *src, u32 n)
{
	int i;

	for (i = 0; i < n / sizeof(u32); i++) {
		writel(*src, dest);
		src++;
		dest++;
	}
}

static void phy_pctrl_reset(struct dram_info *priv)
{
	phy_pctrl_reset_cru(priv);
	clrsetbits_le32(&priv->phy->phy_reg0,
			RESET_DIGITAL_CORE_MASK | RESET_ANALOG_LOGIC_MASK,
			RESET_DIGITAL_CORE_ACT << RESET_DIGITAL_CORE_SHIFT |
			RESET_ANALOG_LOGIC_ACT << RESET_ANALOG_LOGIC_SHIFT);
	udelay(1);
	clrsetbits_le32(&priv->phy->phy_reg0,
			RESET_ANALOG_LOGIC_MASK,
			RESET_ANALOG_LOGIC_DIS << RESET_ANALOG_LOGIC_SHIFT);
	udelay(5);
	clrsetbits_le32(&priv->phy->phy_reg0,
			RESET_DIGITAL_CORE_MASK,
			RESET_DIGITAL_CORE_DIS << RESET_DIGITAL_CORE_SHIFT);
	udelay(1);
}

static void phy_dll_bypass_set(struct dram_info *priv, unsigned int freq)
{
	clrsetbits_le32(&priv->phy->phy_reg13,
			CMD_DLL_BYPASS_MASK << CMD_DLL_BYPASS_SHIFT,
			CMD_DLL_BYPASS << CMD_DLL_BYPASS_SHIFT);

	writel(CK_DLL_BYPASS_DISABLE << CK_DLL_BYPASS_SHIFT,
	       &priv->phy->phy_reg14);

	clrsetbits_le32(&priv->phy->phy_reg26,
			LEFT_CHN_A_DQ_DLL_BYPASS_MASK << LEFT_CHN_A_DQ_DLL_SHIFT,
			LEFT_CHN_A_DQ_DLL_BYPASS << LEFT_CHN_A_DQ_DLL_SHIFT);
	writel(LEFT_CHN_A_DQS_DLL_BYPASS_DIS << LEFT_CHN_A_DQS_DLL_SHIFT,
	       &priv->phy->phy_reg27);

	clrsetbits_le32(&priv->phy->phy_reg36,
			RIGHT_CHN_A_DQ_DLL_BYPASS_MASK << RIGHT_CHN_A_DQ_DLL_SHIFT,
			RIGHT_CHN_A_DQ_DLL_BYPASS << RIGHT_CHN_A_DQ_DLL_SHIFT);
	writel(RIGHT_CHN_A_DQS_DLL_BYPASS_DIS <<
	       RIGHT_CHN_A_DQS_DLL_SHIFT, &priv->phy->phy_reg37);

	if (freq <= PHY_LOW_SPEED_MHZ) {
		writel(RIGHT_CHN_A_TX_DQ_BYPASS_SET <<
		       RIGHT_CHN_A_TX_DQ_BYPASS_SHIFT |
		       LEFT_CHN_A_TX_DQ_BYPASS_SET <<
		       LEFT_CHN_A_TX_DQ_BYPASS_SHIFT |
		       CMD_CK_DLL_BYPASS_SET << CMD_CK_DLL_BYPASS_SHIFT,
		       &priv->phy->phy_regdll);
	} else {
		writel(RIGHT_CHN_A_TX_DQ_BYPASS_DIS <<
		       RIGHT_CHN_A_TX_DQ_BYPASS_SHIFT |
		       LEFT_CHN_A_TX_DQ_BYPASS_DIS <<
		       LEFT_CHN_A_TX_DQ_BYPASS_SHIFT |
		       CMD_CK_DLL_BYPASS_DIS << CMD_CK_DLL_BYPASS_SHIFT,
				&priv->phy->phy_regdll);
	}

	ddr_phy_dqs_rx_dll_cfg(priv, freq);
}

static void send_command(struct dram_info *priv,
			 u32 rank, u32 cmd, u32 arg)
{
	writel((START_CMD | (rank << RANK_SEL_SHIFT) | arg | cmd),
	       &priv->pctl->mcmd);
	while (readl(&priv->pctl->mcmd) & START_CMD)
		;
}

static void memory_init(struct dram_info *priv,
			struct sdram_params *params_priv)
{
	u32 mr0;

	if (params_priv->ddr_config_t.ddr_type == DDR3 ||
	    params_priv->ddr_config_t.ddr_type == DDR2) {
		send_command(priv, RANK_SEL_CS0_CS1, DESELECT_CMD, 0);
		udelay(1);
		send_command(priv, RANK_SEL_CS0_CS1, PREA_CMD, 0);
		send_command(priv, RANK_SEL_CS0_CS1, DESELECT_CMD, 0);
		udelay(1);
		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (MR2 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[2] &
			     CMD_ADDR_MASK) << CMD_ADDR_SHIFT);

		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (MR3 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[3] &
			     CMD_ADDR_MASK) << CMD_ADDR_SHIFT);

		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (MR1 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[1] &
			     CMD_ADDR_MASK) << CMD_ADDR_SHIFT);

		mr0 = params_priv->ddr_timing_t.phy_timing.mr[0];
		if (params_priv->ddr_config_t.ddr_type == DDR3) {
			send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
				     (MR0 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
				     (((mr0 | DDR3_DLL_RESET) &
				       CMD_ADDR_MASK) << CMD_ADDR_SHIFT));

			send_command(priv, RANK_SEL_CS0_CS1, ZQCL_CMD, 0);
		} else {
			send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
				     (MR0 & BANK_ADDR_MASK) << BANK_ADDR_SHIFT |
				     (((mr0 | DDR3_DLL_RESET) &
				       CMD_ADDR_MASK) << CMD_ADDR_SHIFT));
			send_command(priv, RANK_SEL_CS0_CS1, PREA_CMD, 0);
			send_command(priv, RANK_SEL_CS0_CS1, REF_CMD, 0);
			send_command(priv, RANK_SEL_CS0_CS1, REF_CMD, 0);
			send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
				     (MR0 & BANK_ADDR_MASK) <<
				     BANK_ADDR_SHIFT |
				     ((mr0 & CMD_ADDR_MASK) <<
				      CMD_ADDR_SHIFT));
		}
	} else {
		/* reset */
		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (63 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0 & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		/* tINIT5 */
		udelay(10);
		/* ZQ calibration Init */
		send_command(priv, RANK_SEL_CS0, MRS_CMD,
			     (10 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0xFF & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		/* tZQINIT */
		udelay(1);
		send_command(priv, RANK_SEL_CS1, MRS_CMD,
			     (10 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (0xFF & LPDDR23_OP_MASK) <<
			     LPDDR23_OP_SHIFT);
		/* tZQINIT */
		udelay(1);
		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (1 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[1] &
			     LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (2 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[2] &
			     LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
		send_command(priv, RANK_SEL_CS0_CS1, MRS_CMD,
			     (3 & LPDDR23_MA_MASK) << LPDDR23_MA_SHIFT |
			     (params_priv->ddr_timing_t.phy_timing.mr[3] &
			     LPDDR23_OP_MASK) << LPDDR23_OP_SHIFT);
	}
}

void move_to_config_state(struct dram_info *priv)
{
	unsigned int state;

	while (1) {
		state = readl(&priv->pctl->stat) & PCTL_CTL_STAT_MASK;
		switch (state) {
		case LOW_POWER:
			writel(WAKEUP_STATE, &priv->pctl->sctl);
			while ((readl(&priv->pctl->stat) & PCTL_CTL_STAT_MASK)
				!= ACCESS)
				;
			/*
			 * If at low power state, need wakeup first, and then
			 * enter the config, so fallthrough
			 */
		case ACCESS:
		case INIT_MEM:
			writel(CFG_STATE, &priv->pctl->sctl);
			while ((readl(&priv->pctl->stat) & PCTL_CTL_STAT_MASK)
				!= CONFIG)
				;
			break;
		case CONFIG:
			return;
		default:
			break;
		}
	}
}

void move_to_access_state(struct dram_info *priv)
{
	unsigned int state;

	while (1) {
		state = readl(&priv->pctl->stat) & PCTL_CTL_STAT_MASK;
		switch (state) {
		case LOW_POWER:
			writel(WAKEUP_STATE, &priv->pctl->sctl);
			while ((readl(&priv->pctl->stat) &
				PCTL_CTL_STAT_MASK) != ACCESS)
				;
			break;
		case INIT_MEM:
			writel(CFG_STATE, &priv->pctl->sctl);
			while ((readl(&priv->pctl->stat) &
				PCTL_CTL_STAT_MASK) != CONFIG)
				;
			/* fallthrough */
		case CONFIG:
			writel(GO_STATE, &priv->pctl->sctl);
			while ((readl(&priv->pctl->stat) &
				PCTL_CTL_STAT_MASK) != ACCESS)
				;
			break;
		case ACCESS:
			return;
		default:
			break;
		}
	}
}

static void pctl_cfg(struct dram_info *priv,
		     struct sdram_params *params_priv)
{
	u32 reg;
	u32 burstlen;
	u32 bl_mddr_lpddr2;

	/* DFI config */
	writel(DFI_DATA_BYTE_DISABLE_EN << DFI_DATA_BYTE_DISABLE_EN_SHIFT |
	       DFI_INIT_START_EN << DFI_INIT_START_SHIFT,
	       &priv->pctl->dfistcfg0);
	writel(DFI_DRAM_CLK_DISABLE_EN_DPD <<
	       DFI_DRAM_CLK_DISABLE_EN_DPD_SHIFT |
	       DFI_DRAM_CLK_DISABLE_EN << DFI_DRAM_CLK_DISABLE_EN_SHIFT,
	       &priv->pctl->dfistcfg1);
	writel(PARITY_EN << PARITY_EN_SHIFT |
	       PARITY_INTR_EN << PARITY_INTR_EN_SHIFT, &priv->pctl->dfistcfg2);

	writel(TPHYUPD_TYPE0, &priv->pctl->dfitphyupdtype0);
	writel(TPHY_RDLAT, &priv->pctl->dfitphyrdlat);
	writel(TPHY_WRDATA, &priv->pctl->dfitphywrdata);

	writel(DFI_PHYUPD_DISABLE | DFI_CTRLUPD_DISABLE,
	       &priv->pctl->dfiupdcfg);

	copy_to_reg(&priv->pctl->togcnt1u,
		    &params_priv->ddr_timing_t.pctl_timing.togcnt1u,
		    sizeof(struct pctl_timing));
	/*
	 * rv1108 phy is 1:2 mode, noc_timing.b.burstlen
	 * have divide by scheuler clock, so need to * 4
	 */
	burstlen = params_priv->ddr_timing_t.noc_timing.b.burstlen * 4;

	if (params_priv->ddr_config_t.ddr_type == DDR3 ||
	    params_priv->ddr_config_t.ddr_type == DDR2) {
		writel((RANK0_ODT_WRITE_SEL << RANK0_ODT_WRITE_SEL_SHIFT |
		       RANK1_ODT_WRITE_SEL << RANK1_ODT_WRITE_SEL_SHIFT),
		       &priv->pctl->dfiodtcfg);

		writel(ODT_LEN_BL8_W << ODT_LEN_BL8_W_SHIFT,
		       &priv->pctl->dfiodtcfg1);

		writel(params_priv->ddr_timing_t.pctl_timing.trsth,
		       &priv->pctl->trsth);
		if (params_priv->ddr_config_t.ddr_type == DDR3)
			writel(MDDR_LPDDR23_CLOCK_STOP_IDLE_DIS | DDR3_EN |
			       MEM_BL_8 | TFAW_CFG_5_TDDR |
			       PD_EXIT_SLOW_EXIT_MODE | PD_TYPE_ACT_PD |
			       PD_IDLE_DISABLE |
			       params_priv->ddr_2t_en << TWO_T_SHIFT,
			       &priv->pctl->mcfg);
		else if (burstlen == 8)
			writel(MDDR_LPDDR23_CLOCK_STOP_IDLE_DIS | DDR2_EN |
			       MEM_BL_8 | TFAW_CFG_5_TDDR |
			       PD_EXIT_SLOW_EXIT_MODE | PD_TYPE_ACT_PD |
			       PD_IDLE_DISABLE |
			       params_priv->ddr_2t_en << TWO_T_SHIFT,
			       &priv->pctl->mcfg);
		else
			writel(MDDR_LPDDR23_CLOCK_STOP_IDLE_DIS | DDR2_EN |
			       MEM_BL_4 | TFAW_CFG_5_TDDR |
			       PD_EXIT_SLOW_EXIT_MODE | PD_TYPE_ACT_PD |
			       PD_IDLE_DISABLE |
			       params_priv->ddr_2t_en << TWO_T_SHIFT,
			       &priv->pctl->mcfg);
		writel(DFI_LP_EN_SR << DFI_LP_EN_SR_SHIFT |
		       DFI_LP_WAKEUP_SR_32_CYCLES << DFI_LP_WAKEUP_SR_SHIFT |
		       DFI_TLP_RESP << DFI_TLP_RESP_SHIFT,
		       &priv->pctl->dfilpcfg0);

		reg = readl(&priv->pctl->tcl);
		writel((reg - 1) / 2 - 1, &priv->pctl->dfitrddataen);
		reg = readl(&priv->pctl->tcwl);
		writel((reg - 1) / 2 - 1, &priv->pctl->dfitphywrlat);
	} else {
		if (burstlen == 4)
			bl_mddr_lpddr2 = MDDR_LPDDR2_BL_4;
		else
			bl_mddr_lpddr2 = MDDR_LPDDR2_BL_8;
		writel((RANK0_ODT_WRITE_DIS << RANK0_ODT_WRITE_SEL_SHIFT |
		       RANK1_ODT_WRITE_DIS << RANK1_ODT_WRITE_SEL_SHIFT),
		       &priv->pctl->dfiodtcfg);

		writel(ODT_LEN_BL8_W_0 << ODT_LEN_BL8_W_SHIFT,
		       &priv->pctl->dfiodtcfg1);

		writel(0, &priv->pctl->trsth);
		writel(MDDR_LPDDR23_CLOCK_STOP_IDLE_DIS | LPDDR2_EN |
			LPDDR2_S4 | bl_mddr_lpddr2 |
		       TFAW_CFG_6_TDDR | PD_EXIT_FAST_EXIT_MODE |
		       PD_TYPE_ACT_PD | PD_IDLE_DISABLE, &priv->pctl->mcfg);
		writel(DFI_LP_EN_SR << DFI_LP_EN_SR_SHIFT |
		       DFI_LP_WAKEUP_SR_32_CYCLES << DFI_LP_WAKEUP_SR_SHIFT |
		       DFI_TLP_RESP << DFI_TLP_RESP_SHIFT |
		       DFI_LP_WAKEUP_PD_32_CYCLES << DFI_LP_WAKEUP_PD_SHIFT |
		       DFI_LP_EN_PD,
		       &priv->pctl->dfilpcfg0);

		reg = readl(&priv->pctl->tcl);
		writel(reg / 2 - 1, &priv->pctl->dfitrddataen);
		reg = readl(&priv->pctl->tcwl);
		writel(reg / 2 - 1, &priv->pctl->dfitphywrlat);
	}
	pctl_cfg_grf(priv, params_priv);
	setbits_le32(&priv->pctl->scfg, HW_LOW_POWER_EN);

	/* only support x16 memory */
	clrsetbits_le32(&priv->pctl->ppcfg, PPMEM_EN_MASK, PPMEM_EN);
}

static void phy_cfg(struct dram_info *priv,
		    struct sdram_params *params_priv)
{
	u32 burstlen;

	burstlen = params_priv->ddr_timing_t.noc_timing.b.burstlen * 4;
	burstlen = (burstlen == 4) ? PHY_BL_4 : PHY_BL_8;
	ddr_msch_cfg(priv, params_priv);
	ddr_phy_skew_cfg(priv);
	switch (params_priv->ddr_config_t.ddr_type) {
	case DDR2:
		writel(MEMORY_SELECT_DDR2 | PHY_BL_8, &priv->phy->phy_reg1);
		break;
	case DDR3:
		writel(MEMORY_SELECT_DDR3 | PHY_BL_8, &priv->phy->phy_reg1);
		break;
	case LPDDR2:
	default:
		writel(MEMORY_SELECT_LPDDR2 | burstlen, &priv->phy->phy_reg1);
		break;
	}

	writel(params_priv->ddr_timing_t.phy_timing.cl_al,
	       &priv->phy->phy_regb);
	writel(params_priv->ddr_timing_t.pctl_timing.tcwl,
	       &priv->phy->phy_regc);

	set_ds_odt(priv, params_priv);

	/* only support x16 memory */
	clrsetbits_le32(&priv->phy->phy_reg0, DQ_16BIT_EN_MASK,
			DQ_16BIT_EN);
}

static void dram_cfg_rbc(struct dram_info *priv,
			 struct sdram_params *params_priv)
{
	move_to_config_state(priv);
	ddr_msch_cfg_rbc(params_priv, priv);
	move_to_access_state(priv);
}

static void data_training(struct dram_info *priv)
{
	u32 value;
	u32 tmp = 0;
	u32 tmp1 = 0;
	u32 timeout = 1000;

	/* disable auto refresh */
	value = readl(&priv->pctl->trefi);
	writel(UPD_REF, &priv->pctl->trefi);

	tmp1 = readl(&priv->phy->phy_reg2);

	writel(DQS_GATE_TRAINING_SEL_CS0 | DQS_GATE_TRAINING_DIS | tmp1,
	       &priv->phy->phy_reg2);
	writel(DQS_GATE_TRAINING_SEL_CS0 | DQS_GATE_TRAINING_ACT | tmp1,
	       &priv->phy->phy_reg2);

		/* delay until data training done */
	while (tmp != (CHN_A_HIGH_8BIT_TRAINING_DONE |
	       CHN_A_LOW_8BIT_TRAINING_DONE)) {
		udelay(1);
		tmp = (readl(&priv->phy->phy_regff) & CHN_A_TRAINING_DONE_MASK);
		timeout--;
		if (!timeout)
			break;
	}

	writel(DQS_GATE_TRAINING_SEL_CS0 | DQS_GATE_TRAINING_DIS | tmp1,
	       &priv->phy->phy_reg2);

	send_command(priv, RANK_SEL_CS0_CS1, PREA_CMD, 0);

	writel(value | UPD_REF, &priv->pctl->trefi);
}

static int sdram_detect(struct dram_info *priv,
			struct sdram_params *params_priv)
{
	u32 row, col, row_max, col_max, bank_max;
	u32 bw = 1;
	phys_addr_t test_addr;
	struct ddr_schedule ddr_sch;

	/* if col detect wrong,row needs initial */
	row = 0;

	/* detect col */
	move_to_config_state(priv);
	ddr_msch_get_max_col(priv, &ddr_sch);
	col_max = ddr_sch.col;
	bank_max = ddr_sch.bank;
	move_to_access_state(priv);

	for (col = col_max; col >= 10; col--) {
		writel(0, CONFIG_SYS_SDRAM_BASE);
		test_addr = (phys_addr_t)(CONFIG_SYS_SDRAM_BASE +
		    (1ul << (col + bw - 1ul)));
		writel(PATTERN, test_addr);
		if ((readl(test_addr) == PATTERN) &&
		    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
			break;
	}
	if (col <= 9)
		goto cap_err;
	params_priv->ddr_config_t.col = col;

	if (params_priv->ddr_config_t.ddr_type == DDR3) {
		params_priv->ddr_config_t.bank = 3;
	} else {
		writel(0, CONFIG_SYS_SDRAM_BASE);
		test_addr = (phys_addr_t)(CONFIG_SYS_SDRAM_BASE +
		    (1ul << (bank_max + col_max +
		    bw - 1ul)));
		writel(PATTERN, test_addr);
		if ((readl(test_addr) == PATTERN) &&
		    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
			params_priv->ddr_config_t.bank = 3;
		else
			params_priv->ddr_config_t.bank = 2;
	}

	/* detect row */
	move_to_config_state(priv);
	ddr_msch_get_max_row(priv, &ddr_sch);
	move_to_access_state(priv);
	col_max = ddr_sch.col;
	row_max = ddr_sch.row;

	for (row = row_max; row >= 12; row--) {
		writel(0, CONFIG_SYS_SDRAM_BASE);
		test_addr = (phys_addr_t)(CONFIG_SYS_SDRAM_BASE +
				(1ul << (row + bank_max +
				col_max + bw - 1ul)));

		writel(PATTERN, test_addr);
		if ((readl(test_addr) == PATTERN) &&
		    (readl(CONFIG_SYS_SDRAM_BASE) == 0))
			break;
	}
	if (row <= 11)
		goto cap_err;
	params_priv->ddr_config_t.cs0_row = row;
	return 0;
cap_err:
	return -EAGAIN;
}

#define DDR_VERSION	0x2

static void sdram_all_config(struct dram_info *priv,
			     struct sdram_params *params_priv)
{
	u32 version = DDR_VERSION;
	u32 os_reg = 0;
	u32 row_12 = 0;
	u32 ddr_info = 0;
	/* rk3308,rv1108 only support 1 channel, x16 ddr bus, x16 memory */
	u32 chn_cnt = 0;
	u32 rank = 1;
	u32 bw = 1;
	u32 dbw = 1;
	size_t size = 0;
	struct ddr_param ddr_param;

	/* os_reg2 */
	os_reg = (params_priv->ddr_config_t.ddr_type & SYS_REG_DDRTYPE_MASK) <<
		 SYS_REG_DDRTYPE_SHIFT |
		 (chn_cnt & SYS_REG_NUM_CH_MASK) <<
		 SYS_REG_NUM_CH_SHIFT |
		 ((rank - 1) & SYS_REG_RANK_MASK) <<
		 SYS_REG_RANK_SHIFT(0) |
		 ((params_priv->ddr_config_t.col - 9) & SYS_REG_COL_MASK) <<
		 SYS_REG_COL_SHIFT(0) |
		 ((params_priv->ddr_config_t.bank == 3 ? 0 : 1) &
		 SYS_REG_BK_MASK) << SYS_REG_BK_SHIFT(0) |
		 ((params_priv->ddr_config_t.cs0_row - 13) &
		 SYS_REG_CS0_ROW_MASK) << SYS_REG_CS0_ROW_SHIFT(0) |
		 (bw & SYS_REG_BW_MASK) <<
		 SYS_REG_BW_SHIFT(0) |
		 (dbw & SYS_REG_DBW_MASK) <<
		 SYS_REG_DBW_SHIFT(0);

	writel(os_reg, &priv->grf->os_reg2);

	/* os_reg3 */
	if (params_priv->ddr_config_t.cs0_row == 12)
		row_12 = 1;
	os_reg = (version & SYS_REG1_VERSION_MASK) <<
		 SYS_REG1_VERSION_SHIFT | (row_12 &
		 SYS_REG1_EXTEND_CS0_ROW_MASK) <<
		 SYS_REG1_EXTEND_CS0_ROW_SHIFT(0);
	writel(os_reg, &priv->grf->os_reg3);

	printascii("In\n");
	printdec(params_priv->ddr_timing_t.freq);
	printascii("MHz\n");
	switch (params_priv->ddr_config_t.ddr_type & SYS_REG_DDRTYPE_MASK) {
	case 2:
		printascii("DDR2\n");
		break;
	case 5:
		printascii("LPDDR2\n");
		break;
	case 3:
	default:
		printascii("DDR3\n");
		break;
	}
	printascii(" Col=");
	printdec(params_priv->ddr_config_t.col);
	printascii(" Bank=");
	printdec(params_priv->ddr_config_t.bank);
	printascii(" Row=");
	printdec(params_priv->ddr_config_t.cs0_row);

	size = 1llu << (bw +
	       params_priv->ddr_config_t.col +
	       params_priv->ddr_config_t.cs0_row +
	       params_priv->ddr_config_t.bank);
	ddr_info = size >> 20;
	printascii(" Size=");
	printdec(ddr_info);
	printascii("MB\n");
	printascii("msch:");
	ddr_info = readl(&priv->service_msch->ddrconf);
	printdec(ddr_info);
	printascii("\n");

	priv->info.base = CONFIG_SYS_SDRAM_BASE;
	priv->info.size = size;
	ddr_param.count = 1;
	ddr_param.para[0] = priv->info.base;
	ddr_param.para[1] = priv->info.size;
	rockchip_setup_ddr_param(&ddr_param);
}

int rv1108_sdram_init(struct dram_info *sdram_priv,
		      struct sdram_params *params_priv)
{
	/* pmu enable ddr io retention */
	enable_ddr_io_ret(sdram_priv);
	rkdclk_init(sdram_priv, params_priv);
	phy_pctrl_reset(sdram_priv);
	phy_dll_bypass_set(sdram_priv, params_priv->ddr_timing_t.freq);
	pctl_cfg(sdram_priv, params_priv);
	phy_cfg(sdram_priv, params_priv);
	writel(POWER_UP_START, &sdram_priv->pctl->powctl);
	while (!(readl(&sdram_priv->pctl->powstat) & POWER_UP_DONE))
		;

	memory_init(sdram_priv, params_priv);
re_training:
	move_to_config_state(sdram_priv);
	data_training(sdram_priv);
	move_to_access_state(sdram_priv);
	if (sdram_detect(sdram_priv, params_priv)) {
		while (1)
			;
	}
	if (check_rd_gate(sdram_priv))
		goto re_training;

	/* workaround data training not in middle */
	modify_data_training(sdram_priv, params_priv);

	dram_cfg_rbc(sdram_priv, params_priv);
	sdram_all_config(sdram_priv, params_priv);
	enable_low_power(sdram_priv, params_priv);

	return 0;
}
