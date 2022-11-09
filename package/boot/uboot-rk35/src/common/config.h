/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if on AIX 3.
   System headers sometimes define this.
   We just want to avoid a redefinition error message.  */
#ifndef _ALL_SOURCE
/* #undef _ALL_SOURCE */
#endif

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

/* Define if you have alloca, as a function or macro.  */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
#define HAVE_ALLOCA_H 1

/* Define if you have a working `mmap' system call.  */
/* #undef HAVE_MMAP */

/* Define if your struct stat has st_rdev.  */
#define HAVE_ST_RDEV 1

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* Define if on MINIX.  */
/* #undef _MINIX */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef mode_t */

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef off_t */

/* Define if the system does not provide POSIX.1 features except
   with this defined.  */
/* #undef _POSIX_1_SOURCE */

/* Define if you need to in order for stat and other things to work.  */
/* #undef _POSIX_SOURCE */

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define if the setvbuf function takes the buffering type as its second
   argument and the buffer pointer as the third, as on System V
   before release 3.  */
/* #undef SETVBUF_REVERSED */

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if you can safely include both <sys/time.h> and <time.h>.  */
//#define TIME_WITH_SYS_TIME 1

/* Define if your <sys/time.h> declares struct tm.  */
/* #undef TM_IN_SYS_TIME */

/* define this if you have a reliable ftime function */
//#define HAVE_FTIME 1

/* define this if you have the timezone variable */
//#define HAVE_TIMEZONE_VAR 1

/* Define to 1 if NLS is requested.  */
//#define ENABLE_NLS 1

/* Define as 1 if you have catgets and don't want to use GNU gettext.  */
/* #undef HAVE_CATGETS */

/* Define as 1 if you have gettext and don't want to use GNU gettext.  */
#define HAVE_GETTEXT 1

/* Define if your locale.h file contains LC_MESSAGES.  */
#define HAVE_LC_MESSAGES 1

/* Define to the name of the distribution.  */
#define PACKAGE "lrzsz"

/* The concatenation of the strings PACKAGE, "-", and VERSION.  */
#define PACKAGE_VERSION "lrzsz-0.12.20"

/* Define to the version of the distribution.  */
#define VERSION "0.12.20"

/* Define to 1 if you have the stpcpy function.  */
#define HAVE_STPCPY 1

/* Define to 1 if your utime() takes struct utimbuf as second argument */
//#define HAVE_STRUCT_UTIMBUF 1

/* Define to 1 if ANSI function prototypes are usable.  */
#define PROTOTYPES 1

/* Define to LOG_xxx (a syslog facility) if syslog() shall be used */
//#define ENABLE_SYSLOG LOG_UUCP

/* Define to 1 if syslogging shall be forced */
/* #undef ENABLE_SYSLOG_FORCE */

/* Define to 1 if syslogging shall be default */
//#define ENABLE_SYSLOG_DEFAULT 1

/* Define to 1 if lrz shall create directories if needed */
//#define ENABLE_MKDIR 1

/* Define to public writable directory if you want this. Leave out the "'s */
/* #undef PUBDIR */

/* Define to 1 if you want support for the timesync protocol */
//#define ENABLE_TIMESYNC 1

/* define to 1. we have a replacement function for it. */
#define HAVE_STRERROR 1

/* define to 1 if you want strict ANSI prototypes. will remove some 
   extern x(); declarations. */
/* #undef STRICT_PROTOTYPES */

/* where the localedata hides */
/* #undef LOCALEDIR */

/* do your system libraries declare errno? */
#define HAVE_ERRNO_DECLARATION 1

/* define to type of speed_t (long?) */
/* #undef speed_t */

/* define this if you headers conflict */
/* #undef SYS_TIME_WITHOUT_SYS_SELECT */

/* Define if you have the __argz_count function.  */
#define HAVE___ARGZ_COUNT 1

/* Define if you have the __argz_next function.  */
#define HAVE___ARGZ_NEXT 1

/* Define if you have the __argz_stringify function.  */
#define HAVE___ARGZ_STRINGIFY 1

/* Define if you have the dcgettext function.  */
#define HAVE_DCGETTEXT 1

/* Define if you have the getcwd function.  */
#define HAVE_GETCWD 1

