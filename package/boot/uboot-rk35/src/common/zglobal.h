#ifndef ZMODEM_GLOBAL_H
#define ZMODEM_GLOBAL_H

/* zglobal.h - prototypes etcetera for lrzsz

  Copyright (C) until 1998 Chuck Forsberg (OMEN Technology Inc)
  Copyright (C) 1994 Matt Porter
  Copyright (C) 1996, 1997 Uwe Ohse

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.
*/

#include "config.h"
//#include <sys/types.h>

#ifdef __GNUC__
# define alloca __builtin_alloca
# define HAVE_ALLOCA 1
#else
# if defined HAVE_ALLOCA_H || defined _LIBC
#  include <alloca.h>
# else
#  ifdef _AIX
#pragma alloca
#  else
#   ifndef alloca
#    ifndef __GLIBC__
char *alloca ();
#    endif
#   endif
#  endif
# endif
#endif

#ifndef __P
#if defined (__GNUC__) || (defined (__STDC__) && __STDC__)
#define __P(args) args
#else
#define __P(args) ()
#endif  /* GCC.  */
#endif  /* Not __P.  */

#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#  include <sys/time.h>
#  include <time.h>
#  define INCLUDED_SYS_TIME
#else
#  ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#    define INCLUDED_SYS_TIME
#  else
#    include <time.h>
#  endif
#endif
#ifdef SYS_TIME_WITHOUT_SYS_SELECT
# ifdef INCLUDED_SYS_TIME
#  undef HAVE_SYS_SELECT_H
# endif
#endif


#ifdef HAVE_SYS_SELECT_H
#  include <sys/select.h>
#endif
#ifdef __BEOS__
 /* BeOS 4.0: sys/select.h is almost completely #ifdefd out */
#define  HAVE_SOCKET_H
#ifdef HAVE_SOCKET_H
#include <socket.h>
#endif
#endif

#if STDC_HEADERS
# include <linux/string.h>
#else
# ifdef HAVE_STRINGS_H
#   include <linux/strings.h>
# endif
# ifndef HAVE_STRCHR
#  define strchr index
#  define strrchr rindex
# endif
char *strchr (), *strrchr ();
# ifndef HAVE_MEMCPY
#  define memcpy(d, s, n) bcopy ((s), (d), (n))
#  define memmove(d, s, n) bcopy ((s), (d), (n))
# endif
#endif

//#include <sys/stat.h>

/* we need to decide whether readcheck is possible */
#ifdef HAVE_FCNTL_H
#  include <fcntl.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
#  include <sys/ioctl.h>
#endif
#ifdef HAVE_RDCHK
#  define READCHECK
#else
#  ifdef FIONREAD
#    define READCHECK_FIONREAD
#    define READCHECK
#  else
#    ifdef F_GETFL
#      define READCHECK
#      define READCHECK_READS
#      define READCHECK_GETFL
#    endif
#  endif
#endif

/* used to use #elif, but native braindead hpux 9.00 c compiler didn't 
 * understand it */
#ifdef HAVE_TERMIOS_H
/* get rid of warnings on SCO ODT 3.2 */
struct termios;
# include <termios.h>
# define USE_TERMIOS
#else
# if defined(HAVE_SYS_TERMIOS_H)
#  include <sys/termios.h>
#  define USE_TERMIOS
# else
#  if defined(HAVE_TERMIO_H)
#   include <termio.h>
#   define USE_TERMIO
#  else
#   if defined(HAVE_SYS_TERMIO_H)
#    include <sys/termio.h>
#    define USE_TERMIO
#   else
#    if defined(HAVE_SGTTY_H)
#     include <sgtty.h>
#     define USE_SGTTY
#     ifdef LLITOUT
       extern long Locmode;		/* Saved "local mode" for 4.x BSD "new driver" */
       extern long Locbit;	/* Bit SUPPOSED to disable output translations */
#     endif
#    else
#    // error neither termio.h nor sgtty.h found. Cannot continue.
#    endif
#   endif
#  endif
# endif
#endif

#ifdef USE_SGTTY
#  ifdef TIOCSBRK
#    define CANBREAK
#  endif
#endif
#ifdef USE_TERMIO
#  define CANBREAK
#endif



/* Take care of NLS matters.  */
#if HAVE_LOCALE_H
# include <locale.h>
#endif
#if !HAVE_SETLOCALE
# define setlocale(Category, Locale) /* empty */
#endif

#if ENABLE_NLS
# include <libintl.h>
# define _(Text) gettext (Text)
#else
# define bindtextdomain(Domain, Directory) /* empty */
# define textdomain(Domain) /* empty */
# define _(Text) Text
#endif

