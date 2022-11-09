// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <bitfield.h>
#include <thermal.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <div64.h>
#include <errno.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <clk.h>
#include <clk-uclass.h>
#include <reset.h>

DECLARE_GLOBAL_DATA_PTR;

/**
 * If the temperature over a period of time High,
 * the resulting TSHUT gave CRU module,let it reset the entire chip,
 * or via GPIO give PMIC.
 */
enum tshut_mode {
	TSHUT_MODE_CRU = 0,
	TSHUT_MODE_GPIO,
};

/**
 * The system Temperature Sensors tshut(tshut) polarity
 * the bit 8 is tshut polarity.
 * 0: low active, 1: high active
 */
enum tshut_polarity {
	TSHUT_LOW_ACTIVE = 0,
	TSHUT_HIGH_ACTIVE,
};

/**
 * The conversion table has the adc value and temperature.
 * ADC_DECREMENT: the adc value is of diminishing.(e.g. rk3288_code_table)
 * ADC_INCREMENT: the adc value is incremental.(e.g. rk3368_code_table)
 */
enum adc_sort_mode {
	ADC_DECREMENT = 0,
	ADC_INCREMENT,
};

#define SOC_MAX_SENSORS				7

#define TSADCV2_USER_CON			0x00
#define TSADCV2_AUTO_CON			0x04
#define TSADCV2_INT_EN				0x08
#define TSADCV2_INT_PD				0x0c
#define TSADCV3_AUTO_SRC_CON			0x0c
#define TSADCV3_HT_INT_EN			0x14
#define TSADCV3_HSHUT_GPIO_INT_EN		0x18
#define TSADCV3_HSHUT_CRU_INT_EN		0x1c
#define TSADCV3_INT_PD				0x24
#define TSADCV3_HSHUT_PD			0x28
#define TSADCV2_DATA(chn)			(0x20 + (chn) * 0x04)
#define TSADCV2_COMP_INT(chn)		        (0x30 + (chn) * 0x04)
#define TSADCV2_COMP_SHUT(chn)		        (0x40 + (chn) * 0x04)
#define TSADCV3_DATA(chn)			(0x2c + (chn) * 0x04)
#define TSADCV3_COMP_INT(chn)		        (0x6c + (chn) * 0x04)
#define TSADCV3_COMP_SHUT(chn)		        (0x10c + (chn) * 0x04)
#define TSADCV2_HIGHT_INT_DEBOUNCE		0x60
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE		0x64
#define TSADCV3_HIGHT_INT_DEBOUNCE		0x14c
#define TSADCV3_HIGHT_TSHUT_DEBOUNCE		0x150
#define TSADCV2_AUTO_PERIOD			0x68
#define TSADCV2_AUTO_PERIOD_HT			0x6c
#define TSADCV3_AUTO_PERIOD			0x154
#define TSADCV3_AUTO_PERIOD_HT			0x158

#define TSADCV2_AUTO_EN				BIT(0)
#define TSADCV2_AUTO_EN_MASK			BIT(16)
#define TSADCV2_AUTO_SRC_EN(chn)		BIT(4 + (chn))
#define TSADCV3_AUTO_SRC_EN(chn)		BIT(chn)
#define TSADCV3_AUTO_SRC_EN_MASK(chn)		BIT(16 + (chn))
#define TSADCV2_AUTO_TSHUT_POLARITY_HIGH	BIT(8)
#define TSADCV2_AUTO_TSHUT_POLARITY_MASK	BIT(24)

#define TSADCV3_AUTO_Q_SEL_EN			BIT(1)

#define TSADCV2_INT_SRC_EN(chn)			BIT(chn)
#define TSADCV2_INT_SRC_EN_MASK(chn)		BIT(16 + (chn))
#define TSADCV2_SHUT_2GPIO_SRC_EN(chn)		BIT(4 + (chn))
#define TSADCV2_SHUT_2CRU_SRC_EN(chn)		BIT(8 + (chn))

#define TSADCV2_INT_PD_CLEAR_MASK		~BIT(8)
#define TSADCV3_INT_PD_CLEAR_MASK		~BIT(16)
#define TSADCV4_INT_PD_CLEAR_MASK		0xffffffff

#define TSADCV2_DATA_MASK			0xfff
#define TSADCV3_DATA_MASK			0x3ff
#define TSADCV4_DATA_MASK			0x1ff

#define TSADCV2_HIGHT_INT_DEBOUNCE_COUNT	4
#define TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT	4
#define TSADCV2_AUTO_PERIOD_TIME		250
#define TSADCV2_AUTO_PERIOD_HT_TIME		50
#define TSADCV3_AUTO_PERIOD_TIME		1875
#define TSADCV3_AUTO_PERIOD_HT_TIME		1875
#define TSADCV5_AUTO_PERIOD_TIME		1622 /* 2.5ms */
#define TSADCV5_AUTO_PERIOD_HT_TIME		1622 /* 2.5ms */
#define TSADCV6_AUTO_PERIOD_TIME		5000 /* 2.5ms */
#define TSADCV6_AUTO_PERIOD_HT_TIME		5000 /* 2.5ms */

