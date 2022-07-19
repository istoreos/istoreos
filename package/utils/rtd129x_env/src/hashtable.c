/*
 * This implementation is based on code from uClibc-0.9.30.3 but was
 * modified and extended for use within U-Boot.
 *
 * Copyright (C) 2010-2013 Wolfgang Denk <wd@denx.de>
 *
 * Original license header:
 *
 * Copyright (C) 1993, 1995, 1996, 1997, 2002 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 * Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1993.
 *
 * SPDX-License-Identifier:	LGPL-2.1+
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>
#include <ctype.h>

# ifndef debug
#  ifdef DEBUG
#   define debug(fmt,args...)	printf(fmt ,##args)
#  else
#   define debug(fmt,args...)
#  endif
# endif


#ifndef	CONFIG_ENV_MIN_ENTRIES	/* minimum number of entries */
#define	CONFIG_ENV_MIN_ENTRIES 64
#endif
#ifndef	CONFIG_ENV_MAX_ENTRIES	/* maximum number of entries */
#define	CONFIG_ENV_MAX_ENTRIES 512
#endif

#include "search.h"

/*
 * [Aho,Sethi,Ullman] Compilers: Principles, Techniques and Tools, 1986
 * [Knuth]	      The Art of Computer Programming, part 3 (6.4)
 */

/*
 * The reentrant version has no static variables to maintain the state.
 * Instead the interface of all functions is extended to take an argument
 * which describes the current status.
 */

typedef struct _ENTRY {
	int used;
	ENTRY entry;
} _ENTRY;


static void _hdelete(const char *key, struct hsearch_data *htab, ENTRY *ep,
	int idx);

/*
 * hcreate()
 */

/*
 * For the used double hash method the table size has to be a prime. To
 * correct the user given table size we need a prime test.  This trivial
 * algorithm is adequate because
 * a)  the code is (most probably) called a few times per program run and
 * b)  the number is small because the table must fit in the core
 * */
static int isprime(unsigned int number)
{
	/* no even number will be passed */
	unsigned int div = 3;

	while (div * div < number && number % div != 0)
		div += 2;

	return number % div != 0;
}

/*
 * Before using the hash table we must allocate memory for it.
 * Test for an existing table are done. We allocate one element
 * more as the found prime number says. This is done for more effective
 * indexing as explained in the comment for the hsearch function.
 * The contents of the table is zeroed, especially the field used
 * becomes zero.
 */

int hcreate_r(size_t nel, struct hsearch_data *htab)
{
	/* Test for correct arguments.  */
	if (htab == NULL) {
		__set_errno(EINVAL);
		return 0;
	}

	/* There is still another table active. Return with error. */
	if (htab->table != NULL)
		return 0;

	/* Change nel to the first prime number not smaller as nel. */
	nel |= 1;		/* make odd */
	while (!isprime(nel))
		nel += 2;

	htab->size = nel;
	htab->filled = 0;

	/* allocate memory and zero out */
	htab->table = (_ENTRY *) calloc(htab->size + 1, sizeof(_ENTRY));
	if (htab->table == NULL)
		return 0;

	/* everything went alright */
	return 1;
}


/*
 * hdestroy()
 */

/*
 * After using the hash table it has to be destroyed. The used memory can
 * be freed and the local static variable can be marked as not used.
 */

void hdestroy_r(struct hsearch_data *htab)
{
	int i;

	/* Test for correct arguments.  */
	if (htab == NULL) {
		__set_errno(EINVAL);
		return;
	}

	/* free used memory */
	for (i = 1; i <= htab->size; ++i) {
		if (htab->table[i].used > 0) {
			ENTRY *ep = &htab->table[i].entry;

			free((void *)ep->key);
			free(ep->data);
		}
	}
	free(htab->table);

	/* the sign for an existing table is an value != NULL in htable */
	htab->table = NULL;
}

/*
 * hsearch()
 */

