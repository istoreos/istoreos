/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "layout.h"

static 
int json_getstr(cJSON * json, const char* field, const char **value) {
  *value = cJSON_GetStringValue(cJSON_GetObjectItem(json, field));
  if (*value == NULL) {
    fprintf(stderr, "%s undefined\n", field);
    return 1;
  }
  return 0;
}

static 
int json_getlong(cJSON * json, const char* field, long *value) {
  const char *val;
  if (json_getstr(json, field, &val)) {
    return 1;
  }
  *value = strtol(val, NULL, 0);
  return 0;
}

static 
int json_tofirmware(cJSON * json, firmware_t *p) {
  const char* fw_type;
  if (
       json_getstr(json, "type", &fw_type)
    || json_getlong(json, "target", &p->target)
    || json_getstr(json, "file", &p->file)
    ) {
    return 1;
  }
  fw_type_mapping_t * tm = find_fw_type_by_ln(fw_type);
  if (tm == NULL) {
    fprintf(stderr, "unsupported fwtype:%s\n", fw_type);
    return 1;
  }
  p->type = tm->code;
  return 0;
}

static 
int json_tofirmwares(cJSON * array, int count, firmware_t *p) {
  for (int i=0;i<count;++i) {
    cJSON * fwi = cJSON_GetArrayItem(array, i);
    if (json_tofirmware(fwi, p)) {
      return 1;
    }
    ++p;
  }
  return 0;
}

static 
int json_topartition(cJSON * json, partition_t *p) {
  const char* fs_type;
  if (
      json_getstr(json, "filesystem", &fs_type)
    || json_getstr(json, "name", &p->name)
    || json_getstr(json, "mp", &p->mp)
    || json_getlong(json, "size", &p->size)
    || json_getstr(json, "filetype", &p->filetype)
    || json_getstr(json, "file", &p->file)
    ) {
    return 1;
  }
  fs_type_mapping_t * tm = find_fs_type_by_name(fs_type);
  if (tm == NULL) {
    fprintf(stderr, "unsupported fstype:%s\n", fs_type);
    return 1;
  }
  p->filesystem = tm->code;
  return 0;
}

static 
int json_topartitions(cJSON * array, int count, partition_t *p) {
  for (int i=0;i<count;++i) {
    cJSON * parti = cJSON_GetArrayItem(array, i);
    if (json_topartition(parti, p)) {
      return 1;
    }
    ++p;
  }
  return 0;
}

void free_layout(layout_t *layout) {
  if (layout->fw) {
    free(layout->fw);
  }
  if (layout->part) {
    free(layout->part);
  }
  if (*((cJSON **)(layout+1))) {
    cJSON_Delete(*((cJSON **)(layout+1)));
  }
  free(layout);
}

layout_t *parse_layout(const char* layoutstr, size_t layoutsize) {
  layout_t *layout = (layout_t *)malloc(sizeof(layout_t) + sizeof(void*));
  layout->fw = NULL;
  layout->part = NULL;

  cJSON * json = cJSON_ParseWithLength(layoutstr, layoutsize);
  *((cJSON **)(layout+1)) = json;
  if (json == NULL) {
    fprintf(stderr, "parse json failed!\n");
    goto fail;
  }

  if (
      json_getlong(json, "size", &layout->size)
      || json_getlong(json, "fw_table_offset", &layout->fw_table_offset)
      || json_getlong(json, "fw_start", &layout->fw_start)
      || json_getlong(json, "fw_align", &layout->fw_align)
      || json_getlong(json, "part_start", &layout->part_start)
      || json_getlong(json, "part_align", &layout->part_align)
      ) {
        goto fail;
  }
  layout->gold_start = 0;
  json_getlong(json, "gold_start", &layout->gold_start);

  layout->gold_table_offset = 0;
  json_getlong(json, "gold_table_offset", &layout->gold_table_offset);

  cJSON * fw = cJSON_GetObjectItem(json, "fw");
  layout->_fw_count = cJSON_GetArraySize(fw);
  printf("fw count:%d\n", layout->_fw_count);
  layout->fw = (firmware_t *)malloc(sizeof(firmware_t) * (layout->_fw_count + 1));
  if (json_tofirmwares(fw, layout->_fw_count, layout->fw)) {
    goto fail;
  }

  cJSON * part = cJSON_GetObjectItem(json, "part");
  layout->_part_count = cJSON_GetArraySize(part);
  printf("part count:%d\n", layout->_part_count);
  layout->part = (partition_t *)malloc(sizeof(partition_t) * (layout->_part_count + 1));
  if (json_topartitions(part, layout->_part_count, layout->part)) {
    goto fail;
  }

  layout->_gold_count = 0;
  cJSON * gold = cJSON_GetObjectItem(json, "gold");
  if (gold) {
    if (layout->gold_start == 0 || layout->gold_table_offset == 0) {
      fprintf(stderr, "gold firmwares present, but gold_start is 0 or gold_table_offset is 0!\n");
      goto fail;
    }
    layout->_gold_count = cJSON_GetArraySize(gold);
    printf("gold count:%d\n", layout->_gold_count);
    layout->gold = (firmware_t *)malloc(sizeof(firmware_t) * (layout->_gold_count + 1));
    if (json_tofirmwares(gold, layout->_gold_count, layout->gold)) {
      goto fail;
    }
  }

  return layout;
fail:
  free_layout(layout);
  return NULL;
}
