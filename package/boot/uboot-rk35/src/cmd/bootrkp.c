/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <attestation_key.h>
#include <bootm.h>
#include <boot_rkimg.h>
#include <keymaster.h>
#include <console.h>
#include <image.h>
#include <malloc.h>
#include <sysmem.h>
#include <linux/libfdt.h>
#include <asm/arch-rockchip/hotkey.h>
#include <asm/arch-rockchip/resource_img.h>
#include <asm/arch-rockchip/boot_mode.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_ROCKCHIP_CRC
#define tole(x) cpu_to_le32(x)

/* Table of CRC-32's of all single-byte values (made by make_crc_table) */
static const uint32_t crc_table[256] = {
	tole(0x00000000L), tole(0x04c10db7L), tole(0x09821b6eL), tole(0x0d4316d9L),
	tole(0x130436dcL), tole(0x17c53b6bL), tole(0x1a862db2L), tole(0x1e472005L),
	tole(0x26086db8L), tole(0x22c9600fL), tole(0x2f8a76d6L), tole(0x2b4b7b61L),
	tole(0x350c5b64L), tole(0x31cd56d3L), tole(0x3c8e400aL), tole(0x384f4dbdL),
	tole(0x4c10db70L), tole(0x48d1d6c7L), tole(0x4592c01eL), tole(0x4153cda9L),
	tole(0x5f14edacL), tole(0x5bd5e01bL), tole(0x5696f6c2L), tole(0x5257fb75L),
	tole(0x6a18b6c8L), tole(0x6ed9bb7fL), tole(0x639aada6L), tole(0x675ba011L),
	tole(0x791c8014L), tole(0x7ddd8da3L), tole(0x709e9b7aL), tole(0x745f96cdL),
	tole(0x9821b6e0L), tole(0x9ce0bb57L), tole(0x91a3ad8eL), tole(0x9562a039L),
	tole(0x8b25803cL), tole(0x8fe48d8bL), tole(0x82a79b52L), tole(0x866696e5L),
	tole(0xbe29db58L), tole(0xbae8d6efL), tole(0xb7abc036L), tole(0xb36acd81L),
	tole(0xad2ded84L), tole(0xa9ece033L), tole(0xa4aff6eaL), tole(0xa06efb5dL),
	tole(0xd4316d90L), tole(0xd0f06027L), tole(0xddb376feL), tole(0xd9727b49L),
	tole(0xc7355b4cL), tole(0xc3f456fbL), tole(0xceb74022L), tole(0xca764d95L),
	tole(0xf2390028L), tole(0xf6f80d9fL), tole(0xfbbb1b46L), tole(0xff7a16f1L),
	tole(0xe13d36f4L), tole(0xe5fc3b43L), tole(0xe8bf2d9aL), tole(0xec7e202dL),
	tole(0x34826077L), tole(0x30436dc0L), tole(0x3d007b19L), tole(0x39c176aeL),
	tole(0x278656abL), tole(0x23475b1cL), tole(0x2e044dc5L), tole(0x2ac54072L),
	tole(0x128a0dcfL), tole(0x164b0078L), tole(0x1b0816a1L), tole(0x1fc91b16L),
	tole(0x018e3b13L), tole(0x054f36a4L), tole(0x080c207dL), tole(0x0ccd2dcaL),
	tole(0x7892bb07L), tole(0x7c53b6b0L), tole(0x7110a069L), tole(0x75d1addeL),
	tole(0x6b968ddbL), tole(0x6f57806cL), tole(0x621496b5L), tole(0x66d59b02L),
	tole(0x5e9ad6bfL), tole(0x5a5bdb08L), tole(0x5718cdd1L), tole(0x53d9c066L),
	tole(0x4d9ee063L), tole(0x495fedd4L), tole(0x441cfb0dL), tole(0x40ddf6baL),
	tole(0xaca3d697L), tole(0xa862db20L), tole(0xa521cdf9L), tole(0xa1e0c04eL),
	tole(0xbfa7e04bL), tole(0xbb66edfcL), tole(0xb625fb25L), tole(0xb2e4f692L),
	tole(0x8aabbb2fL), tole(0x8e6ab698L), tole(0x8329a041L), tole(0x87e8adf6L),
	tole(0x99af8df3L), tole(0x9d6e8044L), tole(0x902d969dL), tole(0x94ec9b2aL),
	tole(0xe0b30de7L), tole(0xe4720050L), tole(0xe9311689L), tole(0xedf01b3eL),
	tole(0xf3b73b3bL), tole(0xf776368cL), tole(0xfa352055L), tole(0xfef42de2L),
	tole(0xc6bb605fL), tole(0xc27a6de8L), tole(0xcf397b31L), tole(0xcbf87686L),
	tole(0xd5bf5683L), tole(0xd17e5b34L), tole(0xdc3d4dedL), tole(0xd8fc405aL),
	tole(0x6904c0eeL), tole(0x6dc5cd59L), tole(0x6086db80L), tole(0x6447d637L),
	tole(0x7a00f632L), tole(0x7ec1fb85L), tole(0x7382ed5cL), tole(0x7743e0ebL),
	tole(0x4f0cad56L), tole(0x4bcda0e1L), tole(0x468eb638L), tole(0x424fbb8fL),
	tole(0x5c089b8aL), tole(0x58c9963dL), tole(0x558a80e4L), tole(0x514b8d53L),
	tole(0x25141b9eL), tole(0x21d51629L), tole(0x2c9600f0L), tole(0x28570d47L),
	tole(0x36102d42L), tole(0x32d120f5L), tole(0x3f92362cL), tole(0x3b533b9bL),
	tole(0x031c7626L), tole(0x07dd7b91L), tole(0x0a9e6d48L), tole(0x0e5f60ffL),
	tole(0x101840faL), tole(0x14d94d4dL), tole(0x199a5b94L), tole(0x1d5b5623L),
	tole(0xf125760eL), tole(0xf5e47bb9L), tole(0xf8a76d60L), tole(0xfc6660d7L),
	tole(0xe22140d2L), tole(0xe6e04d65L), tole(0xeba35bbcL), tole(0xef62560bL),
	tole(0xd72d1bb6L), tole(0xd3ec1601L), tole(0xdeaf00d8L), tole(0xda6e0d6fL),
	tole(0xc4292d6aL), tole(0xc0e820ddL), tole(0xcdab3604L), tole(0xc96a3bb3L),
	tole(0xbd35ad7eL), tole(0xb9f4a0c9L), tole(0xb4b7b610L), tole(0xb076bba7L),
	tole(0xae319ba2L), tole(0xaaf09615L), tole(0xa7b380ccL), tole(0xa3728d7bL),
	tole(0x9b3dc0c6L), tole(0x9ffccd71L), tole(0x92bfdba8L), tole(0x967ed61fL),
	tole(0x8839f61aL), tole(0x8cf8fbadL), tole(0x81bbed74L), tole(0x857ae0c3L),
	tole(0x5d86a099L), tole(0x5947ad2eL), tole(0x5404bbf7L), tole(0x50c5b640L),
	tole(0x4e829645L), tole(0x4a439bf2L), tole(0x47008d2bL), tole(0x43c1809cL),
	tole(0x7b8ecd21L), tole(0x7f4fc096L), tole(0x720cd64fL), tole(0x76cddbf8L),
	tole(0x688afbfdL), tole(0x6c4bf64aL), tole(0x6108e093L), tole(0x65c9ed24L),
	tole(0x11967be9L), tole(0x1557765eL), tole(0x18146087L), tole(0x1cd56d30L),
	tole(0x02924d35L), tole(0x06534082L), tole(0x0b10565bL), tole(0x0fd15becL),
	tole(0x379e1651L), tole(0x335f1be6L), tole(0x3e1c0d3fL), tole(0x3add0088L),
	tole(0x249a208dL), tole(0x205b2d3aL), tole(0x2d183be3L), tole(0x29d93654L),
	tole(0xc5a71679L), tole(0xc1661bceL), tole(0xcc250d17L), tole(0xc8e400a0L),
	tole(0xd6a320a5L), tole(0xd2622d12L), tole(0xdf213bcbL), tole(0xdbe0367cL),
	tole(0xe3af7bc1L), tole(0xe76e7676L), tole(0xea2d60afL), tole(0xeeec6d18L),
	tole(0xf0ab4d1dL), tole(0xf46a40aaL), tole(0xf9295673L), tole(0xfde85bc4L),
	tole(0x89b7cd09L), tole(0x8d76c0beL), tole(0x8035d667L), tole(0x84f4dbd0L),
	tole(0x9ab3fbd5L), tole(0x9e72f662L), tole(0x9331e0bbL), tole(0x97f0ed0cL),
	tole(0xafbfa0b1L), tole(0xab7ead06L), tole(0xa63dbbdfL), tole(0xa2fcb668L),
	tole(0xbcbb966dL), tole(0xb87a9bdaL), tole(0xb5398d03L), tole(0xb1f880b4L)
};

