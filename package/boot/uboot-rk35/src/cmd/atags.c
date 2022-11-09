// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 *
 */

#include <common.h>
#include <asm/arch-rockchip/rk_atags.h>
#if CONFIG_IS_ENABLED(TINY_FRAMEWORK)
#include <debug_uart.h>
#endif

static void atags_stat(void)
{
	u32 start = ATAGS_PHYS_BASE, end = ATAGS_PHYS_BASE + ATAGS_SIZE;
	u32 in_use = 0, in_available = 0;
	struct tag *t;

	if (!atags_is_available())
		return;

	for_each_tag(t, (struct tag *)ATAGS_PHYS_BASE) {
		if (atags_overflow(t))
			return;

		if (atags_bad_magic(t->hdr.magic))
			return;

		in_use += (t->hdr.size << 2);
	}

	in_available = ATAGS_SIZE - in_use;

	printf("ATAGS state:\n");
	printf("              addr = 0x%08x ~ 0x%08x\n", start, end);
	printf("        Total size = 0x%08x\n", ATAGS_SIZE);
	printf("       in use size = 0x%08x\n", in_use);
	printf("    available size = 0x%08x\n", in_available);
}

static void atags_print_tag(struct tag *t)
{
	u32 i;

	if (!t)
		return;

	switch (t->hdr.magic) {
	case ATAG_SERIAL:
		printf("[serial]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.serial.version);
		printf("    enable = 0x%x\n", t->u.serial.enable);
		printf("      addr = 0x%llx\n", t->u.serial.addr);
		printf("  baudrate = %d\n", t->u.serial.baudrate);
		printf("    m_mode = 0x%x\n", t->u.serial.m_mode);
		printf("        id = 0x%x\n", t->u.serial.id);
		for (i = 0; i < ARRAY_SIZE(t->u.serial.reserved); i++)
			printf("    res[%d] = 0x%x\n", i, t->u.serial.reserved[i]);
		printf("      hash = 0x%x\n", t->u.serial.hash);
		break;
	case ATAG_BOOTDEV:
		printf("[bootdev]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.bootdev.version);
		printf("   devtype = 0x%x\n", t->u.bootdev.devtype);
		printf("    devnum = 0x%x\n", t->u.bootdev.devnum);
		printf("      mode = 0x%x\n", t->u.bootdev.mode);
		for (i = 0; i < ARRAY_SIZE(t->u.bootdev.reserved); i++)
			printf("    res[%d] = 0x%x\n",
			       i, t->u.bootdev.reserved[i]);
		printf("      hash = 0x%x\n", t->u.bootdev.hash);
		break;
	case ATAG_TOS_MEM:
		printf("[tos_mem]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.tos_mem.version);
		printf("   tee_mem:\n");
		printf("            name = %s\n", t->u.tos_mem.tee_mem.name);
		printf("        phy_addr = 0x%llx\n", t->u.tos_mem.tee_mem.phy_addr);
		printf("            size = 0x%x\n", t->u.tos_mem.tee_mem.size);
		printf("           flags = 0x%x\n", t->u.tos_mem.tee_mem.flags);
		printf("   drm_mem:\n");
		printf("            name = %s\n", t->u.tos_mem.drm_mem.name);
		printf("        phy_addr = 0x%llx\n", t->u.tos_mem.drm_mem.phy_addr);
		printf("            size = 0x%x\n", t->u.tos_mem.drm_mem.size);
		printf("           flags = 0x%x\n", t->u.tos_mem.drm_mem.flags);
		for (i = 0; i < ARRAY_SIZE(t->u.tos_mem.reserved); i++)
			printf("   res[%d] = 0x%llx\n", i, t->u.tos_mem.reserved[i]);
		printf("     res1 = 0x%x\n", t->u.tos_mem.reserved1);
		printf("     hash = 0x%x\n", t->u.tos_mem.hash);
		break;
	case ATAG_DDR_MEM:
		printf("[ddr_mem]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("     count = 0x%x\n", t->u.ddr_mem.count);
		printf("   version = 0x%x\n", t->u.ddr_mem.version);
		for (i = 0; i < ARRAY_SIZE(t->u.ddr_mem.bank); i++)
			printf("  bank[%d] = 0x%llx\n", i, t->u.ddr_mem.bank[i]);
		printf("     flags = 0x%x\n", t->u.ddr_mem.flags);
		for (i = 0; i < ARRAY_SIZE(t->u.ddr_mem.data); i++)
			printf("  data[%d] = 0x%x\n", i, t->u.ddr_mem.data[i]);
		printf("      hash = 0x%x\n", t->u.ddr_mem.hash);
		break;
	case ATAG_RAM_PARTITION:
		printf("[ram_partition]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("   version = 0x%x\n", t->u.ram_part.version);
		printf("     count = 0x%x\n", t->u.ram_part.count);
		for (i = 0; i < ARRAY_SIZE(t->u.ram_part.reserved); i++)
			printf("    res[%d] = 0x%x\n", i, t->u.ram_part.reserved[i]);

		printf("    Part:  Name       Start Addr      Size\t\n");
		for (i = 0; i < ARRAY_SIZE(t->u.ram_part.part); i++)
			printf("%16s      0x%08llx      0x%08llx\n",
			       t->u.ram_part.part[i].name,
			       t->u.ram_part.part[i].start,
			       t->u.ram_part.part[i].size);
		for (i = 0; i < ARRAY_SIZE(t->u.ram_part.reserved1); i++)
			printf("   res1[%d] = 0x%x\n", i, t->u.ram_part.reserved1[i]);
		printf("      hash = 0x%x\n", t->u.ram_part.hash);
		break;
	case ATAG_ATF_MEM:
		printf("[atf_mem]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.atf_mem.version);
		printf("  phy_addr = 0x%llx\n", t->u.atf_mem.phy_addr);
		printf("      size = 0x%x\n", t->u.atf_mem.size);
		for (i = 0; i < ARRAY_SIZE(t->u.atf_mem.reserved); i++)
			printf("    res[%d] = 0x%x\n", i, t->u.atf_mem.reserved[i]);
		printf("      hash = 0x%x\n", t->u.atf_mem.hash);
		break;
	case ATAG_PUB_KEY:
		printf("[pub_key_mem]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.pub_key.version);
		printf("      hash = 0x%x\n", t->u.pub_key.hash);
		break;
	case ATAG_SOC_INFO:
		printf("[soc_info]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.soc.version);
		printf("      name = 0x%x\n", t->u.soc.name);
		printf("     flags = 0x%x\n", t->u.soc.flags);
		for (i = 0; i < ARRAY_SIZE(t->u.soc.reserved); i++)
			printf("    res[%d] = 0x%x\n", i, t->u.soc.reserved[i]);
		printf("      hash = 0x%x\n", t->u.soc.hash);
		break;
	case ATAG_BOOT1_PARAM:
		printf("[boot1 param]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("   version = 0x%x\n", t->u.boot1p.version);
		for (i = 0; i < ARRAY_SIZE(t->u.boot1p.param); i++)
			printf("  param[%d] = 0x%x\n", i, t->u.boot1p.param[i]);
		for (i = 0; i < ARRAY_SIZE(t->u.boot1p.reserved); i++)
			printf("    res[%d] = 0x%x\n", i, t->u.boot1p.reserved[i]);
		printf("      hash = 0x%x\n", t->u.boot1p.hash);
		break;
	case ATAG_CORE:
		printf("[core]:\n");
		printf("     magic = 0x%x\n", t->hdr.magic);
		printf("      size = 0x%x\n\n", t->hdr.size << 2);
		printf("     flags = 0x%x\n", t->u.core.flags);
		printf("  pagesize = 0x%x\n", t->u.core.pagesize);
		printf("   rootdev = 0x%x\n", t->u.core.rootdev);
		break;
	default:
		printf("%s: magic(%x) is not support\n", __func__, t->hdr.magic);
	}

	printf("\n");
}

static void atags_print_all_tags(void)
{
	struct tag *t;

	if (!atags_is_available())
		return;

	for_each_tag(t, (struct tag *)ATAGS_PHYS_BASE) {
		if (atags_overflow(t))
			return;

		if (atags_bad_magic(t->hdr.magic))
			return;

		atags_print_tag(t);
	}
}

static int do_dump_atags(cmd_tbl_t *cmdtp, int flag,
			 int argc, char * const argv[])
{
	atags_print_all_tags();
	atags_stat();

	return 0;
}

U_BOOT_CMD(
	atags, 1, 1, do_dump_atags,
	"Dump all atags",
	""
);
