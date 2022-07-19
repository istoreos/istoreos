/*
 * (C) Copyright 2013
 * David Feng <fenghua@phytium.com.cn>
 *
 * (C) Copyright 2002
 * Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x00000000;

	. = ALIGN(8);
	.text :
	{
		*(.__image_copy_start)
		CPUDIR/start.o (.text*)
		*(.text*)
	}

	. = ALIGN(8);
	.rodata : { *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*))) }

	. = ALIGN(8);
	.data : {
		*(.data*)
		
		/********* Insert A/V CPU related image start *********/
		. = ALIGN(8);

		_f_exc_redirect_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.exc_redirect))
		. = ALIGN(8);
		_e_exc_redirect_img = .;

		_f_exc_dispatch_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.exc_dispatch))
		. = ALIGN(8);
		_e_exc_dispatch_img = .;

		_f_a_entry_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.a_entry))
		. = ALIGN(8);
		_e_a_entry_img = .;

		_f_v_entry_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.v_entry))
		. = ALIGN(8);
		_e_v_entry_img = .;

		_f_isrvideo_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.isrvideoimg))
		. = ALIGN(8);
		_e_isrvideo_img = .;

		_f_rosbootvector_img = .;
		KEEP(MIPS_BOOTLOAD_LIB_PATH (.rosbootvectorimg))
		. = ALIGN(8);
		_e_rosbootvector_img = .;

		/********* Insert A/V CPU related image end *********/
	}

	. = ALIGN(8);

	. = .;

	. = ALIGN(8);
	.u_boot_list : {
		KEEP(*(SORT(.u_boot_list*)));
	}

	. = ALIGN(8);

	.image_copy_end :
	{
		*(.__image_copy_end)
	}

	. = ALIGN(8);

	.rel_dyn_start :
	{
		*(.__rel_dyn_start)
	}

	.rela.dyn : {
		*(.rela*)
	}

	.rel_dyn_end :
	{
		*(.__rel_dyn_end)
	}

	_end = .;

	. = ALIGN(8);

	.bss_start : {
		KEEP(*(.__bss_start));
	}

	.bss : {
		*(.bss*)
		 . = ALIGN(8);
	}

	.bss_end : {
		KEEP(*(.__bss_end));
	}

	/DISCARD/ : { *(.dynsym) }
	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
}
