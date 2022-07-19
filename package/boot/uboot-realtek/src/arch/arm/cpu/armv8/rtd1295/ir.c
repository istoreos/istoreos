#include <asm/arch/rbus/iso_reg.h>
//#include <debug.h>
//#include <platform/interrupts.h>
#include <asm/arch/rtk_ipc_shm.h>
//#include <linux/input.h>
#include <common.h>

#define u32 unsigned int
#define BYTE(d,n)	(((d) >> ((n) << 3)) & 0xFF)
#define SWAPEND32(d)	((BYTE(d,0) << 24) | (BYTE(d,1) << 16) | (BYTE(d,2) << 8) | (BYTE(d,3) << 0))

#define KEY_POWER 116
#define KEY_HOME 102
#define KEY_OPTION 128
#define KEY_UP 103
#define KEY_LEFT 105
#define KEY_RIGHT 106
#define KEY_DOWN 108
#define KEY_VOLUMEDOWN 114
#define KEY_VOLUMEUP 115

/* IR setting */
#define CONFIG_IR_PROTOCOL  1
#define CONFIG_IR_SCANCODE_MASK  0x00FF0000
#define CONFIG_IR_WAKEUP_SCANCODE  0x18
#define CONFIG_IR_CUS_MASK  0x0000FFFF
#define CONFIG_IR_CUS_CODE  0x7F80

//#define USE_IRQ
#define CONFIG_IR_NEC_PROTOCOL

struct venus_key {
	u32 scancode;
	u32 keycode;
};

static struct venus_key rtk_mk5_tv_keys[] = {
	{0x18, KEY_POWER},			//POWER
//	{0x5A, KEY_SELECT},			//SOURCE
//	{0x58, KEY_CYCLEWINDOWS},	//PIP
//	{0x1A, KEY_TV},				//TV SYSTEM
	{0x14, KEY_HOME},			//HOME
	{0x56, KEY_OPTION},			//OPTION MENU
//	{0x54, KEY_INFO},				//MEDIA_INFO
//	{0x19, KEY_REPLY},			//REPEAT
//	{0x57, KEY_BACK},			//RETURN
//	{0x55, KEY_PLAY},				//PLAY/PAUSE
//	{0x17, KEY_STOP},			//STOP
//	{0x15, KEY_ZOOM},			//ZOOM_IN
//	{0x4F, KEY_REWIND},			//FR
	{0x4D, KEY_UP},				//UP
//	{0x16, KEY_FASTFORWARD},	//FF
	{0x0C, KEY_LEFT},				//LEFT
//	{0x4C, KEY_OK},				//OK
	{0x0E, KEY_RIGHT},			//RIGHT
//	{0x08, KEY_PREVIOUS},		//PREVIOUS
	{0x48, KEY_DOWN},			//DOWN
//	{0x09, KEY_NEXT},			//NEXT
	{0x4B, KEY_VOLUMEDOWN},		//VOL-
	{0x49, KEY_VOLUMEUP},		//VOL+
//	{0x0B, KEY_TOUCHPAD_OFF},	//CURSOR
//	{0x0A, KEY_TOUCHPAD_ON},	// GESTURE
};
 #if defined(CONFIG_IR_KK_Y261_PROTOCOL)
