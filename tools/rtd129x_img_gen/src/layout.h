#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "fwtbl.h"

typedef struct {
	fw_type_code_e code;
	const char *c_name;
  const char *l_name;
  const char *g_c_name; // gold
  const char *g_l_name; // gold
} fw_type_mapping_t;

typedef struct {
	fs_type_code_e code;
	const char *name;
} fs_type_mapping_t;

typedef struct {
  fw_type_code_e type;
  size_t target;
  const char * file;
  size_t _offset;
  size_t _length;
  size_t _padding;
  unsigned char	_sha256[32];
} firmware_t;

typedef struct {
  const char * name;
  const char * mp;
  ssize_t size;
  const char * filetype;
  fs_type_code_e filesystem;
  const char * file;
  size_t _offset;
} partition_t;

typedef struct {
  size_t size;
  size_t fw_table_offset;
  size_t gold_table_offset;
  size_t fw_start;
  size_t gold_start;
  size_t fw_align;
  size_t part_start;
  size_t part_align;
  firmware_t *fw;
  firmware_t *gold;
  partition_t *part;
  int _fw_count;
  int _part_count;
  int _gold_count;
  size_t _fw_table_size;
  size_t _gold_table_size;
} layout_t;

fw_type_mapping_t *find_fw_type_by_ln(const char *name);
fw_type_mapping_t *find_fw_type_by_code(fw_type_code_e code);

fs_type_mapping_t *find_fs_type_by_name(const char *name);
fs_type_mapping_t *find_fs_type_by_code(fs_type_code_e code);

int layout_auto_fill(layout_t *layout);

void free_layout(layout_t *layout);
layout_t *parse_layout(const char* content, size_t size);

#endif