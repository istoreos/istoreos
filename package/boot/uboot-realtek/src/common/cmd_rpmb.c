#include "common.h"
#include "command.h" 
#include <exports.h>
#include <u-boot/sha256.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include "mmc.h"
#include <asm/arch/rtkemmc.h>


#define KS_START   		 0x98017100
#define OTP_KS 	          2048
#define KF_LEN	          16
#define TRNG_REG_BASE           0x9801aa00
#define RNG_CTRL				TRNG_REG_BASE
#define RNG_CALI_CHK            (TRNG_REG_BASE + 0x18)
#define RNG_ANA                 (TRNG_REG_BASE + 0x14)
#define RNG_LOCK_CHK            (TRNG_REG_BASE + 0x24)
#define RNG_RETURN3             (TRNG_REG_BASE + 0x2c)
#define RNG_RETURN4             (TRNG_REG_BASE + 0x30)
#define RNG_RESULTR             (TRNG_REG_BASE + 0x38)
#define MAX_1MS_TO_CNT          1000

typedef enum STATE{
	EXIT_SUCCESS =0,
	EXIT_FAILURE ,
}OPS_STATE;



#define TEST_AND_RETURN_FALSE(_x)                     \
  do {                                                \
     int con= (_x);                              \
    if (con != EXIT_SUCCESS) {                          \
    	printf(" %s fail !!\n",#_x);              \
      return false;                                      \
    }                                                    \
  } while (0)

/* Sizes of RPMB data frame */
#define RPMB_SZ_STUFF		196
#define RPMB_SZ_MAC		    32
#define RPMB_SZ_DATA		256
#define RPMB_SZ_NONCE		16

#define SHA256_BLOCK_SIZE	64

/* Request codes */
#define RPMB_REQ_KEY		1
#define RPMB_REQ_WCOUNTER	2
#define RPMB_REQ_WRITE_DATA	3
#define RPMB_REQ_READ_DATA	4
#define RPMB_REQ_STATUS		5

/* Response code */
#define RPMB_RESP_KEY			0x0100
#define RPMB_RESP_WCOUNTER		0x0200
#define RPMB_RESP_WRITE_DATA	0x0300
#define RPMB_RESP_READ_DATA		0x0400


//#define KS_OFFSET            2048
#define KF_OFFSET			 4736
#define HASH_BLOCK_SIZE      64
#define RPMB_EMMC_CID_SIZE   16
#define SHA256_DIGEST_SIZE   32


/* Error messages */
static const char * const rpmb_err_msg[] = {
	"",
	"General failure",
	"Authentication failure",
	"Counter failure",
	"Address failure",
	"Write failure",
	"Read failure",
	"Authentication key not yet programmed",
};


/* Error codes */
#define RPMB_OK					0
#define RPMB_ERR_GENERAL		1
#define RPMB_ERR_AUTH			2
#define RPMB_ERR_COUNTER		3
#define RPMB_ERR_ADDRESS		4
#define RPMB_ERR_WRITE			5
#define RPMB_ERR_READ			6
#define RPMB_ERR_KEY			7
#define RPMB_ERR_CNT_EXPIRED	0x80
#define RPMB_ERR_MSK			0x7

/*******************declearation******************************/

#define KF_LEN 16
#define ISB __asm__ volatile("isb" ::: "memory")
#define RESULT_ERROR_MASK 0x7

#define RPMB_EMMC_CID_SIZE 16
#define MAX_DESCRIPTOR_NUM    (8)
#define EMMC_MAX_SCRIPT_BLK   (8)
#define EMMC_MAX_MULTI_BLK    (EMMC_MAX_SCRIPT_BLK * MAX_DESCRIPTOR_NUM)
#define wait_done(_a, _m, _v) __wait_done(U64_PTR(_a), _m, _v)
#define uswap_32(x) \
		( (((x) & 0xff000000)>>24) | \
		  (((x) & 0x00ff0000)>>8 ) | \
		  (((x) & 0x0000ff00)<<8 ) | \
		  (((x) & 0x000000ff)<<24) )

#define uswap_16(x) \
	( (((x) & 0xff00)>>8) | \
	  (((x) & 0x00ff)<<8)  )

#define SWITCH_ERROR            (1<<7)

/******************global variables***********************/
unsigned char ks[16]={0};
				

//unsigned char emmc_cid[16]={0};
unsigned char key_pad_to_64[64]={0};
unsigned char first_step_key[64]={0};
unsigned char second_step_key[64]={0};
unsigned char rpmb_key[32] ={0};
static unsigned int emmc_rca = (1<<16);  //emmc address
static unsigned int * rw_descriptor  = NULL;

static void __wait_done(volatile unsigned int *addr, unsigned int mask, unsigned int value){	
	int n = 0;	
	while (((*addr) & mask) != value)  {		
		if(n++ > 0x1000) {			
			printf("TIMEOUT\n");	
			printf("%s: addr=0x%08x, mask=0x%08x, value=0x%08x\n",__func__, PTR_U32(addr), mask, value);		
			break;
		}

		mdelay(1);
		sync();	
	}
}


//function declaration
extern int OTP_Get_Byte(int offset, unsigned char *ptr, unsigned int cnt);
static int Calculate_RPMB_key(unsigned char *rpmb_key);
static OPS_STATE emmc_rpmb_counter(unsigned int *pwcount);



enum operation {
	MMC_RPMB_WRITE_EN =0,
	MMC_RPMB_WRITE_RAW,
	MMC_RPMB_READ_DE,
	MMC_RPMB_READ_RAW,
	MMC_RPMB_COUNTER,
	MMC_RPMB_BURN,
	MMC_INVALID,
};

/*static void dump_hex(unsigned char* pData, unsigned short Len)
{
	int i ;
	for (i=0; i<Len; i++)									
		printf("%02x", pData[i]);									 
	printf("\n");											 
}*/

struct rpmb_operation{

	//switch to corresponding place
	 OPS_STATE (*switch_partition)(int num);

	/* it's different from normal write operation
	 * |buff| 	 : data source
	 * |block|   : destination
	 * |count|   : how many blocks to write
	 * |Encrypt| : whether use key to encrypt
	 */
	 OPS_STATE (*write_block)(void* buff,uint block,uint count,bool Encrypt);

	
	/* it's different from normal read operation
	 * |buff| 	 : destination
	 * |block|   : source
	 * |count|   : how many blocks to write
	 * |Decrypt| : whether use key to decrypt,for the data in rpmb area is encrypted
	 */	 
	 OPS_STATE (*read_blcok)(void * buff ,uint block , uint count, bool Decrypt);


	/* Counter value for the total amount of successful authenticated
	 * data write requests and Authenticated Device Configuration 
	 * write request made by the host.
	 */
	 OPS_STATE (*get_counter)(unsigned int * pwcount);


	/*  burn rpmb key calculated by kf and cid
	 *  can only burn once !!!!
	 */
	 OPS_STATE (*burn_key)(void);

};

/* Structure of RPMB data frame. */
struct s_rpmb {                          //512 bytes
	unsigned char stuff[RPMB_SZ_STUFF];
	unsigned char mac[RPMB_SZ_MAC];
	unsigned char data[RPMB_SZ_DATA];
	unsigned char nonce[RPMB_SZ_NONCE];
	unsigned long write_counter;
	unsigned short address;
	unsigned short block_count;
	unsigned short result;
	unsigned short request;
};

static int emmc_rpmb_request(struct s_rpmb * rpmb_frame,int count ,bool reliable);
static int emmc_rpmb_response(struct s_rpmb * rpmb_frame,unsigned short expected);
static void make_ip_des_rpmb(const unsigned char *dma_addr, unsigned int dma_length);

#if 0
static int mmc_set_blockcount(struct mmc* mmc , unsigned int block_count ,bool is_rel_write){
	
	//refer to Jedec ,we should set block count 1 via cmd23,after we can use cmd 25
	struct mmc_cmd cmd23={0};
	cmd23.opcode = MMC_CMD_SET_BLOCK_COUNT;
	cmd23.arg = (block_count & 0xFF) ;

	if(is_rel_write){
		cmd23.arg |= (1<<31);	
	}

	
	cmd23.flags = MMC_RSP_R1;

	//printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	//printf("after rel write cmd23's arg is 0x%x\n",cmd23.arg);

	//return rtkemmc_request(mmc , &cmd23 , NULL);
	return cmd23_request(mmc , &cmd23 , NULL);

}
#endif

#if 0
static int mmc_rpmb_request(struct mmc *mmc ,struct s_rpmb * rpmb_request ,unsigned int count ,bool is_rel_write){ 

	struct mmc_cmd cmd25 = {0};
	struct mmc_data data = {{0},0,0,0};
	int ret = -1;
	
	//printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	ret = mmc_set_blockcount(mmc , count , is_rel_write);
	if(ret){
		printf("mmc_set_blockcount fail\n");
		return EXIT_FAILURE;
	}

	cmd25.opcode = MMC_CMD_WRITE_MULTIPLE_BLOCK;
	cmd25.arg = 0; //write address
	cmd25.flags = MMC_RSP_R1B;

/**********cmd and data is separated**********/
	data.src =(const char *) rpmb_request; //attention
	data.blocks = 1;
	data.blocksize = MMC_MAX_BLOCK_LEN;
	data.flags = MMC_DATA_WRITE;


	ret = cmd25_request(mmc , &cmd25 , &data);
	if(ret){
		printf("cmd 25 fail\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
									
}
#endif


#if 0
static int mmc_rpmb_response(struct mmc *mmc,
							        struct s_rpmb * rpmb_frame,
							        unsigned short expected){//0x0100
		struct mmc_cmd cmd18={0};
		struct mmc_data data={{0},0,0,0};
		int ret =-1;

		//printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);

		ret = mmc_set_blockcount( mmc,1,false);
		if(ret){
		printf("mmc_set_blockcount fail\n");
		return EXIT_FAILURE;
		}

		cmd18.opcode = MMC_CMD_READ_MULTIPLE_BLOCK;
		cmd18.arg = 0;
		cmd18.flags = MMC_RSP_R1;

		data.src =(const char *) rpmb_frame;
		data.blocks =1;
		data.blocksize = MMC_MAX_BLOCK_LEN;
		data.flags = MMC_DATA_READ;
	
		memcpy((void*)0x200000,0,0x200); //clear rpmb frame to see clean consequence
		if(cmd18_request(mmc, &cmd18 , &data)){
			printf("send cmd 18  fail\n");
			return EXIT_FAILURE;
	    }
		
		//printf("result is 0x%x\n",be16_to_cpu(rpmb_frame->result));
		//printf("response is 0x%x\n",be16_to_cpu(rpmb_frame->request));
		//printf("expected  0x%x\n",expected);

		//if(be16_to_cpu(rpmb_frame ->result)){ //non zero means failure
			/*print result*/
	//		printf("%s\n",rpmb_err_msg[be16_to_cpu(rpmb_frame->result) & RPMB_ERR_MSK] );
	//		return -1;
	//	}

	//	if(be16_to_cpu(rpmb_frame->request) != expected){ 
   	//		printf("response is %d\n",be16_to_cpu(rpmb_frame->request) );			
	//		printf("response not equal to expected\n");
	//		return -1;
		//}

		return EXIT_SUCCESS; //run here means program success
		
}
#endif


#if 0
static  OPS_STATE emmc_switch_partition(int part_num){
	printf("switch 1\n");
	int error = -1;
    error = mmc_switch_part(0,part_num);
		printf("switch 2\n");

	if( 0 == error ){
		printf("switch success\n");
		return EXIT_SUCCESS;
	}else{
		printf("switch error\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
#endif


static OPS_STATE emmc_switch_partition(int part_num){
	/*switch to partition,we should check response by MMC_SEND_STATUS	
	 * MMC_SWITCH_MODE_WRITE_BYTE <<24 |	 
	 *EXT_CSD_PART_CONF<<16 |
	 * part_num << 8 |	
	 * 1 <<0	
	 */
	emmc_send_cmd_get_rsp(MMC_SWITCH, 				
						((MMC_SWITCH_MODE_WRITE_BYTE<<24)|(EXT_CSD_PART_CONF<<16) | ((part_num & PART_ACCESS_MASK)<<8)|(1<<0)) ,					
	 			        1,				
	 			        1);
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS,emmc_rca,1,1);

	CP15ISB;

	if( (cr_readl(CR_EMMC_RESP0) & SWITCH_ERROR) ==1){
		printf("switch fail\n");
		return EXIT_FAILURE;
	}
	else if( (cr_readl(CR_EMMC_RESP0) & SWITCH_ERROR) ==0){ 
		printf("switch success\n");
		return EXIT_SUCCESS;
	}
	else{
		printf("can't get response\n");
		return EXIT_FAILURE;
	}
}


static int Calculate_RPMB_Hmac(unsigned char * key,
			   	     					 unsigned char * buff,
										 int len,
										 unsigned char * output){
	sha256_context ctx;
	int i;
	unsigned char k_ipad[SHA256_BLOCK_SIZE];
	unsigned char k_opad[SHA256_BLOCK_SIZE];

	sha256_starts(&ctx);

	/* According to RFC 4634, the HMAC transform looks like:
	   SHA(K XOR opad, SHA(K XOR ipad, text))

	   where K is an n byte key.
	   ipad is the byte 0x36 repeated blocksize times
	   opad is the byte 0x5c repeated blocksize times
	   and text is the data being protected.
	*/

	for (i = 0; i < RPMB_SZ_MAC; i++) {
		k_ipad[i] = key[i] ^ 0x36;
		k_opad[i] = key[i] ^ 0x5c;
	}
	/* remaining pad bytes are '\0' XOR'd with ipad and opad values */
	for ( ; i < SHA256_BLOCK_SIZE; i++) {
		k_ipad[i] = 0x36;
		k_opad[i] = 0x5c;
	}
	sha256_update(&ctx, k_ipad, SHA256_BLOCK_SIZE);
	sha256_update(&ctx, buff, len);
	sha256_finish(&ctx, output);

	/* Init context for second pass */
	sha256_starts(&ctx);

	/* start with outer pad */
	sha256_update(&ctx, k_opad, SHA256_BLOCK_SIZE);

	/* then results of 1st hash */
	sha256_update(&ctx, output, RPMB_SZ_MAC);

	/* finish up 2nd pass */
	sha256_finish(&ctx, output);
	return EXIT_SUCCESS;
						 
}

#if 0
static  OPS_STATE rtk_rpmb_write_block( void *buff , uint block , uint count, bool Encrypt){

	struct mmc *mmc = find_mmc_device(0);
	/* some variable */
	unsigned char rpmb_key[32]={0}; 	
	unsigned int index=0;		
	unsigned int write_counter=0;	
	
	
	/* reset the pointer */
	MY_CLR_ALIGN_BUFFER(); //for align
	
	/* alloc rpmb frame */
	MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame, 0x01); //512 bytes
	
	
	/* calculate rpmb key */	
	Calculate_RPMB_key(rpmb_key);	
	
	/* data loop */
	for(index=0 ; index < count;index++){		
	
		/* get write counter */ 	
		emmc_rpmb_counter(& write_counter); 		
		
		memcpy( rpmb_frame->data , buff+index * RPMB_SZ_DATA , RPMB_SZ_DATA ); 
		
		rpmb_frame->request 	  = cpu_to_be16(RPMB_REQ_WRITE_DATA);		
		rpmb_frame->address 	  = cpu_to_be16(block+index);		
		rpmb_frame->block_count   = cpu_to_be16(1); 		
		rpmb_frame->write_counter = cpu_to_be32(write_counter); 
	
		
		/* calculate Hmac */		
		Calculate_RPMB_Hmac(rpmb_key,rpmb_frame->data,284,rpmb_frame->mac); 
	
		/* send request */
		if (mmc_rpmb_request(mmc, rpmb_frame, 1, true)){ //must true
			printf("%s : Line %d: func:%s fail\n", __FILE__, __LINE__,__func__);
			break;
		}
	
		/* get status */
		/*if(mmc_rpmb_status(mmc,RPMB_RESP_WRITE_DATA)){
			printf("%s : Line %d: func:%s fail\n", __FILE__, __LINE__,__func__);
			break;
		}*/
		
		memset(rpmb_frame , 0 , sizeof(struct s_rpmb));
		rpmb_frame->request = cpu_to_be16(RPMB_REQ_STATUS); 
		if(mmc_rpmb_request( mmc, rpmb_frame,1 ,false)){			
			printf("rpmb request fail\n");
			break;
		}
		
		if(mmc_rpmb_response(mmc , rpmb_frame , RPMB_RESP_WRITE_DATA)){
			printf("rpmb response fail\n");
			break;
		}
		
		if(cpu_to_be16(rpmb_frame ->result)){	//non zero means failure
			break;
		}	
	}
	
	/* whether succeed */
	if(index==count){	
		printf("%d blocks write done\n",index); 
		return EXIT_SUCCESS;
	}else{		
		printf("rpmb write fail at %d\n",index);	
		return EXIT_FAILURE;
	}	
	
	return EXIT_FAILURE;
}
#endif

static OPS_STATE rtk_rpmb_write_block( void *buff , uint block , uint count, bool Encrypt){
	unsigned int index=0;		
	//int times =0;
	unsigned int write_counter=0;	
	unsigned char rpmb_key[32]={0};		
	int ret =1;
	//unsigned char KF[16]={0};
	//AES_KEY aes_key_en;

	/* judge whether exceed address range
 	 * rpmb_size * 128 * 1024 / 256 ==max block count
	 */
	/*
	if( (block+count) > (rpmb_size <<9) ){
		printf("address out of range\n");
		return EXIT_FAILURE;
	}
	*/
	
	/* reset the pointer */
	//MY_CLR_ALIGN_BUFFER(); //for align
	
	/*1.alloc mem for rpmb packet*/		
	/* alloc rpmb frame */
	//MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame, 0x01); //512 bytes
	struct s_rpmb * rpmb_frame = (struct s_rpmb*)memalign(0x200,0x200);

	/*2.calculate rpmb key*/	
	Calculate_RPMB_key(rpmb_key);		

	
	/*3. Encrypt data by KF */
	/*
	if(Encrypt){
		GET_KF_IN_OTP(KF);	
		unsigned int KF_temp[4];
		memcpy(KF_temp,KF,16);
		KF_temp[0]= uswap_32(KF_temp[0]);
		KF_temp[1]= uswap_32(KF_temp[1]);
		KF_temp[2]= uswap_32(KF_temp[2]);
		KF_temp[3]= uswap_32(KF_temp[3]);
		memcpy(KF,KF_temp,16);	
		AES_set_encrypt_key(KF, 128, &aes_key_en);
		printf("start encryption...\n");
	}
	*/

	/* 4.data loop*/		
	for(index=0 ; index < count;index++){		
		/*get write counter*/		
		emmc_rpmb_counter(& write_counter);			
		//printf("write counter is %d\n",write_counter);
		
		/*clear*/			
		memset(rpmb_frame,0x00,0x200);	

		/*encrypt*/
		/*
		if(Encrypt){   //encrypt by kf
			unsigned char cipher_text[256]={0};		
			memset(cipher_text,0x00,256); 
			for(times=0;times<16;times++){
				AES_encrypt((const unsigned char *)buff+times*16+index*256, cipher_text+times*16, &aes_key_en);
			}
			memcpy( rpmb_frame->data, cipher_text , RPMB_SZ_DATA );	
		}else{  //write raw data
			memcpy( rpmb_frame->data , buff+index * RPMB_SZ_DATA , RPMB_SZ_DATA ); 
		}
		*/
		//write raw data
		memcpy( rpmb_frame->data , buff+index * RPMB_SZ_DATA , RPMB_SZ_DATA ); 
		
		rpmb_frame->request       = uswap_16(RPMB_REQ_WRITE_DATA);		
		rpmb_frame->address       = uswap_16(block+index);		
		rpmb_frame->block_count   = uswap_16(1);			
		rpmb_frame->write_counter = uswap_32(write_counter);		  

		/*calculate Hmac*/		
		Calculate_RPMB_Hmac(rpmb_key,rpmb_frame->data,284,rpmb_frame->mac);		


		/*send request*/		
		ret = emmc_rpmb_request(rpmb_frame,1,true);
		if(ret){
			printf("rpmb request fail\n");
			break;
		}

		/*get status*/		
		memset(rpmb_frame,0x00,sizeof(struct s_rpmb));		
		rpmb_frame->request = uswap_16(RPMB_REQ_STATUS);	
		ret = emmc_rpmb_request(rpmb_frame,1,false);
		if(ret){
			printf("rpmb request fail\n");
			break;
		}
		
		
		memset(rpmb_frame,0x00,sizeof(struct s_rpmb)); 
		ret = emmc_rpmb_response(rpmb_frame,RPMB_RESP_WRITE_DATA);
		if(ret){
			printf("rpmb response fail\n");
			break;
		}
		if(uswap_16(rpmb_frame ->result)){   //non zero means failure
			break;
		}
	}

	/*5. whether succeed*/
	if(index==count){	
		printf("%d blocks write done\n",index);	
		return EXIT_SUCCESS;	
	}else{		
		printf("rpmb write fail at %d\n",index);
		return EXIT_FAILURE;		
	}	

	free(rpmb_frame);
	return EXIT_FAILURE;
}

/*
 * set block count to 1 in the case of rpmb read/write
 * ret:
 * 1 == fail
 * 0 == success
 */
static int emmc_set_blockcount(int count,bool reliable){
	int ret =1;

	/*argument*/
	unsigned int arg = (count & 0xff);
	if(reliable)
		arg |= (1<<31);

	ret = emmc_send_cmd_get_rsp(MMC_SET_BLOCK_COUNT,arg,1,1);
	return ret;
}

static int emmc_rw_ip_rpmb(unsigned int cmd_idx,unsigned int blk_addr,
					       unsigned char * dma_addr,unsigned int dma_length){
	cr_writel(0,CR_EMMC_SWC_SEL);
	cr_writel(0,CR_EMMC_CP);
	CP15ISB;
	sync();

	flush_cache(PTR_U32(dma_addr), dma_length);
	
	make_ip_des_rpmb(dma_addr,dma_length);
	
	cr_writel(0x200, CR_EMMC_BYTCNT);	
	
	cr_writel(PTR_U32(rw_descriptor), CR_EMMC_DBADDR);
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);	
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);	
	cr_writel(blk_addr, CR_EMMC_CMDARG);	
	CP15ISB;	
	sync();		
	
	if (cmd_idx == MMC_READ_MULTIPLE_BLOCK){	
		//printf("inside read multiple\n");		
		cr_writel(0xa0002340 | cmd_idx, CR_EMMC_CMD);   
		
	}else if (cmd_idx ==MMC_WRITE_MULTIPLE_BLOCK){	
		//printf("inside write multiple\n");		
		cr_writel(0xa0002740 | cmd_idx, CR_EMMC_CMD);		
		
	}else if(cmd_idx ==MMC_SEND_EXT_CSD){	
		//printf("inside send ext csd\n");		
		cr_writel(0xa0000340 | cmd_idx, CR_EMMC_CMD);	
		
	}else	
		return -1;	

	CP15ISB;
	sync();

	wait_done(CR_EMMC_RINTSTS, 0x4, 0x4); //command done	
	wait_done(CR_EMMC_RINTSTS, 0x8, 0x8);//data transfer over	

	CP15ISB;	
	sync();		

	//read: polling dma done	
	if (cmd_idx == MMC_READ_MULTIPLE_BLOCK || cmd_idx == MMC_SEND_EXT_CSD) {	  
		wait_done(CR_EMMC_ISR, 0x2, 0x2); //dma done	  
		cr_writel(0x2, CR_EMMC_ISR);	    
		CP15ISB;	   
		sync();	
	}	

	wait_done(CR_EMMC_STATUS, 0x200, 0x0);//data busy	
	CP15ISB;	
	sync();	
	return check_error(0);
}

static int emmc_rpmb_response(struct s_rpmb * rpmb_frame,unsigned short expected){
	int ret =1;
	//printf("inside rpmb response\n");

	/*set block count to 1*/
	ret = emmc_set_blockcount(1,false);
	if(ret){
		printf("set block count fail\n");		
		return ret;
	}

	//printf("set block count success\n");

	ret = emmc_rw_ip_rpmb(MMC_READ_MULTIPLE_BLOCK,0,(unsigned char *)rpmb_frame,0x200);
	if(ret){
		printf("rpmb read write ip fail\n");	
		return ret;
	}
	
	invalidate_dcache_range(PTR_U32(rpmb_frame), PTR_U32(rpmb_frame) + sizeof(struct s_rpmb) * 0x200);

	
	/*deal with expected*/
	if( uswap_16(rpmb_frame->request) != expected){
		printf("response type error\n");
		printf("response type value:%04x\n",uswap_16(rpmb_frame->request));
		//return 1;
	}

	/* whether error occurs */
	if(uswap_16(rpmb_frame ->result)){   //non zero means failure
		/*print result*/
		printf("%s\n",rpmb_err_msg[uswap_16(rpmb_frame->result) & RESULT_ERROR_MASK] );
	}

	//dump_hex((unsigned char *)rpmb_frame,0x200);
	return 0;
}

static int emmc_rpmb_request(struct s_rpmb * rpmb_frame,int count ,bool reliable){
	int ret =1;

	/*set block count  to 1 */
	ret = emmc_set_blockcount(count,reliable);
	if(ret){
		printf("set block count fail\n");		
		return ret;
	}
	
	ret = emmc_rw_ip_rpmb(MMC_WRITE_MULTIPLE_BLOCK,0,( unsigned char *)rpmb_frame,0x200);
	if(ret){
		printf("emmc r/w ip fail\n");
		return ret;
	}

	return 0;
}

static void make_ip_des_rpmb(const unsigned char *dma_addr, unsigned int dma_length)

{
	unsigned int *des_base = rw_descriptor;
	unsigned int blk_cnt;                                                                                                                               
	unsigned int remain_blk_cnt;

	blk_cnt        = dma_length >> 9;
  	remain_blk_cnt = blk_cnt;
	CP15ISB;
	sync();

	flush_cache(PTR_U32(rw_descriptor), 4 * sizeof(unsigned int) * MAX_DESCRIPTOR_NUM);

	while(remain_blk_cnt) {
		unsigned int para;
		unsigned int cur_blk_cnt;

		/* setting des0; transfer parameter  */
		para = 0x80000000 | 0x2 | 0x10;
		para |= remain_blk_cnt == blk_cnt ? 0x8 : 0;
		para |= remain_blk_cnt <= EMMC_MAX_SCRIPT_BLK ? 0x4 : 0;
		des_base[0] = para;		

		/* setting des1; buffer size in byte */                         
		cur_blk_cnt = remain_blk_cnt > EMMC_MAX_SCRIPT_BLK ? EMMC_MAX_SCRIPT_BLK : remain_blk_cnt;
		des_base[1] = (cur_blk_cnt << 9);                                                   

		/* setting des2; Physical address to DMA to/from */                             
		des_base[2] = PTR_U32(dma_addr);

		/* setting des3; next descrpter entry */                                        
		des_base[3] = PTR_U32(des_base + 4);

		dma_addr       += (cur_blk_cnt << 9);
		remain_blk_cnt -= cur_blk_cnt; 
		des_base       += 4;

		CP15ISB;
		sync();
	}       

	flush_cache(PTR_U32(rw_descriptor), 4 * sizeof(unsigned int)*  MAX_DESCRIPTOR_NUM);
} 

#if 0
static  OPS_STATE rtk_rpmb_read_block(void * buff ,uint block , uint count, bool Decrypt){
		
	struct mmc *mmc = find_mmc_device(0);
	
	/* some variable */
	unsigned char rpmb_key[32]={0}; 
	uint index =0;	
	
	/* reset the pointer */
	MY_CLR_ALIGN_BUFFER(); //for align
	
	/* alloc rpmb frame */
	MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame,  0x01); //512 bytes
	
	/* calculate rpmb key */	
	Calculate_RPMB_key(rpmb_key);
	
	/* data loop */
	for(index=0;index < count;index++){
	
		/* clear */
		memset(rpmb_frame,0,sizeof(struct s_rpmb));
		rpmb_frame->request = cpu_to_be16(RPMB_REQ_READ_DATA);
		rpmb_frame->address = cpu_to_be16(block+index);
	
		/* send request */
		if(mmc_rpmb_request(mmc,rpmb_frame,1,false))
			break;
	
		/*read response*/
		if(mmc_rpmb_response(mmc,rpmb_frame,RPMB_RESP_READ_DATA))
			break;
	
		/*check hmac*/
		unsigned char ret_hmac[RPMB_SZ_MAC] ;			
		Calculate_RPMB_Hmac(rpmb_key,rpmb_frame->data, 284 ,ret_hmac);
		if(memcmp(ret_hmac , rpmb_frame->mac,RPMB_SZ_MAC)){
			printf("MAC error on block %d\n",index);
			break;
		}
		
		memcpy(buff+index*RPMB_SZ_DATA , rpmb_frame->data , RPMB_SZ_DATA);
	}
	
	/* succeed or not */	
	if(index == count){ 	
		printf("%d blocks read success\n",index);		
		return EXIT_SUCCESS;
	}else{		
		printf("read fail at block %d\n",index);					
		return EXIT_FAILURE;
	}
	
	return EXIT_FAILURE;
}
#endif

static OPS_STATE rtk_rpmb_read_block(void * buff ,uint block , uint count, bool Decrypt){
		/*rpmb key is global varible*/	 
		unsigned char rpmb_key[32]={0};	
		int ret = 1;
		//int times =0;
		uint index =0;	
		//unsigned char KF[16]={0};
		//AES_KEY aes_key_de;

		/* judge whether exceed address range*/
		/*
		if( (block+count) > (rpmb_size<<9 )){
			printf("address out of range\n");
			return 1;
		}
		*/
		
		/* reset the pointer */
		//MY_CLR_ALIGN_BUFFER(); //for align

		/* 1.alloc mem for rpmb packet*/ 
		/* alloc rpmb frame */
		//MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame,  0x01); //512 bytes
		struct s_rpmb * rpmb_frame = (struct s_rpmb*)memalign(0x200,0x200);
		
		/* 2.calculate rpmb key*/
		Calculate_RPMB_key(rpmb_key);	

		/* 3.decrypt data by KF */
		/*
		if(Decrypt){
			GET_KF_IN_OTP(KF);
			unsigned int KF_temp[4];
			memcpy(KF_temp,KF,16);
			KF_temp[0]= uswap_32(KF_temp[0]);
			KF_temp[1]= uswap_32(KF_temp[1]);
			KF_temp[2]= uswap_32(KF_temp[2]);
			KF_temp[3]= uswap_32(KF_temp[3]);	
			memcpy(KF,KF_temp,16);
			AES_set_decrypt_key(KF, 128, &aes_key_de);
			printf("start decryption...\n");
		}
		*/

		
		/* 4.deal with each packet */	
		for(index=0;index<count;index++){		
			/*clear */		
			memset(rpmb_frame, 0x00 ,sizeof(struct s_rpmb));	

			/*fullfill*/		
			rpmb_frame->request = uswap_16(RPMB_REQ_READ_DATA);		
			rpmb_frame->address = uswap_16(block+index);		

			/*send packet*/	
			ret = emmc_rpmb_request(rpmb_frame,1,false);
			if(ret){
				printf("rpmb request fail\n");
				break;
			}

			/*get response*/	
			//memset(rpmb_frame,0x00,sizeof(struct rpmb_packet));	
			ret = emmc_rpmb_response(rpmb_frame,RPMB_RESP_READ_DATA);
			if(ret){
				printf("rpmb response fail\n");
				break;
			}

			//dump_hex((unsigned char *)rpmb_frame,0x200);
			
			/*check hmac*/		
			unsigned char ret_hmac[RPMB_SZ_MAC];
			Calculate_RPMB_Hmac(rpmb_key,rpmb_frame->data,284,ret_hmac);	


			/*compare whether match*/		
			if( memcmp(ret_hmac,rpmb_frame->mac,RPMB_SZ_MAC) ){		
				printf("hmac error at %d\n",index);	
				break;	
			}	

			/*
			if(Decrypt){
				unsigned char plain_text[256]={0}; 			
				memset(plain_text,0x00,256); 
				for(times=0;times<16;times++){
					AES_decrypt((const unsigned char *)(rpmb_frame->data)+times*16, plain_text+times*16, &aes_key_de);
				}				
				memcpy(buff+index*RPMB_SZ_DATA, plain_text,RPMB_SZ_DATA);
			}else{
				memcpy(buff+index*RPMB_SZ_DATA, rpmb_frame->data,RPMB_SZ_DATA);
			}
			*/
			memcpy(buff+index*RPMB_SZ_DATA, rpmb_frame->data,RPMB_SZ_DATA);
		}

	   /* 5.succeed or not a*/	
			if(index==count){		
				printf("%d blocks read success\n",index);	
				return EXIT_SUCCESS;
			}else{		
				printf("read fail at block %d\n",index);
				return EXIT_FAILURE;		
			}

	free(rpmb_frame);
	return EXIT_FAILURE;
}

#if 0
static  OPS_STATE emmc_rpmb_counter(unsigned int *pwcount){
	struct mmc *mmc = find_mmc_device(0);

	printf("here1\n");
	/* restore pointer */
	MY_CLR_ALIGN_BUFFER(); //for align

	printf("here2\n");

	/* alloc rpmb frame */
	MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame,  0x01); //512 bytes
	memset(rpmb_frame, 0, sizeof(struct s_rpmb));

	printf("here3\n");

    /* fullfille request */
	rpmb_frame->request = cpu_to_be16(RPMB_REQ_WCOUNTER);
	if(mmc_rpmb_request(mmc,rpmb_frame,1,false)){
		return EXIT_FAILURE;
	}
		printf("here4\n");

	/* get response */
	if(mmc_rpmb_response(mmc, rpmb_frame,RPMB_RESP_WCOUNTER)){
		return EXIT_FAILURE;
	}
		printf("here5\n");

	if(be16_to_cpu(rpmb_frame ->result)){ //non zero means failure
		/*print result*/
		printf("%s\n",rpmb_err_msg[be16_to_cpu(rpmb_frame->result) & RPMB_ERR_MSK] );
		return EXIT_FAILURE;
	}
		printf("here6\n");
				
	*pwcount = be32_to_cpu(rpmb_frame->write_counter);
	printf("here7\n");

	return EXIT_SUCCESS; //run here means success
}
#endif

