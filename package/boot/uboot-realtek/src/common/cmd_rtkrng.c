/*
 * (C) Copyright 2000-2003
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

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <asm/arch/rbus/sb2_reg.h>
#include <asm/arch/rbus/md_reg.h>
#include <asm/arch/rbus/rng_reg.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/io.h>
#include <asm/arch/io.h>

#define MAX_1MS_TO_CNT		1000

unsigned int rtkgen(int debug_reg)
{
	unsigned int reg_val=0, tocnt=0, ret_val = 0;

	//1. hw do the cali
	rtd_outl(RNG_CALI_CHK,0x0d800220);
	//2. lock chk
	rtd_outl(RNG_LOCK_CHK,0x0d800220);
	//3. release TRNG HardMaco power-on
	rtd_outl(RNG_ANA,0x00008891);
	//4. wait CKOUT_ROSC stable
	mdelay(1);
	if( debug_reg ) {
    	reg_val = rtd_inl(RNG_CALI_RETURN);
    	printf("rng cali val: 0x%08x\n", reg_val);
	}
    
	//5. polling bit 0 to 1 as stable in 1 sec
	while (!(rtd_inl(RNG_RETURN3) & 0x1))
	{
		mdelay(1);
		if (tocnt++ > MAX_1MS_TO_CNT)
		{
			return 0;
		}
	}
	//6. get data
	ret_val = rtd_inl(RNG_RESULTR);
	return ret_val;	
}

void show_rtkgen(int debug_reg)
{
	unsigned int reg_val;
	
	reg_val = rtkgen(debug_reg);
	
	printf("rng val = 0x%08x\n", reg_val);
}

int do_rtkrng(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int cmd;

    cmd = -1;

    // parse command
    if( argc > 1 ) {
        if( strncmp( argv[1], "gen", 3 ) == 0 ) {
        	if( argc > 2 ) {
        		if( strncmp( argv[2], "debug", 5 ) == 0  ) {
        			cmd = 1;
        		}
			}
			else {
				cmd = 0;
			}
        }
    }

    if( cmd < 0 ) {
        printf("Error: command %s error\n", argv[1]);
        return -1;
    }

    do {
        if( cmd == 0 || cmd == 1 ) {
        	show_rtkgen(cmd);
            return 0;
        }
    }
    while(0);

    return -1;
}

U_BOOT_CMD(
    rtkrng, 5, 0,   do_rtkrng,
    "rng utility",
    "\nrtkrng gen [debug]\n"
);
