0x12345678,
2,/* version */
(0 << 0) | (1 << 8) | (9 << 16) | (8 << 24),/* cpu_gen,global index */
(0 << 0) | (9 << 8) | (17 << 16) | (9 << 24),/* d2,d3 index */
(26 << 0) | (9 << 8) | (0 << 16) | (0 << 24),/* d4,d5 index */
(0 << 0) | (9 << 8) | (35 << 16) | (9 << 24),/* lp2,lp3 index */
(44 << 0) | (13 << 8) | (0 << 16) | (0 << 24),/* lp4,lp5 index */
(0 << 0) | (0 << 8) | (57 << 16) | (8 << 24),/* skew index, dq_map index */
(65 << 0) | (13 << 8) | (0 << 16) | (0 << 24), /*lp4x index*/
/* global info */
0,
(93 << 16) | 13,/* sr_idle << 16 | pd_idle */
0,/* channel info */
1,/* 2t info */
0, 0, 0, 0,/* reserved */

/* ddr3 */
(924 << DDR_FREQ_F0_SHIFT) | (328 << DDR_FREQ_F1_SHIFT),
(528 << DDR_FREQ_F2_SHIFT) | (784 << DDR_FREQ_F3_SHIFT),
(0 << DDR_FREQ_F4_SHIFT) | (0 << DDR_FREQ_F5_SHIFT),
/* drv when odt on */
(30 << PHY_DQ_DRV_SHIFT) | (41 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* drv when odt off */
(30 << PHY_DQ_DRV_SHIFT) | (30 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* odt info */
(120 << DRAM_ODT_SHIFT) | (141 << PHY_ODT_SHIFT) |
	(1 << PHY_ODT_PUUP_EN_SHIFT) |
	(0 << PHY_ODT_PUDN_EN_SHIFT),
/* odt enable freq */
(333 << DRAM_ODT_EN_FREQ_SHIFT) | (333 << PHY_ODT_EN_FREQ_SHIFT),
/* slew rate when odt enable */
(0x1f << PHY_DQ_SR_SHIFT) | (0x1f << PHY_CA_SR_SHIFT) |
	(0x1f << PHY_CLK_SR_SHIFT),
/* slew  ratee when odt disable */
(0x1f << PHY_DQ_SR_SHIFT) | (0x1f << PHY_CA_SR_SHIFT) |
	(0x1f << PHY_CLK_SR_SHIFT),

/* ddr4 */
(924 << DDR_FREQ_F0_SHIFT) | (328 << DDR_FREQ_F1_SHIFT),
(528 << DDR_FREQ_F2_SHIFT) | (784 << DDR_FREQ_F3_SHIFT),
(0 << DDR_FREQ_F4_SHIFT) | (0 << DDR_FREQ_F5_SHIFT),
/* drv when odt on */
(37 << PHY_DQ_DRV_SHIFT) | (44 << PHY_CA_DRV_SHIFT) |
	(37 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* drv when odt off */
(37 << PHY_DQ_DRV_SHIFT) | (44 << PHY_CA_DRV_SHIFT) |
	(37 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* odt info */
(120 << DRAM_ODT_SHIFT) | (148 << PHY_ODT_SHIFT) |
	(1 << PHY_ODT_PUUP_EN_SHIFT) | (1 << PHY_ODT_PUDN_EN_SHIFT),
/* odt enable freq */
(625 << DRAM_ODT_EN_FREQ_SHIFT) | (625 << PHY_ODT_EN_FREQ_SHIFT),
/* slew rate when odt enable */
(0xe << PHY_DQ_SR_SHIFT) | (0x3 << PHY_CA_SR_SHIFT) |
	(0x3 << PHY_CLK_SR_SHIFT),
/* slew  ratee when odt disable */
(0xe << PHY_DQ_SR_SHIFT) | (0x3 << PHY_CA_SR_SHIFT) |
	(0x3 << PHY_CLK_SR_SHIFT),

/* lpddr3 */
(924 << DDR_FREQ_F0_SHIFT) | (328 << DDR_FREQ_F1_SHIFT),
(528 << DDR_FREQ_F2_SHIFT) | (784 << DDR_FREQ_F3_SHIFT),
(0 << DDR_FREQ_F4_SHIFT) | (0 << DDR_FREQ_F5_SHIFT),
/* drv when odt on */
(28 << PHY_DQ_DRV_SHIFT) | (37 << PHY_CA_DRV_SHIFT) |
	(34 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* drv when odt off */
(28 << PHY_DQ_DRV_SHIFT) | (37 << PHY_CA_DRV_SHIFT) |
	(34 << PHY_CLK_DRV_SHIFT) | (34 << DRAM_DQ_DRV_SHIFT),
/* odt info */
(120 << DRAM_ODT_SHIFT) | (148 << PHY_ODT_SHIFT) |
	(1 << PHY_ODT_PUUP_EN_SHIFT) | (1 << PHY_ODT_PUDN_EN_SHIFT),
/* odt enable freq */
(333 << DRAM_ODT_EN_FREQ_SHIFT) | (333 << PHY_ODT_EN_FREQ_SHIFT),

/* slew rate when odt enable */
(0xe << PHY_DQ_SR_SHIFT) | (0x0 << PHY_CA_SR_SHIFT) |
	(0x0 << PHY_CLK_SR_SHIFT),
/* slew  ratee when odt disable */
(0xe << PHY_DQ_SR_SHIFT) | (0x0 << PHY_CA_SR_SHIFT) |
	(0x0 << PHY_CLK_SR_SHIFT),

/* lpddr4 */
(924 << DDR_FREQ_F0_SHIFT) | (328 << DDR_FREQ_F1_SHIFT),
(528 << DDR_FREQ_F2_SHIFT) | (784 << DDR_FREQ_F3_SHIFT),
(0 << DDR_FREQ_F4_SHIFT) | (0 << DDR_FREQ_F5_SHIFT),

/* drv when odt on */
(38 << PHY_DQ_DRV_SHIFT) | (46 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (40 << DRAM_DQ_DRV_SHIFT),
/* drv when odt off */
(38 << PHY_DQ_DRV_SHIFT) | (46 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (40 << DRAM_DQ_DRV_SHIFT),
/* odt info and PU-cal info */
(240 << DRAM_ODT_SHIFT) | (80 << PHY_ODT_SHIFT) |
	(0 << LP4_CA_ODT_SHIFT) |
	(LPDDR4_VDDQ_2_5 << LP4_DRV_PU_CAL_ODTEN_SHIFT) |
	(LPDDR4_VDDQ_2_5 << LP4_DRV_PU_CAL_ODTOFF_SHIFT) |
	(0 << PHY_LP4_DRV_PULLDOWN_EN_ODTEN_SHIFT) |
	(0 << PHY_LP4_DRV_PULLDOWN_EN_ODTOFF_SHIFT),
/* odt enable freq */
(333 << PHY_LP4_ODT_EN_FREQ_SHIFT) | (333 << LP4_DQ_ODT_EN_FREQ_SHIFT),
/* slew rate when odt enable */
(0xf << PHY_DQ_SR_SHIFT) | (0xf << PHY_CA_SR_SHIFT) |
	(0xf << PHY_CLK_SR_SHIFT),
/* slew  ratee when odt disable */
(0xf << PHY_DQ_SR_SHIFT) | (0xf << PHY_CA_SR_SHIFT) |
	(0xf << PHY_CLK_SR_SHIFT),
/* ca odt en freq */
(333 << LP4_CA_ODT_EN_FREQ_SHIFT),
/* cs drv info and ca odt info */
(0 << PHY_LP4_CS_DRV_ODTEN_SHIFT) |
	(0 << PHY_LP4_CS_DRV_ODTOFF_SHIFT) |
	(0 << LP4_ODTE_CK_SHIFT) | (0 << LP4_ODTE_CS_EN_SHIFT) |
	(0 << LP4_ODTD_CA_EN_SHIFT),
/* vref info when odt enable */
(200 << PHY_LP4_DQ_VREF_SHIFT) | (420 << LP4_DQ_VREF_SHIFT) |
	(420 << LP4_CA_VREF_SHIFT),
/* vref info when odt disable */
(420 << PHY_LP4_DQ_VREF_SHIFT) | (420 << LP4_DQ_VREF_SHIFT) |
	(420 << LP4_CA_VREF_SHIFT),
/* ddr4 map << 0 | ddr3 map << 24 */
((0x2 << 6) | (0x1 << 4) | (0x3 << 2) | (0x0 << 0)) |
	(0 << 8) | (0 << 16) |
	(((0x2 << 6) | (0x1 << 4) | (0x3 << 2) | (0x0 << 0)) << 24),
/* lp3 map << 16 | lp4 map << 24 */
/* lp4 should equal to 0xc9 */
(((0x3 << 6) | (0x2 << 4) | (0x1 << 2) | (0x0 << 0)) << 16) |
	(((0x3 << 6) | (0x0 << 4) | (0x2 << 2) | (0x1 << 0)) << 24),
/* lp3 dq0-7 map */
(2 << 0) | (6 << 4) | (4 << 8) | (0 << 12) | (3 << 16) | (7 << 20) |
	( 5 << 24) | (1 << 28),
/* lp2 dq0-7 map */
0,
/* ddr4 dq map */
/* cs0 dq0-15 */
	((2 << 0 | 0 << 2 | 3 << 4 | 1 << 6) << 0) |
	((0 << 0 | 2 << 2 | 3 << 4 | 1 << 6) << 8) |
	((2 << 0 | 2 << 2 | 1 << 4 | 3 << 6) << 16) |
	((1 << 0 | 3 << 2 | 0 << 4 | 0 << 6) << 24),
/* cs0 dq16-31 */
	((2 << 0 | 0 << 2 | 2 << 4 | 0 << 6) << 0) |
	((1 << 0 | 3 << 2 | 3 << 4 | 1 << 6) << 8) |
	((0 << 0 | 0 << 2 | 1 << 4 | 3 << 6) << 16) |
	((1 << 0 | 3 << 2 | 2 << 4 | 2 << 6) << 24),
/* cs1 dq0-15 */
	((2 << 0 | 0 << 2 | 3 << 4 | 1 << 6) << 0) |
	((0 << 0 | 2 << 2 | 3 << 4 | 1 << 6) << 8) |
	((2 << 0 | 2 << 2 | 1 << 4 | 3 << 6) << 16) |
	((1 << 0 | 3 << 2 | 0 << 4 | 0 << 6) << 24),
/* cs1 dq16-31 */
	((2 << 0 | 0 << 2 | 2 << 4 | 0 << 6) << 0) |
	((1 << 0 | 3 << 2 | 3 << 4 | 1 << 6) << 8) |
	((0 << 0 | 0 << 2 | 1 << 4 | 3 << 6) << 16) |
	((1 << 0 | 3 << 2 | 2 << 4 | 2 << 6) << 24),

/* lpddr4x */
(1056 << DDR_FREQ_F0_SHIFT) | (328 << DDR_FREQ_F1_SHIFT),
(528 << DDR_FREQ_F2_SHIFT) | (784 << DDR_FREQ_F3_SHIFT),
(0 << DDR_FREQ_F4_SHIFT) | (0 << DDR_FREQ_F5_SHIFT),

/* drv when odt on */
(38 << PHY_DQ_DRV_SHIFT) | (38 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (40 << DRAM_DQ_DRV_SHIFT),
/* drv when odt off */
(38 << PHY_DQ_DRV_SHIFT) | (38 << PHY_CA_DRV_SHIFT) |
	(38 << PHY_CLK_DRV_SHIFT) | (40 << DRAM_DQ_DRV_SHIFT),
/* odt info and PU-cal info */
(48 << DRAM_ODT_SHIFT) | (60 << PHY_ODT_SHIFT) |
	(120 << LP4_CA_ODT_SHIFT) |
	(LPDDR4X_VDDQ_0_6 << LP4_DRV_PU_CAL_ODTEN_SHIFT) |
	(LPDDR4X_VDDQ_0_6 << LP4_DRV_PU_CAL_ODTOFF_SHIFT) |
	(0 << PHY_LP4_DRV_PULLDOWN_EN_ODTEN_SHIFT) |
	(0 << PHY_LP4_DRV_PULLDOWN_EN_ODTOFF_SHIFT),
/* odt enable freq */
(0 << PHY_LP4_ODT_EN_FREQ_SHIFT) | (0 << LP4_DQ_ODT_EN_FREQ_SHIFT),
/* slew rate when odt enable */
(0xf << PHY_DQ_SR_SHIFT) | (0xf << PHY_CA_SR_SHIFT) |
	(0xf << PHY_CLK_SR_SHIFT),
/* slew  ratee when odt disable */
(0xf << PHY_DQ_SR_SHIFT) | (0xf << PHY_CA_SR_SHIFT) |
	(0xf << PHY_CLK_SR_SHIFT),
/* ca odt en freq */
(333 << LP4_CA_ODT_EN_FREQ_SHIFT),
/* cs drv info and ca odt info */
(0 << PHY_LP4_CS_DRV_ODTEN_SHIFT) |
	(0 << PHY_LP4_CS_DRV_ODTOFF_SHIFT) |
	(0 << LP4_ODTE_CK_SHIFT) | (0 << LP4_ODTE_CS_EN_SHIFT) |
	(0 << LP4_ODTD_CA_EN_SHIFT),
/* vref info when odt enable, phy vddq=1.1V, lp4x vddq=0.6V */
(153 << PHY_LP4_DQ_VREF_SHIFT) | (515 << LP4_DQ_VREF_SHIFT) |
	(629 << LP4_CA_VREF_SHIFT),
/* vref info when odt disable */
(153 << PHY_LP4_DQ_VREF_SHIFT) | (629 << LP4_DQ_VREF_SHIFT) |
	(629 << LP4_CA_VREF_SHIFT),

