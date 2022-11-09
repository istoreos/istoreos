/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <adc.h>
#include <dm.h>
#include <key.h>
#include <dm/lists.h>
#include <irq-generic.h>

#define KEY_WARN(fmt, args...)	printf("Key Warn: "fmt, ##args)
#define KEY_ERR(fmt, args...)	printf("Key Error: "fmt, ##args)
#define KEY_DBG(fmt, args...)	 debug("Key Debug: "fmt, ##args)

static inline uint64_t arch_counter_get_cntpct(void)
{
	uint64_t cval = 0;

	isb();
#ifdef CONFIG_ARM64
	asm volatile("mrs %0, cntpct_el0" : "=r" (cval));
#else
	asm volatile("mrrc p15, 0, %Q0, %R0, c14" : "=r" (cval));
#endif
	return cval;
}

uint64_t key_timer(uint64_t base)
{
	uint64_t cntpct;

	cntpct = arch_counter_get_cntpct() / 24000UL;
	return (cntpct > base) ? (cntpct - base) : 0;
}

static int key_adc_event(struct dm_key_uclass_platdata *uc_key, int adcval)
{
	return (adcval <= uc_key->max && adcval >= uc_key->min) ?
		KEY_PRESS_DOWN : KEY_PRESS_NONE;
}

static int key_gpio_event(struct dm_key_uclass_platdata *uc_key)
{
	if (!dm_gpio_is_valid(&uc_key->gpio)) {
		KEY_ERR("'%s' Invalid gpio\n", uc_key->name);
		return KEY_PRESS_NONE;
	}

	return dm_gpio_get_value(&uc_key->gpio) ?
	       KEY_PRESS_DOWN : KEY_PRESS_NONE;
}

static int key_gpio_interrupt_event(struct dm_key_uclass_platdata *uc_key)
{
	int event;

	debug("%s: %s: up=%llu, down=%llu, delta=%llu\n",
	      __func__, uc_key->name, uc_key->rise_ms, uc_key->fall_ms,
	      uc_key->rise_ms - uc_key->fall_ms);

	/* Possible this is machine power-on long pressed, so ignore this */
	if (uc_key->fall_ms == 0 && uc_key->rise_ms != 0) {
		event = KEY_PRESS_NONE;
		goto out;
	}

	if ((uc_key->rise_ms > uc_key->fall_ms) &&
	    (uc_key->rise_ms - uc_key->fall_ms) >= KEY_LONG_DOWN_MS) {
		uc_key->rise_ms = 0;
		uc_key->fall_ms = 0;
		event = KEY_PRESS_LONG_DOWN;
		KEY_DBG("%s key long pressed..\n", uc_key->name);
	} else if (uc_key->fall_ms &&
		   key_timer(uc_key->fall_ms) >= KEY_LONG_DOWN_MS) {
		uc_key->rise_ms = 0;
		uc_key->fall_ms = 0;
		event = KEY_PRESS_LONG_DOWN;
		KEY_DBG("%s key long pressed(hold)..\n", uc_key->name);
	} else if ((uc_key->rise_ms > uc_key->fall_ms) &&
		   (uc_key->rise_ms - uc_key->fall_ms) < KEY_LONG_DOWN_MS) {
		uc_key->rise_ms = 0;
		uc_key->fall_ms = 0;
		event = KEY_PRESS_DOWN;
		KEY_DBG("%s key short pressed..\n", uc_key->name);
	/* Possible in charge animation, we enable irq after fuel gauge updated */
	} else if (uc_key->rise_ms && uc_key->fall_ms &&
		   (uc_key->rise_ms == uc_key->fall_ms)) {
		uc_key->rise_ms = 0;
		uc_key->fall_ms = 0;
		event = KEY_PRESS_DOWN;
		KEY_DBG("%s key short pressed..\n", uc_key->name);
	} else {
		event = KEY_PRESS_NONE;
	}

out:
	return event;
}

