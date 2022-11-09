/*
 * Rockchip trust image generator
 *
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 * Peter, Software Engineering, <superpeter.cai@gmail.com>.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <sys/stat.h>
#include <u-boot/sha256.h>
#include "trust_merger.h"
#include "sha2.h"

/* #define DEBUG */

static bool gDebug =
#ifdef DEBUG
        true;
#else
        false;
#endif /* DEBUG */

#define LOGE(fmt, args...) fprintf(stderr, "E: [%s] " fmt, __func__, ##args)
#define LOGD(fmt, args...)                                                     \
  do {                                                                         \
    if (gDebug)                                                                \
      fprintf(stderr, "D: [%s] " fmt, __func__, ##args);                       \
  } while (0)

/* trust image has g_trust_max_num backups */
static uint32_t g_trust_max_num = 2;
static uint32_t g_trust_max_size = 2 * 1024 * 1024;

/* config sha and rsa */
#define SHA_SEL_256 3    /* little endian */
#define SHA_SEL_256_RK 2 /* big endian: only rk3368 need it */
#define SHA_SEL_160 1
#define SHA_SEL_NONE 0

#define RSA_SEL_2048_PSS 3 /* only RK3326, PX30, RK3308 */
#define RSA_SEL_2048 2     /* most platforms except above PSS */
#define RSA_SEL_1024 1
#define RSA_SEL_NONE 0

#define is_digit(c) ((c) >= '0' && (c) <= '9')

static char *gConfigPath;
static OPT_T gOpts;
#define BL3X_FILESIZE_MAX (512 * 1024)
static uint8_t gBuf[BL3X_FILESIZE_MAX];
static bool gSubfix;
static char *gLegacyPath;
static char *gNewPath;
static char *gPrePath;
static uint8_t gRSAmode = RSA_SEL_2048;
static uint8_t gSHAmode = SHA_SEL_256;
static bool gIgnoreBL32;

const uint8_t gBl3xID[BL_MAX_SEC][4] = { { 'B', 'L', '3', '0' },
	{ 'B', 'L', '3', '1' },
	{ 'B', 'L', '3', '2' },
	{ 'B', 'L', '3', '3' }
};

static inline uint32_t getBCD(uint16_t value)
{
	uint8_t tmp[2] = { 0 };
	int i;
	uint32_t ret;

	if (value > 0xFFFF) {
		return 0;
	}

	for (i = 0; i < 2; i++) {
		tmp[i] = (((value / 10) % 10) << 4) | (value % 10);
		value /= 100;
	}
	ret = ((uint16_t)(tmp[1] << 8)) | tmp[0];

	LOGD("ret:%x\n", ret);
	return ret & 0xFF;
}

static inline void fixPath(char *path)
{
	int i, len = strlen(path);
	char tmp[MAX_LINE_LEN];
	char *start, *end;

	for (i = 0; i < len; i++) {
		if (path[i] == '\\')
			path[i] = '/';
		else if (path[i] == '\r' || path[i] == '\n')
			path[i] = '\0';
	}

	if (gLegacyPath && gNewPath) {
		start = strstr(path, gLegacyPath);
		if (start) {
			end = start + strlen(gLegacyPath);
			/* Backup, so tmp can be src for strcat() */
			strcpy(tmp, end);
			/* Terminate, so path can be dest for strcat() */
			*start = '\0';
			strcat(path, gNewPath);
			strcat(path, tmp);
		} else {
			strcpy(tmp, path);
			strcpy(path, gNewPath);
			strcat(path, tmp);
		}
	} else if ((ulong)path != (ulong)gOpts.outPath && /* ignore output */
		   gPrePath && strncmp(path, gPrePath, strlen(gPrePath))) {
		strcpy(tmp, path);
		strcpy(path, gPrePath);
		strcat(path, tmp);
	}
}

static bool parseVersion(FILE *file)
{
	int d = 0;

	if (SCANF_EAT(file) != 0) {
		return false;
	}
	if (fscanf(file, OPT_MAJOR "=%d", &d) != 1)
		return false;
	gOpts.major = (uint16_t) d;
	if (SCANF_EAT(file) != 0) {
		return false;
	}
	if (fscanf(file, OPT_MINOR "=%d", &d) != 1)
		return false;
	gOpts.minor = (uint16_t) d;
	LOGD("major:%d, minor:%d\n", gOpts.major, gOpts.minor);
	return true;
}

static bool parseBL3x(FILE *file, int bl3x_id)
{
	int pos;
	int sec;
	char buf[MAX_LINE_LEN];
	bl_entry_t *pbl3x = NULL;

	if (bl3x_id >= BL_MAX_SEC) {
		return false;
	}

	pbl3x = &gOpts.bl3x[bl3x_id];

	/* SEC */
	if (SCANF_EAT(file) != 0) {
		return false;
	}
	if (fscanf(file, OPT_SEC "=%d", &sec) != 1) {
		return false;
	}
	if ((gSubfix) && (bl3x_id == BL32_SEC)) {
		if (sec == 0) {
			sec = 1;
			printf("BL3%d adjust sec from 0 to 1\n", bl3x_id);
		}
	} else if (gIgnoreBL32 && (bl3x_id == BL32_SEC)) {
		if (sec == 1) {
			sec = 0;
			printf("BL3%d adjust sec from 1 to 0\n", bl3x_id);
		}
	}
	pbl3x->sec = sec;
	LOGD("bl3%d sec: %d\n", bl3x_id, pbl3x->sec);

	/* PATH */
	if (SCANF_EAT(file) != 0) {
		return false;
	}
	memset(buf, 0, MAX_LINE_LEN);
	if (fscanf(file, OPT_PATH "=%s", buf) != 1) {
		if (pbl3x->sec)
			return false;
	} else {
		if (strlen(buf) != 0) {
			fixPath(buf);
			strcpy(pbl3x->path, buf);
			LOGD("bl3%d path:%s\n", bl3x_id, pbl3x->path);
		}
	}

	/* ADDR */
	if (SCANF_EAT(file) != 0) {
		return false;
	}
	memset(buf, 0, MAX_LINE_LEN);
	if (fscanf(file, OPT_ADDR "=%s", buf) != 1) {
		if (pbl3x->sec)
			return false;
	} else {
		if (strlen(buf) != 0) {
			pbl3x->addr = strtoul(buf, NULL, 16);
			LOGD("bl3%d addr:0x%x\n", bl3x_id, pbl3x->addr);
		}
	}

	pos = ftell(file);
	if (pos < 0) {
		return false;
	}
	if (SCANF_EAT(file) != 0) {
		return false;
	}

	return true;
}

static bool parseOut(FILE *file)
{
	if (SCANF_EAT(file) != 0) {
		return false;
	}
	if (fscanf(file, OPT_OUT_PATH "=%[^\r^\n]", gOpts.outPath) != 1)
		return false;
	/* fixPath(gOpts.outPath); */
	printf("out:%s\n", gOpts.outPath);

	return true;
}

void printOpts(FILE *out)
{
	fprintf(out, SEC_BL30 "\n" OPT_SEC "=%d\n", gOpts.bl3x[BL30_SEC].sec);
	if (gOpts.bl3x[BL30_SEC].sec) {
		fprintf(out, OPT_PATH "=%s\n", gOpts.bl3x[BL30_SEC].path);
		fprintf(out, OPT_ADDR "=0x%08x\n", gOpts.bl3x[BL30_SEC].addr);
	}

	fprintf(out, SEC_BL31 "\n" OPT_SEC "=%d\n", gOpts.bl3x[BL31_SEC].sec);
	if (gOpts.bl3x[BL31_SEC].sec) {
		fprintf(out, OPT_PATH "=%s\n", gOpts.bl3x[BL31_SEC].path);
		fprintf(out, OPT_ADDR "=0x%08x\n", gOpts.bl3x[BL31_SEC].addr);
	}

	fprintf(out, SEC_BL32 "\n" OPT_SEC "=%d\n", gOpts.bl3x[BL32_SEC].sec);
	if (gOpts.bl3x[BL32_SEC].sec) {
		fprintf(out, OPT_PATH "=%s\n", gOpts.bl3x[BL32_SEC].path);
		fprintf(out, OPT_ADDR "=0x%08x\n", gOpts.bl3x[BL32_SEC].addr);
	}

	fprintf(out, SEC_BL33 "\n" OPT_SEC "=%d\n", gOpts.bl3x[BL33_SEC].sec);
	if (gOpts.bl3x[BL33_SEC].sec) {
		fprintf(out, OPT_PATH "=%s\n", gOpts.bl3x[BL33_SEC].path);
		fprintf(out, OPT_ADDR "=0x%08x\n", gOpts.bl3x[BL33_SEC].addr);
	}

	fprintf(out, SEC_OUT "\n" OPT_OUT_PATH "=%s\n", gOpts.outPath);
}

static bool parseOpts(void)
{
	FILE *file = NULL;
	char *configPath = (gConfigPath == NULL) ? DEF_CONFIG_FILE : gConfigPath;
	bool bl30ok = false, bl31ok = false, bl32ok = false, bl33ok = false;
	bool outOk = false;
	bool versionOk = false;
	char buf[MAX_LINE_LEN];
	bool ret = false;

	file = fopen(configPath, "r");
	if (!file) {
		fprintf(stderr, "config(%s) not found!\n", configPath);
		if (configPath == (char *)DEF_CONFIG_FILE) {
			file = fopen(DEF_CONFIG_FILE, "w");
			if (file) {
				fprintf(stderr, "create defconfig\n");
				printOpts(file);
			}
		}
		goto end;
	}

	LOGD("start parse\n");

	if (SCANF_EAT(file) != 0) {
		goto end;
	}
	while (fscanf(file, "%s", buf) == 1) {
		if (!strcmp(buf, SEC_VERSION)) {
			versionOk = parseVersion(file);
			if (!versionOk) {
				LOGE("parseVersion failed!\n");
				goto end;
			}
		} else if (!strcmp(buf, SEC_BL30)) {
			bl30ok = parseBL3x(file, BL30_SEC);
			if (!bl30ok) {
				LOGE("parseBL30 failed!\n");
				goto end;
			}
		} else if (!strcmp(buf, SEC_BL31)) {
			bl31ok = parseBL3x(file, BL31_SEC);
			if (!bl31ok) {
				LOGE("parseBL31 failed!\n");
				goto end;
			}
		} else if (!strcmp(buf, SEC_BL32)) {
			bl32ok = parseBL3x(file, BL32_SEC);
			if (!bl32ok) {
				LOGE("parseBL32 failed!\n");
				goto end;
			}
		} else if (!strcmp(buf, SEC_BL33)) {
			bl33ok = parseBL3x(file, BL33_SEC);
			if (!bl33ok) {
				LOGE("parseBL33 failed!\n");
				goto end;
			}
		} else if (!strcmp(buf, SEC_OUT)) {
			outOk = parseOut(file);
			if (!outOk) {
				LOGE("parseOut failed!\n");
				goto end;
			}
		} else if (buf[0] == '#') {
			continue;
		} else {
			LOGD("unknown sec: %s!\n", buf);
			continue;
		}
		if (SCANF_EAT(file) != 0) {
			goto end;
		}
	}

	if (bl30ok && bl31ok && bl32ok && bl33ok && outOk)
		ret = true;
end:
	if (file)
		fclose(file);

	return ret;
}

bool initOpts(void)
{

	memset(&gOpts, 0, sizeof(gOpts));

	gOpts.major = DEF_MAJOR;
	gOpts.minor = DEF_MINOR;

	memcpy(&gOpts.bl3x[BL30_SEC].id, gBl3xID[BL30_SEC], 4);
	strcpy(gOpts.bl3x[BL30_SEC].path, DEF_BL30_PATH);

	memcpy(&gOpts.bl3x[BL31_SEC].id, gBl3xID[BL31_SEC], 4);
	strcpy(gOpts.bl3x[BL31_SEC].path, DEF_BL31_PATH);

	memcpy(&gOpts.bl3x[BL32_SEC].id, gBl3xID[BL32_SEC], 4);
	strcpy(gOpts.bl3x[BL32_SEC].path, DEF_BL32_PATH);

	memcpy(&gOpts.bl3x[BL33_SEC].id, gBl3xID[BL33_SEC], 4);
	strcpy(gOpts.bl3x[BL33_SEC].path, DEF_BL33_PATH);

	strcpy(gOpts.outPath, DEF_OUT_PATH);

	return parseOpts();
}

static inline bool getFileSize(const char *path, uint32_t *size)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return false;
	*size = st.st_size;
	LOGD("path:%s, size:%d\n", path, *size);
	return true;
}