/*
 * This is the search function. It uses double hashing with open addressing.
 * The argument item.key has to be a pointer to an zero terminated, most
 * probably strings of chars. The function for generating a number of the
 * strings is simple but fast. It can be replaced by a more complex function
 * like ajw (see [Aho,Sethi,Ullman]) if the needs are shown.
 *
 * We use an trick to speed up the lookup. The table is created by hcreate
 * with one more element available. This enables us to use the index zero
 * special. This index will never be used because we store the first hash
 * index in the field used where zero means not used. Every other value
 * means used. The used field can be used as a first fast comparison for
 * equality of the stored and the parameter value. This helps to prevent
 * unnecessary expensive calls of strcmp.
 *
 * This implementation differs from the standard library version of
 * this function in a number of ways:
 *
 * - While the standard version does not make any assumptions about
 *   the type of the stored data objects at all, this implementation
 *   works with NUL terminated strings only.
 * - Instead of storing just pointers to the original objects, we
 *   create local copies so the caller does not need to care about the
 *   data any more.
 * - The standard implementation does not provide a way to update an
 *   existing entry.  This version will create a new entry or update an
 *   existing one when both "action == ENTER" and "item.data != NULL".
 * - Instead of returning 1 on success, we return the index into the
 *   internal hash table, which is also guaranteed to be positive.
 *   This allows us direct access to the found hash table slot for
 *   example for functions like hdelete().
 */

int hmatch_r(const char *match, int last_idx, ENTRY ** retval,
	     struct hsearch_data *htab)
{
	unsigned int idx;
	size_t key_len = strlen(match);

	for (idx = last_idx + 1; idx < htab->size; ++idx) {
		if (htab->table[idx].used <= 0)
			continue;
		if (!strncmp(match, htab->table[idx].entry.key, key_len)) {
			*retval = &htab->table[idx].entry;
			return idx;
		}
	}

	__set_errno(ESRCH);
	*retval = NULL;
	return 0;
}

/*
 * Compare an existing entry with the desired key, and overwrite if the action
 * is ENTER.  This is simply a helper function for hsearch_r().
 */
static inline int _compare_and_overwrite_entry(ENTRY item, ACTION action,
	ENTRY **retval, struct hsearch_data *htab, int flag,
	unsigned int hval, unsigned int idx)
{
	if (htab->table[idx].used == hval
	    && strcmp(item.key, htab->table[idx].entry.key) == 0) {
		/* Overwrite existing value? */
		if ((action == ENTER) && (item.data != NULL)) {

			free(htab->table[idx].entry.data);
			htab->table[idx].entry.data = strdup(item.data);
			if (!htab->table[idx].entry.data) {
				__set_errno(ENOMEM);
				*retval = NULL;
				return 0;
			}
		}
		/* return found entry */
		*retval = &htab->table[idx].entry;
		return idx;
	}
	/* keep searching */
	return -1;
}

int hsearch_r(ENTRY item, ACTION action, ENTRY ** retval,
	      struct hsearch_data *htab, int flag)
{
	unsigned int hval;
	unsigned int count;
	unsigned int len = strlen(item.key);
	unsigned int idx;
	unsigned int first_deleted = 0;
	int ret;

	/* Compute an value for the given string. Perhaps use a better method. */
	hval = len;
	count = len;
	while (count-- > 0) {
		hval <<= 4;
		hval += item.key[count];
	}

	/*
	 * First hash function:
	 * simply take the modul but prevent zero.
	 */
	hval %= htab->size;
	if (hval == 0)
		++hval;

	/* The first index tried. */
	idx = hval;

	if (htab->table[idx].used) {
		/*
		 * Further action might be required according to the
		 * action value.
		 */
		unsigned hval2;

		if (htab->table[idx].used == -1
		    && !first_deleted)
			first_deleted = idx;

		ret = _compare_and_overwrite_entry(item, action, retval, htab,
			flag, hval, idx);
		if (ret != -1)
			return ret;

		/*
		 * Second hash function:
		 * as suggested in [Knuth]
		 */
		hval2 = 1 + hval % (htab->size - 2);

		do {
			/*
			 * Because SIZE is prime this guarantees to
			 * step through all available indices.
			 */
			if (idx <= hval2)
				idx = htab->size + idx - hval2;
			else
				idx -= hval2;

			/*
			 * If we visited all entries leave the loop
			 * unsuccessfully.
			 */
			if (idx == hval)
				break;

			/* If entry is found use it. */
			ret = _compare_and_overwrite_entry(item, action, retval,
				htab, flag, hval, idx);
			if (ret != -1)
				return ret;
		}
		while (htab->table[idx].used);
	}

