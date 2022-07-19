#include <config.h>
#include <common.h>
#include <command.h>
#include <mmc.h>
#include <part.h>
#include <malloc.h>
#include <mmc.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <asm/dma-mapping.h>

#include "rtksdmmc.h"

static struct mmc *sd_mmc = NULL;
static struct rtk_sdmmc_host *sd_rtk_sdmmc_host = NULL;

static u8 g_cmd[6];
#define SD_ALLOC_LENGTH    2048
static u32 *dma_phy_addr = NULL;
static u32 *dma_virt_addr = NULL;

static int rtk_sdmmc_allocate_dma_buf(void);
static int rtk_sdmmc_set_rspparam(struct sdmmc_cmd_pkt *cmd_info);
static int rtk_sdmmc_send_cmd_get_rsp(struct sdmmc_cmd_pkt *cmd_info);
static void rtk_sdmmc_read_rsp(struct rtk_sdmmc_host *rtk_host, u32 *rsp, int reg_count);
static unsigned int mmc_detected = 0;
static u8 rtk_sdmmc_get_rsp_len(u8 rsp_para);
void rtk_sdmmc_sync(struct rtk_sdmmc_host *rtk_host);
static int rtk_sdmmc_stream(struct sdmmc_cmd_pkt *cmd_info);
static u8 rtk_sdmmc_get_rsp_type(struct mmc_cmd* cmd);
//======================== for SD 3.0 mode: TBD =========================
#ifdef CONFIG_SD30

#define MAX_PHASE    31
#define TUNING_CNT    3
#define RCA_SHIFTER                16

static unsigned int sdmmc_rca = 0;

struct timing_phase_path {
        int start;
        int end;
        int mid;
        int len;
};

static int rtk_sdmmc_wait_voltage_stable_low(struct rtk_sdmmc_host *rtk_host)
{
    u8 status = 0;
    u8 i = 0;
    u32 sdmmc_base = rtk_host->sdmmc_base;

    while(1){
        status = readb(sdmmc_base + SD_BUS_STATUS);
        if((status & (SD_DAT3_0_LEVEL | SD_CMD_LEVEL)) == 0x0)
            break;

        if(i++>100) {
		printf("voltage_stable_low failed!!!\n");
            break;
	}
    }

    return 0;
}

static int rtk_sdmmc_wait_voltage_stable_high(struct rtk_sdmmc_host *rtk_host)
{
    u8 status = 0;
    u8 i = 0;
    u32 sdmmc_base = rtk_host->sdmmc_base;

    while(1){
        status = readb(sdmmc_base + SD_BUS_STATUS);
        if((status & (SD_DAT3_0_LEVEL | SD_CMD_LEVEL)) == (SD_DAT3_0_LEVEL | SD_CMD_LEVEL))
            break;
	mdelay(1);
	if(i++>100) {
                printf("voltage_stable_high failed!!!\n");
            break;
        }

    }

    return 0;
}

static int rtk_sdmmc_switch_voltage(struct mmc *mmc, u32 voltage)
{
    struct rtk_sdmmc_host *rtk_host = mmc->priv;
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 pll_base = rtk_host->crt_base;
    int ret = 0;

    if(voltage == MMC_SIGNAL_VOLTAGE_180){	//for double check

        ret = rtk_sdmmc_wait_voltage_stable_low(rtk_host); //check DAT[3:0] are at LOW level

        if(ret < 0)
            goto out;

        writeb(0x3B, sdmmc_base + CARD_CLOCK_EN_CTL); //host stop clk
        mdelay(10); //delay 5 ms to fit SD spec

        /* Workaround : keep IO pad voltage at 3.3v for SD card compatibility, jamestai20141225 */
        writel(0x00000000, sdmmc_base + CR_SD_PAD_CTL);

        rtk_sdmmc_sync(rtk_host);

        writel(0x0004003, pll_base + CR_PLL_SD1);
        mdelay(10); //delay 5 ms to fit SD spec
        writeb(0x3F, sdmmc_base + CARD_CLOCK_EN_CTL); //force output clk
        writeb(0x80, sdmmc_base + SD_BUS_STATUS); //force a short period 1.8v clk
        rtk_sdmmc_sync(rtk_host);

        ret = rtk_sdmmc_wait_voltage_stable_high(rtk_host); //check DAT[3:0] are at HIGH level
        if (ret < 0)
            goto out;
    }

    writeb(0x00, sdmmc_base + SD_BUS_STATUS); //stop 1.8v clk

out:
    return ret;
}
static u8 rtk_sdmmc_search_final_phase(struct rtk_sdmmc_host *rtk_host, u32 phase_map)
{
    struct timing_phase_path path[MAX_PHASE + 1];
    struct timing_phase_path swap;
    int i = 0;
    int j = 0;
    int k = 0;
    int cont_path_cnt = 0;
    int new_block = 1;
    int max_len = 0;
    //int final_path_idx = 0;
    u8 final_phase = 0xFF;

    /* Parse phase_map, take it as a bit-ring */
    for(i = 0 ; i < MAX_PHASE + 1 ; i++){
        if(phase_map & (1 << i)){
            if(new_block){
                new_block = 0;
                j = cont_path_cnt++;
                path[j].start = i;
                path[j].end = i;
            }else
                path[j].end = i;
        }else{
            new_block = 1;
            if(cont_path_cnt){
                /* Calculate path length and middle point */
                int idx = cont_path_cnt - 1;
                path[idx].len = path[idx].end - path[idx].start + 1;
                path[idx].mid = path[idx].start + path[idx].len / 2;
            }
        }
    }

    if(cont_path_cnt == 0){
        printf(" %s No continuous phase path\n", __func__);
        goto finish;
    }else{
        /* Calculate last continuous path length and middle point */
        int idx = cont_path_cnt - 1;
        path[idx].len = path[idx].end - path[idx].start + 1;
        path[idx].mid = path[idx].start + path[idx].len / 2;
    }

    /* Connect the first and last continuous paths if they are adjacent */
    if (!path[0].start && (path[cont_path_cnt - 1].end == MAX_PHASE)){
        /* Using negative index */
        path[0].start = path[cont_path_cnt - 1].start - MAX_PHASE - 1;
        path[0].len += path[cont_path_cnt - 1].len;
        path[0].mid = path[0].start + path[0].len / 2;
        /* Convert negative middle point index to positive one */
        if (path[0].mid < 0)
            path[0].mid += MAX_PHASE + 1;
        cont_path_cnt--;
    }

    /* Sorting path array,jamestai20141223 */
    for(k = 0 ; k < cont_path_cnt ; ++k){
        for(i = 0 ; i < cont_path_cnt - 1 - k ; ++i){
            if(path[i].len < path[i+1].len){
                swap.end = path[i+1].end;
                swap.len = path[i+1].len;
                swap.mid = path[i+1].mid;
                swap.start = path[i+1].start;

                path[i+1].end = path[i].end;
                path[i+1].len = path[i].len;
                path[i+1].mid = path[i].mid;
                path[i+1].start = path[i].start;

                path[i].end = swap.end;
                path[i].len = swap.len;
                path[i].mid = swap.mid;
                path[i].start = swap.start;
            }
        }
    }

    /* Choose the longest continuous phase path */
    max_len = 0;
    final_phase = 0;
    //final_path_idx = 0;
    for(i = 0 ; i < cont_path_cnt ; i++){
        if(path[i].len > max_len){
            max_len = path[i].len;
            if(max_len > 6)    //for compatibility issue, continue len should bigger than 6
                final_phase = (u8)path[i].mid;
            else
                final_phase = 0xFF;
            //final_path_idx = i;
        }
    }
finish:
    //printf("%s Final chosen phase: %d\n", __func__, final_phase);
    return final_phase;
}


static int rtk_sdmmc_change_tx_phase(struct rtk_sdmmc_host *rtk_host, u8 sample_point)
{
    u32 pll_base = rtk_host->crt_base;
    unsigned int temp_reg = 0;

    temp_reg = readl(pll_base + CR_PLL_SD1);
    temp_reg = (temp_reg & ~0x000000F8) | (sample_point << 3);
    writel(temp_reg,  pll_base + CR_PLL_SD1);

    rtk_sdmmc_sync(rtk_host);
    udelay(100);

    return 0;
}

static int rtk_sdmmc_change_rx_phase(struct rtk_sdmmc_host *rtk_host, u8 sample_point)
{
    u32 pll_base = rtk_host->crt_base;
    unsigned int temp_reg = 0;

    temp_reg = readl(pll_base + CR_PLL_SD1);
    temp_reg = (temp_reg & ~0x00001F00) | (sample_point << 8);
    writel(temp_reg, pll_base + CR_PLL_SD1);

    rtk_sdmmc_sync(rtk_host);
    udelay(100);

    return 0;
}

static int rtk_sdmmc_tuning_tx_cmd(struct rtk_sdmmc_host *rtk_host, u8 sample_point)
{
    struct mmc_cmd cmd;
    struct sdmmc_cmd_pkt cmd_info;
    u32 sdmmc_base = rtk_host->sdmmc_base;

    rtk_sdmmc_change_tx_phase(rtk_host, sample_point);

    memset(&cmd, 0x00, sizeof(struct mmc_cmd));
    memset(&cmd_info, 0x00, sizeof(struct sdmmc_cmd_pkt));

    cmd.opcode = MMC_CMD_SEND_STATUS;
    cmd.arg = (sdmmc_rca << RCA_SHIFTER);
    cmd.flags = 0x0;
    cmd_info.cmd = &cmd;
    cmd_info.rtk_host = rtk_host;
    cmd_info.rsp_para2 = 0x41;
    cmd_info.rsp_len = rtk_sdmmc_get_rsp_len(0x41);
    rtk_sdmmc_send_cmd_get_rsp(&cmd_info);
    
    if(readb(sdmmc_base + SD_TRANSFER) & 0x10)
        return -1;
    return 0;
}