/*  get write counter from emmc
 *  ret:
 *  1 == fail
 *  0 == success
 */
static OPS_STATE emmc_rpmb_counter(unsigned int * wcounter){
	int ret =1;
	/* restore pointer */
	//MY_CLR_ALIGN_BUFFER(); //for align
	//MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame,  0x01); //512 bytes
	struct s_rpmb * rpmb_frame = (struct s_rpmb*)memalign(0x200,0x200);
	memset(rpmb_frame,0x00,sizeof(struct s_rpmb));

	rpmb_frame->request = uswap_16(RPMB_REQ_WCOUNTER);

	/* send request */
	ret = emmc_rpmb_request(rpmb_frame,1,false);
	if(ret){
		printf("rpmb request fail\n");
		goto FAIL;
	}

	/* get response */
	memset(rpmb_frame,0x00,sizeof(struct s_rpmb));
	ret = emmc_rpmb_response(rpmb_frame,RPMB_RESP_WCOUNTER);
	if(ret){
		printf("rpmb response fail\n");
		goto FAIL;
	}


	/*print response*/
	if(uswap_16(rpmb_frame ->result)){ //non zero means failure
			printf("%s\n",rpmb_err_msg[uswap_16(rpmb_frame->result) & RESULT_ERROR_MASK] );
			goto FAIL;
	}
	
	/*get counter*/
	(*wcounter) = uswap_32(rpmb_frame->write_counter);
	free(rpmb_frame);
	return EXIT_SUCCESS;
FAIL:
	free(rpmb_frame);
	rpmb_frame = NULL;
	return EXIT_FAILURE;
}