void fill_file(FILE *file, char ch, uint32_t fill_size)
{
	uint8_t fill_buffer[1024];
	uint32_t cur_write;

	memset(fill_buffer, ch, 1024);
	while (fill_size > 0) {
		cur_write = (fill_size >= 1024) ? 1024 : fill_size;
		fwrite(fill_buffer, 1, cur_write, file);
		fill_size -= cur_write;
	}
}

bool filter_elf(uint32_t index, uint8_t *pMeta, uint32_t *pMetaNum,
                bool *bElf)
{
	bool ret = false;
	FILE *file = NULL;
	uint8_t *file_buffer = NULL;
	uint32_t file_size, read_size, i;
	Elf32_Ehdr *pElfHeader32;
	Elf32_Phdr *pElfProgram32;
	Elf64_Ehdr *pElfHeader64;
	Elf64_Phdr *pElfProgram64;
	bl_entry_t *pEntry = (bl_entry_t *)(pMeta + sizeof(bl_entry_t) * (*pMetaNum));
	LOGD("index=%d,file=%s\n", index, gOpts.bl3x[index].path);

	if (!getFileSize(gOpts.bl3x[index].path, &file_size))
		goto exit_fileter_elf;
	file = fopen(gOpts.bl3x[index].path, "rb");
	if (!file) {
		LOGE("open file(%s) failed\n", gOpts.bl3x[index].path);
		goto exit_fileter_elf;
	}
	file_buffer = malloc(file_size);
	if (!file_buffer)
		goto exit_fileter_elf;
	read_size = fread(file_buffer, 1, file_size, file);
	if (read_size != file_size)
		goto exit_fileter_elf;

	if (*((uint32_t *)file_buffer) != ELF_MAGIC) {
		ret = true;
		*bElf = false;
		goto exit_fileter_elf;
	}
	*bElf = true;
	if (file_buffer[5] != 1) { /* only support little endian */
		goto exit_fileter_elf;
	}
	if (*((uint16_t *)(file_buffer + EI_NIDENT)) !=
	    2) { /* only support executable case */
		goto exit_fileter_elf;
	}

	if (file_buffer[4] == 2) {
		pElfHeader64 = (Elf64_Ehdr *)file_buffer;
		for (i = 0; i < pElfHeader64->e_phnum; i++) {
			pElfProgram64 = (Elf64_Phdr *)(file_buffer + pElfHeader64->e_phoff +
			                               i * pElfHeader64->e_phentsize);
			if (pElfProgram64->p_type == 1) { /* PT_LOAD */
				pEntry->id = gOpts.bl3x[index].id;
				strcpy(pEntry->path, gOpts.bl3x[index].path);
				pEntry->size = (uint32_t) pElfProgram64->p_filesz;
				pEntry->offset = (uint32_t) pElfProgram64->p_offset;
				pEntry->align_size = DO_ALIGN(pEntry->size, ENTRY_ALIGN);
				pEntry->addr = (uint32_t) pElfProgram64->p_paddr;
				if (pEntry->align_size > BL3X_FILESIZE_MAX) {
					LOGE("elf_file %s too large,segment=%d.\n", pEntry->path, i);
					goto exit_fileter_elf;
				}
				LOGD("bl3%d: filesize = %d, imagesize = %d, segment=%d\n", index,
				     pEntry->size, pEntry->align_size, i);
				pEntry++;
				(*pMetaNum)++;
			}
		}

	} else {
		pElfHeader32 = (Elf32_Ehdr *)file_buffer;
		for (i = 0; i < pElfHeader32->e_phnum; i++) {
			pElfProgram32 = (Elf32_Phdr *)(file_buffer + pElfHeader32->e_phoff +
			                               i * pElfHeader32->e_phentsize);
			if (pElfProgram32->p_type == 1) { /* PT_LOAD */
				pEntry->id = gOpts.bl3x[index].id;
				strcpy(pEntry->path, gOpts.bl3x[index].path);
				pEntry->size = pElfProgram32->p_filesz;
				pEntry->offset = pElfProgram32->p_offset;
				pEntry->align_size = DO_ALIGN(pEntry->size, ENTRY_ALIGN);
				pEntry->addr = pElfProgram32->p_paddr;
				if (pEntry->align_size > BL3X_FILESIZE_MAX) {
					LOGE("elf_file %s too large,segment=%d.\n", pEntry->path, i);
					goto exit_fileter_elf;
				}
				LOGD("bl3%d: filesize = %d, imagesize = %d, segment=%d\n", index,
				     pEntry->size, pEntry->align_size, i);
				pEntry++;
				(*pMetaNum)++;
			}
		}
	}
	ret = true;
exit_fileter_elf:
	if (file)
		fclose(file);
	if (file_buffer)
		free(file_buffer);
	return ret;
}