static int rtk_sdmmc_tuning_tx(struct rtk_sdmmc_host *rtk_host)
{
    int sample_point;
    int ret = 0;
    int i = 0;
    u32 raw_phase_map[TUNING_CNT] = {0};
    u32 phase_map = 0;
    u8 final_phase = 0;

    for(sample_point = 0 ; sample_point <= MAX_PHASE ; sample_point++){
        for(i = 0 ; i < TUNING_CNT ; i++){
            /*if (!(rtk_host->rtflags & RTKCR_FCARD_DETECTED)){
                ret = -MMC_ERR_RMOVE;
                goto out ;
            }*/

            ret = rtk_sdmmc_tuning_tx_cmd(rtk_host, (u8)sample_point);
            if(0 == ret)
                raw_phase_map[i] |= (1 << sample_point);
        }
    }

    phase_map = 0xFFFFFFFF;
    for(i = 0 ; i < TUNING_CNT ; i++){
        //rtk_sdmmc_debug("%s TX raw_phase_map[%d] = 0x%08x\n", __func__, i, raw_phase_map[i]);
        phase_map &= raw_phase_map[i];
    }
    printf("%s TX phase_map = 0x%08x\n", __func__, phase_map);

    if(phase_map){
        final_phase = rtk_sdmmc_search_final_phase(rtk_host, phase_map);
        printf("%s final phase = 0x%08x\n", __func__, final_phase);
        if(final_phase == 0xFF){
            //rtk_sdmmc_debug("%s final phase = 0x%08x\n", __func__, final_phase);
            ret = -EINVAL;
            goto out ;
        }
        rtk_sdmmc_change_tx_phase(rtk_host, final_phase);
        ret = 0;
        goto out ;
    }else{
        printf("%s  fail !phase_map\n", __func__);
        ret = -EINVAL;
        goto out ;
    }

out:
    return ret;
}

static int rtk_sdmmc_tuning_rx_cmd(struct rtk_sdmmc_host *rtk_host, u8 sample_point)
{
    struct mmc_cmd cmd;
    struct mmc_data data;
    struct sdmmc_cmd_pkt cmd_info;
    u32 sdmmc_base = rtk_host->sdmmc_base;
    int err = 0;

    MY_CLR_ALIGN_BUFFER();
    MY_ALLOC_CACHE_ALIGN_BUFFER(char, ssr, 64);

    rtk_sdmmc_change_rx_phase(rtk_host, sample_point);
    
    cmd.opcode = MMC_SEND_TUNING_BLOCK;
    cmd.arg = 0;
    cmd.flags = 0x35;

    data.dest = (char *)ssr;
    data.blocksize = 64;
    data.blocks = 1;
    data.flags = MMC_DATA_READ;

    memset(&cmd_info, 0x00, sizeof(struct sdmmc_cmd_pkt));
    cmd_info.cmd = &cmd;
    cmd_info.rtk_host = rtk_host;
    cmd_info.rsp_para2 = rtk_sdmmc_get_rsp_type(cmd_info.cmd);
    cmd_info.rsp_len = rtk_sdmmc_get_rsp_len(cmd_info.rsp_para2);
    cmd_info.data = &data;

    rtk_sdmmc_stream(&cmd_info);
 
    if(err) {
	printf("tuning rx failed...\n");
	return err;
    }

    //if(readb(sdmmc_base + SD_STATUS1) & 0x01)
      //  return -1;
if(readb(sdmmc_base + SD_TRANSFER) & 0x10)
        return -1;
    return 0;
}

static int rtk_sdmmc_tuning_rx(struct rtk_sdmmc_host *rtk_host)
{
    int sample_point = 0;
    int ret = 0;
    int i = 0;
    u32 raw_phase_map[TUNING_CNT] = {0};
    u32 phase_map = 0;
    u8 final_phase = 0;

    for(sample_point = 0 ; sample_point <= MAX_PHASE ; sample_point++){
        for(i = 0 ; i < TUNING_CNT ; i++){
            /*if (!(rtk_host->rtflags & RTKCR_FCARD_DETECTED)){
                ret = -MMC_ERR_RMOVE;
                goto out ;
            }*/

            ret = rtk_sdmmc_tuning_rx_cmd(rtk_host, (u8)sample_point);
            if (0 == ret)
                raw_phase_map[i] |= (1 << sample_point);
        }
    }

    phase_map = 0xFFFFFFFF;
    for(i = 0 ; i < TUNING_CNT ; i++){
  //      rtk_sdmmc_debug("%s RX raw_phase_map[%d] = 0x%08x\n", __func__, i, raw_phase_map[i]);
        phase_map &= raw_phase_map[i];
    }
    printf("%s RX phase_map = 0x%08x\n", __func__, phase_map);

    if(phase_map){
        final_phase = rtk_sdmmc_search_final_phase(rtk_host, phase_map);
        printf("%s final phase = 0x%08x\n", __func__, final_phase);
        if (final_phase == 0xFF){
            printf("%s final phase = 0x%08x\n", __func__, final_phase);
            ret = -EINVAL;
            goto out ;
        }
        rtk_sdmmc_change_rx_phase(rtk_host, final_phase);
        ret = 0;
        goto out ;
    }else{
        printf("%s  fail !phase_map\n", __func__);
        ret = -EINVAL;
        goto out ;
    }
out:
    return ret;
}

