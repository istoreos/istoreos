/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <blk.h>
#include <boot_rkimg.h>
#include <dm.h>
#include <errno.h>
#include <image.h>
#include <linux/log2.h>
#include <malloc.h>
#include <nand.h>
#include <part.h>
#include <spi.h>
#include <dm/device-internal.h>
#include <linux/mtd/spi-nor.h>
#ifdef CONFIG_NAND
#include <linux/mtd/nand.h>
#endif

#define MTD_PART_NAND_HEAD		"mtdparts="
#define MTD_ROOT_PART_NUM		"ubi.mtd="
#define MTD_ROOT_PART_NAME_UBIFS	"root=ubi0:rootfs"
#define MTD_ROOT_PART_NAME_SQUASHFS	"root=/dev/ubiblock0_0"
#define MTD_PART_INFO_MAX_SIZE		512
#define MTD_SINGLE_PART_INFO_MAX_SIZE	40

#define MTD_BLK_TABLE_BLOCK_UNKNOWN	(-2)
#define MTD_BLK_TABLE_BLOCK_SHIFT	(-1)

static int *mtd_map_blk_table;

int mtd_blk_map_table_init(struct blk_desc *desc,
			   loff_t offset,
			   size_t length)
{
	u32 blk_total, blk_begin, blk_cnt;
	struct mtd_info *mtd = NULL;
	int i, j;

	if (!desc)
		return -ENODEV;

	switch (desc->devnum) {
	case BLK_MTD_NAND:
	case BLK_MTD_SPI_NAND:
		mtd = desc->bdev->priv;
		break;
	default:
		break;
	}

	if (!mtd) {
		return -ENODEV;
	} else {
		blk_total = (mtd->size + mtd->erasesize - 1) >> mtd->erasesize_shift;
		if (!mtd_map_blk_table) {
			mtd_map_blk_table = (int *)malloc(blk_total * sizeof(int));
			if (!mtd_map_blk_table)
				return -ENOMEM;
			for (i = 0; i < blk_total; i++)
				mtd_map_blk_table[i] = MTD_BLK_TABLE_BLOCK_UNKNOWN;
		}

		blk_begin = (u32)offset >> mtd->erasesize_shift;
		blk_cnt = ((u32)((offset & mtd->erasesize_mask) + length + \
			mtd->erasesize - 1) >> mtd->erasesize_shift);
		if (blk_begin >= blk_total) {
			pr_err("map table blk begin[%d] overflow\n", blk_begin);
			return -EINVAL;
		}
		if ((blk_begin + blk_cnt) > blk_total)
			blk_cnt = blk_total - blk_begin;

		if (mtd_map_blk_table[blk_begin] != MTD_BLK_TABLE_BLOCK_UNKNOWN)
			return 0;

		j = 0;
		 /* should not across blk_cnt */
		for (i = 0; i < blk_cnt; i++) {
			if (j >= blk_cnt)
				mtd_map_blk_table[blk_begin + i] = MTD_BLK_TABLE_BLOCK_SHIFT;
			for (; j < blk_cnt; j++) {
				if (!mtd_block_isbad(mtd, (blk_begin + j) << mtd->erasesize_shift)) {
					mtd_map_blk_table[blk_begin + i] = blk_begin + j;
					j++;
					if (j == blk_cnt)
						j++;
					break;
				}
			}
		}

		return 0;
	}
}

static bool get_mtd_blk_map_address(struct mtd_info *mtd, loff_t *off)
{
	bool mapped;
	loff_t offset = *off;
	size_t block_offset = offset & (mtd->erasesize - 1);

	mapped = false;
	if (!mtd_map_blk_table ||
	    mtd_map_blk_table[(u64)offset >> mtd->erasesize_shift] ==
	    MTD_BLK_TABLE_BLOCK_UNKNOWN ||
	    mtd_map_blk_table[(u64)offset >> mtd->erasesize_shift] ==
	    0xffffffff)
		return mapped;

	mapped = true;
	*off = (loff_t)(((u32)mtd_map_blk_table[(u64)offset >>
		mtd->erasesize_shift] << mtd->erasesize_shift) + block_offset);

	return mapped;
}

