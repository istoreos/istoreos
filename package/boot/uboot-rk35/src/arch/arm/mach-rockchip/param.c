// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <ram.h>
#include <asm/io.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/param.h>

DECLARE_GLOBAL_DATA_PTR;

#define SZ_4GB				0x100000000ULL

#ifndef CONFIG_SPL_BUILD
#define SDRAM_OFFSET(offset)		(CONFIG_SYS_SDRAM_BASE + (offset))
#define PARAM_DRAM_INFO_OFFSET		(SZ_32M)
#define PARAM_OPTEE_INFO_OFFSET		(SZ_32M + SZ_2M)

struct tos_param_t {
	u32 version;
	u32 checksum;
	struct {
		char name[8];
		s64 phy_addr;
		u32 size;
		u32 flags;
	} tee_mem;
	struct {
		char name[8];
		s64 phy_addr;
		u32 size;
		u32 flags;
	} drm_mem;
	s64 reserve[8];
};

static uint16_t trust_checksum(const uint8_t *buf, uint16_t len)
{
	uint16_t i, checksum = 0;

	for (i = 0; i < len; i++) {
		if (i % 2)
			checksum += buf[i] << 8;
		else
			checksum += buf[i];
	}
	checksum = ~checksum;

	return checksum;
}

struct memblock param_parse_atf_mem(void)
{
	struct memblock mem;

	mem.base = 0;
	mem.size = 0;

#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	struct tag *t = NULL;

	/*
	 * Get memory region of ATF
	 *
	 * 1. New way: atags info;
	 * 2. Leagcy way: 2MB size and start from ddr 0x0 offset;
	 */
	t = atags_get_tag(ATAG_ATF_MEM);
	if (t && t->u.atf_mem.size) {
		mem.base = t->u.atf_mem.phy_addr;
		mem.size = t->u.atf_mem.size;
		/* Sanity */
		if (mem.base + mem.size > SDRAM_OFFSET(SZ_1M)) {
			printf("%s: ATF reserved region is not within 0-1MB "
			       "offset(0x%08llx-0x%08llx)!\n",
			       __func__, (u64)mem.base, (u64)mem.base + mem.size);
			return mem;
		}
	}
#endif

	/* Legacy */
	if (!mem.size) {
		if (IS_ENABLED(CONFIG_ARM64) ||
		    IS_ENABLED(CONFIG_ARM64_BOOT_AARCH32)) {
			mem.base = SDRAM_OFFSET(0);
			mem.size = SZ_1M;
		}
	}

	debug("ATF: 0x%llx - 0x%llx\n", (u64)mem.base, (u64)mem.base + mem.size);

	return mem;
}

struct memblock param_parse_optee_mem(void)
{
	struct tos_param_t *tos_parameter;
	struct memblock mem;
	u32 checksum;

	mem.base = 0;
	mem.size = 0;

#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	struct tag *t = NULL;

	/*
	 * Get memory region of OP-TEE
	 *
	 * 1. New way: atags info;
	 * 2. Leagcy way: info in ddr 34M offset;
	 */
	t = atags_get_tag(ATAG_TOS_MEM);
	if (t && (t->u.tos_mem.tee_mem.flags == 1)) {
		mem.base = t->u.tos_mem.tee_mem.phy_addr;
		mem.size = t->u.tos_mem.tee_mem.size;
	}
#endif

	/* Legacy */
	if (!mem.size) {
		tos_parameter =
		(struct tos_param_t *)(SDRAM_OFFSET(PARAM_OPTEE_INFO_OFFSET));
		checksum =
		trust_checksum((uint8_t *)(unsigned long)tos_parameter + 8,
			       sizeof(struct tos_param_t) - 8);
		if ((checksum == tos_parameter->checksum) &&
		    (tos_parameter->tee_mem.flags == 1)) {
			mem.base = tos_parameter->tee_mem.phy_addr;
			mem.size = tos_parameter->tee_mem.size;
		}
	}

	if (mem.size)
		gd->flags |= GD_FLG_BL32_ENABLED;

	debug("TOS: 0x%llx - 0x%llx\n", (u64)mem.base, (u64)mem.base + mem.size);

	return mem;
}

