{
	.start_tag = 0x12345678,
	.version_info = 0,
	.gcpu_gen_freq = 0,
	.g_d2_lp2_freq = (451 << 16) | 451,
	.g_d3_lp3_freq = (589 << 16) | 0,
	.g_d4_lp4_freq = 0x00000000,
	.g_uart_info = (2 << 28) | (1 << 24) | 1500000,
	.g_sr_pd_idle = (48 << 16) | 10,
	.g_ch_info = 0 | 128,
	.g_2t_info = 1,
	.reserved11 = 0,
	.reserved12 = 0,
	.reserved13 = 0
},
{
	{/*cmd,addr de-skew*/
		0x22,
		0x22,
		0x21,
		0x21,
		0x21,
		0x10,
		0x21,
		0x21,
		0x13,
		0x23,
		0x10,
		0x99,/*clk*/
		0x03,
		0x30,
	},
	{/*cs0 dq0~7,dm,dqs*/
		0xaa,
		0xaa,
		0x88,
		0xbb,
		0x88,
		0x88,
		0x99,
		0x88,
		0x88,
		0x7a,/*dqs0 rx tx*/
		0xa,/*dqsb0  tx*/
	/*cs0 dq8~15,dm,dqs*/
		0x88,
		0xaa,
		0x99,
		0x68,
                0x89,
		0x88,
		0x99,
		0x87,
                0x89,
		0x56,/*dqs1 rx tx*/
		0x6,/*dqsb1  tx*/
	},
}