void mtd_blk_map_partitions(struct blk_desc *desc)
{
	disk_partition_t info;
	int i, ret;

	if (!desc)
		return;

	if (desc->if_type != IF_TYPE_MTD)
		return;

	for (i = 1; i < MAX_SEARCH_PARTITIONS; i++) {
		ret = part_get_info(desc, i, &info);
		if (ret != 0)
			continue;

		if (mtd_blk_map_table_init(desc,
					   info.start << 9,
					   info.size << 9)) {
			pr_debug("mtd block map table fail\n");
		}
	}
}

void mtd_blk_map_fit(struct blk_desc *desc, ulong sector, void *fit)
{
	struct mtd_info *mtd = NULL;
	int totalsize = 0;

	if (desc->if_type != IF_TYPE_MTD)
		return;

	if (desc->devnum == BLK_MTD_NAND) {
#if defined(CONFIG_NAND)
		mtd = dev_get_priv(desc->bdev->parent);
#endif
	} else if (desc->devnum == BLK_MTD_SPI_NAND) {
#if defined(CONFIG_MTD_SPI_NAND)
		mtd = desc->bdev->priv;
#endif
	}

#ifdef CONFIG_SPL_FIT
	if (fit_get_totalsize(fit, &totalsize))
		debug("Can not find /totalsize node.\n");
#endif
	if (mtd && totalsize) {
		if (mtd_blk_map_table_init(desc, sector << 9, totalsize + (size_t)mtd->erasesize))
			debug("Map block table fail.\n");
	}
}

static __maybe_unused int mtd_map_read(struct mtd_info *mtd, loff_t offset,
				       size_t *length, size_t *actual,
				       loff_t lim, u_char *buffer)
{
	size_t left_to_read = *length;
	u_char *p_buffer = buffer;
	int rval;

	while (left_to_read > 0) {
		size_t block_offset = offset & (mtd->erasesize - 1);
		size_t read_length;
		loff_t mapped_offset;

		if (offset >= mtd->size)
			return 0;

		mapped_offset = offset;
		if (!get_mtd_blk_map_address(mtd, &mapped_offset)) {
			if (mtd_block_isbad(mtd, mapped_offset &
					    ~(mtd->erasesize - 1))) {
				printf("Skipping bad block 0x%08llx\n",
				       offset & ~(mtd->erasesize - 1));
				offset += mtd->erasesize - block_offset;
				continue;
			}
		}

		if (left_to_read < (mtd->erasesize - block_offset))
			read_length = left_to_read;
		else
			read_length = mtd->erasesize - block_offset;

		rval = mtd_read(mtd, mapped_offset, read_length, &read_length,
				p_buffer);
		if (rval && rval != -EUCLEAN) {
			printf("NAND read from offset %llx failed %d\n",
			       offset, rval);
			*length -= left_to_read;
			return rval;
		}

		left_to_read -= read_length;
		offset       += read_length;
		p_buffer     += read_length;
	}

	return 0;
}

