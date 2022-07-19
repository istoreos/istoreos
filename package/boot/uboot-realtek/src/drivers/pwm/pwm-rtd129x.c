#include <common.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/io.h>
#include <asm/arch/pwm.h>

#define RTK_PWM_OCD_SHIFT       (8)
#define RTK_PWM_CD_SHIFT        (8)
#define RTK_PWM_CSD_SHIFT       (4)

#define RTK_PWM_OCD_MASK       (0xff)
#define RTK_PWM_CD_MASK        (0xff)
#define RTK_PWM_CSD_MASK       (0xf)

#define RTK_PWM_OCD_DEFAULT      	(0xff)
#define RTK_PWM_CD_DEFAULT       	(0x1)
#define RTK_PWM_CSD_DEFAULT     	(0x1)

#define NUM_PWM 4

#define PWM_DEBUG 0

#if PWM_DEBUG
#define DBG(format, ...) printf(format , ## __VA_ARGS__)
#else
#define DBG(format, ...)
#endif

#define BIT(nr)         (1UL << (nr))

struct rtd1295_pwm_chip {
	int			base_freq;
	int			out_freq[NUM_PWM]; //Hz
	int			duty_rate[NUM_PWM];
	int			enable[NUM_PWM];
	int			clksrc_div[NUM_PWM];
	int			clkout_div[NUM_PWM];
	int			clk_duty[NUM_PWM];
};

static struct rtd1295_pwm_chip rtd_pc, *pc;


static int set_real_freq_by_target_freq(int hwpwm, int target_freq, bool fixed_ocd) {
	int base_freq = pc->base_freq;
	int real_freq;
	int ocd, csd, div, opt_div;
	div = base_freq / target_freq;

	{
		// give a div to get max ocd and min csd
		int min_ocd = 0;
		int max_ocd = 255;
		int min_csd = 0;
		int max_csd = 15;
		int i;
		// find max bit
		for (i = 0; i < 32; i++) {
			if ((div << i) & BIT(31)) {
				break;
			}
		}
		csd = (32 - (i + 8)) - 1;
		ocd = (div >> (csd + 1)) - 1;
		if (csd > max_csd) csd = max_csd;
		else if (csd < min_csd) csd = min_csd;

		if (ocd > max_ocd) ocd = max_ocd;
		else if (ocd < min_ocd) ocd = min_ocd;

		if (fixed_ocd)
			ocd = pc->clkout_div[hwpwm];

		opt_div = BIT(csd + 1)*(ocd + 1);
		DBG("--- debug : target_div=%d, real_div=%d, osd=%d, ocd=%d\n", div, opt_div, csd, ocd);
	}

	real_freq = base_freq / opt_div;
	pc->clkout_div[hwpwm] = ocd;
	pc->clksrc_div[hwpwm] = csd;

	pc->out_freq[hwpwm] = real_freq;

	DBG("--- %s debug : hwpwm=%d, target_freq=%d, real_freq=%d, osd=%d, ocd=%d\n",
			__func__, hwpwm, target_freq, pc->out_freq[hwpwm], pc->clksrc_div[hwpwm], pc->clkout_div[hwpwm]);

	return real_freq;
}

static int set_real_freq_by_target_div(int hwpwm, int clksrc_div, int clkout_div) {
	int base_freq = pc->base_freq;
	int real_freq, div;

	div = BIT(clksrc_div + 1) * (clkout_div + 1);
	real_freq = base_freq / div;

	pc->clkout_div[hwpwm] = clkout_div;
	pc->clksrc_div[hwpwm] = clksrc_div;

	pc->out_freq[hwpwm] = real_freq;

	DBG("--- %s debug : real_freq=%d, osd=%d, ocd=%d\n",
			__func__, pc->out_freq[hwpwm], pc->clksrc_div[hwpwm], pc->clkout_div[hwpwm]);

	return real_freq;
}

