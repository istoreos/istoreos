/*
 *  This is a driver for the eMMC controller found in Realtek RTD1195
 *  SoCs.
 *
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include "rtkemmc_generic.h"

#define __RTKEMMC_GENERIC_C__
#define CONFIG_GENERIC_MMC

int mmc_had_been_initialized;
int mmc_ready_to_use;
static struct mmc mmc_dev[2];

extern unsigned int rtkemmc_debug_msg;
extern unsigned int rtkemmc_off_error_msg_in_init_flow;
extern unsigned int sys_ext_csd_addr;
extern char *mmc_name;

#ifdef CONFIG_GENERIC_MMC


int board_mmc_init(bd_t * bis)
{
	int ret_err;
	struct mmc * pmmc;

    MMCPRINTF("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    
	mmc_had_been_initialized = 0;
	mmc_ready_to_use = 0;

#if 0 // directly check eMMC device by customized init flow ( only for eMMC )
	rtkemmc_debug_msg = 1; // 1: enable debug message
	rtkemmc_off_error_msg_in_init_flow = 0; // 1: not show error message in initial stage
	ret_err = rtk_eMMC_init();
#else
	rtkemmc_debug_msg = 1; // 1: enable debug message
	rtkemmc_off_error_msg_in_init_flow = 1; // 1: not show error message in initial stage
	mmc_initial(1);	
	ret_err = 0;
#endif
	if( !ret_err ) {
		pmmc = &mmc_dev[0];
		sprintf(pmmc->name, mmc_name);
		pmmc->request = rtkemmc_request;
		pmmc->set_ios = rtkemmc_set_ios;
		pmmc->init = rtkemmc_init_setup;
		pmmc->getcd = NULL;
		pmmc->priv = NULL;
		pmmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;
#ifdef CONFIG_MMC_MODE_4BIT
		pmmc->host_caps = (MMC_MODE_4BIT | MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_HC);
#else
		pmmc->host_caps = (MMC_MODE_4BIT | MMC_MODE_8BIT | MMC_MODE_HS200 | MMC_MODE_HSDDR_52MHz | MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_HC);
#endif

		pmmc->f_min = 400000;
		pmmc->f_max = 50000000;
		pmmc->b_max = 256; // max transfer block size
		mmc_register(pmmc);
	}
	return ret_err;
}

int bringup_mmc_driver( void )
{
	int ret_err;
	struct mmc * mmc;
	int total_device_num = -1;
	int curr_device = 0;
	bool has_enh;
	bool usr_enh;

	MMCPRINTF("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    
	total_device_num = get_mmc_num();
	if ( total_device_num < 0 ) {
		printf("no registed mmc device\n");
		return curr_device;
	}
	
	if( mmc_had_been_initialized ) {
		return 0; // alwasy use slot 0
	}

	curr_device = 0; // alwasy use slot 0
	rtkemmc_debug_msg = 1; // 1: enable debug message
	rtkemmc_off_error_msg_in_init_flow = 1; // 1: not show error message in initial stage
	mmc = find_mmc_device(curr_device);

	has_enh = (mmc->part_support & ENHNCD_SUPPORT) != 0;
	usr_enh = has_enh && (mmc->part_attr & EXT_CSD_ENH_USR);

	if( mmc ) {
        EXECUTE_CUSTOMIZE_FUNC(0);
		mmc_init(mmc);
        EXECUTE_CUSTOMIZE_FUNC(0);
		printf("Device: %s\n", mmc->name);
		printf("Manufacturer ID: %x\n", mmc->cid[0] >> 24);
		printf("OEM: %x\n", (mmc->cid[0] >> 8) & 0xffff);
		printf("Name: %c%c%c%c%c \n", (mmc->cid[0] & 0xff),
		                              (mmc->cid[1] >> 24) & 0xff,
		                              (mmc->cid[1] >> 16) & 0xff,
				                      (mmc->cid[1] >> 8) & 0xff,
				                      (mmc->cid[1] >> 0) & 0xff);
		printf("Tran Speed: %lld\n", (u64)mmc->tran_speed);
		printf("Rd Block Len: %d\n", mmc->read_bl_len);
		printf("%s version %d.%d\n", IS_SD(mmc) ? "SD" : "MMC", EXTRACT_SDMMC_MAJOR_VERSION(mmc->version), EXTRACT_SDMMC_MINOR_VERSION(mmc->version));
		printf("High Capacity: %s\n", mmc->high_capacity ? "Yes" : "No");
		puts("Capacity: ");
		print_size((u64)mmc->capacity, "\n");
		puts("User Capacity: ");
		print_size(mmc->capacity_user, usr_enh ? " ENH" : "\n");
		puts("Boot Capacity: ");
		print_size(mmc->capacity_boot, has_enh ? " ENH\n" : "\n");
		puts("RPMB Capacity: ");
		print_size(mmc->capacity_rpmb, has_enh ? " ENH\n" : "\n");
		printf("Bus Width: %d-bit\n", mmc->bus_width);
		printf("Speed: ");
		if (mmc->boot_caps & MMC_MODE_HS200)
			printf("HS200\n");
		else if (mmc->boot_caps & MMC_MODE_HSDDR_52MHz)
			printf("DDR50\n");
		else
			printf("SDR50\n");
		
		ret_err = curr_device;
		
		mmc_had_been_initialized = 1;
		if( mmc->capacity ) {
			mmc_ready_to_use = 1;
		}
		else {
			mmc_ready_to_use = 0;	
		}
	}
	else {
		printf("no mmc device at slot %x\n", curr_device);
		ret_err = -999;
	}
	rtkemmc_debug_msg = 0; // 0: off cmd message
	rtkemmc_off_error_msg_in_init_flow = 0; // 0: show error message after init done
	return ret_err;
}

#endif // end of CONFIG_GENERIC_MMC
