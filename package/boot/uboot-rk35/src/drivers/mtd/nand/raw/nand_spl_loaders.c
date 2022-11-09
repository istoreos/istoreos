int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst)
{
	unsigned int block, lastblock;
	unsigned int page, page_offset;

	/* offs has to be aligned to a page address! */
	block = offs / CONFIG_SYS_NAND_BLOCK_SIZE;
	lastblock = (offs + size - 1) / CONFIG_SYS_NAND_BLOCK_SIZE;
	page = (offs % CONFIG_SYS_NAND_BLOCK_SIZE) / CONFIG_SYS_NAND_PAGE_SIZE;
	page_offset = offs % CONFIG_SYS_NAND_PAGE_SIZE;

	while (block <= lastblock) {
		if (!nand_is_bad_block(block)) {
			/* Skip bad blocks */
			while (page < CONFIG_SYS_NAND_PAGE_COUNT) {
				nand_read_page(block, page, dst);
				/*
				 * When offs is not aligned to page address the
				 * extra offset is copied to dst as well. Copy
				 * the image such that its first byte will be
				 * at the dst.
				 */
				if (unlikely(page_offset)) {
					memmove(dst, dst + page_offset,
						CONFIG_SYS_NAND_PAGE_SIZE);
					dst = (void *)((int)dst - page_offset);
					page_offset = 0;
				}
				dst += CONFIG_SYS_NAND_PAGE_SIZE;
				page++;
			}

			page = 0;
		} else {
			lastblock++;
		}

		block++;
	}

	return 0;
}

#ifdef CONFIG_SPL_UBI
/*
 * Temporary storage for non NAND page aligned and non NAND page sized
 * reads. Note: This does not support runtime detected FLASH yet, but
 * that should be reasonably easy to fix by making the buffer large
 * enough :)
 */
static u8 scratch_buf[CONFIG_SYS_NAND_PAGE_SIZE];

/**
 * nand_spl_read_block - Read data from physical eraseblock into a buffer
 * @block:	Number of the physical eraseblock
 * @offset:	Data offset from the start of @peb
 * @len:	Data size to read
 * @dst:	Address of the destination buffer
 *
 * This could be further optimized if we'd have a subpage read
 * function in the simple code. On NAND which allows subpage reads
 * this would spare quite some time to readout e.g. the VID header of
 * UBI.
 *
 * Notes:
 *	@offset + @len are not allowed to be larger than a physical
 *	erase block. No sanity check done for simplicity reasons.
 *
 * To support runtime detected flash this needs to be extended by
 * information about the actual flash geometry, but thats beyond the
 * scope of this effort and for most applications where fast boot is
 * required it is not an issue anyway.
 */
int nand_spl_read_block(int block, int offset, int len, void *dst)
{
	int page, read;

	/* Calculate the page number */
	page = offset / CONFIG_SYS_NAND_PAGE_SIZE;

	/* Offset to the start of a flash page */
	offset = offset % CONFIG_SYS_NAND_PAGE_SIZE;

	while (len) {
		/*
		 * Non page aligned reads go to the scratch buffer.
		 * Page aligned reads go directly to the destination.
		 */
		if (offset || len < CONFIG_SYS_NAND_PAGE_SIZE) {
			nand_read_page(block, page, scratch_buf);
			read = min(len, CONFIG_SYS_NAND_PAGE_SIZE - offset);
			memcpy(dst, scratch_buf + offset, read);
			offset = 0;
		} else {
			nand_read_page(block, page, dst);
			read = CONFIG_SYS_NAND_PAGE_SIZE;
		}
		page++;
		len -= read;
		dst += read;
	}
	return 0;
}
#endif
