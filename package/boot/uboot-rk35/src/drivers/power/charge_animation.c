/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/io.h>
#include <common.h>
#include <boot_rkimg.h>
#include <console.h>
#include <dm.h>
#include <errno.h>
#include <key.h>
#include <led.h>
#include <rtc.h>
#include <pwm.h>
#include <asm/arch-rockchip/rockchip_smccc.h>
#include <asm/suspend.h>
#include <linux/input.h>
#include <power/charge_display.h>
#include <power/charge_animation.h>
#include <power/rockchip_pm.h>
#include <power/fuel_gauge.h>
#include <power/pmic.h>
#include <power/rk8xx_pmic.h>
#include <power/regulator.h>
#include <video_rockchip.h>
#ifdef CONFIG_IRQ
#include <irq-generic.h>
#include <rk_timer_irq.h>
#endif
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
#include <rk_eink.h>
#endif
DECLARE_GLOBAL_DATA_PTR;

#define IMAGE_RESET_IDX				-1
#define IMAGE_SOC_100_IDX(n)			((n) - 2)
#define IMAGE_LOWPOWER_IDX(n)			((n) - 1)
#define SYSTEM_SUSPEND_DELAY_MS			5000
#define FUEL_GAUGE_POLL_MS			1000

#define LED_CHARGING_NAME			"battery_charging"
#define LED_CHARGING_FULL_NAME			"battery_full"

struct charge_image {
	const char *name;
	int soc;
	int period;	/* ms */
};

struct charge_animation_priv {
	struct udevice *pmic;
	struct udevice *fg;
	struct udevice *charger;
	struct udevice *rtc;
#ifdef CONFIG_LED
	struct udevice *led_charging;
	struct udevice *led_full;
#endif
	const struct charge_image *image;
	int image_num;

	int auto_wakeup_key_state;
	ulong auto_screen_off_timeout;	/* ms */
	ulong suspend_delay_timeout;	/* ms */
};

/*
 * IF you want to use your own charge images, please:
 *
 * 1. Update the following 'image[]' to point to your own images;
 * 2. You must set the failed image as last one and soc = -1 !!!
 */
static const struct charge_image image[] = {
	{ .name = "battery_0.bmp", .soc = 5, .period = 600 },
	{ .name = "battery_1.bmp", .soc = 20, .period = 600 },
	{ .name = "battery_2.bmp", .soc = 40, .period = 600 },
	{ .name = "battery_3.bmp", .soc = 60, .period = 600 },
	{ .name = "battery_4.bmp", .soc = 80, .period = 600 },
	{ .name = "battery_5.bmp", .soc = 100, .period = 600 },
	{ .name = "battery_fail.bmp", .soc = -1, .period = 1000 },
};

static int charge_animation_ofdata_to_platdata(struct udevice *dev)
{
	struct charge_animation_pdata *pdata = dev_get_platdata(dev);

	/* charge mode */
	pdata->uboot_charge =
		dev_read_u32_default(dev, "rockchip,uboot-charge-on", 0);
	pdata->android_charge =
		dev_read_u32_default(dev, "rockchip,android-charge-on", 0);

	pdata->auto_exit_charge =
		dev_read_u32_default(dev, "rockchip,uboot-exit-charge-auto", 0);
	pdata->exit_charge_level =
		dev_read_u32_default(dev, "rockchip,uboot-exit-charge-level", 0);
	pdata->exit_charge_voltage =
		dev_read_u32_default(dev, "rockchip,uboot-exit-charge-voltage", 0);

	pdata->low_power_voltage =
		dev_read_u32_default(dev, "rockchip,uboot-low-power-voltage", 0);

	pdata->screen_on_voltage =
		dev_read_u32_default(dev, "rockchip,screen-on-voltage", 0);
	pdata->system_suspend =
		dev_read_u32_default(dev, "rockchip,system-suspend", 0);

	pdata->auto_wakeup_interval =
		dev_read_u32_default(dev, "rockchip,auto-wakeup-interval", 0);
	pdata->auto_wakeup_screen_invert =
		dev_read_u32_default(dev, "rockchip,auto-wakeup-screen-invert", 0);

	pdata->auto_off_screen_interval =
		dev_read_u32_default(dev, "rockchip,auto-off-screen-interval", 15);

	if (pdata->screen_on_voltage > pdata->exit_charge_voltage)
		pdata->screen_on_voltage = pdata->exit_charge_voltage;

	if (pdata->auto_exit_charge && !pdata->auto_wakeup_interval)
		pdata->auto_wakeup_interval = 10;

	debug("mode: uboot=%d, android=%d; exit: soc=%d%%, voltage=%dmv;\n"
	      "lp_voltage=%d%%, screen_on=%dmv\n",
	      pdata->uboot_charge, pdata->android_charge,
	      pdata->exit_charge_level, pdata->exit_charge_voltage,
	      pdata->low_power_voltage, pdata->screen_on_voltage);

	return 0;
}

