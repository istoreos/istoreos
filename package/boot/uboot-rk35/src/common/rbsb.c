/*
  rbsb.c - terminal handling stuff for lrzsz
  Copyright (C) until 1988 Chuck Forsberg (Omen Technology INC)
  Copyright (C) 1994 Matt Porter, Michael D. Black
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

  originally written by Chuck Forsberg
*/

/*
 *  Rev 05-05-1988
 *  ============== (not quite, but originated there :-). -- uwe 
 */
#include "zglobal.h"

#include <stdio.h>
#include <errno.h>

#ifndef HAVE_ERRNO_DECLARATION
extern int errno;
#endif

#ifdef USE_SGTTY
#  ifdef LLITOUT
long Locmode;		/* Saved "local mode" for 4.x BSD "new driver" */
long Locbit = LLITOUT;	/* Bit SUPPOSED to disable output translations */
#  endif
#endif

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#ifdef MAJOR_IN_MKDEV
#include <sys/mkdev.h>
#else
# ifdef MAJOR_IN_SYSMACROS
# include <sys/sysmacros.h>
# endif
#endif
#ifndef HOWMANY
#ifdef NFGVMIN
#define HOWMANY MAX_BLOCK
#else
#define HOWMANY 255
#endif
#endif


#if defined(HOWMANY) && HOWMANY  > 255
#ifndef NFGVMIN
Howmany must be 255 or less
#endif
#endif

#define B110 110
#define B300 300
#define B600 600
#define B1200 1200
#define B2400 2400
#define B2400 2400
static struct {
	unsigned baudr;
	int  speedcode;
} speeds[] = {
	{110,	B110},
	{300,	B300},
	{600,	B600},
	{1200,	B1200},
#ifdef B19200
    {19200,  B19200},
#endif
#ifdef B38400
    {38400,  B38400},
#endif
#ifdef B57600
    {57600,  B57600},
#endif
#ifdef B115200
    {115200,  B115200},
#endif
#ifdef B230400
    {230400,  B230400},
#endif
#ifdef B460800
    {460800,  B460800},
#endif
#ifdef EXTA
	{19200,	EXTA},
#endif
#ifdef EXTB
	{38400,	EXTB},
#endif
	{0, 0}
};

extern int CYGACC_COMM_IF_GETC_TIMEOUT (char chan, char *c);
extern void CYGACC_COMM_IF_PUTC (char x, char y);
extern int CYGACC_COMM_IF_GETC_TIMEOUT (char chan, char *c);

unsigned
getspeed(int  code)
{
	int n;

	for (n=0; speeds[n].baudr; ++n)
		if (speeds[n].speedcode == code)
			return speeds[n].baudr;
	return 38400;	/* Assume fifo if ioctl failed */
}

/*
 * return 1 if stdout and stderr are different devices
 *  indicating this program operating with a modem on a
 *  different line
 */
int Fromcu;		/* Were called from cu or yam */
int 
from_cu(void)
{
#if 0
#ifdef HAVE_ST_RDEV
	struct stat a, b;
#if defined(makedev)
	dev_t help=makedev(0,0);
#else
	int help=0;
#endif

	/* in case fstat fails */
	a.st_rdev=b.st_rdev=a.st_dev=b.st_dev=help;

	fstat(1, &a); fstat(2, &b);

#if defined(major) && defined(minor)
	if (major(a.st_rdev) != major(b.st_rdev) 
		|| minor(a.st_rdev) != minor(b.st_rdev))
		Fromcu=1;
	else if (major(a.st_dev) != major(b.st_dev) 
		|| minor(a.st_dev) != minor(b.st_dev))
		Fromcu=1;
	else
		Fromcu=0;
#else
	Fromcu = (a.st_rdev != b.st_rdev) || (a.st_dev != b.st_dev);
#endif
#else
	Fromcu = 1; /* a bad guess .. */
#endif
	return Fromcu;
#endif
	return 0;
}



int Twostop;		/* Use two stop bits */


