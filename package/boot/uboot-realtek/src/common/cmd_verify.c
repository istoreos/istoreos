#include <common.h>
#include <command.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/system.h>
#include <malloc.h>

#if 1
#define PRINT_DEBUG printf
#else
#define PRINT_DEBUG(fmt,args...)
#endif
#define SRING_SIZE 256


int do_verify_hdcp (const char * str)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);


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

    snprintf(cmd, sizeof(cmd),"facro read %s %x",image_name,image_src_addr);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    image_size = getenv_ulong("filesize", 16, 0);
    snprintf(cmd, sizeof(cmd),"md.b %x %x;",image_src_addr,image_size);    
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
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

int do_verify_mac (void)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);

    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    image_name=FACTORY_RO_MAC_BIN;
    snprintf(cmd, sizeof(cmd),"facro read %s %x",image_name,image_src_addr);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }

    image_size = getenv_ulong("filesize", 16, 0);
    snprintf(cmd, sizeof(cmd),"md.b %x %x;",image_src_addr,image_size);    
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
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

int do_verify_ci (void)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_dst_addr;
    unsigned int Kh_key[4],image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);
    
    // 1. read image from  factory_ro to DDR    
    image_name=FACTORY_RO_CI_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    snprintf(cmd, sizeof(cmd),"facro read %s %x",image_name,image_src_addr);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }
    
    // 2. decrypt images in DDR
    Kh_key[0] = SECURE_KH_KEY0;
    Kh_key[1] = SECURE_KH_KEY1;
    Kh_key[2] = SECURE_KH_KEY2;
    Kh_key[3] = SECURE_KH_KEY3;
    image_dst_addr=image_src_addr+0x100000;
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);
    rcode = AES_ECB_decrypt((unsigned char *)(uintptr_t)image_src_addr, image_size, (unsigned char *)(uintptr_t)image_dst_addr, Kh_key);
    if( rcode )
    {
        printf("decrypt CI+ image error: %d\n", rcode);
        goto FAIL;
    }
    
    //3. dump decrypted CI+ image in DDR
    snprintf(cmd, sizeof(cmd),"md.b %x  %x;",(unsigned int)image_dst_addr,image_size);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
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


int do_verify_widevine (void)
{
    char * image_name=NULL;
    char *cmd = NULL;
    int rcode = CMD_RET_SUCCESS;
    unsigned int image_src_addr,image_dst_addr;
    unsigned int Kh_key[4],image_size=0;

    cmd=(char *)malloc(SRING_SIZE);
    if (!cmd)
    {
        return CMD_RET_FAILURE;
    }
    memset(cmd, 0, SRING_SIZE);
    
    // 1. read image from  factory_ro to DDR    
    image_name=FACTORY_RO_WIDEVINE_BIN;
    image_src_addr=TEMP_BUFFER_FOR_FLASH_DATA_ADDR;
    snprintf(cmd, sizeof(cmd),"facro read %s %x",image_name,image_src_addr);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
    rcode=run_command(cmd,0);
    if (rcode != 0)
    {
        printf("[INFO %s] %s: failed. \n", __FUNCTION__,cmd);
        goto FAIL;
    }
    
    // 2. decrypt images in DDR
    Kh_key[0] = SECURE_KH_KEY0;
    Kh_key[1] = SECURE_KH_KEY1;
    Kh_key[2] = SECURE_KH_KEY2;
    Kh_key[3] = SECURE_KH_KEY3;
    image_dst_addr=image_src_addr+0x100000;
    image_size = getenv_ulong("filesize", 16, 0);
    printf("image_size=%d       %x\n",image_size,image_size);
    rcode = AES_ECB_decrypt((unsigned char *)(uintptr_t)image_src_addr, image_size, (unsigned char *)(uintptr_t)image_dst_addr, Kh_key);
    if( rcode )
    {
        printf("decrypt widevine image error: %d\n", rcode);
        goto FAIL;
    }
    
    //3. dump decrypted CI+ image in DDR
    snprintf(cmd, sizeof(cmd),"md.b %x  %x;",(unsigned int)image_dst_addr,image_size);
    PRINT_DEBUG(cmd);PRINT_DEBUG("\n");
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


int do_verify (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    if (argc == 2)
    {
        if ( strcmp(argv[1], "hdcp1.4") == 0)
        {
            return do_verify_hdcp("hdcp1.4");
        }
        else if ( strcmp(argv[1], "hdcp2.1") == 0)
        {
            return do_verify_hdcp("hdcp2.1");
        }
        else if ( strcmp(argv[1], "mac") == 0)
        {
            return do_verify_mac();
        }
        else if (strcmp(argv[1], "CI+") == 0)
        {
            return do_verify_ci();
        }
        else if (strcmp(argv[1], "widevine") == 0)
        {
            return do_verify_widevine();
        }
    }

    return CMD_RET_USAGE;
}

U_BOOT_CMD
(
    verify, 2, 1,   do_verify,
    "verify image in factory",
    "hdcp1.4\n"
    "verify hdcp2.1\n"
    "verify mac\n"
    "verify CI+\n"
    "verify widevine"
);