#define TSADCV2_USER_INTER_PD_SOC		0x340	/* 13 clocks */
#define TSADCV5_USER_INTER_PD_SOC		0xfc0 /* 97us, at least 90us */

#define GRF_SARADC_TESTBIT			0x0e644
#define GRF_TSADC_TESTBIT_L			0x0e648
#define GRF_TSADC_TESTBIT_H			0x0e64c

#define PX30_GRF_SOC_CON0			0x0400
#define PX30_GRF_SOC_CON2			0x0408

#define RK3568_GRF_TSADC_CON			0x0600
#define RK3568_GRF_TSADC_ANA_REG0		(0x10001 << 0)
#define RK3568_GRF_TSADC_ANA_REG1		(0x10001 << 1)
#define RK3568_GRF_TSADC_ANA_REG2		(0x10001 << 2)
#define RK3568_GRF_TSADC_TSEN			(0x10001 << 8)

#define GRF_SARADC_TESTBIT_ON			(0x10001 << 2)
#define GRF_TSADC_TESTBIT_H_ON			(0x10001 << 2)
#define GRF_TSADC_VCM_EN_L			(0x10001 << 7)
#define GRF_TSADC_VCM_EN_H			(0x10001 << 7)

#define GRF_CON_TSADC_CH_INV			(0x10001 << 1)
#define PX30S_TSADC_TDC_MODE                    (0x10001 << 4)

#define MIN_TEMP				(-40000)
#define LOWEST_TEMP				(-273000)
#define MAX_TEMP				(125000)
#define MAX_ENV_TEMP				(85000)

#define BASE					(1024)
#define BASE_SHIFT				(10)
#define START_DEBOUNCE_COUNT			(100)
#define HIGHER_DEBOUNCE_TEMP			(30000)
#define LOWER_DEBOUNCE_TEMP			(15000)

/**
 * struct tsadc_table - hold information about code and temp mapping
 * @code: raw code from tsadc ip
 * @temp: the mapping temperature
 */

struct tsadc_table {
	unsigned long code;
	int temp;
};

struct chip_tsadc_table {
	const struct tsadc_table *id;
	unsigned int length;
	u32 data_mask;
	/* Tsadc is linear, using linear parameters */
	int knum;
	int bnum;
	enum adc_sort_mode mode;
};

enum sensor_id {
	SENSOR_CPU = 0,
	SENSOR_GPU,
};

struct rockchip_tsadc_chip {
	/* The sensor id of chip correspond to the ADC channel */
	int chn_id[SOC_MAX_SENSORS];
	int chn_num;
	fdt_addr_t base;
	fdt_addr_t grf;

	/* The hardware-controlled tshut property */
	int tshut_temp;
	enum tshut_mode tshut_mode;
	enum tshut_polarity tshut_polarity;

	void (*tsadc_control)(struct udevice *dev, bool enable);
	void (*tsadc_init)(struct udevice *dev);
	int (*tsadc_get_temp)(struct udevice *dev, int chn,
			      int *temp);
	void (*irq_ack)(struct udevice *dev);
	void (*set_alarm_temp)(struct udevice *dev,
			       int chn, int temp);
	void (*set_tshut_temp)(struct udevice *dev,
			       int chn, int temp);
	void (*set_tshut_mode)(struct udevice *dev, int chn, enum tshut_mode m);
	struct chip_tsadc_table table;
};

struct rockchip_thermal_priv {
	void *base;
	void *grf;
	enum tshut_mode tshut_mode;
	enum tshut_polarity tshut_polarity;
	const struct rockchip_tsadc_chip *data;
};

