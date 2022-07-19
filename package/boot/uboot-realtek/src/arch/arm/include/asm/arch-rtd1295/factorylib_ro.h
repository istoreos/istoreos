#ifndef __FACTORY_LIB_READ_ONLY_H__
#define __FACTORY_LIB_READ_ONLY_H__

#ifndef CONFIG_FACTORY_RO_START
#define CONFIG_FACTORY_RO_START	0x1000000	/* For eMMC */
#endif
#ifndef CONFIG_FACTORY_RO_SIZE
#define CONFIG_FACTORY_RO_SIZE	0x10000		/* For eMMC */
#endif

#define FACTORY_RO_HEADER_FILE_NAME		"tmp/factory_ro/"

#define FACTORY_RO_HDCP_1_4_BIN			FACTORY_RO_HEADER_FILE_NAME"hdcp1.4.bin"
#define FACTORY_RO_HDCP_2_1_BIN			FACTORY_RO_HEADER_FILE_NAME"hdcp2.1.bin"
#define FACTORY_RO_HDCP_BIN			FACTORY_RO_HEADER_FILE_NAME"hdcp.bin"


#define FACTORY_RO_MAC_BIN		FACTORY_RO_HEADER_FILE_NAME"mac.bin"
#define FACTORY_RO_WIDEVINE_BIN		FACTORY_RO_HEADER_FILE_NAME"widevine.bin"
#define FACTORY_RO_CI_BIN			FACTORY_RO_HEADER_FILE_NAME"CI.bin"

int factory_ro_dump_info(void);
int factory_ro_reset(void);
int factory_ro_delete(char *path);
int factory_ro_read_by_index(int index, char *buffer, int *length, char *name);
int factory_ro_read(char *path, char**buffer, int *length);
int factory_ro_write(char *path, char *buffer, int length);
int factory_ro_save(void);
int factory_ro_init(void);

#endif /* __FACTORY_LIB_READ_ONLY_H__ */