static int check_key_press(struct udevice *dev)
{
	struct charge_animation_pdata *pdata = dev_get_platdata(dev);
	struct charge_animation_priv *priv = dev_get_priv(dev);
	u32 state, rtc_state = 0;

#ifdef CONFIG_DM_RTC
	if (priv->rtc)
		rtc_state = rtc_alarm_trigger(priv->rtc);
#endif
	if (rtc_state) {
		printf("rtc alarm trigger...\n");
		return KEY_PRESS_LONG_DOWN;
	}

	state = key_read(KEY_POWER);
	if (state < 0)
		printf("read power key failed: %d\n", state);
	else if (state == KEY_PRESS_DOWN)
		printf("power key pressed...\n");
	else if (state == KEY_PRESS_LONG_DOWN)
		printf("power key long pressed...\n");

	/* Fixup key state for following cases */
	if (pdata->auto_wakeup_interval) {
		if (pdata->auto_wakeup_screen_invert) {
			if (priv->auto_wakeup_key_state == KEY_PRESS_DOWN) {
				/* Value is updated in timer interrupt */
				priv->auto_wakeup_key_state = KEY_PRESS_NONE;
				state = KEY_PRESS_DOWN;
			}
		}
	}
	if (!pdata->auto_wakeup_screen_invert &&
	    pdata->auto_off_screen_interval) {
		if (priv->auto_screen_off_timeout &&
		    get_timer(priv->auto_screen_off_timeout) >
		    pdata->auto_off_screen_interval * 1000) {	/* 1000ms */
			state = KEY_PRESS_DOWN;
			printf("Auto screen off\n");
		}
	}

	return state;
}

/*
 * If not enable CONFIG_IRQ, cpu can't suspend to ATF or wfi, so that wakeup
 * period timer is useless.
 */
#if !defined(CONFIG_IRQ) || !defined(CONFIG_ARM_CPU_SUSPEND)
static int system_suspend_enter(struct udevice *dev)
{
	return 0;
}

static void autowakeup_timer_init(struct udevice *dev, uint32_t seconds) {}
static void autowakeup_timer_uninit(void) {}

#else
static int system_suspend_enter(struct udevice *dev)
{
	struct charge_animation_pdata *pdata = dev_get_platdata(dev);
	struct charge_animation_priv *priv = dev_get_priv(dev);

	/*
	 * When cpu is in wfi and we try to give a long key press event without
	 * key release, cpu would wakeup and enter wfi again immediately. So
	 * here is the problem: cpu can only wakeup when long key released.
	 *
	 * Actually, we want cpu can detect long key event without key release,
	 * so we give a suspend delay timeout for cpu to detect this.
	 */
	if (priv->suspend_delay_timeout &&
	    get_timer(priv->suspend_delay_timeout) <= SYSTEM_SUSPEND_DELAY_MS)
		return 0;

	if (pdata->system_suspend && IS_ENABLED(CONFIG_ARM_SMCCC)) {
		printf("\nSystem suspend: ");
		putc('0');
		local_irq_disable();
		putc('1');
		regulators_enable_state_mem(false);
		putc('2');
		pmic_suspend(priv->pmic);
		putc('3');
		irqs_suspend();
		putc('4');
		device_suspend();
		putc('5');
		putc('\n');

		/* Trap into ATF for low power mode */
		cpu_suspend(0, psci_system_suspend);

		putc('\n');
		putc('4');
		device_resume();
		putc('3');
		irqs_resume();
		putc('2');
		pmic_resume(priv->pmic);
		putc('1');
		local_irq_enable();
		putc('0');
		putc('\n');
	} else {
		irqs_suspend();
		printf("\nWfi\n");
		wfi();
		putc('1');
		irqs_resume();
	}

	priv->suspend_delay_timeout = get_timer(0);

	/*
	 * We must wait for key release event finish, otherwise
	 * we may read key state too early.
	 */
	mdelay(300);

	return 0;
}

