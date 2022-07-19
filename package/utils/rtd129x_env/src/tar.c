
/************************************************************************
 *
 *  tarread.c
 *
 *  find a file in a tar image.
 *
 *
 *
 * ######################################################################
 *
 * mips_start_of_legal_notice
 *
 * Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
 *
 *
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 *
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies"). Any copying, reproducing, modifying or use of this code
 * (in whole or in part) that is not expressly permitted in writing by MIPS
 * Technologies or an authorized third party is strictly prohibited. At a
 * minimum, this code is protected under unfair competition and copyright
 * laws. Violations thereof may result in criminal penalties and fines.
 *
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise. MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of any
 * error or omission in such code. Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the implied
 * warranties of merchantability or fitness for a particular purpose, are
 * excluded. Except as expressly provided in any written license agreement
 * from MIPS Technologies or an authorized third party, the furnishing of
 * this code does not give recipient any license to any intellectual
 * property rights, including any patent rights, that cover this code.
 *
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 *
 * This code constitutes one or more of the following: commercial computer
 * software, commercial computer software documentation or other commercial
 * items. If the user of this code, or any related documentation of any
 * kind, including related technical data or manuals, is an agency,
 * department, or other entity of the United States government
 * ("Government"), the use, duplication, reproduction, release,
 * modification, disclosure, or transfer of this code, or any related
 * documentation of any kind, is restricted in accordance with Federal
 * Acquisition Regulation 12.212 for civilian agencies and Defense Federal
 * Acquisition Regulation Supplement 227.7202 for military agencies. The use
 * of this code by the Government is further restricted in accordance with
 * the terms of the license agreement(s) and/or applicable contract terms
 * and conditions covering this code from MIPS Technologies or an authorized
 * third party.
 *
 *
 * mips_end_of_legal_notice
 *
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include "tar.h"
//#include <sysdefs.h>
//#include <string.h>
//#include <stdio.h>
//#include <ctype.h>
//#include <sys_api.h>
//#define TAR_DEBUG(msg,arg...)   do { printf("[%s %d]:", __FILE__, __LINE__); printf(msg,##arg); } while(0)
#define TAR_DEBUG(msg,arg...)

/************************************************************************
 *  Definitions
 ************************************************************************/
/* State event machine states */

/************************************************************************
 *  Public variables
 ************************************************************************/
unsigned int tar_read_print_info = 0; /* set 1 to print the file name that matched tar_read_print_prefix */
unsigned char tar_read_print_prefix[32] = "";

/************************************************************************
 *  Static variables
 ************************************************************************/
/************************************************************************
 *  Static function prototypes
 ************************************************************************/
//static unsigned char g_tar_buf[CONFIG_FACTORY_SIZE];

/************************************************************************
 *  Implementation : Static functions
 ************************************************************************/

unsigned int tar_checksum(char *header ) {

	unsigned char *data = (unsigned char *)header;
	unsigned int sum;
	int i;
	// check checksum;
	sum=0;
	for (i=0;i<148;i++) sum+=data[i];

	for (i=156;i<512;i++) sum+=data[i];

	for (i=0; i<8; i++) sum += 32;

	TAR_DEBUG("check_sum = %06o\n", sum);
	return sum;
}

int tar_check_header(	char *cheader ) {

	posix_header* header = (posix_header *)cheader;
	 if (isascii(header->name[0]) == 0) {
		return -1;
	 }

	if (tar_checksum((char *)header) != strtol(header->chksum, 0, 8))  {
		// true tar function
		fprintf(stderr, "check sum error\n");
		//printf("check sum error %s %o\n", header->chksum, tar_checksum(header));
		return -1;
	}
	return 0;

}

void tar_fill_checksum(char *cheader ) {

	posix_header* header = (posix_header *)cheader;
	sprintf(header->chksum, "%06o", tar_checksum((char *)header));

	header->chksum[6] = 0;
	header->chksum[7] = 0x20;
	TAR_DEBUG("fill checksum  = %s\n", header->chksum);
}

void tar_build_header(char *cheader, char* filename, int length, char filetype ) {

	posix_header* header = (posix_header *)cheader;
	TAR_DEBUG("%s %d\n", __FUNCTION__, __LINE__);
	TAR_DEBUG("filename = %s\n", filename);
	strcpy(header->name, filename);
	strcpy(header->mode, "0000777");
	strcpy(header->uid, "0001760");
	strcpy(header->gid, "0001761");
	strcpy(header->mtime, "11720412623");
	header->typeflag = filetype;

	memset(header->linkname, 0, sizeof(header->linkname));
	sprintf(header->size,  "%011o", length);
	TAR_DEBUG("header->size = %s\n", header->size);
	sprintf(header->magic, "ustar");
	memset(header->uname, 0, sizeof(header->uname));
	sprintf(header->uname, "root");
	memset(header->gname, 0, sizeof(header->gname));
	sprintf(header->gname, "root");
	memset(header->prefix, 0, sizeof(header->prefix));
	TAR_DEBUG("header->size = %s\n", header->size);
	tar_fill_checksum((char *)header);


}



