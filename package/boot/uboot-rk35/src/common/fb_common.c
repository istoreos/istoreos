/*
* Copyright (C) 2016 The Android Open Source Project
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#include <common.h>
#include <fastboot.h>
#ifdef CONFIG_UDP_FUNCTION_FASTBOOT
#include <net/fastboot.h>
#endif

void fastboot_fail(const char *reason, char *response)
{
	const char *fail_str = "FAIL";
	strncpy(response, fail_str, FASTBOOT_RESPONSE_LEN);
	strncat(response, reason, FASTBOOT_RESPONSE_LEN - strlen(fail_str) - 1);
}

void fastboot_okay(const char *reason, char *response)
{
	const char *okay_str = "OKAY";
	strncpy(response, okay_str, FASTBOOT_RESPONSE_LEN);
	strncat(response, reason, FASTBOOT_RESPONSE_LEN - strlen(okay_str) - 1);
}

void timed_send_info(ulong *start, const char *msg)
{
#ifdef CONFIG_UDP_FUNCTION_FASTBOOT
	/* Initialize timer */
	if (*start == 0) {
		*start = get_timer(0);
	}
	ulong time = get_timer(*start);
	/* Send INFO packet to host every 30 seconds */
	if (time >= 30000) {
		*start = get_timer(0);
		fastboot_send_info(msg);
	}
#endif
}
