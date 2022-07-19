#include <common.h>
#include <asm/arch/io.h>
#include <asm/arch/platform_lib/board/power.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/rtk_ipc_shm.h>
#include <asm/arch/system.h>
#include <asm/arch/platform_lib/board/gpio.h>

extern struct RTK119X_ipc_shm ipc_shm;

struct power_saving_config
{
	unsigned int magic;
	char power_down_SDIO;
	char power_down_GSPI;
	char power_down_eMMC;
	char power_down_CardReader;
	char power_down_CP_RNG;
	char power_down_MD;
	char power_down_AE;
	char power_down_VCPU_VE1_VE2_GPU;
	char power_down_VO_TVE;
	char power_down_VideoDAC_A; //fw:power_down_VideoDAC_AtoC;
	char power_down_TP;
	char power_down_SE;
	char power_down_HDMITx_MHLTx;
	char power_down_Audio_I2S;
	char power_down_AudioDAC;
	char power_down_SPDIF;
	char power_down_HDMIRx_MHLRx;
	char power_down_LVDS;
	char power_down_MIPI;
	char power_down_LSADC;
	char power_down_ALL_AV;
	char power_down_ETN;
	char power_down_VFD;
	char power_down_CBUS;
	char power_down_CEC;
	char power_down_IR;
	char power_down_S5; // Notify ACPU that whole SYSTEM will default enter S5 status
	char power_down_reserved2;

};

										 
static struct power_saving_config * pconfig = NULL;