int key_is_pressed(int event)
{
	return (event == KEY_PRESS_DOWN || event == KEY_PRESS_LONG_DOWN);
}

static int key_core_read(struct dm_key_uclass_platdata *uc_key)
{
	unsigned int adcval;

	if (uc_key->type == ADC_KEY) {
		if (adc_channel_single_shot("saradc",
					    uc_key->channel, &adcval)) {
			KEY_ERR("%s failed to read saradc\n", uc_key->name);
			return KEY_NOT_EXIST;
		}

		return key_adc_event(uc_key, adcval);
	}

	return (uc_key->code == KEY_POWER) ?
		key_gpio_interrupt_event(uc_key) :
		key_gpio_event(uc_key);
}

int key_read(int code)
{
	struct dm_key_uclass_platdata *uc_key;
	struct udevice *dev;
	struct uclass *uc;
	bool allow_pre_reloc = false;
	int ret, event = KEY_NOT_EXIST;

	ret = uclass_get(UCLASS_KEY, &uc);
	if (ret)
		return ret;

try_again:
	for (uclass_first_device(UCLASS_KEY, &dev);
	     dev;
	     uclass_next_device(&dev)) {
		uc_key = dev_get_uclass_platdata(dev);

		if (!allow_pre_reloc && uc_key->pre_reloc)
			continue;

		if (uc_key->code != code)
			continue;

		event = key_core_read(uc_key);
		if (key_is_pressed(event))
			return event;
	}

	/* If not find valid key node from kernel, try from u-boot */
	if (event == KEY_NOT_EXIST && !allow_pre_reloc) {
		allow_pre_reloc = true;
		goto try_again;
	}

	return event;
}

#if CONFIG_IS_ENABLED(IRQ)
#if defined(CONFIG_PWRKEY_DNL_TRIGGER_NUM) && \
		(CONFIG_PWRKEY_DNL_TRIGGER_NUM > 0)
static void power_key_download(struct dm_key_uclass_platdata *uc_key)
{
	int trig_cnt = CONFIG_PWRKEY_DNL_TRIGGER_NUM;
	static u64 old_rise_ms;

	if (uc_key->code == KEY_POWER && old_rise_ms != uc_key->rise_ms) {
		old_rise_ms = uc_key->rise_ms;
		uc_key->trig_cnt++;
		if (uc_key->trig_cnt >= trig_cnt) {
			printf("\nEnter download mode by pwrkey\n");
			irq_handler_disable(uc_key->irq);
			run_command("rockusb 0 $devtype $devnum", 0);
			run_command("rbrom", 0);
		}
	}
}

int pwrkey_download_init(void)
{
	return (KEY_NOT_EXIST == key_read(KEY_POWER));
}
#endif

static void gpio_irq_handler(int irq, void *data)
{
	struct udevice *dev = data;
	struct dm_key_uclass_platdata *uc_key = dev_get_uclass_platdata(dev);

	if (uc_key->irq != irq)
		return;

	if (uc_key->irq_thread) {
		uc_key->irq_thread(irq, data);
	} else {
		if (irq_get_gpio_level(irq)) {
			uc_key->rise_ms = key_timer(0);
			KEY_DBG("%s: key dn: %llu ms\n",
				uc_key->name, uc_key->fall_ms);
		} else {
			uc_key->fall_ms = key_timer(0);
			KEY_DBG("%s: key up: %llu ms\n",
				uc_key->name, uc_key->rise_ms);
		}

		/* Must delay */
		mdelay(10);
		irq_revert_irq_type(irq);
	}

	/* Hook event: enter download mode by pwrkey */
#if defined(CONFIG_PWRKEY_DNL_TRIGGER_NUM) && \
		(CONFIG_PWRKEY_DNL_TRIGGER_NUM > 0)
	power_key_download(uc_key);
#endif
}
#endif