	/* An empty bucket has been found. */
	if (action == ENTER) {
		/*
		 * If table is full and another entry should be
		 * entered return with error.
		 */
		if (htab->filled == htab->size) {
			__set_errno(ENOMEM);
			*retval = NULL;
			return 0;
		}

		/*
		 * Create new entry;
		 * create copies of item.key and item.data
		 */
		if (first_deleted)
			idx = first_deleted;

		htab->table[idx].used = hval;
		htab->table[idx].entry.key = strdup(item.key);
		htab->table[idx].entry.data = strdup(item.data);
		if (!htab->table[idx].entry.key ||
		    !htab->table[idx].entry.data) {
			__set_errno(ENOMEM);
			*retval = NULL;
			return 0;
		}

		++htab->filled;

		/* Also look for flags */
		//env_flags_init(&htab->table[idx].entry);

		/* return new entry */
		*retval = &htab->table[idx].entry;
		return 1;
	}

	__set_errno(ESRCH);
	*retval = NULL;
	return 0;
}


/*
 * hdelete()
 */

/*
 * The standard implementation of hsearch(3) does not provide any way
 * to delete any entries from the hash table.  We extend the code to
 * do that.
 */

static void _hdelete(const char *key, struct hsearch_data *htab, ENTRY *ep,
	int idx)
{
	/* free used ENTRY */
	debug("hdelete: DELETING key \"%s\"\n", key);
	free((void *)ep->key);
	free(ep->data);
	ep->flags = 0;
	htab->table[idx].used = -1;

	--htab->filled;
}

int hdelete_r(const char *key, struct hsearch_data *htab, int flag)
{
	ENTRY e, *ep;
	int idx;

	debug("hdelete: DELETE key \"%s\"\n", key);

	e.key = (char *)key;

	idx = hsearch_r(e, FIND, &ep, htab, 0);
	if (idx == 0) {
		__set_errno(ESRCH);
		return 0;	/* not found */
	}

	_hdelete(key, htab, ep, idx);

	return 1;
}

/*
 * hexport()
 */

#ifndef CONFIG_SPL_BUILD
/*
 * Export the data stored in the hash table in linearized form.
 *
 * Entries are exported as "name=value" strings, separated by an
 * arbitrary (non-NUL, of course) separator character. This allows to
 * use this function both when formatting the U-Boot environment for
 * external storage (using '\0' as separator), but also when using it
 * for the "printenv" command to print all variables, simply by using
 * as '\n" as separator. This can also be used for new features like
 * exporting the environment data as text file, including the option
 * for later re-import.
 *
 * The entries in the result list will be sorted by ascending key
 * values.
 *
 * If the separator character is different from NUL, then any
 * separator characters and backslash characters in the values will
 * be escaped by a preceeding backslash in output. This is needed for
 * example to enable multi-line values, especially when the output
 * shall later be parsed (for example, for re-import).
 *
 * There are several options how the result buffer is handled:
 *
 * *resp  size
 * -----------
 *  NULL    0	A string of sufficient length will be allocated.
 *  NULL   >0	A string of the size given will be
 *		allocated. An error will be returned if the size is
 *		not sufficient.  Any unused bytes in the string will
 *		be '\0'-padded.
 * !NULL    0	The user-supplied buffer will be used. No length
 *		checking will be performed, i. e. it is assumed that
 *		the buffer size will always be big enough. DANGEROUS.
 * !NULL   >0	The user-supplied buffer will be used. An error will
 *		be returned if the size is not sufficient.  Any unused
 *		bytes in the string will be '\0'-padded.
 */

static int cmpkey(const void *p1, const void *p2)
{
	ENTRY *e1 = *(ENTRY **) p1;
	ENTRY *e2 = *(ENTRY **) p2;

	return (strcmp(e1->key, e2->key));
}

static int match_string(int flag, const char *str, const char *pat, void *priv)
{
	switch (flag & H_MATCH_METHOD) {
	case H_MATCH_IDENT:
		if (strcmp(str, pat) == 0)
			return 1;
		break;
	case H_MATCH_SUBSTR:
		if (strstr(str, pat))
			return 1;
		break;
#ifdef CONFIG_REGEX
	case H_MATCH_REGEX:
		{
			struct slre *slrep = (struct slre *)priv;
			struct cap caps[slrep->num_caps + 2];

			if (slre_match(slrep, str, strlen(str), caps))
				return 1;
		}
		break;
#endif
	default:
		printf("## ERROR: unsupported match method: 0x%02x\n",
			flag & H_MATCH_METHOD);
		break;
	}
	return 0;
}

