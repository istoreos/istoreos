/*
 * 
 */

#ifndef __RTKSPI_NAND_H__
#define __RTKSPI_NAND_H__

#include <config.h>

#define SPI_BOOTCODE_MAGIC			0xbeef1195
#define SPI_BOOTCODE_BIN_ONLY		0			// u-boot.bin
#define SPI_BOOTCODE_NORMAL_MODE	1			// u-boot.bin + pedding + SHA256(16bytes)
#define SPI_BOOTCODE_RTK_MODE		2			// ENCRY(u-boot.bin + pedding + SIGNATURE(256byts))

typedef struct
{
    unsigned int    magic_tag ;
    unsigned int    secue_mode;
    unsigned int    bootcode_size;
    unsigned int    bootcode_entry_addr;
} s_bootcode2_header;

#define SPI_RBUS_BASE_ADDR      (0x88100000UL)
#define SPI_FLASH_ID_FOUND      (0x80000000UL)

int rtkspi_erase( unsigned int spi_offset_address, unsigned int byte_length );
void rtkspi_write8( unsigned int target_address, unsigned int source_address, unsigned int byte_length );
void rtkspi_read32( unsigned int target_address, unsigned int source_address, unsigned int byte_length );
void rtkspi_read32_md( unsigned int target_address, unsigned int source_address, unsigned int byte_length );
unsigned int rtkspi_load_DT_for_kernel( unsigned int _target_fdt_address );
unsigned int rtkspi_load_DT_for_rescure_android( unsigned int _target_fdt_address );

static inline int rtkspi_read(unsigned int source_address, unsigned int byte_length, unsigned int *target_address) {
	rtkspi_read32_md((unsigned int)(uintptr_t)target_address, source_address, byte_length );
	return 1;
}
#endif // __RTKSPI_NAND_H__