#define SHA256_CHECK_SZ ((uint32_t)(256 * 1024))
static bool bl3xHash256(uint8_t *pHash, uint8_t *pData, uint32_t nDataSize)
{
	uint32_t nHashSize, nHasHashSize;

	if (!pHash || !pData || !nDataSize) {
		return false;
	}

	nHasHashSize = 0;

	if (gSHAmode == SHA_SEL_256_RK) {
		sha256_ctx ctx;

		sha256_begin(&ctx);
		while (nDataSize > 0) {
			nHashSize = (nDataSize >= SHA256_CHECK_SZ) ? SHA256_CHECK_SZ : nDataSize;
			sha256_hash(&ctx, pData + nHasHashSize, nHashSize);
			nHasHashSize += nHashSize;
			nDataSize -= nHashSize;
		}
		sha256_end(&ctx, pHash);
	} else {
		sha256_context ctx;

		sha256_starts(&ctx);
		while (nDataSize > 0) {
			nHashSize = (nDataSize >= SHA256_CHECK_SZ) ? SHA256_CHECK_SZ : nDataSize;
			sha256_update(&ctx, pData + nHasHashSize, nHashSize);
			nHasHashSize += nHashSize;
			nDataSize -= nHashSize;
		}
		sha256_finish(&ctx, pHash);
	}
	return true;
}