static const struct tsadc_table rk1808_code_table[] = {
	{0, -40000},
	{3455, -40000},
	{3463, -35000},
	{3471, -30000},
	{3479, -25000},
	{3487, -20000},
	{3495, -15000},
	{3503, -10000},
	{3511, -5000},
	{3519, 0},
	{3527, 5000},
	{3535, 10000},
	{3543, 15000},
	{3551, 20000},
	{3559, 25000},
	{3567, 30000},
	{3576, 35000},
	{3584, 40000},
	{3592, 45000},
	{3600, 50000},
	{3609, 55000},
	{3617, 60000},
	{3625, 65000},
	{3633, 70000},
	{3642, 75000},
	{3650, 80000},
	{3659, 85000},
	{3667, 90000},
	{3675, 95000},
	{3684, 100000},
	{3692, 105000},
	{3701, 110000},
	{3709, 115000},
	{3718, 120000},
	{3726, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const struct tsadc_table rk3228_code_table[] = {
	{0, -40000},
	{588, -40000},
	{593, -35000},
	{598, -30000},
	{603, -25000},
	{608, -20000},
	{613, -15000},
	{618, -10000},
	{623, -5000},
	{629, 0},
	{634, 5000},
	{639, 10000},
	{644, 15000},
	{649, 20000},
	{654, 25000},
	{660, 30000},
	{665, 35000},
	{670, 40000},
	{675, 45000},
	{681, 50000},
	{686, 55000},
	{691, 60000},
	{696, 65000},
	{702, 70000},
	{707, 75000},
	{712, 80000},
	{717, 85000},
	{723, 90000},
	{728, 95000},
	{733, 100000},
	{738, 105000},
	{744, 110000},
	{749, 115000},
	{754, 120000},
	{760, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const struct tsadc_table rk3288_code_table[] = {
	{TSADCV2_DATA_MASK, -40000},
	{3800, -40000},
	{3792, -35000},
	{3783, -30000},
	{3774, -25000},
	{3765, -20000},
	{3756, -15000},
	{3747, -10000},
	{3737, -5000},
	{3728, 0},
	{3718, 5000},
	{3708, 10000},
	{3698, 15000},
	{3688, 20000},
	{3678, 25000},
	{3667, 30000},
	{3656, 35000},
	{3645, 40000},
	{3634, 45000},
	{3623, 50000},
	{3611, 55000},
	{3600, 60000},
	{3588, 65000},
	{3575, 70000},
	{3563, 75000},
	{3550, 80000},
	{3537, 85000},
	{3524, 90000},
	{3510, 95000},
	{3496, 100000},
	{3482, 105000},
	{3467, 110000},
	{3452, 115000},
	{3437, 120000},
	{3421, 125000},
};

static const struct tsadc_table rk3328_code_table[] = {
	{0, -40000},
	{296, -40000},
	{304, -35000},
	{313, -30000},
	{331, -20000},
	{340, -15000},
	{349, -10000},
	{359, -5000},
	{368, 0},
	{378, 5000},
	{388, 10000},
	{398, 15000},
	{408, 20000},
	{418, 25000},
	{429, 30000},
	{440, 35000},
	{451, 40000},
	{462, 45000},
	{473, 50000},
	{485, 55000},
	{496, 60000},
	{508, 65000},
	{521, 70000},
	{533, 75000},
	{546, 80000},
	{559, 85000},
	{572, 90000},
	{586, 95000},
	{600, 100000},
	{614, 105000},
	{629, 110000},
	{644, 115000},
	{659, 120000},
	{675, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const struct tsadc_table rk3368_code_table[] = {
	{0, -40000},
	{106, -40000},
	{108, -35000},
	{110, -30000},
	{112, -25000},
	{114, -20000},
	{116, -15000},
	{118, -10000},
	{120, -5000},
	{122, 0},
	{124, 5000},
	{126, 10000},
	{128, 15000},
	{130, 20000},
	{132, 25000},
	{134, 30000},
	{136, 35000},
	{138, 40000},
	{140, 45000},
	{142, 50000},
	{144, 55000},
	{146, 60000},
	{148, 65000},
	{150, 70000},
	{152, 75000},
	{154, 80000},
	{156, 85000},
	{158, 90000},
	{160, 95000},
	{162, 100000},
	{163, 105000},
	{165, 110000},
	{167, 115000},
	{169, 120000},
	{171, 125000},
	{TSADCV3_DATA_MASK, 125000},
};

static const struct tsadc_table rk3399_code_table[] = {
	{0, -40000},
	{402, -40000},
	{410, -35000},
	{419, -30000},
	{427, -25000},
	{436, -20000},
	{444, -15000},
	{453, -10000},
	{461, -5000},
	{470, 0},
	{478, 5000},
	{487, 10000},
	{496, 15000},
	{504, 20000},
	{513, 25000},
	{521, 30000},
	{530, 35000},
	{538, 40000},
	{547, 45000},
	{555, 50000},
	{564, 55000},
	{573, 60000},
	{581, 65000},
	{590, 70000},
	{599, 75000},
	{607, 80000},
	{616, 85000},
	{624, 90000},
	{633, 95000},
	{642, 100000},
	{650, 105000},
	{659, 110000},
	{668, 115000},
	{677, 120000},
	{685, 125000},
	{TSADCV3_DATA_MASK, 125000},
};

static const struct tsadc_table rk3568_code_table[] = {
	{0, -40000},
	{1584, -40000},
	{1620, -35000},
	{1652, -30000},
	{1688, -25000},
	{1720, -20000},
	{1756, -15000},
	{1788, -10000},
	{1824, -5000},
	{1856, 0},
	{1892, 5000},
	{1924, 10000},
	{1956, 15000},
	{1992, 20000},
	{2024, 25000},
	{2060, 30000},
	{2092, 35000},
	{2128, 40000},
	{2160, 45000},
	{2196, 50000},
	{2228, 55000},
	{2264, 60000},
	{2300, 65000},
	{2332, 70000},
	{2368, 75000},
	{2400, 80000},
	{2436, 85000},
	{2468, 90000},
	{2500, 95000},
	{2536, 100000},
	{2572, 105000},
	{2604, 110000},
	{2636, 115000},
	{2672, 120000},
	{2704, 125000},
	{TSADCV2_DATA_MASK, 125000},
};

static const struct tsadc_table rk3588_code_table[] = {
	{0, -40000},
	{215, -40000},
	{285, 25000},
	{350, 85000},
	{395, 125000},
	{TSADCV4_DATA_MASK, 125000},
};

/*
 * Struct used for matching a device
 */
struct of_device_id {
	char compatible[32];
	const void *data;
};

static int tsadc_code_to_temp(struct chip_tsadc_table *table, u32 code,
			      int *temp)
{
	unsigned int low = 1;
	unsigned int high = table->length - 1;
	unsigned int mid = (low + high) / 2;
	unsigned int num;
	unsigned long denom;

	if (table->knum) {
		*temp = (((int)code - table->bnum) * 10000 / table->knum) * 100;
		if (*temp < MIN_TEMP || *temp > MAX_TEMP)
			return -EAGAIN;
		return 0;
	}

	switch (table->mode) {
	case ADC_DECREMENT:
		code &= table->data_mask;
		if (code < table->id[high].code)
			return -EAGAIN;	/* Incorrect reading */

		while (low <= high) {
			if (code >= table->id[mid].code &&
			    code < table->id[mid - 1].code)
				break;
			else if (code < table->id[mid].code)
				low = mid + 1;
			else
				high = mid - 1;

			mid = (low + high) / 2;
		}
		break;
	case ADC_INCREMENT:
		code &= table->data_mask;
		if (code < table->id[low].code)
			return -EAGAIN;	/* Incorrect reading */

		while (low <= high) {
			if (code <= table->id[mid].code &&
			    code > table->id[mid - 1].code)
				break;
			else if (code > table->id[mid].code)
				low = mid + 1;
			else
				high = mid - 1;

			mid = (low + high) / 2;
		}
		break;
	default:
		printf("%s: Invalid the conversion table mode=%d\n",
		       __func__, table->mode);
		return -EINVAL;
	}

	/*
	 * The 5C granularity provided by the table is too much. Let's
	 * assume that the relationship between sensor readings and
	 * temperature between 2 table entries is linear and interpolate
	 * to produce less granular result.
	 */
	num = table->id[mid].temp - table->id[mid - 1].temp;
	num *= abs(table->id[mid - 1].code - code);
	denom = abs(table->id[mid - 1].code - table->id[mid].code);
	*temp = table->id[mid - 1].temp + (num / denom);

	return 0;
}

static u32 tsadc_temp_to_code_v2(struct chip_tsadc_table table,
				 int temp)
{
	int high, low, mid;
	unsigned long num;
	unsigned int denom;
	u32 error = table.data_mask;

	if (table.knum)
		return (((temp / 1000) * table.knum) / 1000 + table.bnum);

	low = 0;
	high = table.length - 1;
	mid = (high + low) / 2;

	/* Return mask code data when the temp is over table range */
	if (temp < table.id[low].temp || temp > table.id[high].temp)
		goto exit;

	while (low <= high) {
		if (temp == table.id[mid].temp)
			return table.id[mid].code;
		else if (temp < table.id[mid].temp)
			high = mid - 1;
		else
			low = mid + 1;
		mid = (low + high) / 2;
	}

	num = abs(table.id[mid + 1].code - table.id[mid].code);
	num *= temp - table.id[mid].temp;
	denom = table.id[mid + 1].temp - table.id[mid].temp;

	switch (table.mode) {
	case ADC_DECREMENT:
		return table.id[mid].code - (num / denom);
	case ADC_INCREMENT:
		return table.id[mid].code + (num / denom);
	default:
		pr_err("%s: unknown table mode: %d\n", __func__, table.mode);
		return error;
	}

exit:
	pr_err("%s: Invalid conversion table: code=%d, temperature=%d\n",
	       __func__, error, temp);

	return error;
}

static void tsadc_irq_ack_v2(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV2_INT_PD);
	writel(val & TSADCV2_INT_PD_CLEAR_MASK, priv->base + TSADCV2_INT_PD);
}

static void tsadc_irq_ack_v3(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV2_INT_PD);
	writel(val & TSADCV3_INT_PD_CLEAR_MASK, priv->base + TSADCV2_INT_PD);
}

static void tsadc_irq_ack_v4(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV3_INT_PD);
	writel(val & TSADCV4_INT_PD_CLEAR_MASK, priv->base + TSADCV3_INT_PD);
	val = readl(priv->base + TSADCV3_HSHUT_PD);
	writel(val & TSADCV3_INT_PD_CLEAR_MASK, priv->base + TSADCV3_HSHUT_PD);
}

static void tsadc_control_v2(struct udevice *dev, bool enable)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV2_AUTO_CON);
	if (enable)
		val |= TSADCV2_AUTO_EN;
	else
		val &= ~TSADCV2_AUTO_EN;

	writel(val, priv->base + TSADCV2_AUTO_CON);
}

static void tsadc_control_v3(struct udevice *dev, bool enable)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV2_AUTO_CON);
	if (enable)
		val |= TSADCV2_AUTO_EN | TSADCV3_AUTO_Q_SEL_EN;
	else
		val &= ~TSADCV2_AUTO_EN;

	writel(val, priv->base + TSADCV2_AUTO_CON);
}