static void KEY_pad_to_64bytes(unsigned char * original_key,int original_len,unsigned char * padded_key){
	memcpy(padded_key, original_key , original_len);

	//zero padding
	memset(padded_key+original_len ,0x00  , (HASH_BLOCK_SIZE - original_len));
}

static int GET_KF_IN_OTP(unsigned char * kf){
	OTP_Get_Byte(KF_OFFSET,kf,16);	
	return 0;
}

#if 0
static int Calculate_RPMB_key(unsigned char *rpmb_key){

	/* some varibles */	
	sha256_context ctx;	
	int index=0;		
	unsigned char first_step_key[64]	={0};
	unsigned char key_pad_to_64[64]		={0};
	unsigned char first_step_hash[32]	={0};		
	unsigned char second_step_key[64]	={0};
	unsigned char kF[16]				={0};
	
	/* get kF from otp area */	
	GET_KF_IN_OTP(kF);
	
	/*make it pad to 64 bytes*/	
	KEY_pad_to_64bytes(kF,KF_LEN,key_pad_to_64);	  

	/* Create the initial vector  */	
	for(index=0; index < HASH_BLOCK_SIZE; index++) {  
		first_step_key[index] = key_pad_to_64[index] ^ 0x36;
	}

	/* get emmc cid */
	struct mmc *mmc = find_mmc_device(0);
	int count;
	unsigned char emmc_cid[16]={0};
	unsigned int after[4]={0};
	for(count=0;count<4;count++){
		after[count] = cpu_to_be32(mmc->cid[count]);
	}
	memcpy(emmc_cid , after , 16);


	/* Pre-pend that to the hash data */
	sha256_starts(&ctx);	
	sha256_update(&ctx, first_step_key,HASH_BLOCK_SIZE);
	sha256_update(&ctx, emmc_cid,RPMB_EMMC_CID_SIZE);

	/* Get the hash of the first  vector plus the data */	
	//memcpy(first_step_hash,sha256_finish(&ctx),SHA256_DIGEST_SIZE);	
	sha256_finish(&ctx,first_step_hash);

	/* Create the second  vector vector */	 
	for(index=0; index < HASH_BLOCK_SIZE; index++) {
		second_step_key[index] = key_pad_to_64[index] ^ 0x5C;  
	}

	/* Now calculate the "outer" hash */	
	memset(&ctx,0x00,sizeof(sha256_context));
	sha256_starts(&ctx);
	sha256_update(&ctx, second_step_key,HASH_BLOCK_SIZE);	
	sha256_update(&ctx, first_step_hash,SHA256_DIGEST_SIZE);
//	memcpy(	rpmb_key,sha256_finish(&ctx),SHA256_DIGEST_SIZE);   
	sha256_finish(&ctx,rpmb_key);
	
	return 0;
}
#endif

