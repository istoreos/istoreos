/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <adc.h>
#include <asm/io.h>
#include <dm/ofnode.h>
#include <asm/arch-rockchip/resource_img.h>

#define is_digit(c)		((c) >= '0' && (c) <= '9')
#define is_abcd(c)		((c) >= 'a' && (c) <= 'd')
#define is_equal(c)		((c) == '=')
#define KEY_WORDS_ADC_CTRL	"#_"
#define KEY_WORDS_ADC_CH	"_ch"
#define KEY_WORDS_GPIO		"#gpio"
#define MAX_ADC_CH_NR		10
#define MAX_GPIO_NR		10

static fdt_addr_t gpio_base_addr[MAX_GPIO_NR];
static uint32_t gpio_record[MAX_GPIO_NR];
static int adc_record[MAX_ADC_CH_NR];

#ifdef CONFIG_ROCKCHIP_GPIO_V2
#define GPIO_SWPORT_DDR		0x08
#define GPIO_EXT_PORT		0x70
#define WMSK_SETBIT(n)		(n << 16 | n)
#define WMSK_CLRBIT(n)		(n << 16)
#define REG_PLUS4(off, n)	(off + (n >= BIT(16) ? 4 : 0))
#define BIT_SUB16(n)		(n >= BIT(16) ? (n >> 16) : n)
static int gpio_read(fdt_addr_t gpio_addr, int gpio_bank, int gpio_pin)
{
	uint32_t off, bit;

	bit = gpio_bank * 8 + gpio_pin;
	off = REG_PLUS4(GPIO_SWPORT_DDR, bit);
	bit = BIT_SUB16(bit);
	writel(WMSK_CLRBIT(bit), gpio_addr + off);

	return readl(gpio_addr + GPIO_EXT_PORT);
}

#else
#define GPIO_SWPORT_DDR		0x04
#define GPIO_EXT_PORT		0x50
static int gpio_read(fdt_addr_t gpio_addr, int gpio_bank, int gpio_pin)
{
	uint32_t val;

	val = readl(gpio_addr + GPIO_SWPORT_DDR);
	val &= ~(1 << (gpio_bank * 8 + gpio_pin));
	writel(val, gpio_addr + GPIO_SWPORT_DDR);

	return readl(gpio_addr + GPIO_EXT_PORT);
}
#endif

static int gpio_parse_base_address(fdt_addr_t *gpio_base_addr)
{
	static int initialized;
	ofnode parent, node;
	int idx = 0;

	if (initialized)
		return 0;

	parent = ofnode_path("/pinctrl");
	if (!ofnode_valid(parent)) {
		debug("   - No pinctrl node\n");
		return -EINVAL;
	}

	ofnode_for_each_subnode(node, parent) {
		if (!ofnode_get_property(node, "gpio-controller", NULL)) {
			debug("   - No gpio controller node\n");
			continue;
		}
		gpio_base_addr[idx] = ofnode_get_addr(node);
		debug("   - gpio%d: 0x%x\n", idx, (uint32_t)gpio_base_addr[idx]);
		idx++;
	}

	if (idx == 0) {
		debug("   - parse gpio address failed\n");
		return -EINVAL;
	}

	initialized = 1;

	return 0;
}

static void hwid_init_data(void)
{
	memset(adc_record, 0, sizeof(adc_record));
	memset(gpio_record, 0, sizeof(gpio_record));
	memset(gpio_base_addr, 0, sizeof(gpio_base_addr));
}

/*
 * How to use ?
 *
 * 1. Pack dtbs into resource.img, dtb file name:
 *    - End with: ".dtb"
 *    - Pattern: ...#_[controller]_ch[channel]=[value]...dtb
 *	    @controller: adc controller name in dts, eg. "saradc", ...;
 *	    @channel: adc channel;
 *	    @value: adc value;
 *    - Eg: ...#_saradc_ch1=223#_saradc_ch2=650....dtb
 *
 * 2. U-Boot dtsi about adc node:
 *    - Add "u-boot,dm-pre-reloc;"
 *    - Set node "okay"
 */