static int match_entry(ENTRY *ep, int flag,
		 int argc, char * const argv[])
{
	int arg;
	void *priv = NULL;

	for (arg = 0; arg < argc; ++arg) {
#ifdef CONFIG_REGEX
		struct slre slre;

		if (slre_compile(&slre, argv[arg]) == 0) {
			printf("Error compiling regex: %s\n", slre.err_str);
			return 0;
		}

		priv = (void *)&slre;
#endif
		if (flag & H_MATCH_KEY) {
			if (match_string(flag, ep->key, argv[arg], priv))
				return 1;
		}
		if (flag & H_MATCH_DATA) {
			if (match_string(flag, ep->data, argv[arg], priv))
				return 1;
		}
	}
	return 0;
}

ssize_t hexport_r(struct hsearch_data *htab, const char sep, int flag,
		 char **resp, size_t size,
		 int argc, char * const argv[])
{
	ENTRY *list[htab->size];
	char *res, *p;
	size_t totlen;
	int i, n;

	/* Test for correct arguments.  */
	if ((resp == NULL) || (htab == NULL)) {
		__set_errno(EINVAL);
		return (-1);
	}

	debug("EXPORT  table = %p, htab.size = %d, htab.filled = %d, "
		"size = %zu\n", htab, htab->size, htab->filled, size);
	/*
	 * Pass 1:
	 * search used entries,
	 * save addresses and compute total length
	 */
	for (i = 1, n = 0, totlen = 0; i <= htab->size; ++i) {

		if (htab->table[i].used > 0) {
			ENTRY *ep = &htab->table[i].entry;
			int found = match_entry(ep, flag, argc, argv);

			if ((argc > 0) && (found == 0))
				continue;

			if ((flag & H_HIDE_DOT) && ep->key[0] == '.')
				continue;

			list[n++] = ep;

			totlen += strlen(ep->key) + 2;

			if (sep == '\0') {
				totlen += strlen(ep->data);
			} else {	/* check if escapes are needed */
				char *s = ep->data;

				while (*s) {
					++totlen;
					/* add room for needed escape chars */
					if ((*s == sep) || (*s == '\\'))
						++totlen;
					++s;
				}
			}
			totlen += 2;	/* for '=' and 'sep' char */
		}
	}

#ifdef DEBUG
	/* Pass 1a: print unsorted list */
	printf("Unsorted: n=%d\n", n);
	for (i = 0; i < n; ++i) {
		printf("\t%3d: %p ==> %-10s => %s\n",
		       i, list[i], list[i]->key, list[i]->data);
	}
#endif

	/* Sort list by keys */
	qsort(list, n, sizeof(ENTRY *), cmpkey);

	/* Check if the user supplied buffer size is sufficient */
	if (size) {
		if (size < totlen + 1) {	/* provided buffer too small */
			printf("Env export buffer too small: %zu, "
				"but need %zu\n", size, totlen + 1);
			__set_errno(ENOMEM);
			return (-1);
		}
	} else {
		size = totlen + 1;
	}

	/* Check if the user provided a buffer */
	if (*resp) {
		/* yes; clear it */
		res = *resp;
		memset(res, '\0', size);
	} else {
		/* no, allocate and clear one */
		*resp = res = calloc(1, size);
		if (res == NULL) {
			__set_errno(ENOMEM);
			return (-1);
		}
	}
	/*
	 * Pass 2:
	 * export sorted list of result data
	 */
	for (i = 0, p = res; i < n; ++i) {
		const char *s;

		s = list[i]->key;
		while (*s)
			*p++ = *s++;
		*p++ = '=';

		s = list[i]->data;

		while (*s) {
			if ((*s == sep) || (*s == '\\'))
				*p++ = '\\';	/* escape */
			*p++ = *s++;
		}
		*p++ = sep;
	}
	*p = '\0';		/* terminate result */

	return size;
}
#endif


/*
 * himport()
 */