struct memblock param_parse_common_resv_mem(void)
{
	struct memblock mem;

#if defined(CONFIG_ARM64)
	mem.base = SDRAM_OFFSET(SZ_1M);
	mem.size = SZ_1M;
/*
 * The ARMv8 platform enabling AArch32 mode should reserve memory the same
 * as AArch64 mode(because there is no difference about ATF), only some
 * platform has special request, they are: RK3308.
 */
#elif defined(CONFIG_ARM64_BOOT_AARCH32) && !defined(CONFIG_ROCKCHIP_RK3308)
	mem.base = SDRAM_OFFSET(SZ_1M);
	mem.size = SZ_1M;
#else
	mem.size = 0;
#endif
	return mem;
}

int param_parse_bootdev(char **devtype, char **devnum)
{
#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	struct tag *t;

	t = atags_get_tag(ATAG_BOOTDEV);
	if (t) {
		switch (t->u.bootdev.devtype) {
#ifdef CONFIG_DM_MMC
		case BOOT_TYPE_EMMC:
			*devtype = "mmc";
			*devnum = "0";
			break;
		case BOOT_TYPE_SD0:
		case BOOT_TYPE_SD1:
			*devtype = "mmc";
			*devnum = "1";
			/*
			 * If preloader does not pass sdupdate value, we treat it
			 * as a unknown card and call the rkimgtest cmd to find
			 * out what it is.
			 *
			 * If preloader pass sdupdate value as an update card,
			 * we just set "sdfwupdate" to bootargs instead of
			 * calling rkimgtest cmd which consumes time.
			 */
			if (t->u.bootdev.sdupdate == SD_UNKNOWN_CARD) {
				run_command("mmc dev 1", 0);
				run_command("rkimgtest mmc 1", 0);
			} else if (t->u.bootdev.sdupdate == SD_UPDATE_CARD) {
				env_update("bootargs", "sdfwupdate");
			}
			break;
#endif
#if defined(CONFIG_RKNAND) || defined(CONFIG_RKNANDC_NAND)
		case BOOT_TYPE_NAND:
			*devtype = "rknand";
			*devnum = "0";
			break;
#endif
#ifdef CONFIG_RKSFC_NAND
		case BOOT_TYPE_SPI_NAND:
			*devtype = "spinand";
			*devnum = "0";
			break;
#endif
#ifdef CONFIG_RKSFC_NOR
		case BOOT_TYPE_SPI_NOR:
			*devtype = "spinor";
			*devnum = "1";
			break;
#endif
#ifdef CONFIG_DM_RAMDISK
		case BOOT_TYPE_RAM:
			*devtype = "ramdisk";
			*devnum = "0";
			break;
#endif
#ifdef CONFIG_NAND
		case BOOT_TYPE_MTD_BLK_NAND:
			*devtype = "mtd";
			*devnum = "0";
			break;
#endif
#ifdef CONFIG_MTD_SPI_NAND
		case BOOT_TYPE_MTD_BLK_SPI_NAND:
			*devtype = "mtd";
			*devnum = "1";
			break;
#endif
#ifdef CONFIG_SPI_FLASH_MTD
		case BOOT_TYPE_MTD_BLK_SPI_NOR:
			*devtype = "mtd";
			*devnum = "2";
			break;
#endif
		default:
			printf("Unknown bootdev type: 0x%x\n",
			       t->u.bootdev.devtype);
			return -EINVAL;
		}

		return 0;
	}
#endif

	return -ENOSYS;
}
#endif

static phys_size_t ddr_mem_get_usable_size(u64 base, u64 size)
{
	return (base + size >= CONFIG_SYS_SDRAM_BASE + SDRAM_MAX_SIZE) ?
	       (CONFIG_SYS_SDRAM_BASE + SDRAM_MAX_SIZE - base) : size;
}

struct memblock *param_parse_ddr_mem(int *out_count)
{
	struct udevice *dev;
	struct memblock *mem;
	struct ram_info ram;
	int i, ret, count;

	/*
	 * Get memory region of DDR
	 *
	 * 1. New: atags info;
	 * 2. Leagcy: os register;
	 */
#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	struct tag *t;
	u64 base, size;
	int n;

