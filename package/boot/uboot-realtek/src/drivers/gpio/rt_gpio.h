

#define PMUX_BASE_SB2	0x9801A000
#define PMUX_BASE_DISP	0x9804D000
#define PMUX_BASE_CR	0x98012000
#define PMUX_BASE_ISO	0x98007000

#define PADDRI_4_8 1
#define PADDRI_2_4 0
#define PADDRI_UNSUPPORT 0xFFFF

#define PCOF_UNSUPPORT 0xFFFF
#define PMUX_UNSUPPORT 0xFFFF

#define PULL_DISABLE	0
#define PULL_DOWN		1
#define PULL_UP			2

struct rtk_pin_regmap{
	unsigned int pmux_base;
	unsigned int pmux_regoff;
	unsigned int pmux_regbit;
	unsigned int pmux_regbitmsk;
	unsigned int pcof_regoff;
	unsigned int pcof_regbit;
	unsigned int pcof_cur_strgh;//0 : 2&4mA   1:4&8mA
};

int getGPIO(int GPIO_NUM);
int setGPIO(int GPIO_NUM, int value);
int getISOGPIO(int ISOGPIO_NUM);
int setISOGPIO(int ISOGPIO_NUM, int value);
int setGPIO_pullsel(unsigned int GPIO_NUM, unsigned char pull_sel);
int setISOGPIO_pullsel(int ISOGPIO_NUM, unsigned char pull_sel);