#define rtk_suspend_shm_func(_name, _offset, _def)					\
static void rtk_suspend_##_name##_set(unsigned int val)					\
{											\
	writel(SWAPEND32(SUSPEND_MAGIC_MASK | _def##_MASK(val)), &(ipc_shm._offset));	\
}											\
static unsigned int rtk_suspend_##_name##_get(void)						\
{											\
	unsigned int val = SWAPEND32(readl(&(ipc_shm._offset)));			\
	if (SUSPEND_MAGIC_GET(val) != SUSPEND_MAGIC_KEY) {				\
		printf("[RTD129x_PM] Error! val = 0x%08x\n", val);		\
		return -1;								\
	}										\
	return _def##_GET(val);								\
}

rtk_suspend_shm_func(wakeup_flags, suspend_wakeup_flag, WAKEUP_FLAGS);
rtk_suspend_shm_func(gpio_wakeup_en, gpio_wakeup_enable, GPIO_WAKEUP_EN);
rtk_suspend_shm_func(gpio_wakeup_act, gpio_wakeup_activity, GPIO_WAKEUP_ACT);
rtk_suspend_shm_func(gpio_wakeup_en2, gpio_wakeup_enable2, GPIO_WAKEUP_EN2);
rtk_suspend_shm_func(gpio_wakeup_act2, gpio_wakeup_activity2, GPIO_WAKEUP_ACT2);

void set_suspend_wakeup_src(unsigned int val)
{
	rtk_suspend_wakeup_flags_set(val);
}

unsigned int get_suspend_wakeup_src(void)
{
	return rtk_suspend_wakeup_flags_get();
}

/* Only support igpio for wakeup-src */
/* (0) active low (1) active high    */
int set_suspend_gpio_wakeup_src(int igpio, int activity)
{
	int orig_src, orig_activ, target_src, target_activ;
	int base_shift;
	void (*_gpio_wakeup_en_set)(unsigned int);
	unsigned int (*_gpio_wakeup_en_get)(void);
	void (*_gpio_wakeup_act_set)(unsigned int);
	unsigned int (*_gpio_wakeup_act_get)(void);

	if (igpio < 0 || igpio > ISO_GPIO_MAX) {
		printf("%s, invalid IGPIO:%d\n", __func__, igpio);
		return -1;
	}

	if (igpio < GPIO_WAKEUP_EN_BITS) {
		base_shift = 0;
		_gpio_wakeup_en_set = rtk_suspend_gpio_wakeup_en_set;
		_gpio_wakeup_en_get = rtk_suspend_gpio_wakeup_en_get;
		_gpio_wakeup_act_set = rtk_suspend_gpio_wakeup_act_set;
		_gpio_wakeup_act_get = rtk_suspend_gpio_wakeup_act_get;
	} else {
		base_shift = GPIO_WAKEUP_EN_BITS;
		_gpio_wakeup_en_set = rtk_suspend_gpio_wakeup_en2_set;
		_gpio_wakeup_en_get = rtk_suspend_gpio_wakeup_en2_get;
		_gpio_wakeup_act_set = rtk_suspend_gpio_wakeup_act2_set;
		_gpio_wakeup_act_get = rtk_suspend_gpio_wakeup_act2_get;
	}

	orig_src = _gpio_wakeup_en_get();
	orig_activ = _gpio_wakeup_act_get();

	if (orig_src == -1 || orig_activ == -1) {
		printf("%s, wakeup GPIO not config\n", __func__);
		target_src = 0;
		target_activ = 0;
	} else {
		target_src = orig_src;
		target_activ = orig_activ;
	}

	target_src |= (1 << (igpio - base_shift));
	if (activity)
		target_activ |=  (1 << (igpio - base_shift));
	else
		target_activ &=  ~(1 << (igpio - base_shift));

	_gpio_wakeup_en_set(target_src);
	_gpio_wakeup_act_set(target_activ);

	return 0;
}


void SDIO_power_off(void)
{
	debug("SDIO off, TBD\n");
	//Turn off SDIO (clock from USB)
}

void GSPI_power_off(void)
{	
	debug("GSPI off, TBD\n");
	//Turn off GSPI
}

void eMMC_power_off(void)
{	
	debug("eMMC off, TBD\n");
	//Turn off eMMC
}

void CardReader_power_off(void)
{	
	debug("CardReader off, TBD\n");
	//Turn off Card Reader
}

void CP_RNG_power_off(void)
{	
	debug("CP_RNG off, TBD\n");
	//Turn off CP, RNG
}

void MD_power_off(void)
{	
	debug("MD off, TBD\n");
	//Turn off MD
}

void AE_power_off(void)
{	
	debug("AE off, TBD\n");
	//Turn off AE
}

void VCPU_VE1_VE2_GPU_power_off(void)
{	
	debug("VCPU_VE1_VE2_GPU off, TBD\n");
	//Turn off VCPU VE1,VE2,GPU
}

void VO_TVE_power_off(void)
{	
	debug("VO_TVE off, TBD\n");
	//Turn off display VO, TVE
}

void VideoDAC_A_power_off(void)
{	
	debug("VideoDAC_A off, TBD\n");
	//Turn off Video DAC A
}

void TP_power_off(void)
{	 
	debug("TP off, TBD\n");
	//Turn off TP
}

void SE_power_off(void)
{	
	debug("SE off, TBD\n");
	//Turn off SE
}

void HDMITx_power_off(void)
{	
	debug("HDMITx/MHLTx off, TBD\n");
	//Turn off HDMI Tx
}

void Audio_I2S_power_off(void)
{		
	debug("Audio_I2S off, TBD\n");
	//Turn off Audio I2S in/out
}

void AudioDAC_power_off(void)
{
	debug("AudioDAC off, TBD\n");
	//Turn off Audio DAC
}

void SPDIF_power_off(void)
{	
	debug("SPDIF off, TBD\n");
	//Turn off SPDIF
}

void HDMIRx_power_off(void)
{	
	debug("HDMIRx/MHLRx off, TBD\n");
	//Turn off HDMI Rx (flow PLL?)
}

void LVDS_power_off(void)
{	
	debug("LVDS off, TBD\n");
	//Turn off LVDS (flow, PLL?)
}

void MIPI_power_off(void)
{	
	debug("MIPI off, TBD\n");
	//Turn off MIPI
}

void LSADC_power_off(void)
{
	debug("LSADC off, TBD\n");
	//Turn off LSADC
}

void ALL_AV_power_off(void)
{	
	debug("all AV off, TBD\n");
	//Turn off all AV
}
//ISO	block

void ETN_power_off(void)
{	
	debug("ETN off, TBD\n");		
	//Turn off ETN & PHY
}

void VFD_power_off(void)
{	
	debug("VFD off, TBD\n");
	//Turn off VFD
}

void CBUS_power_off(void)
{
	debug("CBUS off, TBD\n");
	//Turn off CBUS
}

void CEC_power_off(void)
{
	debug("CEC off, TBD\n");
	//Turn off CEC
}

void IR_power_off(void)
{
}

void Enhance_Wifi_storage(void)
{
	debug("Enhance Wifi storage, TBD\n");
}

void disable_soc_full_reset(void)
{
    rtd_outl(ISO_TCWOV_RSTB_PAD, 0);
    printf("Disable Watchdog OE\n");
}

#ifdef CONFIG_POWER_DOWN_S5
void RTK_set_power_on_S5(void)
{
	// First, disable pmic reset so dummy register could be passed
	disable_soc_full_reset();
	
	pconfig =(struct power_saving_config *)POWER_SAVING;
	pconfig->power_down_S5 = 1;
	flush_cache((unsigned long)pconfig, sizeof(struct power_saving_config));
	printf("%s, boot into S5\n", __func__);
}
#endif //CONFIG_POWER_DOWN_S5

void RTK_set_power_saving_config(void)
{
	
	struct power_saving_config temp;	
	pconfig =(struct power_saving_config *)POWER_SAVING;
	ipc_shm.power_saving_ptr = SWAPEND32(POWER_SAVING);
	
	memset(&temp,0x0,sizeof(temp));		   	
	temp.magic = 0x65868380; //PSVA( power saving version A)
	
#ifdef CONFIG_POWER_DOWN_SDIO
	temp.power_down_SDIO =1;	
#endif

#ifdef CONFIG_POWER_DOWN_GSPI
	temp.power_down_GSPI =1;
#endif

#ifdef CONFIG_POWER_DOWN_eMMC
	temp.power_down_eMMC =1;
#endif

#ifdef CONFIG_POWER_DOWN_CardReader
	temp.power_down_CardReader =1;
#endif

#ifdef CONFIG_POWER_DOWN_CP_RNG
	temp.power_down_CP_RNG =1;
#endif

#ifdef CONFIG_POWER_DOWN_MD
	temp.power_down_MD =1;
#endif

#ifdef CONFIG_POWER_DOWN_AE
	temp.power_down_AE =1;
#endif

#ifdef CONFIG_POWER_DOWN_VCPU_VE1_VE2_GPU
	temp.power_down_VCPU_VE1_VE2_GPU =1;
#endif

#ifdef CONFIG_POWER_DOWN_VO_TVE
	temp.power_down_VO_TVE =1;
#endif

#ifdef CONFIG_POWER_DOWN_VideoDAC_A
	temp.power_down_VideoDAC_A =1;
#endif

#ifdef CONFIG_POWER_DOWN_TP
	temp.power_down_TP =1;
#endif

#ifdef CONFIG_POWER_DOWN_SE
	temp.power_down_SE =1;
#endif

#ifdef CONFIG_POWER_DOWN_HDMITx_MHLTx
	temp.power_down_HDMITx_MHLTx =1;
#endif

#ifdef CONFIG_POWER_DOWN_Audio_I2S
	temp.power_down_Audio_I2S =1;
#endif

#ifdef CONFIG_POWER_DOWN_AudioDAC
	temp.power_down_AudioDAC =1;
#endif

#ifdef CONFIG_POWER_DOWN_SPDIF
	temp.power_down_SPDIF =1;
#endif 

#ifdef CONFIG_POWER_DOWN_HDMIRx_MHLRx
	temp.power_down_HDMIRx_MHLRx =1;
#endif

#ifdef CONFIG_POWER_DOWN_LVDS
	temp.power_down_LVDS =1;
#endif

#ifdef CONFIG_POWER_DOWN_MIPI
	temp.power_down_MIPI =1;
#endif

#ifdef CONFIG_POWER_DOWN_LSADC
   temp.power_down_LSADC =1;
#endif

#ifdef CONFIG_POWER_DOWN_ALL_AV
   temp.power_down_ALL_AV =1;
#endif

//ISO	block
#ifdef CONFIG_POWER_DOWN_ETN
	 temp.power_down_ETN =1;
#endif

#ifdef CONFIG_POWER_DOWN_VFD
	temp.power_down_VFD =1;
#endif

#ifdef CONFIG_POWER_DOWN_CBUS
	 temp.power_down_CBUS =1;
#endif

#ifdef CONFIG_POWER_DOWN_CEC
	temp.power_down_CEC =1;
#endif

#ifdef CONFIG_POWER_DOWN_IR
	temp.power_down_IR =1;
#endif

#ifdef CONFIG_POWER_DOWN_S5
	printf("%s:Default POWERE_ON_S5 not set\n", __func__);
#endif
	memcpy(pconfig, &temp, sizeof(temp) );
	flush_cache((unsigned long)pconfig, sizeof(temp));
}


void RTK_power_saving(void)
{
#ifdef CONFIG_POWER_DOWN_SDIO
	SDIO_power_off();	
#endif

#ifdef CONFIG_POWER_DOWN_GSPI
	GSPI_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_eMMC
	eMMC_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_CardReader
	CardReader_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_CP_RNG
	CP_RNG_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_MD
	MD_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_AE
	AE_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_VCPU_VE1_VE2_GPU
	VCPU_VE1_VE2_GPU_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_VO_TVE
	VO_TVE_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_VideoDAC_A
	VideoDAC_A_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_TP
	TP_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_SE
	SE_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_HDMITx_MHLTx
	HDMITx_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_Audio_I2S
	Audio_I2S_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_AudioDAC
	AudioDAC_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_SPDIF
	SPDIF_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_HDMIRx_MHLRx
	HDMIRx_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_LVDS
	LVDS_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_MIPI
	MIPI_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_LSADC
   LSADC_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_ALL_AV
   ALL_AV_power_off();
#endif

//ISO	block
#ifdef CONFIG_POWER_DOWN_ETN
	ETN_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_VFD
	VFD_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_CBUS
	CBUS_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_CEC
	CEC_power_off();
#endif

#ifdef CONFIG_POWER_DOWN_IR
	IR_power_off();
#endif

#ifdef CONFIG_BOARD_QA_RTD1195_WIFI_STORAGE
	Enhance_Wifi_storage();
#endif	

	RTK_set_power_saving_config();
	
}