static int rtk_sdmmc_execute_tuning(struct mmc *mmc, u32 opcode)
{
    struct rtk_sdmmc_host *rtk_host = mmc->priv;
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 pll_base = rtk_host->crt_base;
    u32 sysbrdg_base = rtk_host->sysbrdg;
    int ret = 0;
    unsigned int reg_tmp = 0;
    unsigned int reg_tmp2 = 0;
    unsigned int reg_tuned3318 = 0;

    reg_tmp2 = readl(pll_base + CR_PLL_SD2); //disable spectrum
    writel((reg_tmp2 & 0xFFFF1FFF), pll_base + CR_PLL_SD2); //PLL_SD2 clear [15:13]

    /*if tune tx phase fail, down 8MHz and retry*/
    do{
        ret = rtk_sdmmc_tuning_tx(rtk_host);
        /*if(ret == -MMC_ERR_RMOVE){
            printf("%s: Tuning TX fail.\n", __func__);
            return ret;
        }else*/ if(ret){
            reg_tmp = readl(pll_base + CR_PLL_SD3);
            reg_tuned3318 = (reg_tmp & 0x03FF0000) >> 16;
            if (reg_tuned3318 <= 100){
                printf("%s: Tuning TX fail\n", __func__);
                return ret;
            }
            writel(readl(sdmmc_base + CR_SD_CKGEN_CTL) | 0x00070000, sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to 4MHz by Hsin-yin
            reg_tmp = ((reg_tmp & (~0x3FF0000)) | ((reg_tuned3318 - 8) << 16)); //down 8MHz

            if(readl(sysbrdg_base+0x204)!=0x0)
                writel(0x40000000,sdmmc_base+0x2c);
            writel(0x00000006, pll_base + 0x01EC);       //JIM modified, 1AC->1EC
            writel(reg_tmp, pll_base + CR_PLL_SD3);
            mdelay(2);
            writel(0x00000007, pll_base + 0x01EC);        //JIM modified, 1AC->1EC
            if(readl(sysbrdg_base+0x204)!=0x0)
                writel(0x00000000,sdmmc_base+0x2c);
            writel(readl(sdmmc_base + CR_SD_CKGEN_CTL) & 0xFFF8FFFF, sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to normal clock source by Hsin-yin
            writeb(readb(sdmmc_base + SD_CONFIGURE1) & 0xEF, sdmmc_base + SD_CONFIGURE1); //Reset FIFO pointer by Hsin-yin
        }
    }while(ret);

    if(ret){
        printf("%s: Tuning TX  fail\n", __func__);
        return ret;
    }

    ret = rtk_sdmmc_tuning_rx(rtk_host);
    writel(reg_tmp2, pll_base + CR_PLL_SD2); //enable spectrum

    if(ret){
        printf("%s: Tuning RX fail\n", __func__);
        return ret;
    }

    //printk(KERN_INFO "%s CR_PLL_SD3: %d (0x%02x)\n", __func__, (readl(pll_base + CR_PLL_SD3) >> 16), (readl(pll_base + CR_PLL_SD3) >> 16));
    //printk(KERN_INFO "%s CLK_GEN DVI: %d\n", __func__, 1 << (readl(sdmmc_base + CR_SD_CKGEN_CTL) & 0x03));

    return ret;
}

#endif
//=======================================================================

void rtk_sdmmc_sync(struct rtk_sdmmc_host *rtk_host){
    writel(0x00000000, rtk_host->sysbrdg + SDMMC_SYNC);
}

static void rtk_sdmmc_reset(struct rtk_sdmmc_host *rtk_host)
{
    if(rtk_host==NULL) return;

    u32 sdmmc_base = rtk_host->sdmmc_base;
#ifdef CONFIG_SD30
    sdmmc_rca = 0;
#endif

    writel(0x00000000, sdmmc_base + CR_SD_DMA_CTL3);
    writeb(0x00, sdmmc_base + SD_TRANSFER);
    writeb(0xFF, sdmmc_base + CR_CARD_STOP); //SD Card module transfer stop and idle state.
    writeb(0x00, sdmmc_base + CR_CARD_STOP); //SD Card module transfer start.

    rtk_sdmmc_sync(rtk_host);
}

static void rtk_sdmmc_set_div(struct rtk_sdmmc_host *rtk_host, u32 set_div)
{
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u8 tmp_div = 0;

    //sync();
	rtk_sdmmc_sync(rtk_host);
    tmp_div = readb(sdmmc_base + SD_CONFIGURE1) & ~MASK_CLOCK_DIV;
    if(set_div != CLOCK_DIV_NON){
        writeb(tmp_div | set_div | SDCLK_DIV, sdmmc_base + SD_CONFIGURE1);
    }else{
        writeb(tmp_div, sdmmc_base + SD_CONFIGURE1);
    }
    //sync();
	rtk_sdmmc_sync(rtk_host);
}

static void rtk_sdmmc_set_speed(struct rtk_sdmmc_host *rtk_host, u8 level)
{
	u32 sdmmc_base = rtk_host->sdmmc_base;

    switch(level){
        case 0: //ddr50 , highest speed
            //printf("%s: speed 2100\n", __func__);
            writel(0x00002100, sdmmc_base + CR_SD_CKGEN_CTL);
            break;
        case 1:
        	//printf("%s: speed 2101\n", __func__);
            writel(0x00002101, sdmmc_base + CR_SD_CKGEN_CTL);
            break;
        case 2:
        	//printf("%s: speed 2102\n", __func__);
            writel(0x00002102, sdmmc_base + CR_SD_CKGEN_CTL);
            break;
        case 3:
        	//printf("%s: speed 2103\n", __func__);
            writel(0x00002103, sdmmc_base + CR_SD_CKGEN_CTL);
            break;
        default :
        	//printf("%s: default speed 2102\n", __func__);
            writel(0x00002102, sdmmc_base + CR_SD_CKGEN_CTL);
            break;
    }
rtk_sdmmc_sync(rtk_host);
    //sync();
}

static void rtk_sdmmc_speed(struct rtk_sdmmc_host *rtk_host, enum sdmmc_clock_speed sd_speed)
{
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 pll_base = rtk_host->crt_base;
    u32 emmc_base = rtk_host->emmc_base;
    u32 sysbrdg_base = rtk_host->sysbrdg;

    switch(sd_speed){
        case SDMMC_CLOCK_200KHZ:
            //printf("%s: speed SDMMC_CLOCK_200KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_256); //0x580 = 0xd0
            rtk_sdmmc_set_speed(rtk_host, 1); //0x478 = 0x2101
            break;
        case SDMMC_CLOCK_400KHZ:
            //printf("%s: speed SDMMC_CLOCK_400KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_256); //0x580 = 0xd0
            rtk_sdmmc_set_speed(rtk_host, 0); //0x478 = 0x2100
            break;
        case SDMMC_CLOCK_6200KHZ:
            //printf("%s: speed SDMMC_CLOCK_6200KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_NON); //0x580 = 0x10
            rtk_sdmmc_set_speed(rtk_host, 3); //0x478 = 0x2103
            break;
        case SDMMC_CLOCK_25000KHZ:
       	   // printf("%s: speed SDMMC_CLOCK_25000KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_NON); //0x580 = 0x10
            rtk_sdmmc_set_speed(rtk_host, 1); //0x478 = 0x2101
            break;
        case SDMMC_CLOCK_50000KHZ:
            //printf("%s: speed SDMMC_CLOCK_50000KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_NON); //0x580 = 0x10
            rtk_sdmmc_set_speed(rtk_host, 0); //0x478 = 0x2100
            break;
        case SDMMC_CLOCK_100000KHZ:
            printf("SD 3.0 SDR50 mode!!!\n");
	    writel(0x00005555, emmc_base + 0x634);         //JIM modified this part from 3333 to 5555 to enlarge the signal to work around a issue that can not recognize some SD 3.0 card
            writel(0x55555555, emmc_base + 0x638);

            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_NON); //0x580 = 0x10
            rtk_sdmmc_set_speed(rtk_host, 0); //0x478 = 0x2100
            break;
	case SDMMC_CLOCK_208000KHZ:
	    printf("SD 3.0 SDR104 mode!!!\n");
	    writel(0x0000bbbb, emmc_base + 0x634);
            writel(0xbbbbbbbb, emmc_base + 0x638);

	    if(readl(sysbrdg_base+0x204)!=0x0)
                        writel(0x40000000,sdmmc_base+0x2c);
            writel(0x00000006, pll_base + 0x01EC);         //JIM modified, 1AC->1EC
            writel(readl(sdmmc_base + CR_SD_CKGEN_CTL) | 0x00070000, sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to 4MHz by Hsin-yin
            mdelay(2);
            writel(0x00000007, pll_base + 0x01EC);          //JIM modified, 1AC->1EC
            if(readl(sysbrdg_base+0x204)!=0x0)
                        writel(0x00000000,sdmmc_base+0x2c);

            if(readl(sysbrdg_base+0x204)!=0x0) {
                writel(0x40000000,sdmmc_base+0x2c);
                mdelay(100);
                writel(0x00000006, pll_base + 0x01EC);            //JIM modified, 1AC->1EC
                writel(0x00b64388, pll_base + CR_PLL_SD3); //SD clock rate formula: (ssc_div_n +3) *4.5/4, jamestai20141222
                mdelay(2);
                writel(0x00000007, pll_base + 0x01EC);             //JIM modified, 1AC->1EC
                writel(0x00000000,sdmmc_base+0x2c);
            }
            else {
                /*Workaround: PLL clcok 208 MHz  */
                writel(0x00000006, pll_base + 0x01EC);           //JIM modified, 1AC->1EC
                writel(0x00b74388, pll_base + CR_PLL_SD3); //SD clock rate formula: (ssc_div_n +3) *4.5/4, jamestai20141222
                mdelay(2);
                writel(0x00000007, pll_base + 0x01EC);           //JIM modified, 1AC->1EC

                mdelay(100);
                writel(0x00000006, pll_base + 0x01EC);            //JIM modified, 1AC->1EC
                writel(0x00b64388, pll_base + CR_PLL_SD3); //SD clock rate formula: (ssc_div_n +3) *4.5/4, jamestai20141222
                mdelay(2);
                writel(0x00000007, pll_base + 0x01EC);             //JIM modified, 1AC->1EC
            }

            if(readl(sysbrdg_base+0x204)!=0x0)
                writel(0x40000000,sdmmc_base+0x2c);
            writel(0x00000006, pll_base + 0x01EC);              //JIM modified, 1AC->1EC
            writel(readl(sdmmc_base + CR_SD_CKGEN_CTL) & 0xFFF8FFFF, sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to normal clock source by Hsin-yin
            mdelay(2);
            writel(0x00000007, pll_base + 0x01EC);              //JIM modified, 1AC->1EC
            if(readl(sysbrdg_base+0x204)!=0x0)
                writel(0x00000000,sdmmc_base+0x2c);

            writeb(readb(sdmmc_base + SD_CONFIGURE1) & 0xEF, sdmmc_base + SD_CONFIGURE1); //Reset FIFO pointer by Hsin-yin

            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_NON); //0x580 = 0x10
            rtk_sdmmc_set_speed(rtk_host, 0); //0x478 = 0x2100
	    break;
        default :
        	//printf("%s: default speed SDMMC_CLOCK_400KHZ\n", __func__);
            rtk_sdmmc_set_div(rtk_host, CLOCK_DIV_256); //0x580 = 0xd0
            rtk_sdmmc_set_speed(rtk_host, 0); //0x478 = 0x2100
            break;
    }
rtk_sdmmc_sync(rtk_host);
   // sync();
}

int rtk_sdmmc_cpu_wait(struct rtk_sdmmc_host *rtk_host, u8 cmdcode){

    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 start = 0;
    u32 tick = 0;

    sync();

    writeb((u8)(cmdcode | START_EN), sdmmc_base + SD_TRANSFER);
	start = get_timer(0);

    while(1){

    	sync();

    	if((readb(sdmmc_base + SD_STATUS2) & 0x01) == 1){
            return COMM_ERR;
        }

        if((readb(sdmmc_base + SD_TRANSFER) & (END_STATE | IDLE_STATE)) == (END_STATE | IDLE_STATE)){
            break;
        }

        if((readb(sdmmc_base + SD_TRANSFER) & (ERR_STATUS)) == (ERR_STATUS)){
			if(rtk_host!=NULL) {
				printf("%s(%d) trans error(error status) :\n opcode=%d trans: 0x%08x, st1: 0x%08x, st2: 0x%08x, bus: 0x%08x\n",
					__func__,
					__LINE__,
					rtk_host->cmd_opcode,
					readb(sdmmc_base + SD_TRANSFER),
					readb(sdmmc_base + SD_STATUS1),
					readb(sdmmc_base + SD_STATUS2),
					readb(sdmmc_base + SD_BUS_STATUS));
			}
			else {
				printf("%s(%d) trans error(error status) :\n trans: 0x%08x, st1: 0x%08x, st2: 0x%08x, bus: 0x%08x\n",
					__func__,
					__LINE__,
					readb(sdmmc_base + SD_TRANSFER),
					readb(sdmmc_base + SD_STATUS1),
					readb(sdmmc_base + SD_STATUS2),
					readb(sdmmc_base + SD_BUS_STATUS));
			}
            return COMM_ERR;
        }
		tick = get_timer(0);
        if ( (tick - start)  > 3000 ) {
			if(rtk_host!=NULL)
				printf("%s: opcode=%d timeout waiting for SD_TRANSFER (%x) to clear\n", __func__, rtk_host->cmd_opcode,readb(sdmmc_base + SD_TRANSFER));
			else
				printf("%s: timedout waiting for SD_TRANSFER (%x) to clear\n", __func__, readb(sdmmc_base + SD_TRANSFER));
			rtk_sdmmc_reset(rtk_host);
			return TIMEOUT;
		}
    }

    return 0;
}

static u8 rtk_sdmmc_chk_cmdcode(struct sdmmc_cmd_pkt *cmd_info)
{
    u8 cmdcode = 0;

    if(cmd_info->cmd->opcode < 59){
        if(cmd_info->cmd->opcode == 8 && mmc_detected == 1)   //jim comment
            cmdcode = SD_NORMALREAD;
        else
           cmdcode = rtk_sdmmc_cmdcode[cmd_info->cmd->opcode][0];

        if(cmd_info->data->flags & MMC_DATA_WRITE){
            if(cmd_info->cmd->opcode == 42)
                cmdcode = SD_NORMALWRITE;
            else if(cmd_info->cmd->opcode == 56)
                cmdcode = SD_AUTOWRITE2;
        }
    }else
        cmdcode = SD_CMD_UNKNOW;

    return cmdcode;
}

static int rtk_sdmmc_stream_cmd(u16 cmdcode, struct sdmmc_cmd_pkt *cmd_info, u8 data_len, int dma_leng)
{
    u8 cmd_idx = cmd_info->cmd->opcode;
    u32 sd_arg = 0;
    s8 rsp_para1 = 0;
    s8 rsp_para2 = 0;
    s8 rsp_para3 = 0;
    int rsp_len = cmd_info->rsp_len;
    int ret = 0;
    u32 data = cmd_info->dma_buffer;
    u32 sa = 0;
    u32 *rsp = (u32 *)&cmd_info->cmd->resp;
    u16 byte_count = cmd_info->byte_count;
    u16 block_count = cmd_info->block_count;

    struct rtk_sdmmc_host *rtk_host = cmd_info->rtk_host;
    u32 sdmmc_base = rtk_host->sdmmc_base;

    if(!data || rsp == NULL){
        BUG_ON(1);
    }

    rtk_sdmmc_set_rspparam(cmd_info);
    sd_arg = cmd_info->cmd->arg;

    if (rsp_para1 != -1)
        rsp_para1 = cmd_info->rsp_para1;

    /* Fix CRC error for SD_AUTOWRITE3, jamestai20150325 */
    if(cmdcode == SD_AUTOWRITE3){
        rsp_para2 = 0;
    }else{
        rsp_para2 = cmd_info->rsp_para2;
    }

    if(rsp_para3 != -1)
        rsp_para3 = cmd_info->rsp_para3;

    sa = (data / 8);
    //sa = ((u32)data / 8);
    
    if((cmdcode == SD_NORMALWRITE)){
   		byte_count = 512;
    }
    else if(cmdcode == SD_NORMALREAD && mmc_detected == 1){
    	byte_count = 512;
    }
    
    g_cmd[0] = (0x40 | cmd_idx);
    g_cmd[1] = (sd_arg >> 24) & 0xff;
    g_cmd[2] = (sd_arg >> 16) & 0xff;
    g_cmd[3] = (sd_arg >> 8) & 0xff;
    g_cmd[4] = sd_arg & 0xff;
    g_cmd[5] = 0x00;

    writeb(g_cmd[0], sdmmc_base + SD_CMD0); //0x10
    writeb(g_cmd[1], sdmmc_base + SD_CMD1); //0x14
    writeb(g_cmd[2], sdmmc_base + SD_CMD2); //0x18
    writeb(g_cmd[3], sdmmc_base + SD_CMD3); //0x1C
    writeb(g_cmd[4], sdmmc_base + SD_CMD4); //0x20
    writeb(g_cmd[5], sdmmc_base + SD_CMD5); //0x20

    if(rsp_para1 != -1){
        writeb(readb(sdmmc_base + SD_CONFIGURE1) | rsp_para1, sdmmc_base + SD_CONFIGURE1); //0x0C
    }

    writeb(rsp_para2, sdmmc_base + SD_CONFIGURE2); //0x0C

    if(rsp_para3 != -1){
        writeb(readb(sdmmc_base + SD_CONFIGURE3) | rsp_para3, sdmmc_base + SD_CONFIGURE3); //0x0C
    }

    writeb(byte_count, sdmmc_base + SD_BYTE_CNT_L); //0x24
    writeb(byte_count >> 8, sdmmc_base + SD_BYTE_CNT_H); //0x28
    writeb(block_count, sdmmc_base + SD_BLOCK_CNT_L); //0x2C
    writeb(block_count >> 8, sdmmc_base + SD_BLOCK_CNT_H); //0x30

	//printf("SD_CONFIGURE1 = %x, SD_CONFIGURE2= %x, SD_CONFIGURE3=%x, SD_BYTE_CNT_L=%x, SD_BYTE_CNT_H=%x, SD_BLOCK_CNT_L=%x, SD_BLOCK_CNT_H=%x\n",readb(sdmmc_base + SD_CONFIGURE1),readb(sdmmc_base + SD_CONFIGURE2),readb(sdmmc_base + SD_CONFIGURE3),readb(sdmmc_base + SD_BYTE_CNT_L),readb(sdmmc_base + SD_BYTE_CNT_H),readb(sdmmc_base + SD_BLOCK_CNT_L),readb(sdmmc_base + SD_BLOCK_CNT_H));

    if(cmd_info->data->flags & MMC_DATA_READ){    //jim modified cmd_info->data->flags
        writel((u32)sa, sdmmc_base + CR_SD_DMA_CTL1);
        writel(block_count, sdmmc_base + CR_SD_DMA_CTL2);

        if(data_len == RESP_LEN64) {
            writel(RSP64_SEL | DDR_WR | DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);
        }
        else if(data_len == RESP_LEN17) {
            writel(RSP17_SEL | DDR_WR | DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);
        }
        else
            writel(DDR_WR | DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);

    }
    else if(cmd_info->data->flags & MMC_DATA_WRITE){    //jim modified cmd_info->data->flags
       // rtk_sdmmc_debug("%s: DMA sa = 0x%x\nDMA len = 0x%x\nDMA set = 0x%x\n", __func__, (u32)sa, block_count, DMA_XFER);
        writel((u32)sa, sdmmc_base + CR_SD_DMA_CTL1);
        writel(block_count, sdmmc_base + CR_SD_DMA_CTL2);

        if(data_len == RESP_LEN64) {
            writel(RSP64_SEL | DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);
        }
        else if(data_len == RESP_LEN17) {
            writel(RSP17_SEL | DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);
        }
        else
            writel(DMA_XFER, sdmmc_base + CR_SD_DMA_CTL3);
    }
    /*printf("CR_SD_DMA_CTL1 = %x, CR_SD_DMA_CTL2=%x, CR_SD_DMA_CTL3=%x\n",readl(sdmmc_base + CR_SD_DMA_CTL1),readl(sdmmc_base + CR_SD_DMA_CTL2),readl(sdmmc_base + CR_SD_DMA_CTL3));*/
    rtk_host->cmd_opcode = cmd_idx;
#if 0
    flush_dcache_range(cmd_info->dma_buffer,cmd_info->dma_buffer+dma_leng);
#else /* porting issue */
	flush_cache(cmd_info->dma_buffer, dma_leng);
#endif
    //rtk_sdmmc_get_cmd_timeout(cmd_info);    //comment by jim
    ret = rtk_sdmmc_cpu_wait(rtk_host, cmdcode);

#ifdef CONFIG_SD30
    /* Reset dat64_sel and rsp17_sel, #CMD19 DMA won't be auto-cleared */
    if(cmd_info->cmd->opcode == MMC_SEND_TUNING_BLOCK)
        writel(0x00000000, sdmmc_base + CR_SD_DMA_CTL3);
#endif

    if(ret == 0){
        if((cmdcode == SD_AUTOREAD1) || (cmdcode == SD_AUTOWRITE1)){
         //   rtk_sdmmc_debug("%s: auto read/write 1 skip response\n", __func__);
        }
        else{
            rtk_sdmmc_read_rsp(rtk_host,rsp, rsp_len);
           // rtk_sdmmc_debug("%s: stream cmd done\n", __func__);
        }
		//printf("stream_cmd: cmd=%d, cmd_arg=%x, cmd_flag=%x, rsp_para2=%x, rsp[0]=%x, rsp[1]=%x, rsp[2]=%x, rsp[3]=%x, rsp[4]=%x, SD_TRANSFER=%x\n",cmd_idx, sd_arg, cmd_info->cmd->flags, rsp_para2, rsp[0], rsp[1], rsp[2],rsp[3],rsp[4],readb(sdmmc_base + SD_TRANSFER));
    }

    return ret;
}

#if 0

static int rtk_sdmmc_stream(struct sdmmc_cmd_pkt *cmd_info)
{
	u8 cmd_idx = cmd_info->cmd->opcode;
	int ret = 0;
	u32 i = 0;
	//u32 dir = 0;
	//u32 dma_nents = 0;
	u32 dma_leng = 0;
	u32 dma_addr = 0;
	
	u32 old_arg = 0;
	u16 cmdcode = 0;
	u8 data_len = 0;
	//struct mmc_host *host = cmd_info->rtk_host->mmc;
	//struct rtk_sdmmc_host *rtk_host = cmd_info->rtk_host;


	//if(cmd_info->data->flags & MMC_DATA_READ){
	//    dir = DMA_FROM_DEVICE;
	//}else{
	//    dir = DMA_TO_DEVICE;
	//}

	cmd_info->data->bytes_xfered = 0;

	old_arg = cmd_info->cmd->arg;

	for(i = 0 ; i < cmd_info->data->blocks ; i++) {
		u32 blk_cnt = 0;
		
		if(cmd_idx==SD_CMD_APP_SEND_SCR)
			dma_leng = 64;
		else
			dma_leng = cmd_info->data->blocksize;//cmd_info->data->buf_len;	//jim comment
		
		//dma_addr = sg_dma_address(sg);
		dma_addr = (uintptr_t)cmd_info->data->dest;	//jim comment
		
		//printf("dma_addr: 0x%x, dma_leng: 0x%x\n",dma_addr, dma_leng);
		
		if((cmd_idx == SD_CMD_SWITCH_FUNC) && (cmd_info->cmd->flags | MMC_CMD_ADTC)){
			cmd_info->byte_count = 0x40;
			blk_cnt = dma_leng / 0x40;
			data_len = RESP_LEN64;
		}
		else if((cmd_idx == MMC_CMD_SEND_STATUS) && ((cmd_info->cmd->flags & (0x3<<5)) == MMC_CMD_ADTC)){
			cmd_info->byte_count = 0x40;
			blk_cnt = dma_leng / 0x40;
			data_len = RESP_LEN64;
		}
#ifdef CONFIG_SD30
		else if( ( cmd_idx == MMC_SEND_TUNING_BLOCK ) || ( cmd_idx == SD_CMD_APP_SEND_SCR ) ){ /* porting issue: add parentheses around comparison */
			cmd_info->byte_count = 0x40; //rtk HW limite, one trigger 512 byte pass.
			blk_cnt = 1;
			data_len = RESP_LEN64;
		}
#else
		else if(cmd_idx == SD_CMD_APP_SEND_SCR){
			cmd_info->byte_count = 0x40; //rtk HW limite, one trigger 512 byte pass.
			blk_cnt = 1;
			data_len = RESP_LEN64;
		}
#endif
		else if((cmd_idx == MMC_CMD_ALL_SEND_CID) | (cmd_idx == MMC_CMD_SEND_CSD) | (cmd_idx == MMC_CMD_SEND_CID)){
			cmd_info->byte_count = 0x11;
			blk_cnt = dma_leng / 0x11;
			data_len = RESP_LEN17;
		}
		else{
			cmd_info->byte_count = BYTE_CNT; //rtk HW limite, one trigger 512 byte pass.
			blk_cnt = dma_leng / BYTE_CNT;
			data_len = 0;
		}
		
		if(blk_cnt == 0 && dma_leng){
			blk_cnt = 1;
		}

        cmd_info->block_count = blk_cnt;
        cmd_info->dma_buffer = dma_addr;
        cmdcode = rtk_sdmmc_chk_cmdcode(cmd_info);    //jim add
        ret = rtk_sdmmc_stream_cmd(cmdcode, cmd_info, data_len, dma_leng);

        if(ret == 0){
            cmd_info->cmd->arg += 1;//dma_leng;
            cmd_info->data->bytes_xfered += dma_leng;    //jim comment
        }

		if(cmd_idx==MMC_CMD_WRITE_MULTIPLE_BLOCK)
			cmd_info->data->src= cmd_info->data->src + cmd_info->data->blocksize;
		else if(cmd_idx==MMC_CMD_READ_MULTIPLE_BLOCK)
			cmd_info->data->dest= cmd_info->data->dest + cmd_info->data->blocksize;

		if(ret){
	        cmd_info->cmd->arg = old_arg;
	        break;
		}

    }

    g_cmd[0] = 0x00;

    return ret;
}

#else /* improve streaming performance */

#define CR_MAX_BLK_XFER_CNT (128)
#define CR_MAX_BYTE_XFER (CR_MAX_BLK_XFER_CNT<<9)

static int rtk_sdmmc_stream(struct sdmmc_cmd_pkt *cmd_info)
{
	u8 cmd_idx = cmd_info->cmd->opcode;
	int ret = 0;
	u32 i = 0;
	u32 dma_leng = 0;
	u32 dma_addr = 0;
	u32 cur_blk_xfer_count;
	u32 cur_dma_leng = 0;
	u32 old_arg = 0;
	u16 cmdcode = 0;
	u8 data_len = 0;
	u32 blk_cnt = 0;

	cmd_info->data->bytes_xfered = 0;

	old_arg = cmd_info->cmd->arg;

	if(cmd_idx==SD_CMD_APP_SEND_SCR)
		dma_leng = 64;
	else {
		dma_leng = cmd_info->data->blocks * cmd_info->data->blocksize;
	}

	//dma_addr = sg_dma_address(sg);
	dma_addr = (uintptr_t)cmd_info->data->dest;	//jim comment

	//DDDDYELLOW("blks# %d, blksize %d, dma_length 0x%08x, dma addr 0x%08x\n", cmd_info->data->blocks, cmd_info->data->blocksize, dma_leng, dma_addr);
	//printf("dma_addr: 0x%x, dma_leng: 0x%x\n",dma_addr, dma_leng);

	if((cmd_idx == SD_CMD_SWITCH_FUNC) && (cmd_info->cmd->flags | MMC_CMD_ADTC)){
		cmd_info->byte_count = 0x40;
		blk_cnt = dma_leng / 0x40;
		data_len = RESP_LEN64;
	}
	else if((cmd_idx == MMC_CMD_SEND_STATUS) && ((cmd_info->cmd->flags & (0x3<<5)) == MMC_CMD_ADTC)){
		cmd_info->byte_count = 0x40;
		blk_cnt = dma_leng / 0x40;
		data_len = RESP_LEN64;
	}
#ifdef CONFIG_SD30
	else if( ( cmd_idx == MMC_SEND_TUNING_BLOCK ) || ( cmd_idx == SD_CMD_APP_SEND_SCR ) ){ /* porting issue: add parentheses around comparison */
		cmd_info->byte_count = 0x40; //rtk HW limite, one trigger 512 byte pass.
		blk_cnt = 1;
		data_len = RESP_LEN64;
	}
#else
	else if(cmd_idx == SD_CMD_APP_SEND_SCR){
		cmd_info->byte_count = 0x40; //rtk HW limite, one trigger 512 byte pass.
		blk_cnt = 1;
		data_len = RESP_LEN64;
	}
#endif
	else if((cmd_idx == MMC_CMD_ALL_SEND_CID) | (cmd_idx == MMC_CMD_SEND_CSD) | (cmd_idx == MMC_CMD_SEND_CID)){
		cmd_info->byte_count = 0x11;
		blk_cnt = dma_leng / 0x11;
		data_len = RESP_LEN17;
	}
	else{
		cmd_info->byte_count = BYTE_CNT; //rtk HW limite, one trigger 512 byte pass.
		blk_cnt = dma_leng / BYTE_CNT;
		data_len = 0;
	}

	if((blk_cnt == 0) && dma_leng){
		blk_cnt = (dma_leng+cmd_info->data->blocksize-1)/
					(cmd_info->data->blocksize); // alignment
	}

	for(i = 0 ; i < cmd_info->data->blocks ; i+=cur_blk_xfer_count ) {

		if( blk_cnt > CR_MAX_BLK_XFER_CNT ) {
			cur_blk_xfer_count = CR_MAX_BLK_XFER_CNT;
		}
		else {
			cur_blk_xfer_count = blk_cnt;
		}
		cur_dma_leng = cur_blk_xfer_count * cmd_info->data->blocksize;

        //DDDDYELLOW("     i=%d xfer blks# %d, cur_dma_length 0x%08x, curr dma addr 0x%08x\n", i, cur_blk_xfer_count, cur_dma_leng, dma_addr);

        cmd_info->block_count = cur_blk_xfer_count;
        cmd_info->dma_buffer = dma_addr;
        cmdcode = rtk_sdmmc_chk_cmdcode(cmd_info);    //jim add
        ret = rtk_sdmmc_stream_cmd(cmdcode, cmd_info, data_len, cur_dma_leng);

        if(ret == 0){
            cmd_info->cmd->arg += cur_blk_xfer_count;
            cmd_info->data->bytes_xfered += cur_dma_leng;
            dma_addr += cur_dma_leng;
            blk_cnt -= cur_blk_xfer_count;
        }

		if(cmd_idx==MMC_CMD_WRITE_MULTIPLE_BLOCK)
			cmd_info->data->src = cmd_info->data->src + cur_dma_leng;
		else if(cmd_idx==MMC_CMD_READ_MULTIPLE_BLOCK)
			cmd_info->data->dest = cmd_info->data->dest + cur_dma_leng;

		if(ret){
	        cmd_info->cmd->arg = old_arg;
	        break;
		}

    }

    g_cmd[0] = 0x00;

    return ret;
}
#endif

static u8 rtk_sdmmc_get_rsp_type(struct mmc_cmd* cmd)
{
    u32 rsp_type = 0;
    u32 rsp_type_chk = mmc_resp_type(cmd);

    if(rsp_type_chk == MMC_RSP_R1)
       rsp_type = SD_R1;
    else if(rsp_type_chk == MMC_RSP_R1B)
       rsp_type = SD_R1b;
    else if(rsp_type_chk == MMC_RSP_R2)
       rsp_type = SD_R2;
    else if(rsp_type_chk == MMC_RSP_R3)
       rsp_type = SD_R3;
    else if(rsp_type_chk == MMC_RSP_R6)
       rsp_type = SD_R6;
    else if(rsp_type_chk == MMC_RSP_R7)
       rsp_type = SD_R7;
    else
       rsp_type = SD_R0;

    return rsp_type;
}

static u8 rtk_sdmmc_get_rsp_len(u8 rsp_para)
{
    switch(rsp_para & 0x03){
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 16;
    default:
        return 0;
    }
}

static int rtk_sdmmc_set_rspparam(struct sdmmc_cmd_pkt *cmd_info)
{
    switch(cmd_info->cmd->opcode){
        case MMC_CMD_GO_IDLE_STATE: //cmd 0
            cmd_info->rsp_para1 = 0xD0; //SD1_R0;
            cmd_info->rsp_para2 = 0x74; //0x50 | SD_R0;
            cmd_info->rsp_para3 = 0x00;
            break;
        case MMC_CMD_SEND_OP_COND:
	    /*if(mmc_detected == 1){
                cmd_info->rsp_para1 = SD1_R0;
                cmd_info->rsp_para2 = 0x45;
                cmd_info->rsp_para3 = 0x01;
                cmd_info->cmd->arg = MMC_VDD_30_31 | MMC_VDD_31_32 | MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_SECTOR_ADDR;
            }*/

            break;
        case MMC_CMD_ALL_SEND_CID: //cmd 2
            cmd_info->rsp_para1 = -1; //SD1_R0;
            cmd_info->rsp_para2 = 0x42; //SD_R2;
            cmd_info->rsp_para3 = 0x05; //SD2_R0;
            break;
        case SD_CMD_SEND_RELATIVE_ADDR: //cmd3
            cmd_info->rsp_para1 = -1; //SD1_R0;
            cmd_info->rsp_para2 = 0x41; //SD_R1 | CRC16_CAL_DIS;
            cmd_info->rsp_para3 = 0x05;
            break;
        case MMC_CMD_SET_DSR: //cmd4
            cmd_info->rsp_para1 = -1; //don't update
            cmd_info->rsp_para3 = -1; //don't update
            break;
        case SD_CMD_SWITCH_FUNC: //cmd6
            if((cmd_info->cmd->flags & (0x3 << 5)) == MMC_CMD_ADTC){ //SD_SWITCH
                cmd_info->rsp_para1 = -1;
                cmd_info->rsp_para2 = 0x01; //SD_R1b | CRC16_CAL_DIS;
                cmd_info->rsp_para3 = 0x05;
            }else{
                cmd_info->rsp_para1 = -1;
		if(mmc_detected == 1){
                    cmd_info->rsp_para2 = 0x09; //SD_R1b | CRC16_CAL_DIS;
                    cmd_info->rsp_para3 = 0x05;
                }else{
                    cmd_info->rsp_para2 = 0x61; //SD_R1b | CRC16_CAL_DIS;
                    cmd_info->rsp_para3 = 0x0D;
                }

            }
            break;
        case MMC_CMD_SELECT_CARD: //cmd7
            /*cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x41; //SD_R1b|CRC16_CAL_DIS;
            cmd_info->rsp_para3 = 0x05;*/
	    if(cmd_info->cmd->flags == (MMC_RSP_R1 | MMC_CMD_AC) ) {  //select /* porting issue: add parentheses around comparison */
                cmd_info->rsp_para1 = -1;
                cmd_info->rsp_para2 = 0x41; //SD_R1b|CRC16_CAL_DIS;
                cmd_info->rsp_para3 = 0x05;
            }
            else {      //deselect
                cmd_info->rsp_para1 = -1;
                cmd_info->rsp_para2 = 0x40; //SD_R0|CRC16_CAL_DIS;
                cmd_info->rsp_para3 = 0x05;
            }

            break;
        case SD_CMD_SEND_IF_COND: //cmd8
            cmd_info->rsp_para1 = 0xD0;
            cmd_info->rsp_para2 = 0x41; //SD_R1;
            cmd_info->rsp_para3 = 0x0;
	    /*if (cmd_info->rtk_host->rtflags & RTKCR_FCARD_SELECTED && mmc_detected == 1){
                cmd_info->rsp_para1 = 0x50;
                cmd_info->rsp_para2 = SD_R1;
                cmd_info->rsp_para3 = 0x05;
            }*/

            break;
        case MMC_CMD_SEND_CSD: //cmd9
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x42; //SD_R2;
            cmd_info->rsp_para3 = 0x05;
            break;
        case MMC_CMD_SEND_CID://cmd10
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x42; //SD_R2;
            cmd_info->rsp_para3 = 0x5;
            break;
#ifdef CONFIG_SD30
	case SD_SWITCH_VOLTAGE: //cmd11
            cmd_info->rsp_para1 = -1; //0;
            cmd_info->rsp_para2 = 0x41; //don't update
            cmd_info->rsp_para3 = 0x00; //don't update
            break;
#endif
        case MMC_CMD_STOP_TRANSMISSION: //cmd12
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x7C; //SD_R1 | CRC16_CAL_DIS;
            cmd_info->rsp_para3 = 0x00;
            break;
        case MMC_CMD_SEND_STATUS: //cmd13
            if((cmd_info->cmd->flags & (0x3<<5)) == MMC_CMD_ADTC){ //SD_APP_SD_STATUS
                cmd_info->rsp_para1 = -1;
                cmd_info->rsp_para2 = 0x01; //SD_R1 | CRC16_CAL_DIS;
                cmd_info->rsp_para3 = 0x05;
            }else{
                cmd_info->rsp_para1 = -1;
                cmd_info->rsp_para2 = 0x41; //SD_R1 | CRC16_CAL_DIS;
                cmd_info->rsp_para3 = -1;
            }
            break;
        case MMC_CMD_SET_BLOCKLEN: //cmd16
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x41;
            cmd_info->rsp_para3 = 0x05;
            break;
        case MMC_CMD_READ_SINGLE_BLOCK: //cmd17
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x1;
            cmd_info->rsp_para3 = -1;
            break;
        case MMC_CMD_READ_MULTIPLE_BLOCK: //cmd18
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
	    if(mmc_detected == 1){
                cmd_info->rsp_para3 = 0x04; //0x04;
            }else{
                cmd_info->rsp_para3 = 0x00;//0x02;  ----jim
            }

            break;
#ifdef CONFIG_SD30
	case MMC_SEND_TUNING_BLOCK: //cmd19
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
            cmd_info->rsp_para3 = -1; //0x04;
            break;
#endif
        case MMC_CMD_WRITE_SINGLE_BLOCK: //cmd24
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
            cmd_info->rsp_para3 = -1;
            break;
	case MMC_CMD_WRITE_MULTIPLE_BLOCK: //cmd25
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
            cmd_info->rsp_para3 = 0x00;//0x02;--------jim
            break;
        case SD_CMD_ERASE_WR_BLK_START: //cmd32
            cmd_info->rsp_para1 = -1; //don't update
            cmd_info->rsp_para3 = -1; //don't update
            break;
        case SD_CMD_ERASE_WR_BLK_END: //cmd33
            cmd_info->rsp_para1 = -1; //don't update
            cmd_info->rsp_para3 = -1; //don't update
            break;
        case MMC_CMD_ERASE: //cmd38
            cmd_info->rsp_para1 = -1; //don't update
            cmd_info->rsp_para3 = -1; //don't update
            break;
        case SD_CMD_APP_SEND_OP_COND: //cmd41
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x45;
            cmd_info->rsp_para3 = 0x00;
            break;
        case SD_CMD_APP_SEND_SCR: //cmd51
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x41;
            cmd_info->rsp_para3 = 0x05;
            break;
        case MMC_CMD_APP_CMD: //cmd55
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x41;
            cmd_info->rsp_para3 = 0x05;
            break;
        case MMC_CMD_SPI_READ_OCR: //cmd58
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
	    if(mmc_detected == 1)
                cmd_info->rsp_para3 = 0x04;
            else
                cmd_info->rsp_para3 = 0x02;
            break;
        case MMC_CMD_SPI_CRC_ON_OFF: //cmd59
            cmd_info->rsp_para1 = -1;
            cmd_info->rsp_para2 = 0x01;
            cmd_info->rsp_para3 = 0x02;
            break;
        default:
            cmd_info->rsp_para1 = -1; //don't update
            cmd_info->rsp_para3 = -1; //don't update
            break;
    }

    return 0;
}

static u32 rtk_sdmmc_swap_endian(u32 input)
{
    u32 output = 0;
    output = (input & 0xFF000000) >> 24 |
             (input & 0x00FF0000) >> 8 |
             (input & 0x0000FF00) << 8 |
             (input & 0x000000FF) << 24;
    return output;
}

static void rtk_sdmmc_read_rsp(struct rtk_sdmmc_host *rtk_host, u32 *rsp, int reg_count)
{
    u32 sdmmc_base = rtk_host->sdmmc_base;

    if(reg_count == 6){
        rsp[0] = readb(sdmmc_base + SD_CMD1) << 24 |
                 readb(sdmmc_base + SD_CMD2) << 16 |
                 readb(sdmmc_base + SD_CMD3) << 8 |
                 readb(sdmmc_base + SD_CMD4);
    }
    else if(reg_count == 16){
        rsp[0] = rtk_sdmmc_swap_endian(rsp[0]);
        rsp[1] = rtk_sdmmc_swap_endian(rsp[1]);
        rsp[2] = rtk_sdmmc_swap_endian(rsp[2]);
        rsp[3] = rtk_sdmmc_swap_endian(rsp[3]);
    }
}

static int rtk_sdmmc_allocate_dma_buf(void)
{
    if(!dma_virt_addr){
#if 1
        dma_virt_addr = dma_alloc_coherent(SD_ALLOC_LENGTH, (unsigned long *)(&dma_phy_addr));
#else /* porting issue */
		dma_virt_addr = dma_alloc_coherent(SD_ALLOC_LENGTH, (unsigned long *)(dma_phy_addr));
#endif
        //dma_phy_addr = (u32 *)rtk_host->paddr;
        memset( dma_virt_addr, 0, SD_ALLOC_LENGTH);
    }

    if(!dma_virt_addr){
        printf("%s: allocate rtk sd dma buf FAIL !\n", __func__);
        return 0;
    }
    
    memset( dma_virt_addr, 0, SD_ALLOC_LENGTH);

    return 1;
}

/*static int rtk_sdmmc_free_dma_buf(struct rtk_sdmmc_host *rtk_host)
{
    if (dma_virt_addr)
        dma_free_coherent(NULL, SD_ALLOC_LENGTH, dma_virt_addr ,rtk_host->paddr);
    else
        return 0;

    return 1;
}*/

static void rtk_sdmmc_swap_data(u8 *buffer, u32 sdmmc_base)
{
    buffer[3] = buffer[2];
    buffer[2] = buffer[1];
    buffer[1] = buffer[0];
    buffer[0] = buffer[3+4];
    buffer[3+4] = buffer[3+3];
    buffer[3+3] = buffer[3+2];
    buffer[3+2] = buffer[3+1];
    buffer[3+1] = buffer[7+4];
    buffer[7+4] = buffer[7+3];
    buffer[7+3] = buffer[7+2];
    buffer[7+2] = buffer[7+1];
    buffer[7+1] = buffer[11+4];
    buffer[11+4] = buffer[11+3];
    buffer[11+3] = buffer[11+2];
    buffer[11+2] = buffer[11+1];
    buffer[11+1] = readb(sdmmc_base + SD_CMD5);
}

static int rtk_sdmmc_send_cmd_get_rsp(struct sdmmc_cmd_pkt *cmd_info)
{
    u8 cmd_idx = cmd_info->cmd->opcode;
    u32 sd_arg = 0;
    s8 rsp_para1 = 0;
    s8 rsp_para2 = 0;
    s8 rsp_para3 = 0;
    u8 rsp_len = cmd_info->rsp_len;
    u32 *rsp = (u32 *)&cmd_info->cmd->resp;
    u32 dma_val = 0;
    u32 byte_count = 0x200;
    u32 block_count = 1;
    u64 sa = 0;
    u8 RESP17_buffer[16];
    int ret = 0;
    //int i=0;
    struct rtk_sdmmc_host *rtk_host = cmd_info->rtk_host;
    u32 sdmmc_base = rtk_host->sdmmc_base;

    rtk_sdmmc_set_rspparam(cmd_info);

    sd_arg = cmd_info->cmd->arg;
    rsp_para1 = cmd_info->rsp_para1;
    rsp_para2 = cmd_info->rsp_para2;
    rsp_para3 = cmd_info->rsp_para3;

    if (rsp_para1 != -1)
        writeb(rsp_para1, sdmmc_base + SD_CONFIGURE1);

    writeb(rsp_para2, sdmmc_base + SD_CONFIGURE2);

    if (rsp_para3 != -1)
        writeb(rsp_para3, sdmmc_base + SD_CONFIGURE3);

    g_cmd[0] = (0x40 | cmd_idx);
    g_cmd[1] = (sd_arg >> 24) & 0xff;
    g_cmd[2] = (sd_arg >> 16) & 0xff;
    g_cmd[3] = (sd_arg >> 8) & 0xff;
    g_cmd[4] = sd_arg & 0x000000FF;
    g_cmd[5] = 0x00000000;

    writeb(g_cmd[0], sdmmc_base + SD_CMD0);
    writeb(g_cmd[1], sdmmc_base + SD_CMD1);
    writeb(g_cmd[2], sdmmc_base + SD_CMD2);
    writeb(g_cmd[3], sdmmc_base + SD_CMD3);
    writeb(g_cmd[4], sdmmc_base + SD_CMD4);
    writeb(g_cmd[5], sdmmc_base + SD_CMD5);

    rtk_host->cmd_opcode = cmd_idx;
    
    if(RESP_TYPE_17B & rsp_para2){
        /*remap the resp dst buffer to un-cache*/
        sa = (u64)((void *)dma_phy_addr);
        sa = sa / 8;
        dma_val = RSP17_SEL | DDR_WR | DMA_XFER;
        writeb(byte_count, sdmmc_base + SD_BYTE_CNT_L); //0x24
        writeb(byte_count >> 8, sdmmc_base + SD_BYTE_CNT_H); //0x28
        writeb(block_count, sdmmc_base + SD_BLOCK_CNT_L); //0x2C
        writeb(block_count >> 8, sdmmc_base + SD_BLOCK_CNT_H); //0x30

        writel(sa, sdmmc_base + CR_SD_DMA_CTL1); //espeical for R2
        writel(0x00000001, sdmmc_base + CR_SD_DMA_CTL2); //espeical for R2
        writel(dma_val, sdmmc_base + CR_SD_DMA_CTL3); //espeical for R2
		flush_cache((uintptr_t)dma_virt_addr, SD_ALLOC_LENGTH);
    }
    else if(RESP_TYPE_6B & rsp_para2){
        //do nothing
    }

    ret = rtk_sdmmc_cpu_wait(rtk_host, SD_SENDCMDGETRSP);

	if(ret == 0){
		rtk_sdmmc_read_rsp(rtk_host, (void *)dma_virt_addr, rsp_len);

		if(rsp_len == 16){
			memcpy(RESP17_buffer, (void *)dma_virt_addr, 16);
			rtk_sdmmc_swap_data(RESP17_buffer, sdmmc_base);
			memcpy(rsp, (void *)RESP17_buffer, 16);
		}
		else{
			memcpy(rsp, (void *)dma_virt_addr, 16);
		}
	}
	else {
		rtk_sdmmc_read_rsp(rtk_host, rsp, rsp_len);
	}

	sync();

	/*if (cmd_idx == SD_CMD_SEND_RELATIVE_ADDR){
		printf("%s: SD/MMC card init done.\n", __func__);
	}*/
	//memset(dma_virt_addr, 0x00, SD_ALLOC_LENGTH);

    return ret;
}

static int rtk_sdmmc_request(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data)
{
	struct rtk_sdmmc_host *rtk_host = (struct rtk_sdmmc_host *)mmc->priv;
	struct sdmmc_cmd_pkt cmd_info;
#ifdef CONFIG_SD30
	u32 sdmmc_base = rtk_host->sdmmc_base;
#endif /* CONFIG_SD30 */
	int ret = 0;

	memset(&cmd_info, 0, sizeof(struct sdmmc_cmd_pkt));

	cmd_info.cmd = cmd;
	cmd_info.rtk_host = rtk_host;
	cmd_info.rsp_para2 = rtk_sdmmc_get_rsp_type(cmd_info.cmd);
	cmd_info.rsp_len = rtk_sdmmc_get_rsp_len(cmd_info.rsp_para2);

	if(cmd_info.cmd->opcode == MMC_CMD_SEND_OP_COND) {
		mmc_detected = 1;
	}
#ifdef CONFIG_SD30
	else if(cmd_info.cmd->opcode == SD_SWITCH_VOLTAGE) {
        	writeb(0x40, sdmmc_base + SD_BUS_STATUS);
	}
#endif

	if(data){
		cmd_info.data = data;
		ret = rtk_sdmmc_stream(&cmd_info);
	}
	else{
		cmd_info.data = NULL;
		rtk_sdmmc_allocate_dma_buf();
		ret = rtk_sdmmc_send_cmd_get_rsp(&cmd_info);
#ifdef CONFIG_SD30
		if(cmd_info.cmd->opcode == SD_CMD_SEND_RELATIVE_ADDR)	
			 sdmmc_rca = ((cmd->resp[0]) >> RCA_SHIFTER);
#endif /* CONFIG_SD30 */
	}

	return ret;
}

static void rtk_sdmmc_set_access_mode(struct rtk_sdmmc_host *rtk_host,u8 level)
{
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 tmp_bits = 0;

    tmp_bits = readb(sdmmc_base + SD_CONFIGURE1) & ~MODE_SEL_MASK;

    if(level == ACCESS_MODE_SD20)
        tmp_bits |= MODE_SEL_SD20;
    else if(level == ACCESS_MODE_DDR)
        tmp_bits |= MODE_SEL_DDR;
    else if(level == ACCESS_MODE_SD30)
        tmp_bits |= (MODE_SEL_SD30 | SD30_ASYNC_FIFO_RST);
    else
        tmp_bits |= MODE_SEL_SD20;

    writeb(tmp_bits, sdmmc_base + SD_CONFIGURE1);
}

static void rtk_sdmmc_set_bits(struct rtk_sdmmc_host *rtk_host, unsigned int set_bit)
{
    u32 sdmmc_base = rtk_host->sdmmc_base;
    u32 tmp_bits = 0;

    tmp_bits = readb(sdmmc_base + SD_CONFIGURE1);
    if((tmp_bits & MASK_BUS_WIDTH) != set_bit){
        tmp_bits &= ~MASK_BUS_WIDTH;
        writeb(tmp_bits | set_bit, sdmmc_base + SD_CONFIGURE1);
    }

}

static void rtk_sdmmc_set_ios(struct mmc *mmc, unsigned int caps)
{
	struct rtk_sdmmc_host *rtk_host = (struct rtk_sdmmc_host *)mmc->priv;

	if ( caps & MMC_IOS_BUSWIDTH/*bit2*/ ) {
		if (mmc->bus_width == 4){
			rtk_sdmmc_set_bits(rtk_host, BUS_WIDTH_4);
		}
		else{
			rtk_sdmmc_set_bits(rtk_host, BUS_WIDTH_1);
		}
	}

	if( caps & MMC_IOS_CLK/*bit1*/ ) {
#ifdef CONFIG_SD30
		if(mmc->clock >= 208000000) {
			rtk_sdmmc_set_access_mode(rtk_host, ACCESS_MODE_SD30);
			rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_208000KHZ);
			//	printf("%s: UHS mode Speed SDMMC_CLOCK_208000KHZ\n", __func__);
		}
		else if(mmc->clock>=100000000) {
			rtk_sdmmc_set_access_mode(rtk_host, ACCESS_MODE_SD30);
			rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_100000KHZ);
			//	printf("%s: UHS mode Speed SDMMC_CLOCK_100000KHZ\n", __func__);
		}
		else if(mmc->clock >= 50000000) {
#else
		if(mmc->clock >= 50000000) {
#endif
			rtk_sdmmc_set_access_mode(rtk_host, ACCESS_MODE_SD20);
			rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_50000KHZ);
			// printf("%s: High Speed SDMMC_CLOCK_50000KHZ\n", __func__);
		}
		else if(mmc->clock >= 6200000) {
			rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_6200KHZ);
			//printf("%s: Mid speed RTKCR_FCARD_SELECTED = 1 SDMMC_CLOCK_6200KHZ\n", __func__);
		}
		else {
			rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_400KHZ);
			//printf("%s: set clock SDMMC_CLOCK_400KHZ\n", __func__);
		}
	}
}