static void timer_irq_handler(int irq, void *data)
{
	struct udevice *dev = data;
	struct charge_animation_priv *priv = dev_get_priv(dev);
	static long long count;

	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);

	priv->auto_wakeup_key_state = KEY_PRESS_DOWN;
	printf("auto wakeup count: %lld\n", ++count);
}

static void autowakeup_timer_init(struct udevice *dev, uint32_t seconds)
{
	uint64_t period = 24000000ULL * seconds;

	/* Disable before conifg */
	writel(0, TIMER_BASE + TIMER_CTRL);

	/* Config */
	writel((uint32_t)period, TIMER_BASE + TIMER_LOAD_COUNT0);
	writel((uint32_t)(period >> 32), TIMER_BASE + TIMER_LOAD_COUNT1);
	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	writel(TIMER_EN | TIMER_INT_EN, TIMER_BASE + TIMER_CTRL);

	/* IRQ */
	irq_install_handler(TIMER_IRQ, timer_irq_handler, dev);
	irq_handler_enable(TIMER_IRQ);
}

static void autowakeup_timer_uninit(void)
{
	writel(0, TIMER_BASE + TIMER_CTRL);

	irq_handler_disable(TIMER_IRQ);
	irq_free_handler(TIMER_IRQ);
}
#endif

#ifdef CONFIG_DRM_ROCKCHIP
static void charge_show_bmp(const char *name)
{
	rockchip_show_bmp(name);
}

static void charge_show_logo(void)
{
	rockchip_show_logo();
}
#else
static void charge_show_bmp(const char *name) {}
static void charge_show_logo(void) {}
#endif

#ifdef CONFIG_LED
static int leds_update(struct udevice *dev, int soc)
{
	struct charge_animation_priv *priv = dev_get_priv(dev);
	static int old_soc = -1;
	int ret, ledst;

	if (old_soc == soc)
		return 0;

	old_soc = soc;
	if (priv->led_charging) {
		ledst = (soc < 100) ? LEDST_ON : LEDST_OFF;
		ret = led_set_state(priv->led_charging, ledst);
		if (ret) {
			printf("set charging led %s failed, ret=%d\n",
			       (ledst == LEDST_ON) ? "ON" : "OFF", ret);
			return ret;
		}
	}

	if (priv->led_full) {
		ledst = (soc == 100) ? LEDST_ON : LEDST_OFF;
		ret = led_set_state(priv->led_full, ledst);
		if (ret) {
			printf("set charging full led %s failed, ret=%d\n",
			       ledst == LEDST_ON ? "ON" : "OFF", ret);
			return ret;
		}
	}

	return 0;
}
#else
static int leds_update(struct udevice *dev, int soc) { return 0; }
#endif

static int fg_charger_get_chrg_online(struct udevice *dev)
{
	struct charge_animation_priv *priv = dev_get_priv(dev);
	struct udevice *charger;

	charger = priv->charger ? : priv->fg;

	return fuel_gauge_get_chrg_online(charger);
}

