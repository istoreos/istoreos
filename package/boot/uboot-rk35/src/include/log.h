/*
 * Logging support
 *
 * Copyright (c) 2017 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __LOG_H
#define __LOG_H

#include <dm/uclass-id.h>
#include <linux/list.h>

/** Log levels supported, ranging from most to least important */
enum log_level_t {
	LOGL_EMERG = 0,		/*U-Boot is unstable */
	LOGL_ALERT,		/* Action must be taken immediately */
	LOGL_CRIT,		/* Critical conditions */
	LOGL_ERR,		/* Error that prevents something from working */
	LOGL_WARNING,		/* Warning may prevent optimial operation */
	LOGL_NOTICE,		/* Normal but significant condition, printf() */
	LOGL_INFO,		/* General information message */
	LOGL_DEBUG,		/* Basic debug-level message */
	LOGL_DEBUG_CONTENT,	/* Debug message showing full message content */
	LOGL_DEBUG_IO,		/* Debug message showing hardware I/O access */

	LOGL_COUNT,
	LOGL_FIRST = LOGL_EMERG,
	LOGL_MAX = LOGL_DEBUG,
};

/**
 * Log categories supported. Most of these correspond to uclasses (i.e.
 * enum uclass_id) but there are also some more generic categories
 */
enum log_category_t {
	LOGC_FIRST = 0,	/* First part mirrors UCLASS_... */

	LOGC_NONE = UCLASS_COUNT,
	LOGC_ARCH,
	LOGC_BOARD,
	LOGC_CORE,
	LOGC_DM,	/* Core driver-model */
	LOGC_DT,	/* Device-tree */
	LOGC_EFI,	/* EFI implementation */
	LOGC_ALLOC,	/* Memory allocation */

	LOGC_COUNT,
	LOGC_END,
};

/* Helper to cast a uclass ID to a log category */
static inline int log_uc_cat(enum uclass_id id)
{
	return (enum log_category_t)id;
}

/**
 * _log() - Internal function to emit a new log record
 *
 * @cat: Category of log record (indicating which subsystem generated it)
 * @level: Level of log record (indicating its severity)
 * @file: File name of file where log record was generated
 * @line: Line number in file where log record was generated
 * @func: Function where log record was generated
 * @fmt: printf() format string for log record
 * @...: Optional parameters, according to the format string @fmt
 * @return 0 if log record was emitted, -ve on error
 */
int _log(enum log_category_t cat, enum log_level_t level, const char *file,
	 int line, const char *func, const char *fmt, ...);

/* Define this at the top of a file to add a prefix to debug messages */
#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

/* Use a default category if this file does not supply one */
#ifndef LOG_CATEGORY
#define LOG_CATEGORY LOGC_NONE
#endif

/*
 * This header may be including when CONFIG_LOG is disabled, in which case
 * CONFIG_LOG_MAX_LEVEL is not defined. Add a check for this.
 */
#if CONFIG_IS_ENABLED(LOG)
#define _LOG_MAX_LEVEL CONFIG_VAL(LOG_MAX_LEVEL)
#else
#define _LOG_MAX_LEVEL LOGL_INFO
#endif

/* Emit a log record if the level is less that the maximum */
#define log(_cat, _level, _fmt, _args...) ({ \
	int _l = _level; \
	if (_l <= _LOG_MAX_LEVEL) \
		_log((enum log_category_t)(_cat), _l, __FILE__, __LINE__, \
		      __func__, \
		      pr_fmt(_fmt), ##_args); \
	})

#ifdef DEBUG
#define _DEBUG	1
#else
#define _DEBUG	0
#endif

#ifdef CONFIG_SPL_BUILD
#define _SPL_BUILD	1
#else
#define _SPL_BUILD	0
#endif

#if !_DEBUG && CONFIG_IS_ENABLED(LOG)

