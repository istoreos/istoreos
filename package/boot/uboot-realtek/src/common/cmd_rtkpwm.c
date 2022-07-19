/*
 * Control GPIO pins on the fly
 *
 * Copyright (c) 2008-2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <command.h>

#include <asm/arch/pwm.h>

enum pwm_cmd {
	PWM_INIT,
	PWM_SHOW,
	PWM_ENABLE,
	PWM_DUTY,
	PWM_FREQ,
};

static int do_pwm(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong id, value;
	//int ret;
	
	id = 0xdeadbeef;
	value = 0xdeadbeef;

	if (argc < 2)
		return CMD_RET_USAGE;

	switch (*argv[1]) {
	case 'i': /* init */
#ifdef CONFIG_RTD129X_PWM
		rtd129x_pwm_init();
#endif /* CONFIG_RTD129X_PWM */
		return 0;

	case 's': /* show */
#ifdef CONFIG_RTD129X_PWM
		rtd129x_pwm_show();
#endif /* CONFIG_RTD129X_PWM */
		return 0;

	case 'e': /* enable */
		if (argc >= 4) {
			id = simple_strtoul(argv[2], NULL, 10);
			value = simple_strtoul(argv[3], NULL, 10);
#ifdef CONFIG_RTD129X_PWM
			if (pwm_enable(id, value) == 0)
				return 0;
#endif /* CONFIG_RTD129X_PWM */
		}
		break;

	case 'd': /* duty */
		if (argc >= 4) {
			id = simple_strtoul(argv[2], NULL, 10);
			value = simple_strtoul(argv[3], NULL, 10);
#ifdef CONFIG_RTD129X_PWM
			if (pwm_set_duty_rate(id, value) == 0)
				return 0;
#endif /* CONFIG_RTD129X_PWM */
		} else if (argc == 3) {
			id = simple_strtoul(argv[2], NULL, 10);
#ifdef CONFIG_RTD129X_PWM
			if (pwm_get_duty_rate(id, &value) == 0) {
				printf("PWM %d duty rate %d%%\n", id, value);
				return 0;
			}
#endif /* CONFIG_RTD129X_PWM */
		}
		break;
	case 'f': /* freq */
		if (argc >= 4) {
			id = simple_strtoul(argv[2], NULL, 10);
			value = simple_strtoul(argv[3], NULL, 10);
#ifdef CONFIG_RTD129X_PWM
			if (pwm_set_freq(id, value) == 0)
				return 0;
#endif /* CONFIG_RTD129X_PWM */
		} else if (argc == 3) {
			id = simple_strtoul(argv[2], NULL, 10);
#ifdef CONFIG_RTD129X_PWM
			if (pwm_get_freq(id, &value) == 0) {
				printf("PWM %d output frequency %d HZ\n", id, value);
				return 0;
			}
#endif /* CONFIG_RTD129X_PWM */
		}
	}
	
	printf("\nid 0x%lx, value 0x%lx\n\n", id, value); /* [-Werror=unused-but-set-variable] */

	return CMD_RET_USAGE;
}

U_BOOT_CMD(pwm, 4, 0, do_pwm,
	"Control PWM 0,1,2,3",
	"\t init                      --- set pin mux and PWM initial values\n"
	"\t show                      --- show current setting of PWM 0 ~ 3\n"
	"\t enable <ID> <1|0>         --- turn on/off PWM <ID>\n"
	"\t duty <ID> [<duty_rate>]   --- get/set duty rate of PWM <ID>\n"
	"\t freq <ID> [<target freq>] --- get/set target frequency of PWM <ID>\n"
	"Parameters:\n"
	"\t ID : <0-3>\n"
	"\t duty_rate : <0-100>\n"
	"\t freq : <1-52735>\n");