static int Calculate_RPMB_key(unsigned char *rpmb_key){	
	/*some varibles*/	
	sha256_context ctx;	int index=0;	
	unsigned char first_step_hash[32]={0};		

	/*get kf from otp area*/	
	GET_KF_IN_OTP(ks);
	
	
	/*make it pad to 64 bytes*/	
	KEY_pad_to_64bytes(ks,KF_LEN,key_pad_to_64);	  

	/* Create the initial vector  */	
	for(index=0; index < HASH_BLOCK_SIZE; index++) {  
		first_step_key[index] = key_pad_to_64[index] ^ 0x36;
	}

	/* Pre-pend that to the hash data */
	
	
	sha256_starts(&ctx);	
	sha256_update(&ctx, first_step_key,HASH_BLOCK_SIZE);
	sha256_update(&ctx, (const uint8_t *)emmc_cid,RPMB_EMMC_CID_SIZE);


	/* Get the hash of the first  vector plus the data */	
	//memcpy(first_step_hash,SHA256_final(&ctx),SHA256_DIGEST_SIZE);	
	sha256_finish(&ctx,first_step_hash);

	/* Create the second  vector vector */   
	for(index=0; index < HASH_BLOCK_SIZE; index++) {
		second_step_key[index] = key_pad_to_64[index] ^ 0x5C;  
	}

	/* Now calculate the "outer" hash */	
	memset(&ctx,0,sizeof(sha256_context));
	sha256_starts(&ctx);
	sha256_update(&ctx, second_step_key,HASH_BLOCK_SIZE);	
	sha256_update(&ctx, first_step_hash,SHA256_DIGEST_SIZE);
	//memcpy(	rpmb_key,SHA256_final(&ctx),SHA256_DIGEST_SIZE);
	sha256_finish(&ctx,rpmb_key);	
	return 0;
}