#define DO_CRC(x) crc = tab[((crc >> 24) ^ (x)) & 255] ^ (crc << 8)

static uint32_t crc32_rk(uint32_t crc, const unsigned char *s, uint32_t len)
{
	const uint32_t *tab;

	tab = crc_table;
	crc = cpu_to_le32(crc);

	do {
		DO_CRC(*s++);
	} while (--len);

	return le32_to_cpu(crc);
}

#undef DO_CRC

static u32 crc32_verify(unsigned char *data, u32 size)
{
	u32 crc_check = 0, crc_calc = 0;
	int i = 0;

	if (size <= 4)
		return 0;

	size -= 4;
	for (i = 3; i >= 0; i--)
		crc_check = (crc_check << 8) + (*(data + size + i));

	crc_calc = crc32_rk(0, data, size);

	return (crc_calc == crc_check) ? crc_check : 0;
}
#endif

#if !defined(CONFIG_ARM64)
#ifdef CONFIG_LMB
static void boot_start_lmb(bootm_headers_t *images)
{
	lmb_init(&images->lmb);
#ifdef CONFIG_NR_DRAM_BANKS
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		lmb_add(&images->lmb, gd->bd->bi_dram[i].start,
			gd->bd->bi_dram[i].size);
	}
#else
	ulong		mem_start;
	phys_size_t	mem_size;

	mem_start = env_get_bootm_low();
	mem_size = env_get_bootm_size();
	lmb_add(&images->lmb, (phys_addr_t)mem_start, mem_size);