static struct venus_key Konka_tv_keys[] = {
//	{0x18, KEY_GREEN},
//	{0x5A, KEY_SELECT},			//SOURCE
//	{0x58, KEY_CYCLEWINDOWS},	//PIP
//	{0x1A, KEY_TV},				//TV SYSTEM
//	{0x14, KEY_HOME},			//HOME
//	{0x56, KEY_OPTION},			//OPTION MENU
//	{0x54, KEY_INFO},				//MEDIA_INFO
//	{0x19, KEY_YELLOW},
//	{0x57, KEY_BACK},			//RETURN
//	{0x55, KEY_PLAY},				//PLAY/PAUSE
//	{0x17, KEY_STOP},			//STOP
//	{0x15, KEY_ZOOM},			//ZOOM_IN
//	{0x4F, KEY_REWIND},			//FR
	{0x1C, KEY_UP},				//UP
//	{0x16, KEY_FASTFORWARD},	//FF
	{0x0D, KEY_LEFT},				//LEFT
//	{0x4C, KEY_OK},				//OK
	{0x1D, KEY_RIGHT},			//RIGHT
//	{0x08, KEY_PREVIOUS},		//PREVIOUS
	{0x1E, KEY_DOWN},			//DOWN
//	{0x09, KEY_NEXT},			//NEXT
//	{0x4B, KEY_VOLUMEDOWN},		//VOL-
//	{0x49, KEY_VOLUMEUP},		//VOL+
//	{0x0B, KEY_TOUCHPAD_OFF},	//CURSOR
//	{0x0A, KEY_TOUCHPAD_ON},	// GESTURE
};
#endif
unsigned int IR_Parsing_key(void)
{

	unsigned int scan_code=0;
	unsigned int i;

	scan_code =(0x00ff0000 & get_ISO_IR_RP_reg)>> 16;
	printf("scan_code=%x\n",scan_code);

#if defined(CONFIG_IR_KK_Y261_PROTOCOL)
	for(i=0;i<sizeof(Konka_tv_keys)/sizeof(struct venus_key);i++)
	{
			if(scan_code == Konka_tv_keys[i].scancode)
			{
				printf("Konka_tv_keys[%d].keycode=%d\n",i,Konka_tv_keys[i].keycode);
				return Konka_tv_keys[i].keycode;
			}
	}

#else
	for(i=0;i<sizeof(rtk_mk5_tv_keys)/sizeof(struct venus_key);i++)
	{
			if(scan_code == rtk_mk5_tv_keys[i].scancode)
			{
				printf("rtk_mk5_tv_keys[%d].keycode=%d\n",i,rtk_mk5_tv_keys[i].keycode);
				return rtk_mk5_tv_keys[i].keycode;
			}
	}
#endif
	 return 0;
}


unsigned int IR_Protocol_Selection(void)
{
	unsigned int psr_val=0;

#ifdef CONFIG_IR_NEC_PROTOCOL
	// NEC
	// IRSBC=20uS(50KHz) sampling rate
	// IRRBL=>(9mS*80%=IRRBL*IRSBC*4)=>0x5a
	// IRRML=>(560uS*80%=IRRML*IRSBC)=>0x16
	// IRRDZL=>((1.12mS-560uS)*80%=IRRDZL*IRSBC)=>0x16
	// IRRDOL=>((2.25mS-560uS)*80%=IRRDOL*IRSBC)=>0x43

	psr_val = (ISO_IR_PSR_irrbl(0x5a)| ISO_IR_PSR_irrml(0x16)| ISO_IR_PSR_irrdzl(0x16) | ISO_IR_PSR_irrdol(0x43));

#elif defined(CONFIG_IR_SONY_PROTOCOL)
	// SONY
	// IRSBC=20uS(50KHz) sampling rate
	// IRRBL=>(2.4mS*80%=IRRBL*IRSBC*4)=>0x18
	// IRRML=>(600uS*80%=IRRML*IRSBC)=>0x18
	// IRRDZL=>((1.2mS-600uS)*80%=IRRDZL*IRSBC)=>0x18
	// IRRDOL=>((1.8mS-600uS)*80%=IRRDOL*IRSBC)=>0x30
	psr_val = (ISO_IR_PSR_irrbl(0x18)| ISO_IR_PSR_irrml(0x18)|ISO_IR_PSR_irrdzl(0x18) | ISO_IR_PSR_irrdol(0x30));

#elif defined(CONFIG_IR_RC5_PROTOCOL)

	psr_val = (ISO_IR_PSR_irrbl(0x0)| ISO_IR_PSR_irrml(0x23)|ISO_IR_PSR_irrdzl(0x23) | ISO_IR_PSR_irrdol(0x23));

#elif defined(CONFIG_IR_RC6_PROTOCOL)

	psr_val = (ISO_IR_PSR_irrbl(0x1a)| ISO_IR_PSR_IRRML(0x0e)|ISO_IR_PSR_irrdzl(0x0e) | ISO_IR_PSR_irrdol(0x0e));

#elif defined(CONFIG_IR_KK_Y261_PROTOCOL)

	psr_val = (ISO_IR_PSR_irrbl(0x1e)| ISO_IR_PSR_IRRML(0x14)|ISO_IR_PSR_irrdzl(0x3c) | ISO_IR_PSR_irrdol(0x64));

#endif

	return psr_val;
}

