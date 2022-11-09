/*
 * Copyright (c) 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <malloc.h>
#include <version.h>
#include <asm/sections.h>
#include <asm/io.h>
#include <asm/u-boot.h>
#include <lzma/LzmaTools.h>
#include <asm/arch-rockchip/rk_atags.h>

/********************** SPL framework weak ***********************/
void board_init_f(ulong dummy)
{
	/* Mainly to init secure */
	arch_cpu_init();
}

ulong spl_relocate_stack_gd(void)
{
	return 0;
}

int board_fit_config_name_match(const char *name)
{
	return 0;
}

/********************** Decomp Header code ***********************/
#define UART_FIFO_EMPTY                (BIT(6) | BIT(5))
#define UART_LSR                       0x14

enum {
	E_OK,
	E_BD,
	E_TLB,
	E_MAGIC,
	E_HCRC,
	E_DCRC,
	E_ALGO,
	E_UNDEF,
};

static const char *err_msg[] = {
	"OK", "BD", "TLB", "MAGIC", "HCRC", "DCRC", "ALGO", "UNDEF"
};

static ulong g_uart_base = CONFIG_DEBUG_UART_BASE;

static void put_char(char ch)
{
	ulong base = g_uart_base;

	if (!g_uart_base)
		return;

	writel(ch, base);
	if (ch == '\n')
		writel('\r', base);

	while (!(__arch_getl(base + UART_LSR) & UART_FIFO_EMPTY))
		;
}

static void put_string(const char *str)
{
	while (*str) {
		put_char(*str);
		str++;
	}
}

static void put_dec_0_19(int dec)
{
	if (dec >= 10) {
		put_char('1');
		dec -= 10;
	}

	put_char(dec + '0');
}

static void put_hex(u32 hex)
{
	uint8_t c, i = 8;

	put_string("0x");
	while (i--) {
		c = (hex & 0xf0000000) >> 28;
		put_char(c < 0xa ? c + '0' : c - 0xa + 'a');
		hex <<= 4;
	}
}

static void jump_entry(void *addr)
{
	void (*os_entry)(void) = (void *)addr;

	flush_dcache_all();

	/*
	 * Turn off I-cache and invalidate it
	 */
	icache_disable();
	invalidate_icache_all();

	/*
	 * Turn off D-cache
	 * dcache_disable() in turn flushes the d-cache and disables MMU
	 */
	dcache_disable();
	invalidate_dcache_all();

	dsb();
	isb();

	(*os_entry)();
}

static struct tag *uart_init(void)
{
#if defined(CONFIG_ROCKCHIP_PRELOADER_SERIAL) && \
    defined(CONFIG_ROCKCHIP_PRELOADER_ATAGS)
	struct tag *t;

	t = atags_get_tag(ATAG_SERIAL);
	if (t) {
		if (t->u.serial.enable)
			g_uart_base = t->u.serial.addr;
		else
			g_uart_base = 0;
	}
#endif
	return t;
}

static void print_ret(int err, int err_algo)
{
	if (err)
		put_string("ERR ");

	put_string(err_msg[err]);

	if (err_algo) {
		put_char(' ');
		put_dec_0_19(err_algo);
	}
	put_char('\n');
}

#ifdef CONFIG_SPL_LZMA
static int un_lzma(const image_header_t *hdr, int *err_algo)
{
	const void *data;
	ulong load_addr;
	SizeT lzma_len;
	SizeT src_lenp;
	int err;

	load_addr = uimage_to_cpu(hdr->ih_load);
	src_lenp = *(u32 *)(uimage_to_cpu(hdr->ih_size));
	data = (void *)hdr + sizeof(*hdr);
	lzma_len = SZ_2M; /* default max size */
	err = lzmaBuffToBuffDecompress((uchar *)(load_addr), &lzma_len,
				       (uchar *)(data), src_lenp);
	if (err) {
		*err_algo = err;
		err = E_ALGO;
	}

	return err;
}
#endif

static int decompress_image(const image_header_t *hdr, int *err_algo)
{
#ifdef CONFIG_SPL_LZMA
	return un_lzma(hdr, err_algo);
#endif
	return E_UNDEF;
}

void board_init_r(gd_t *dummy1, ulong dummy2)
{
	const image_header_t *hdr;
	struct tag *t;
	ulong addr;
	int err_algo = 0;
	int err = 0;

	t = uart_init();

	put_string("\nDECOMP " PLAIN_VERSION " (" U_BOOT_DATE " - " \
			U_BOOT_TIME ")\n\n");
	if (t) {
		put_string("PreSerial: ");
		put_char('0' + t->u.serial.id);
		put_char('\n');
	}
	put_string("Start... ");

	/* init malloc */
	gd->malloc_limit = CONFIG_VAL(SYS_MALLOC_F_LEN);
	gd->malloc_ptr = 0;

	/* set up bank */
#ifndef CONFIG_ARM64
	if (!gd->bd) {
		gd->bd = calloc(1, sizeof(bd_t));
		if (!gd->bd) {
			err = E_BD;
			goto out;
		}
		gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
		gd->bd->bi_dram[0].size  = SZ_64M; /* default */
	}
#endif
	/* TLB memory should be SZ_16K base align and 4KB end align */
	gd->arch.tlb_size = PGTABLE_SIZE;
	gd->arch.tlb_addr = (ulong)memalign(SZ_16K, ALIGN(PGTABLE_SIZE, SZ_4K));
	if (!gd->arch.tlb_addr) {
		err = E_TLB;
		goto out;
	}

	/* Enable dcache */
	dcache_enable();

	/* Check */
	hdr = (void *)(&__bss_end);
	if (!image_check_magic(hdr)) {
		err = E_MAGIC;
		goto out;
	}

	if (!image_check_hcrc(hdr)) {
		err = E_HCRC;
		goto out;
	}

	if (!image_check_dcrc(hdr)) {
		err = E_DCRC;
		goto out;
	}

	/* Decompress... */
	err = decompress_image(hdr, &err_algo);
out:
	print_ret(err, err_algo);
	if (!err) {
		addr = uimage_to_cpu(hdr->ih_load);
		put_string("Jumping to ");
		put_hex((u32)addr);
		put_char('\n');

		/* jump! */
		jump_entry((void *)addr);
	}

	/* hang */
	put_string("\nPanic hang!");
	while (1)
		;
}