static bool mergetrust(void)
{
	FILE *outFile = NULL;
	uint32_t OutFileSize;
	uint32_t SrcFileNum, SignOffset, nComponentNum;
	TRUST_HEADER *pHead = NULL;
	COMPONENT_DATA *pComponentData = NULL;
	TRUST_COMPONENT *pComponent = NULL;
	bool ret = false, bElf;
	uint32_t i, n;
	uint8_t *outBuf = NULL, *pbuf = NULL, *pMetaBuf = NULL;
	bl_entry_t *pEntry = NULL;
	if (!initOpts())
		return false;

	if (gDebug) {
		printf("---------------\nUSING CONFIG:\n");
		printOpts(stdout);
		printf("---------------\n\n");
	}
	pMetaBuf = malloc(sizeof(bl_entry_t) * 32);
	if (!pMetaBuf) {
		LOGE("Merge trust image: malloc buffer error.\n");
		goto end;
	}

	nComponentNum = SrcFileNum = 0;
	for (i = BL30_SEC; i < BL_MAX_SEC; i++) {
		if (gOpts.bl3x[i].sec) {
			if (!filter_elf(i, pMetaBuf, &nComponentNum, &bElf)) {
				LOGE("filter_elf %s file failed\n", gOpts.bl3x[i].path);
				goto end;
			}
			if (!bElf) {
				pEntry = (bl_entry_t *)(pMetaBuf + sizeof(bl_entry_t) * nComponentNum);
				pEntry->id = gOpts.bl3x[i].id;
				strcpy(pEntry->path, gOpts.bl3x[i].path);
				getFileSize(pEntry->path, &pEntry->size);
				pEntry->offset = 0;
				pEntry->align_size = DO_ALIGN(pEntry->size, ENTRY_ALIGN);
				pEntry->addr = gOpts.bl3x[i].addr;
				if (pEntry->align_size > BL3X_FILESIZE_MAX) {
					LOGE("file %s too large.\n", gOpts.bl3x[i].path);
					goto end;
				}
				LOGD("bl3%d: filesize = %d, imagesize = %d\n", i, pEntry->size,
				     pEntry->align_size);
				pEntry++;
				nComponentNum++;
			}

		}
	}
	LOGD("bl3x bin sec = %d\n", nComponentNum);

	/* 2048bytes for head */
	memset(gBuf, 0, TRUST_HEADER_SIZE);

	/* Trust Head */
	pHead = (TRUST_HEADER *)gBuf;
	memcpy(&pHead->tag, TRUST_HEAD_TAG, 4);
	pHead->version = (getBCD(gOpts.major) << 8) | getBCD(gOpts.minor);
	pHead->flags = 0;
	pHead->flags |= (gSHAmode << 0);
	pHead->flags |= (gRSAmode << 4);

	SignOffset = sizeof(TRUST_HEADER) + nComponentNum * sizeof(COMPONENT_DATA);
	LOGD("trust bin sign offset = %d\n", SignOffset);
	pHead->size = (nComponentNum << 16) | (SignOffset >> 2);

	pComponent = (TRUST_COMPONENT *)(gBuf + SignOffset + SIGNATURE_SIZE);
	pComponentData = (COMPONENT_DATA *)(gBuf + sizeof(TRUST_HEADER));

	OutFileSize = TRUST_HEADER_SIZE;
	pEntry = (bl_entry_t *)pMetaBuf;
	for (i = 0; i < nComponentNum; i++) {
		/* bl3x load and run address */
		pComponentData->LoadAddr = pEntry->addr;

		pComponent->ComponentID = pEntry->id;
		pComponent->StorageAddr = (OutFileSize >> 9);
		pComponent->ImageSize = (pEntry->align_size >> 9);
		pComponentData->LoadSize = pComponent->ImageSize;

		LOGD("bl3%c: LoadAddr = 0x%08x, StorageAddr = %d, ImageSize = %d\n",
		     (char)((pEntry->id & 0xFF000000) >> 24), pComponentData->LoadAddr,
		     pComponent->StorageAddr, pComponent->ImageSize);

		OutFileSize += pEntry->align_size;
		pComponentData++;
		pComponent++;
		pEntry++;
	}

	/* create out file */
	outFile = fopen(gOpts.outPath, "wb+");
	if (!outFile) {
		LOGE("open out file(%s) failed\n", gOpts.outPath);

		outFile = fopen(DEF_OUT_PATH, "wb");
		if (!outFile) {
			LOGE("open default out file:%s failed!\n", DEF_OUT_PATH);
			goto end;
		}
	}

	/* 0 for g_trust_max_num backups */
#if 0
	/* save trust head to out file */
	if (!fwrite(gBuf, TRUST_HEADER_SIZE, 1, outFile))
		goto end;

	/* save trust bl3x bin */
	for (i = BL30_SEC; i < BL_MAX_SEC; i++) {
		if (gOpts.bl3x[i].sec) {
			FILE *inFile = fopen(gOpts.bl3x[i].path, "rb");
			if (!inFile)
				goto end;

			memset(gBuf, 0, imagesize[i]);
			if (!fread(gBuf, filesize[i], 1, inFile))
				goto end;
			fclose(inFile);

			if (!fwrite(gBuf, imagesize[i], 1, outFile))
				goto end;
		}
	}
#else
	/* check bin size */
	if (OutFileSize > g_trust_max_size) {
		LOGE("Merge trust image: trust bin size overfull.\n");
		goto end;
	}

	/* malloc buffer */
	pbuf = outBuf = calloc(g_trust_max_size, g_trust_max_num);
	if (!outBuf) {
		LOGE("Merge trust image: calloc buffer error.\n");
		goto end;
	}
	memset(outBuf, 0, (g_trust_max_size * g_trust_max_num));

	/* save trust head data */
	memcpy(pbuf, gBuf, TRUST_HEADER_SIZE);
	pbuf += TRUST_HEADER_SIZE;

	uint8_t *pHashData = NULL;
	pComponentData = (COMPONENT_DATA *)(outBuf + sizeof(TRUST_HEADER));

	/* save trust bl3x bin */
	pEntry = (bl_entry_t *)pMetaBuf;
	for (i = 0; i < nComponentNum; i++) {
		FILE *inFile = fopen(pEntry->path, "rb");
		if (!inFile)
			goto end;

		memset(gBuf, 0, pEntry->align_size);
		fseek(inFile, pEntry->offset, SEEK_SET);
		if (!fread(gBuf, pEntry->size, 1, inFile))
			goto end;
		fclose(inFile);

		/* bl3x bin hash256 */
		pHashData = (uint8_t *)&pComponentData->HashData[0];
		bl3xHash256(pHashData, gBuf, pEntry->align_size);
		memcpy(pbuf, gBuf, pEntry->align_size);

		pComponentData++;
		pbuf += pEntry->align_size;
		pEntry++;
	}

	/* copy other (g_trust_max_num - 1) backup bin */
	for (n = 1; n < g_trust_max_num; n++) {
		memcpy(outBuf + g_trust_max_size * n, outBuf, g_trust_max_size);
	}

	/* save date to file */
	if (!fwrite(outBuf, g_trust_max_size * g_trust_max_num, 1, outFile)) {
		LOGE("Merge trust image: write file error.\n");
		goto end;
	}
#endif

	ret = true;

end:
	/*
		for (i = BL30_SEC; i < BL_MAX_SEC; i++) {
			if (gOpts.bl3x[i].sec != false) {
				if (gOpts.bl3x[i].is_elf) {
					if (stat(gOpts.bl3x[i].path, &st) >= 0)
						remove(gOpts.bl3x[i].path);
				}
			}
		}
	*/
	if (pMetaBuf)
		free(pMetaBuf);
	if (outBuf)
		free(outBuf);
	if (outFile)
		fclose(outFile);
	return ret;
}