unsigned int IR_Protocol_Extension(void)
{
	unsigned int per_val=0;

#ifdef CONFIG_IR_NEC_PROTOCOL
	// NEC
	// IRRDL=>0x1
	// IRRRL=>(2.25mS*80%=IRRRL*IRSBC*4)=>0x16
	// IRRSL=>(4.5mS*80%=IRRSL*IRSBC*4)=>0x2d

	per_val = (ISO_IR_PER_irrdl(0x1) |ISO_IR_PER_UP_irrrl(0x16) | ISO_IR_PER_irrsl(0x2d));

#elif defined(CONFIG_IR_SONY_PROTOCOL)
	// SONY
	// IRRDL=>0x1
	// IRRRL=>(0mS*80%=IRRRL*IRSBC*4)=>0x0
	// IRRSL=>(600uS*80%=IRRSL*IRSBC*4)=>0x6

	per_val = (ISO_IR_PER_irrdl(0x1) |ISO_IR_PER_UP_irrrl(0x0) | ISO_IR_PER_irrsl(0x6));

#elif defined(CONFIG_IR_RC5_PROTOCOL)

	per_val = 0;

#elif defined(CONFIG_IR_RC6_PROTOCOL)

	per_val = (ISO_IR_PER_irrdl(0x02) |ISO_IR_PER_UP_irrrl(0x0) | ISO_IR_PER_irrsl(0x8));

#elif defined(CONFIG_IR_KK_Y261_PROTOCOL)

	per_val = (ISO_IR_PER_irrdl(0x03) |ISO_IR_PER_UP_irrrl(0x0) | ISO_IR_PER_irrsl(0x1a));

#endif

	return per_val;
}

unsigned int IR_Sampling_Frequency(void)
{
	unsigned int sample_feq=0;

#ifdef CONFIG_IR_NEC_PROTOCOL
	//IR Sampling Frequency, 50kHz
	sample_feq = 0x21b;

#elif defined(CONFIG_IR_SONY_PROTOCOL)
	//sample clock 33MHz/660=50kHz
	sample_feq = 0x293;

#elif defined(CONFIG_IR_RC5_PROTOCOL)

	sample_feq = 0x293;

#elif defined(CONFIG_IR_RC6_PROTOCOL)

	sample_feq = 0x293;

#elif defined(CONFIG_IR_KK_Y261_PROTOCOL)

	sample_feq = 0x293;

#endif

	return sample_feq ;
}

unsigned int IR_Control(void)
{
	unsigned int control_val=0;

#ifdef CONFIG_IR_NEC_PROTOCOL
	//	set Modulation length adjustable disable
	//  Data valid interrupt enable
	//  IR RX endian select is First received bit is in the LSB of FIFO
	//  IRRC unit enable
	//  Coding mode is "length"
	//  Burst mode enable (9ms AGC burst)
	//  Data phase mode is "normal"
	//  Data number is 32 bits

	//control_val = 0x3df;
	control_val = 0x1df; //change endian

#elif defined(CONFIG_IR_SONY_PROTOCOL)
	// 	set Modulation length adjustable enable
	//	Data valid interrupt disable
	//  IR RX endian select is First received bit is in the LSB of FIFO
	//  IRRC unit enable
	//  Coding mode is "length"
	//  Burst mode enable (2.4ms AGC burst)
	//  Data phase mode is "normal"
	//  Data number is 12 bits

	control_val = 0xbcb ;

#elif defined(CONFIG_IR_RC5_PROTOCOL)

	control_val = 0x30c;

#elif defined(CONFIG_IR_RC6_PROTOCOL)

	control_val = 0x715;

#elif defined(CONFIG_IR_KK_Y261_PROTOCOL)

	control_val = 0x7cf;

#endif

	return control_val ;
}

unsigned int IR_Get_irdvf(void)
{
	return ISO_IR_SR_get_irdvf(get_ISO_IR_SR_reg);
}

void IR_Set_irdvf(unsigned int data)
{
	set_ISO_IR_SR_reg(ISO_IR_SR_irdvf(data));
}