static void tsadc_control_v4(struct udevice *dev, bool enable)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	if (enable)
		val = TSADCV2_AUTO_EN | TSADCV2_AUTO_EN_MASK;
	else
		val = TSADCV2_AUTO_EN_MASK;

	writel(val, priv->base + TSADCV2_AUTO_CON);
}

static void tsadc_init_v2(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	writel(TSADCV2_AUTO_PERIOD_TIME,
	       priv->base + TSADCV2_AUTO_PERIOD);
	writel(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
	       priv->base + TSADCV2_HIGHT_INT_DEBOUNCE);
	writel(TSADCV2_AUTO_PERIOD_HT_TIME,
	       priv->base + TSADCV2_AUTO_PERIOD_HT);
	writel(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
	       priv->base + TSADCV2_HIGHT_TSHUT_DEBOUNCE);

	if (priv->tshut_polarity == TSHUT_HIGH_ACTIVE)
		writel(0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
		       priv->base + TSADCV2_AUTO_CON);
	else
		writel(0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
		       priv->base + TSADCV2_AUTO_CON);
}

static void tsadc_init_v3(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	if (!IS_ERR(priv->grf)) {
		writel(GRF_TSADC_VCM_EN_L, priv->grf + GRF_TSADC_TESTBIT_L);
		writel(GRF_TSADC_VCM_EN_H, priv->grf + GRF_TSADC_TESTBIT_H);

		udelay(100);/* The spec note says at least 15 us */
		writel(GRF_SARADC_TESTBIT_ON, priv->grf + GRF_SARADC_TESTBIT);
		writel(GRF_TSADC_TESTBIT_H_ON, priv->grf + GRF_TSADC_TESTBIT_H);
		udelay(200);/* The spec note says at least 90 us */
	}
	tsadc_init_v2(dev);
}