static int set_clk_duty(int hwpwm, int duty_rate) {
	int clkout_div = pc->clkout_div[hwpwm];
	if (duty_rate < 0) duty_rate = 0;
	if (duty_rate > 100) duty_rate = 100;

	pc->duty_rate[hwpwm] = duty_rate;
	pc->clk_duty[hwpwm] = (duty_rate * (clkout_div + 1) / 100) - 1;

	if (pc->clk_duty[hwpwm] < 0) pc->clk_duty[hwpwm] = 0;
	if (pc->clk_duty[hwpwm] > clkout_div) pc->clk_duty[hwpwm] = clkout_div;

	return 0;
}

static void pwm_set_register(int hwpwm)
{
	u32 value;
	int clkout_div = 0;
	int clk_duty = 0;
	int clksrc_div = 0;
	if(pc==NULL) {
		DBG("--- debug : pwm_set_register -- parameter error!-- \n");
		return;
	}

	if (pc->enable[hwpwm]) {
		clkout_div = pc->clkout_div[hwpwm];
		clk_duty = pc->clk_duty[hwpwm];
		clksrc_div = pc->clksrc_div[hwpwm];
	}

	DBG("--- debug : pwm_set_register -- set index %d OCD=%d,CD=%d,CSD=%d\n",
			hwpwm, clkout_div, clk_duty, clksrc_div);

	value = rtd_inl(ISO_PWM_OCD);
	value &= ~(RTK_PWM_OCD_MASK << (hwpwm*RTK_PWM_OCD_SHIFT));
	value |= clkout_div << (hwpwm*RTK_PWM_OCD_SHIFT);
	rtd_outl(ISO_PWM_OCD, value);

	value = rtd_inl(ISO_PWM_CD);
	value &= ~(RTK_PWM_CD_MASK << (hwpwm*RTK_PWM_CD_SHIFT));
	value |= clk_duty << (hwpwm*RTK_PWM_CD_SHIFT);
	rtd_outl(ISO_PWM_CD, value);

	value = rtd_inl(ISO_PWM_CSD);
	value &= ~(RTK_PWM_CSD_MASK << (hwpwm*RTK_PWM_CSD_SHIFT));
	value |= clksrc_div << (hwpwm*RTK_PWM_CSD_SHIFT);
	rtd_outl(ISO_PWM_CSD, value);

	DBG("--- debug :  ---- pwm_set_register --- done! \n");
}

int pwm_get_freq(int pwm_number, unsigned int* freq)
{
	if (pwm_number < 0 || pwm_number > 3) {
		DBG("pwm_get_freq : invalid pwm_number=%d (0~3)\n", pwm_number);
		return 1;
	}
	if (pc->enable[pwm_number]) {
		*freq = pc->out_freq[pwm_number];
	} else {
		*freq = 0;
	}

	DBG("pwm_get_freq : PWM %d, enable %d, out_freq %d\n", pwm_number, pc->enable[pwm_number], pc->out_freq[pwm_number]);
	return 0;
}

int pwm_set_freq(int pwm_number, unsigned int freq)
{
	if (pwm_number < 0 || pwm_number > 3) {
		DBG("pwm_set_freq : invalid pwm_number=%d (0~3)\n", pwm_number);
		return 1;
	}

	if (freq < 1 || freq > 52735) {
		DBG("pwm_set_freq : invalid freq=%d (1~55296)\n", freq);
		return 1;
	}

	if( pc->out_freq[pwm_number] == freq ) {
		DBG("pwm_set_freq : freq value is not changed, skip! \n");
	}
	else {
		DBG(" pwm_set_freq : assign [%d] to out_freq now! \n", freq);

		set_real_freq_by_target_freq(pwm_number, freq, true);
		/* update CD if OCD is not fixed */
		//set_clk_duty(pwm_number, pc->duty_rate[pwm_number]);
		pwm_set_register(pwm_number);
	}

	return 0;
}