#if 0
static  OPS_STATE  rtk_emmc_rpmb_burn_key(void){
	printf("============in case of unmeant operation,we return immediately========================\n");
	return EXIT_SUCCESS;
	
	struct mmc *mmc = find_mmc_device(0);
	
	/* 1. burn kf
	 *   
	 * whether or not kf has been burned,the process will continue
	 */
	//if ( BURN_KF_IN_OTP() ){
		//burn kf fail
	//	return 1;
	//}
	printf("skip burn kf\n");
	
	/* Calculate_RPMB_key */
	unsigned char rpmb_key[32]={0};
	Calculate_RPMB_key(rpmb_key);

	/* alloc rpmb frame */
	MY_CLR_ALIGN_BUFFER(); //for align
	MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_request,  0x01); //512 bytes
	memset(rpmb_request , 0 , sizeof(struct s_rpmb));

    /* fullfill request */
	rpmb_request->request = 0x0100;   //MSB write key
	memcpy(rpmb_request->mac, rpmb_key , RPMB_SZ_MAC);

	/* send request */
	if (mmc_rpmb_request(mmc, rpmb_request, 1, true)){ //must true
		printf("rpmb request fail\n");
		return -1;
	}

	/* get response */
	memset(rpmb_request , 0 , sizeof(struct s_rpmb));
	rpmb_request->request = cpu_to_be16(RPMB_REQ_STATUS);	
	if(mmc_rpmb_request( mmc, rpmb_request,1 ,false)){
		return -1;
	}
	
	if(mmc_rpmb_response(mmc , rpmb_request , RPMB_RESP_KEY)){
		printf("rpmb response fail\n");
		return -1;
	}

	if(cpu_to_be16(rpmb_request ->result)){   //non zero means failure
		printf("rpmb key burned before\n");
	}else{
		printf("burn rpmb key done\n");
	}
	

	return EXIT_SUCCESS;
}
#endif

