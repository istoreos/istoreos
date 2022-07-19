/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include "fwtbl.h"
#include "layout.h"
#include "io.h"
#include "mbr.h"

#define FWTABLE_FILE "fw_tbl.bin"
#define GOLD_FWTABLE_FILE "gold_fw_tbl.bin"
#define MBR_FILE "mbr.bin"

int gen_mbr(layout_t *layout, FILE *out) {
  mbr_t mbr;
  int ret = 0;
  if (layout->_part_count > 4) {
    fprintf(stderr, "not support MBR with over 4 partitions yet\n");
    return 1;
  }
  memset(&mbr, 0, sizeof(mbr_t));
  mbr.signature = 0xAA55;
  for (int i=0;i<layout->_part_count;++i) {
    partition_t* part0 = (layout->part) + i;
    mbr.parts[i].status = 0;
    memcpy(mbr.parts[i].chs_first_sector, "\x03\xd0\xff", 3);
    mbr.parts[i].type = 0x83;
    memcpy(mbr.parts[i].chs_last_sector, "\x03\xd0\xff", 3);
    mbr.parts[i].lba = part0->_offset >> 9;
    mbr.parts[i].sectors = (part0->size >> 9) - 16;// partition's gap
  }

  if (fwrite(&mbr, sizeof(mbr_t), 1, out) != 1) {
    ret = 1;
  }

  return ret;
}

int gen_fwtbl(layout_t *layout, FILE *out, int is_gold) {
  int ret = 0;
  int fw_count = is_gold?layout->_gold_count:layout->_fw_count;
  firmware_t *lfw = is_gold?layout->gold:layout->fw;
  size_t header_size = sizeof(fw_desc_table_v1_t);
  size_t part_size = is_gold?0:(sizeof(part_desc_entry_v1_t) * (layout->_part_count + 1));
  size_t fw_size = sizeof(fw_desc_entry_v2_t) * fw_count;
  size_t fw_tbl_size = header_size + part_size + fw_size;

  unsigned char* buf = (unsigned char*)malloc(fw_tbl_size);

  memset(buf, 0, fw_tbl_size);

  fw_desc_table_v1_t * header = (fw_desc_table_v1_t *)buf;
  memcpy(header->signature, FIRMWARE_DESCRIPTION_TABLE_SIGNATURE, 8);
  header->version = FW_DESC_TABLE_V2_T_VERSION_2;
  header->paddings = (fw_tbl_size + 0x1ff) / 0x200 * 0x200;
  header->part_list_len = part_size;
  header->fw_list_len = fw_size;

  fw_desc_entry_v2_t * fw = (fw_desc_entry_v2_t *)(buf + header_size + part_size);
  if (!is_gold) {
    part_desc_entry_v1_t * part = (part_desc_entry_v1_t *)(buf + header_size);
    part[0].type = 1;
    part[0].ro = 1;
    part[0].length = layout->part_start;
    part[0].fw_count = layout->_part_count;

    part += 1;
    for (int i=0;i<layout->_part_count;++i) {
      partition_t* part0 = (layout->part) + i;
      part[i].type = 2; // FS
      part[i].ro = 0;
      part[i].length = part0->size;
      part[i].fw_count = 1;
      part[i].fw_type = part0->filesystem;
      part[i].partIdx = i + 1;
      strcpy(part[i].mount_point, part0->mp);
    }
  }

  for (int i=0;i<fw_count;++i) {
    firmware_t* fw0 = lfw+i;
    fw[i].type = fw0->type;
    fw[i].ro = 1;
    fw[i].target_addr = fw0->target;
    fw[i].offset = fw0->_offset;
    fw[i].length = fw0->_length;
    fw[i].paddings = fw0->_padding;
    memcpy(fw[i].sha_hash, fw0->_sha256, 32);
  }

  uint32_t sum = 0;
  for (size_t i=12;i<fw_tbl_size;++i) {
    sum += buf[i];
  }
  header->checksum = sum;

  if (fwrite(buf, fw_tbl_size, 1, out) != 1) {
    ret = 1;
  } else {
    if (is_gold) {
      layout->_gold_table_size = fw_tbl_size;
    } else {
      layout->_fw_table_size = fw_tbl_size;
    }
  }

  free(buf);
  return ret;
}

int gen_normal_fwtbl(layout_t *layout, FILE *out) {
  return gen_fwtbl(layout, out, 0);
}

int gen_gold_fwtbl(layout_t *layout, FILE *out) {
  return gen_fwtbl(layout, out, 1);
}

int gen_a_config_txt(layout_t *layout, FILE *out) {
  fputs("\
# Package Information\n\
company=\"\"\n\
description=\"\"\n\
modelname=\"\"\n\
version=\"\"\n\
releaseDate=\"\"\n\
signature=\"\"\n\
# Package Configuration\n\
start_customer=y\n\
verify=y\n\
# bootcode=y\n\
install_dtb=y\n\
# update_etc=y\n\
install_avfile_count=0\n\
reboot_delay=5\n\
efuse_key=0\n\
efuse_fw=0\n\
rpmb_fw=0\n\
secure_boot=0\n\
", out);

  fputs("###\n###	  fw = (type file target)\n", out);
  for (int i=0;i<layout->_fw_count;++i) {
    firmware_t* fw = (layout->fw)+i;
    fprintf(out, "fw = %s %s %#lx\n", find_fw_type_by_code(fw->type)->c_name, fw->file, fw->target);
  }
  fputs("###\n###	  part = (name mount_point filesystem file size)\n", out);
  for (int i=0;i<layout->_part_count;++i) {
    partition_t* part = (layout->part)+i;
    fprintf(out, "part = %s %s %s %s %ld\n", part->name, part->mp, find_fs_type_by_code(part->filesystem)->name, part->file, part->size);
  }
  return 0;
}