static void __maybe_unused tsadc_init_v5(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	/* Set interleave value to workround ic time sync issue */
	writel(TSADCV2_USER_INTER_PD_SOC, priv->base +
		       TSADCV2_USER_CON);
	tsadc_init_v2(dev);
}

static void tsadc_init_v4(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	tsadc_init_v2(dev);
	if (!IS_ERR(priv->grf))
		writel(GRF_CON_TSADC_CH_INV, priv->grf + PX30_GRF_SOC_CON2);
}

static void tsadc_init_v7(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	writel(TSADCV5_USER_INTER_PD_SOC,
	       priv->base + TSADCV2_USER_CON);
	writel(TSADCV5_AUTO_PERIOD_TIME,
	       priv->base + TSADCV2_AUTO_PERIOD);
	writel(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
	       priv->base + TSADCV2_HIGHT_INT_DEBOUNCE);
	writel(TSADCV5_AUTO_PERIOD_HT_TIME,
	       priv->base + TSADCV2_AUTO_PERIOD_HT);
	writel(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
	       priv->base + TSADCV2_HIGHT_TSHUT_DEBOUNCE);

	if (priv->tshut_polarity == TSHUT_HIGH_ACTIVE)
		writel(0U | TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
		       priv->base + TSADCV2_AUTO_CON);
	else
		writel(0U & ~TSADCV2_AUTO_TSHUT_POLARITY_HIGH,
		       priv->base + TSADCV2_AUTO_CON);

	if (!IS_ERR(priv->grf)) {
		writel(RK3568_GRF_TSADC_TSEN,
		       priv->grf + RK3568_GRF_TSADC_CON);
		udelay(15);
		writel(RK3568_GRF_TSADC_ANA_REG0,
		       priv->grf + RK3568_GRF_TSADC_CON);
		writel(RK3568_GRF_TSADC_ANA_REG1,
		       priv->grf + RK3568_GRF_TSADC_CON);
		writel(RK3568_GRF_TSADC_ANA_REG2,
		       priv->grf + RK3568_GRF_TSADC_CON);
		udelay(200);
	}
}

static void tsadc_init_v8(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	writel(TSADCV6_AUTO_PERIOD_TIME, priv->base + TSADCV3_AUTO_PERIOD);
	writel(TSADCV6_AUTO_PERIOD_HT_TIME,
	       priv->base + TSADCV3_AUTO_PERIOD_HT);
	writel(TSADCV2_HIGHT_INT_DEBOUNCE_COUNT,
	       priv->base + TSADCV3_HIGHT_INT_DEBOUNCE);
	writel(TSADCV2_HIGHT_TSHUT_DEBOUNCE_COUNT,
	       priv->base + TSADCV3_HIGHT_TSHUT_DEBOUNCE);

	if (priv->tshut_polarity == TSHUT_HIGH_ACTIVE)
		writel(TSADCV2_AUTO_TSHUT_POLARITY_HIGH |
		       TSADCV2_AUTO_TSHUT_POLARITY_MASK,
		       priv->base + TSADCV2_AUTO_CON);
	else
		writel(TSADCV2_AUTO_TSHUT_POLARITY_MASK,
		       priv->base + TSADCV2_AUTO_CON);
};

static void tsadc_init_v9(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	tsadc_init_v2(dev);
	if (!IS_ERR(priv->grf))
		writel(PX30S_TSADC_TDC_MODE, priv->grf + PX30_GRF_SOC_CON0);
}

