/**
 * 用于把hwsetting.bin还原回.config文本文件
 * 
 * @author jjm2473
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//===================================================

#define OP_WRITE	0x0	// these op code should be in 2-bit space (i.e. 0~3)
#define OP_POLL		0x1
//#define OP_READ		0x2
#define OP_MASK		0x2
#define OP_NOP		0x3

#define TERMINATE_SYMBOL	0xffffffff
#define FILL_SYMBOL	0x0

//===================================================
int decode(char *in_fanme, char *out_fname);
int fgeti(FILE *stream, int *np);
//===================================================

int main(int argc, char **args)
{
	if (argc < 3) {
		printf("Usage:\n\t decode_hwsetting.exe hwsetting.bin hwsetting.config\n");
		return -1;
	}

	return decode(args[1], args[2]);
}

int fgeti(FILE *stream, int *np)
{
	int c;
	int i;
	int n = 0;
	for (i = 0; i < 32; i += 8) {
		c = fgetc(stream);
		if (c == EOF) {
			return EOF;
		}
		n = n | (c << i);
	}
	*np = n;
	return 4;
}

#define OP_NAME "wpmn"
#define NUM_FORMAT "0x%08x"

int decode(char *in_fanme, char *out_fname)
{
	FILE *fin, *fout;
	unsigned int addr, value;
	int op, argc, err = 0;
	fin = fopen(in_fanme, "rt");

	if (fin == NULL)
		return -1;

	fout = fopen(out_fname, "wb");
	if (fout == NULL)
		return -1;

	int terminated = 0;
	while (fgeti(fin, &value) != EOF) {
		if (value == TERMINATE_SYMBOL) {
			terminated = 1;
			break;
		}
		if (value == FILL_SYMBOL) {
			continue;
		}
		op = value & 0x3;
		addr = value & 0xfffffffc;
		if (op == OP_WRITE || op == OP_NOP) {
			argc = 1;
		} else {
			argc = 2;
		}
		if (op == OP_NOP) {
			fputc(OP_NAME[op], fout);
		} else {
			fprintf(fout, "%c " NUM_FORMAT, OP_NAME[op], addr);
		}
		for (int i=0; i<argc; ++i) {
			if (fgeti(fin, &value) == EOF) {
				fputs(" # ERROR: EOF", fout);
				err = 1;
				break;
			}
			fprintf(fout, op == OP_NOP ? " %x": "," NUM_FORMAT, value);
		}
		fputs("\r\n", fout);
	}

	fclose(fin);
	fclose(fout);

	if (err) {
		fputs("ERROR: EOF\n", stderr);
	} else if (!terminated) {
		fputs("WARN: EOF before terminal symbol\n", stderr);
	}
	return err;
}