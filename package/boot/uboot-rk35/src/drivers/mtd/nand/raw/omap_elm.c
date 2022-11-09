/*
 * (C) Copyright 2010-2011 Texas Instruments, <www.ti.com>
 * Mansoor Ahamed <mansoor.ahamed@ti.com>
 *
 * BCH Error Location Module (ELM) support.
 *
 * NOTE:
 * 1. Supports only continuous mode. Dont see need for page mode in uboot
 * 2. Supports only syndrome polynomial 0. i.e. poly local variable is
 *    always set to ELM_DEFAULT_POLY. Dont see need for other polynomial
 *    sets in uboot
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <linux/mtd/omap_elm.h>
#include <asm/arch/hardware.h>

#define DRIVER_NAME		"omap-elm"
#define ELM_DEFAULT_POLY (0)

struct elm *elm_cfg;

/**
 * elm_load_syndromes - Load BCH syndromes based on bch_type selection
 * @syndrome: BCH syndrome
 * @bch_type: BCH4/BCH8/BCH16
 * @poly: Syndrome Polynomial set to use
 */
static void elm_load_syndromes(u8 *syndrome, enum bch_level bch_type, u8 poly)
{
	u32 *ptr;
	u32 val;

	/* reg 0 */
	ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[0];
	val = syndrome[0] | (syndrome[1] << 8) | (syndrome[2] << 16) |
				(syndrome[3] << 24);
	writel(val, ptr);
	/* reg 1 */
	ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[1];
	val = syndrome[4] | (syndrome[5] << 8) | (syndrome[6] << 16) |
				(syndrome[7] << 24);
	writel(val, ptr);

	if (bch_type == BCH_8_BIT || bch_type == BCH_16_BIT) {
		/* reg 2 */
		ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[2];
		val = syndrome[8] | (syndrome[9] << 8) | (syndrome[10] << 16) |
				(syndrome[11] << 24);
		writel(val, ptr);
		/* reg 3 */
		ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[3];
		val = syndrome[12] | (syndrome[13] << 8) |
			(syndrome[14] << 16) | (syndrome[15] << 24);
		writel(val, ptr);
	}

	if (bch_type == BCH_16_BIT) {
		/* reg 4 */
		ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[4];
		val = syndrome[16] | (syndrome[17] << 8) |
			(syndrome[18] << 16) | (syndrome[19] << 24);
		writel(val, ptr);

		/* reg 5 */
		ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[5];
		val = syndrome[20] | (syndrome[21] << 8) |
			(syndrome[22] << 16) | (syndrome[23] << 24);
		writel(val, ptr);

		/* reg 6 */
		ptr = &elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[6];
		val = syndrome[24] | (syndrome[25] << 8) |
			(syndrome[26] << 16) | (syndrome[27] << 24);
		writel(val, ptr);
	}
}

/**
 * elm_check_errors - Check for BCH errors and return error locations
 * @syndrome: BCH syndrome
 * @bch_type: BCH4/BCH8/BCH16
 * @error_count: Returns number of errrors in the syndrome
 * @error_locations: Returns error locations (in decimal) in this array
 *
 * Check the provided syndrome for BCH errors and return error count
 * and locations in the array passed. Returns -1 if error is not correctable,
 * else returns 0
 */
int elm_check_error(u8 *syndrome, enum bch_level bch_type, u32 *error_count,
		u32 *error_locations)
{
	u8 poly = ELM_DEFAULT_POLY;
	s8 i;
	u32 location_status;

	elm_load_syndromes(syndrome, bch_type, poly);

	/* start processing */
	writel((readl(&elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[6])
				| ELM_SYNDROME_FRAGMENT_6_SYNDROME_VALID),
		&elm_cfg->syndrome_fragments[poly].syndrome_fragment_x[6]);

	/* wait for processing to complete */
	while ((readl(&elm_cfg->irqstatus) & (0x1 << poly)) != 0x1)
		;
	/* clear status */
	writel((readl(&elm_cfg->irqstatus) | (0x1 << poly)),
			&elm_cfg->irqstatus);

	/* check if correctable */
	location_status = readl(&elm_cfg->error_location[poly].location_status);
	if (!(location_status & ELM_LOCATION_STATUS_ECC_CORRECTABLE_MASK)) {
		printf("%s: uncorrectable ECC errors\n", DRIVER_NAME);
		return -EBADMSG;
	}

	/* get error count */
	*error_count = readl(&elm_cfg->error_location[poly].location_status) &
					ELM_LOCATION_STATUS_ECC_NB_ERRORS_MASK;

	for (i = 0; i < *error_count; i++) {
		error_locations[i] =
		     readl(&elm_cfg->error_location[poly].error_location_x[i]);
	}

	return 0;
}


/**
 * elm_config - Configure ELM module
 * @level: 4 / 8 / 16 bit BCH
 *
 * Configure ELM module based on BCH level.
 * Set mode as continuous mode.
 * Currently we are using only syndrome 0 and syndromes 1 to 6 are not used.
 * Also, the mode is set only for syndrome 0
 */
int elm_config(enum bch_level level)
{
	u32 val;
	u8 poly = ELM_DEFAULT_POLY;
	u32 buffer_size = 0x7FF;

	/* config size and level */
	val = (u32)(level) & ELM_LOCATION_CONFIG_ECC_BCH_LEVEL_MASK;
	val |= ((buffer_size << ELM_LOCATION_CONFIG_ECC_SIZE_POS) &
				ELM_LOCATION_CONFIG_ECC_SIZE_MASK);
	writel(val, &elm_cfg->location_config);

	/* config continous mode */
	/* enable interrupt generation for syndrome polynomial set */
	writel((readl(&elm_cfg->irqenable) | (0x1 << poly)),
			&elm_cfg->irqenable);
	/* set continuous mode for the syndrome polynomial set */
	writel((readl(&elm_cfg->page_ctrl) & ~(0x1 << poly)),
			&elm_cfg->page_ctrl);

	return 0;
}

/**
 * elm_reset - Do a soft reset of ELM
 *
 * Perform a soft reset of ELM and return after reset is done.
 */
void elm_reset(void)
{
	/* initiate reset */
	writel((readl(&elm_cfg->sysconfig) | ELM_SYSCONFIG_SOFTRESET),
			&elm_cfg->sysconfig);

	/* wait for reset complete and normal operation */
	while ((readl(&elm_cfg->sysstatus) & ELM_SYSSTATUS_RESETDONE) !=
		ELM_SYSSTATUS_RESETDONE)
		;
}

/**
 * elm_init - Initialize ELM module
 *
 * Initialize ELM support. Currently it does only base address init
 * and ELM reset.
 */
void elm_init(void)
{
	elm_cfg = (struct elm *)ELM_BASE;
	elm_reset();
}