#endif
	arch_lmb_reserve(&images->lmb);
	board_lmb_reserve(&images->lmb);
}
#else
static inline void boot_start_lmb(bootm_headers_t *images) { }
#endif

static void boot_lmb_init(bootm_headers_t *images)
{
	boot_start_lmb(images);
	images->state = BOOTM_STATE_OS_GO;
}
#endif

/*
 * non-OTA packaged kernel.img & boot.img return the image size on success,
 * and a negative value on error.
 */
static int read_rockchip_image(struct blk_desc *dev_desc,
			       disk_partition_t *part, void *dst)
{
	struct rockchip_image *img = dst;
	int header_len = 8;
	int cnt, ret;
#ifdef CONFIG_ROCKCHIP_CRC
	u32 crc32;
#endif
	ret = blk_dread(dev_desc, part->start, 1, img);
	if (ret != 1)
		return -EIO;

	if (img->tag != TAG_KERNEL) {
		printf("Invalid %s image tag(0x%x)\n", part->name, img->tag);
		return -EINVAL;
	}

	/* total size = image size + 8 bytes header + 4 bytes crc32 */
	cnt = DIV_ROUND_UP(img->size + 8 + 4, RK_BLK_SIZE);
	if (!sysmem_alloc_base_by_name((const char *)part->name,
				       (phys_addr_t)dst,
				       cnt * dev_desc->blksz))
		return -ENXIO;

	ret = blk_dread(dev_desc, part->start, cnt, dst);
	if (ret != cnt) {
		printf("Failed to read %s part, blkcnt=%d\n", part->name, ret);
		return -EIO;
	} else {
		ret = img->size;
	}
	memcpy(dst, dst + header_len, img->size);

#ifdef CONFIG_ROCKCHIP_CRC
	printf("%s image rk crc32 verify... ", part->name);
	crc32 = crc32_verify((uchar *)(ulong)dst, img->size + 4);
	if (!crc32) {
		printf("fail!\n");
		ret = -EINVAL;
	} else {
		printf("okay.\n");
	}
#endif
	return ret;
}