int key_bind_children(struct udevice *dev, const char *drv_name)
{
	const char *name;
	ofnode node;
	int ret;

	dev_for_each_subnode(node, dev) {
		/*
		 * If this node has "compatible" property, this is not
		 * a amp subnode, but a normal device. skip.
		 */
		ofnode_get_property(node, "compatible", &ret);
		if (ret >= 0)
			continue;

		if (ret != -FDT_ERR_NOTFOUND)
			return ret;

		name = ofnode_get_name(node);
		if (!name)
			return -EINVAL;
		ret = device_bind_driver_to_node(dev, drv_name, name,
						 node, NULL);
		if (ret)
			return ret;
	}

	return 0;
}

static int key_post_probe(struct udevice *dev)
{
	struct dm_key_uclass_platdata *uc_key;
	int ret;
#ifdef CONFIG_SARADC_ROCKCHIP_V2
	int margin = 120;
#else
	int margin = 30;
#endif
	uc_key = dev_get_uclass_platdata(dev);
	if (!uc_key)
		return -ENXIO;

	/* True from U-Boot key node */
	uc_key->pre_reloc = dev_read_bool(dev, "u-boot,dm-pre-reloc") ||
			    dev_read_bool(dev, "u-boot,dm-spl");

	if (uc_key->type == ADC_KEY) {
		uc_key->max = uc_key->adcval + margin;
		uc_key->min = uc_key->adcval > margin ?
					uc_key->adcval - margin : 0;
	} else {
		if (uc_key->code == KEY_POWER) {
#if CONFIG_IS_ENABLED(IRQ)
			int irq;

			if (uc_key->skip_irq_init)
				return 0;

			irq = phandle_gpio_to_irq(uc_key->gpios[0],
						  uc_key->gpios[1]);
			if (irq < 0) {
				KEY_ERR("%s: failed to request irq, ret=%d\n",
					uc_key->name, irq);
				return irq;
			}

			if (uc_key->code != KEY_POWER && uc_key->irq_thread) {
				KEY_WARN("%s: only power key can request irq thread\n",
					 uc_key->name);
				return -EINVAL;
			}

			uc_key->irq = irq;
			irq_install_handler(irq, gpio_irq_handler, dev);
			irq_set_irq_type(irq, IRQ_TYPE_EDGE_FALLING);
			irq_handler_enable(irq);
#else
			KEY_WARN("%s: no IRQ framework available\n", uc_key->name);
#endif
		} else {
			ret = gpio_request_by_name(dev, "gpios", 0,
						   &uc_key->gpio, GPIOD_IS_IN);
			if (ret) {
				KEY_ERR("%s: failed to request gpio, ret=%d\n",
					uc_key->name, ret);
				return ret;
			}
		}
	}

#ifdef DEBUG
	printf("[%s] (%s, %s, %s):\n", uc_key->name,
	       uc_key->type == ADC_KEY ? "ADC" : "GPIO",
	       uc_key->pre_reloc ? "U-Boot" : "Kernel",
	       dev->parent->name);

	if (uc_key->type == ADC_KEY) {
		printf("    adcval: %d (%d, %d)\n", uc_key->adcval,
		       uc_key->min, uc_key->max);
		printf("   channel: %d\n\n", uc_key->channel);
	} else {
		const char *gpio_name =
		     ofnode_get_name(ofnode_get_by_phandle(uc_key->gpios[0]));

		printf("       irq: %d\n", uc_key->irq);
		printf("   gpio[0]: %s\n", gpio_name);
		printf("   gpio[1]: %d\n\n", uc_key->gpios[1]);
	}
#endif

	return 0;
}

UCLASS_DRIVER(key) = {
	.id		= UCLASS_KEY,
	.name		= "key",
	.post_probe	= key_post_probe,
	.per_device_platdata_auto_alloc_size =
			sizeof(struct dm_key_uclass_platdata),
};