static __maybe_unused int mtd_map_write(struct mtd_info *mtd, loff_t offset,
					size_t *length, size_t *actual,
					loff_t lim, u_char *buffer, int flags)
{
	int rval = 0, blocksize;
	size_t left_to_write = *length;
	u_char *p_buffer = buffer;
	struct erase_info ei;

	blocksize = mtd->erasesize;

	/*
	 * nand_write() handles unaligned, partial page writes.
	 *
	 * We allow length to be unaligned, for convenience in
	 * using the $filesize variable.
	 *
	 * However, starting at an unaligned offset makes the
	 * semantics of bad block skipping ambiguous (really,
	 * you should only start a block skipping access at a
	 * partition boundary).  So don't try to handle that.
	 */
	if ((offset & (mtd->writesize - 1)) != 0) {
		printf("Attempt to write non page-aligned data\n");
		*length = 0;
		return -EINVAL;
	}

	while (left_to_write > 0) {
		size_t block_offset = offset & (mtd->erasesize - 1);
		size_t write_size, truncated_write_size;
		loff_t mapped_offset;

		if (offset >= mtd->size)
			return 0;

		mapped_offset = offset;
		if (!get_mtd_blk_map_address(mtd, &mapped_offset)) {
			if (mtd_block_isbad(mtd, mapped_offset &
					    ~(mtd->erasesize - 1))) {
				printf("Skipping bad block 0x%08llx\n",
				       offset & ~(mtd->erasesize - 1));
				offset += mtd->erasesize - block_offset;
				continue;
			}
		}

		if (!(mapped_offset & mtd->erasesize_mask)) {
			memset(&ei, 0, sizeof(struct erase_info));
			ei.addr = mapped_offset;
			ei.len  = mtd->erasesize;
			rval = mtd_erase(mtd, &ei);
			if (rval) {
				pr_info("error %d while erasing %llx\n", rval,
					mapped_offset);
				return rval;
			}
		}

		if (left_to_write < (blocksize - block_offset))
			write_size = left_to_write;
		else
			write_size = blocksize - block_offset;

		truncated_write_size = write_size;
		rval = mtd_write(mtd, mapped_offset, truncated_write_size,
				 (size_t *)(&truncated_write_size), p_buffer);

		offset += write_size;
		p_buffer += write_size;

		if (rval != 0) {
			printf("NAND write to offset %llx failed %d\n",
			       offset, rval);
			*length -= left_to_write;
			return rval;
		}

		left_to_write -= write_size;
	}

	return 0;
}

static __maybe_unused int mtd_map_erase(struct mtd_info *mtd, loff_t offset,
					size_t length)
{
	struct erase_info ei;
	loff_t pos, len;
	int ret;

	pos = offset;
	len = length;

	if ((pos & mtd->erasesize_mask) || (len & mtd->erasesize_mask)) {
		pr_err("Attempt to erase non block-aligned data, pos= %llx, len= %llx\n",
		       pos, len);

		return -EINVAL;
	}

	while (len) {
		loff_t mapped_offset;

		mapped_offset = pos;
		if (!get_mtd_blk_map_address(mtd, &mapped_offset)) {
			if (mtd_block_isbad(mtd, pos) || mtd_block_isreserved(mtd, pos)) {
				pr_debug("attempt to erase a bad/reserved block @%llx\n",
					 pos);
				pos += mtd->erasesize;
				continue;
			}
		}

		memset(&ei, 0, sizeof(struct erase_info));
		ei.addr = mapped_offset;
		ei.len  = mtd->erasesize;
		ret = mtd_erase(mtd, &ei);
		if (ret) {
			pr_err("map_erase error %d while erasing %llx\n", ret,
			       pos);
			return ret;
		}

		pos += mtd->erasesize;
		len -= mtd->erasesize;
	}

	return 0;
}