static int boot_rockchip_image(struct blk_desc *dev_desc,
			       disk_partition_t *boot_part)
{
	disk_partition_t kernel_part;
	ulong ramdisk_addr_r;
	ulong kernel_addr_r;
	ulong fdt_addr_r;
	int ramdisk_size;
	int kernel_size;
	int fdt_size;
	int ret;

	printf("\n## Booting Rockchip Format Image\n");

	ramdisk_addr_r = env_get_ulong("ramdisk_addr_r", 16, 0);
	kernel_addr_r = env_get_ulong("kernel_addr_r", 16, 0);
	fdt_addr_r = env_get_ulong("fdt_addr_r", 16, 0);

	ret = part_get_info_by_name(dev_desc, PART_KERNEL, &kernel_part);
	if (ret < 0) {
		printf("Could not find kernel partition, ret=%d\n", ret);
		return -EINVAL;
	}

	kernel_size = read_rockchip_image(dev_desc, &kernel_part,
					  (void *)kernel_addr_r);
	if (kernel_size < 0) {
		printf("Failed to read kernel image, ret=%d\n", ret);
		return -EINVAL;
	}

	ramdisk_size = read_rockchip_image(dev_desc, boot_part,
					   (void *)ramdisk_addr_r);
	if (ramdisk_size < 0)
		ramdisk_size = 0;

	if (gd->fdt_blob != (void *)fdt_addr_r) {
		fdt_size = rockchip_read_dtb_file((void *)fdt_addr_r);
		if (fdt_size < 0) {
			printf("Failed to read fdt, ret=%d\n", fdt_size);
			return -EINVAL;
		}
	}

	env_set("bootm-no-reloc", "y");

	printf("fdt	 @ 0x%08lx (0x%08x)\n", fdt_addr_r, fdt_totalsize(fdt_addr_r));
	printf("kernel   @ 0x%08lx (0x%08x)\n", kernel_addr_r, kernel_size);
	printf("ramdisk  @ 0x%08lx (0x%08x)\n", ramdisk_addr_r, ramdisk_size);

#if defined(CONFIG_ARM64)
	char cmdbuf[64];

	snprintf(cmdbuf, 64, "booti 0x%lx 0x%lx:0x%x 0x%lx",
		 kernel_addr_r, ramdisk_addr_r, ramdisk_size, fdt_addr_r);
	run_command(cmdbuf, 0);
#else
	/* We asume it's always zImage on 32-bit platform */
	ulong kaddr_c = env_get_ulong("kernel_addr_c", 16, 0);
	ulong kaddr_r, kaddr, ksize;

	if (kernel_addr_r && !kaddr_c) {
		kaddr_c = kernel_addr_r;
		kaddr_r = CONFIG_SYS_SDRAM_BASE;
	}

	if (!sysmem_free((phys_addr_t)kaddr_c)) {
		kaddr = kaddr_r;
		ksize = kernel_size * 100 / 45 ; /* Ratio: 45% */
		ksize = ALIGN(ksize, dev_desc->blksz);
		if (!sysmem_alloc_base(MEM_UNCOMP_KERNEL,
				       (phys_addr_t)kaddr, ksize))
			return -ENOMEM;
	}

	boot_lmb_init(&images);
	images.ep = kernel_addr_r;
	images.initrd_start = ramdisk_addr_r;
	images.initrd_end = ramdisk_addr_r + ramdisk_size;
	images.ft_addr = (void *)fdt_addr_r;
	images.ft_len = fdt_totalsize(fdt_addr_r);
	do_bootm_linux(0, 0, NULL, &images);
#endif

	return 0;
}

static int do_boot_rockchip(cmd_tbl_t *cmdtp, int flag,
			    int argc, char *const argv[])
{
	char *part_name = PART_BOOT;
	struct blk_desc *dev_desc;
	disk_partition_t part;
	int ret;

	dev_desc = rockchip_get_bootdev();
	if (!dev_desc) {
		printf("dev_desc is NULL!\n");
		return CMD_RET_FAILURE;
	}

#ifdef CONFIG_ANDROID_KEYMASTER_CA
	/* load attestation key from misc partition. */
	ret = part_get_info_by_name(dev_desc, PART_MISC, &part);
	if (ret < 0)
		printf("Could not find misc partition\n");
	else
		load_attestation_key(dev_desc, &part);
#endif

#ifdef CONFIG_FASTBOOT_OEM_UNLOCK
	/* read oem unlock status and attach to bootargs */
	char oem_unlock[30] = {0};
	TEEC_Result result;
	uint8_t unlock = 0;

	result = trusty_read_oem_unlock(&unlock);
	if (result) {
		printf("Failed to read oem unlock status, ret=%d\n", result);
	} else {
		snprintf(oem_unlock, sizeof(oem_unlock),
			 "androidboot.oem_unlocked=%d", unlock);
		env_update("bootargs", oem_unlock);
	}
#endif
	if (rockchip_get_boot_mode() == BOOT_MODE_RECOVERY)
		part_name = PART_RECOVERY;

	ret = part_get_info_by_name(dev_desc, part_name, &part);
	if (ret < 0) {
		printf("Could not find %s part\n", part.name);
		return CMD_RET_FAILURE;
	}

	return boot_rockchip_image(dev_desc, &part) ? CMD_RET_FAILURE : 0;
}

U_BOOT_CMD(
	bootrkp,  1,     1,      do_boot_rockchip,
	"Boot Linux Image from rockchip image type",
	"kernel.img: zImage/Image\n"
	"boot.img: ramdisk\n"
	"resource.img: dtb, u-boot logo, kernel logo"
);