/*
 * Check whether variable 'name' is amongst vars[],
 * and remove all instances by setting the pointer to NULL
 */
static int drop_var_from_set(const char *name, int nvars, char * vars[])
{
	int i = 0;
	int res = 0;

	/* No variables specified means process all of them */
	if (nvars == 0)
		return 1;

	for (i = 0; i < nvars; i++) {
		if (vars[i] == NULL)
			continue;
		/* If we found it, delete all of them */
		if (!strcmp(name, vars[i])) {
			vars[i] = NULL;
			res = 1;
		}
	}
	if (!res)
		debug("Skipping non-listed variable %s\n", name);

	return res;
}

/*
 * Import linearized data into hash table.
 *
 * This is the inverse function to hexport(): it takes a linear list
 * of "name=value" pairs and creates hash table entries from it.
 *
 * Entries without "value", i. e. consisting of only "name" or
 * "name=", will cause this entry to be deleted from the hash table.
 *
 * The "flag" argument can be used to control the behaviour: when the
 * H_NOCLEAR bit is set, then an existing hash table will kept, i. e.
 * new data will be added to an existing hash table; otherwise, old
 * data will be discarded and a new hash table will be created.
 *
 * The separator character for the "name=value" pairs can be selected,
 * so we both support importing from externally stored environment
 * data (separated by NUL characters) and from plain text files
 * (entries separated by newline characters).
 *
 * To allow for nicely formatted text input, leading white space
 * (sequences of SPACE and TAB chars) is ignored, and entries starting
 * (after removal of any leading white space) with a '#' character are
 * considered comments and ignored.
 *
 * [NOTE: this means that a variable name cannot start with a '#'
 * character.]
 *
 * When using a non-NUL separator character, backslash is used as
 * escape character in the value part, allowing for example for
 * multi-line values.
 *
 * In theory, arbitrary separator characters can be used, but only
 * '\0' and '\n' have really been tested.
 */

