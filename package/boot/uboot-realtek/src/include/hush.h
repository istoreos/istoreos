/*
 * (C) Copyright 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _HUSH_H_
#define _HUSH_H_

#define FLAG_EXIT_FROM_LOOP 1
#define FLAG_PARSE_SEMICOLON (1 << 1)	  /* symbol ';' is special for parser */
#define FLAG_REPARSING       (1 << 2)	  /* >=2nd pass */

extern int u_boot_hush_start(void);
extern int parse_string_outer(const char *, int);
extern int parse_file_outer(void);

int set_local_var(const char *s, int flg_export);
void unset_local_var(const char *name);
char *get_local_var(const char *s);

#if defined(CONFIG_HUSH_INIT_VAR)
extern int hush_init_var (void);
#endif
#endif