static int charge_extrem_low_power(struct udevice *dev)
{
	struct charge_animation_pdata *pdata = dev_get_platdata(dev);
	struct charge_animation_priv *priv = dev_get_priv(dev);
	struct udevice *pmic = priv->pmic;
	struct udevice *fg = priv->fg;
	int voltage, soc, charging = 1;
	static int timer_initialized;
	int ret;

	voltage = fuel_gauge_get_voltage(fg);
	if (voltage < 0)
		return -EINVAL;

	while (voltage < pdata->low_power_voltage + 50) {
		/* Check charger online */
		charging = fg_charger_get_chrg_online(dev);
		if (charging <= 0) {
			printf("%s: Not charging, online=%d. Shutdown...\n",
			       __func__, charging);
			/* wait uart flush before shutdown */
			mdelay(5);
			/* PMIC shutdown */
			pmic_shutdown(pmic);

			printf("Cpu should never reach here, shutdown failed !\n");
			continue;
		}

		/* Enable auto wakeup */
		if (!timer_initialized) {
			timer_initialized = 1;
			autowakeup_timer_init(dev, 5);
		}

		/*
		 * Just for fuel gauge to update something important,
		 * including charge current, coulometer or other.
		 */
		soc = fuel_gauge_update_get_soc(fg);
		if (soc < 0 || soc > 100) {
			printf("get soc failed: %d\n", soc);
			continue;
		}

		/* Update led */
		ret = leds_update(dev, soc);
		if (ret)
			printf("update led failed: %d\n", ret);

		printf("Extrem low power, force charging... threshold=%dmv, now=%dmv\n",
		       pdata->low_power_voltage, voltage);

		/* System suspend */
		system_suspend_enter(dev);

		/* Update voltage */
		voltage = fuel_gauge_get_voltage(fg);
		if (voltage < 0) {
			printf("get voltage failed: %d\n", voltage);
			continue;
		}

		if (ctrlc()) {
			printf("Extrem low charge: exit by ctrl+c\n");
			break;
		}
	}

	autowakeup_timer_uninit();

	return 0;
}