int himport_r(struct hsearch_data *htab,
		const char *env, size_t size, const char sep, int flag,
		int crlf_is_lf, int nvars, char * const vars[])
{
	char *data, *sp, *dp, *name, *value;
	char *localvars[nvars];
	int i;

	/* Test for correct arguments.  */
	if (htab == NULL) {
		__set_errno(EINVAL);
		return 0;
	}

	/* we allocate new space to make sure we can write to the array */
	if ((data = malloc(size)) == NULL) {
		debug("himport_r: can't malloc %zu bytes\n", size);
		__set_errno(ENOMEM);
		return 0;
	}
	memcpy(data, env, size);
	dp = data;

	/* make a local copy of the list of variables */
	if (nvars)
		memcpy(localvars, vars, sizeof(vars[0]) * nvars);

	if ((flag & H_NOCLEAR) == 0) {
		/* Destroy old hash table if one exists */
		debug("Destroy Hash Table: %p table = %p\n", htab,
		       htab->table);
		if (htab->table)
			hdestroy_r(htab);
	}

	/*
	 * Create new hash table (if needed).  The computation of the hash
	 * table size is based on heuristics: in a sample of some 70+
	 * existing systems we found an average size of 39+ bytes per entry
	 * in the environment (for the whole key=value pair). Assuming a
	 * size of 8 per entry (= safety factor of ~5) should provide enough
	 * safety margin for any existing environment definitions and still
	 * allow for more than enough dynamic additions. Note that the
	 * "size" argument is supposed to give the maximum environment size
	 * (CONFIG_ENV_SIZE).  This heuristics will result in
	 * unreasonably large numbers (and thus memory footprint) for
	 * big flash environments (>8,000 entries for 64 KB
	 * envrionment size), so we clip it to a reasonable value.
	 * On the other hand we need to add some more entries for free
	 * space when importing very small buffers. Both boundaries can
	 * be overwritten in the board config file if needed.
	 */

	if (!htab->table) {
		int nent = CONFIG_ENV_MIN_ENTRIES + size / 8;

		if (nent > CONFIG_ENV_MAX_ENTRIES)
			nent = CONFIG_ENV_MAX_ENTRIES;

		debug("Create Hash Table: N=%d\n", nent);

		if (hcreate_r(nent, htab) == 0) {
			free(data);
			return 0;
		}
	}

	if(!size)
		return 1;		/* everything OK */
	if(crlf_is_lf) {
		/* Remove Carriage Returns in front of Line Feeds */
		unsigned ignored_crs = 0;
		for(;dp < data + size && *dp; ++dp) {
			if(*dp == '\r' &&
			   dp < data + size - 1 && *(dp+1) == '\n')
				++ignored_crs;
			else
				*(dp-ignored_crs) = *dp;
		}
		size -= ignored_crs;
		dp = data;
	}
	/* Parse environment; allow for '\0' and 'sep' as separators */
	do {
		ENTRY e, *rv;

		/* skip leading white space */
		while (isblank(*dp))
			++dp;

		/* skip comment lines */
		if (*dp == '#') {
			while (*dp && (*dp != sep))
				++dp;
			++dp;
			continue;
		}

		/* parse name */
		for (name = dp; *dp != '=' && *dp && *dp != sep; ++dp)
			;

		/* deal with "name" and "name=" entries (delete var) */
		if (*dp == '\0' || *(dp + 1) == '\0' ||
		    *dp == sep || *(dp + 1) == sep) {
			if (*dp == '=')
				*dp++ = '\0';
			*dp++ = '\0';	/* terminate name */

			debug("DELETE CANDIDATE: \"%s\"\n", name);
			if (!drop_var_from_set(name, nvars, localvars))
				continue;

			if (hdelete_r(name, htab, flag) == 0)
				debug("DELETE ERROR ##############################\n");

			continue;
		}
		*dp++ = '\0';	/* terminate name */

		/* parse value; deal with escapes */
		for (value = sp = dp; *dp && (*dp != sep); ++dp) {
			if ((*dp == '\\') && *(dp + 1))
				++dp;
			*sp++ = *dp;
		}
		*sp++ = '\0';	/* terminate value */
		++dp;

		if (*name == 0) {
			debug("INSERT: unable to use an empty key\n");
			__set_errno(EINVAL);
			return 0;
		}

		/* Skip variables which are not supposed to be processed */
		if (!drop_var_from_set(name, nvars, localvars))
			continue;

		/* enter into hash table */
		e.key = name;
		e.data = value;

		hsearch_r(e, ENTER, &rv, htab, flag);
		if (rv == NULL)
			printf("himport_r: can't insert \"%s=%s\" into hash table\n",
				name, value);

		debug("INSERT: table %p, filled %d/%d rv %p ==> name=\"%s\" value=\"%s\"\n",
			htab, htab->filled, htab->size,
			rv, name, value);
	} while ((dp < data + size) && *dp);	/* size check needed for text */
						/* without '\0' termination */
	debug("INSERT: free(data = %p)\n", data);
	free(data);

	/* process variables which were not considered */
	for (i = 0; i < nvars; i++) {
		if (localvars[i] == NULL)
			continue;
		/*
		 * All variables which were not deleted from the variable list
		 * were not present in the imported env
		 * This could mean two things:
		 * a) if the variable was present in current env, we delete it
		 * b) if the variable was not present in current env, we notify
		 *    it might be a typo
		 */
		if (hdelete_r(localvars[i], htab, flag) == 0)
			printf("WARNING: '%s' neither in running nor in imported env!\n", localvars[i]);
		else
			printf("WARNING: '%s' not in imported env, deleting it!\n", localvars[i]);
	}

	debug("INSERT: done\n");
	return 1;		/* everything OK */
}

/*
 * h_detect_r()
 */

/*
 * Check weather default environment variables saved in emmc.
 * If not, add default environment variables in emmc.
 */