#ifndef ENABLE_SYSLOG
#  undef HAVE_SYSLOG
#else
#  ifdef HAVE_SYSLOG_H
#    include <syslog.h>
#  else
#    if defined(HAVE_SYS_SYSLOG_H)
#      include <sys/syslog.h>
#    else
#      undef HAVE_SYSLOG
#    endif
#  endif
#endif
#ifndef ENABLE_SYSLOG
#  define openlog(name,pid,facility) /* void it */
#  define setlogmask(x) /* void it */
#else
extern int enable_syslog;
#endif

#if defined HAVE_UNISTD_H
# include <unistd.h>
#endif
/* The following is from pathmax.h.  */
/* Non-POSIX BSD systems might have gcc's limits.h, which doesn't define
   PATH_MAX but might cause redefinition warnings when sys/param.h is
   later included (as on MORE/BSD 4.3).  */
#if defined(_POSIX_VERSION) || (defined(HAVE_LIMITS_H) && !defined(__GNUC__))
# include <limits.h>
#endif

#ifndef _POSIX_PATH_MAX
# define _POSIX_PATH_MAX 255
#endif

#if !defined(PATH_MAX) && defined(_PC_PATH_MAX)
# define PATH_MAX 255
#endif

/* Don't include sys/param.h if it already has been.  */
#if defined(HAVE_SYS_PARAM_H) && !defined(PATH_MAX) && !defined(MAXPATHLEN)
# include <sys/param.h>
#endif

#if !defined(PATH_MAX) && defined(MAXPATHLEN)
# define PATH_MAX MAXPATHLEN
#endif

#if !defined(LONG_MAX) && defined(HAVE_LIMITS_H)
# include <limits.h>
#endif

#ifndef PATH_MAX
# define PATH_MAX _POSIX_PATH_MAX
#endif

#ifdef __GNUC__

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 5)
# define LRZSZ_ATTRIB_SECTION(x) __attribute__((section(#x)))
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 4)
# define LRZSZ_ATTRIB_CONST  __attribute__((__const__))
#endif

    /* gcc.info sagt, noreturn w?re ab 2.5 verf?gbar. HPUX-gcc 2.5.8
     * kann es noch nicht - what's this?
     */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 5)
# define LRZSZ_ATTRIB_NORET  __attribute__((__noreturn__))
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 5)
# define LRZSZ_ATTRIB_PRINTF(formatnr,firstargnr)  \
    __attribute__((__format__ (printf,formatnr,firstargnr)))
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ > 6)
#define LRZSZ_ATTRIB_UNUSED __attribute__((__unused__))
#endif

#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
# define LRZSZ_ATTRIB_REGPARM(n)  \
    __attribute__((__regparm__ (n)))
#endif
#endif /* __GNUC__ */
#ifndef LRZSZ_ATTRIB_REGPARM
#define LRZSZ_ATTRIB_REGPARM(n)
#endif
#ifndef LRZSZ_ATTRIB_UNUSED
#define LRZSZ_ATTRIB_UNUSED
#endif
#ifndef LRZSZ_ATTRIB_NORET
#define LRZSZ_ATTRIB_NORET
#endif
#ifndef LRZSZ_ATTRIB_CONST
#define LRZSZ_ATTRIB_CONST
#endif
#ifndef LRZSZ_ATTRIB_PRINTF
#define LRZSZ_ATTRIB_PRINTF(x,y)
#endif
#ifndef LRZSZ_ATTRIB_SECTION
#define LRZSZ_ATTRIB_SECTION(n)
#endif
#undef LRZSZ_ATTRIB_SECTION
#define LRZSZ_ATTRIB_SECTION(x)
#undef LRZSZ_ATTRIB_REGPARM
#define LRZSZ_ATTRIB_REGPARM(x)


#define OK 0
#define FALSE 0
#define TRUE 1
#define ERROR (-1)

/* Ward Christensen / CP/M parameters - Don't change these! */
#define ENQ 005
#define CAN ('X'&037)
#define XOFF ('s'&037)
#define XON ('q'&037)
#define SOH 1
#define STX 2
#define EOT 4
#define ACK 6
#define NAK 025
#define CPMEOF 032
#define WANTCRC 0103    /* send C not NAK to get crc not checksum */
#define WANTG 0107  /* Send G not NAK to get nonstop batch xmsn */
#define TIMEOUT (-2)
#define RCDO (-3)
#define WCEOT (-10)

#define RETRYMAX 10

#define UNIXFILE 0xF000  /* The S_IFMT file mask bit for stat */

#define DEFBYTL 2000000000L	/* default rx file size */

enum zm_type_enum {
	ZM_XMODEM,
	ZM_YMODEM,
	ZM_ZMODEM
};