	t = atags_get_tag(ATAG_DDR_MEM);
	if (t && t->u.ddr_mem.count) {
		/* extend top ram size */
		if (t->u.ddr_mem.flags & DDR_MEM_FLG_EXT_TOP)
			gd->ram_top_ext_size = t->u.ddr_mem.data[0];

		/* normal ram size */
		count = t->u.ddr_mem.count;
		mem = calloc(count + MEM_RESV_COUNT, sizeof(*mem));
		if (!mem) {
			printf("Calloc ddr memory failed\n");
			return 0;
		}

		for (i = 0, n = 0; i < count; i++, n++) {
			base = t->u.ddr_mem.bank[i];
			size = t->u.ddr_mem.bank[i + count];

			/* 0~4GB */
			if (base < SZ_4GB) {
				mem[n].base = base;
				mem[n].size = ddr_mem_get_usable_size(base, size);
				if (base + size > SZ_4GB) {
					n++;
					mem[n].base_u64 = SZ_4GB;
					mem[n].size_u64 = base + size - SZ_4GB;
				}
			} else {
				/* 4GB+ */
				mem[n].base_u64 = base;
				mem[n].size_u64 = size;
			}

			assert(n < count + MEM_RESV_COUNT);
		}

		*out_count = n;
		return mem;
	}
#endif

	/* Leagcy */
	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		debug("DRAM init failed: %d\n", ret);
		return NULL;
	}
	ret = ram_get_info(dev, &ram);
	if (ret) {
		debug("Cannot get DRAM size: %d\n", ret);
		return NULL;
	}

	debug("SDRAM base=%lx, size=%lx\n",
	      (unsigned long)ram.base, (unsigned long)ram.size);

	count = 1;
	mem = calloc(1, sizeof(*mem));
	if (!mem) {
		printf("Calloc ddr memory failed\n");
		return 0;
	}

	for (i = 0; i < count; i++) {
		mem[i].base = CONFIG_SYS_SDRAM_BASE;
		mem[i].size = ddr_mem_get_usable_size(mem[i].base, ram.size);
	}

	*out_count = count;
	return mem;
}

#ifndef CONFIG_BIDRAM
/*
 * init_bank=0: called from dram_init_banksize()
 * init_bank=0: called from dram_init()
 */
phys_size_t param_simple_parse_ddr_mem(int init_bank)
{
	struct memblock *list;
	int i, count;

	list = param_parse_ddr_mem(&count);
	if (!list) {
		printf("Can't get dram banks\n");
		return 0;
	}

	if (count > CONFIG_NR_DRAM_BANKS) {
		printf("Dram banks num=%d, over %d\n", count, CONFIG_NR_DRAM_BANKS);
		return 0;
	}

	if (!init_bank) {
		i = count - 1;
		return ddr_mem_get_usable_size(list[i].base, list[i].size);
	}

	for (i = 0; i < count; i++) {
		gd->bd->bi_dram[i].start = list[i].base;
		gd->bd->bi_dram[i].size =
			ddr_mem_get_usable_size(list[i].base, list[i].size);
		debug("bank[%d]: 0x%08lx - 0x%08lx\n", i,
		      (ulong)gd->bd->bi_dram[i].start,
		      (ulong)gd->bd->bi_dram[i].start +
		      (ulong)gd->bd->bi_dram[i].size);
	}

	return 0;
}
#endif

int param_parse_pre_serial(void)
{
#if defined(CONFIG_ROCKCHIP_PRELOADER_SERIAL) && \
    defined(CONFIG_ROCKCHIP_PRELOADER_ATAGS)
	struct tag *t;

	t = atags_get_tag(ATAG_SERIAL);
	if (t) {
		gd->serial.using_pre_serial = 1;
		gd->serial.enable = t->u.serial.enable;
		gd->serial.baudrate = t->u.serial.baudrate;
		gd->serial.addr = t->u.serial.addr;
		gd->serial.id = t->u.serial.id;
		gd->baudrate = CONFIG_BAUDRATE;
		debug("preloader: enable=%d, addr=0x%lx, baudrate=%d, id=%d\n",
		      gd->serial.enable, gd->serial.addr,
		      gd->serial.baudrate, gd->serial.id);
	} else
#endif
	{
		gd->baudrate = CONFIG_BAUDRATE;
		gd->serial.baudrate = CONFIG_BAUDRATE;
		gd->serial.addr = CONFIG_DEBUG_UART_BASE;
	}

	return 0;
}

int param_parse_pubkey_fuse_programmed(void)
{
#ifdef CONFIG_ROCKCHIP_PRELOADER_ATAGS
	struct tag *t;

	t = atags_get_tag(ATAG_PUB_KEY);
	if (t) {
		/* Pass if efuse/otp programmed */
		if (t->u.pub_key.flag == PUBKEY_FUSE_PROGRAMMED)
			env_update("bootargs", "fuse.programmed=1");
		else
			env_update("bootargs", "fuse.programmed=0");
	}
#endif
	return 0;
}

