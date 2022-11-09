// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <linux/ctype.h>
#include <linux/types.h>

long atol(const char *nptr)
{
	int c;
	long total;
	int sign;

	while (isspace((int)(unsigned char)*nptr))
		++nptr;

	c = (int)(unsigned char)*nptr++;
	sign = c;
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++;

	total = 0;

	while (isdigit(c)) {
		total = 10 * total + (c - '0');
		c = (int)(unsigned char)*nptr++;
	}

	if (sign == '-')
		return -total;
	else
		return total;
}

int atoi(const char *nptr)
{
	return (int)atol(nptr);
}