/*
 * 0  ==success
 * !0 ==fail
 */
static OPS_STATE rtk_emmc_rpmb_burn_key(void){	

	int ret =1;
	
	/* 1. burn kf
	 *   
	 * whether or not kf has been burned,the process will continue
	 */
	//BURN_KF_IN_OTP();
	printf("skip burn kf\n");
	 
	/*2.invoke Calculate_RPMB_key */
	unsigned char rpmb_key[32]={0};
	Calculate_RPMB_key(rpmb_key);


	/*3.fullfill the request packet*/
	//MY_CLR_ALIGN_BUFFER(); //for align
	//MY_ALLOC_CACHE_ALIGN_BUFFER(struct s_rpmb , rpmb_frame,  0x01); //512 bytes
	struct s_rpmb * rpmb_frame = (struct s_rpmb*)memalign(0x200,0x200);
	memset(rpmb_frame,0x00,sizeof(struct s_rpmb));

	rpmb_frame->request = uswap_16(RPMB_REQ_KEY);   //MSB write key

	/*copy key to data packet*/
	memcpy(rpmb_frame->mac, rpmb_key , RPMB_SZ_MAC);

	/*send packet*/
	ret = emmc_rpmb_request(rpmb_frame, 1,true);
	if(ret){
		printf("rpmb request fail\n");
		goto FAIL;
	}
	
	/* get response*/
	memset(rpmb_frame,0x00,sizeof(struct s_rpmb));		
	rpmb_frame->request = uswap_16(RPMB_REQ_STATUS);	
	ret = emmc_rpmb_request(rpmb_frame,1,false);
	if(ret){
		printf("RPMB_REQ_STATUS fail\n");
	}
	
	memset(rpmb_frame,0x00,sizeof(struct s_rpmb));
	ret = emmc_rpmb_response(rpmb_frame,RPMB_RESP_KEY);
	if(ret){
		printf("rpmb response fail\n");
		goto FAIL;
	}

	if(uswap_16(rpmb_frame ->result)){   //non zero means failure
		printf("rpmb key burned before\n");
	}else{
		printf("burn rpmb key done\n");
	}

	return EXIT_SUCCESS;

FAIL:
	free(rpmb_frame);
	return EXIT_FAILURE;
	
}

