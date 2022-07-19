/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "layout.h"
#include "io.h"

static fw_type_mapping_t fw_support[]= {
	// LABEL, config name, layout name
	{FW_TYPE_KERNEL, 		  "linuxKernel",  "KERNEL",    "Kernel"},
	{FW_TYPE_KERNEL_DT, 	"kernelDT",     "KERNEL_DT"},
	{FW_TYPE_RESCUE_DT, 	"rescueDT",     "RESCUE_DT"},
	{FW_TYPE_RESCUE_ROOTFS, "rescueRootFS", "RESCUE_ROOTFS", "RootFS",  "ROOTFS"},
	{FW_TYPE_AUDIO, 		  "audioKernel",   "AKERNEL",  "audio"}
};

fw_type_mapping_t *find_fw_type_by_ln(const char *name) {
  for (int i=0;i<sizeof(fw_support)/sizeof(fw_type_mapping_t);++i)
  {
    if (strcmp(fw_support[i].l_name, name)==0)
    {
      return fw_support+i;
    }
  }
  return NULL;
}

fw_type_mapping_t *find_fw_type_by_code(fw_type_code_e code) {
  for (int i=0;i<sizeof(fw_support)/sizeof(fw_type_mapping_t);++i)
  {
    if (fw_support[i].code == code)
    {
      return fw_support+i;
    }
  }
  return NULL;
}

static fs_type_mapping_t fs_support[]= {
	// LABEL, name
	{FS_TYPE_SQUASH, 		"squashfs"},
	{FS_TYPE_EXT4, 	"ext4"},
};

fs_type_mapping_t *find_fs_type_by_name(const char *name) {
  for (int i=0;i<sizeof(fs_support)/sizeof(fs_type_mapping_t);++i)
  {
    if (strcmp(fs_support[i].name, name)==0)
    {
      return fs_support+i;
    }
  }
  return NULL;
}

fs_type_mapping_t *find_fs_type_by_code(fs_type_code_e code) {
  for (int i=0;i<sizeof(fs_support)/sizeof(fs_type_mapping_t);++i)
  {
    if (fs_support[i].code == code)
    {
      return fs_support+i;
    }
  }
  return NULL;
}

static int check_size(const char* file, size_t max_length) {
  int fd = open(file, O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "can not open %s\n", file);
    return 1;
  }
  off_t length0 = lseek(fd, 0, SEEK_END);
  close(fd);
  if (length0 >= 0) {
    if (length0 > max_length) {
      fprintf(stderr, "size of %s is larger than %#lx\n", file, max_length);
      return 1;
    } else {
      return 0;
    }
  } else {
    fprintf(stderr, "seek failed on %s\n", file);
  }
  return 1;
}

static size_t align(size_t size, size_t align) {
  return ((size + align - 1) / align) * align;
}

static size_t firmware_auto_fill(size_t start, size_t fw_align, firmware_t* base, int count) {
  size_t pos = start;
  for (int i=0; i<count; ++i) {
    firmware_t* fw = base + i;
    if (calc_size_sha256(fw->file, &fw->_length, fw->_sha256)) {
      fprintf(stderr, "read %s failed!\n", fw->file);
      return 1;
    }
    fw->_offset = pos;
    fw->_padding = align(fw->_length, fw_align);
    pos += fw->_padding;
  }
  return pos;
}

int layout_auto_fill(layout_t *layout) {
  size_t pos = firmware_auto_fill(layout->fw_start, layout->fw_align, layout->fw, layout->_fw_count);
  if (layout->_gold_count > 0 && pos > layout->gold_start) {
    fprintf(stderr, "firmwares overlaps gold firmwares, %#lx > %#lx\n", pos, layout->gold_start);
    return 1;
  }

  if (layout->_gold_count > 0)
    pos = firmware_auto_fill(layout->gold_start, layout->fw_align, layout->gold, layout->_gold_count);
  if (pos > layout->part_start) {
    fprintf(stderr, "%s firmwares overlaps normal partitions, %#lx > %#lx\n", layout->_gold_count>0?"gold":"", pos, layout->part_start);
    return 1;
  }

  pos = align(layout->part_start, layout->part_align);
  for (int i=0;i<layout->_part_count;++i) {
    partition_t* part = (layout->part)+i;
    if (part->size < 0) {
      if (i + 1 != layout->_part_count) {
        fprintf(stderr, "partition[%d] is not the last partition, can not auto fill size\n", i);
        return 1;
      }
      if (pos + layout->part_align >= layout->size) {
        fprintf(stderr, "there is no space for partition[%d]\n", i);
        return 1;
      }
      part->size = align(layout->size - pos - layout->part_align + 1, layout->part_align);
    }
    if (part->size < 0x2000) {
        fprintf(stderr, "size of partition[%d] is little than %#x bytes\n", i, 0x2000);
        return 1;
    }
    if (check_size(part->file, part->size)) {
      return 1;
    }
    part->_offset = pos;
    pos += align(part->size, layout->part_align);
    if (pos > layout->size) {
      fprintf(stderr, "partition[%d] exceeds flash size, %#lx > %#lx\n", i, pos, layout->part_start);
      return 1;
    }
  }
  return 0;
}