#define debug_cond(cond, fmt, args...)			\
	do {						\
		if (1)					\
			log(LOG_CATEGORY, LOGL_DEBUG, fmt, ##args); \
	} while (0)

#else /* _DEBUG */

/*
 * Output a debug text when condition "cond" is met. The "cond" should be
 * computed by a preprocessor in the best case, allowing for the best
 * optimization.
 */
#define debug_cond(cond, fmt, args...)			\
	do {						\
		if (cond)				\
			printf(pr_fmt(fmt), ##args);	\
	} while (0)

#endif /* _DEBUG */

/* Show a message if DEBUG is defined in a file */
#define debug(fmt, args...)			\
	debug_cond(_DEBUG, fmt, ##args)

/* Show a message if not in SPL */
#define warn_non_spl(fmt, args...)			\
	debug_cond(!_SPL_BUILD, fmt, ##args)

/*
 * An assertion is run-time check done in debug mode only. If DEBUG is not
 * defined then it is skipped. If DEBUG is defined and the assertion fails,
 * then it calls panic*( which may or may not reset/halt U-Boot (see
 * CONFIG_PANIC_HANG), It is hoped that all failing assertions are found
 * before release, and after release it is hoped that they don't matter. But
 * in any case these failing assertions cannot be fixed with a reset (which
 * may just do the same assertion again).
 */
void __assert_fail(const char *assertion, const char *file, unsigned int line,
		   const char *function);
#define assert(x) \
	({ if (!(x) && _DEBUG) \
		__assert_fail(#x, __FILE__, __LINE__, __func__); })

#ifdef CONFIG_LOG_ERROR_RETURN
#define log_ret(_ret) ({ \
	int __ret = (_ret); \
	if (__ret < 0) \
		log(LOG_CATEGORY, LOGL_ERR, "returning err=%d\n", __ret); \
	__ret; \
	})
#define log_msg_ret(_msg, _ret) ({ \
	int __ret = (_ret); \
	if (__ret < 0) \
		log(LOG_CATEGORY, LOGL_ERR, "%s: returning err=%d\n", _msg, \
		    __ret); \
	__ret; \
	})
#else
#define log_ret(_ret) (_ret)
#define log_msg_ret(_msg, _ret) (_ret)
#endif

/**
 * struct log_rec - a single log record
 *
 * Holds information about a single record in the log
 *
 * Members marked as 'not allocated' are stored as pointers and the caller is
 * responsible for making sure that the data pointed to is not overwritten.
 * Memebers marked as 'allocated' are allocated (e.g. via strdup()) by the log
 * system.
 *
 * @cat: Category, representing a uclass or part of U-Boot
 * @level: Severity level, less severe is higher
 * @file: Name of file where the log record was generated (not allocated)
 * @line: Line number where the log record was generated
 * @func: Function where the log record was generated (not allocated)
 * @msg: Log message (allocated)
 */
struct log_rec {
	enum log_category_t cat;
	enum log_level_t level;
	const char *file;
	int line;
	const char *func;
	const char *msg;
};

struct log_device;

/**
 * struct log_driver - a driver which accepts and processes log records
 *
 * @name: Name of driver
 */
struct log_driver {
	const char *name;
	/**
	 * emit() - emit a log record
	 *
	 * Called by the log system to pass a log record to a particular driver
	 * for processing. The filter is checked before calling this function.
	 */
	int (*emit)(struct log_device *ldev, struct log_rec *rec);
};

/**
 * struct log_device - an instance of a log driver
 *
 * Since drivers are set up at build-time we need to have a separate device for
 * the run-time aspects of drivers (currently just a list of filters to apply
 * to records send to this device).
 *
 * @next_filter_num: Seqence number of next filter filter added (0=no filters
 *	yet). This increments with each new filter on the device, but never
 *	decrements
 * @drv: Pointer to driver for this device
 * @filter_head: List of filters for this device
 * @sibling_node: Next device in the list of all devices
 */
struct log_device {
	int next_filter_num;
	struct log_driver *drv;
	struct list_head filter_head;
	struct list_head sibling_node;
};

enum {
	LOGF_MAX_CATEGORIES = 5,	/* maximum categories per filter */
};

enum log_filter_flags {
	LOGFF_HAS_CAT		= 1 << 0,	/* Filter has a category list */
};

/**
 * struct log_filter - criterial to filter out log messages
 *
 * @filter_num: Sequence number of this filter.  This is returned when adding a
 *	new filter, and must be provided when removing a previously added
 *	filter.
 * @flags: Flags for this filter (LOGFF_...)
 * @cat_list: List of categories to allow (terminated by LOGC_none). If empty
 *	then all categories are permitted. Up to LOGF_MAX_CATEGORIES entries
 *	can be provided
 * @max_level: Maximum log level to allow
 * @file_list: List of files to allow, separated by comma. If NULL then all
 *	files are permitted
 * @sibling_node: Next filter in the list of filters for this log device
 */
struct log_filter {
	int filter_num;
	int flags;
	enum log_category_t cat_list[LOGF_MAX_CATEGORIES];
	enum log_level_t max_level;
	const char *file_list;
	struct list_head sibling_node;
};

#define LOG_DRIVER(_name) \
	ll_entry_declare(struct log_driver, _name, log_driver)

/* Handle the 'log test' command */
int do_log_test(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[]);

/**
 * log_add_filter() - Add a new filter to a log device
 *
 * @drv_name: Driver name to add the filter to (since each driver only has a
 *	single device)
 * @cat_list: List of categories to allow (terminated by LOGC_none). If empty
 *	then all categories are permitted. Up to LOGF_MAX_CATEGORIES entries
 *	can be provided
 * @max_level: Maximum log level to allow
 * @file_list: List of files to allow, separated by comma. If NULL then all
 *	files are permitted
 * @return the sequence number of the new filter (>=0) if the filter was added,
 *	or a -ve value on error
 */
int log_add_filter(const char *drv_name, enum log_category_t cat_list[],
		   enum log_level_t max_level, const char *file_list);

/**
 * log_remove_filter() - Remove a filter from a log device
 *
 * @drv_name: Driver name to remove the filter from (since each driver only has
 *	a single device)
 * @filter_num: Filter number to remove (as returned by log_add_filter())
 * @return 0 if the filter was removed, -ENOENT if either the driver or the
 *	filter number was not found
 */
int log_remove_filter(const char *drv_name, int filter_num);

#if CONFIG_IS_ENABLED(LOG)
/**
 * log_init() - Set up the log system ready for use
 *
 * @return 0 if OK, -ENOMEM if out of memory
 */
int log_init(void);
#else
static inline int log_init(void)
{
	return 0;
}
#endif

#endif
