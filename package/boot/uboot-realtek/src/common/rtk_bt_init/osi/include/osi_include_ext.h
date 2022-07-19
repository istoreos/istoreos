/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Realtek Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#ifndef INCLUDE_EXT_H
#define INCLUDE_EXT_H

#include <stdbool.h>
#include <common.h>
#include <command.h>
#include <serial.h>

#include <dm.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <part.h>
#include <usb.h>

#define MEMORY_STATIC_ALLOC FALSE
#if (!MEMORY_STATIC_ALLOC)
#include <stdlib.h>
#endif

DECLARE_GLOBAL_DATA_PTR;
extern int serial_init_uart(char uart);
extern struct serial_device *get_uart(char uart);

#define RTKBT_DEBUG 0

#define RTK_ERROR(fmt, args...)	    debug_cond(1, fmt, ##args)
#define RTK_INFO(fmt, args...)      debug_cond(1, fmt, ##args)

#if RTKBT_DEBUG
#define RTK_DEBUG(fmt, args...)	    debug_cond(RTKBT_DEBUG, fmt, ##args)
#define RTK_WARN(fmt, args...)	    debug_cond(RTKBT_DEBUG, fmt, ##args)
#define RTK_VERBOSE(fmt, args...)	debug_cond(RTKBT_DEBUG, fmt, ##args)
#else
#define RTK_DEBUG(fmt, args...)
#define RTK_WARN(fmt, args...)
#define RTK_VERBOSE(fmt, args...)
#endif


#endif