static int tsadc_get_temp_v2(struct udevice *dev,
			     int chn, int *temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 val;

	val = readl(priv->base + TSADCV2_DATA(chn));

	return tsadc_code_to_temp(&table, val, temp);
}

static int predict_temp(int temp)
{
	/*
	 * The deviation of prediction. the temperature will not change rapidly,
	 * so this cov_q is small
	 */
	int cov_q = 18;
	/*
	 * The deviation of tsadc's reading, deviation of tsadc is very big when
	 * abnormal temperature is get
	 */
	int cov_r = 542;

	int gain;
	int temp_mid;
	int temp_now;
	int prob_mid;
	int prob_now;
	static int temp_last = LOWEST_TEMP;
	static int prob_last = 160;
	static int bounding_cnt;

	/*
	 * init temp_last with a more suitable value, which mostly equals to
	 * temp reading from tsadc, but not higher than MAX_ENV_TEMP. If the
	 * temp is higher than MAX_ENV_TEMP, it is assumed to be abnormal
	 * value and temp_last is adjusted to MAX_ENV_TEMP.
	 */
	if (temp_last == LOWEST_TEMP)
		temp_last = min(temp, MAX_ENV_TEMP);

	/*
	 * Before START_DEBOUNCE_COUNT's samples of temperature, we consider
	 * tsadc is stable, i.e. after that, the temperature may be not stable
	 * and may have abnormal reading, so we set a bounding temperature. If
	 * the reading from tsadc is too big, we set the delta temperature of
	 * DEBOUNCE_TEMP/3 comparing to the last temperature.
	 */

	if (bounding_cnt++ > START_DEBOUNCE_COUNT) {
		bounding_cnt = START_DEBOUNCE_COUNT;
		if (temp - temp_last > HIGHER_DEBOUNCE_TEMP)
			temp = temp_last + HIGHER_DEBOUNCE_TEMP / 3;
		if (temp_last - temp > LOWER_DEBOUNCE_TEMP)
			temp = temp_last - LOWER_DEBOUNCE_TEMP / 3;
	}

	temp_mid = temp_last;

	/* calculate the probability of this time's prediction */
	prob_mid = prob_last + cov_q;

	/* calculate the Kalman Gain */
	gain = (prob_mid * BASE) / (prob_mid + cov_r);

	/* calculate the prediction of temperature */
	temp_now = (temp_mid * BASE + gain * (temp - temp_mid)) >> BASE_SHIFT;

	/*
	 * Base on this time's Kalman Gain, ajust our probability of prediction
	 * for next time calculation
	 */
	prob_now = ((BASE - gain) * prob_mid) >> BASE_SHIFT;

	prob_last = prob_now;
	temp_last = temp_now;

	return temp_last;
}

static int tsadc_get_temp_v3(struct udevice *dev,
			     int chn, int *temp)
{
	int ret;

	ret = tsadc_get_temp_v2(dev, chn, temp);
	if (!ret)
		*temp = predict_temp(*temp);

	return ret;
}

static int tsadc_get_temp_v4(struct udevice *dev, int chn, int *temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 val;

	val = readl(priv->base + TSADCV3_DATA(chn));

	return tsadc_code_to_temp(&table, val, temp);
}

static void tsadc_alarm_temp_v2(struct udevice *dev,
				int chn, int temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 alarm_value, int_en;

	alarm_value = tsadc_temp_to_code_v2(table, temp);
	if (alarm_value == table.data_mask)
		return;

	writel(alarm_value, priv->base + TSADCV2_COMP_INT(chn));

	int_en = readl(priv->base + TSADCV2_INT_EN);
	int_en |= TSADCV2_INT_SRC_EN(chn);
	writel(int_en, priv->base + TSADCV2_INT_EN);
}

static void tsadc_alarm_temp_v3(struct udevice *dev, int chn, int temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 alarm_value;

	alarm_value = tsadc_temp_to_code_v2(table, temp);
	if (alarm_value == table.data_mask)
		return;

	writel(alarm_value, priv->base + TSADCV3_COMP_INT(chn));
	writel(TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn),
	       priv->base + TSADCV3_HT_INT_EN);
}

static void tsadc_tshut_temp_v2(struct udevice *dev,
				int chn, int temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 tshut_value, val;

	tshut_value = tsadc_temp_to_code_v2(table, temp);
	if (tshut_value == table.data_mask)
		return;

	writel(tshut_value, priv->base + TSADCV2_COMP_SHUT(chn));

	/* TSHUT will be valid */
	val = readl(priv->base + TSADCV2_AUTO_CON);
	writel(val | TSADCV2_AUTO_SRC_EN(chn), priv->base + TSADCV2_AUTO_CON);
}

static void tsadc_tshut_temp_v3(struct udevice *dev, int chn, int temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct chip_tsadc_table table = priv->data->table;
	u32 tshut_value;

	tshut_value = tsadc_temp_to_code_v2(table, temp);
	if (tshut_value == table.data_mask)
		return;

	writel(tshut_value, priv->base + TSADCV3_COMP_SHUT(chn));
	writel(TSADCV3_AUTO_SRC_EN(chn) | TSADCV3_AUTO_SRC_EN_MASK(chn),
	       priv->base + TSADCV3_AUTO_SRC_CON);
}