static const struct rtk_pin_regmap pin_regmap[] = {
	/* ----- SB2 muxpad ----- */
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=0, .pmux_regbitmsk=0x7,	.pcof_regoff=0x934, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 0, "gpio_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=3, .pmux_regbitmsk=0x7,	.pcof_regoff=0x934, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 1, "gpio_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x934, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 2, "gpio_2")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x934, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 3, "gpio_3")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 4, "gpio_4")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 5, "gpio_5")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 6, "gpio_6")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x934, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 7, "gpio_7")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 8, "gpio_8")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x910, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 9, "gpio_9")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x92c, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 10, "tp1_sync")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x930, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 11, "i2c_scl_4")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x930, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 12, "i2c_sda_4")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x930, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 13, "i2c_scl_5")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x930, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 14, "i2c_sda_5")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 15, "usb_id")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=30,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 16, "sensor_cko_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=28,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 17, "sensor_cko_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=26,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 18, "sensor_rst")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=24,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 19, "sensor_stb_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x90c, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x938, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 20, "sensor_stb_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=0, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 21, "tp0_data")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 22, "tp0_clk")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 23, "tp0_valid")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=3, .pmux_regbitmsk=0x7,	.pcof_regoff=0x928, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 24, "tp0_sync")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x92c, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 25, "tp1_data")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x92c, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 26, "tp1_clk")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x908, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x92c, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 27, "tp1_valid")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 28, "rgmii0_txc")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 29, "rgmii0_tx_ctl")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 30, "rgmii0_txd_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 31, "rgmii0_txd_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 32, "rgmii0_txd_2")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 33, "rgmii0_txd_3")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 34, "rgmii0_rxc")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x964, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 35, "rgmii0_rx_ctl")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 36, "rgmii0_rxd_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 37, "rgmii0_rxd_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 38, "rgmii0_rxd_2")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 39, "rgmii0_rxd_3")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=24,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 40, "rgmii0_mdio")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x96c, .pmux_regbit=26,.pmux_regbitmsk=0x3,	.pcof_regoff=0x968, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 41, "rgmii0_mdc")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 42, "rgmii1_txc")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 43, "rgmii1_tx_ctl")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 44, "rgmii1_txd_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 45, "rgmii1_txd_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 46, "rgmii1_txd_2")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 47, "rgmii1_txd_3")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 48, "rgmii1_rxc")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x974, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 49, "rgmii1_rx_ctl")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x978, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 50, "rgmii1_rxd_0")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x978, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 51, "rgmii1_rxd_1")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x978, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 52, "rgmii1_rxd_2")
	{.pmux_base=PMUX_BASE_SB2,	.pmux_regoff=0x97c, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x978, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 53, "rgmii1_rxd_3")
	/* ----- disp muxpad ----- */
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x000, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 54, "spdif")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x000, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 55, "dmic_clk")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x000, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 56, "dmic_data")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 57, "ao_lrck")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 58, "ao_bck")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 59, "aock")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 60, "ao_sd_0")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 61, "ao_sd_1")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 62, "ao_sd_2")
	{.pmux_base=PMUX_BASE_DISP, .pmux_regoff=0x008, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x004, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_2_4}, //(P_MISC_BASE + 63, "ao_sd_3")
	/* ----- CardReader muxpad ----- */
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 64, "nf_cle")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 65, "nf_ale")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 66, "nf_rd_n")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 67, "nf_wr_n")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 68, "nf_rdy")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=30,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 69, "nf_dd_7")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=28,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 70, "nf_dd_6")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=26,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 71, "nf_dd_5")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=24,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 72, "nf_dd_4")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 73, "nf_dd_3")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 74, "nf_dd_2")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 75, "nf_dd_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x60c, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 76, "nf_dd_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 77, "nf_dqs")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 78, "nf_ce_n_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x600, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x608, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 79, "nf_ce_n_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 80, "emmc_dd_sb")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 81, "mmc_cmd")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 82, "mmc_clk")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 83, "mmc_wp")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 84, "mmc_cd")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=24,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 85, "mmc_data_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=26,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 86, "mmc_data_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=28,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 87, "mmc_data_2")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=30,.pmux_regbitmsk=0x3,	.pcof_regoff=0x610, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 88, "mmc_data_3")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 89, "sdio_cmd")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 90, "sdio_clk")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 91, "sdio_data_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 92, "sdio_data_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 93, "sdio_data_2")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x604, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x614, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_UNSUPPORT}, //(P_MISC_BASE + 94, "sdio_data_3")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 95, "pcie_clkreq_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 96, "pcie_clkreq_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 97, "prob_0")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 98, "prob_1")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 99, "prob_2")
	{.pmux_base=PMUX_BASE_CR,	.pmux_regoff=0x61c, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x618, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_4_8}, //(P_MISC_BASE + 100, "prob_3")
	/* ----- ISO muxpad ----- */
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0x0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 0, "iso_gpio_0")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=PMUX_UNSUPPORT,	.pmux_regbit=0, .pmux_regbitmsk=0x0,	.pcof_regoff=PCOF_UNSUPPORT, .pcof_regbit=0, .pcof_cur_strgh = 0},//(P_ISO_BASE + 1, "iso_gpio_1)
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=6, .pmux_regbitmsk=0x7,	.pcof_regoff=0x300, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 2,	"iso_gpio_2")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=9, .pmux_regbitmsk=0x7,	.pcof_regoff=0x300, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 3,	"iso_gpio_3")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 4,	"iso_gpio_4")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 5,	"iso_gpio_5")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x30c, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 6,	"hdmi_hpd")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 7,	"iso_gpio_7")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 8,	"ir_rx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 9,	"ir_tx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 10, "ur0_rx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 11, "ur0_tx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 12, "ur1_rx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 13, "ur1_tx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 14, "ur1_cts_n")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 15, "ur1_rts_n")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 16, "i2c_scl_0")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=24,.pmux_regbitmsk=0x3,	.pcof_regoff=0x300, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 17, "i2c_sda_0")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 18, "i2c_scl_1")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=14,.pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 19, "i2c_sda_1")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 20, "i2c_scl_6")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=0, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 21, "iso_gpio_21")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 22, "iso_gpio_22")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=4, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=8, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 23, "iso_gpio_23")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=6, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 24, "iso_gpio_24")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=8, .pmux_regbitmsk=0x3,	.pcof_regoff=0x318, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 25, "iso_gpio_25")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=2, .pmux_regbitmsk=0x3,	.pcof_regoff=0x308, .pcof_regbit=12,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 26, "i2c_sda_6")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=26,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 27, "etn_led_link")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x310, .pmux_regbit=28,.pmux_regbitmsk=0x3,	.pcof_regoff=0x304, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 28, "etn_led_rxtx")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=16,.pmux_regbitmsk=0x3,	.pcof_regoff=0x30c, .pcof_regbit=16,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 29, "nat_led_0")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=18,.pmux_regbitmsk=0x3,	.pcof_regoff=0x30c, .pcof_regbit=20,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 30, "nat_led_1")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=20,.pmux_regbitmsk=0x3,	.pcof_regoff=0x30c, .pcof_regbit=24,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 31, "nat_led_2")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x314, .pmux_regbit=22,.pmux_regbitmsk=0x3,	.pcof_regoff=0x30c, .pcof_regbit=28,.pcof_cur_strgh = PADDRI_4_8}, //(P_ISO_BASE + 32, "nat_led_3")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=10,.pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=0, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 33, "iso_gpio_33")
	{.pmux_base=PMUX_BASE_ISO,	.pmux_regoff=0x31c, .pmux_regbit=12,.pmux_regbitmsk=0x3,	.pcof_regoff=0x320, .pcof_regbit=4, .pcof_cur_strgh = PADDRI_2_4}, //(P_ISO_BASE + 34, "iso_gpio_34")
};