static struct rpmb_operation rpmb_ops ={
	.switch_partition 	 =  emmc_switch_partition,
	.write_block 		 = rtk_rpmb_write_block,
	.read_blcok 		 = rtk_rpmb_read_block,
	.get_counter 		 = emmc_rpmb_counter,
	.burn_key			 = rtk_emmc_rpmb_burn_key,
};



int do_rpmb_ops (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]){

	if(argc ==1)	
		return CMD_RET_USAGE;  

	enum operation state;
	void * ddr_address 		       = NULL;
	unsigned int block 		       = 0;
	unsigned int block_count 	   = 0;
	unsigned int wcounter = 0;	

	
	/* judge input*/
	if(strncmp(argv[1],"write_En",8)==0){
		state = MMC_RPMB_WRITE_EN;
	}else if(strncmp(argv[1],"write_Raw",9)==0){
		state = MMC_RPMB_WRITE_RAW;
	}else if(strncmp(argv[1],"read_De",7)==0){
		state = MMC_RPMB_READ_DE;
	}else if(strncmp(argv[1],"read_Raw",8)==0){
		state = MMC_RPMB_READ_RAW;
	}else if(strncmp(argv[1],"counter",7)==0){
		state = MMC_RPMB_COUNTER;
	}else if(strncmp(argv[1],"burn",4)==0){
		state = MMC_RPMB_BURN;
	}else{
		state = MMC_INVALID;
	}

	
	if(state < MMC_RPMB_COUNTER){
		ddr_address = (void *)simple_strtoul(argv[2], NULL, 16);
		block       =         simple_strtoul(argv[3], NULL, 16);
		block_count = 		  simple_strtoul(argv[4], NULL, 16);
	}

	/* run into corresponding branch */
	switch(state){
		case MMC_RPMB_WRITE_EN:
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));
			TEST_AND_RETURN_FALSE(rtk_rpmb_write_block(ddr_address, block, block_count, true));
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));
			break;
		case MMC_RPMB_WRITE_RAW:
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));
			TEST_AND_RETURN_FALSE(rtk_rpmb_write_block(ddr_address, block, block_count, false));	
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));
			break;
		case MMC_RPMB_READ_DE:
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));
			TEST_AND_RETURN_FALSE(rtk_rpmb_read_block(ddr_address, block, block_count, true));	
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));
			break;
			
		case MMC_RPMB_READ_RAW:
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));
			TEST_AND_RETURN_FALSE(rtk_rpmb_read_block(ddr_address, block, block_count, false));	
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));	
			break;
		case MMC_RPMB_COUNTER:
			//TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));		
			//TEST_AND_RETURN_FALSE(emmc_rpmb_counter(&wcounter));		
			//printf("write counter is %d\n",wcounter);		
			//TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));
			printf("this1\n");
			rpmb_ops.switch_partition(MMC_PART_RPMB);
			printf("this2\n");
			emmc_rpmb_counter(&wcounter);
			printf("write counter is %d\n",wcounter);		
			rpmb_ops.switch_partition(MMC_PART_UDA);
			
			break;
		case MMC_RPMB_BURN:
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_RPMB));		
			TEST_AND_RETURN_FALSE(rtk_emmc_rpmb_burn_key());
			TEST_AND_RETURN_FALSE(rpmb_ops.switch_partition(MMC_PART_UDA));
			break;
		default:
			printf("illegal command\n");
			break;
	}
	return 0;
}




//command used from cmd line
U_BOOT_CMD(
	rpmb, 6, 1, do_rpmb_ops,
	"rpmb operations",
	"rpmb write_En  buff_addr dest_block block_count \n"
	"rpmb write_Raw buff_addr dest_block block_count \n"
	"rpmb read_De  buff_addr start_block block_count \n"
	"rpmb read_Raw buff_addr start_block block_count \n"
	"rpmb counter  -->get rpmb counter \n" 
	"rpmb burn     -->start burn rpmb key and OTP!!!cautiously use!!!\n"
);