int h_detect_r(struct hsearch_data *htab,
		const char *env, size_t size, const char sep, int flag,
		int crlf_is_lf, int nvars, char * const vars[])
{
	char *data, *sp, *dp, *name, *value;
	char *localvars[nvars];
	int i, update_var = 1;

	/* Test for correct arguments.  */
	if (htab == NULL) {
		__set_errno(EINVAL);
		return 0;
	}

	/* we allocate new space to make sure we can write to the array */
	if ((data = malloc(size)) == NULL) {
		debug("himport_r: can't malloc %zu bytes\n", size);
		__set_errno(ENOMEM);
		return 0;
	}
	memcpy(data, env, size);
	dp = data;

	/* make a local copy of the list of variables */
	if (nvars)
		memcpy(localvars, vars, sizeof(vars[0]) * nvars);
	

	if(!size)
		return 1;		/* everything OK */
	if(crlf_is_lf) {
		/* Remove Carriage Returns in front of Line Feeds */
		unsigned ignored_crs = 0;
		for(;dp < data + size && *dp; ++dp) {
			if(*dp == '\r' &&
			   dp < data + size - 1 && *(dp+1) == '\n')
				++ignored_crs;
			else
				*(dp-ignored_crs) = *dp;
		}
		size -= ignored_crs;
		dp = data;
	}
	/* Parse environment; allow for '\0' and 'sep' as separators */
	do {
		ENTRY e, *rv;

		/* skip leading white space */
		while (isblank(*dp))
			++dp;

		/* skip comment lines */
		if (*dp == '#') {
			while (*dp && (*dp != sep))
				++dp;
			++dp;
			continue;
		}

		/* parse name */
		for (name = dp; *dp != '=' && *dp && *dp != sep; ++dp)
			;

		/* deal with "name" and "name=" entries (delete var) */
		if (*dp == '\0' || *(dp + 1) == '\0' ||
		    *dp == sep || *(dp + 1) == sep) {
			if (*dp == '=')
				*dp++ = '\0';
			*dp++ = '\0';	/* terminate name */

			debug("DELETE CANDIDATE: \"%s\"\n", name);
			if (!drop_var_from_set(name, nvars, localvars))
				continue;

			if (hdelete_r(name, htab, flag) == 0)
				debug("DELETE ERROR ##############################\n");

			continue;
		}
		*dp++ = '\0';	/* terminate name */

		/* parse value; deal with escapes */
		for (value = sp = dp; *dp && (*dp != sep); ++dp) {
			if ((*dp == '\\') && *(dp + 1))
				++dp;
			*sp++ = *dp;
		}
		*sp++ = '\0';	/* terminate value */
		++dp;

		if (*name == 0) {
			debug("INSERT: unable to use an empty key\n");
			__set_errno(EINVAL);
			return 0;
		}

		/* Skip variables which are not supposed to be processed */
		if (!drop_var_from_set(name, nvars, localvars))
			continue;

		/* enter into hash table */
		e.key = name;
		e.data = value;
		
		hsearch_r(e, FIND, &rv, htab, flag);
		if (rv != NULL)
			continue;
		
		update_var = 0; /*If add new default variable.*/
		
		hsearch_r(e, ENTER, &rv, htab, flag);
		if (rv == NULL)
			printf("himport_r: can't insert \"%s=%s\" into hash table\n",
				name, value);

		debug("INSERT: table %p, filled %d/%d rv %p ==> name=\"%s\" value=\"%s\"\n",
			htab, htab->filled, htab->size,
			rv, name, value);
	} while ((dp < data + size) && *dp);	/* size check needed for text */
						/* without '\0' termination */
	debug("INSERT: free(data = %p)\n", data);
	free(data);

	/* process variables which were not considered */
	for (i = 0; i < nvars; i++) {
		if (localvars[i] == NULL)
			continue;
		/*
		 * All variables which were not deleted from the variable list
		 * were not present in the imported env
		 * This could mean two things:
		 * a) if the variable was present in current env, we delete it
		 * b) if the variable was not present in current env, we notify
		 *    it might be a typo
		 */
		if (hdelete_r(localvars[i], htab, flag) == 0)
			printf("WARNING: '%s' neither in running nor in imported env!\n", localvars[i]);
		else
			printf("WARNING: '%s' not in imported env, deleting it!\n", localvars[i]);
	}

	debug("INSERT: done\n");
	return update_var;		/* everything OK */
}


/*
 * hwalk_r()
 */

/*
 * Walk all of the entries in the hash, calling the callback for each one.
 * this allows some generic operation to be performed on each element.
 */
int hwalk_r(struct hsearch_data *htab, int (*callback)(ENTRY *))
{
	int i;
	int retval;

	for (i = 1; i <= htab->size; ++i) {
		if (htab->table[i].used > 0) {
			retval = callback(&htab->table[i].entry);
			if (retval)
				return retval;
		}
	}

	return 0;
}