#ifdef READCHECK_FIONREAD
/*
 *  Return non 0 if something to read from io descriptor f
 */
int 
rdchk(int fd)
{
	static long lf;

	ioctl(fd, FIONREAD, &lf);
	return ((int) lf);
}
#endif

#ifdef READCHECK_GETFL
unsigned char checked = '\0' ;
/*
 * Nonblocking I/O is a bit different in System V, Release 2
 */
int 
rdchk(int fd)
{
	int lf, savestat;

	savestat = fcntl(fd, F_GETFL) ;
	if (savestat == -1)
		return 0;
#ifdef OVERLY_PARANOID
	if (-1==fcntl(fd, F_SETFL, savestat | O_NDELAY))
		return 0;
	lf = read(fd, &checked, 1) ;
	if (-1==fcntl(fd, F_SETFL, savestat)) {
#ifdef ENABLE_SYSLOG
		if (enable_syslog)
			lsyslog(LOG_CRIT,"F_SETFL failed in rdchk(): %s",	
				strerror(errno));
#endif
		zpfatal("rdchk: F_SETFL failed\n"); /* lose */
		/* there is really no way to recover. And we can't tell
		 * the other side what's going on if we can't write to
		 * fd, but we try.
		 */
		canit(fd);
		exit(1); 
	}
#else
	fcntl(fd, F_SETFL, savestat | O_NDELAY);
	lf = read(fd, &checked, 1) ;
	fcntl(fd, F_SETFL, savestat);
#endif
	return(lf == -1 && errno==EWOULDBLOCK ? 0 : lf) ;
}
#endif





#ifdef USE_TERMIOS
struct termios oldtty, tty;
#else
#  if defined(USE_TERMIO)
struct termio oldtty, tty;
#  else
//struct sgttyb oldtty, tty;
//struct tchars oldtch, tch;
#  endif
#endif


/*
 * mode(n)
 *  3: save old tty stat, set raw mode with flow control
 *  2: set XON/XOFF for sb/sz with ZMODEM or YMODEM-g
 *  1: save old tty stat, set raw mode 
 *  0: restore original tty mode
 */
