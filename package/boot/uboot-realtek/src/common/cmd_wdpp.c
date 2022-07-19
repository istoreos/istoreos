/*
 * river.chen@wdc.com
 */

#include <common.h>
#include <command.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <part.h>
#include <usb.h>
#include <sata.h>
#include <part_efi.h>
#include <fat.h>

#define msleep(a)	udelay(a * 1000)

#define PING_PONG_FILENAME "current_pp"

extern int sata_curr_device;

unsigned char g_wdpp_flag;

int wdpp_set(unsigned char pp);

int wdpp_usage(void)
{
	printf("usage:\n(1)wdpp set [A | B]\n(2)wdpp get\n");
	return 0;
}

int wdpp_get(void)
{
	char tmpbuf[128];
	char read_buf[2];
	ulong addr = 0x4000000;

	printf("=== %s ===\n",__func__);

#if defined(CONFIG_BOARD_WD_MONARCH)

	if(sata_curr_device != 0){
		sprintf(tmpbuf, "sata init");
		if (run_command(tmpbuf, 0) != 0) {
			printf("%s: Failed to init sata devices, try again!\n",__func__);

			msleep(1000);

			sprintf(tmpbuf, "sata init");
			if (run_command(tmpbuf, 0) != 0) {
				printf("%s: Failed to init sata devices...\n",__func__);
			}
		}
	}

	sprintf(tmpbuf, "fatls sata 0:12"); //CONFIG partition is at sata 0:12
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: Failed to list files in CONFIG partition, set ping pong flag to A\n",__func__);
		wdpp_set('A');
	}


	sprintf(tmpbuf, "fatload sata 0:12 0x4000000 %s 2", PING_PONG_FILENAME);
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: File %s does not exist, set ping pong flag to A\n",__func__, PING_PONG_FILENAME);
		wdpp_set('A');
	}


	read_buf[0] = *(u_char *)addr;
	read_buf[1] = *(u_char *)(addr+1);
	//printf("read_buf[0] = 0x%02x\n", read_buf[0]);
	//printf("read_buf[1] = 0x%02x\n", read_buf[1]);
	if( *read_buf == 'a' || *read_buf == 'A'){
		printf("current_pp = A\n");
		g_wdpp_flag = read_buf[0];
		return 0;
	}
	else if( *read_buf == 'b' || *read_buf == 'B'){
		printf("current_pp = B\n");
		g_wdpp_flag = read_buf[0];
		return 0;
	}
	else{
		printf("Unknown ping pong flag...\n");
		return -4;
	}

	return 0;

#elif defined(CONFIG_BOARD_WD_PELICAN)

	sprintf(tmpbuf, "fatls mmc 0:1"); //CONFIG partition is at mmc 0:1
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: Failed to list files in CONFIG partition, set ping pong flag to A\n",__func__);
		wdpp_set('A');
	}


	sprintf(tmpbuf, "fatload mmc 0:1 0x4000000 %s 2", PING_PONG_FILENAME);
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: File %s does not exist, set ping pong flag to A\n",__func__, PING_PONG_FILENAME);
		wdpp_set('A');
	}


	read_buf[0] = *(u_char *)addr;
	read_buf[1] = *(u_char *)(addr+1);
	//printf("read_buf[0] = 0x%02x\n", read_buf[0]);
	//printf("read_buf[1] = 0x%02x\n", read_buf[1]);
	if( *read_buf == 'a' || *read_buf == 'A'){
		printf("current_pp = A\n");
		g_wdpp_flag = read_buf[0];
		return 0;
	}
	else if( *read_buf == 'b' || *read_buf == 'B'){
		printf("current_pp = B\n");
		g_wdpp_flag = read_buf[0];
		return 0;
	}
	else{
		printf("Unknown ping pong flag...\n");
		return -4;
	}

	return 0;

#else
	echo "OPPS: please definbe valid macro for your BOARD"
#endif


}

int wdpp_set(unsigned char pp)
{

	char tmpbuf[128];
	ulong addr = 0x4000000;


#if defined(CONFIG_BOARD_WD_MONARCH)

	if(sata_curr_device != 0){
		sprintf(tmpbuf, "sata init");
		if (run_command(tmpbuf, 0) != 0) {
			printf("%s: Failed to init sata devices\n",__func__);
			return -1;
		}
	}

	sprintf(tmpbuf, "rtkfat gen sata auto 12");
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: Failed to format sata 0:18 partition\n",__func__);
		return -2;
	}


	*(u_char *)addr = pp;
	*(u_char *)(addr+1) = 0x0a;

	sprintf(tmpbuf, "fatwrite sata 0:12 0x4000000 %s 2", PING_PONG_FILENAME);
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: File %s does not exist, run \"wdpp set\" command manually\n",__func__, PING_PONG_FILENAME);
		return -3;
	}

	g_wdpp_flag = pp;

	printf("%s: set pp to %c\n",__func__, pp);

	return 0;

#elif defined(CONFIG_BOARD_WD_PELICAN)

	*(u_char *)addr = pp;
	*(u_char *)(addr+1) = 0x0a;

	sprintf(tmpbuf, "fatwrite mmc 0:1 0x4000000 %s 2", PING_PONG_FILENAME);
	if (run_command(tmpbuf, 0) != 0) {
		printf("%s: File %s does not exist, run \"wdpp set\" command manually\n",__func__, PING_PONG_FILENAME);
		return -3;
	}

	g_wdpp_flag = pp;

	printf("%s: set pp to %c\n",__func__, pp);

	return 0;

#else
	echo "OPPS: please definbe valid macro for your BOARD"
#endif


}

int do_wdpp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

	int retval = 0;

	if(argc < 2 || argc > 3)
		wdpp_usage();

	if(argc == 2){
		if( strncmp( argv[1], "get", 3 ) == 0 )
			return wdpp_get();
		else
			return wdpp_usage();
	}

	if(argc == 3){

		if((argv[2][0] == 'a') || (argv[2][0] == 'A')){
			retval = wdpp_set('A');
		}
		else if((argv[2][0] == 'b') || (argv[2][0] == 'B')){
			retval = wdpp_set('B');
		}
		else{
			printf("Error! Unknown ping pong flag %s, set flag to A\n", argv[2]);
			retval = wdpp_set('A');
		}
	}

	return retval;
}


U_BOOT_CMD(
    wdpp, 3, 0,   do_wdpp,
    "Western Digital Boot Patition Tool ",
    "\n(1)wdpp set [A | B] [default A]"
    "\n(2)wdpp get "
);