char *mtd_part_parse(struct blk_desc *dev_desc)
{
	char mtd_part_info_temp[MTD_SINGLE_PART_INFO_MAX_SIZE] = {0};
	u32 length, data_len = MTD_PART_INFO_MAX_SIZE;
	disk_partition_t info;
	char *mtd_part_info_p;
	struct mtd_info *mtd;
	char *mtd_part_info;
	int ret;
	int p;

#ifndef CONFIG_SPL_BUILD
	dev_desc = rockchip_get_bootdev();
#endif
	if (!dev_desc)
		return NULL;

	mtd = (struct mtd_info *)dev_desc->bdev->priv;
	if (!mtd)
		return NULL;
#ifndef CONFIG_SPL_BUILD
	char mtd_root_part_info[40] = {0};

	p = part_get_info_by_name(dev_desc, PART_SYSTEM, &info);
	if (p > 0) {
		if (strstr(env_get("bootargs"), "rootfstype=squashfs"))
			snprintf(mtd_root_part_info, ARRAY_SIZE(mtd_root_part_info), "%s%d %s",
				 MTD_ROOT_PART_NUM, p - 1, MTD_ROOT_PART_NAME_SQUASHFS);
		else
			snprintf(mtd_root_part_info, ARRAY_SIZE(mtd_root_part_info), "%s%d %s",
				 MTD_ROOT_PART_NUM, p - 1, MTD_ROOT_PART_NAME_UBIFS);
		env_update("bootargs", mtd_root_part_info);
	}
#endif
	mtd_part_info = (char *)calloc(MTD_PART_INFO_MAX_SIZE, sizeof(char));
	if (!mtd_part_info) {
		printf("%s: Fail to malloc!", __func__);
		return NULL;
	}

	mtd_part_info_p = mtd_part_info;
	snprintf(mtd_part_info_p, data_len - 1, "%s%s:",
		 MTD_PART_NAND_HEAD,
		 dev_desc->product);
	data_len -= strlen(mtd_part_info_p);
	mtd_part_info_p = mtd_part_info_p + strlen(mtd_part_info_p);

	for (p = 1; p < MAX_SEARCH_PARTITIONS; p++) {
		ret = part_get_info(dev_desc, p, &info);
		if (ret)
			break;

		debug("name is %s, start addr is %x\n", info.name,
		      (int)(size_t)info.start);

		snprintf(mtd_part_info_p, data_len - 1, "0x%x@0x%x(%s)",
			 (int)(size_t)info.size << 9,
			 (int)(size_t)info.start << 9,
			 info.name);
		snprintf(mtd_part_info_temp, MTD_SINGLE_PART_INFO_MAX_SIZE - 1,
			 "0x%x@0x%x(%s)",
			 (int)(size_t)info.size << 9,
			 (int)(size_t)info.start << 9,
			 info.name);
		strcat(mtd_part_info, ",");
		if (part_get_info(dev_desc, p + 1, &info)) {
			/* Partition with grow tag in parameter will be resized */
			if ((info.size + info.start + 64) >= dev_desc->lba) {
				if (dev_desc->devnum == BLK_MTD_SPI_NOR) {
					/* Nor is 64KB erase block(kernel) and gpt table just
					 * resserve 33 sectors for the last partition. This
					 * will erase the backup gpt table by user program,
					 * so reserve one block.
					 */
					snprintf(mtd_part_info_p, data_len - 1, "0x%x@0x%x(%s)",
						 (int)(size_t)(info.size -
						 (info.size - 1) %
						 (0x10000 >> 9) - 1) << 9,
						 (int)(size_t)info.start << 9,
						 info.name);
					break;
				} else {
					/* Nand flash is erased by block and gpt table just
					 * resserve 33 sectors for the last partition. This
					 * will erase the backup gpt table by user program,
					 * so reserve one block.
					 */
					snprintf(mtd_part_info_p, data_len - 1, "0x%x@0x%x(%s)",
						 (int)(size_t)(info.size -
						 (info.size - 1) %
						 (mtd->erasesize >> 9) - 1) << 9,
						 (int)(size_t)info.start << 9,
						 info.name);
					break;
				}
			} else {
				snprintf(mtd_part_info_temp, MTD_SINGLE_PART_INFO_MAX_SIZE - 1,
					 "0x%x@0x%x(%s)",
					 (int)(size_t)info.size << 9,
					 (int)(size_t)info.start << 9,
					 info.name);
				break;
			}
		}
		length = strlen(mtd_part_info_temp);
		data_len -= length;
		mtd_part_info_p = mtd_part_info_p + length + 1;
		memset(mtd_part_info_temp, 0, MTD_SINGLE_PART_INFO_MAX_SIZE);
	}

	return mtd_part_info;
}

