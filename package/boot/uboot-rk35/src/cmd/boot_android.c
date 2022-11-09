/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <android_bootloader.h>
#include <android_avb/avb_version.h>
#include <android_avb/avb_ab_flow.h>
#include <android_avb/avb_ops_user.h>
#include <android_cmds.h>
#include <malloc.h>
#include <common.h>
#include <bootm.h>
#include <command.h>
#include <android_bootloader_message.h>
#include <android_avb/rk_avb_ops_user.h>
#include <android_avb/avb_atx_ops.h>

static int do_boot_android(cmd_tbl_t *cmdtp, int flag, int argc,
			   char * const argv[])
{
	unsigned long load_address;
	int ret = CMD_RET_SUCCESS;
	char *addr_arg_endp, *addr_str;
	struct blk_desc *dev_desc;

	if (argc < 3)
		return CMD_RET_USAGE;
	if (argc > 5)
		return CMD_RET_USAGE;

	if (argc >= 5) {
		load_address = simple_strtoul(argv[4], &addr_arg_endp, 16);
		if (addr_arg_endp == argv[4] || *addr_arg_endp != '\0')
			return CMD_RET_USAGE;
	} else {
		addr_str = env_get("kernel_addr_r");
		if (addr_str)
			load_address = simple_strtoul(addr_str, NULL, 16);
		else
			load_address = CONFIG_SYS_LOAD_ADDR;
	}

#if defined(CONFIG_ARM64)
	/* ARM64 kernel load addr need to align to 0x80000, and android boot.img
	 * have a 2KB header, need to reserve space for it.
	 */
	load_address &= ~0x7ffff;
#endif

	dev_desc = blk_get_dev(argv[1], simple_strtoul(argv[2], NULL, 16));
	if (!dev_desc) {
		printf("Could not get %s %s\n", argv[1], argv[2]);
		return CMD_RET_FAILURE;
	}

	ret = android_bootloader_boot_flow(dev_desc, load_address);
	if (ret < 0) {
		printf("Android boot failed, error %d.\n", ret);
		return CMD_RET_FAILURE;
	}
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	boot_android, 5, 0, do_boot_android,
	"Execute the Android Bootloader flow.",
	"<interface> <dev[:part|;part_name]> <slot> [<kernel_addr>]\n"
	"    - Load the Boot Control Block (BCB) from the partition 'part' on\n"
	"      device type 'interface' instance 'dev' to determine the boot\n"
	"      mode, and load and execute the appropriate kernel.\n"
	"      In normal and recovery mode, the kernel will be loaded from\n"
	"      the corresponding \"boot\" partition. In bootloader mode, the\n"
	"      command defined in the \"fastbootcmd\" variable will be\n"
	"      executed.\n"
	"      On Android devices with multiple slots, the pass 'slot' is\n"
	"      used to load the appropriate kernel. The standard slot names\n"
	"      are 'a' and 'b'.\n"
	"    - If 'part_name' is passed, preceded with a ; instead of :, the\n"
	"      partition name whose label is 'part_name' will be looked up in\n"
	"      the partition table. This is commonly the \"misc\" partition.\n"
);

