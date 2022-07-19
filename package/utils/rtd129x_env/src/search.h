/*
 * Declarations for System V style searching functions.
 * Copyright (C) 1995-1999, 2000 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * SPDX-License-Identifier:	LGPL-2.1+
 */

/*
 * Based on code from uClibc-0.9.30.3
 * Extensions for use within U-Boot
 * Copyright (C) 2010-2013 Wolfgang Denk <wd@denx.de>
 */

#ifndef _SEARCH_H
#define	_SEARCH_H 1

#include <stddef.h>

#define __set_errno(val) do { errno = val; } while (0)

enum env_op {
	env_op_create,
	env_op_delete,
	env_op_overwrite,
};

/* Action which shall be performed in the call the hsearch.  */
typedef enum {
	FIND,
	ENTER
} ACTION;

typedef struct entry {
	const char *key;
	char *data;
	int flags;
} ENTRY;

/* Opaque type for internal use.  */
struct _ENTRY;

/*
 * Family of hash table handling functions.  The functions also
 * have reentrant counterparts ending with _r.  The non-reentrant
 * functions all work on a signle internal hashing table.
 */

/* Data type for reentrant functions.  */
struct hsearch_data {
	struct _ENTRY *table;
	unsigned int size;
	unsigned int filled;
};

/* Create a new hashing table which will at most contain NEL elements.  */
extern int hcreate_r(size_t __nel, struct hsearch_data *__htab);

/* Destroy current internal hashing table.  */
extern void hdestroy_r(struct hsearch_data *__htab);

/*
 * Search for entry matching ITEM.key in internal hash table.  If
 * ACTION is `FIND' return found entry or signal error by returning
 * NULL.  If ACTION is `ENTER' replace existing data (if any) with
 * ITEM.data.
 * */
extern int hsearch_r(ENTRY __item, ACTION __action, ENTRY ** __retval,
		     struct hsearch_data *__htab, int __flag);

/*
 * Search for an entry matching `MATCH'.  Otherwise, Same semantics
 * as hsearch_r().
 */
extern int hmatch_r(const char *__match, int __last_idx, ENTRY ** __retval,
		    struct hsearch_data *__htab);

/* Search and delete entry matching ITEM.key in internal hash table. */
extern int hdelete_r(const char *__key, struct hsearch_data *__htab,
		     int __flag);

extern ssize_t hexport_r(struct hsearch_data *__htab,
		     const char __sep, int __flag, char **__resp, size_t __size,
		     int argc, char * const argv[]);

/*
 * nvars: length of vars array
 * vars: array of strings (variable names) to import (nvars == 0 means all)
 * do_apply: whether to call callback function to check the new argument,
 * and possibly apply changes (false means accept everything)
 */
extern int himport_r(struct hsearch_data *__htab,
		     const char *__env, size_t __size, const char __sep,
		     int __flag, int __crlf_is_lf, int nvars,
		     char * const vars[]);
			 
/*
 * Check weather default environment variables saved in emmc.
 * If not, add default environment variables in emmc.
 */

extern int h_detect_r(struct hsearch_data *htab,
		const char *env, size_t size, const char sep, int flag,
		int crlf_is_lf, int nvars, char * const vars[]);
		

/* Walk the whole table calling the callback on each element */
extern int hwalk_r(struct hsearch_data *__htab, int (*callback)(ENTRY *));

/* Flags for himport_r(), hexport_r(), hdelete_r(), and hsearch_r() */
#define H_NOCLEAR	(1 << 0) /* do not clear hash table before importing */
#define H_FORCE		(1 << 1) /* overwrite read-only/write-once variables */
#define H_INTERACTIVE	(1 << 2) /* indicate that an import is user directed */
#define H_HIDE_DOT	(1 << 3) /* don't print env vars that begin with '.' */
#define H_MATCH_KEY	(1 << 4) /* search/grep key  = variable names	     */
#define H_MATCH_DATA	(1 << 5) /* search/grep data = variable values	     */
#define H_MATCH_BOTH	(H_MATCH_KEY | H_MATCH_DATA) /* search/grep both     */
#define H_MATCH_IDENT	(1 << 6) /* search for indentical strings	     */
#define H_MATCH_SUBSTR	(1 << 7) /* search for substring matches	     */
#define H_MATCH_REGEX	(1 << 8) /* search for regular expression matches    */
#define H_MATCH_METHOD	(H_MATCH_IDENT | H_MATCH_SUBSTR | H_MATCH_REGEX)
#define H_PROGRAMMATIC	(1 << 9) /* indicate that an import is from setenv() */
#define H_ORIGIN_FLAGS	(H_INTERACTIVE | H_PROGRAMMATIC)

#endif /* search.h */