static void tsadc_tshut_mode_v2(struct udevice *dev, int chn,
				enum tshut_mode mode)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val;

	val = readl(priv->base + TSADCV2_INT_EN);
	if (mode == TSHUT_MODE_GPIO) {
		val &= ~TSADCV2_SHUT_2CRU_SRC_EN(chn);
		val |= TSADCV2_SHUT_2GPIO_SRC_EN(chn);
	} else {
		val &= ~TSADCV2_SHUT_2GPIO_SRC_EN(chn);
		val |= TSADCV2_SHUT_2CRU_SRC_EN(chn);
	}

	writel(val, priv->base + TSADCV2_INT_EN);
}

static void tsadc_tshut_mode_v4(struct udevice *dev, int chn,
				enum tshut_mode mode)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	u32 val_gpio, val_cru;

	if (mode == TSHUT_MODE_GPIO) {
		val_gpio = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
		val_cru = TSADCV2_INT_SRC_EN_MASK(chn);
	} else {
		val_cru = TSADCV2_INT_SRC_EN(chn) | TSADCV2_INT_SRC_EN_MASK(chn);
		val_gpio = TSADCV2_INT_SRC_EN_MASK(chn);
	}
	writel(val_gpio, priv->base + TSADCV3_HSHUT_GPIO_INT_EN);
	writel(val_cru, priv->base + TSADCV3_HSHUT_CRU_INT_EN);
}

int rockchip_thermal_get_temp(struct udevice *dev, int *temp)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	priv->data->tsadc_get_temp(dev, 0, temp);

	return 0;
}

static const struct dm_thermal_ops rockchip_thermal_ops = {
	.get_temp	= rockchip_thermal_get_temp,
};

static const struct rockchip_tsadc_chip px30s_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* 2 channels for tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v9,
	.tsadc_control = tsadc_control_v2,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.knum = 2699,
		.bnum = 2796,
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3308bs_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* 1 channels for tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v2,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.knum = 2699,
		.bnum = 2796,
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static int rockchip_thermal_probe(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);
	struct rockchip_tsadc_chip *tsadc;
	struct clk clk;
	int ret, i, shut_temp;

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		printf("%s clk_set_defaults failed %d\n", __func__, ret);

	if (soc_is_rk3308bs() || soc_is_px30s()) {
		ret = clk_get_by_name(dev, "tsadc", &clk);
		if (ret) {
			printf("%s get tsadc clk fail\n", __func__);
			return -EINVAL;
		}
		ret = clk_set_rate(&clk, 4000000);
		if (ret < 0) {
			printf("%s: failed to set tsadc clk rate for %s\n",
			       __func__, dev_read_name(dev));
			return -EINVAL;
		}
	}
	if (soc_is_rk3308bs())
		tsadc = (struct rockchip_tsadc_chip *)&rk3308bs_tsadc_data;
	else if (soc_is_px30s())
		tsadc = (struct rockchip_tsadc_chip *)&px30s_tsadc_data;
	else
		tsadc = (struct rockchip_tsadc_chip *)dev_get_driver_data(dev);

	priv->data = tsadc;

	priv->tshut_mode = dev_read_u32_default(dev,
						"rockchip,hw-tshut-mode",
						-1);
	if (priv->tshut_mode < 0)
		priv->tshut_mode = priv->data->tshut_mode;

	priv->tshut_polarity = dev_read_u32_default(dev,
						    "rockchip,hw-tshut-polarity",
						    -1);
	if (priv->tshut_polarity < 0)
		priv->tshut_polarity = tsadc->tshut_polarity;

	if (priv->tshut_mode == TSHUT_MODE_GPIO)
		pinctrl_select_state(dev, "otpout");
	else
		pinctrl_select_state(dev, "gpio");

	tsadc->tsadc_init(dev);
	tsadc->irq_ack(dev);

	shut_temp = dev_read_u32_default(dev, "rockchip,hw-tshut-temp", -1);
	if (shut_temp < 0)
		shut_temp = 120000;

	for (i = 0; i < tsadc->chn_num; i++) {
		tsadc->set_alarm_temp(dev, i, tsadc->tshut_temp);
		tsadc->set_tshut_temp(dev, i, shut_temp);
		if (priv->tshut_mode == TSHUT_MODE_GPIO)
			tsadc->set_tshut_mode(dev, i, TSHUT_MODE_GPIO);
		else
			tsadc->set_tshut_mode(dev, i, TSHUT_MODE_CRU);
	}

	tsadc->tsadc_control(dev, true);
	if (soc_is_rk3308bs() || soc_is_px30s())
		mdelay(3);
	else
		udelay(1000);

	debug("tsadc probed successfully\n");

	return 0;
}

static int rockchip_thermal_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_thermal_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);

	return 0;
}

