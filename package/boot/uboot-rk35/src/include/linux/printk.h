#ifndef __KERNEL_PRINTK__
#define __KERNEL_PRINTK__

#include <stdio.h>
#include <linux/compiler.h>

#define KERN_EMERG
#define KERN_ALERT
#define KERN_CRIT
#define KERN_ERR
#define KERN_WARNING
#define KERN_NOTICE
#define KERN_INFO
#define KERN_DEBUG
#define KERN_CONT

#define printk(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)

/*
 * Dummy printk for disabled debugging statements to use whilst maintaining
 * gcc's format checking.
 */
#define no_printk(fmt, ...)				\
({							\
	if (0)						\
		printk(fmt, ##__VA_ARGS__);		\
	0;						\
})

#define __printk(level, fmt, ...)					\
({									\
	level < CONFIG_LOGLEVEL ? printk(fmt, ##__VA_ARGS__) : 0;	\
})

#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

#define pr_emerg(fmt, ...) \
	__printk(0, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_alert(fmt, ...) \
	__printk(1, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_crit(fmt, ...) \
	__printk(2, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_err(fmt, ...) \
	__printk(3, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warning(fmt, ...) \
	__printk(4, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn pr_warning
#define pr_notice(fmt, ...) \
	__printk(5, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_info(fmt, ...) \
	__printk(6, pr_fmt(fmt), ##__VA_ARGS__)

#define pr_cont(fmt, ...) \
	printk(fmt, ##__VA_ARGS__)

/* pr_devel() should produce zero code unless DEBUG is defined */
#ifdef DEBUG
#define pr_devel(fmt, ...) \
	__printk(7, pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_devel(fmt, ...) \
	no_printk(pr_fmt(fmt), ##__VA_ARGS__)
#endif

#ifdef DEBUG
#define pr_debug(fmt, ...) \
	__printk(7, pr_fmt(fmt), ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...) \
	no_printk(pr_fmt(fmt), ##__VA_ARGS__)
#endif

#define printk_once(fmt, ...) \
	printk(fmt, ##__VA_ARGS__)

#endif