int pwm_get_duty_rate(int pwm_number, unsigned int* duty_rate)
{
	if (pwm_number < 0 || pwm_number > 3) {
		DBG("pwm_get_duty_rate : invalid pwm_number=%d (0~3)\n", pwm_number);
		return 1;
	}
	if (pc->enable[pwm_number]) {
		*duty_rate = pc->duty_rate[pwm_number];
	} else {
		*duty_rate = 0;
	}

	DBG("pwm_get_duty_rate : PWM %d, enable %d, duty_rate %d\n", pwm_number, pc->enable[pwm_number], pc->duty_rate[pwm_number]);
	return 0;
}

int pwm_set_duty_rate(int pwm_number, unsigned int duty_rate)
{
	if (pwm_number < 0 || pwm_number > 3) {
		DBG("pwm_set_duty_rate : invalid pwm_number=%d (0~3)\n", pwm_number);
		return 1;
	}

	if (duty_rate > 100) {
		DBG("pwm_set_duty_rate : invalid duty_rate=%d (0~100)\n", duty_rate);
		return 1;
	}

	if( pc->duty_rate[pwm_number] == duty_rate ) {
		DBG("pwm_set_duty_rate : dutyRate value is not changed, skip! \n");
	}
	else {
		DBG(" pwm_set_duty_rate : assign [%d] to duty_rate now! \n", duty_rate);

		set_clk_duty(pwm_number, duty_rate);
		pwm_set_register(pwm_number);
	}

	return 0;
}

int pwm_enable(int pwm_number, unsigned int value)
{
	if (pwm_number < 0 || pwm_number > 3) {
		DBG("pwm_enable : invalid pwm_number=%d (0~3)\n", pwm_number);
		return 1;
	}

	if (value > 1) {
		DBG("pwm_enable : invalid value=%d (0~1)\n", value);
		return 1;
	}

	pc->enable[pwm_number] = value;
	pwm_set_register(pwm_number);
	return 0;
}

int rtd129x_pwm_show(void)
{
	//u32 value;
	int i;

	printf("Registers:\n");
	printf("\t MUXPAD0: 0x%08x\n", rtd_inl(ISO_MUXPAD0));
	printf("\t MUXPAD1: 0x%08x\n", rtd_inl(ISO_MUXPAD1));
	printf("\t MUXPAD2: 0x%08x\n", rtd_inl(ISO_MUXPAD2));
	printf("\t PWM_OCD: 0x%08x\n", rtd_inl(ISO_PWM_OCD));
	printf("\t PWM_CD:  0x%08x\n", rtd_inl(ISO_PWM_CD));
	printf("\t PWM_CSD: 0x%08x\n", rtd_inl(ISO_PWM_CSD));

	for (i = 0; i < NUM_PWM; i++) {
		printf("\nPWM %d:", i);
		printf("\t enable     %2d, \t out_freq %5d, \t duty_rate %3d\n", pc->enable[i], pc->out_freq[i], pc->duty_rate[i]);
		printf("\t clksrc_div %2d, \t clkout_div %3d, \t clk_duty  %3d\n", pc->clksrc_div[i], pc->clkout_div[i], pc->clk_duty[i]);
	}

	return 0;
}

