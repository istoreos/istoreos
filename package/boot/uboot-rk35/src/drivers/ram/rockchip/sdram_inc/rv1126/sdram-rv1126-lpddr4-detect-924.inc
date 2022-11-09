{
	{
		{
			.rank = 0x1,
			.col = 0xB,
			.bk = 0x3,
			.bw = 0x1,
			.dbw = 0x1,
			.row_3_4 = 0x0,
			.cs0_row = 0x11,
			.cs1_row = 0x11,
			.cs0_high16bit_row = 0x0,
			.cs1_high16bit_row = 0x0,
			.ddrconfig = 0
		},
		{
			{0x3e20121d},
			{0x12050a07},
			{0x00000602},
			{0x00001111},
			{0x00000054},
			{0x00000000},
			0x000000ff
		}
	},
	{
		.ddr_freq = 924,	/* clock rate(MHz) */
		.dramtype = LPDDR4,
		.num_channels = 1,
		.stride = 0,
		.odt = 1
	},
	{
		{
			{0x00000000, 0x81081020},	/* MSTR */
			{0x00000064, 0x00380082},	/* RFSHTMG */
			{0x000000d0, 0x00020388},	/* INIT0 */
			{0x000000d4, 0x005c0000},	/* INIT1 */
			{0x000000d8, 0x00000205},	/* INIT2 */
			{0x000000dc, 0x0034001b},	/* INIT3 */
			{0x000000e0, 0x00310000},	/* INIT4 */
			{0x000000e8, 0x00110000},	/* INIT6 */
			{0x000000ec, 0x00000000},	/* INIT7 */
			{0x000000f4, 0x000f033f},	/* RANKCTL */
			{0x00000100, 0x12130f14},	/* DRAMTMG0 */
			{0x00000104, 0x0004041e},	/* DRAMTMG1 */
			{0x00000108, 0x050a0e0f},	/* DRAMTMG2 */
			{0x0000010c, 0x00707000},	/* DRAMTMG3 */
			{0x00000110, 0x0904050a},	/* DRAMTMG4 */
			{0x00000114, 0x02040707},	/* DRAMTMG5 */
			{0x00000118, 0x01010005},	/* DRAMTMG6 */
			{0x0000011c, 0x00000401},	/* DRAMTMG7 */
			{0x00000120, 0x00000606},	/* DRAMTMG8 */
			{0x00000130, 0x00020000},	/* DRAMTMG12 */
			{0x00000134, 0x0a100002},	/* DRAMTMG13 */
			{0x00000138, 0x00000085},	/* DRAMTMG14 */
			{0x00000180, 0x01ce000e},	/* ZQCTL0 */
			{0x00000184, 0x01800000},	/* ZQCTL1 */
			{0x00000190, 0x07070001},	/* DFITMG0 */
			{0x00000198, 0x07000101},	/* DFILPCFG0 */
			{0x000001a0, 0xc0400003},	/* DFIUPD0 */
			{0x00000240, 0x0b050d3c},	/* ODTCFG */
			{0x00000244, 0x00000101},	/* ODTMAP */
			{0x00000250, 0x00001f00},	/* SCHED */
			{0x00000490, 0x00000001},	/* PCTRL_0 */
			{0xffffffff, 0xffffffff}
		}
	},
	{
		{
			{0x00000004, 0x0000008d},	/* PHYREG01 */
			{0x00000014, 0x00000014},	/* PHYREG05 */
			{0x00000018, 0x00000000},	/* PHYREG06 */
			{0x0000001c, 0x0000000a},	/* PHYREG07 */
			{0xffffffff, 0xffffffff}
		}
	}
},