static int charge_animation_show(struct udevice *dev)
{
	struct charge_animation_pdata *pdata = dev_get_platdata(dev);
	struct charge_animation_priv *priv = dev_get_priv(dev);
	const struct charge_image *image = priv->image;
	struct udevice *pmic = priv->pmic;
	struct udevice *fg = priv->fg;
	const char *preboot = env_get("preboot");
	int image_num = priv->image_num;
	bool ever_lowpower_screen_off = false;
	bool screen_on = true;
	ulong show_start = 0, charge_start = 0, debug_start = 0;
	ulong delta;
	ulong ms = 0, sec = 0;
	int start_idx = 0, show_idx = -1, old_show_idx = IMAGE_RESET_IDX;
	int soc, voltage, current, key_state;
	int i, charging = 1, ret;
	int boot_mode;
	int first_poll_fg = 1;
	bool exit_charge = false;

/*
 * Check sequence:
 *
 * 1. Extrem low power charge?
 * 2. Preboot cmd?
 * 3. Valid boot mode?
 * 4. U-Boot charge enabled by dts config?
 * 5. Screen off before charge?
 * 6. Enter charge !
 *
 */
	if (!fuel_gauge_bat_is_exist(fg)) {
		printf("Exit charge: battery is not exist\n");
		return 0;
	}

	/* Extrem low power charge */
	ret = charge_extrem_low_power(dev);
	if (ret < 0) {
		printf("extrem low power charge failed, ret=%d\n", ret);
		return ret;
	}

	/* If there is preboot command, exit */
	if (preboot && !strstr(preboot, "dvfs")) {
		printf("Exit charge: due to preboot cmd '%s'\n", preboot);
		return 0;
	}

	/* Not valid charge mode, exit */
#ifdef CONFIG_RKIMG_BOOTLOADER
	boot_mode = rockchip_get_boot_mode();
	if ((boot_mode != BOOT_MODE_CHARGING) &&
	    (boot_mode != BOOT_MODE_UNDEFINE)) {
		printf("Exit charge: due to boot mode\n");
		return 0;
	}
#endif
	charging = fg_charger_get_chrg_online(dev);
	/* Not charger online and low power, shutdown */
	if (charging <= 0 && pdata->auto_exit_charge) {
		soc = fuel_gauge_update_get_soc(fg);
		voltage = fuel_gauge_get_voltage(fg);
		if (soc < pdata->exit_charge_level) {
			printf("soc(%d%%) < exit_charge_level(%d%%)\n",
			       soc, pdata->exit_charge_level);
			exit_charge = true;
		}
		if (voltage < pdata->exit_charge_voltage) {
			printf("voltage(%d) < exit_charge_voltage(%d)\n",
			       voltage, pdata->exit_charge_voltage);
			exit_charge = true;
		}
		if (exit_charge) {
			printf("Not charging and low power, Shutdown...\n");
			show_idx = IMAGE_LOWPOWER_IDX(image_num);
			charge_show_bmp(image[show_idx].name);
			mdelay(1000);
			pmic_shutdown(pmic);
		}
	}

	/* Not charger online, exit */
	if (charging <= 0) {
		printf("Exit charge: due to charger offline\n");
		return 0;
	}

	/* Enter android charge, set property for kernel */
	if (pdata->android_charge) {
		env_update("bootargs", "androidboot.mode=charger");
		printf("Android charge mode\n");
	}

	/* Not enable U-Boot charge, exit */
	if (!pdata->uboot_charge) {
		printf("Exit charge: due to not enable uboot charge\n");
		return 0;
	}

	voltage = fuel_gauge_get_voltage(fg);
	if (voltage < 0) {
		printf("get voltage failed: %d\n", voltage);
		return -EINVAL;
	}

	/* If low power, turn off screen */
	if (voltage <= pdata->screen_on_voltage + 50) {
		screen_on = false;
		ever_lowpower_screen_off = true;
		charge_show_bmp(NULL);
	}

	/* Auto wakeup */
	if (pdata->auto_wakeup_interval) {
		printf("Auto wakeup: %dS\n", pdata->auto_wakeup_interval);
		autowakeup_timer_init(dev, pdata->auto_wakeup_interval);
	}

/* Give a message warning when CONFIG_IRQ is not enabled */
#ifdef CONFIG_IRQ
	printf("Enter U-Boot charging mode\n");
#else
	printf("Enter U-Boot charging mode(without IRQ)\n");
#endif

	charge_start = get_timer(0);
	delta = get_timer(0);

	/* Charging ! */
	while (1) {
		/*
		 * At the most time, fuel gauge is usually a i2c device, we
		 * should avoid read/write all the time. We had better set
		 * poll seconds to update fuel gauge info.
		 */
		if (!first_poll_fg && get_timer(delta) < FUEL_GAUGE_POLL_MS)
			goto show_images;

		delta = get_timer(0);

		debug("step1 (%d)... \n", screen_on);

		/*
		 * Most fuel gauge is I2C interface, it shouldn't be interrupted
		 * during transfer. The power key event depends on interrupt, so
		 * we should disable local irq when update fuel gauge.
		 */
		local_irq_disable();

		/* Step1: Is charging now ? */
		charging = fg_charger_get_chrg_online(dev);
		if (charging <= 0) {
			printf("Not charging, online=%d. Shutdown...\n",
			       charging);
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
			/*
			 * If charger is plug out during charging, display poweroff
			 * image before device power off.
			 * Irq must be enable if CONFIG_IRQ is defined, because
			 * ebc need to wait irq to indicate frame is complete.
			 */
#ifdef CONFIG_IRQ
			local_irq_enable();
#endif
			ret = rockchip_eink_show_charge_logo(EINK_LOGO_POWEROFF);
			if (ret != 0)
				printf("Eink display reset logo failed\n");
#ifdef CONFIG_IRQ
			local_irq_disable();
#endif
#endif
			/* wait uart flush before shutdown */
			mdelay(5);

			/* PMIC shutdown */
			pmic_shutdown(pmic);

			printf("Cpu should never reach here, shutdown failed !\n");
			continue;
		}

		debug("step2 (%d)... show_idx=%d\n", screen_on, show_idx);

		/* Step2: get soc and voltage */
		soc = fuel_gauge_update_get_soc(fg);
		if (soc < 0 || soc > 100) {
			printf("get soc failed: %d\n", soc);
			continue;
		}

		voltage = fuel_gauge_get_voltage(fg);
		if (voltage < 0) {
			printf("get voltage failed: %d\n", voltage);
			continue;
		}

		current = fuel_gauge_get_current(fg);
		if (current == -ENOSYS) {
			printf("get current failed: %d\n", current);
			continue;
		}

		first_poll_fg = 0;
		local_irq_enable();

		if (pdata->auto_exit_charge) {
			/* Is able to boot now ? */
			if (pdata->exit_charge_level &&
			    soc >= pdata->exit_charge_level) {
				printf("soc(%d%%) exit charge animation...\n",
				       soc);
				break;
			}
			if (pdata->exit_charge_voltage &&
			    voltage >= pdata->exit_charge_voltage) {
				printf("vol(%d) exit charge animation...\n",
				       voltage);
				break;
			}
		}

show_images:
		/*
		 * Just for debug, otherwise there will be nothing output which
		 * is not good to know what happen.
		 */
		if (!debug_start)
			debug_start = get_timer(0);
		if (get_timer(debug_start) > 20000) {
			debug_start = get_timer(0);
			printf("[%8ld]: soc=%d%%, vol=%dmv, c=%dma, "
			       "online=%d, screen_on=%d\n",
			       get_timer(0)/1000, soc, voltage,
			       current, charging, screen_on);
		}

		/* Update leds */
		ret = leds_update(dev, soc);
		if (ret)
			printf("update led failed: %d\n", ret);

		/*
		 * If ever lowpower screen off, force screen_on=false, which
		 * means key event can't modify screen_on, only voltage higher
		 * then threshold can update screen_on=true;
		 */
		if (ever_lowpower_screen_off)
			screen_on = false;

		/*
		 * Auto turn on screen when voltage higher than Vol screen on.
		 * 'ever_lowpower_screen_off' means enter the while(1) loop with
		 * screen off.
		 */
		if ((ever_lowpower_screen_off) &&
		    (voltage > pdata->screen_on_voltage)) {
			ever_lowpower_screen_off = false;
			screen_on = true;
			show_idx = IMAGE_RESET_IDX;
		}

		/*
		 * IMAGE_RESET_IDX means show_idx show be update by start_idx.
		 * When short key pressed event trigged, we will set show_idx
		 * as IMAGE_RESET_IDX which updates images index from start_idx
		 * that calculate by current soc.
		 */
		if (show_idx == IMAGE_RESET_IDX) {
			for (i = 0; i < IMAGE_SOC_100_IDX(image_num); i++) {
				/* Find out which image we start to show */
				if ((soc >= image[i].soc) &&
				    (soc < image[i + 1].soc)) {
					start_idx = i;
					break;
				}

				if (soc >= 100) {
					start_idx = IMAGE_SOC_100_IDX(image_num);
					break;
				}
			}

			debug("%s: show_idx=%d, screen_on=%d\n",
			      __func__, show_idx, screen_on);

			/* Mark start index and start time */
			show_idx = start_idx;
			show_start = get_timer(0);
		}

		debug("step3 (%d)... show_idx=%d\n", screen_on, show_idx);

#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
		/*
		 * Device is auto wakeup from suspend, if it's eink display,
		 * screen will display the last image after suspend, so
		 * we should update the image to show the approximate
		 * battery power if battery is charging to next level.
		 */
		if (pdata->auto_wakeup_interval &&
		    priv->auto_wakeup_key_state == KEY_PRESS_DOWN &&
		    !screen_on) {
			if (soc >= image[old_show_idx + 1].soc &&
			    soc < 100) {
				int ret;
				int logo_type = EINK_LOGO_CHARGING_0;

				logo_type = logo_type << (old_show_idx + 1);
				ret = rockchip_eink_show_charge_logo(logo_type);
				/*
				 * only change the logic if eink is
				 * actually exist
				 */
				if (ret == 0) {
					printf("Update image id[%d] for eink\n",
					       old_show_idx + 1);
					old_show_idx++;
				}
			}
		}
		/*
		 * If battery capacity is charged to 100%, exit charging
		 * animation and boot android system.
		 */
		if (soc >= 100) {
			int ret;
			int logo_type = EINK_LOGO_CHARGING_5;

			ret = rockchip_eink_show_charge_logo(logo_type);
			/* Only change the logic if eink is acutally exist */
			if (ret == 0) {
				printf("battery FULL,exit charge animation\n");
				mdelay(20);
				break;
			}
		}
#endif
		/* Step3: show images */
		if (screen_on) {
			/* Don't call 'charge_show_bmp' unless image changed */
			if (old_show_idx != show_idx) {
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
				int logo_type = EINK_LOGO_CHARGING_0;

				rockchip_eink_show_charge_logo(logo_type <<
							       show_idx);
#endif
				old_show_idx = show_idx;
				debug("SHOW: %s\n", image[show_idx].name);
				charge_show_bmp(image[show_idx].name);
			}
			/* Re-calculate timeout to off screen */
			if (priv->auto_screen_off_timeout == 0)
				priv->auto_screen_off_timeout = get_timer(0);
		} else {
			priv->auto_screen_off_timeout = 0;
			system_suspend_enter(dev);
		}

		mdelay(5);

		/* Every image shows period */
		if (get_timer(show_start) > image[show_idx].period) {
			show_start = get_timer(0);
			/* Update to next image */
			show_idx++;
			if (show_idx > IMAGE_SOC_100_IDX(image_num))
				show_idx = IMAGE_RESET_IDX;
		}

		debug("step4 (%d)... \n", screen_on);

		/*
		 * Step4: check key event.
		 *
		 * Short key event: turn on/off screen;
		 * Long key event: show logo and boot system or still charging.
		 */
		key_state = check_key_press(dev);
		if (key_state == KEY_PRESS_DOWN) {
			/*
			 * Clear current image index, and show image
			 * from start_idx
			 */
			old_show_idx = IMAGE_RESET_IDX;
			show_idx = IMAGE_RESET_IDX;

			/*
			 *	Reverse the screen state
			 *
			 * If screen_on=false, means this short key pressed
			 * event turn on the screen and we need show images.
			 *
			 * If screen_on=true, means this short key pressed
			 * event turn off the screen and we never show images.
			 */
			if (screen_on) {
#ifdef CONFIG_ROCKCHIP_EINK_DISPLAY
				int type = EINK_LOGO_CHARGING_0 << start_idx;
				/*
				 * Show current battery capacity before suspend
				 * if it's eink display, because eink screen
				 * will continue to display the last image
				 * after suspend, so user can get the
				 * approximate capacity by image displayed.
				 */
				ret = rockchip_eink_show_charge_logo(type);
				/* only change the logic if eink display ok */
				if (ret == 0)
					old_show_idx = start_idx;
#endif
				charge_show_bmp(NULL); /* Turn off screen */
				screen_on = false;
				priv->suspend_delay_timeout = get_timer(0);
			} else {
				screen_on = true;
			}

			printf("screen %s\n", screen_on ? "on" : "off");
		} else if (key_state == KEY_PRESS_LONG_DOWN) {
			/* Set screen_on=true anyway when key long pressed */
			if (!screen_on)
				screen_on = true;

			printf("screen %s\n", screen_on ? "on" : "off");

			/* Is able to boot now ? */
			if (soc < pdata->exit_charge_level) {
				printf("soc=%d%%, threshold soc=%d%%\n",
				       soc, pdata->exit_charge_level);
				printf("Low power, unable to boot, charging...\n");
				show_idx = IMAGE_LOWPOWER_IDX(image_num);
				continue;
			}

			if (voltage < pdata->exit_charge_voltage) {
				printf("voltage=%dmv, threshold voltage=%dmv\n",
				       voltage, pdata->exit_charge_voltage);
				printf("Low power, unable to boot, charging...\n");
				show_idx = IMAGE_LOWPOWER_IDX(image_num);
				continue;
			}

			/* Success exit charging */
			printf("Exit charge animation...\n");
			charge_show_logo();
			break;
		} else {
			/* Do nothing */
		}

		debug("step5 (%d)... \n", screen_on);

		/* Step5: Exit by ctrl+c */
		if (ctrlc()) {
			if (voltage >= pdata->screen_on_voltage)
				charge_show_logo();
			printf("Exit charge, due to ctrl+c\n");
			break;
		}
	}

	if (pdata->auto_wakeup_interval)
		autowakeup_timer_uninit();

	ms = get_timer(charge_start);
	if (ms >= 1000) {
		sec = ms / 1000;
		ms = ms % 1000;
	}

	printf("charging time total: %lu.%lus, soc=%d%%, vol=%dmv\n",
	       sec, ms, soc, voltage);

	return 0;
}