#define ISO_MUXPAD0_PWM_FUNC	2
#define ISO_MUXPAD1_PWM_FUNC	2
#define ISO_MUXPAD2_PWM_FUNC	1
static void rtd129x_pwm_pin_mux(void)
{
	u32 value;

	#ifdef PWM_0_PIN_0
	value = rtd_inl(ISO_MUXPAD2);
	value &= ~ISO_MUXPAD2_iso_gpio_21_mask;
	value |= ISO_MUXPAD2_iso_gpio_21(ISO_MUXPAD2_PWM_FUNC);
	rtd_outl(ISO_MUXPAD2, value);
	#endif /* PWM_0_PIN_0 */

	#ifdef PWM_0_PIN_1
	value = rtd_inl(ISO_MUXPAD0);
	value &= ~ISO_MUXPAD0_etn_led_link_mask;
	value |= ISO_MUXPAD0_etn_led_link(ISO_MUXPAD0_PWM_FUNC);
	rtd_outl(ISO_MUXPAD0, value);
	#endif /* PWM_0_PIN_1 */

	#ifdef PWM_1_PIN_0
	value = rtd_inl(ISO_MUXPAD2);
	value &= ~ISO_MUXPAD2_iso_gpio_22_mask;
	value |= ISO_MUXPAD2_iso_gpio_22(ISO_MUXPAD2_PWM_FUNC);
	rtd_outl(ISO_MUXPAD2, value);
	#endif /* PWM_1_PIN_0 */

	#ifdef PWM_1_PIN_1
	value = rtd_inl(ISO_MUXPAD0);
	value &= ~ISO_MUXPAD0_etn_led_rxtx_mask;
	value |= ISO_MUXPAD0_etn_led_rxtx(ISO_MUXPAD0_PWM_FUNC);
	rtd_outl(ISO_MUXPAD0, value);
	#endif /* PWM_1_PIN_1 */

	#ifdef PWM_2_PIN_0
	value = rtd_inl(ISO_MUXPAD2);
	value &= ~ISO_MUXPAD2_iso_gpio_23_mask;
	value |= ISO_MUXPAD2_iso_gpio_23(ISO_MUXPAD2_PWM_FUNC);
	rtd_outl(ISO_MUXPAD2, value);
	#endif /* PWM_2_PIN_0 */

	#ifdef PWM_2_PIN_1
	value = rtd_inl(ISO_MUXPAD1);
	value &= ~ISO_MUXPAD1_nat_led_0_mask;
	value |= ISO_MUXPAD1_nat_led_0(ISO_MUXPAD1_PWM_FUNC);
	rtd_outl(ISO_MUXPAD1, value);
	#endif /* PWM_2_PIN_1 */

	#ifdef PWM_3_PIN_0
	value = rtd_inl(ISO_MUXPAD2);
	value &= ~ISO_MUXPAD2_iso_gpio_24_mask;
	value |= ISO_MUXPAD2_iso_gpio_24(ISO_MUXPAD2_PWM_FUNC);
	rtd_outl(ISO_MUXPAD2, value);
	#endif /* PWM_3_PIN_0 */

	#ifdef PWM_3_PIN_1
	value = rtd_inl(ISO_MUXPAD1);
	value &= ~ISO_MUXPAD1_nat_led_1_mask;
	value |= ISO_MUXPAD1_nat_led_1(ISO_MUXPAD1_PWM_FUNC);
	rtd_outl(ISO_MUXPAD1, value);
	#endif /* PWM_3_PIN_1 */
}

int rtd129x_pwm_init(void)
{
	//int ret=0;
	//u32 val=0;
	int i;
	DBG("--- debug : rtd129x_pwm_init ---- \n");

	pc = &rtd_pc;
	pc->base_freq = 27000000;

	for (i=0; i<NUM_PWM; i++) {
		pc->out_freq[i] = 0;
		pc->enable[i] = 0;
		pc->clkout_div[i] = RTK_PWM_OCD_MASK;
		pc->clksrc_div[i] = RTK_PWM_CSD_DEFAULT;
		set_real_freq_by_target_div(i, pc->clksrc_div[i], pc->clkout_div[i]);
		pc->clk_duty[i] = RTK_PWM_CD_DEFAULT;
		pc->duty_rate[i] = 0;
	}

	/* init pin mux reg */
	rtd129x_pwm_pin_mux();

	/* init PWM reg */
	for (i=0; i<NUM_PWM; i++) {
		DBG("--- debug : rtd129x_pwm_init - hwpwm=(%d) enable=(%d) duty_rate=(%d) clksrc_div=(%d) clkout_div=(%d)---  \n",
			i, pc->enable[i], pc->duty_rate[i], pc->clksrc_div[i], pc->clkout_div[i]);
		DBG("--- debug : rtd129x_pwm_init - defualt output frequence = %dHz ---  \n",
			pc->out_freq[i]);
		pwm_set_register(i);
	}

	DBG("--- debug : rtd129x_pwm_init --  done! !\n");
	
	return 0;
}