/* Define if you have the getpagesize function.  */
#define HAVE_GETPAGESIZE 1

/* Define if you have the gettimeofday function.  */
//#define HAVE_GETTIMEOFDAY 1

/* Define if you have the memcpy function.  */
//#define HAVE_MEMCPY 1

/* Define if you have the mkdir function.  */
#define HAVE_MKDIR 1

/* Define if you have the mktime function.  */
#define HAVE_MKTIME 1

/* Define if you have the munmap function.  */
#define HAVE_MUNMAP 1

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the rdchk function.  */
/* #undef HAVE_RDCHK */

/* Define if you have the select function.  */
//#define HAVE_SELECT 1

/* Define if you have the setenv function.  */
#define HAVE_SETENV 1

/* Define if you have the setlocale function.  */
#define HAVE_SETLOCALE 1

/* Define if you have the settimeofday function.  */
//#define HAVE_SETTIMEOFDAY 1

/* Define if you have the siginterrupt function.  */
//#define HAVE_SIGINTERRUPT 1

/* Define if you have the stpcpy function.  */
#define HAVE_STPCPY 1

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strchr function.  */
#define HAVE_STRCHR 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strftime function.  */
#define HAVE_STRFTIME 1

/* Define if you have the strpbrk function.  */
#define HAVE_STRPBRK 1

/* Define if you have the strstr function.  */
#define HAVE_STRSTR 1

/* Define if you have the strtol function.  */
#define HAVE_STRTOL 1

/* Define if you have the strtoul function.  */
#define HAVE_STRTOUL 1

/* Define if you have the syslog function.  */
//#define HAVE_SYSLOG 1

/* Define if you have the times function.  */
#define HAVE_TIMES 1

/* Define if you have the utime function.  */
//#define HAVE_UTIME 1

/* Define if you have the vasprintf function.  */
#define HAVE_VASPRINTF 1

/* Define if you have the vprintf function.  */
#define HAVE_VPRINTF 1

/* Define if you have the <argz.h> header file.  */
#define HAVE_ARGZ_H 1

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <fcntl.h> header file.  */
//#define HAVE_FCNTL_H 1

/* Define if you have the <limits.h> header file.  */
//#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file.  */
//#define HAVE_LOCALE_H 1

/* Define if you have the <malloc.h> header file.  */
#define HAVE_MALLOC_H 1

/* Define if you have the <nl_types.h> header file.  */
#define HAVE_NL_TYPES_H 1

/* Define if you have the <sgtty.h> header file.  */
//#define HAVE_SGTTY_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <strings.h> header file.  */
#define HAVE_STRINGS_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
//#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/mman.h> header file.  */
#define HAVE_SYS_MMAN_H 1

/* Define if you have the <sys/param.h> header file.  */
//#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/select.h> header file.  */
//#define HAVE_SYS_SELECT_H 1

/* Define if you have the <sys/syslog.h> header file.  */
#define HAVE_SYS_SYSLOG_H 1

/* Define if you have the <sys/termio.h> header file.  */
/* #undef HAVE_SYS_TERMIO_H */

/* Define if you have the <sys/termios.h> header file.  */
//#define HAVE_SYS_TERMIOS_H 1

/* Define if you have the <sys/time.h> header file.  */
//#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/times.h> header file.  */
//#define HAVE_SYS_TIMES_H 1

/* Define if you have the <syslog.h> header file.  */
//#define HAVE_SYSLOG_H 1

/* Define if you have the <termio.h> header file.  */
//#define HAVE_TERMIO_H 1

/* Define if you have the <termios.h> header file.  */
//#define HAVE_TERMIOS_H 1

/* Define if you have the <unistd.h> header file.  */
//#define HAVE_UNISTD_H 1

/* Define if you have the <utime.h> header file.  */
//#define HAVE_UTIME_H 1

/* Define if you have the <values.h> header file.  */
#define HAVE_VALUES_H 1

/* Define if you have the be library (-lbe).  */
/* #undef HAVE_LIBBE */

/* Define if you have the i library (-li).  */
/* #undef HAVE_LIBI */

/* Define if you have the nsl library (-lnsl).  */
#define HAVE_LIBNSL 1

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */
