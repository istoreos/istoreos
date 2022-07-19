#ifndef __MBR_H__
#define __MBR_H__

#include <stdint.h>
#include <stddef.h>

typedef struct {
  unsigned char	status;
  unsigned char chs_first_sector[3];
  unsigned char	type;
  unsigned char chs_last_sector[3];
  uint32_t lba;
  uint32_t sectors;
} __attribute__((packed)) mbr_part_t;

typedef struct {
	unsigned char	unused[0x1BE];
  mbr_part_t parts[4];
  uint16_t signature;
} __attribute__((packed)) mbr_t;

#endif