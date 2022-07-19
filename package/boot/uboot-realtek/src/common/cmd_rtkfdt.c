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
#include <asm/arch/system.h>
#include <asm/global_data.h>
#include <fdt.h>
#include <libfdt.h>
#include <fdt_support.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * external variable and functions were defined in cmd_fdt.c
 */
extern struct fdt_header *working_fdt;
extern int fdt_valid(struct fdt_header **blobp);
extern int fdt_parse_prop(char *const*newval, int count, char *data, int *len);
extern int fdt_print(const char *pathp, char *prop, int depth);
extern int is_printable_string(const void *data, int len);


/*
 * local definition
 */
#define MAX_LEVEL   32      	/* how deeply nested we will go */
#define SCRATCHPAD  1024    	/* bytes of scratchpad memory */

#define PROP_SNAME  "factory"
#define PROP_NAME   "/"PROP_SNAME

enum rtkfdt_cmd {
    RTKFDT_UNKNOWN = -1,
    RTKFDT_SET = 0,
    RTKFDT_RM,
    RTKFDT_LIST,
    RTKFDT_SIMULATION,
};

enum rtkfdt_tag {
    RTKFDT_MAC = 0,
    RTKFDT_SN,
    RTKFDT_CUSTOMIZE,
};

int rtkfdt_find_entry(void)
{
    ulong fdt_addr;
    int nodeoffset; /* node offset from libfdt */
    int err;
    struct fdt_header *blob;

    fdt_addr = getenv_ulong("fdt_loadaddr", 16, 0);

	/* find fdt address */
    if (fdt_addr) {
#if 0
        ret = fdt_chosen(fdt_addr, 1);
        if (ret < 0) {
            return ret;
        }
#else

        set_working_fdt_addr((ulong)fdt_addr);
        blob = working_fdt;

        if (!fdt_valid(&blob)) {
            return 1;
        }
#endif
    }
    else {
        printf("Error: Not found FDT base address by fdt_loadaddr\n");
        return 1;
    }

    /*
     * find node offset of PROP_NAME
     */
    nodeoffset = fdt_path_offset (working_fdt, PROP_NAME);
    if (nodeoffset < 0)
    {
        /*
         * Not found or something else bad happened.
         */
        printf("libfdt fdt_path_offset() returned %s\n", fdt_strerror(nodeoffset));
        printf("Info: Try to add new node %s...\n", PROP_NAME);
        nodeoffset = fdt_path_offset (working_fdt, "/");
        if (nodeoffset < 0) {
            /*
             * Not found or something else bad happened.
             */
            printf ("libfdt fdt_path_offset() returned %s\n",
            fdt_strerror(nodeoffset));
            return 1;
        }
        err = fdt_add_subnode(working_fdt, nodeoffset, PROP_SNAME);
        if (err < 0) {
            printf ("libfdt fdt_add_subnode(): %s\n", fdt_strerror(err));
            return err;
        }
    }

    return 0;
}

int rtkfdt_set( char * prop, char * input_data)
{
    int ret = 0;
    int nodeoffset; /* node offset from libfdt */
    int len;        /* new length of the property */
    static char data[SCRATCHPAD];

    /* not support multi val */
    ret = fdt_parse_prop(&input_data, 1, data, &len);
    if (ret != 0) {
        return ret;
    }

    nodeoffset = fdt_path_offset (working_fdt, PROP_NAME);
    if (nodeoffset < 0) {
        /*
         * Not found or something else bad happened.
         */
        printf ("libfdt fdt_path_offset() returned %s\n", fdt_strerror(nodeoffset));
        return 1;
    }
    ret = fdt_setprop(working_fdt, nodeoffset, prop, data, len);
    if (ret < 0) {
        printf ("libfdt fdt_setprop(): %s\n", fdt_strerror(ret));
        return ret;
    }

    return 0;
}

int rtkfdt_rm( char * prop )
{
    int ret = 0;
    int nodeoffset; /* node offset from libfdt */
    //int len;      /* new length of the property */

    /*
     * Get the path.  The root node is an oddball, the offset
     * is zero and has no name.
     */
    nodeoffset = fdt_path_offset (working_fdt, PROP_NAME);
    if (nodeoffset < 0) {
        /*
         * Not found or something else bad happened.
         */
        printf ("libfdt fdt_path_offset() returned %s\n", fdt_strerror(nodeoffset));
        return 1;
    }
    /*
     * Do the delete.  A fourth parameter means delete a property,
     * otherwise delete the node.
     */
    ret = fdt_delprop(working_fdt, nodeoffset, prop);
    if (ret < 0) {
        printf("libfdt fdt_delprop():  %s\n", fdt_strerror(ret));
        return ret;
    }

    return 0;
}

int rtkfdt_list(void)
{
    printf("*****************************************\n");
    fdt_print(PROP_NAME, NULL, 1);
	printf("*****************************************\n");
	return 0;
}