static void rtk_sdmmc_init(void)
{
	struct rtk_sdmmc_host *rtk_host = sd_rtk_sdmmc_host;

	if( rtk_host == NULL ) {
		printf("SD host not initialized\n");
		return;	
	}

	u32 emmc_base = rtk_host->emmc_base;
    //printf("%s , rtk_host->sdmmc_base = %x\n", __func__, rtk_host->sdmmc_base);
    //printf("%s , rtk_host->crt_base = %x\n", __func__, rtk_host->crt_base);
    //printf("%s , rtk_host->emmc_base = %x\n", __func__, rtk_host->emmc_base);
    //printf("%s , rtk_host->sysbrdg = %x\n", __func__, rtk_host->sysbrdg);

    writel(0x03200332,0x98012618);
    writel(0x55550555,0x98012604);
    writel(0x33333323,0x98012610);
    /*SD PLL Initialization, jamestai20150721*/
    writel(readl(rtk_host->crt_base + CR_PLL_SD4) | 0x00000004, rtk_host->crt_base + CR_PLL_SD4);
    writel(readl(rtk_host->crt_base + CR_PLL_SD4) | 0x00000007, rtk_host->crt_base + CR_PLL_SD4);

    writel(0x00002003, rtk_host->crt_base + CR_PLL_SD1); //PLL_SD1

    if(readl(rtk_host->sysbrdg+0x204)!=0x0)
        writel(0x40000000,rtk_host->sdmmc_base+0x2c);
    udelay(100);
    writel(0x00000006, rtk_host->crt_base + 0x01EC);
    writel(readl(rtk_host->sdmmc_base + CR_SD_CKGEN_CTL) | 0x00070000, rtk_host->sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to 4MHz by Hsin-yin
    mdelay(2);
    writel(0x00000007, rtk_host->crt_base + 0x01EC);
    if(readl(rtk_host->sysbrdg+0x204)!=0x0)
        writel(0x00000000,rtk_host->sdmmc_base+0x2c);

	if(readl(rtk_host->sysbrdg+0x204)!=0x0)	//A01 version, we add dummy register
		writel(0x40000000,rtk_host->sdmmc_base+0x2c);
    udelay(100);
    writel(0x00000006, rtk_host->crt_base + 0x01EC);
    writel(0x04517893, rtk_host->crt_base + CR_PLL_SD2); //Reduce the impact of spectrum by Hsin-yin, jamestai20150302
    writel(0x00564388, rtk_host->crt_base + CR_PLL_SD3); //Set PLL clock rate, default clock 100MHz
    mdelay(2);
    writel(0x00000007, rtk_host->crt_base + 0x01EC);
    if(readl(rtk_host->sysbrdg+0x204)!=0x0)
        writel(0x00000000,rtk_host->sdmmc_base+0x2c);

    writel(readl(rtk_host->crt_base + 0x04) | (0x1 << 10), rtk_host->crt_base + 0x04);
    writel(readl(rtk_host->crt_base + 0x0C) | (0x1 << 25) | (0x1 << 31), rtk_host->crt_base + 0x0C);
    //writel(readl(rtk_host->sdmmc_base + 0x20) | 0x00000003, rtk_host->sdmmc_base + 0x20);
    writel(readl(rtk_host->sdmmc_base + 0x20) |0x02, rtk_host->sdmmc_base + 0x20);    //Disable L4 gate

    writel(readl(rtk_host->sdmmc_base + 0x20) & (~0x01), rtk_host->sdmmc_base + 0x20);
    writel(readl(rtk_host->sdmmc_base + 0x20) | 0x00000001, rtk_host->sdmmc_base + 0x20);   //reset the DMA

    if(readl(rtk_host->sysbrdg+0x204)!=0x0)
        writel(0x40000000,rtk_host->sdmmc_base+0x2c);
    udelay(100);
	writel(0x00000006, rtk_host->crt_base + 0x01EC);
	writel(readl(rtk_host->sdmmc_base + CR_SD_CKGEN_CTL) & 0xFFF8FFFF, rtk_host->sdmmc_base + CR_SD_CKGEN_CTL); //Switch SD source clock to normal clock source by Hsin-yin
	udelay(100);
	writel(0x00000007, rtk_host->crt_base + 0x01EC);
    if(readl(rtk_host->sysbrdg+0x204)!=0x0)
        writel(0x00000000,rtk_host->sdmmc_base+0x2c);

	writeb(readb(rtk_host->sdmmc_base + SD_CONFIGURE1) & 0x000000EF, rtk_host->sdmmc_base + SD_CONFIGURE1); //Reset FIFO pointer by Hsin-yin
	writel(0x00000007, rtk_host->crt_base + CR_PLL_SD4); //PLL_SD4
	udelay(100);
	writeb(0xD0, rtk_host->sdmmc_base + SD_CONFIGURE1);
	rtk_sdmmc_speed(rtk_host, SDMMC_CLOCK_400KHZ);

	writel(0x00003333, emmc_base + 0x634);         //JIM modified this part from 3333 to 5555 to enlarge the signal to work around a issue that can not recognize some SD 3.0 card
    writel(0x33333333, emmc_base + 0x638);

	writel(0x00000000, rtk_host->sdmmc_base + CR_SD_PAD_CTL); //change to 3.3v

	writel(0x00000016, rtk_host->sdmmc_base + CR_SD_ISR); //enable interrupt
	writel(0x00000017, rtk_host->sdmmc_base + CR_SD_ISREN);

	writeb(0x02, rtk_host->sdmmc_base + CARD_SELECT); //for emmc, select SD ip
}

static int rtk_sdmmc_getcd(struct mmc *mmc){

	struct rtk_sdmmc_host *rtk_host = (struct rtk_sdmmc_host *)mmc->priv;
	u32 sdmmc_base = rtk_host->sdmmc_base;
	u8 reginfo = 0;

	reginfo = readb(sdmmc_base + CARD_EXIST);

	if(reginfo & SD_EXISTENCE){
		//printf("SD is exist, regCARD_EXIST = 0x%02x (CD flag is 0x%02x)\n", reginfo, SD_EXISTENCE);
		return 1;
	}
	printf("SD is not exist, regCARD_EXIST = 0x%02x (CD flag is 0x%02x)\n", reginfo, SD_EXISTENCE);
	return 0;
}

int board_sd_init(bd_t * bis)
{
    struct mmc *mmc = NULL;
    struct rtk_sdmmc_host *rtk_host = NULL;

    mmc = malloc(sizeof(struct mmc));

    if (!mmc) {
		printf("%s %d: malloc failed\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
    }

    rtk_host = malloc(sizeof(struct rtk_sdmmc_host));
	if (!rtk_host) {
		printf("%s %d: malloc failed\n", __FUNCTION__, __LINE__);
		return -ENOMEM;
	}
    
    sd_mmc = mmc;
    sd_rtk_sdmmc_host = rtk_host;

    rtk_host->sdmmc_base = 0x98010400;
    rtk_host->crt_base = 0x98000000;
    rtk_host->emmc_base = 0x98012000;
    rtk_host->sysbrdg = 0x9801A000;

    //printf("%s , rtk_host->sdmmc_base = %x\n", __func__, rtk_host->sdmmc_base);
    //printf("%s , rtk_host->crt_base = %x\n", __func__, rtk_host->crt_base);
    //printf("%s , rtk_host->emmc_base = %x\n", __func__, rtk_host->emmc_base);
    //printf("%s , rtk_host->sysbrdg = %x\n", __func__, rtk_host->sysbrdg);

	sprintf(mmc->name, "RTK SDMMC");
	mmc->request = rtk_sdmmc_request;
	mmc->set_ios = rtk_sdmmc_set_ios;
	mmc->init = rtk_sdmmc_init;
	mmc->getcd = rtk_sdmmc_getcd;
#ifdef CONFIG_SD30
	mmc->switch_voltage = rtk_sdmmc_switch_voltage;
	mmc->execute_tuning = rtk_sdmmc_execute_tuning;
#endif
	mmc->priv = rtk_host;

	mmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195;

	mmc->host_caps = MMC_MODE_4BIT |
						MMC_MODE_HS_52MHz |
						MMC_MODE_HS |
#ifdef CONFIG_SD30
						MMC_CAP_UHS_SDR50 |
						MMC_CAP_UHS_SDR104 |
#endif
						MMC_MODE_HC;

	mmc->f_min = 400000;
	mmc->f_max = 208000000;

	sd_register(mmc);

	return 0;
}