int gen_layout_txt(layout_t *layout, FILE *out) {
  time_t now;
  struct tm * timeinfo;
  char buffer [128];
  time(&now);
  timeinfo=localtime(&now);
  strftime(buffer, sizeof(buffer), "#define CREATE_DATE \" %b %d %Y \"\n#define CREATE_TIME \" %H:%M:%S \"\n", timeinfo);
  fputs(buffer, out);
  fputs("\
#define BOOTTYPE \" BOOTTYPE_COMPLETE \"\n\
#define SSUWORKPART 0\n\
#define BOOTPART 0\n\
", out);

  for (int i=0;i<layout->_fw_count;++i) {
    firmware_t* fw = (layout->fw)+i;
    fprintf(out, "#define FW_%s \" target=%lx offset=%lx size=%lx type=bin name=%s \"\n", 
      find_fw_type_by_code(fw->type)->l_name,
      fw->target,
      fw->_offset,
      fw->_length,
      fw->file);
  }
  fprintf(out, "#define FW_FWTBL \" target=0 offset=%lx size=%lx type=bin name=%s \"\n", 
    layout->fw_table_offset, 
    layout->_fw_table_size,
    FWTABLE_FILE);
  if (layout->_gold_count > 0) {
    if (layout->gold_table_offset > 0) {
      // there is not any GOLD_FWTBL, so use unknown fwtype FW_CONFIG
      fprintf(out, "#define FW_CONFIG \" target=0 offset=%lx size=%lx type=bin name=%s \"\n", 
        layout->gold_table_offset, 
        layout->_gold_table_size,
        GOLD_FWTABLE_FILE);
    }
    for (int i=0;i<layout->_gold_count;++i) {
      firmware_t* fw = (layout->gold)+i;
      fw_type_mapping_t *t = find_fw_type_by_code(fw->type);
      fprintf(out, "#define FW_GOLD_%s \" target=%lx offset=%lx size=%lx type=bin name=%s \"\n", 
        t->g_l_name?t->g_l_name:t->l_name,
        fw->target,
        fw->_offset,
        fw->_length,
        fw->file);
    }
  }
  for (int i=0;i<layout->_part_count;++i) {
    partition_t* part = (layout->part)+i;
    fprintf(out, "#define PART%d \" offset=%lx size=%lx mount_point=%s \
mount_dev=/dev/block/mmcblk0p%d filesystem=%s partname=%s type=%s name=%s \"\n", 
    i, part->_offset, part->size, part->mp,
    i+1, find_fs_type_by_code(part->filesystem)->name,
    part->name, part->filetype, part->file);
  }
  fprintf(out, "#define MBR0 \" offset=0 size=200 name=%s \"\n", MBR_FILE);
  fprintf(out, "#define TAG 45\n");
  return 0;
}

int gen_file(layout_t *layout, const char* file, int (*func)(layout_t *layout, FILE *out)) {
  int ret = 0;
  FILE* f = fopen(file, "w");
  if (f == NULL) {
    fprintf(stderr, "can not open %s\n", file);
    return 1;
  }
  if (func(layout, f)) {
    ret = 1;
  }
  fclose(f);
  return ret;
}

#define LAYOUT_MAX_SIZE 8192

int main (int argc, char* argv[])
{
    char* layoutfile;
    ssize_t layoutsize;
    char layoutstr[LAYOUT_MAX_SIZE + 1];
    layout_t *layout;
    int ret = -1;

    if( 2 > argc || 3 < argc) {
        printf(
            "Syntax\n"
            "   %s <LAYOUT.json> [<WORKING_DIR>]\n", argv[0]);
        return 1;
    }

    layoutfile = argv[1];

    layoutsize = fullread(layoutfile, layoutstr, LAYOUT_MAX_SIZE);
    if (layoutsize < 0) {
      fprintf(stderr, "%s can not be opened or it's large than %d bytes\n", layoutfile, LAYOUT_MAX_SIZE);
      return -1;
    }
    layoutstr[layoutsize] = '\0';

    layout = parse_layout(layoutstr, layoutsize);
    if (!layout) {
      goto fail;
    }

    if (argc > 2) {
      if (chdir(argv[2])) {
        fprintf(stderr, "can not change current working directory to %s\n", argv[2]);
        goto fail;
      }
    }

    if (layout_auto_fill(layout)) {
      goto fail;
    }

    if (gen_file(layout, "config.txt", gen_a_config_txt)
      || gen_file(layout, FWTABLE_FILE, gen_normal_fwtbl)
      || (layout->_gold_count > 0 && gen_file(layout, GOLD_FWTABLE_FILE, gen_gold_fwtbl))
      || gen_file(layout, MBR_FILE, gen_mbr)
      || gen_file(layout, "layout.txt", gen_layout_txt)) {
      goto fail;
    }

    ret = 0;
fail:
    if (layout)
      free_layout(layout);
    return ret;
}