#ifdef USE_IRQ
int cnt;
static enum handler_return irda_irq_handler(void *arg)
{
	unsigned int reg;
	reg = get_ISO_ISR_reg;
	if(reg & ISO_ISR_irda_int_mask) {
		set_ISO_IR_SR_reg(ISO_IR_SR_irdvf_mask);
		reg = get_ISO_IR_RP_reg;
		printf("IR interrupt occur, data=0x%x\n", reg);
	}
	else {
		cnt++;
		printf("other interrupt occur = 0x%x\n", reg);
	}
	if(cnt>=10)
		mask_interrupt(73);

	return INT_RESCHEDULE;
}
#endif

int IR_config_wakeup_keys(void *addr)
{
	struct RTK119X_ipc_shm_ir *tbl = (struct RTK119X_ipc_shm_ir*)addr;
	tbl->RTK119X_ipc_shm_ir_magic = SWAPEND32(0x49525641); //IRVA(IR Version A)
	tbl->dev_count = SWAPEND32(1);
	tbl->key_tbl[0].protocol = SWAPEND32(CONFIG_IR_PROTOCOL);
	tbl->key_tbl[0].ir_scancode_mask = SWAPEND32(CONFIG_IR_SCANCODE_MASK);
	tbl->key_tbl[0].ir_wakeup_scancode = SWAPEND32(CONFIG_IR_WAKEUP_SCANCODE);
	tbl->key_tbl[0].ir_cus_mask = SWAPEND32(CONFIG_IR_CUS_MASK);
	tbl->key_tbl[0].ir_cus_code = SWAPEND32(CONFIG_IR_CUS_CODE);
	return 0;
}

void IR_init(void)
{
	unsigned int psr_val,per_val,sample_feq,control_val;
	//-------- for NEC & Sample Clock Rate = 50KHz --------
	//Each pulse is a 560μs long 38kHz carrier burst (about 21 cycles). 
	//A logical "1" takes 2.25ms to transmit, while a logical "0" is only half of that, being 1.125ms.
	set_ISO_SOFT_RESET_reg(get_ISO_SOFT_RESET_reg | ISO_SOFT_RESET_rstn_ir_mask);//rstn_ir
	set_ISO_CLOCK_ENABLE_reg(get_ISO_CLOCK_ENABLE_reg | ISO_CLOCK_ENABLE_clk_en_misc_ir_mask); //clock enable
	set_ISO_MUXPAD0_reg(get_ISO_MUXPAD0_reg |0x40);			//muxpad mux to ir_RX port
	set_ISO_IR_CR_reg(get_ISO_IR_CR_reg | ISO_IR_CR_irsr_mask);   	//Software reset

//	printf("get_SOFT_RESET_reg=0x%x\n",get_ISO_SOFT_RESET_reg);
//	printf("get_CLOCK_ENABLE_reg=0x%x\n",get_ISO_CLOCK_ENABLE_reg);
//	printf("get_ISO_MUXPAD0_reg=0x%x\n",get_ISO_MUXPAD0_reg);
//	printf("get_IR_CR_reg=0x%x\n",get_ISO_IR_CR_reg);

	psr_val= IR_Protocol_Selection();
	set_ISO_IR_PSR_reg(psr_val);
//	printf("get_IR_PSR_reg=0x%x\n",get_ISO_IR_PSR_reg);

	per_val= IR_Protocol_Extension();
	set_ISO_IR_PER_reg( per_val);
//	printf("get_IR_PER_reg=0x%x\n",get_ISO_IR_PER_reg);

	sample_feq = IR_Sampling_Frequency();
	set_ISO_IR_SF_reg(sample_feq);
//	printf("get_IR_SF_reg=0x%x\n",get_ISO_IR_SF_reg);

	control_val = IR_Control();
	set_ISO_IR_CR_reg(control_val);
//	printf("get_IR_CR_reg=0x%x\n",get_ISO_IR_CR_reg);

#ifdef USE_IRQ
	cnt = 0;
	set_ISO_SCPU_INT_EN_reg((get_ISO_SCPU_INT_EN_reg & ~ISO_SCPU_INT_EN_ur0_mask) | ISO_SCPU_INT_EN_irda_mask);

	register_int_handler(73, irda_irq_handler, NULL);
	unmask_interrupt(73);
	set_ISO_IR_CR_reg(get_ISO_IR_CR_reg | ISO_IR_CR_irie_mask);   	//Software reset
	set_ISO_UMSK_ISR_reg(get_ISO_UMSK_ISR_reg | ISO_UMSK_ISR_irda_int_mask);
#endif
	return ;
}

