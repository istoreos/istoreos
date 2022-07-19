#include <common.h>
#include <command.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/flash_writer_u/otp_reg.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/system.h>
#include <malloc.h>

#define SRING_SIZE 256

#if 1
#define PRINT_DEBUG printf
#else
#define PRINT_DEBUG(fmt,args...)
#endif

extern int burn_id_test(unsigned int startbyte, unsigned int totalbyte, unsigned char *src_array);
extern int read_id_test(unsigned int startbyte, unsigned int totalbyte, unsigned char *src_array);
extern int do_burn_efuse_keysel (unsigned char keysel);
extern int do_burn_efuse_secureboot (void);
extern int do_burn_efuse_mptest2 (void);
extern int do_burn_efuse_getmptest2 (void);
extern int do_burn_efuse_hwchk (unsigned char hwchk);
extern int do_burn_efuse_disonecore (void);
extern int do_burn_efuse_loadsos (void);
extern int do_burn_efuse_bootenc (void);

static unsigned int test_burn[]=
{
    0x12ff9440,0x8ec0883f,0x5481c382,0x3dba11fa
};

int do_burn_id_test(void){

    int burn_len=4; //burn len(bytes)
    unsigned char uuid_data[burn_len];
    memset(uuid_data, 0x00, burn_len);
    int start_addr=4480; //start OTP address(4096~8184 bit)
    
        printf("do_burn_id_test=%x\n",test_burn[0]);
        burn_id_test(start_addr, burn_len,(unsigned char *)test_burn);

    read_id_test(start_addr, burn_len, uuid_data);

    int i;
    for(i = 0; i < burn_len; i++) {
        printf("[%s, %d] %d: %02X(%02d)\n", __func__, __LINE__, i, uuid_data[i], uuid_data[i]);
    }
    printf("\n");
    
	return 0;
}

int do_burn_hdcp (const char * str)
{
    char *cmd = NULL;
    unsigned int image_src_addr,image_size=0;
    char * image_name=NULL;
    int rcode = CMD_RET_SUCCESS;

    if (str && (strcmp(str,"hdcp1.4")==0))
    {
        image_name=FACTORY_RO_HDCP_1_4_BIN;
    }
    else if (str && (strcmp(str,"hdcp2.1")==0))
    {
        image_name=FACTORY_RO_HDCP_2_1_BIN;
    }
    else
    {
        printf("[INFO %s] %s: failed.       hdcp file name is wrong\n", __FUNCTION__,str);
        return CMD_RET_FAILURE;
    }

    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);

    //1. upload image file
    snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    //2. write image file from DDR to facro section
    image_size = getenv_ulong("filesize", 16, 0);
    snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_src_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_FAILURE;


}

int do_burn_mac (void)
{
    char *cmd = NULL;
    unsigned int image_src_addr,image_size=0;
    char * image_name=NULL;
    int rcode = CMD_RET_SUCCESS;

    image_name=FACTORY_RO_MAC_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }

    //1. upload image file
    snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    //2. write image file from DDR to facro section
    image_size = getenv_ulong("filesize", 16, 0);
    snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_src_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_SUCCESS;


FAIL:
    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_FAILURE;

}

int do_burn_ci (void)
{
    unsigned int Kh_key[4],image_size=0;
    char *cmd = NULL;
    unsigned int image_src_addr,image_dst_addr;
    char * image_name=NULL;
    int rcode = CMD_RET_SUCCESS;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }

    image_name=FACTORY_RO_CI_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    //1. get widevine file
    snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    //2. encrpt widevine using AES ECB
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);

    Kh_key[0] = SECURE_KH_KEY0;
    Kh_key[1] = SECURE_KH_KEY1;
    Kh_key[2] = SECURE_KH_KEY2;
    Kh_key[3] = SECURE_KH_KEY3;

    image_dst_addr=image_src_addr+1*1024*1024;
#if 1     // get key off line
    rcode = AES_ECB_encrypt((unsigned char *)(uintptr_t)image_src_addr, image_size, (unsigned char *)(uintptr_t)image_dst_addr, Kh_key);
#else       // get Key on line
    rcode = AES_ECB_encrypt(hasharray+8, programmed_img_size-8-SHA256_SIZE, programmed_img_base+8, NULL);
#endif
    if( rcode )
    {
        printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt ci+ image error",rcode);
        //printf("encrypt widevine image error: %d\n", rcode);
        goto FAIL;
    }

    //3. write encrpyed widevine image to factory_ro
    snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_dst_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_FAILURE;

}


int do_burn_widevine (void)
{
    unsigned int Kh_key[4],image_size=0, image_src_addr,image_dst_addr;
    char *cmd = NULL;
    char * image_name=NULL;
    int rcode = CMD_RET_SUCCESS;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }

    image_name=FACTORY_RO_WIDEVINE_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

    //1. get widevine file
    snprintf(cmd, sizeof(cmd),"loady %x",image_src_addr);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    //2. encrpt widevine using AES ECB
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);

    Kh_key[0] = SECURE_KH_KEY0;
    Kh_key[1] = SECURE_KH_KEY1;
    Kh_key[2] = SECURE_KH_KEY2;
    Kh_key[3] = SECURE_KH_KEY3;

    image_dst_addr=image_src_addr+1*1024*1024;