int 
io_mode(int fd, int n)
{
#if 1
	__maybe_unused static int did0 = FALSE;

	vfile("mode:%d", n);

	switch(n) {

#ifdef USE_TERMIOS
	case 2:		/* Un-raw mode used by sz, sb when -g detected */
		if(!did0) {
			did0 = TRUE;
			tcgetattr(fd,&oldtty);
		}
		tty = oldtty;

		tty.c_iflag = BRKINT|IXON;

		tty.c_oflag = 0;	/* Transparent output */

		tty.c_cflag &= ~PARENB;	/* Disable parity */
		tty.c_cflag |= CS8;	/* Set character size = 8 */
		if (Twostop)
			tty.c_cflag |= CSTOPB;	/* Set two stop bits */

#ifdef READCHECK
		tty.c_lflag = protocol==ZM_ZMODEM ? 0 : ISIG;
		tty.c_cc[VINTR] = protocol==ZM_ZMODEM ? -1 : 030;	/* Interrupt char */
#else
		tty.c_lflag = 0;
		tty.c_cc[VINTR] = protocol==ZM_ZMODEM ? 03 : 030;	/* Interrupt char */
#endif
#ifdef _POSIX_VDISABLE
		if (((int) _POSIX_VDISABLE)!=(-1)) {
			tty.c_cc[VQUIT] = _POSIX_VDISABLE;		/* Quit char */
		} else {
			tty.c_cc[VQUIT] = -1;			/* Quit char */
		}
#else
		tty.c_cc[VQUIT] = -1;			/* Quit char */
#endif
#ifdef NFGVMIN
		tty.c_cc[VMIN] = 1;
#else
		tty.c_cc[VMIN] = 3;	 /* This many chars satisfies reads */
#endif
		tty.c_cc[VTIME] = 1;	/* or in this many tenths of seconds */

		tcsetattr(fd,TCSADRAIN,&tty);

		return OK;
	case 1:
	case 3:
		if(!did0) {
			did0 = TRUE;
			tcgetattr(fd,&oldtty);
		}
		tty = oldtty;

		tty.c_iflag = IGNBRK;
		if (n==3) /* with flow control */
			tty.c_iflag |= IXOFF;

		 /* No echo, crlf mapping, INTR, QUIT, delays, no erase/kill */
		tty.c_lflag &= ~(ECHO | ICANON | ISIG);
		tty.c_oflag = 0;	/* Transparent output */

		tty.c_cflag &= ~(PARENB);	/* Same baud rate, disable parity */
		/* Set character size = 8 */
		tty.c_cflag &= ~(CSIZE);
		tty.c_cflag |= CS8;	
		if (Twostop)
			tty.c_cflag |= CSTOPB;	/* Set two stop bits */
#ifdef NFGVMIN
		tty.c_cc[VMIN] = 1; /* This many chars satisfies reads */
#else
		tty.c_cc[VMIN] = HOWMANY; /* This many chars satisfies reads */
#endif
		tty.c_cc[VTIME] = 1;	/* or in this many tenths of seconds */
		tcsetattr(fd,TCSADRAIN,&tty);
		Baudrate = getspeed(cfgetospeed(&tty));
		return OK;
	case 0:
		if(!did0)
			return ERROR;
		tcdrain (fd); /* wait until everything is sent */
		tcflush (fd,TCIOFLUSH); /* flush input queue */
		tcsetattr (fd,TCSADRAIN,&oldtty);
		tcflow (fd,TCOON); /* restart output */

		return OK;
#endif

#ifdef USE_TERMIO
	case 2:		/* Un-raw mode used by sz, sb when -g detected */
		if(!did0)
			(void) ioctl(fd, TCGETA, &oldtty);
		tty = oldtty;

		tty.c_iflag = BRKINT|IXON;

		tty.c_oflag = 0;	/* Transparent output */

		tty.c_cflag &= ~PARENB;	/* Disable parity */
		tty.c_cflag |= CS8;	/* Set character size = 8 */
		if (Twostop)
			tty.c_cflag |= CSTOPB;	/* Set two stop bits */


#ifdef READCHECK
		tty.c_lflag = protocol==ZM_ZMODEM ? 0 : ISIG;
		tty.c_cc[VINTR] = protocol==ZM_ZMODEM ? -1 : 030;	/* Interrupt char */
#else
		tty.c_lflag = 0;
		tty.c_cc[VINTR] = protocol==ZM_ZMODEM ? 03 : 030;	/* Interrupt char */
#endif
		tty.c_cc[VQUIT] = -1;			/* Quit char */
#ifdef NFGVMIN
		tty.c_cc[VMIN] = 1;
#else
		tty.c_cc[VMIN] = 3;	 /* This many chars satisfies reads */
#endif
		tty.c_cc[VTIME] = 1;	/* or in this many tenths of seconds */

		(void) ioctl(fd, TCSETAW, &tty);
		did0 = TRUE;
		return OK;
	case 1:
	case 3:
		if(!did0)
			(void) ioctl(fd, TCGETA, &oldtty);
		tty = oldtty;

		tty.c_iflag = n==3 ? (IGNBRK|IXOFF) : IGNBRK;

		 /* No echo, crlf mapping, delays, no erase/kill */
		tty.c_lflag &= ~(ECHO | ICANON | ISIG);

		tty.c_oflag = 0;	/* Transparent output */

		tty.c_cflag &= ~PARENB;	/* Same baud rate, disable parity */
		tty.c_cflag |= CS8;	/* Set character size = 8 */
		if (Twostop)
			tty.c_cflag |= CSTOPB;	/* Set two stop bits */
#ifdef NFGVMIN
		tty.c_cc[VMIN] = 1; /* This many chars satisfies reads */
#else
		tty.c_cc[VMIN] = HOWMANY; /* This many chars satisfies reads */
#endif
		tty.c_cc[VTIME] = 1;	/* or in this many tenths of seconds */
		(void) ioctl(fd, TCSETAW, &tty);
		did0 = TRUE;
		Baudrate = getspeed(tty.c_cflag & CBAUD);
		return OK;
	case 0:
		if(!did0)
			return ERROR;
		(void) ioctl(fd, TCSBRK, 1);	/* Wait for output to drain */
		(void) ioctl(fd, TCFLSH, 0);	/* Flush input queue */
		(void) ioctl(fd, TCSETAW, &oldtty);	/* Restore modes */
		(void) ioctl(fd, TCXONC,1);	/* Restart output */
		return OK;
#endif


#ifdef USE_SGTTY
	/*
	 *  NOTE: this should transmit all 8 bits and at the same time
	 *   respond to XOFF/XON flow control.  If no FIONREAD or other
	 *   READCHECK alternative, also must respond to INTRRUPT char
	 *   This doesn't work with V7.  It should work with LLITOUT,
	 *   but LLITOUT was broken on the machine I tried it on.
	 */
	case 2:		/* Un-raw mode used by sz, sb when -g detected */
		if(!did0) {
			ioctl(fd, TIOCEXCL, 0);
			ioctl(fd, TIOCGETP, &oldtty);
			ioctl(fd, TIOCGETC, &oldtch);
#ifdef LLITOUT
			ioctl(fd, TIOCLGET, &Locmode);
#endif
		}
		tty = oldtty;
		tch = oldtch;
#ifdef READCHECK
		tch.t_intrc = Zmodem ? -1:030;	/* Interrupt char */
#else
		tch.t_intrc = Zmodem ? 03:030;	/* Interrupt char */
#endif
		tty.sg_flags |= (ODDP|EVENP|CBREAK);
		tty.sg_flags &= ~(ALLDELAY|CRMOD|ECHO|LCASE);
		ioctl(fd, TIOCSETP, &tty);
		ioctl(fd, TIOCSETC, &tch);
#ifdef LLITOUT
		ioctl(fd, TIOCLBIS, &Locbit);
#else
		bibi(99);	/* un-raw doesn't work w/o lit out */
#endif
		did0 = TRUE;
		return OK;
	case 1:
	case 3:
		if(!did0) {
			ioctl(fd, TIOCEXCL, 0);
			ioctl(fd, TIOCGETP, &oldtty);
			ioctl(fd, TIOCGETC, &oldtch);
#ifdef LLITOUT
			ioctl(fd, TIOCLGET, &Locmode);
#endif
		}
		tty = oldtty;
		tty.sg_flags |= RAW;
		tty.sg_flags &= ~ECHO;
		ioctl(fd, TIOCSETP, &tty);
		did0 = TRUE;
		Baudrate = getspeed(tty.sg_ospeed);
		return OK;
	case 0:
		if(!did0)
			return ERROR;
		ioctl(fd, TIOCSETP, &oldtty);
		ioctl(fd, TIOCSETC, &oldtch);
		ioctl(fd, TIOCNXCL, 0);
#ifdef LLITOUT
		ioctl(fd, TIOCLSET, &Locmode);
#endif
#ifdef TIOCFLUSH
		{ int x=1; ioctl(fd,TIOCFLUSH,&x); }
#endif
#endif

		return OK;
	default:
		return ERROR;
	}
#endif
}

void
sendbrk(int fd)
{
#if 0
#ifdef USE_TERMIOS
	tcsendbreak(fd,0);
#endif
#ifdef USE_TERMIO
	ioctl(fd, TCSBRK, 0);
#endif
#ifdef USE_SGTTY
#ifdef TIOCSBRK
	sleep(1);
	ioctl(fd, TIOCSBRK, 0);
	sleep(1);
	ioctl(fd, TIOCCBRK, 0);
#endif
#endif
#endif
}

void
purgeline(int fd)
{
	readline_purge();
#if 0
#ifdef TCFLSH
	ioctl(fd, TCFLSH, 0);
#else
	lseek(fd, 0L, 2);
#endif
#endif
}

/* End of rbsb.c */