void rtkfdt_add_factory( void )
{
	int ret;
	char * pdata;

	ret = rtkfdt_find_entry();
    if( ret != 0 ) {
		return;
	}

	/* read mac from environment ethaddr */
	pdata = getenv("ethaddr");
	if( pdata ) {
		ret = rtkfdt_set("ethaddr", pdata);
	}
#if 0
	/* read gateway ip from environment gatewayip */
	pdata = getenv("gatewayip");
	if( pdata ) {
		ret = rtkfdt_set("gatewayip", pdata);
	}
#endif
	/* read ip addr from environment ipaddr */
	pdata = getenv("ipaddr");
	if( pdata ) {
		ret = rtkfdt_set("ipaddr", pdata);
	}
#if 0
	/* read netmask from environment netmask */
	pdata = getenv("netmask");
	if( pdata ) {
		ret = rtkfdt_set("netmask", pdata);
	}
#endif
	pdata = getenv("serial");
	if( pdata ) {
		ret = rtkfdt_set("serial", pdata);
	}

	pdata = getenv("ver");
	if( pdata ) {
		ret = rtkfdt_set("ver", pdata);
	}

	pdata = getenv("cbr");
	if( pdata ) {
		ret = rtkfdt_set("cbr", pdata);
	}

	pdata = getenv("nbr");
	if( pdata ) {
		ret = rtkfdt_set("nbr", pdata);
	}

	pdata = getenv("bna");
	if( pdata ) {
		ret = rtkfdt_set("bna", pdata);
	}

	pdata = getenv("bootstate");
	if( pdata ) {
		ret = rtkfdt_set("bootstate", pdata);
	}

	/* show current factory prop */
	rtkfdt_list();
}

int do_rtkfdt(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    enum rtkfdt_cmd my_cmd;
    //enum rtkfdt_tag my_tag;
    int ret;

    ret = 0;
    my_cmd = RTKFDT_UNKNOWN;
    //my_tag = RTKFDT_CUSTOMIZE;

    /* parse command */
    if( argc >= 2 ) {
        if( strncmp( argv[1], "set", 3 ) == 0 ) {
            if( argc < 4 ) {
                printf("Error: no enough arguments\n");
                return -1;
            }
            my_cmd = RTKFDT_SET;
        }
        if( strncmp( argv[1], "rm", 2 ) == 0 ) {
            if( argc > 3 ) {
                printf("Error: too many arguments\n");
                return -1;
            }
            my_cmd = RTKFDT_RM;
        }
        if( strncmp( argv[1], "list", 4 ) == 0 ) {
            my_cmd = RTKFDT_LIST;
        }
        if( strncmp( argv[1], "simulation", 10 ) == 0 ) {
            my_cmd = RTKFDT_SIMULATION;
        }
    }

    if( my_cmd < 0 ) {
        printf("Error: command %s error\n", argv[1]);
        return -1;
    }

    if( ( argc > 2 ) && strncmp( argv[2], "mac", 3 ) == 0 ) {
        //my_tag = RTKFDT_MAC;
        if( my_cmd == RTKFDT_SET && ( argc > 3 ) && ( strlen(argv[3]) != 17 ) ) {
            printf("Error: Argu3 string size must be 17-byte length\n");
            return -1;
        }
    }

    if( ( argc > 2 ) && strncmp( argv[2], "sn", 2 ) == 0 ) {
        //my_tag = RTKFDT_SN;
        if( my_cmd == RTKFDT_SET && ( argc > 3 ) && ( strlen(argv[3]) > 32 ) ) {
            printf("Error: Argu3 size is over 32 bytes\n");
            return -1;
        }
    }

    do {
		ret = rtkfdt_find_entry();
		if( ret != 0 ) {
			return 1;
		}

        /* set */
        if( my_cmd == RTKFDT_SET ) {
        	ret = rtkfdt_set(argv[2], argv[3]);
        }
        /* remove */
        if( my_cmd == RTKFDT_RM ) {
        	ret = rtkfdt_rm(argv[2]);
        }
        /* list */
        if( my_cmd == RTKFDT_LIST ) {
            ret = rtkfdt_list();
        }
        /* simulation */
        if( my_cmd == RTKFDT_SIMULATION ) {
            rtkfdt_add_factory();
        }
    }
    while(0);

    return 0;
}

U_BOOT_CMD(
    rtkfdt, 4, 0, do_rtkfdt,
    "RTK fdt utility",
    "\n"
    "(1) rtkfdt [set|rm] mac xx:xx:xx:xx:xx:xx\n"
    "(2) rtkfdt [set|rm] sn  ########\n"
    "(3) rtkfdt [set|rm] str1 str2\n"
    "(4) rtkfdt list\n"
    "(5) rtkfdt simulation\n"
    " Note: read nodes in kerel, Path is /sys/firmware/devicetree/base/factory"
);
