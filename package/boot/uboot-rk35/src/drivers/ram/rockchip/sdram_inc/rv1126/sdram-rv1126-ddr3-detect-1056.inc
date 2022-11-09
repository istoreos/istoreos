{
	{
		{
			.rank = 0x1,
			.col = 0xC,
			.bk = 0x3,
			.bw = 0x0,
			.dbw = 0x0,
			.row_3_4 = 0x0,
			.cs0_row = 0x10,
			.cs1_row = 0x10,
			.cs0_high16bit_row = 0x10,
			.cs1_high16bit_row = 0x10,
			.ddrconfig = 0
		},
		{
			{0x351b1019},
			{0x12030903},
			{0x00000002},
			{0x00001111},
			{0x0000000c},
			{0x00000000},
			0x000000ff
		}
	},
	{
		.ddr_freq = 1056,	/* clock rate(MHz) */
		.dramtype = DDR3,
		.num_channels = 1,
		.stride = 0,
		.odt = 1
	},
	{
		{
			{0x00000000, 0x43042001},	/* MSTR */
			{0x00000064, 0x008000b9},	/* RFSHTMG */
			{0x000000d0, 0x00020103},	/* INIT0 */
			{0x000000d4, 0x00690000},	/* INIT1 */
			{0x000000d8, 0x00000100},	/* INIT2 */
			{0x000000dc, 0x01240040},	/* INIT3 */
			{0x000000e0, 0x00280000},	/* INIT4 */
			{0x000000e4, 0x000c0000},	/* INIT5 */
			{0x000000f4, 0x000f011f},	/* RANKCTL */
			{0x00000100, 0x0f132414},	/* DRAMTMG0 */
			{0x00000104, 0x000d0419},	/* DRAMTMG1 */
			{0x00000108, 0x0507050b},	/* DRAMTMG2 */
			{0x0000010c, 0x00202008},	/* DRAMTMG3 */
			{0x00000110, 0x07020408},	/* DRAMTMG4 */
			{0x00000114, 0x06060404},	/* DRAMTMG5 */
			{0x00000120, 0x00000907},	/* DRAMTMG8 */
			{0x00000180, 0x00a9002b},	/* ZQCTL0 */
			{0x00000184, 0x00000000},	/* ZQCTL1 */
			{0x00000190, 0x07050003},	/* DFITMG0 */
			{0x00000198, 0x07000101},	/* DFILPCFG0 */
			{0x000001a0, 0xc0400003},	/* DFIUPD0 */
			{0x00000240, 0x06000610},	/* ODTCFG */
			{0x00000244, 0x00000201},	/* ODTMAP */
			{0x00000250, 0x00001f00},	/* SCHED */
			{0x00000490, 0x00000001},	/* PCTRL_0 */
			{0xffffffff, 0xffffffff}
		}
	},
	{
		{
			{0x00000004, 0x0000008a},	/* PHYREG01 */
			{0x00000014, 0x0000000e},	/* PHYREG05 */
			{0x00000018, 0x00000000},	/* PHYREG06 */
			{0x0000001c, 0x0000000a},	/* PHYREG07 */
			{0xffffffff, 0xffffffff}
		}
	}
},