#if 1     // get key off line
    rcode = AES_ECB_encrypt((unsigned char *)(uintptr_t)image_src_addr, image_size, (unsigned char *)(uintptr_t)image_dst_addr, Kh_key);
#else       // get Key on line
    rcode = AES_ECB_encrypt(hasharray+8, programmed_img_size-8-SHA256_SIZE, programmed_img_base+8, NULL);
#endif
    if( rcode )
    {
        printf("[INFO %s] %s: %d   failed. \n", __FUNCTION__,"encrypt widevine image error",rcode);
        //printf("encrypt widevine image error: %d\n", rcode);
        goto FAIL;
    }

    //3. write encrpyed widevine image to factory_ro
    snprintf(cmd, sizeof(cmd),"facro write %s %x  %x;facro save",image_name,image_dst_addr,image_size);
    PRINT_DEBUG(cmd);
    PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_SUCCESS;

FAIL:
    if (cmd)
    {
        free(cmd);
    }
    return CMD_RET_FAILURE;


}

extern int do_burn_efuse_rsa (void);
extern int do_burn_efuse_aes (otp_aes_enum_t aes_enum);
extern int do_burn_efuse_deviceID (void);
extern int do_burn_efuse_all (void);
extern int read_efuse (void);

int do_burn_efuse (const char * type)
{
    //int rcode = CMD_RET_SUCCESS;
    unsigned char keysel=0, hwchk=2;
    
    if (strcmp(type, "rsa") == 0)
    {
        return do_burn_efuse_rsa();
    }
    else if (strcmp(type, "id_test") == 0)
    {
        return do_burn_id_test();
    }
    else if (strcmp(type, "aes_ks") == 0)
    {
        return do_burn_efuse_aes(OTP_AES_KS);
    }
    else if (strcmp(type, "aes_kh") == 0)
    {
        return do_burn_efuse_aes(OTP_AES_KH);
    }
    else if (strcmp(type, "aes_kn") == 0)
    {
        return do_burn_efuse_aes(OTP_AES_KN);
    }
    else if (strcmp(type, "deviceID") == 0)
    {
        return do_burn_efuse_deviceID();
    }
    else if (strcmp(type, "keysel") == 0)
    {
        return do_burn_efuse_keysel(keysel);
    }
    else if (strcmp(type, "secureboot") == 0)
    {
        return do_burn_efuse_secureboot();
    }
    else if (strcmp(type, "mptest2") == 0)
    {
        return do_burn_efuse_mptest2();
    }
    else if (strcmp(type, "getmptest2") == 0)
    {
        return do_burn_efuse_getmptest2();
    }
    else if (strcmp(type, "hwchk") == 0)
    {
        return do_burn_efuse_hwchk(hwchk);
    }
    else if (strcmp(type, "disonecore") == 0)
    {
        return do_burn_efuse_disonecore();
    }
    else if (strcmp(type, "loadsos") == 0)
    {
        return do_burn_efuse_loadsos();
    }
    else if (strcmp(type, "bootenc") == 0)
    {
        return do_burn_efuse_bootenc();
    }
    else if (strcmp(type, "all") == 0)
    {
        return do_burn_efuse_all();
    }
    else if (strcmp(type, "test") == 0)
    {
        return read_efuse();
    }
    else
    {
        return CMD_RET_FAILURE;
    }

}


int do_burn (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{

    if (argc == 2)
    {
        if (strcmp(argv[1], "hdcp1.4") == 0)
        {
            return do_burn_hdcp("hdcp1.4");
        }

        if (strcmp(argv[1], "hdcp2.1") == 0)
        {
            return do_burn_hdcp("hdcp2.1");
        }

        else if (strcmp(argv[1], "mac") == 0)
        {
            return do_burn_mac();
        }
        else if (strcmp(argv[1], "CI+") == 0)
        {
            return do_burn_ci();
        }
        else if (strcmp(argv[1], "widevine") == 0)
        {
            return do_burn_widevine();
        }
    }
    else if (argc == 3)
    {
        if (strcmp(argv[1], "efuse") == 0)
        {
            return do_burn_efuse(argv[2]);
        }
    }


    return CMD_RET_USAGE;
}

U_BOOT_CMD
(
    burn, 3, 1,   do_burn,
    "burn image to factory via uart by rtice",
    "hdcp1.4\n"
    "burn hdcp2.1\n"
    "burn mac\n"
    "burn CI+\n"
    "burn widevine\n"
    "burn efuse rsa\n"
    "burn efuse aes\n"
    "burn efuse devideID\n"
    "burn efuse all\n"
);


