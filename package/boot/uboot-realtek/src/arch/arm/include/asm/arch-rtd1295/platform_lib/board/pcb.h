#ifndef __PCB_H__
#define __PCB_H__

#include <platform_lib/board/pcb_mgr.h>


#if defined(CONFIG_BOARD_FPGA_RTD1295_EMMC)
	#include "pcb/pcb_rtd1295_fpga.h"	
#else
	#include "pcb/pcb_rtd1295_default.h"
	//#error "pcbMgr no support this board."
#endif

#endif	// __PCB_H__