static int saveDatatoFile(char *FileName, void *pBuf, uint32_t size)
{
	FILE *OutFile = NULL;
	int ret = -1;

	OutFile = fopen(FileName, "wb");
	if (!OutFile) {
		printf("open OutPutFlie:%s failed!\n", FileName);
		goto end;
	}
	if (1 != fwrite(pBuf, size, 1, OutFile)) {
		printf("write output file failed!\n");
		goto end;
	}

	ret = 0;
end:
	if (OutFile)
		fclose(OutFile);

	return ret;
}

static bool unpacktrust(char *path)
{
	FILE *FileSrc = NULL;
	uint32_t FileSize;
	uint8_t *pBuf = NULL;
	uint32_t SrcFileNum, SignOffset;
	TRUST_HEADER *pHead = NULL;
	COMPONENT_DATA *pComponentData = NULL;
	TRUST_COMPONENT *pComponent = NULL;
	char str[MAX_LINE_LEN];
	bool ret = false;
	uint32_t i;

	FileSrc = fopen(path, "rb");
	if (FileSrc == NULL) {
		printf("open %s failed!\n", path);
		goto end;
	}

	if (getFileSize(path, &FileSize) == false) {
		printf("File Size failed!\n");
		goto end;
	}
	printf("File Size = %d\n", FileSize);

	pBuf = (uint8_t *)malloc(FileSize);
	if (1 != fread(pBuf, FileSize, 1, FileSrc)) {
		printf("read input file failed!\n");
		goto end;
	}

	pHead = (TRUST_HEADER *)pBuf;

	memcpy(str, &pHead->tag, 4);
	str[4] = '\0';
	printf("Header Tag:%s\n", str);
	printf("Header version:%d\n", pHead->version);
	printf("Header flag:%d\n", pHead->flags);

	SrcFileNum = (pHead->size >> 16) & 0xffff;
	SignOffset = (pHead->size & 0xffff) << 2;
	printf("SrcFileNum:%d\n", SrcFileNum);
	printf("SignOffset:%d\n", SignOffset);

	pComponent = (TRUST_COMPONENT *)(pBuf + SignOffset + SIGNATURE_SIZE);
	pComponentData = (COMPONENT_DATA *)(pBuf + sizeof(TRUST_HEADER));

	for (i = 0; i < SrcFileNum; i++) {
		printf("Component %d:\n", i);

		memcpy(str, &pComponent->ComponentID, 4);
		str[4] = '\0';
		printf("ComponentID:%s\n", str);
		printf("StorageAddr:0x%x\n", pComponent->StorageAddr);
		printf("ImageSize:0x%x\n", pComponent->ImageSize);
		printf("LoadAddr:0x%x\n", pComponentData->LoadAddr);

		saveDatatoFile(str, pBuf + (pComponent->StorageAddr << 9),
		               pComponent->ImageSize << 9);

		pComponentData++;
		pComponent++;
	}

	ret = true;
end:
	if (FileSrc)
		fclose(FileSrc);
	if (pBuf)
		free(pBuf);

	return ret;
}