int tar_read_by_index(
    int index,
    char *src_addr,
    char *dst_addr, int* length, char *name)
{
    posix_header *header = NULL;  //512 bytes
    int file_size=0;
    int pos = 0;
    char *data = NULL;
    TAR_DEBUG("%s %d ............................................. \n", __FUNCTION__, index);
    for (;index >= 0;)
    {
		header = (posix_header *) &src_addr[pos];
       // check checksum;
        if (tar_check_header((char *)header) < 0) {
			break;
	 }
	 data = &src_addr[pos + 512];
        file_size = strtol(header->size ,0,8);
	 pos = pos + 512 + ((file_size + 511)/512) * 512;

        if (strncmp(header->name, "tmp/factory/env/", strlen("tmp/factory/env/")))
    	      continue;
	 index--;

    }
    if (index >= 0) {
		printf("no filename found\n");
		return -1;
    }
    TAR_DEBUG("Found filename = %s %x\n", header->name, file_size);

    if (dst_addr != NULL) {
		strcpy(name, header->name);
		strcpy(dst_addr, data);
    }
    if (length != NULL) {
		*length = file_size;
	}
    return file_size;
}

/************************************************************************
 *                          tar_read
 ************************************************************************/
int tar_read(
    char *s,
    char *src_addr,
    unsigned int length,
    char **dst_addr,
    unsigned int *dst_length )
{
	long fd,sum;
	char *header;  //512 bytes

	TAR_DEBUG("tar read %s %x \n", s, src_addr);

	fd = (long)src_addr;

	if (src_addr == NULL)
		;

	for (;;)
	{
		int len;

		header = (char *)fd;
		if (header[0] == 0) {
			return 0;
		}

		// check checksum;
		sum = tar_checksum(header);
		TAR_DEBUG(" checksum2 = %s\n", ((posix_header *) header)->chksum);

		if (tar_check_header(header) < 0) {
			return 0;
		}

		if (tar_read_print_info && !strncmp((const char *)tar_read_print_prefix, header, strlen((const char *)tar_read_print_prefix)))
		{
			printf("%s\n", header);
		}

		if (header[0] == '\0') {
			break;
		}

		TAR_DEBUG("filename = %s\n", header);

		// match name
		if (!strncmp(s,header,100))
		{
			// found it!
			TAR_DEBUG("Found it 0x%x\n", fd);
			if (sum != strtol(header + 148,0,8))
			{
				printf("Invalid tar file,check sum error \n");
				return 0;
			}

			TAR_DEBUG("dump 0x%x 0x%x", dst_addr, dst_length);
			TAR_DEBUG("dump 0x%x 0x%x", header + 512, strtol(header + 124,0,8));

			*dst_addr = header + 512;
			*dst_length = strtol(header + 124,0,8);

			return fd;
		}

		len = strtol(header + 124,0,8);
		len = ((len + 511) / 512 + 1)*512;

		fd += len ;

		if (fd > (long)(src_addr + length) )
		{
			printf("tar end,not found \n");
			return 0;
		}
	}
	return 0;
}



int  tar_add_or_delete(char *dst_tar_buf, char* filename, char *src_buf, int length, char *tmp_buf, int tmp_buf_length, int addordel) {
	posix_header *header;
	int file_size, pos, tmp_pos;
	//char *tar_buf;
	int done = 0;
	header = (posix_header *) dst_tar_buf;
	//tar_buf = (char *) dst_tar_buf;
	pos = 0;
	tmp_pos = 0;
	if (tmp_buf == NULL) {
		return 0;
		//tmp_buffer = g_tar_buf;
	}
	TAR_DEBUG("addordel = %d\n", addordel);
	memset(tmp_buf, 0, tmp_buf_length);
	TAR_DEBUG("header =%x\n", header);
	TAR_DEBUG("filename = %s\n", filename);
	TAR_DEBUG("%s %d\n", __FUNCTION__, __LINE__);

	while(header->name[0]) {
		TAR_DEBUG("%s %d\n", __FUNCTION__, __LINE__);
		if (tar_check_header((char *)header) < 0) {
			break;
		}
		file_size = strtol(header->size, 0, 8);
		TAR_DEBUG("tar file : %s %x %s %s %x\n", filename, length, header->name, header->size, file_size);
		file_size = ((file_size + 511) /512) * 512;


		if (strstr(header->name, filename) == header->name) {
			TAR_DEBUG("Found %s\n", header->name);
			if (addordel && done == 0) {
				tar_build_header((char *)header, filename, length, '0');
				memcpy(&tmp_buf[tmp_pos], header, 512);
				tmp_pos += 512;
				memcpy(&tmp_buf[tmp_pos], src_buf, length);
				tmp_pos += ((length+511)/512) * 512;
				done = 1;
			}
		} else {
#ifdef NAS_ENABLE
			/* Skip redudant header check at the end of tar file */
			if(strcmp(header->rtk_signature, "RTK") || !pos)
#endif
			{
			memcpy(&tmp_buf[tmp_pos], header, 512+file_size);
			tmp_pos += (512 + file_size);
			}
		}
		pos = pos + 512 + file_size;
		header = (posix_header *) &dst_tar_buf[pos];

	}
	if ((done == 0) && (addordel != 0) ) {
		TAR_DEBUG("%s %d\n", __FUNCTION__, __LINE__);
		header = (posix_header *) &tmp_buf[tmp_pos];
		TAR_DEBUG("header =%x\n", header);
		tar_build_header((char *)header, filename, length, '0');
		memcpy(&tmp_buf[tmp_pos], header, 512);
		tmp_pos += 512;
		memcpy(&tmp_buf[tmp_pos], src_buf, length);
		tmp_pos += ((length+511)/512) * 512;
	}
	tmp_buf[tmp_pos] = 0;
	memset(dst_tar_buf, 0, pos);
	memcpy(dst_tar_buf, tmp_buf, tmp_pos);
	TAR_DEBUG("tmp_pos = %x pos = %x\n", tmp_pos, pos);
	TAR_DEBUG("dst_tar_buf = %s\n", &dst_tar_buf[tmp_pos-512]);
	return tmp_pos;
}