ulong mtd_dread(struct udevice *udev, lbaint_t start,
		lbaint_t blkcnt, void *dst)
{
	struct blk_desc *desc = dev_get_uclass_platdata(udev);
#if defined(CONFIG_NAND) || defined(CONFIG_MTD_SPI_NAND) || defined(CONFIG_SPI_FLASH_MTD)
	loff_t off = (loff_t)(start * 512);
	size_t rwsize = blkcnt * 512;
#endif
	struct mtd_info *mtd;
	int ret = 0;

	if (!desc)
		return ret;

	mtd = desc->bdev->priv;
	if (!mtd)
		return 0;

	if (blkcnt == 0)
		return 0;

	pr_debug("mtd dread %s %lx %lx\n", mtd->name, start, blkcnt);

	if (desc->devnum == BLK_MTD_NAND) {
		ret = mtd_map_read(mtd, off, &rwsize,
				   NULL, mtd->size,
				   (u_char *)(dst));
		if (!ret)
			return blkcnt;
		else
			return 0;
	} else if (desc->devnum == BLK_MTD_SPI_NAND) {
		ret = mtd_map_read(mtd, off, &rwsize,
				   NULL, mtd->size,
				   (u_char *)(dst));
		if (!ret)
			return blkcnt;
		else
			return 0;
	} else if (desc->devnum == BLK_MTD_SPI_NOR) {
#if defined(CONFIG_SPI_FLASH_MTD) || defined(CONFIG_SPL_BUILD)
		struct spi_nor *nor = (struct spi_nor *)mtd->priv;
		struct spi_slave *spi = nor->spi;
		size_t retlen_nor;

		if (desc->op_flag == BLK_PRE_RW)
			spi->mode |= SPI_DMA_PREPARE;
		mtd_read(mtd, off, rwsize, &retlen_nor, dst);
		if (desc->op_flag == BLK_PRE_RW)
			spi->mode &= ~SPI_DMA_PREPARE;

		if (retlen_nor == rwsize)
			return blkcnt;
		else
#endif
			return 0;
	} else {
		return 0;
	}
}

#if CONFIG_IS_ENABLED(MTD_WRITE)
ulong mtd_dwrite(struct udevice *udev, lbaint_t start,
		 lbaint_t blkcnt, const void *src)
{
	struct blk_desc *desc = dev_get_uclass_platdata(udev);
#if defined(CONFIG_NAND) || defined(CONFIG_MTD_SPI_NAND) || defined(CONFIG_SPI_FLASH_MTD)
	loff_t off = (loff_t)(start * 512);
	size_t rwsize = blkcnt * 512;
#endif
	struct mtd_info *mtd;
	int ret = 0;

	if (!desc)
		return ret;

	mtd = desc->bdev->priv;
	if (!mtd)
		return 0;

	pr_debug("mtd dwrite %s %lx %lx\n", mtd->name, start, blkcnt);

	if (blkcnt == 0)
		return 0;

	if (desc->devnum == BLK_MTD_NAND ||
	    desc->devnum == BLK_MTD_SPI_NAND ||
	    desc->devnum == BLK_MTD_SPI_NOR) {
		if (desc->op_flag == BLK_MTD_CONT_WRITE) {
			ret = mtd_map_write(mtd, off, &rwsize,
					    NULL, mtd->size,
					    (u_char *)(src), 0);
			if (!ret)
				return blkcnt;
			else
				return 0;
		} else {
			lbaint_t off_aligned, alinged;
			size_t rwsize_aligned;
			u8 *p_buf;

			alinged = off & mtd->erasesize_mask;
			off_aligned = off - alinged;
			rwsize_aligned = rwsize + alinged;
			rwsize_aligned = (rwsize_aligned + mtd->erasesize - 1) &
				~(mtd->erasesize - 1);

			p_buf = malloc(rwsize_aligned);
			if (!p_buf) {
				printf("%s: Fail to malloc!", __func__);
				return 0;
			}

			ret = mtd_map_read(mtd, off_aligned, &rwsize_aligned,
					   NULL, mtd->size,
					   (u_char *)(p_buf));
			if (ret) {
				free(p_buf);
				return 0;
			}

			memcpy(p_buf + alinged, src, rwsize);

			ret = mtd_map_write(mtd, off_aligned, &rwsize_aligned,
					    NULL, mtd->size,
					    (u_char *)(p_buf), 0);
			free(p_buf);
			if (!ret)
				return blkcnt;
			else
				return 0;
		}
	} else {
		return 0;
	}

	return 0;
}