static void printHelp(void)
{
	printf("Usage: trust_merger [options]... FILE\n");
	printf(
	        "Merge or unpack Rockchip's trust image (Default action is to merge.)\n");
	printf("Options:\n");
	printf("\t" OPT_MERGE "\t\t\tMerge trust with specified config.\n");
	printf("\t" OPT_UNPACK "\t\tUnpack specified trust to current dir.\n");
	printf("\t" OPT_VERBOSE "\t\tDisplay more runtime informations.\n");
	printf("\t" OPT_HELP "\t\t\tDisplay this information.\n");
	printf("\t" OPT_VERSION "\t\tDisplay version information.\n");
	printf("\t" OPT_SUBFIX "\t\tSpec subfix.\n");
	printf("\t" OPT_REPLACE "\t\tReplace some part of binary path.\n");
	printf("\t" OPT_PREPATH "\t\tAdd prefix path of binary path.\n");
	printf("\t" OPT_RSA "\t\t\tRSA mode.\"--rsa [mode]\", [mode] can be: "
	       "0(none), 1(1024), 2(2048), 3(2048 pss).\n");
	printf("\t" OPT_SHA
	       "\t\t\tSHA mode.\"--sha [mode]\", [mode] can be: 0(none), 1(160), "
	       "2(256 RK big endian), 3(256 little endian).\n");
	printf("\t" OPT_SIZE "\t\t\tTrustImage size.\"--size [per image KB size] "
	       "[copy count]\", per image must be 64KB aligned\n");
}

