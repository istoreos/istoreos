// copy from U-Boot64/examples/flash_writer/tools/hw_setting_maker/generate_config.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//===================================================
#define LINE_SIZE	2048

#define OP_WRITE	0x0	// these op code should be in 2-bit space (i.e. 0~3)
#define OP_POLL		0x1
//#define OP_READ		0x2
#define OP_MASK		0x2
#define OP_NOP		0x3

#define TERMINATE_SYMBOL	0xffffffff

#define PP_MAPPING_SIZE	512
//===================================================
void load_config(char *in_fanme, char *out_fname);
unsigned int atoh(char *str);
void fputi(int n, FILE *stream);

//===================================================

int main(int argc, char **args)
{
	char default_fname[64] = "hw_setting.bin";

	printf("2013-05-08 15:00\n");

	if (argc < 2) {
		printf("Usage:\n\t generate_config.exe <config_file> [<out_file>]\n");
		return -1;
	}

	load_config(args[1], (argc == 3 ? args[2] : default_fname));

	return 0;
}

void load_config(char *in_fanme, char *out_fname)
{
	FILE *fin, *fout;
	char line_orig[LINE_SIZE];
	char line[LINE_SIZE];
	char delim[4] = " ,";
	char *token;
	unsigned int addr, mask, value;
	int count = 0;
	int repeat;
	int repeate_val;
	int do_repeat_once = 0;	
	int error = 0;
	char op_code;
	int w_cnt, n_cnt, p_cnt, r_cnt, m_cnt;
	int remain, zero_count;
	
	fin = fopen(in_fanme, "rt");
	
	if (fin == NULL)
		return;

	fout = fopen(out_fname, "wb");
	w_cnt = n_cnt = p_cnt = r_cnt = m_cnt = 0;
	
	while ((fgets(line_orig, LINE_SIZE, fin)) != NULL) {

		repeat = 1;
		do_repeat_once = 0;

		while( repeat-- ) {
			memcpy( line, line_orig, LINE_SIZE); 
			//printf("line=%s", line);	// each line contains CR/LF
			token = strtok(line, delim);
			op_code = token[0];
			
			if (op_code == '\0' || 
				op_code == 0x9 || 
				op_code == 0xa ||  
				op_code == '#' || 
				op_code == '/') {
				break;
			}	
				
			// how many bytes available in the PP mapping area
			remain = PP_MAPPING_SIZE - (count % PP_MAPPING_SIZE);
			zero_count = 0;
			
			if (op_code == 'w') {	// write register
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				addr = atoh(token);
	
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				value = atoh(token);
				
				if (remain < 8) {
					while (remain > 0) {
						fputi(0, fout);
						remain -= 4;
						count += 4;
						zero_count++;
					}
					printf("stuff %d dummy zero(es)\n", zero_count);
				}
				
				fputi(addr|OP_WRITE, fout);
				fputi(value, fout);
				printf("write: 0x%08x = 0x%08x\n", addr, value);
				count += 8;
				w_cnt++;
			}
			else if (op_code == 'p') {	// polling
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				addr = atoh(token);
	
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				mask = atoh(token);
				
				if ((token = strtok(NULL, delim)) == NULL){
					error = -1;
					break;
				}
				value = atoh(token);
				
				if (remain < 12) {
					while (remain > 0) {
						fputi(0, fout);
						remain -= 4;
						count += 4;
						zero_count++;
					}
					printf("stuff %d dummy zero(es)\n", zero_count);
				}
	
				fputi(addr|OP_POLL, fout);
				fputi(mask, fout);
				fputi(value, fout);
				
				printf("poll: 0x%08x & 0x%08x = 0x%08x\n", addr, mask, value);
				count += 12;
				p_cnt++;
			}
			else if (op_code == 'n') {	// NOP loop
				if ((token = strtok(NULL, delim)) == NULL){
					error = -1;
					break;
				}
				value = atoh(token);	// NOP count
				
				if (remain < 8) {
					while (remain > 0) {
						fputi(0, fout);
						remain -= 4;
						count += 4;
						zero_count++;
					}
					printf("stuff %d dummy zero(es)\n", zero_count);
				}
	
				fputi(OP_NOP, fout);
				fputi(value, fout);
				
				printf("nop: 0x%x\n", value);
				count += 8;
				n_cnt++;
			}
	#if 0
			else if (op_code == 'r') {
				if ((token = strtok(NULL, delim)) == NULL){
					error = -1;
					break;
				}
				addr = atoh(token);	// src address
	
				if ((token = strtok(NULL, delim)) == NULL){
					error = -1;
					break;
				}
				value = atoh(token);	// dest address
				
				if (remain < 8) {
					while (remain > 0) {
						fputi(0, fout);
						remain -= 4;
						count += 4;
						zero_count++;
					}
					printf("stuff %d dummy zero(es)\n", zero_count);
				}
	
				fputi(addr|OP_READ, fout);
				fputi(value, fout);
				printf("read: 0x%08x -> 0x%08x\n", addr, value);
				count += 8;
				r_cnt++;
			}
	#endif
			else if (op_code == 'm') {	// alter bit in register
				repeate_val = 9;
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				addr = atoh(token);	// register
	
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				mask = atoh(token);	// "AND" mask
				
				if ((token = strtok(NULL, delim)) == NULL) {
					error = -1;
					break;
				}
				value = atoh(token);	// "OR" mask
				
				if ((token = strtok(NULL, delim)) != NULL) {
					if( token[0] != '/' ) {
						repeate_val = atoh(token);	// repeate_val
					}
				}
				
				if (remain < 12) {
					while (remain > 0) {
						fputi(0, fout);
						remain -= 4;
						count += 4;
						zero_count++;
					}
					printf("stuff %d dummy zero(es)\n", zero_count);
				}
	
				printf("mask: (0x%08x & 0x%08x) | 0x%08x, repeat=%d\n", addr, mask, value, repeat);

				fputi(addr|OP_MASK, fout);
				fputi(mask, fout);
				fputi(value, fout);
				count += 12;
				m_cnt++;
				if( ( addr == 0xb801a60c ) && (repeat==0) && !do_repeat_once ) {
					if( repeate_val > 1 ) {
						repeat = repeate_val;
					}
					do_repeat_once = 1;	
				}
			}
			else {
				printf("skip unknown: %s\n", token);
				break;
			}
		} // inner while-loop
		if( error < 0 ) {
			break;
		}
	}
	
	fputi(TERMINATE_SYMBOL, fout);
	count += 4;
	
	fclose(fin);
	fclose(fout);
	printf("\noutput file: %s (%d bytes)\n", out_fname, count);
	printf("write: %d\npolling: %d\nnop: %d\nmask: %d\n", w_cnt, p_cnt, n_cnt, m_cnt);
}

unsigned int atoh(char *str)
{
	unsigned int value, digit;
	char c;
	
	value = 0;
	while ((c = *str++) != '\0') {
		//printf("%c", c);
		if (c >= '0' && c <= '9')
			digit = (unsigned int) (c - '0');
		else if (c >= 'a' && c <= 'f')
			digit = (unsigned int) (c - 'a') + 10;
		else if (c >= 'A' && c <= 'F')
			digit = (unsigned int) (c - 'A') + 10;
		else if (c == 'X' || c == 'x')
			value = 0;	// reset value
		else
			break;

		value <<= 4;
		value += digit;
	}

	return value;
}

void fputi(int n, FILE *stream)
{
	int i;

	//for (i = 24; i >= 0; i-=8)
		//fputc((n>>i & 0xff), stream);
	for (i = 0; i < 32; i += 8)
		fputc( (n >> i)&0xff, stream);
}
