/*
* Copyright (C) 2016 The Android Open Source Project
*
* SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef __NET_FASTBOOT_H__
#define __NET_FASTBOOT_H__

/**********************************************************************/
/*
 *	Global functions and variables.
 */

/**
 * Wait for incoming fastboot comands.
 */
void fastboot_start_server(void);
/**
 * Send an INFO packet during long commands
 *
 * @param msg: String describing the reason for waiting
 */
void fastboot_send_info(const char*);

/**********************************************************************/

#endif /* __NET_FASTBOOT_H__ */