int main(int argc, char **argv)
{
	bool merge = true;
	char *optPath = NULL;
	int i;

	gConfigPath = NULL;
	for (i = 1; i < argc; i++) {
		if (!strcmp(OPT_VERBOSE, argv[i])) {
			gDebug = true;
		} else if (!strcmp(OPT_HELP, argv[i])) {
			printHelp();
			return 0;
		} else if (!strcmp(OPT_VERSION, argv[i])) {
			printf("trust_merger (cwz@rock-chips.com)\t" VERSION "\n");
			return 0;
		} else if (!strcmp(OPT_MERGE, argv[i])) {
			merge = true;
		} else if (!strcmp(OPT_UNPACK, argv[i])) {
			merge = false;
		} else if (!strcmp(OPT_SUBFIX, argv[i])) {
			gSubfix = true;
			printf("trust_merger: Spec subfix!\n");
		} else if (!strcmp(OPT_REPLACE, argv[i])) {
			i++;
			gLegacyPath = argv[i];
			i++;
			gNewPath = argv[i];
		} else if (!strcmp(OPT_PREPATH, argv[i])) {
			i++;
			gPrePath = argv[i];
		} else if (!strcmp(OPT_RSA, argv[i])) {
			i++;
			if (!is_digit(*(argv[i]))) {
				printHelp();
				return -1;
			}
			gRSAmode = *(argv[i]) - '0';
			LOGD("rsa mode:%d\n", gRSAmode);
		} else if (!strcmp(OPT_SHA, argv[i])) {
			i++;
			if (!is_digit(*(argv[i]))) {
				printHelp();
				return -1;
			}
			gSHAmode = *(argv[i]) - '0';
			LOGD("sha mode:%d\n", gSHAmode);
		} else if (!strcmp(OPT_SIZE, argv[i])) {
			/* Per trust image size */
			g_trust_max_size = strtoul(argv[++i], NULL, 10);
			/*
			 * Usually, it must be at 512kb align due to preloader
			 * detects every 512kb. But some product has critial
			 * flash size requirement, we have to make it small than
			 * 512KB.
			 */
			if (g_trust_max_size % 64) {
				printHelp();
				return -1;
			}
			g_trust_max_size *= 1024; /* bytes */

			/* Total backup numbers */
			g_trust_max_num = strtoul(argv[++i], NULL, 10);
		} else if (!strcmp(OPT_IGNORE_BL32, argv[i])) {
			gIgnoreBL32 = true;
		} else {
			if (optPath) {
				fprintf(stderr, "only need one path arg, but we have:\n%s\n%s.\n",
				        optPath, argv[i]);
				printHelp();
				return -1;
			}
			optPath = argv[i];
		}
	}
	if (!merge && !optPath) {
		fprintf(stderr, "need set out path to unpack!\n");
		printHelp();
		return -1;
	}

	if (merge) {
		LOGD("do_merge\n");
		gConfigPath = optPath;
		if (!mergetrust()) {
			fprintf(stderr, "merge failed!\n");
			return -1;
		}
		printf("merge success(%s)\n", gOpts.outPath);
	} else {
		LOGD("do_unpack\n");
		if (!unpacktrust(optPath)) {
			fprintf(stderr, "unpack failed!\n");
			return -1;
		}
		printf("unpack success\n");
	}

	return 0;
}
