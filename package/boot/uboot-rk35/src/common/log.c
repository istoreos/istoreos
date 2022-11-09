/*
 * Logging support
 *
 * Copyright (c) 2017 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <log.h>
#include <malloc.h>

DECLARE_GLOBAL_DATA_PTR;

static struct log_device *log_device_find_by_name(const char *drv_name)
{
	struct log_device *ldev;

	list_for_each_entry(ldev, &gd->log_head, sibling_node) {
		if (!strcmp(drv_name, ldev->drv->name))
			return ldev;
	}

	return NULL;
}

/**
 * log_has_cat() - check if a log category exists within a list
 *
 * @cat_list: List of categories to check, at most LOGF_MAX_CATEGORIES entries
 *	long, terminated by LC_END if fewer
 * @cat: Category to search for
 * @return true if @cat is in @cat_list, else false
 */
static bool log_has_cat(enum log_category_t cat_list[], enum log_category_t cat)
{
	int i;

	for (i = 0; i < LOGF_MAX_CATEGORIES && cat_list[i] != LOGC_END; i++) {
		if (cat_list[i] == cat)
			return true;
	}

	return false;
}

/**
 * log_has_file() - check if a file is with a list
 *
 * @file_list: List of files to check, separated by comma
 * @file: File to check for. This string is matched against the end of each
 *	file in the list, i.e. ignoring any preceding path. The list is
 *	intended to consist of relative pathnames, e.g. common/main.c,cmd/log.c
 * @return true if @file is in @file_list, else false
 */
static bool log_has_file(const char *file_list, const char *file)
{
	int file_len = strlen(file);
	const char *s, *p;
	int substr_len;

	for (s = file_list; *s; s = p + (*p != '\0')) {
		p = strchrnul(s, ',');
		substr_len = p - s;
		if (file_len >= substr_len &&
		    !strncmp(file + file_len - substr_len, s, substr_len))
			return true;
	}

	return false;
}

/**
 * log_passes_filters() - check if a log record passes the filters for a device
 *
 * @ldev: Log device to check
 * @rec: Log record to check
 * @return true if @rec is not blocked by the filters in @ldev, false if it is
 */
static bool log_passes_filters(struct log_device *ldev, struct log_rec *rec)
{
	struct log_filter *filt;

	/* If there are no filters, filter on the default log level */
	if (list_empty(&ldev->filter_head)) {
		if (rec->level > gd->default_log_level)
			return false;
		return true;
	}

	list_for_each_entry(filt, &ldev->filter_head, sibling_node) {
		if (rec->level > filt->max_level)
			continue;
		if ((filt->flags & LOGFF_HAS_CAT) &&
		    !log_has_cat(filt->cat_list, rec->cat))
			continue;
		if (filt->file_list &&
		    !log_has_file(filt->file_list, rec->file))
			continue;
		return true;
	}

	return false;
}

/**
 * log_dispatch() - Send a log record to all log devices for processing
 *
 * The log record is sent to each log device in turn, skipping those which have
 * filters which block the record
 *
 * @rec: Log record to dispatch
 * @return 0 (meaning success)
 */
static int log_dispatch(struct log_rec *rec)
{
	struct log_device *ldev;

	list_for_each_entry(ldev, &gd->log_head, sibling_node) {
		if (log_passes_filters(ldev, rec))
			ldev->drv->emit(ldev, rec);
	}

	return 0;
}

int _log(enum log_category_t cat, enum log_level_t level, const char *file,
	 int line, const char *func, const char *fmt, ...)
{
	char buf[CONFIG_SYS_CBSIZE];
	struct log_rec rec;
	va_list args;

	rec.cat = cat;
	rec.level = level;
	rec.file = file;
	rec.line = line;
	rec.func = func;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	rec.msg = buf;
	if (!gd || !(gd->flags & GD_FLG_LOG_READY)) {
		if (gd)
			gd->log_drop_count++;
		return -ENOSYS;
	}
	log_dispatch(&rec);

	return 0;
}

int log_add_filter(const char *drv_name, enum log_category_t cat_list[],
		   enum log_level_t max_level, const char *file_list)
{
	struct log_filter *filt;
	struct log_device *ldev;
	int i;

	ldev = log_device_find_by_name(drv_name);
	if (!ldev)
		return -ENOENT;
	filt = (struct log_filter *)calloc(1, sizeof(*filt));
	if (!filt)
		return -ENOMEM;

	if (cat_list) {
		filt->flags |= LOGFF_HAS_CAT;
		for (i = 0; ; i++) {
			if (i == ARRAY_SIZE(filt->cat_list))
				return -ENOSPC;
			filt->cat_list[i] = cat_list[i];
			if (cat_list[i] == LOGC_END)
				break;
		}
	}
	filt->max_level = max_level;
	if (file_list) {
		filt->file_list = strdup(file_list);
		if (!filt->file_list)
			goto nomem;
	}
	filt->filter_num = ldev->next_filter_num++;
	list_add_tail(&filt->sibling_node, &ldev->filter_head);

	return filt->filter_num;

nomem:
	free(filt);
	return -ENOMEM;
}

int log_remove_filter(const char *drv_name, int filter_num)
{
	struct log_filter *filt;
	struct log_device *ldev;

	ldev = log_device_find_by_name(drv_name);
	if (!ldev)
		return -ENOENT;

	list_for_each_entry(filt, &ldev->filter_head, sibling_node) {
		if (filt->filter_num == filter_num) {
			list_del(&filt->sibling_node);
			free(filt);

			return 0;
		}
	}

	return -ENOENT;
}

int log_init(void)
{
	struct log_driver *drv = ll_entry_start(struct log_driver, log_driver);
	const int count = ll_entry_count(struct log_driver, log_driver);
	struct log_driver *end = drv + count;

	/*
	 * We cannot add runtime data to the driver since it is likely stored
	 * in rodata. Instead, set up a 'device' corresponding to each driver.
	 * We only support having a single device.
	 */
	INIT_LIST_HEAD((struct list_head *)&gd->log_head);
	while (drv < end) {
		struct log_device *ldev;

		ldev = calloc(1, sizeof(*ldev));
		if (!ldev) {
			debug("%s: Cannot allocate memory\n", __func__);
			return -ENOMEM;
		}
		INIT_LIST_HEAD(&ldev->filter_head);
		ldev->drv = drv;
		list_add_tail(&ldev->sibling_node,
			      (struct list_head *)&gd->log_head);
		drv++;
	}
	gd->flags |= GD_FLG_LOG_READY;
	gd->default_log_level = LOGL_INFO;

	return 0;
}