static int fg_charger_get_device(struct udevice **fuel_gauge,
				 struct udevice **charger)
{
	struct udevice *dev;
	struct uclass *uc;
	int ret, cap;

	*fuel_gauge = NULL,
	*charger = NULL;

	ret = uclass_get(UCLASS_FG, &uc);
	if (ret)
		return ret;

	for (uclass_first_device(UCLASS_FG, &dev);
	     dev;
	     uclass_next_device(&dev)) {
		cap = fuel_gauge_capability(dev);
		if (cap == (FG_CAP_CHARGER | FG_CAP_FUEL_GAUGE)) {
			*fuel_gauge = dev;
			*charger = NULL;
		} else if (cap == FG_CAP_FUEL_GAUGE) {
			*fuel_gauge = dev;
		} else if (cap == FG_CAP_CHARGER) {
			*charger = dev;
		}
	}

	return (*fuel_gauge) ? 0 : -ENODEV;
}

static const struct dm_charge_display_ops charge_animation_ops = {
	.show = charge_animation_show,
};

static int charge_animation_probe(struct udevice *dev)
{
	struct charge_animation_priv *priv = dev_get_priv(dev);
	int ret, soc;

	/* Get PMIC: used for power off system  */
	ret = uclass_get_device(UCLASS_PMIC, 0, &priv->pmic);
	if (ret) {
		if (ret == -ENODEV)
			printf("Can't find PMIC\n");
		else
			printf("Get UCLASS PMIC failed: %d\n", ret);
		return ret;
	}

	/* Get fuel gauge and charger(If need) */
	ret = fg_charger_get_device(&priv->fg, &priv->charger);
	if (ret) {
		if (ret == -ENODEV)
			debug("Can't find FG\n");
		else
			debug("Get UCLASS FG failed: %d\n", ret);
		return ret;
	}

	/* Get rtc: used for power on */
	ret = uclass_get_device(UCLASS_RTC, 0, &priv->rtc);
	if (ret) {
		if (ret == -ENODEV)
			debug("Can't find RTC\n");
		else
			debug("Get UCLASS RTC failed: %d\n", ret);
	}

	/* Get PWRKEY: used for wakeup and turn off/on LCD */
	if (key_read(KEY_POWER) == KEY_NOT_EXIST) {
		debug("Can't find power key\n");
		return -EINVAL;
	}

	/* Initialize charge current */
	soc = fuel_gauge_update_get_soc(priv->fg);
	if (soc < 0 || soc > 100) {
		debug("get soc failed: %d\n", soc);
		return -EINVAL;
	}

	/* Get leds */
#ifdef CONFIG_LED
	ret = led_get_by_label(LED_CHARGING_NAME, &priv->led_charging);
	if (!ret)
		printf("Found Charging LED\n");
	ret = led_get_by_label(LED_CHARGING_FULL_NAME, &priv->led_full);
	if (!ret)
		printf("Found Charging-Full LED\n");
#endif

	/* Get charge images */
	priv->image = image;
	priv->image_num = ARRAY_SIZE(image);

	printf("Enable charge animation display\n");

	return 0;
}

static const struct udevice_id charge_animation_ids[] = {
	{ .compatible = "rockchip,uboot-charge" },
	{ },
};

U_BOOT_DRIVER(charge_animation) = {
	.name = "charge-animation",
	.id = UCLASS_CHARGE_DISPLAY,
	.probe = charge_animation_probe,
	.of_match = charge_animation_ids,
	.ops = &charge_animation_ops,
	.ofdata_to_platdata = charge_animation_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct charge_animation_pdata),
	.priv_auto_alloc_size = sizeof(struct charge_animation_priv),
};
