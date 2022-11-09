{
	{
		{
			.rank = 0x1,
			.col = 0xC,
			.bk = 0x3,
			.bw = 0x1,
			.dbw = 0x0,
			.row_3_4 = 0x0,
			.cs0_row = 0x10,
			.cs1_row = 0x10,
			.cs0_high16bit_row = 0x10,
			.cs1_high16bit_row = 0x10,
			.ddrconfig = 0
		},
		{
			{0x2b0d080d},
			{0x0a020403},
			{0x00000002},
			{0x00001111},
			{0x0000000c},
			{0x00000000},
			0x000000ff
		}
	},
	{
		.ddr_freq = 396,	/* clock rate(MHz) */
		.dramtype = LPDDR3,
		.num_channels = 1,
		.stride = 0,
		.odt = 0
	},
	{
		{
			{0x00000000, 0x43041008},	/* MSTR */
			{0x00000064, 0x0018002a},	/* RFSHTMG */
			{0x000000d0, 0x00280002},	/* INIT0 */
			{0x000000d4, 0x00010000},	/* INIT1 */
			{0x000000d8, 0x00000803},	/* INIT2 */
			{0x000000dc, 0x00830004},	/* INIT3 */
			{0x000000e0, 0x00010000},	/* INIT4 */
			{0x000000e4, 0x00080003},	/* INIT5 */
			{0x000000f4, 0x000f011f},	/* RANKCTL */
			{0x00000100, 0x070a0d08},	/* DRAMTMG0 */
			{0x00000104, 0x0002020d},	/* DRAMTMG1 */
			{0x00000108, 0x02030606},	/* DRAMTMG2 */
			{0x0000010c, 0x00505000},	/* DRAMTMG3 */
			{0x00000110, 0x04020205},	/* DRAMTMG4 */
			{0x00000114, 0x01010303},	/* DRAMTMG5 */
			{0x00000118, 0x02020003},	/* DRAMTMG6 */
			{0x00000120, 0x00000303},	/* DRAMTMG8 */
			{0x00000138, 0x0000002c},	/* DRAMTMG14 */
			{0x00000180, 0x00480012},	/* ZQCTL0 */
			{0x00000184, 0x00a00000},	/* ZQCTL1 */
			{0x00000190, 0x07020000},	/* DFITMG0 */
			{0x00000198, 0x07000101},	/* DFILPCFG0 */
			{0x000001a0, 0xc0400003},	/* DFIUPD0 */
			{0x00000240, 0x09000a0c},	/* ODTCFG */
			{0x00000244, 0x00000101},	/* ODTMAP */
			{0x00000250, 0x00001f00},	/* SCHED */
			{0x00000490, 0x00000001},	/* PCTRL_0 */
			{0xffffffff, 0xffffffff}
		}
	},
	{
		{
			{0x00000004, 0x0000008b},	/* PHYREG01 */
			{0x00000014, 0x00000006},	/* PHYREG05 */
			{0x00000018, 0x00000000},	/* PHYREG06 */
			{0x0000001c, 0x00000003},	/* PHYREG07 */
			{0xffffffff, 0xffffffff}
		}
	}
},
