/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <adc.h>
#include <console.h>
#include <dm.h>
#include <key.h>
#include <misc.h>
#include <rc.h>
#ifdef CONFIG_IRQ
#include <irq-generic.h>
#include <rk_timer_irq.h>
#endif
#include <asm/io.h>
#include <linux/input.h>
#include "test-rockchip.h"

#ifdef CONFIG_IRQ
/* Must use volatile to avoid being optimized by complier */
static int volatile irq_exit;
static ulong seconds;

static void timer_irq_handler(int irq, void *data)
{
	int period;

	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	period = get_timer(seconds);
	printf("    Hello, this is timer isr: irq=%d, period=%dms\n", irq, period);

	irq_exit = 1;
}

static int timer_interrupt_test(void)
{
	printf("Timer interrupt:\n");

	/* Disable before config */
	writel(0, TIMER_BASE + TIMER_CTRL);

	/* Configure 1s */
	writel(COUNTER_FREQUENCY, TIMER_BASE + TIMER_LOAD_COUNT0);
	writel(0, TIMER_BASE + TIMER_LOAD_COUNT1);
	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	writel(TIMER_EN | TIMER_INT_EN, TIMER_BASE + TIMER_CTRL);

	/* Request irq */
	irq_install_handler(TIMER_IRQ, timer_irq_handler, NULL);
	irq_handler_enable(TIMER_IRQ);

	irq_exit = 0;
	seconds = get_timer(0);
	while (!irq_exit)
		;

	irq_free_handler(TIMER_IRQ);

	return 0;
}
#endif

static void timer_delay_test(void)
{
	ulong delay = 100, delta;
	u64 start;

	printf("Timer delay:\n");

	start = get_ticks();
	udelay(delay);
	delta = (get_ticks() - start) / 24UL;
	printf("    Set %4luus, real %4luus\n", delay, delta);

	start = get_ticks();
	mdelay(delay);
	delta = (get_ticks() - start) / 24000UL;
	printf("    Set %4lums, real %4lums\n", delay, delta);

	start = get_ticks();
	mdelay(delay * 10UL);
	delta = (get_ticks() - start) / 24000UL;
	printf("    Set %4lums, real %4lums\n\n", delay * 10UL, delta);
}

int do_test_timer(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	timer_delay_test();

#ifdef CONFIG_IRQ
	timer_interrupt_test();
#endif
	return 0;
}

#ifdef CONFIG_RK_IR
static int ir_test(void)
{
	struct udevice *dev;
	int keycode, repeat;
	int last_keycode;
	int last_repeat;
	ulong start;
	int ret;

	printf("\nYou have 30s to test ir, press them, start!\n");

	ret = uclass_get_device(UCLASS_RC, 0, &dev);
	if (ret) {
		ut_err("ir: failed to get device, ret=%d\n", ret);
		goto out;
	}

	keycode = rc_get_keycode(dev);
	if (keycode == -ENOSYS) {
		ut_err("ir: failed to bind driver\n");
		goto out;
	}

	last_keycode = KEY_RESERVED;
	last_repeat = KEY_RESERVED;
	start = get_timer(0);
	while (get_timer(start) <= 30000) {
		mdelay(100);

		keycode = rc_get_keycode(dev);
		repeat = rc_get_repeat(dev);
		if (keycode == KEY_RESERVED)
			continue;

		if (keycode != last_keycode || repeat != last_repeat) {
			printf("ir: press key:0x%x repeat:%d\n",
			       keycode, repeat);
			last_keycode = keycode;
			last_repeat = repeat;
		}
	}

	return 0;

out:
	return -EINVAL;
}

int do_test_ir(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	return ir_test();
}
#endif

#ifdef CONFIG_DM_KEY
int do_test_key(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	struct dm_key_uclass_platdata *key;
	struct udevice *dev;
	struct uclass *uc;
	int ret, evt;

	ret = uclass_get(UCLASS_KEY, &uc);
	if (ret)
		return ret;

	printf("Please press any key button...\n");
	while (!ctrlc()) {
		for (uclass_first_device(UCLASS_KEY, &dev);
		     dev;
		     uclass_next_device(&dev)) {
			key = dev_get_uclass_platdata(dev);
			evt = key_read(key->code);
			if (evt == KEY_PRESS_DOWN)
				printf("'%s' key pressed...\n", key->name);
			else if (evt == KEY_PRESS_LONG_DOWN)
				printf("'%s' key long pressed...\n", key->name);

			mdelay(25);
		}
	}

	return 0;
}
#endif

#ifdef CONFIG_DM_CRYPTO
static int do_test_crypto(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	return run_command("crypto", 0);
}
#endif

#ifdef CONFIG_ADC
static int do_test_adc(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	uint val, chn;
	int ret;

	chn = argc < 2 ? 0 : strtoul(argv[1], NULL, 10);
	ret = adc_channel_single_shot("saradc", chn, &val);
	if (ret)
		ut_err("adc: failed to get channel%d value, ret=%d\n", chn, ret);

	printf("adc channel%d: adc value is %d\n", chn, val);

	return ret;
}
#endif

static cmd_tbl_t sub_cmd[] = {
#ifdef CONFIG_DM_CRYPTO
	UNIT_CMD_DEFINE(crypto, 0),
#endif
#ifdef CONFIG_RK_IR
	UNIT_CMD_ATTR_DEFINE(ir, 0, CMD_FLG_INTERACTIVE),
#endif
#ifdef CONFIG_DM_KEY
	UNIT_CMD_ATTR_DEFINE(key, 0, CMD_FLG_INTERACTIVE),
#endif
#ifdef CONFIG_ADC
	UNIT_CMD_DEFINE(adc, 0),
#endif
#ifdef CONFIG_IRQ
	UNIT_CMD_DEFINE(timer, 0),
#endif
};

static const char sub_cmd_help[] =
#ifdef CONFIG_DM_CRYPTO
"    [.] rktest crypto                      - test crypto\n"
#endif
#ifdef CONFIG_RK_IR
"    [i] rktest ir                          - test pwm ir remoter\n"
#endif
#ifdef CONFIG_DM_KEY
"    [i] rktest key                         - test key buttons\n"
#endif
#ifdef CONFIG_ADC
"    [.] rktest adc [chn]                   - test adc channel\n"
#endif
#ifdef CONFIG_IRQ
"    [.] rktest timer                       - test timer and interrupt\n"
#endif
;

const struct cmd_group cmd_grp_misc = {
	.id	= TEST_ID_MISC,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