static int hwid_adc_find_dtb(const char *file_name)
{
	char *cell_name, *adc_tail, *adc_head, *p;
	int prefix_len, chn_len, len;
	int found = 0, margin = 30;
	int ret, channel;
	char dev_name[32];
	char adc_val[10];
	ulong dtb_adc;
	u32 raw_adc;

	debug("[HW-ADC]: %s\n", file_name);

	chn_len = strlen(KEY_WORDS_ADC_CH);
	prefix_len = strlen(KEY_WORDS_ADC_CTRL);
	cell_name = strstr(file_name, KEY_WORDS_ADC_CTRL);
	while (cell_name) {
		/* Parse adc controller name */
		adc_tail = strstr(cell_name, KEY_WORDS_ADC_CH);
		adc_head = cell_name + prefix_len;
		len = adc_tail - adc_head;
		strlcpy(dev_name, adc_head, len + 1);

		/* Parse adc channel */
		p = adc_tail + chn_len;
		if (is_digit(*p) && is_equal(*(p + 1))) {
			channel = *p - '0';
		} else {
			debug("   - invalid format: %s\n", cell_name);
			return 0;
		}

		/*
		 * Read raw adc value
		 *
		 * It doesn't need to read adc value every loop, reading once
		 * is enough. We use adc_record[] to save what we have read, zero
		 * means not read before.
		 */
		if (adc_record[channel] == 0) {
			ret = adc_channel_single_shot(dev_name, channel, &raw_adc);
			if (ret) {
				debug("   - failed to read adc, ret=%d\n", ret);
				return 0;
			}
			adc_record[channel] = raw_adc;
		}

		/* Parse dtb adc value */
		p = adc_tail + chn_len + 2;	/* 2: channel and '=' */
		while (*p && is_digit(*p)) {
			len++;
			p++;
		}
		strlcpy(adc_val, adc_tail + chn_len + 2, len + 1);
		dtb_adc = simple_strtoul(adc_val, NULL, 10);
		found = (abs(dtb_adc - adc_record[channel]) <= margin) ? 1 : 0;
		debug("   - dev=%s, channel=%d, dtb_adc=%ld, read=%d, found=%d\n",
		      dev_name, channel, dtb_adc, adc_record[channel], found);
		if (!found)
			break;
		cell_name = strstr(p, KEY_WORDS_ADC_CTRL);

	}

	return found;
}

/*
 * How to use ?
 *
 * 1. Pack dtbs into resource.img, dtb file name:
 *    - End with: ".dtb"
 *    - Pattern: ...#gpio[pin]=[level]...dtb
 *	     @pin: gpio name, eg. 0a2 means GPIO0A2
 *	     @level: gpio level, 0 or 1
 *    - Eg: ...#gpio0a6=1#gpio1c2=0....dtb
 *
 * 2. U-Boot dtsi about gpio node:
 *    - Add "u-boot,dm-pre-reloc;" for [all] gpio node;
 *    - Set all gpio node "disabled" (We just want their property);
 */
static int hwid_gpio_find_dtb(const char *file_name)
{
	uint8_t port, pin, bank, lvl, val;
	char *cell_name, *p;
	int ret, prefix_len;
	int found = 0;
	u32 bit;

	debug("[HW-GPIO]: %s\n", file_name);

	if (gpio_base_addr[0] == 0) {
		ret = gpio_parse_base_address(gpio_base_addr);
		if (ret) {
			debug("[HW-GPIO]: Can't parse gpio base, ret=%d\n", ret);
			return 0;
		}
	}

	prefix_len = strlen(KEY_WORDS_GPIO);
	cell_name = strstr(file_name, KEY_WORDS_GPIO);
	while (cell_name) {
		p = cell_name + prefix_len;

		/* Invalid format ? */
		if (!(is_digit(*(p + 0)) && is_abcd(*(p + 1)) &&
		      is_digit(*(p + 2)) && is_equal(*(p + 3)) &&
		      is_digit(*(p + 4)))) {
			debug("   - invalid format: %s\n", cell_name);
			return 0;
		}

		/* Read gpio value */
		port = *(p + 0) - '0';
		bank = *(p + 1) - 'a';
		pin  = *(p + 2) - '0';
		lvl  = *(p + 4) - '0';

		/*
		 * It doesn't need to read gpio value every loop, reading once
		 * is enough. We use gpio_record[] to save what we have read, zero
		 * means not read before.
		 */
		if (gpio_record[port] == 0) {
			if (!gpio_base_addr[port]) {
				debug("   - can't find gpio%d base\n", port);
				return 0;
			}
			gpio_record[port] =
				gpio_read(gpio_base_addr[port], bank, pin);
		}

		/* Verify result */
		bit = bank * 8 + pin;
		val = gpio_record[port] & (1 << bit) ? 1 : 0;
		found = (val == !!lvl) ? 1 : 0;
		debug("   - gpio%d%c%d=%d, read=%d, found=%d\n",
		      port, bank + 'a', pin, lvl, val, found);
		if (!found)
			break;
		cell_name = strstr(p, KEY_WORDS_GPIO);
	}

	return found;
}

struct resource_file *resource_read_hwid_dtb(void)
{
	struct resource_file *file;
	struct list_head *node;

	hwid_init_data();

	if (list_empty(&entrys_head)) {
		if (resource_init_list())
			return NULL;
	}

	list_for_each(node, &entrys_dtbs_head) {
		file = list_entry(node, struct resource_file, dtbs);
		if (!strstr(file->name, DTB_SUFFIX))
			continue;

		if (strstr(file->name, KEY_WORDS_ADC_CTRL) &&
		    strstr(file->name, KEY_WORDS_ADC_CH) &&
		    hwid_adc_find_dtb(file->name)) {
			return file;
		} else if (strstr(file->name, KEY_WORDS_GPIO) &&
			   hwid_gpio_find_dtb(file->name)) {
			return file;
		}
	}

	return NULL;
}