struct zm_fileinfo {
	char *fname;
	time_t modtime;
	mode_t mode;
	size_t bytes_total;
	size_t bytes_sent;
	size_t bytes_received;
	size_t bytes_skipped; /* crash recovery */
	int    eof_seen;
};

#define R_BYTESLEFT(x) ((x)->bytes_total-(x)->bytes_received)

extern enum zm_type_enum protocol;

extern const char *program_name;        /* the name by which we were called */
extern int Verbose;
extern int errors;
extern int no_timeout;
extern int Zctlesc;    /* Encode control characters */
extern int under_rsh;

RETSIGTYPE bibi __P ((int n));

//#define sendline(c) putchar((c) & 0377)
//#define xsendline(c) putchar(c)

/* zreadline.c */
extern char *readline_ptr; /* pointer for removing chars from linbuf */
extern int readline_left; /* number of buffered chars left to read */
#define READLINE_PF(timeout) \
    (--readline_left >= 0? (*readline_ptr++ & 0377) : readline_internal(timeout))

int readline_internal __P ((unsigned int timeout));
void readline_purge __P ((void));
void readline_setup __P ((int fd, size_t readnum, 
	size_t buffer_size)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);


/* rbsb.c */
extern int Fromcu;
extern int Twostop;
#ifdef READCHECK_READS
extern unsigned char checked;
#endif
extern int iofd;
extern unsigned Baudrate;

void zperr __P ((const char *fmt, ...));
void zpfatal __P ((const char *fmt, ...));
void vfile __P ((const char *format, ...));
#define vchar(x) putc(x)
#define vstring(x) fputs(stderr, x)

#ifdef __GNUC__
#if __GNUC__ > 1
#define vstringf(format,args...) fprintf(stderr,format, ##args)
#endif
#endif
#ifndef vstringf
void vstringf __P ((const char *format, ...));
#endif
#define VPRINTF(level,format_args) do {if ((Verbose)>=(level)) \
	vstringf format_args ; } while(0)

/* rbsb.c */
int from_cu __P ((void)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
int rdchk __P ((int fd));
int io_mode __P ((int fd, int n)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
void sendbrk __P ((int fd));
//#define flushmo() fflush(stdout)
void purgeline __P ((int fd));
void canit __P ((int fd));


/* crctab.c */
extern unsigned short crctab[256];
#define updcrc(cp, crc) ( crctab[((crc >> 8) & 255)] ^ (crc << 8) ^ cp)
extern long cr3tab[];
#define UPDC32(b, c) (cr3tab[((int)c ^ b) & 0xff] ^ ((c >> 8) & 0x00FFFFFF))

/* zm.c */
#include "zmodem.h"
extern unsigned int Rxtimeout;        /* Tenths of seconds to wait for something */
extern int bytes_per_error;  /* generate one error around every x bytes */

/* Globals used by ZMODEM functions */
extern int Rxframeind;     /* ZBIN ZBIN32, or ZHEX type of frame received */
extern int Rxtype;     /* Type of header received */
extern int Zrwindow;       /* RX window size (controls garbage count) */
/* extern int Rxcount; */       /* Count of data bytes received */
extern char Rxhdr[4];      /* Received header */
extern char Txhdr[4];      /* Transmitted header */
extern long Txpos;     /* Transmitted file position */
extern int Txfcs32;        /* TURE means send binary frames with 32 bit FCS */
extern int Crc32t;     /* Display flag indicating 32 bit CRC being sent */
extern int Crc32;      /* Display flag indicating 32 bit CRC being received */
extern int Znulls;     /* Number of nulls to send at beginning of ZDATA hdr */
extern char Attn[ZATTNLEN+1];  /* Attention string rx sends to tx on err */

extern void zsendline __P ((int c));
extern void zsendline_init __P ((void)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
void zsbhdr __P ((int type, char *hdr));
void zshhdr __P ((int type, char *hdr));
void zsdata __P ((const char *buf, size_t length, int frameend));
void zsda32 __P ((const char *buf, size_t length, int frameend));
int zrdata __P ((char *buf, int length, size_t *received));
int zgethdr __P ((char *hdr, int eflag, size_t *));
void stohdr __P ((size_t pos)) LRZSZ_ATTRIB_REGPARM(1);
long rclhdr __P ((char *hdr)) LRZSZ_ATTRIB_REGPARM(1);

int tcp_server __P ((char *buf)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
int tcp_connect __P ((char *buf)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
int tcp_accept __P ((int d)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);


const char * protname __P ((void)) LRZSZ_ATTRIB_SECTION(lrzsz_rare);
void lsyslog __P ((int, const char *,...));
#define xil_printf printf




#endif