ulong mtd_derase(struct udevice *udev, lbaint_t start,
		 lbaint_t blkcnt)
{
	struct blk_desc *desc = dev_get_uclass_platdata(udev);
#if defined(CONFIG_NAND) || defined(CONFIG_MTD_SPI_NAND) || defined(CONFIG_SPI_FLASH_MTD)
	loff_t off = (loff_t)(start * 512);
	size_t len = blkcnt * 512;
#endif
	struct mtd_info *mtd;
	int ret = 0;

	if (!desc)
		return ret;

	mtd = desc->bdev->priv;
	if (!mtd)
		return 0;

	pr_debug("mtd derase %s %lx %lx\n", mtd->name, start, blkcnt);

	if (blkcnt == 0)
		return 0;

	if (desc->devnum == BLK_MTD_NAND ||
	    desc->devnum == BLK_MTD_SPI_NAND ||
	    desc->devnum == BLK_MTD_SPI_NOR) {
		ret = mtd_map_erase(mtd, off, len);
		if (ret)
			return ret;
	} else {
		return 0;
	}

	return 0;
}
#endif

static int mtd_blk_probe(struct udevice *udev)
{
	struct mtd_info *mtd;
	struct blk_desc *desc = dev_get_uclass_platdata(udev);
	int ret, i = 0;

	mtd = dev_get_uclass_priv(udev->parent);
	if (mtd->type == MTD_NANDFLASH && desc->devnum == BLK_MTD_NAND) {
#ifndef CONFIG_SPL_BUILD
		mtd = dev_get_priv(udev->parent);
#endif
	}

	/* Fill mtd devices information */
	if (is_power_of_2(mtd->erasesize))
		mtd->erasesize_shift = ffs(mtd->erasesize) - 1;
	else
		mtd->erasesize_shift = 0;

	if (is_power_of_2(mtd->writesize))
		mtd->writesize_shift = ffs(mtd->writesize) - 1;
	else
		mtd->writesize_shift = 0;

	mtd->erasesize_mask = (1 << mtd->erasesize_shift) - 1;
	mtd->writesize_mask = (1 << mtd->writesize_shift) - 1;

	desc->bdev->priv = mtd;
	sprintf(desc->vendor, "0x%.4x", 0x2207);
	if (strncmp(mtd->name, "nand", 4) == 0)
		memcpy(desc->product, "rk-nand", strlen("rk-nand"));
	else
		memcpy(desc->product, mtd->name, strlen(mtd->name));
	memcpy(desc->revision, "V1.00", sizeof("V1.00"));
	if (mtd->type == MTD_NANDFLASH) {
#ifdef CONFIG_NAND
		if (desc->devnum == BLK_MTD_NAND)
			i = NAND_BBT_SCAN_MAXBLOCKS;
		else if (desc->devnum == BLK_MTD_SPI_NAND)
			i = NANDDEV_BBT_SCAN_MAXBLOCKS;
#endif

		/*
		 * Find the first useful block in the end,
		 * and it is the end lba of the nand storage.
		 */
		for (; i < (mtd->size / mtd->erasesize); i++) {
			ret =  mtd_block_isbad(mtd,
					       mtd->size - mtd->erasesize * (i + 1));
			if (!ret) {
				desc->lba = (mtd->size >> 9) -
					(mtd->erasesize >> 9) * i;
				break;
			}
		}
	} else {
		desc->lba = mtd->size >> 9;
	}

	debug("MTD: desc->lba is %lx\n", desc->lba);

	return 0;
}

static const struct blk_ops mtd_blk_ops = {
	.read	= mtd_dread,
#if CONFIG_IS_ENABLED(MTD_WRITE)
	.write	= mtd_dwrite,
	.erase	= mtd_derase,
#endif
};

U_BOOT_DRIVER(mtd_blk) = {
	.name		= "mtd_blk",
	.id		= UCLASS_BLK,
	.ops		= &mtd_blk_ops,
	.probe		= mtd_blk_probe,
};