#ifdef CONFIG_ANDROID_AB
int do_avb_init_ab_metadata(cmd_tbl_t *cmdtp, int flag,
			    int argc, char * const argv[])
{
	AvbOps *ops;
	AvbABData ab_data;

	memset(&ab_data, 0, sizeof(AvbABData));
	debug("sizeof(AvbABData) = %d\n", (int)(size_t)sizeof(AvbABData));
	if (argc != 1)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	avb_ab_data_init(&ab_data);
	if (ops->ab_ops->write_ab_metadata(ops->ab_ops, &ab_data) != 0) {
		printf("do_avb_init_ab_metadata error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("Initialize ab data to misc partition success.\n");
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_ab_mark_slot_active(cmd_tbl_t *cmdtp, int flag,
			       int argc, char * const argv[])
{
	AvbOps *ops;
	unsigned int slot_number;

	if (argc != 2)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	slot_number = simple_strtoul(argv[1], NULL, 16);
	if (avb_ab_mark_slot_active(ops->ab_ops, slot_number) != 0) {
		printf("avb_ab_mark_slot_active error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("Mark slot %d active successfully.\n", slot_number);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_ab_mark_slot_unbootable(cmd_tbl_t *cmdtp, int flag,
				   int argc, char * const argv[])
{
	AvbOps *ops;
	unsigned int slot_number;

	if (argc != 2)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	slot_number = simple_strtoul(argv[1], NULL, 16);
	if (avb_ab_mark_slot_unbootable(ops->ab_ops, slot_number) != 0) {
		printf("do_avb_ab_mark_slot_unbootable error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("Mark slot %d unbootable successfully.\n", slot_number);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_ab_mark_slot_successful(cmd_tbl_t *cmdtp, int flag,
				   int argc, char * const argv[])
{
	AvbOps *ops;
	unsigned int slot_number;

	if (argc != 2)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	slot_number = simple_strtoul(argv[1], NULL, 16);
	if (avb_ab_mark_slot_successful(ops->ab_ops, slot_number) != 0) {
		printf("do_avb_ab_mark_slot_successful error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_read_ab_metadata(cmd_tbl_t *cmdtp, int flag,
			    int argc, char * const argv[])
{
	AvbOps *ops;
	AvbABData ab_data;

	if (argc != 1)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->ab_ops->read_ab_metadata(ops->ab_ops, &ab_data) != 0) {
		printf("do_avb_write_ab_metadata error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("Slot A information:\n");
	printf("slot A: priority = %d, tries_remaining = %d,\
	       successful_boot = %d\n",
	       ab_data.slots[0].priority,
	       ab_data.slots[0].tries_remaining,
	       ab_data.slots[0].successful_boot);
	printf("Slot B information:\n");
	printf("slot B: priority = %d, tries_remaining = %d,\
	       successful_boot = %d\n",
	       ab_data.slots[1].priority,
	       ab_data.slots[1].tries_remaining,
	       ab_data.slots[1].successful_boot);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_write_ab_metadata(cmd_tbl_t *cmdtp, int flag,
			     int argc, char * const argv[])
{
	AvbOps *ops;
	AvbABData ab_data;

	if (argc != 1)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->ab_ops->write_ab_metadata(ops->ab_ops, &ab_data) != 0) {
		printf("do_avb_write_ab_metadata error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}
#endif

#ifdef CONFIG_ANDROID_AVB
int do_avb_version(cmd_tbl_t *cmdtp, int flag, int argc,
		   char * const argv[])
{
	const char *avb_version;

	if (argc != 1)
		return CMD_RET_USAGE;

	avb_version = avb_version_string();
	printf("Android avb version is %s.\n", avb_version);

	return CMD_RET_SUCCESS;
}

int do_avb_read_rollback_index(cmd_tbl_t *cmdtp, int flag,
			       int argc, char * const argv[])
{
	AvbOps *ops;
	uint64_t out_rollback_index;
	size_t rollback_index_location;

	if (argc != 2)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	rollback_index_location = simple_strtoul(argv[1], NULL, 16);
	if (ops->read_rollback_index(ops, rollback_index_location,
				     &out_rollback_index) != 0) {
		printf("do_avb_read_rollback_index error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("\nout_rollback_index = %llx\n", out_rollback_index);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_write_rollback_index(cmd_tbl_t *cmdtp, int flag,
				int argc, char * const argv[])
{
	AvbOps *ops;
	uint64_t out_rollback_index;
	size_t rollback_index_location;

	if (argc != 3)
		return CMD_RET_USAGE;

	rollback_index_location = simple_strtoul(argv[1], NULL, 16);
	out_rollback_index = simple_strtoull(argv[2], NULL, 16);
	debug("out_rollback_index = %llx\n", out_rollback_index);
	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->write_rollback_index(ops, rollback_index_location,
				      out_rollback_index) != 0) {
		printf("do_avb_write_rollback_index error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("\nWrite  rollback index successfully.\n");
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_read_is_device_unlocked(cmd_tbl_t *cmdtp, int flag,
				   int argc, char * const argv[])
{
	AvbOps *ops;
	bool out_is_unlocked;

	if (argc != 1)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->read_is_device_unlocked(ops, &out_is_unlocked) != 0) {
		printf("do_avb_read_is_device_unlocked error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("\n The device is %s\n",
		out_is_unlocked ? "UNLOCKED" : "LOCKED");
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}
int do_avb_write_is_device_unlocked(cmd_tbl_t *cmdtp, int flag,
				    int argc, char * const argv[])
{
	AvbOps *ops;
	bool out_is_unlocked;

	if (argc != 2)
		return CMD_RET_USAGE;

	out_is_unlocked = simple_strtoul(argv[1], NULL, 16);
	if ((out_is_unlocked != 0) || (out_is_unlocked != 1))
		printf("enter out_is_unlocked value must is '0' or '1'\n");

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->write_is_device_unlocked(ops, &out_is_unlocked) != 0) {
		printf("do_avb_write_is_device_unlocked error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	debug("out_is_unlocked = %d\n", out_is_unlocked);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_get_size_of_partition(cmd_tbl_t *cmdtp, int flag,
				 int argc, char * const argv[])
{
	AvbOps *ops;
	char *requested_partitions;
	uint64_t out_size_in_bytes;

	if (argc != 2)
		return CMD_RET_USAGE;

	requested_partitions = argv[1];
	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->get_size_of_partition(ops, requested_partitions,
				       &out_size_in_bytes) != 0) {
		printf("Can not get %s partition size!\n", requested_partitions);
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("%s partition size = 0x%llx\n", requested_partitions,
	       out_size_in_bytes);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_get_get_unique_guid_for_partition(cmd_tbl_t *cmdtp, int flag,
					     int argc, char * const argv[])
{
	AvbOps *ops;
	char *requested_partitions;
	size_t guid_buf_size = 37;
	char guid_buf[37];

	if (argc != 2)
		return CMD_RET_USAGE;

	requested_partitions = argv[1];
	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->get_unique_guid_for_partition(ops, requested_partitions,
					       guid_buf, guid_buf_size) != 0) {
		printf("Can not get %s partition UUID!\n",
		       requested_partitions);
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	printf("%s partition UUID is %s\n", requested_partitions, guid_buf);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_read(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	AvbOps *ops;
	char *requested_partitions;
	int64_t offset_blk;
	size_t blkcnt;
	size_t out_num_read;
	int i;
	char *buffer;

	if (argc != 4)
		return CMD_RET_USAGE;

	requested_partitions = argv[1];
	offset_blk = simple_strtoul(argv[2], NULL, 16);
	blkcnt = simple_strtoul(argv[3], NULL, 16);
	ops = avb_ops_user_new();
	buffer = (char *)malloc(blkcnt * 512);
	if (buffer == NULL)
		printf("malloc buffer failed!\n");

	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->read_from_partition(ops, requested_partitions,
				     offset_blk, blkcnt, buffer,
				     &out_num_read) != 0) {
		printf("do avb read error!\n");
		free(buffer);
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	for (i = 0; i < 512 * blkcnt; i++) {
		printf("buffer %d = %x", i, buffer[i]);
		if ((i + 1) % 4 == 0)
			printf("\n");
	}

	free(buffer);
	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_perm_attr_test(cmd_tbl_t *cmdtp, int flag,
		      int argc, char * const argv[])
{
	AvbOps *ops;
	int i;
	uint8_t hash[AVB_SHA256_DIGEST_SIZE];

	if (argc != 1)
		return CMD_RET_USAGE;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return CMD_RET_FAILURE;
	}

	if (ops->atx_ops->read_permanent_attributes_hash(ops->atx_ops, hash) != 0) {
		printf("read_permanent_attributes_hash error!\n");
		avb_ops_user_free(ops);
		return CMD_RET_FAILURE;
	}

	for (i = 0; i < AVB_SHA256_DIGEST_SIZE; i++) {
		if (i % 4 == 0)
			printf("\n");
		printf("0x%x  ", hash[i]);
	}

	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}

int do_avb_verify_partition(cmd_tbl_t *cmdtp, int flag,
			    int argc, char * const argv[])
{
	AvbOps *ops;
	const char *requested_partitions[1];
	const char * slot_suffixes[2] = {"_a", "_b"};
	AvbSlotVerifyFlags flags;
	AvbSlotVerifyData *slot_data[2] = {NULL, NULL};
	AvbSlotVerifyResult verify_result;
	size_t n;

	if (argc != 3)
		return CMD_RET_USAGE;

	requested_partitions[0] = argv[1];
	n = simple_strtoul(argv[2], NULL, 16);
	ops = avb_ops_user_new();
	flags = AVB_SLOT_VERIFY_FLAGS_NONE;
	verify_result =
		avb_slot_verify(ops,
				requested_partitions,
				slot_suffixes[n],
				flags,
				AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE,
				&slot_data[n]);
	if (verify_result != 0)
		return CMD_RET_FAILURE;

	avb_ops_user_free(ops);

	return CMD_RET_SUCCESS;
}
#endif

static cmd_tbl_t cmd_avb[] = {
#ifdef CONFIG_ANDROID_AB
	U_BOOT_CMD_MKENT(init, 1, 1, do_avb_init_ab_metadata, "", ""),
	U_BOOT_CMD_MKENT(slot_active, 2, 1,
			 do_avb_ab_mark_slot_active, "", ""),
	U_BOOT_CMD_MKENT(slot_unbootable, 2, 1,
			 do_avb_ab_mark_slot_unbootable, "", ""),
	U_BOOT_CMD_MKENT(slot_successful, 2, 1,
			 do_avb_ab_mark_slot_successful, "", ""),
	U_BOOT_CMD_MKENT(readabmisc, 1, 1, do_avb_read_ab_metadata, "", ""),
#endif
#ifdef CONFIG_ANDROID_AVB
	U_BOOT_CMD_MKENT(version, 1, 1, do_avb_version, "", ""),
	U_BOOT_CMD_MKENT(read_rollback, 2, 1,
			 do_avb_read_rollback_index, "", ""),
	U_BOOT_CMD_MKENT(write_rollback, 3, 1,
			 do_avb_write_rollback_index, "", ""),
	U_BOOT_CMD_MKENT(read_lock_status, 1, 1,
			 do_avb_read_is_device_unlocked, "", ""),
	U_BOOT_CMD_MKENT(write_lock_status, 2, 1,
			 do_avb_write_is_device_unlocked, "", ""),
	U_BOOT_CMD_MKENT(part_size, 2, 1,
			 do_avb_get_size_of_partition, "", ""),
	U_BOOT_CMD_MKENT(part_guid, 2, 1,
			 do_avb_get_get_unique_guid_for_partition, "", ""),
	U_BOOT_CMD_MKENT(read, 4, 1, do_avb_read, "", ""),
	U_BOOT_CMD_MKENT(perm_attr_test, 1, 1, do_perm_attr_test, "", ""),
	U_BOOT_CMD_MKENT(verify, 3, 1, do_avb_verify_partition, "", ""),
#endif
};

static int do_boot_avb(cmd_tbl_t *cmdtp,
		       int flag,
		       int argc,
		       char * const argv[])
{
	cmd_tbl_t *cp;

	cp = find_cmd_tbl(argv[1], cmd_avb, ARRAY_SIZE(cmd_avb));

	argc--;
	argv++;

	if (cp == NULL || argc > cp->maxargs)
		return CMD_RET_USAGE;
	if (flag == CMD_FLAG_REPEAT && !cp->repeatable)
		return CMD_RET_SUCCESS;

	return cp->cmd(cmdtp, flag, argc, argv);
}

U_BOOT_CMD(
	bootavb, 29, 1, do_boot_avb,
	"Execute the Android avb a/b boot flow.",
	"init - initialize the avbabmeta\n"
	"bootavb version - display info of bootavb version\n"
	"bootavb slot_active cnt\n"
	"bootavb slot_unbootable cnt\n"
	"bootavb slot_successful cnt\n"
	"bootavb read_rollback rollback_index_location\n"
	"bootavb write_rollback rollback_index_location rollback_index\n"
	"bootavb read_lock_status\n"
	"bootavb write_lock_status 0 or 1\n"
	"bootavb part_size partitions_name\n"
	"bootavb part_guid partitions_name\n"
	"bootavb read partition offset_blk cnt\n"
	"bootavb readabmisc\n"
	"bootavb perm_attr_test\n"
	"bootavb verify partition slot_cnt;partion name without '_a' or '_b'\n"
);