static const struct rockchip_tsadc_chip rk1808_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channel for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk1808_code_table,
		.length = ARRAY_SIZE(rk1808_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3228_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channel for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3228_code_table,
		.length = ARRAY_SIZE(rk3228_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3288_tsadc_data = {
	.chn_id[SENSOR_CPU] = 1, /* cpu sensor is channel 1 */
	.chn_id[SENSOR_GPU] = 2, /* gpu sensor is channel 2 */
	.chn_num = 2, /* two channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v2,
	.tsadc_get_temp = tsadc_get_temp_v3,
	.irq_ack = tsadc_irq_ack_v2,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3288_code_table,
		.length = ARRAY_SIZE(rk3288_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_DECREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3308_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* 2 channels for tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v4,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3328_code_table,
		.length = ARRAY_SIZE(rk3328_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip px30_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* 2 channels for tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v4,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3328_code_table,
		.length = ARRAY_SIZE(rk3328_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3328_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_num = 1, /* one channels for tsadc */

	.tshut_mode = TSHUT_MODE_CRU, /* default TSHUT via CRU */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3328_code_table,
		.length = ARRAY_SIZE(rk3328_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3366_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v3,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3228_code_table,
		.length = ARRAY_SIZE(rk3228_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3368_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v2,
	.tsadc_control = tsadc_control_v2,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v2,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3368_code_table,
		.length = ARRAY_SIZE(rk3368_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3399_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v3,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3399_code_table,
		.length = ARRAY_SIZE(rk3399_code_table),
		.data_mask = TSADCV3_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3568_tsadc_data = {
	.chn_id[SENSOR_CPU] = 0, /* cpu sensor is channel 0 */
	.chn_id[SENSOR_GPU] = 1, /* gpu sensor is channel 1 */
	.chn_num = 2, /* two channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v7,
	.tsadc_control = tsadc_control_v3,
	.tsadc_get_temp = tsadc_get_temp_v2,
	.irq_ack = tsadc_irq_ack_v3,
	.set_alarm_temp = tsadc_alarm_temp_v2,
	.set_tshut_temp = tsadc_tshut_temp_v2,
	.set_tshut_mode = tsadc_tshut_mode_v2,

	.table = {
		.id = rk3568_code_table,
		.length = ARRAY_SIZE(rk3568_code_table),
		.data_mask = TSADCV2_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct rockchip_tsadc_chip rk3588_tsadc_data = {
	/* top, big_core0, big_core1, little_core, center, gpu, npu */
	.chn_id = {0, 1, 2, 3, 4, 5, 6},
	.chn_num = 7, /* seven channels for tsadc */

	.tshut_mode = TSHUT_MODE_GPIO, /* default TSHUT via GPIO give PMIC */
	.tshut_polarity = TSHUT_LOW_ACTIVE, /* default TSHUT LOW ACTIVE */
	.tshut_temp = 95000,

	.tsadc_init = tsadc_init_v8,
	.tsadc_control = tsadc_control_v4,
	.tsadc_get_temp = tsadc_get_temp_v4,
	.irq_ack = tsadc_irq_ack_v4,
	.set_alarm_temp = tsadc_alarm_temp_v3,
	.set_tshut_temp = tsadc_tshut_temp_v3,
	.set_tshut_mode = tsadc_tshut_mode_v4,

	.table = {
		.id = rk3588_code_table,
		.length = ARRAY_SIZE(rk3588_code_table),
		.data_mask = TSADCV4_DATA_MASK,
		.mode = ADC_INCREMENT,
	},
};

static const struct udevice_id rockchip_thermal_match[] = {
	{
		.compatible = "rockchip,px30-tsadc",
		.data = (ulong)&px30_tsadc_data,
	},
	{
		.compatible = "rockchip,px30s-tsadc",
		.data = (ulong)&px30s_tsadc_data,
	},
	{
		.compatible = "rockchip,rk1808-tsadc",
		.data = (ulong)&rk1808_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3228-tsadc",
		.data = (ulong)&rk3228_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3288-tsadc",
		.data = (ulong)&rk3288_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3308-tsadc",
		.data = (ulong)&rk3308_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3308bs-tsadc",
		.data = (ulong)&rk3308bs_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3328-tsadc",
		.data = (ulong)&rk3328_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3366-tsadc",
		.data = (ulong)&rk3366_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3368-tsadc",
		.data = (ulong)&rk3368_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3399-tsadc",
		.data = (ulong)&rk3399_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3568-tsadc",
		.data = (ulong)&rk3568_tsadc_data,
	},
	{
		.compatible = "rockchip,rk3588-tsadc",
		.data = (ulong)&rk3588_tsadc_data,
	},
	{ /* end */ },
};

U_BOOT_DRIVER(rockchip_thermal) = {
	.name		= "rockchip_thermal",
	.id		= UCLASS_THERMAL,
	.of_match	= rockchip_thermal_match,
	.priv_auto_alloc_size = sizeof(struct rockchip_thermal_priv),
	.ofdata_to_platdata = rockchip_thermal_ofdata_to_platdata,
	.ops		= &rockchip_thermal_ops,
	.probe		= rockchip_thermal_probe,
};
