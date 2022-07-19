/**************************************************************
// Spec Version                  : 1.9
// Parser Version                : DVR_Parser_6.3
// CModelGen Version             : 5.0 2009.04.09
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/11/22 16:10:51
***************************************************************/


#ifndef _HDMI_REG_H_INCLUDED_
#define _HDMI_REG_H_INCLUDED_
#ifdef  _HDMI_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     rxsenseint:1;
unsigned int     enriupdint:1;
unsigned int     enpjupdint:1;
unsigned int     write_data:1;
}INTEN;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     vendint:1;
unsigned int     vsyncint:1;
unsigned int     write_data:1;
}INTENV;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     asfifo_empty:1;
unsigned int     asfifo_full:1;
unsigned int     owctshw:1;
unsigned int     asfifoow:1;
unsigned int     write_data:1;
}AUDIO_ST;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     rxupdated:1;
unsigned int     riupdated:1;
unsigned int     pjupdated:1;
}INTST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     vendupdated:1;
unsigned int     vsyncupdated:1;
}INTSTV;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     wdout:1;
unsigned int     Rxstatus:1;
}HDMI_PHY_STATUS;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en2:1;
unsigned int     rirate:8;
unsigned int     write_en1:1;
unsigned int     pjrate:8;
}UPDATE_ST;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     sram_shut_down_en:1;
unsigned int     sram_sleep_en:1;
unsigned int     video_sd:1;
unsigned int     Interlaced_vfmt:1;
unsigned int     3D_video_format:4;
unsigned int     En_3D:1;
unsigned int     timing_gen_en:1;
unsigned int     chl_sel:2;
}CHNL_SEL;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c1:17;
}CS_TRANS0;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c2:17;
}CS_TRANS1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c3:17;
}CS_TRANS2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c4:17;
}CS_TRANS3;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c5:17;
}CS_TRANS4;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c6:17;
}CS_TRANS5;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c7:17;
}CS_TRANS6;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c8:17;
}CS_TRANS7;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     c9:17;
}CS_TRANS8;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     k1:16;
}CS_TRANS9;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     k2:16;
}CS_TRANS10;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     k3:16;
}CS_TRANS11;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en2:1;
unsigned int     ygmax:12;
unsigned int     reserved_1:3;
unsigned int     write_en1:1;
unsigned int     ygmin:12;
}CS_TRANS12;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en2:1;
unsigned int     cbbmax:12;
unsigned int     reserved_1:3;
unsigned int     write_en1:1;
unsigned int     cbbmin:12;
}CS_TRANS13;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en2:1;
unsigned int     crrmax:12;
unsigned int     reserved_1:3;
unsigned int     write_en1:1;
unsigned int     crrmin:12;
}CS_TRANS14;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en4:1;
unsigned int     nor_v:2;
unsigned int     write_en3:1;
unsigned int     nor_h:2;
unsigned int     write_en2:1;
unsigned int     disp_v:2;
unsigned int     write_en1:1;
unsigned int     disp_h:2;
}SYNC_DLY;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_en3:1;
unsigned int     tmds_encen:1;
unsigned int     write_en2:1;
unsigned int     enablehdcp:1;
unsigned int     write_en1:1;
unsigned int     enablehdmi:1;
}CR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en9:1;
unsigned int     dp_vfch_num:2;
unsigned int     reserved_1:2;
unsigned int     write_en8:1;
unsigned int     fp_swen:1;
unsigned int     write_en7:1;
unsigned int     fp:3;
unsigned int     write_en6:1;
unsigned int     pp_swen:1;
unsigned int     reserved_2:2;
unsigned int     write_en4:1;
unsigned int     dp_swen:1;
unsigned int     write_en3:1;
unsigned int     default_phase:1;
unsigned int     reserved_3:3;
unsigned int     write_en2:1;
unsigned int     color_depth:4;
unsigned int     reserved_4:2;
unsigned int     write_en1:1;
unsigned int     dpc_enable:1;
}DPC;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_en2:1;
unsigned int     dp_vfch:1;
unsigned int     reserved_1:3;
unsigned int     write_en1:1;
unsigned int     pp:4;
}DPC1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     tmds_ch2_out:10;
unsigned int     tmds_ch1_out:10;
unsigned int     tmds_ch0_out:10;
}TMDS_EODR0;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     default_phase_st:1;
unsigned int     reserved_1:2;
unsigned int     tmds_clk_out:10;
}TMDS_EODR1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     REG_LDO_PLL_VSEL:3;
unsigned int     REG_LDO_CCO_VSEL:2;
unsigned int     REG_TX_CK5XP_DUTY:2;
unsigned int     REG_TX_CK5XN_DUTY:2;
unsigned int     REG_TX_AMP:4;
unsigned int     REG_TX_IBIAS:2;
unsigned int     REG_TX_EMPH:3;
unsigned int     REG_TX_EN_EMPH:1;
unsigned int     REG_TX_FORCE_VC:1;
unsigned int     REG_TX_SET_VC:2;
unsigned int     REG_TX_PLL_EDGE:1;
unsigned int     REG_TX_PLL_ICP:3;
unsigned int     REG_TX_PLL_RS:3;
}TMDS_SCR1;

typedef struct 
{
unsigned int     REG_TX_V1P05_SEL:2;
unsigned int     REG_TX_PDRV_ISEL:2;
unsigned int     REG_TX_PLL_KVCO:1;
unsigned int     REG_TX_PLL_CS:2;
unsigned int     REG_TX_PLL_CP:2;
unsigned int     REG_TX_PLL_PU:1;
unsigned int     REG_TX_PU:4;
unsigned int     REG_TX_DRIVER:2;
unsigned int     REG_TX_SLEW:2;
unsigned int     REG_TX_TST_EN:1;
unsigned int     REG_TX_VGATE:3;
unsigned int     REG_PLL_TST_EN:1;
unsigned int     REG_TST_SEL:2;
unsigned int     REG_TX_BYPASS_PLL:1;
unsigned int     REG_TX_RT_EN:1;
unsigned int     REG_TX_RT_SEL:2;
unsigned int     REG_PLL_VCO_SCALE:2;
unsigned int     REG_BYPASS_DIN:1;
}TMDS_SCR2;

typedef struct 
{
unsigned int     REG_TX_PLL_WDMODE:2;
unsigned int     REG_RESERVE:16;
unsigned int     REG_CEC_ENB:1;
unsigned int     REG_EN_MHL:1;
unsigned int     REG_FORCE_RXSENSE:1;
unsigned int     REG_RXSENSE:2;
unsigned int     REG_MHL_DIV:1;
unsigned int     REG_MHL_VCM:2;
unsigned int     REG_DIFF_RT_EN:1;
unsigned int     REG_CABLE_DET_EN:1;
unsigned int     REG_LDO_TMDS_VSEL20:3;
unsigned int     REG_LDO_TMDS_CAPSEL:1;
}TMDS_SCR3;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     REG_TV_WDMODE:2;
unsigned int     REG_TV_KVCO:1;
unsigned int     REG_TV_CS:2;
unsigned int     REG_TV_CP:2;
unsigned int     REG_TV_ICP:3;
unsigned int     REG_TV_RS:3;
unsigned int     REG_TV_BYPASS_PLL:1;
unsigned int     REG_TV_FORCE_VC:1;
unsigned int     REG_TV_SET_VC:2;
unsigned int     REG_TV_TST_EN:1;
}TVPLL_CTRL2;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     REGO_TV_WDOUT:1;
unsigned int     REGO_TX_PLL_WDOUT:1;
unsigned int     REGO_TX_PLL_LOCK:1;
unsigned int     REGO_CABLE_DETECT:8;
unsigned int     REGO_TV_PLL_LOCK:1;
}MHL_CBUS;

typedef struct 
{
unsigned int     tmds1ten:1;
unsigned int     td1src:1;
unsigned int     reserved_0:4;
unsigned int     tmds1td:10;
unsigned int     tmds0ten:1;
unsigned int     td0src:1;
unsigned int     reserved_1:4;
unsigned int     tmds0td:10;
}TMDS_STR0;

typedef struct 
{
unsigned int     tmdscten:1;
unsigned int     tdcsrc:1;
unsigned int     reserved_0:4;
unsigned int     tmdsctd:10;
unsigned int     tmds2ten:1;
unsigned int     td2src:1;
unsigned int     reserved_1:4;
unsigned int     tmds2td:10;
}TMDS_STR1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en8:1;
unsigned int     ycbcr422_8bits:1;
unsigned int     write_en7:1;
unsigned int     cts_pkt_hp:1;
unsigned int     write_en6:1;
unsigned int     Audioheader0:8;
unsigned int     write_en5:1;
unsigned int     samplepresent:4;
unsigned int     write_en4:1;
unsigned int     forcesamplepresent:1;
unsigned int     write_en3:1;
unsigned int     b_frame:4;
unsigned int     write_en2:1;
unsigned int     forceb_frame:1;
unsigned int     write_en1:1;
unsigned int     audiolayout:1;
}ASPCR1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     write_en4:1;
unsigned int     hdmi_pk3map:3;
unsigned int     write_en3:1;
unsigned int     hdmi_pk2map:3;
unsigned int     write_en2:1;
unsigned int     hdmi_pk1map:3;
unsigned int     write_en1:1;
unsigned int     hdmi_pk0map:3;
}ACACR;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     write_en6:1;
unsigned int     Audio_info_hp:1;
unsigned int     write_en5:1;
unsigned int     ac_hw_ctrl_en:1;
unsigned int     write_en4:1;
unsigned int     fs_div4:1;
unsigned int     write_en3:1;
unsigned int     disablecrp:1;
unsigned int     write_en2:1;
unsigned int     cts_source:1;
unsigned int     write_en1:1;
unsigned int     n_value:20;
}ACRPCR;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     ctssw:20;
}ACRPCTSR;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     ctshw:20;
}ACRPPR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     enablegcp:1;
unsigned int     gcp_clearavmute:1;
unsigned int     gcp_setavmute:1;
unsigned int     write_data:1;
}GCPCR;

typedef struct 
{
unsigned int     once_pkt:32;
}ORP6PH;

typedef struct 
{
unsigned int     once_pkt:32;
}ORP6W;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     write_en6:1;
unsigned int     prp5period:4;
unsigned int     write_en5:1;
unsigned int     prp4period:4;
unsigned int     write_en4:1;
unsigned int     prp3period:4;
unsigned int     write_en3:1;
unsigned int     prp2period:4;
unsigned int     write_en2:1;
unsigned int     prp1period:4;
unsigned int     write_en1:1;
unsigned int     prp0period:4;
}RPCR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     enprpkt5:1;
unsigned int     enprpkt4:1;
unsigned int     enprpkt3:1;
unsigned int     enprpkt2:1;
unsigned int     enprpkt1:1;
unsigned int     enprpkt0:1;
unsigned int     write_data:1;
}RPEN;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     isramrbd:18;
}RPRBDR;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     write_en4:1;
unsigned int     enrbpktsram:1;
unsigned int     write_en3:1;
unsigned int     wrdes:1;
unsigned int     write_en2:1;
unsigned int     rprwcmd:1;
unsigned int     write_en1:1;
unsigned int     rpadd:8;
}OPCR;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     vbidipcnt:5;
unsigned int     write_en1:1;
unsigned int     hbidipcnt:5;
}DIPCCR;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en12:1;
unsigned int     color_transform_en:1;
unsigned int     write_en11:1;
unsigned int     ycbcr422_algo:1;
unsigned int     write_en10:1;
unsigned int     422_pixel_repeat:1;
unsigned int     write_en9:1;
unsigned int     vsyncpolin:1;
unsigned int     write_en8:1;
unsigned int     hsyncpolin:1;
unsigned int     write_en7:1;
unsigned int     vsyncpolinv:1;
unsigned int     write_en6:1;
unsigned int     hsyncpolinv:1;
unsigned int     write_en5:1;
unsigned int     pixelencycbcr422:1;
unsigned int     write_en4:1;
unsigned int     hdmi_videoxs:5;
unsigned int     write_en3:1;
unsigned int     pixelencfmt:2;
unsigned int     write_en2:1;
unsigned int     pixelrepeat:1;
unsigned int     write_en1:1;
unsigned int     hdmi_modesel:1;
}SCHCR;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en3:1;
unsigned int     enaudio:1;
unsigned int     write_en2:1;
unsigned int     envitd:1;
unsigned int     write_en1:1;
unsigned int     vitd:24;
}ICR;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_en1:1;
unsigned int     vitd:12;
}ICR1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     write_en2:1;
unsigned int     crcmode:1;
unsigned int     write_en1:1;
unsigned int     crcchsel:2;
}CRCCR;

typedef struct 
{
unsigned int     crcvalue:32;
}CRCDOR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     hdcprekeykeepoutwin:8;
}HDCP_KOWR;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     hdcpverkeepoutwinend:12;
unsigned int     write_en1:1;
unsigned int     hdcpvertkeepoutwinstart:12;
}HDCP_KOWRSE;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     hdcpoppwinend:12;
unsigned int     write_en1:1;
unsigned int     hdcpoppwinstart:12;
}HDCP_OWR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     write_en4:1;
unsigned int     en1_1_feature:1;
unsigned int     write_en3:1;
unsigned int     downstrisrepeater:1;
unsigned int     write_en2:1;
unsigned int     aninfluencemode:1;
unsigned int     write_en1:1;
unsigned int     hdcp_encryptenable:1;
}HDCP_CR;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en9:1;
unsigned int     ddpken:1;
unsigned int     write_en8:1;
unsigned int     resetkmacc:1;
unsigned int     write_en7:1;
unsigned int     update_an:1;
unsigned int     write_en6:1;
unsigned int     aninfreq:1;
unsigned int     write_en5:1;
unsigned int     seedload:1;
unsigned int     write_en4:1;
unsigned int     deviceauthenticated:1;
unsigned int     write_en3:1;
unsigned int     forcetounauthenticated:1;
unsigned int     write_en2:1;
unsigned int     authcompute:1;
unsigned int     write_en1:1;
unsigned int     authrequest:1;
}HDCP_AUTH;

typedef struct 
{
unsigned int     hdcpcipherstate:8;
unsigned int     reserved_0:20;
unsigned int     curdpkaccdone:1;
unsigned int     hdcp_encrypt_status:1;
unsigned int     authenticatedok:1;
unsigned int     anready:1;
}HDCP_SR;

typedef struct 
{
unsigned int     anlsw:32;
}HDCP_ANLR;

typedef struct 
{
unsigned int     anmsw:32;
}HDCP_ANMR;

typedef struct 
{
unsigned int     aninfluencelsw:32;
}HDCP_ANILR;

typedef struct 
{
unsigned int     aninfluencemsw:32;
}HDCP_ANIMR;

typedef struct 
{
unsigned int     ddpklsb24:24;
unsigned int     dpkencpnt:8;
}HDCP_DPKLR;

typedef struct 
{
unsigned int     ddpkmsw:32;
}HDCP_DPKMR;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ri:16;
unsigned int     pj:8;
}HDCP_LIR;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     shastart:1;
unsigned int     shafirst:1;
unsigned int     rstshaptr:1;
unsigned int     write_data:1;
}HDCP_SHACR;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     vmatch:1;
unsigned int     shaready:1;
}HDCP_SHARR;

typedef struct 
{
unsigned int     sha_data:32;
}HDCP_SHADR;

typedef struct 
{
unsigned int     milsw:32;
}HDCP_MILSW;

typedef struct 
{
unsigned int     mimsw:32;
}HDCP_MIMSW;

typedef struct 
{
unsigned int     kmlsw:32;
}HDCP_KMLSW;

typedef struct 
{
unsigned int     kmmsw:32;
}HDCP_KMMSW;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     write_en5:1;
unsigned int     pkt_vdo_cnt_add:1;
unsigned int     write_en4:1;
unsigned int     hdcp_2_2_en:1;
unsigned int     write_en3:1;
unsigned int     aes_sw_en:1;
unsigned int     write_en2:1;
unsigned int     aes_sw_start1:1;
unsigned int     write_en1:1;
unsigned int     aes_sw_start2:1;
}HDCP_2_2_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     rgs_sw_done_1:1;
unsigned int     rgs_sw_done_2:1;
}HDCP_2_2_STATUS;

typedef struct 
{
unsigned int     sw_data_1_1:32;
}HDCP_2_2_SW_DATA_1_1;

typedef struct 
{
unsigned int     sw_data_1_2:32;
}HDCP_2_2_SW_DATA_1_2;

typedef struct 
{
unsigned int     sw_data_1_3:32;
}HDCP_2_2_SW_DATA_1_3;

typedef struct 
{
unsigned int     sw_data_1_4:32;
}HDCP_2_2_SW_DATA_1_4;

typedef struct 
{
unsigned int     sw_data_2_1:32;
}HDCP_2_2_SW_DATA_2_1;

typedef struct 
{
unsigned int     sw_data_2_2:32;
}HDCP_2_2_SW_DATA_2_2;

typedef struct 
{
unsigned int     sw_data_2_3:32;
}HDCP_2_2_SW_DATA_2_3;

typedef struct 
{
unsigned int     sw_data_2_4:32;
}HDCP_2_2_SW_DATA_2_4;

typedef struct 
{
unsigned int     sw_key_1_1:32;
}HDCP_2_2_SW_KEY_1_1;

typedef struct 
{
unsigned int     sw_key_1_2:32;
}HDCP_2_2_SW_KEY_1_2;

typedef struct 
{
unsigned int     sw_key_1_3:32;
}HDCP_2_2_SW_KEY_1_3;

typedef struct 
{
unsigned int     sw_key_1_4:32;
}HDCP_2_2_SW_KEY_1_4;

typedef struct 
{
unsigned int     sw_key_2_1:32;
}HDCP_2_2_SW_KEY_2_1;

typedef struct 
{
unsigned int     sw_key_2_2:32;
}HDCP_2_2_SW_KEY_2_2;

typedef struct 
{
unsigned int     sw_key_2_3:32;
}HDCP_2_2_SW_KEY_2_3;

typedef struct 
{
unsigned int     sw_key_2_4:32;
}HDCP_2_2_SW_KEY_2_4;

typedef struct 
{
unsigned int     sw_data_xor_1_1:32;
}HDCP_2_2_SW_DATA_XOR_1_1;

typedef struct 
{
unsigned int     sw_data_xor_1_2:32;
}HDCP_2_2_SW_DATA_XOR_1_2;

typedef struct 
{
unsigned int     sw_data_xor_1_3:32;
}HDCP_2_2_SW_DATA_XOR_1_3;

typedef struct 
{
unsigned int     sw_data_xor_1_4:32;
}HDCP_2_2_SW_DATA_XOR_1_4;

typedef struct 
{
unsigned int     sw_data_xor_2_1:32;
}HDCP_2_2_SW_DATA_XOR_2_1;

typedef struct 
{
unsigned int     sw_data_xor_2_2:32;
}HDCP_2_2_SW_DATA_XOR_2_2;

typedef struct 
{
unsigned int     sw_data_xor_2_3:32;
}HDCP_2_2_SW_DATA_XOR_2_3;

typedef struct 
{
unsigned int     sw_data_xor_2_4:32;
}HDCP_2_2_SW_DATA_XOR_2_4;

typedef struct 
{
unsigned int     data_out_1_1:32;
}HDCP_2_2_SW_DATA_OUT_1_1;

typedef struct 
{
unsigned int     data_out_1_2:32;
}HDCP_2_2_SW_DATA_OUT_1_2;

typedef struct 
{
unsigned int     data_out_1_3:32;
}HDCP_2_2_SW_DATA_OUT_1_3;

typedef struct 
{
unsigned int     data_out_1_4:32;
}HDCP_2_2_SW_DATA_OUT_1_4;

typedef struct 
{
unsigned int     data_out_2_1:32;
}HDCP_2_2_SW_DATA_OUT_2_1;

typedef struct 
{
unsigned int     data_out_2_2:32;
}HDCP_2_2_SW_DATA_OUT_2_2;

typedef struct 
{
unsigned int     data_out_2_3:32;
}HDCP_2_2_SW_DATA_OUT_2_3;

typedef struct 
{
unsigned int     data_out_2_4:32;
}HDCP_2_2_SW_DATA_OUT_2_4;

typedef struct 
{
unsigned int     hw_riv_1_1:32;
}HDCP_2_2_HW_RIV_1;

typedef struct 
{
unsigned int     hw_riv_1_2:32;
}HDCP_2_2_HW_RIV_2;

typedef struct 
{
unsigned int     frame_num_1:32;
}HDCP_2_2_HW_FRAME_NUM_1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     frame_num_2:6;
}HDCP_2_2_HW_FRAME_NUM_2;

typedef struct 
{
unsigned int     frame_num_add_1:32;
}HDCP_2_2_HW_FRAME_NUM_ADD_1;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     frame_num_add_2:6;
}HDCP_2_2_HW_FRAME_NUM_ADD_2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     data_num:26;
}HDCP_2_2_HW_DATA_NUM;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     data_num_add:26;
}HDCP_2_2_HW_DATA_NUM_ADD;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     write_en2:1;
unsigned int     free_run_mod_en:1;
unsigned int     write_en1:1;
unsigned int     keep_out_win:26;
}HDCP_2_2_HW_FREE_RUN;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     chsel0:4;
unsigned int     chsel1:4;
}DBG;

typedef struct 
{
unsigned int     dummy:32;
}DUMMY;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     test_mode:1;
unsigned int     data_realign:1;
}PHY;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hblank:14;
unsigned int     reserved_1:2;
unsigned int     hactive:14;
}H_PARA1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     hsync:14;
unsigned int     reserved_1:2;
unsigned int     hfront:14;
}H_PARA2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     hback:14;
}H_PARA3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vact_video:14;
unsigned int     reserved_1:2;
unsigned int     vactive:14;
}V_PARA1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vact_space1:14;
unsigned int     reserved_1:2;
unsigned int     Vact_space:14;
}V_PARA2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vblank3:14;
unsigned int     reserved_1:2;
unsigned int     Vact_space2:14;
}V_PARA3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsync:14;
unsigned int     reserved_1:2;
unsigned int     vblank:14;
}V_PARA4;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vback:14;
unsigned int     reserved_1:2;
unsigned int     vfront:14;
}V_PARA5;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vsync1:14;
unsigned int     reserved_1:2;
unsigned int     Vblank1:14;
}V_PARA6;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vback1:14;
unsigned int     reserved_1:2;
unsigned int     Vfront1:14;
}V_PARA7;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vsync2:14;
unsigned int     reserved_1:2;
unsigned int     Vblank2:14;
}V_PARA8;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     Vback2:14;
unsigned int     reserved_1:2;
unsigned int     Vfront2:14;
}V_PARA9;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vsynci:14;
unsigned int     reserved_1:2;
unsigned int     vblanki:14;
}V_PARA12;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     vbacki:14;
unsigned int     reserved_1:2;
unsigned int     vfronti:14;
}V_PARA13;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     G:12;
}V_PARA10;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     B:12;
unsigned int     reserved_1:4;
unsigned int     R:12;
}V_PARA11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dft_test_resume:1;
unsigned int     dft_bist_mode:1;
unsigned int     bist_mode:1;
unsigned int     rme:1;
unsigned int     rm:4;
}BIST1_CTRL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dft_test_resume:1;
unsigned int     dft_bist_mode:1;
unsigned int     bist_mode:1;
unsigned int     rme:1;
unsigned int     rm:4;
}BIST2_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     bist1_fail0:1;
unsigned int     bist1_done:1;
}BIST1_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_bist1_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_bist1_fail0:1;
unsigned int     drf_bist1_done:1;
}DRF_BIST1_ST;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     bist2_fail0:1;
unsigned int     bist2_done:1;
}BIST2_ST;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     drf_bist2_start_pause:1;
unsigned int     reserved_1:14;
unsigned int     drf_bist2_fail0:1;
unsigned int     drf_bist2_done:1;
}DRF_BIST2_ST;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_en6:1;
unsigned int     mhl_pp_ch1sel:1;
unsigned int     write_en5:1;
unsigned int     mhl_phy_test_mode:1;
unsigned int     write_en4:1;
unsigned int     xor_pixel_sel:3;
unsigned int     write_en3:1;
unsigned int     mhl_enc_sel:1;
unsigned int     write_en2:1;
unsigned int     mhl_pp_mode:1;
unsigned int     write_en1:1;
unsigned int     mhl_enable:1;
}MHLCTRL;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     write_en3:1;
unsigned int     mhl_ch_sel:1;
unsigned int     write_en2:1;
unsigned int     hdmi_chcclk_swap:1;
unsigned int     write_en1:1;
unsigned int     hdmi_chab_swap:1;
}CHSWAP;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     hdmi_prefifo_inv:1;
unsigned int     write_en1:1;
unsigned int     async_update:1;
}PREFIFO_CTRL;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_en5:1;
unsigned int     data_pola_inv:1;
unsigned int     write_en4:1;
unsigned int     hdmi_chclk_data_swap:2;
unsigned int     write_en3:1;
unsigned int     hdmi_chc_data_swap:2;
unsigned int     write_en2:1;
unsigned int     hdmi_chb_data_swap:2;
unsigned int     write_en1:1;
unsigned int     hdmi_cha_data_swap:2;
}PHYCHCRTL;

#endif

#define INTEN                                                                        000
#define INTEN_reg_addr                                                               "0x9800D000"
#define INTEN_reg                                                                    0x9800D000
#define set_INTEN_reg(data)   (*((volatile unsigned int*) INTEN_reg)=data)
#define get_INTEN_reg   (*((volatile unsigned int*) INTEN_reg))
#define INTEN_inst_adr                                                               "0x0000"
#define INTEN_inst                                                                   0x0000
#define INTEN_rxsenseint_shift                                                       (3)
#define INTEN_rxsenseint_mask                                                        (0x00000008)
#define INTEN_rxsenseint(data)                                                       (0x00000008&((data)<<3))
#define INTEN_rxsenseint_src(data)                                                   ((0x00000008&(data))>>3)
#define INTEN_get_rxsenseint(data)                                                   ((0x00000008&(data))>>3)
#define INTEN_enriupdint_shift                                                       (2)
#define INTEN_enriupdint_mask                                                        (0x00000004)
#define INTEN_enriupdint(data)                                                       (0x00000004&((data)<<2))
#define INTEN_enriupdint_src(data)                                                   ((0x00000004&(data))>>2)
#define INTEN_get_enriupdint(data)                                                   ((0x00000004&(data))>>2)
#define INTEN_enpjupdint_shift                                                       (1)
#define INTEN_enpjupdint_mask                                                        (0x00000002)
#define INTEN_enpjupdint(data)                                                       (0x00000002&((data)<<1))
#define INTEN_enpjupdint_src(data)                                                   ((0x00000002&(data))>>1)
#define INTEN_get_enpjupdint(data)                                                   ((0x00000002&(data))>>1)
#define INTEN_write_data_shift                                                       (0)
#define INTEN_write_data_mask                                                        (0x00000001)
#define INTEN_write_data(data)                                                       (0x00000001&((data)<<0))
#define INTEN_write_data_src(data)                                                   ((0x00000001&(data))>>0)
#define INTEN_get_write_data(data)                                                   ((0x00000001&(data))>>0)


#define INTENV                                                                       274
#define INTENV_reg_addr                                                              "0x9800D274"
#define INTENV_reg                                                                   0x9800D274
#define set_INTENV_reg(data)   (*((volatile unsigned int*) INTENV_reg)=data)
#define get_INTENV_reg   (*((volatile unsigned int*) INTENV_reg))
#define INTENV_inst_adr                                                              "0x009D"
#define INTENV_inst                                                                  0x009D
#define INTENV_vendint_shift                                                         (2)
#define INTENV_vendint_mask                                                          (0x00000004)
#define INTENV_vendint(data)                                                         (0x00000004&((data)<<2))
#define INTENV_vendint_src(data)                                                     ((0x00000004&(data))>>2)
#define INTENV_get_vendint(data)                                                     ((0x00000004&(data))>>2)
#define INTENV_vsyncint_shift                                                        (1)
#define INTENV_vsyncint_mask                                                         (0x00000002)
#define INTENV_vsyncint(data)                                                        (0x00000002&((data)<<1))
#define INTENV_vsyncint_src(data)                                                    ((0x00000002&(data))>>1)
#define INTENV_get_vsyncint(data)                                                    ((0x00000002&(data))>>1)
#define INTENV_write_data_shift                                                      (0)
#define INTENV_write_data_mask                                                       (0x00000001)
#define INTENV_write_data(data)                                                      (0x00000001&((data)<<0))
#define INTENV_write_data_src(data)                                                  ((0x00000001&(data))>>0)
#define INTENV_get_write_data(data)                                                  ((0x00000001&(data))>>0)


#define AUDIO_ST                                                                     004
#define AUDIO_ST_reg_addr                                                            "0x9800D004"
#define AUDIO_ST_reg                                                                 0x9800D004
#define set_AUDIO_ST_reg(data)   (*((volatile unsigned int*) AUDIO_ST_reg)=data)
#define get_AUDIO_ST_reg   (*((volatile unsigned int*) AUDIO_ST_reg))
#define AUDIO_ST_inst_adr                                                            "0x0001"
#define AUDIO_ST_inst                                                                0x0001
#define AUDIO_ST_asfifo_empty_shift                                                  (4)
#define AUDIO_ST_asfifo_empty_mask                                                   (0x00000010)
#define AUDIO_ST_asfifo_empty(data)                                                  (0x00000010&((data)<<4))
#define AUDIO_ST_asfifo_empty_src(data)                                              ((0x00000010&(data))>>4)
#define AUDIO_ST_get_asfifo_empty(data)                                              ((0x00000010&(data))>>4)
#define AUDIO_ST_asfifo_full_shift                                                   (3)
#define AUDIO_ST_asfifo_full_mask                                                    (0x00000008)
#define AUDIO_ST_asfifo_full(data)                                                   (0x00000008&((data)<<3))
#define AUDIO_ST_asfifo_full_src(data)                                               ((0x00000008&(data))>>3)
#define AUDIO_ST_get_asfifo_full(data)                                               ((0x00000008&(data))>>3)
#define AUDIO_ST_owctshw_shift                                                       (2)
#define AUDIO_ST_owctshw_mask                                                        (0x00000004)
#define AUDIO_ST_owctshw(data)                                                       (0x00000004&((data)<<2))
#define AUDIO_ST_owctshw_src(data)                                                   ((0x00000004&(data))>>2)
#define AUDIO_ST_get_owctshw(data)                                                   ((0x00000004&(data))>>2)
#define AUDIO_ST_asfifoow_shift                                                      (1)
#define AUDIO_ST_asfifoow_mask                                                       (0x00000002)
#define AUDIO_ST_asfifoow(data)                                                      (0x00000002&((data)<<1))
#define AUDIO_ST_asfifoow_src(data)                                                  ((0x00000002&(data))>>1)
#define AUDIO_ST_get_asfifoow(data)                                                  ((0x00000002&(data))>>1)
#define AUDIO_ST_write_data_shift                                                    (0)
#define AUDIO_ST_write_data_mask                                                     (0x00000001)
#define AUDIO_ST_write_data(data)                                                    (0x00000001&((data)<<0))
#define AUDIO_ST_write_data_src(data)                                                ((0x00000001&(data))>>0)
#define AUDIO_ST_get_write_data(data)                                                ((0x00000001&(data))>>0)


#define INTST                                                                        008
#define INTST_reg_addr                                                               "0x9800D008"
#define INTST_reg                                                                    0x9800D008
#define set_INTST_reg(data)   (*((volatile unsigned int*) INTST_reg)=data)
#define get_INTST_reg   (*((volatile unsigned int*) INTST_reg))
#define INTST_inst_adr                                                               "0x0002"
#define INTST_inst                                                                   0x0002
#define INTST_rxupdated_shift                                                        (2)
#define INTST_rxupdated_mask                                                         (0x00000004)
#define INTST_rxupdated(data)                                                        (0x00000004&((data)<<2))
#define INTST_rxupdated_src(data)                                                    ((0x00000004&(data))>>2)
#define INTST_get_rxupdated(data)                                                    ((0x00000004&(data))>>2)
#define INTST_riupdated_shift                                                        (1)
#define INTST_riupdated_mask                                                         (0x00000002)
#define INTST_riupdated(data)                                                        (0x00000002&((data)<<1))
#define INTST_riupdated_src(data)                                                    ((0x00000002&(data))>>1)
#define INTST_get_riupdated(data)                                                    ((0x00000002&(data))>>1)
#define INTST_pjupdated_shift                                                        (0)
#define INTST_pjupdated_mask                                                         (0x00000001)
#define INTST_pjupdated(data)                                                        (0x00000001&((data)<<0))
#define INTST_pjupdated_src(data)                                                    ((0x00000001&(data))>>0)
#define INTST_get_pjupdated(data)                                                    ((0x00000001&(data))>>0)


#define INTSTV                                                                       0x9800D278
#define INTSTV_reg_addr                                                              "0x9800D278"
#define INTSTV_reg                                                                   0x9800D278
#define set_INTSTV_reg(data)   (*((volatile unsigned int*) INTSTV_reg)=data)
#define get_INTSTV_reg   (*((volatile unsigned int*) INTSTV_reg))
#define INTSTV_inst_adr                                                              "0x009E"
#define INTSTV_inst                                                                  0x009E
#define INTSTV_vendupdated_shift                                                     (1)
#define INTSTV_vendupdated_mask                                                      (0x00000002)
#define INTSTV_vendupdated(data)                                                     (0x00000002&((data)<<1))
#define INTSTV_vendupdated_src(data)                                                 ((0x00000002&(data))>>1)
#define INTSTV_get_vendupdated(data)                                                 ((0x00000002&(data))>>1)
#define INTSTV_vsyncupdated_shift                                                    (0)
#define INTSTV_vsyncupdated_mask                                                     (0x00000001)
#define INTSTV_vsyncupdated(data)                                                    (0x00000001&((data)<<0))
#define INTSTV_vsyncupdated_src(data)                                                ((0x00000001&(data))>>0)
#define INTSTV_get_vsyncupdated(data)                                                ((0x00000001&(data))>>0)


#define HDMI_PHY_STATUS                                                              0x9800D15c
#define HDMI_PHY_STATUS_reg_addr                                                     "0x9800D15C"
#define HDMI_PHY_STATUS_reg                                                          0x9800D15C
#define HDMI_set_PHY_STATUS_reg(data)   (*((volatile unsigned int*) PHY_STATUS_reg)=data)
#define HDMI_get_PHY_STATUS_reg   (*((volatile unsigned int*) PHY_STATUS_reg))
#define HDMI_PHY_STATUS_inst_adr                                                     "0x0057"
#define HDMI_PHY_STATUS_inst                                                         0x0057
#define HDMI_PHY_STATUS_wdout_shift                                                  (1)
#define HDMI_PHY_STATUS_wdout_mask                                                   (0x00000002)
#define HDMI_PHY_STATUS_wdout(data)                                                  (0x00000002&((data)<<1))
#define HDMI_PHY_STATUS_wdout_src(data)                                              ((0x00000002&(data))>>1)
#define HDMI_PHY_STATUS_get_wdout(data)                                              ((0x00000002&(data))>>1)
#define HDMI_PHY_STATUS_Rxstatus_shift                                               (0)
#define HDMI_PHY_STATUS_Rxstatus_mask                                                (0x00000001)
#define HDMI_PHY_STATUS_Rxstatus(data)                                               (0x00000001&((data)<<0))
#define HDMI_PHY_STATUS_Rxstatus_src(data)                                           ((0x00000001&(data))>>0)
#define HDMI_PHY_STATUS_get_Rxstatus(data)                                           ((0x00000001&(data))>>0)


#define UPDATE_ST                                                                    0x9800D00c
#define UPDATE_ST_reg_addr                                                           "0x9800D00C"
#define UPDATE_ST_reg                                                                0x9800D00C
#define set_UPDATE_ST_reg(data)   (*((volatile unsigned int*) UPDATE_ST_reg)=data)
#define get_UPDATE_ST_reg   (*((volatile unsigned int*) UPDATE_ST_reg))
#define UPDATE_ST_inst_adr                                                           "0x0003"
#define UPDATE_ST_inst                                                               0x0003
#define UPDATE_ST_write_en2_shift                                                    (17)
#define UPDATE_ST_write_en2_mask                                                     (0x00020000)
#define UPDATE_ST_write_en2(data)                                                    (0x00020000&((data)<<17))
#define UPDATE_ST_write_en2_src(data)                                                ((0x00020000&(data))>>17)
#define UPDATE_ST_get_write_en2(data)                                                ((0x00020000&(data))>>17)
#define UPDATE_ST_rirate_shift                                                       (9)
#define UPDATE_ST_rirate_mask                                                        (0x0001FE00)
#define UPDATE_ST_rirate(data)                                                       (0x0001FE00&((data)<<9))
#define UPDATE_ST_rirate_src(data)                                                   ((0x0001FE00&(data))>>9)
#define UPDATE_ST_get_rirate(data)                                                   ((0x0001FE00&(data))>>9)
#define UPDATE_ST_write_en1_shift                                                    (8)
#define UPDATE_ST_write_en1_mask                                                     (0x00000100)
#define UPDATE_ST_write_en1(data)                                                    (0x00000100&((data)<<8))
#define UPDATE_ST_write_en1_src(data)                                                ((0x00000100&(data))>>8)
#define UPDATE_ST_get_write_en1(data)                                                ((0x00000100&(data))>>8)
#define UPDATE_ST_pjrate_shift                                                       (0)
#define UPDATE_ST_pjrate_mask                                                        (0x000000FF)
#define UPDATE_ST_pjrate(data)                                                       (0x000000FF&((data)<<0))
#define UPDATE_ST_pjrate_src(data)                                                   ((0x000000FF&(data))>>0)
#define UPDATE_ST_get_pjrate(data)                                                   ((0x000000FF&(data))>>0)


#define CHNL_SEL                                                                     0x9800D020
#define CHNL_SEL_reg_addr                                                            "0x9800D020"
#define CHNL_SEL_reg                                                                 0x9800D020
#define set_CHNL_SEL_reg(data)   (*((volatile unsigned int*) CHNL_SEL_reg)=data)
#define get_CHNL_SEL_reg   (*((volatile unsigned int*) CHNL_SEL_reg))
#define CHNL_SEL_inst_adr                                                            "0x0008"
#define CHNL_SEL_inst                                                                0x0008
#define CHNL_SEL_sram_shut_down_en_shift                                             (11)
#define CHNL_SEL_sram_shut_down_en_mask                                              (0x00000800)
#define CHNL_SEL_sram_shut_down_en(data)                                             (0x00000800&((data)<<11))
#define CHNL_SEL_sram_shut_down_en_src(data)                                         ((0x00000800&(data))>>11)
#define CHNL_SEL_get_sram_shut_down_en(data)                                         ((0x00000800&(data))>>11)
#define CHNL_SEL_sram_sleep_en_shift                                                 (10)
#define CHNL_SEL_sram_sleep_en_mask                                                  (0x00000400)
#define CHNL_SEL_sram_sleep_en(data)                                                 (0x00000400&((data)<<10))
#define CHNL_SEL_sram_sleep_en_src(data)                                             ((0x00000400&(data))>>10)
#define CHNL_SEL_get_sram_sleep_en(data)                                             ((0x00000400&(data))>>10)
#define CHNL_SEL_video_sd_shift                                                      (9)
#define CHNL_SEL_video_sd_mask                                                       (0x00000200)
#define CHNL_SEL_video_sd(data)                                                      (0x00000200&((data)<<9))
#define CHNL_SEL_video_sd_src(data)                                                  ((0x00000200&(data))>>9)
#define CHNL_SEL_get_video_sd(data)                                                  ((0x00000200&(data))>>9)
#define CHNL_SEL_Interlaced_vfmt_shift                                               (8)
#define CHNL_SEL_Interlaced_vfmt_mask                                                (0x00000100)
#define CHNL_SEL_Interlaced_vfmt(data)                                               (0x00000100&((data)<<8))
#define CHNL_SEL_Interlaced_vfmt_src(data)                                           ((0x00000100&(data))>>8)
#define CHNL_SEL_get_Interlaced_vfmt(data)                                           ((0x00000100&(data))>>8)
#define CHNL_SEL_3D_video_format_shift                                               (4)
#define CHNL_SEL_3D_video_format_mask                                                (0x000000F0)
#define CHNL_SEL_3D_video_format(data)                                               (0x000000F0&((data)<<4))
#define CHNL_SEL_3D_video_format_src(data)                                           ((0x000000F0&(data))>>4)
#define CHNL_SEL_get_3D_video_format(data)                                           ((0x000000F0&(data))>>4)
#define CHNL_SEL_En_3D_shift                                                         (3)
#define CHNL_SEL_En_3D_mask                                                          (0x00000008)
#define CHNL_SEL_En_3D(data)                                                         (0x00000008&((data)<<3))
#define CHNL_SEL_En_3D_src(data)                                                     ((0x00000008&(data))>>3)
#define CHNL_SEL_get_En_3D(data)                                                     ((0x00000008&(data))>>3)
#define CHNL_SEL_timing_gen_en_shift                                                 (2)
#define CHNL_SEL_timing_gen_en_mask                                                  (0x00000004)
#define CHNL_SEL_timing_gen_en(data)                                                 (0x00000004&((data)<<2))
#define CHNL_SEL_timing_gen_en_src(data)                                             ((0x00000004&(data))>>2)
#define CHNL_SEL_get_timing_gen_en(data)                                             ((0x00000004&(data))>>2)
#define CHNL_SEL_chl_sel_shift                                                       (0)
#define CHNL_SEL_chl_sel_mask                                                        (0x00000003)
#define CHNL_SEL_chl_sel(data)                                                       (0x00000003&((data)<<0))
#define CHNL_SEL_chl_sel_src(data)                                                   ((0x00000003&(data))>>0)
#define CHNL_SEL_get_chl_sel(data)                                                   ((0x00000003&(data))>>0)


#define CS_TRANS0                                                                    0x9800D024
#define CS_TRANS0_reg_addr                                                           "0x9800D024"
#define CS_TRANS0_reg                                                                0x9800D024
#define set_CS_TRANS0_reg(data)   (*((volatile unsigned int*) CS_TRANS0_reg)=data)
#define get_CS_TRANS0_reg   (*((volatile unsigned int*) CS_TRANS0_reg))
#define CS_TRANS0_inst_adr                                                           "0x0009"
#define CS_TRANS0_inst                                                               0x0009
#define CS_TRANS0_c1_shift                                                           (0)
#define CS_TRANS0_c1_mask                                                            (0x0001FFFF)
#define CS_TRANS0_c1(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS0_c1_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS0_get_c1(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS1                                                                    0x9800D028
#define CS_TRANS1_reg_addr                                                           "0x9800D028"
#define CS_TRANS1_reg                                                                0x9800D028
#define set_CS_TRANS1_reg(data)   (*((volatile unsigned int*) CS_TRANS1_reg)=data)
#define get_CS_TRANS1_reg   (*((volatile unsigned int*) CS_TRANS1_reg))
#define CS_TRANS1_inst_adr                                                           "0x000A"
#define CS_TRANS1_inst                                                               0x000A
#define CS_TRANS1_c2_shift                                                           (0)
#define CS_TRANS1_c2_mask                                                            (0x0001FFFF)
#define CS_TRANS1_c2(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS1_c2_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS1_get_c2(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS2                                                                    0x9800D02c
#define CS_TRANS2_reg_addr                                                           "0x9800D02C"
#define CS_TRANS2_reg                                                                0x9800D02C
#define set_CS_TRANS2_reg(data)   (*((volatile unsigned int*) CS_TRANS2_reg)=data)
#define get_CS_TRANS2_reg   (*((volatile unsigned int*) CS_TRANS2_reg))
#define CS_TRANS2_inst_adr                                                           "0x000B"
#define CS_TRANS2_inst                                                               0x000B
#define CS_TRANS2_c3_shift                                                           (0)
#define CS_TRANS2_c3_mask                                                            (0x0001FFFF)
#define CS_TRANS2_c3(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS2_c3_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS2_get_c3(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS3                                                                    0x9800D200
#define CS_TRANS3_reg_addr                                                           "0x9800D200"
#define CS_TRANS3_reg                                                                0x9800D200
#define set_CS_TRANS3_reg(data)   (*((volatile unsigned int*) CS_TRANS3_reg)=data)
#define get_CS_TRANS3_reg   (*((volatile unsigned int*) CS_TRANS3_reg))
#define CS_TRANS3_inst_adr                                                           "0x0080"
#define CS_TRANS3_inst                                                               0x0080
#define CS_TRANS3_c4_shift                                                           (0)
#define CS_TRANS3_c4_mask                                                            (0x0001FFFF)
#define CS_TRANS3_c4(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS3_c4_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS3_get_c4(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS4                                                                    0x9800D204
#define CS_TRANS4_reg_addr                                                           "0x9800D204"
#define CS_TRANS4_reg                                                                0x9800D204
#define set_CS_TRANS4_reg(data)   (*((volatile unsigned int*) CS_TRANS4_reg)=data)
#define get_CS_TRANS4_reg   (*((volatile unsigned int*) CS_TRANS4_reg))
#define CS_TRANS4_inst_adr                                                           "0x0081"
#define CS_TRANS4_inst                                                               0x0081
#define CS_TRANS4_c5_shift                                                           (0)
#define CS_TRANS4_c5_mask                                                            (0x0001FFFF)
#define CS_TRANS4_c5(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS4_c5_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS4_get_c5(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS5                                                                    0x9800D208
#define CS_TRANS5_reg_addr                                                           "0x9800D208"
#define CS_TRANS5_reg                                                                0x9800D208
#define set_CS_TRANS5_reg(data)   (*((volatile unsigned int*) CS_TRANS5_reg)=data)
#define get_CS_TRANS5_reg   (*((volatile unsigned int*) CS_TRANS5_reg))
#define CS_TRANS5_inst_adr                                                           "0x0082"
#define CS_TRANS5_inst                                                               0x0082
#define CS_TRANS5_c6_shift                                                           (0)
#define CS_TRANS5_c6_mask                                                            (0x0001FFFF)
#define CS_TRANS5_c6(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS5_c6_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS5_get_c6(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS6                                                                    0x9800D20c
#define CS_TRANS6_reg_addr                                                           "0x9800D20C"
#define CS_TRANS6_reg                                                                0x9800D20C
#define set_CS_TRANS6_reg(data)   (*((volatile unsigned int*) CS_TRANS6_reg)=data)
#define get_CS_TRANS6_reg   (*((volatile unsigned int*) CS_TRANS6_reg))
#define CS_TRANS6_inst_adr                                                           "0x0083"
#define CS_TRANS6_inst                                                               0x0083
#define CS_TRANS6_c7_shift                                                           (0)
#define CS_TRANS6_c7_mask                                                            (0x0001FFFF)
#define CS_TRANS6_c7(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS6_c7_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS6_get_c7(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS7                                                                    0x9800D210
#define CS_TRANS7_reg_addr                                                           "0x9800D210"
#define CS_TRANS7_reg                                                                0x9800D210
#define set_CS_TRANS7_reg(data)   (*((volatile unsigned int*) CS_TRANS7_reg)=data)
#define get_CS_TRANS7_reg   (*((volatile unsigned int*) CS_TRANS7_reg))
#define CS_TRANS7_inst_adr                                                           "0x0084"
#define CS_TRANS7_inst                                                               0x0084
#define CS_TRANS7_c8_shift                                                           (0)
#define CS_TRANS7_c8_mask                                                            (0x0001FFFF)
#define CS_TRANS7_c8(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS7_c8_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS7_get_c8(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS8                                                                    0x9800D214
#define CS_TRANS8_reg_addr                                                           "0x9800D214"
#define CS_TRANS8_reg                                                                0x9800D214
#define set_CS_TRANS8_reg(data)   (*((volatile unsigned int*) CS_TRANS8_reg)=data)
#define get_CS_TRANS8_reg   (*((volatile unsigned int*) CS_TRANS8_reg))
#define CS_TRANS8_inst_adr                                                           "0x0085"
#define CS_TRANS8_inst                                                               0x0085
#define CS_TRANS8_c9_shift                                                           (0)
#define CS_TRANS8_c9_mask                                                            (0x0001FFFF)
#define CS_TRANS8_c9(data)                                                           (0x0001FFFF&((data)<<0))
#define CS_TRANS8_c9_src(data)                                                       ((0x0001FFFF&(data))>>0)
#define CS_TRANS8_get_c9(data)                                                       ((0x0001FFFF&(data))>>0)


#define CS_TRANS9                                                                    0x9800D218
#define CS_TRANS9_reg_addr                                                           "0x9800D218"
#define CS_TRANS9_reg                                                                0x9800D218
#define set_CS_TRANS9_reg(data)   (*((volatile unsigned int*) CS_TRANS9_reg)=data)
#define get_CS_TRANS9_reg   (*((volatile unsigned int*) CS_TRANS9_reg))
#define CS_TRANS9_inst_adr                                                           "0x0086"
#define CS_TRANS9_inst                                                               0x0086
#define CS_TRANS9_k1_shift                                                           (0)
#define CS_TRANS9_k1_mask                                                            (0x0000FFFF)
#define CS_TRANS9_k1(data)                                                           (0x0000FFFF&((data)<<0))
#define CS_TRANS9_k1_src(data)                                                       ((0x0000FFFF&(data))>>0)
#define CS_TRANS9_get_k1(data)                                                       ((0x0000FFFF&(data))>>0)


#define CS_TRANS10                                                                   0x9800D21c
#define CS_TRANS10_reg_addr                                                          "0x9800D21C"
#define CS_TRANS10_reg                                                               0x9800D21C
#define set_CS_TRANS10_reg(data)   (*((volatile unsigned int*) CS_TRANS10_reg)=data)
#define get_CS_TRANS10_reg   (*((volatile unsigned int*) CS_TRANS10_reg))
#define CS_TRANS10_inst_adr                                                          "0x0087"
#define CS_TRANS10_inst                                                              0x0087
#define CS_TRANS10_k2_shift                                                          (0)
#define CS_TRANS10_k2_mask                                                           (0x0000FFFF)
#define CS_TRANS10_k2(data)                                                          (0x0000FFFF&((data)<<0))
#define CS_TRANS10_k2_src(data)                                                      ((0x0000FFFF&(data))>>0)
#define CS_TRANS10_get_k2(data)                                                      ((0x0000FFFF&(data))>>0)


#define CS_TRANS11                                                                   0x9800D220
#define CS_TRANS11_reg_addr                                                          "0x9800D220"
#define CS_TRANS11_reg                                                               0x9800D220
#define set_CS_TRANS11_reg(data)   (*((volatile unsigned int*) CS_TRANS11_reg)=data)
#define get_CS_TRANS11_reg   (*((volatile unsigned int*) CS_TRANS11_reg))
#define CS_TRANS11_inst_adr                                                          "0x0088"
#define CS_TRANS11_inst                                                              0x0088
#define CS_TRANS11_k3_shift                                                          (0)
#define CS_TRANS11_k3_mask                                                           (0x0000FFFF)
#define CS_TRANS11_k3(data)                                                          (0x0000FFFF&((data)<<0))
#define CS_TRANS11_k3_src(data)                                                      ((0x0000FFFF&(data))>>0)
#define CS_TRANS11_get_k3(data)                                                      ((0x0000FFFF&(data))>>0)


#define CS_TRANS12                                                                   0x9800D224
#define CS_TRANS12_reg_addr                                                          "0x9800D224"
#define CS_TRANS12_reg                                                               0x9800D224
#define set_CS_TRANS12_reg(data)   (*((volatile unsigned int*) CS_TRANS12_reg)=data)
#define get_CS_TRANS12_reg   (*((volatile unsigned int*) CS_TRANS12_reg))
#define CS_TRANS12_inst_adr                                                          "0x0089"
#define CS_TRANS12_inst                                                              0x0089
#define CS_TRANS12_write_en2_shift                                                   (28)
#define CS_TRANS12_write_en2_mask                                                    (0x10000000)
#define CS_TRANS12_write_en2(data)                                                   (0x10000000&((data)<<28))
#define CS_TRANS12_write_en2_src(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS12_get_write_en2(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS12_ygmax_shift                                                       (16)
#define CS_TRANS12_ygmax_mask                                                        (0x0FFF0000)
#define CS_TRANS12_ygmax(data)                                                       (0x0FFF0000&((data)<<16))
#define CS_TRANS12_ygmax_src(data)                                                   ((0x0FFF0000&(data))>>16)
#define CS_TRANS12_get_ygmax(data)                                                   ((0x0FFF0000&(data))>>16)
#define CS_TRANS12_write_en1_shift                                                   (12)
#define CS_TRANS12_write_en1_mask                                                    (0x00001000)
#define CS_TRANS12_write_en1(data)                                                   (0x00001000&((data)<<12))
#define CS_TRANS12_write_en1_src(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS12_get_write_en1(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS12_ygmin_shift                                                       (0)
#define CS_TRANS12_ygmin_mask                                                        (0x00000FFF)
#define CS_TRANS12_ygmin(data)                                                       (0x00000FFF&((data)<<0))
#define CS_TRANS12_ygmin_src(data)                                                   ((0x00000FFF&(data))>>0)
#define CS_TRANS12_get_ygmin(data)                                                   ((0x00000FFF&(data))>>0)


#define CS_TRANS13                                                                   0x9800D228
#define CS_TRANS13_reg_addr                                                          "0x9800D228"
#define CS_TRANS13_reg                                                               0x9800D228
#define set_CS_TRANS13_reg(data)   (*((volatile unsigned int*) CS_TRANS13_reg)=data)
#define get_CS_TRANS13_reg   (*((volatile unsigned int*) CS_TRANS13_reg))
#define CS_TRANS13_inst_adr                                                          "0x008A"
#define CS_TRANS13_inst                                                              0x008A
#define CS_TRANS13_write_en2_shift                                                   (28)
#define CS_TRANS13_write_en2_mask                                                    (0x10000000)
#define CS_TRANS13_write_en2(data)                                                   (0x10000000&((data)<<28))
#define CS_TRANS13_write_en2_src(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS13_get_write_en2(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS13_cbbmax_shift                                                      (16)
#define CS_TRANS13_cbbmax_mask                                                       (0x0FFF0000)
#define CS_TRANS13_cbbmax(data)                                                      (0x0FFF0000&((data)<<16))
#define CS_TRANS13_cbbmax_src(data)                                                  ((0x0FFF0000&(data))>>16)
#define CS_TRANS13_get_cbbmax(data)                                                  ((0x0FFF0000&(data))>>16)
#define CS_TRANS13_write_en1_shift                                                   (12)
#define CS_TRANS13_write_en1_mask                                                    (0x00001000)
#define CS_TRANS13_write_en1(data)                                                   (0x00001000&((data)<<12))
#define CS_TRANS13_write_en1_src(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS13_get_write_en1(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS13_cbbmin_shift                                                      (0)
#define CS_TRANS13_cbbmin_mask                                                       (0x00000FFF)
#define CS_TRANS13_cbbmin(data)                                                      (0x00000FFF&((data)<<0))
#define CS_TRANS13_cbbmin_src(data)                                                  ((0x00000FFF&(data))>>0)
#define CS_TRANS13_get_cbbmin(data)                                                  ((0x00000FFF&(data))>>0)


#define CS_TRANS14                                                                   0x9800D22c
#define CS_TRANS14_reg_addr                                                          "0x9800D22C"
#define CS_TRANS14_reg                                                               0x9800D22C
#define set_CS_TRANS14_reg(data)   (*((volatile unsigned int*) CS_TRANS14_reg)=data)
#define get_CS_TRANS14_reg   (*((volatile unsigned int*) CS_TRANS14_reg))
#define CS_TRANS14_inst_adr                                                          "0x008B"
#define CS_TRANS14_inst                                                              0x008B
#define CS_TRANS14_write_en2_shift                                                   (28)
#define CS_TRANS14_write_en2_mask                                                    (0x10000000)
#define CS_TRANS14_write_en2(data)                                                   (0x10000000&((data)<<28))
#define CS_TRANS14_write_en2_src(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS14_get_write_en2(data)                                               ((0x10000000&(data))>>28)
#define CS_TRANS14_crrmax_shift                                                      (16)
#define CS_TRANS14_crrmax_mask                                                       (0x0FFF0000)
#define CS_TRANS14_crrmax(data)                                                      (0x0FFF0000&((data)<<16))
#define CS_TRANS14_crrmax_src(data)                                                  ((0x0FFF0000&(data))>>16)
#define CS_TRANS14_get_crrmax(data)                                                  ((0x0FFF0000&(data))>>16)
#define CS_TRANS14_write_en1_shift                                                   (12)
#define CS_TRANS14_write_en1_mask                                                    (0x00001000)
#define CS_TRANS14_write_en1(data)                                                   (0x00001000&((data)<<12))
#define CS_TRANS14_write_en1_src(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS14_get_write_en1(data)                                               ((0x00001000&(data))>>12)
#define CS_TRANS14_crrmin_shift                                                      (0)
#define CS_TRANS14_crrmin_mask                                                       (0x00000FFF)
#define CS_TRANS14_crrmin(data)                                                      (0x00000FFF&((data)<<0))
#define CS_TRANS14_crrmin_src(data)                                                  ((0x00000FFF&(data))>>0)
#define CS_TRANS14_get_crrmin(data)                                                  ((0x00000FFF&(data))>>0)


#define SYNC_DLY                                                                     0x9800D030
#define SYNC_DLY_reg_addr                                                            "0x9800D030"
#define SYNC_DLY_reg                                                                 0x9800D030
#define set_SYNC_DLY_reg(data)   (*((volatile unsigned int*) SYNC_DLY_reg)=data)
#define get_SYNC_DLY_reg   (*((volatile unsigned int*) SYNC_DLY_reg))
#define SYNC_DLY_inst_adr                                                            "0x000C"
#define SYNC_DLY_inst                                                                0x000C
#define SYNC_DLY_write_en4_shift                                                     (11)
#define SYNC_DLY_write_en4_mask                                                      (0x00000800)
#define SYNC_DLY_write_en4(data)                                                     (0x00000800&((data)<<11))
#define SYNC_DLY_write_en4_src(data)                                                 ((0x00000800&(data))>>11)
#define SYNC_DLY_get_write_en4(data)                                                 ((0x00000800&(data))>>11)
#define SYNC_DLY_nor_v_shift                                                         (9)
#define SYNC_DLY_nor_v_mask                                                          (0x00000600)
#define SYNC_DLY_nor_v(data)                                                         (0x00000600&((data)<<9))
#define SYNC_DLY_nor_v_src(data)                                                     ((0x00000600&(data))>>9)
#define SYNC_DLY_get_nor_v(data)                                                     ((0x00000600&(data))>>9)
#define SYNC_DLY_write_en3_shift                                                     (8)
#define SYNC_DLY_write_en3_mask                                                      (0x00000100)
#define SYNC_DLY_write_en3(data)                                                     (0x00000100&((data)<<8))
#define SYNC_DLY_write_en3_src(data)                                                 ((0x00000100&(data))>>8)
#define SYNC_DLY_get_write_en3(data)                                                 ((0x00000100&(data))>>8)
#define SYNC_DLY_nor_h_shift                                                         (6)
#define SYNC_DLY_nor_h_mask                                                          (0x000000C0)
#define SYNC_DLY_nor_h(data)                                                         (0x000000C0&((data)<<6))
#define SYNC_DLY_nor_h_src(data)                                                     ((0x000000C0&(data))>>6)
#define SYNC_DLY_get_nor_h(data)                                                     ((0x000000C0&(data))>>6)
#define SYNC_DLY_write_en2_shift                                                     (5)
#define SYNC_DLY_write_en2_mask                                                      (0x00000020)
#define SYNC_DLY_write_en2(data)                                                     (0x00000020&((data)<<5))
#define SYNC_DLY_write_en2_src(data)                                                 ((0x00000020&(data))>>5)
#define SYNC_DLY_get_write_en2(data)                                                 ((0x00000020&(data))>>5)
#define SYNC_DLY_disp_v_shift                                                        (3)
#define SYNC_DLY_disp_v_mask                                                         (0x00000018)
#define SYNC_DLY_disp_v(data)                                                        (0x00000018&((data)<<3))
#define SYNC_DLY_disp_v_src(data)                                                    ((0x00000018&(data))>>3)
#define SYNC_DLY_get_disp_v(data)                                                    ((0x00000018&(data))>>3)
#define SYNC_DLY_write_en1_shift                                                     (2)
#define SYNC_DLY_write_en1_mask                                                      (0x00000004)
#define SYNC_DLY_write_en1(data)                                                     (0x00000004&((data)<<2))
#define SYNC_DLY_write_en1_src(data)                                                 ((0x00000004&(data))>>2)
#define SYNC_DLY_get_write_en1(data)                                                 ((0x00000004&(data))>>2)
#define SYNC_DLY_disp_h_shift                                                        (0)
#define SYNC_DLY_disp_h_mask                                                         (0x00000003)
#define SYNC_DLY_disp_h(data)                                                        (0x00000003&((data)<<0))
#define SYNC_DLY_disp_h_src(data)                                                    ((0x00000003&(data))>>0)
#define SYNC_DLY_get_disp_h(data)                                                    ((0x00000003&(data))>>0)


#define CR                                                                           0x9800D034
#define CR_reg_addr                                                                  "0x9800D034"
#define CR_reg                                                                       0x9800D034
#define set_CR_reg(data)   (*((volatile unsigned int*) CR_reg)=data)
#define get_CR_reg   (*((volatile unsigned int*) CR_reg))
#define CR_inst_adr                                                                  "0x000D"
#define CR_inst                                                                      0x000D
#define CR_write_en3_shift                                                           (5)
#define CR_write_en3_mask                                                            (0x00000020)
#define CR_write_en3(data)                                                           (0x00000020&((data)<<5))
#define CR_write_en3_src(data)                                                       ((0x00000020&(data))>>5)
#define CR_get_write_en3(data)                                                       ((0x00000020&(data))>>5)
#define CR_tmds_encen_shift                                                          (4)
#define CR_tmds_encen_mask                                                           (0x00000010)
#define CR_tmds_encen(data)                                                          (0x00000010&((data)<<4))
#define CR_tmds_encen_src(data)                                                      ((0x00000010&(data))>>4)
#define CR_get_tmds_encen(data)                                                      ((0x00000010&(data))>>4)
#define CR_write_en2_shift                                                           (3)
#define CR_write_en2_mask                                                            (0x00000008)
#define CR_write_en2(data)                                                           (0x00000008&((data)<<3))
#define CR_write_en2_src(data)                                                       ((0x00000008&(data))>>3)
#define CR_get_write_en2(data)                                                       ((0x00000008&(data))>>3)
#define CR_enablehdcp_shift                                                          (2)
#define CR_enablehdcp_mask                                                           (0x00000004)
#define CR_enablehdcp(data)                                                          (0x00000004&((data)<<2))
#define CR_enablehdcp_src(data)                                                      ((0x00000004&(data))>>2)
#define CR_get_enablehdcp(data)                                                      ((0x00000004&(data))>>2)
#define CR_write_en1_shift                                                           (1)
#define CR_write_en1_mask                                                            (0x00000002)
#define CR_write_en1(data)                                                           (0x00000002&((data)<<1))
#define CR_write_en1_src(data)                                                       ((0x00000002&(data))>>1)
#define CR_get_write_en1(data)                                                       ((0x00000002&(data))>>1)
#define CR_enablehdmi_shift                                                          (0)
#define CR_enablehdmi_mask                                                           (0x00000001)
#define CR_enablehdmi(data)                                                          (0x00000001&((data)<<0))
#define CR_enablehdmi_src(data)                                                      ((0x00000001&(data))>>0)
#define CR_get_enablehdmi(data)                                                      ((0x00000001&(data))>>0)


#define DPC                                                                          0x9800D154
#define DPC_reg_addr                                                                 "0x9800D154"
#define DPC_reg                                                                      0x9800D154
#define set_DPC_reg(data)   (*((volatile unsigned int*) DPC_reg)=data)
#define get_DPC_reg   (*((volatile unsigned int*) DPC_reg))
#define DPC_inst_adr                                                                 "0x0055"
#define DPC_inst                                                                     0x0055
#define DPC_write_en9_shift                                                          (30)
#define DPC_write_en9_mask                                                           (0x40000000)
#define DPC_write_en9(data)                                                          (0x40000000&((data)<<30))
#define DPC_write_en9_src(data)                                                      ((0x40000000&(data))>>30)
#define DPC_get_write_en9(data)                                                      ((0x40000000&(data))>>30)
#define DPC_dp_vfch_num_shift                                                        (28)
#define DPC_dp_vfch_num_mask                                                         (0x30000000)
#define DPC_dp_vfch_num(data)                                                        (0x30000000&((data)<<28))
#define DPC_dp_vfch_num_src(data)                                                    ((0x30000000&(data))>>28)
#define DPC_get_dp_vfch_num(data)                                                    ((0x30000000&(data))>>28)
#define DPC_write_en8_shift                                                          (25)
#define DPC_write_en8_mask                                                           (0x02000000)
#define DPC_write_en8(data)                                                          (0x02000000&((data)<<25))
#define DPC_write_en8_src(data)                                                      ((0x02000000&(data))>>25)
#define DPC_get_write_en8(data)                                                      ((0x02000000&(data))>>25)
#define DPC_fp_swen_shift                                                            (24)
#define DPC_fp_swen_mask                                                             (0x01000000)
#define DPC_fp_swen(data)                                                            (0x01000000&((data)<<24))
#define DPC_fp_swen_src(data)                                                        ((0x01000000&(data))>>24)
#define DPC_get_fp_swen(data)                                                        ((0x01000000&(data))>>24)
#define DPC_write_en7_shift                                                          (23)
#define DPC_write_en7_mask                                                           (0x00800000)
#define DPC_write_en7(data)                                                          (0x00800000&((data)<<23))
#define DPC_write_en7_src(data)                                                      ((0x00800000&(data))>>23)
#define DPC_get_write_en7(data)                                                      ((0x00800000&(data))>>23)
#define DPC_fp_shift                                                                 (20)
#define DPC_fp_mask                                                                  (0x00700000)
#define DPC_fp(data)                                                                 (0x00700000&((data)<<20))
#define DPC_fp_src(data)                                                             ((0x00700000&(data))>>20)
#define DPC_get_fp(data)                                                             ((0x00700000&(data))>>20)
#define DPC_write_en6_shift                                                          (19)
#define DPC_write_en6_mask                                                           (0x00080000)
#define DPC_write_en6(data)                                                          (0x00080000&((data)<<19))
#define DPC_write_en6_src(data)                                                      ((0x00080000&(data))>>19)
#define DPC_get_write_en6(data)                                                      ((0x00080000&(data))>>19)
#define DPC_pp_swen_shift                                                            (18)
#define DPC_pp_swen_mask                                                             (0x00040000)
#define DPC_pp_swen(data)                                                            (0x00040000&((data)<<18))
#define DPC_pp_swen_src(data)                                                        ((0x00040000&(data))>>18)
#define DPC_get_pp_swen(data)                                                        ((0x00040000&(data))>>18)
#define DPC_write_en4_shift                                                          (15)
#define DPC_write_en4_mask                                                           (0x00008000)
#define DPC_write_en4(data)                                                          (0x00008000&((data)<<15))
#define DPC_write_en4_src(data)                                                      ((0x00008000&(data))>>15)
#define DPC_get_write_en4(data)                                                      ((0x00008000&(data))>>15)
#define DPC_dp_swen_shift                                                            (14)
#define DPC_dp_swen_mask                                                             (0x00004000)
#define DPC_dp_swen(data)                                                            (0x00004000&((data)<<14))
#define DPC_dp_swen_src(data)                                                        ((0x00004000&(data))>>14)
#define DPC_get_dp_swen(data)                                                        ((0x00004000&(data))>>14)
#define DPC_write_en3_shift                                                          (13)
#define DPC_write_en3_mask                                                           (0x00002000)
#define DPC_write_en3(data)                                                          (0x00002000&((data)<<13))
#define DPC_write_en3_src(data)                                                      ((0x00002000&(data))>>13)
#define DPC_get_write_en3(data)                                                      ((0x00002000&(data))>>13)
#define DPC_default_phase_shift                                                      (12)
#define DPC_default_phase_mask                                                       (0x00001000)
#define DPC_default_phase(data)                                                      (0x00001000&((data)<<12))
#define DPC_default_phase_src(data)                                                  ((0x00001000&(data))>>12)
#define DPC_get_default_phase(data)                                                  ((0x00001000&(data))>>12)
#define DPC_write_en2_shift                                                          (8)
#define DPC_write_en2_mask                                                           (0x00000100)
#define DPC_write_en2(data)                                                          (0x00000100&((data)<<8))
#define DPC_write_en2_src(data)                                                      ((0x00000100&(data))>>8)
#define DPC_get_write_en2(data)                                                      ((0x00000100&(data))>>8)
#define DPC_color_depth_shift                                                        (4)
#define DPC_color_depth_mask                                                         (0x000000F0)
#define DPC_color_depth(data)                                                        (0x000000F0&((data)<<4))
#define DPC_color_depth_src(data)                                                    ((0x000000F0&(data))>>4)
#define DPC_get_color_depth(data)                                                    ((0x000000F0&(data))>>4)
#define DPC_write_en1_shift                                                          (1)
#define DPC_write_en1_mask                                                           (0x00000002)
#define DPC_write_en1(data)                                                          (0x00000002&((data)<<1))
#define DPC_write_en1_src(data)                                                      ((0x00000002&(data))>>1)
#define DPC_get_write_en1(data)                                                      ((0x00000002&(data))>>1)
#define DPC_dpc_enable_shift                                                         (0)
#define DPC_dpc_enable_mask                                                          (0x00000001)
#define DPC_dpc_enable(data)                                                         (0x00000001&((data)<<0))
#define DPC_dpc_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define DPC_get_dpc_enable(data)                                                     ((0x00000001&(data))>>0)


#define DPC1                                                                         0x9800D158
#define DPC1_reg_addr                                                                "0x9800D158"
#define DPC1_reg                                                                     0x9800D158
#define set_DPC1_reg(data)   (*((volatile unsigned int*) DPC1_reg)=data)
#define get_DPC1_reg   (*((volatile unsigned int*) DPC1_reg))
#define DPC1_inst_adr                                                                "0x0056"
#define DPC1_inst                                                                    0x0056
#define DPC1_write_en2_shift                                                         (9)
#define DPC1_write_en2_mask                                                          (0x00000200)
#define DPC1_write_en2(data)                                                         (0x00000200&((data)<<9))
#define DPC1_write_en2_src(data)                                                     ((0x00000200&(data))>>9)
#define DPC1_get_write_en2(data)                                                     ((0x00000200&(data))>>9)
#define DPC1_dp_vfch_shift                                                           (8)
#define DPC1_dp_vfch_mask                                                            (0x00000100)
#define DPC1_dp_vfch(data)                                                           (0x00000100&((data)<<8))
#define DPC1_dp_vfch_src(data)                                                       ((0x00000100&(data))>>8)
#define DPC1_get_dp_vfch(data)                                                       ((0x00000100&(data))>>8)
#define DPC1_write_en1_shift                                                         (4)
#define DPC1_write_en1_mask                                                          (0x00000010)
#define DPC1_write_en1(data)                                                         (0x00000010&((data)<<4))
#define DPC1_write_en1_src(data)                                                     ((0x00000010&(data))>>4)
#define DPC1_get_write_en1(data)                                                     ((0x00000010&(data))>>4)
#define DPC1_pp_shift                                                                (0)
#define DPC1_pp_mask                                                                 (0x0000000F)
#define DPC1_pp(data)                                                                (0x0000000F&((data)<<0))
#define DPC1_pp_src(data)                                                            ((0x0000000F&(data))>>0)
#define DPC1_get_pp(data)                                                            ((0x0000000F&(data))>>0)


#define TMDS_EODR0                                                                   0x9800D038
#define TMDS_EODR0_reg_addr                                                          "0x9800D038"
#define TMDS_EODR0_reg                                                               0x9800D038
#define set_TMDS_EODR0_reg(data)   (*((volatile unsigned int*) TMDS_EODR0_reg)=data)
#define get_TMDS_EODR0_reg   (*((volatile unsigned int*) TMDS_EODR0_reg))
#define TMDS_EODR0_inst_adr                                                          "0x000E"
#define TMDS_EODR0_inst                                                              0x000E
#define TMDS_EODR0_tmds_ch2_out_shift                                                (20)
#define TMDS_EODR0_tmds_ch2_out_mask                                                 (0x3FF00000)
#define TMDS_EODR0_tmds_ch2_out(data)                                                (0x3FF00000&((data)<<20))
#define TMDS_EODR0_tmds_ch2_out_src(data)                                            ((0x3FF00000&(data))>>20)
#define TMDS_EODR0_get_tmds_ch2_out(data)                                            ((0x3FF00000&(data))>>20)
#define TMDS_EODR0_tmds_ch1_out_shift                                                (10)
#define TMDS_EODR0_tmds_ch1_out_mask                                                 (0x000FFC00)
#define TMDS_EODR0_tmds_ch1_out(data)                                                (0x000FFC00&((data)<<10))
#define TMDS_EODR0_tmds_ch1_out_src(data)                                            ((0x000FFC00&(data))>>10)
#define TMDS_EODR0_get_tmds_ch1_out(data)                                            ((0x000FFC00&(data))>>10)
#define TMDS_EODR0_tmds_ch0_out_shift                                                (0)
#define TMDS_EODR0_tmds_ch0_out_mask                                                 (0x000003FF)
#define TMDS_EODR0_tmds_ch0_out(data)                                                (0x000003FF&((data)<<0))
#define TMDS_EODR0_tmds_ch0_out_src(data)                                            ((0x000003FF&(data))>>0)
#define TMDS_EODR0_get_tmds_ch0_out(data)                                            ((0x000003FF&(data))>>0)


#define TMDS_EODR1                                                                   0x9800D03c
#define TMDS_EODR1_reg_addr                                                          "0x9800D03C"
#define TMDS_EODR1_reg                                                               0x9800D03C
#define set_TMDS_EODR1_reg(data)   (*((volatile unsigned int*) TMDS_EODR1_reg)=data)
#define get_TMDS_EODR1_reg   (*((volatile unsigned int*) TMDS_EODR1_reg))
#define TMDS_EODR1_inst_adr                                                          "0x000F"
#define TMDS_EODR1_inst                                                              0x000F
#define TMDS_EODR1_default_phase_st_shift                                            (12)
#define TMDS_EODR1_default_phase_st_mask                                             (0x00001000)
#define TMDS_EODR1_default_phase_st(data)                                            (0x00001000&((data)<<12))
#define TMDS_EODR1_default_phase_st_src(data)                                        ((0x00001000&(data))>>12)
#define TMDS_EODR1_get_default_phase_st(data)                                        ((0x00001000&(data))>>12)
#define TMDS_EODR1_tmds_clk_out_shift                                                (0)
#define TMDS_EODR1_tmds_clk_out_mask                                                 (0x000003FF)
#define TMDS_EODR1_tmds_clk_out(data)                                                (0x000003FF&((data)<<0))
#define TMDS_EODR1_tmds_clk_out_src(data)                                            ((0x000003FF&(data))>>0)
#define TMDS_EODR1_get_tmds_clk_out(data)                                            ((0x000003FF&(data))>>0)


#define TMDS_SCR1                                                                    0x9800D040
#define TMDS_SCR1_reg_addr                                                           "0x9800D040"
#define TMDS_SCR1_reg                                                                0x9800D040
#define set_TMDS_SCR1_reg(data)   (*((volatile unsigned int*) TMDS_SCR1_reg)=data)
#define get_TMDS_SCR1_reg   (*((volatile unsigned int*) TMDS_SCR1_reg))
#define TMDS_SCR1_inst_adr                                                           "0x0010"
#define TMDS_SCR1_inst                                                               0x0010
#define TMDS_SCR1_REG_LDO_PLL_VSEL_shift                                             (26)
#define TMDS_SCR1_REG_LDO_PLL_VSEL_mask                                              (0x1C000000)
#define TMDS_SCR1_REG_LDO_PLL_VSEL(data)                                             (0x1C000000&((data)<<26))
#define TMDS_SCR1_REG_LDO_PLL_VSEL_src(data)                                         ((0x1C000000&(data))>>26)
#define TMDS_SCR1_get_REG_LDO_PLL_VSEL(data)                                         ((0x1C000000&(data))>>26)
#define TMDS_SCR1_REG_LDO_CCO_VSEL_shift                                             (24)
#define TMDS_SCR1_REG_LDO_CCO_VSEL_mask                                              (0x03000000)
#define TMDS_SCR1_REG_LDO_CCO_VSEL(data)                                             (0x03000000&((data)<<24))
#define TMDS_SCR1_REG_LDO_CCO_VSEL_src(data)                                         ((0x03000000&(data))>>24)
#define TMDS_SCR1_get_REG_LDO_CCO_VSEL(data)                                         ((0x03000000&(data))>>24)
#define TMDS_SCR1_REG_TX_CK5XP_DUTY_shift                                            (22)
#define TMDS_SCR1_REG_TX_CK5XP_DUTY_mask                                             (0x00C00000)
#define TMDS_SCR1_REG_TX_CK5XP_DUTY(data)                                            (0x00C00000&((data)<<22))
#define TMDS_SCR1_REG_TX_CK5XP_DUTY_src(data)                                        ((0x00C00000&(data))>>22)
#define TMDS_SCR1_get_REG_TX_CK5XP_DUTY(data)                                        ((0x00C00000&(data))>>22)
#define TMDS_SCR1_REG_TX_CK5XN_DUTY_shift                                            (20)
#define TMDS_SCR1_REG_TX_CK5XN_DUTY_mask                                             (0x00300000)
#define TMDS_SCR1_REG_TX_CK5XN_DUTY(data)                                            (0x00300000&((data)<<20))
#define TMDS_SCR1_REG_TX_CK5XN_DUTY_src(data)                                        ((0x00300000&(data))>>20)
#define TMDS_SCR1_get_REG_TX_CK5XN_DUTY(data)                                        ((0x00300000&(data))>>20)
#define TMDS_SCR1_REG_TX_AMP_shift                                                   (16)
#define TMDS_SCR1_REG_TX_AMP_mask                                                    (0x000F0000)
#define TMDS_SCR1_REG_TX_AMP(data)                                                   (0x000F0000&((data)<<16))
#define TMDS_SCR1_REG_TX_AMP_src(data)                                               ((0x000F0000&(data))>>16)
#define TMDS_SCR1_get_REG_TX_AMP(data)                                               ((0x000F0000&(data))>>16)
#define TMDS_SCR1_REG_TX_IBIAS_shift                                                 (14)
#define TMDS_SCR1_REG_TX_IBIAS_mask                                                  (0x0000C000)
#define TMDS_SCR1_REG_TX_IBIAS(data)                                                 (0x0000C000&((data)<<14))
#define TMDS_SCR1_REG_TX_IBIAS_src(data)                                             ((0x0000C000&(data))>>14)
#define TMDS_SCR1_get_REG_TX_IBIAS(data)                                             ((0x0000C000&(data))>>14)
#define TMDS_SCR1_REG_TX_EMPH_shift                                                  (11)
#define TMDS_SCR1_REG_TX_EMPH_mask                                                   (0x00003800)
#define TMDS_SCR1_REG_TX_EMPH(data)                                                  (0x00003800&((data)<<11))
#define TMDS_SCR1_REG_TX_EMPH_src(data)                                              ((0x00003800&(data))>>11)
#define TMDS_SCR1_get_REG_TX_EMPH(data)                                              ((0x00003800&(data))>>11)
#define TMDS_SCR1_REG_TX_EN_EMPH_shift                                               (10)
#define TMDS_SCR1_REG_TX_EN_EMPH_mask                                                (0x00000400)
#define TMDS_SCR1_REG_TX_EN_EMPH(data)                                               (0x00000400&((data)<<10))
#define TMDS_SCR1_REG_TX_EN_EMPH_src(data)                                           ((0x00000400&(data))>>10)
#define TMDS_SCR1_get_REG_TX_EN_EMPH(data)                                           ((0x00000400&(data))>>10)
#define TMDS_SCR1_REG_TX_FORCE_VC_shift                                              (9)
#define TMDS_SCR1_REG_TX_FORCE_VC_mask                                               (0x00000200)
#define TMDS_SCR1_REG_TX_FORCE_VC(data)                                              (0x00000200&((data)<<9))
#define TMDS_SCR1_REG_TX_FORCE_VC_src(data)                                          ((0x00000200&(data))>>9)
#define TMDS_SCR1_get_REG_TX_FORCE_VC(data)                                          ((0x00000200&(data))>>9)
#define TMDS_SCR1_REG_TX_SET_VC_shift                                                (7)
#define TMDS_SCR1_REG_TX_SET_VC_mask                                                 (0x00000180)
#define TMDS_SCR1_REG_TX_SET_VC(data)                                                (0x00000180&((data)<<7))
#define TMDS_SCR1_REG_TX_SET_VC_src(data)                                            ((0x00000180&(data))>>7)
#define TMDS_SCR1_get_REG_TX_SET_VC(data)                                            ((0x00000180&(data))>>7)
#define TMDS_SCR1_REG_TX_PLL_EDGE_shift                                              (6)
#define TMDS_SCR1_REG_TX_PLL_EDGE_mask                                               (0x00000040)
#define TMDS_SCR1_REG_TX_PLL_EDGE(data)                                              (0x00000040&((data)<<6))
#define TMDS_SCR1_REG_TX_PLL_EDGE_src(data)                                          ((0x00000040&(data))>>6)
#define TMDS_SCR1_get_REG_TX_PLL_EDGE(data)                                          ((0x00000040&(data))>>6)
#define TMDS_SCR1_REG_TX_PLL_ICP_shift                                               (3)
#define TMDS_SCR1_REG_TX_PLL_ICP_mask                                                (0x00000038)
#define TMDS_SCR1_REG_TX_PLL_ICP(data)                                               (0x00000038&((data)<<3))
#define TMDS_SCR1_REG_TX_PLL_ICP_src(data)                                           ((0x00000038&(data))>>3)
#define TMDS_SCR1_get_REG_TX_PLL_ICP(data)                                           ((0x00000038&(data))>>3)
#define TMDS_SCR1_REG_TX_PLL_RS_shift                                                (0)
#define TMDS_SCR1_REG_TX_PLL_RS_mask                                                 (0x00000007)
#define TMDS_SCR1_REG_TX_PLL_RS(data)                                                (0x00000007&((data)<<0))
#define TMDS_SCR1_REG_TX_PLL_RS_src(data)                                            ((0x00000007&(data))>>0)
#define TMDS_SCR1_get_REG_TX_PLL_RS(data)                                            ((0x00000007&(data))>>0)


#define TMDS_SCR2                                                                    0x044
#define TMDS_SCR2_reg_addr                                                           "0x9800D044"
#define TMDS_SCR2_reg                                                                0x9800D044
#define set_TMDS_SCR2_reg(data)   (*((volatile unsigned int*) TMDS_SCR2_reg)=data)
#define get_TMDS_SCR2_reg   (*((volatile unsigned int*) TMDS_SCR2_reg))
#define TMDS_SCR2_inst_adr                                                           "0x0011"
#define TMDS_SCR2_inst                                                               0x0011
#define TMDS_SCR2_REG_TX_V1P05_SEL_shift                                             (30)
#define TMDS_SCR2_REG_TX_V1P05_SEL_mask                                              (0xC0000000)
#define TMDS_SCR2_REG_TX_V1P05_SEL(data)                                             (0xC0000000&((data)<<30))
#define TMDS_SCR2_REG_TX_V1P05_SEL_src(data)                                         ((0xC0000000&(data))>>30)
#define TMDS_SCR2_get_REG_TX_V1P05_SEL(data)                                         ((0xC0000000&(data))>>30)
#define TMDS_SCR2_REG_TX_PDRV_ISEL_shift                                             (28)
#define TMDS_SCR2_REG_TX_PDRV_ISEL_mask                                              (0x30000000)
#define TMDS_SCR2_REG_TX_PDRV_ISEL(data)                                             (0x30000000&((data)<<28))
#define TMDS_SCR2_REG_TX_PDRV_ISEL_src(data)                                         ((0x30000000&(data))>>28)
#define TMDS_SCR2_get_REG_TX_PDRV_ISEL(data)                                         ((0x30000000&(data))>>28)
#define TMDS_SCR2_REG_TX_PLL_KVCO_shift                                              (27)
#define TMDS_SCR2_REG_TX_PLL_KVCO_mask                                               (0x08000000)
#define TMDS_SCR2_REG_TX_PLL_KVCO(data)                                              (0x08000000&((data)<<27))
#define TMDS_SCR2_REG_TX_PLL_KVCO_src(data)                                          ((0x08000000&(data))>>27)
#define TMDS_SCR2_get_REG_TX_PLL_KVCO(data)                                          ((0x08000000&(data))>>27)
#define TMDS_SCR2_REG_TX_PLL_CS_shift                                                (25)
#define TMDS_SCR2_REG_TX_PLL_CS_mask                                                 (0x06000000)
#define TMDS_SCR2_REG_TX_PLL_CS(data)                                                (0x06000000&((data)<<25))
#define TMDS_SCR2_REG_TX_PLL_CS_src(data)                                            ((0x06000000&(data))>>25)
#define TMDS_SCR2_get_REG_TX_PLL_CS(data)                                            ((0x06000000&(data))>>25)
#define TMDS_SCR2_REG_TX_PLL_CP_shift                                                (23)
#define TMDS_SCR2_REG_TX_PLL_CP_mask                                                 (0x01800000)
#define TMDS_SCR2_REG_TX_PLL_CP(data)                                                (0x01800000&((data)<<23))
#define TMDS_SCR2_REG_TX_PLL_CP_src(data)                                            ((0x01800000&(data))>>23)
#define TMDS_SCR2_get_REG_TX_PLL_CP(data)                                            ((0x01800000&(data))>>23)
#define TMDS_SCR2_REG_TX_PLL_PU_shift                                                (22)
#define TMDS_SCR2_REG_TX_PLL_PU_mask                                                 (0x00400000)
#define TMDS_SCR2_REG_TX_PLL_PU(data)                                                (0x00400000&((data)<<22))
#define TMDS_SCR2_REG_TX_PLL_PU_src(data)                                            ((0x00400000&(data))>>22)
#define TMDS_SCR2_get_REG_TX_PLL_PU(data)                                            ((0x00400000&(data))>>22)
#define TMDS_SCR2_REG_TX_PU_shift                                                    (18)
#define TMDS_SCR2_REG_TX_PU_mask                                                     (0x003C0000)
#define TMDS_SCR2_REG_TX_PU(data)                                                    (0x003C0000&((data)<<18))
#define TMDS_SCR2_REG_TX_PU_src(data)                                                ((0x003C0000&(data))>>18)
#define TMDS_SCR2_get_REG_TX_PU(data)                                                ((0x003C0000&(data))>>18)
#define TMDS_SCR2_REG_TX_DRIVER_shift                                                (16)
#define TMDS_SCR2_REG_TX_DRIVER_mask                                                 (0x00030000)
#define TMDS_SCR2_REG_TX_DRIVER(data)                                                (0x00030000&((data)<<16))
#define TMDS_SCR2_REG_TX_DRIVER_src(data)                                            ((0x00030000&(data))>>16)
#define TMDS_SCR2_get_REG_TX_DRIVER(data)                                            ((0x00030000&(data))>>16)
#define TMDS_SCR2_REG_TX_SLEW_shift                                                  (14)
#define TMDS_SCR2_REG_TX_SLEW_mask                                                   (0x0000C000)
#define TMDS_SCR2_REG_TX_SLEW(data)                                                  (0x0000C000&((data)<<14))
#define TMDS_SCR2_REG_TX_SLEW_src(data)                                              ((0x0000C000&(data))>>14)
#define TMDS_SCR2_get_REG_TX_SLEW(data)                                              ((0x0000C000&(data))>>14)
#define TMDS_SCR2_REG_TX_TST_EN_shift                                                (13)
#define TMDS_SCR2_REG_TX_TST_EN_mask                                                 (0x00002000)
#define TMDS_SCR2_REG_TX_TST_EN(data)                                                (0x00002000&((data)<<13))
#define TMDS_SCR2_REG_TX_TST_EN_src(data)                                            ((0x00002000&(data))>>13)
#define TMDS_SCR2_get_REG_TX_TST_EN(data)                                            ((0x00002000&(data))>>13)
#define TMDS_SCR2_REG_TX_VGATE_shift                                                 (10)
#define TMDS_SCR2_REG_TX_VGATE_mask                                                  (0x00001C00)
#define TMDS_SCR2_REG_TX_VGATE(data)                                                 (0x00001C00&((data)<<10))
#define TMDS_SCR2_REG_TX_VGATE_src(data)                                             ((0x00001C00&(data))>>10)
#define TMDS_SCR2_get_REG_TX_VGATE(data)                                             ((0x00001C00&(data))>>10)
#define TMDS_SCR2_REG_PLL_TST_EN_shift                                               (9)
#define TMDS_SCR2_REG_PLL_TST_EN_mask                                                (0x00000200)
#define TMDS_SCR2_REG_PLL_TST_EN(data)                                               (0x00000200&((data)<<9))
#define TMDS_SCR2_REG_PLL_TST_EN_src(data)                                           ((0x00000200&(data))>>9)
#define TMDS_SCR2_get_REG_PLL_TST_EN(data)                                           ((0x00000200&(data))>>9)
#define TMDS_SCR2_REG_TST_SEL_shift                                                  (7)
#define TMDS_SCR2_REG_TST_SEL_mask                                                   (0x00000180)
#define TMDS_SCR2_REG_TST_SEL(data)                                                  (0x00000180&((data)<<7))
#define TMDS_SCR2_REG_TST_SEL_src(data)                                              ((0x00000180&(data))>>7)
#define TMDS_SCR2_get_REG_TST_SEL(data)                                              ((0x00000180&(data))>>7)
#define TMDS_SCR2_REG_TX_BYPASS_PLL_shift                                            (6)
#define TMDS_SCR2_REG_TX_BYPASS_PLL_mask                                             (0x00000040)
#define TMDS_SCR2_REG_TX_BYPASS_PLL(data)                                            (0x00000040&((data)<<6))
#define TMDS_SCR2_REG_TX_BYPASS_PLL_src(data)                                        ((0x00000040&(data))>>6)
#define TMDS_SCR2_get_REG_TX_BYPASS_PLL(data)                                        ((0x00000040&(data))>>6)
#define TMDS_SCR2_REG_TX_RT_EN_shift                                                 (5)
#define TMDS_SCR2_REG_TX_RT_EN_mask                                                  (0x00000020)
#define TMDS_SCR2_REG_TX_RT_EN(data)                                                 (0x00000020&((data)<<5))
#define TMDS_SCR2_REG_TX_RT_EN_src(data)                                             ((0x00000020&(data))>>5)
#define TMDS_SCR2_get_REG_TX_RT_EN(data)                                             ((0x00000020&(data))>>5)
#define TMDS_SCR2_REG_TX_RT_SEL_shift                                                (3)
#define TMDS_SCR2_REG_TX_RT_SEL_mask                                                 (0x00000018)
#define TMDS_SCR2_REG_TX_RT_SEL(data)                                                (0x00000018&((data)<<3))
#define TMDS_SCR2_REG_TX_RT_SEL_src(data)                                            ((0x00000018&(data))>>3)
#define TMDS_SCR2_get_REG_TX_RT_SEL(data)                                            ((0x00000018&(data))>>3)
#define TMDS_SCR2_REG_PLL_VCO_SCALE_shift                                            (1)
#define TMDS_SCR2_REG_PLL_VCO_SCALE_mask                                             (0x00000006)
#define TMDS_SCR2_REG_PLL_VCO_SCALE(data)                                            (0x00000006&((data)<<1))
#define TMDS_SCR2_REG_PLL_VCO_SCALE_src(data)                                        ((0x00000006&(data))>>1)
#define TMDS_SCR2_get_REG_PLL_VCO_SCALE(data)                                        ((0x00000006&(data))>>1)
#define TMDS_SCR2_REG_BYPASS_DIN_shift                                               (0)
#define TMDS_SCR2_REG_BYPASS_DIN_mask                                                (0x00000001)
#define TMDS_SCR2_REG_BYPASS_DIN(data)                                               (0x00000001&((data)<<0))
#define TMDS_SCR2_REG_BYPASS_DIN_src(data)                                           ((0x00000001&(data))>>0)
#define TMDS_SCR2_get_REG_BYPASS_DIN(data)                                           ((0x00000001&(data))>>0)


#define TMDS_SCR3                                                                    0x9800D230
#define TMDS_SCR3_reg_addr                                                           "0x9800D230"
#define TMDS_SCR3_reg                                                                0x9800D230
#define set_TMDS_SCR3_reg(data)   (*((volatile unsigned int*) TMDS_SCR3_reg)=data)
#define get_TMDS_SCR3_reg   (*((volatile unsigned int*) TMDS_SCR3_reg))
#define TMDS_SCR3_inst_adr                                                           "0x008C"
#define TMDS_SCR3_inst                                                               0x008C
#define TMDS_SCR3_REG_TX_PLL_WDMODE_shift                                            (30)
#define TMDS_SCR3_REG_TX_PLL_WDMODE_mask                                             (0xC0000000)
#define TMDS_SCR3_REG_TX_PLL_WDMODE(data)                                            (0xC0000000&((data)<<30))
#define TMDS_SCR3_REG_TX_PLL_WDMODE_src(data)                                        ((0xC0000000&(data))>>30)
#define TMDS_SCR3_get_REG_TX_PLL_WDMODE(data)                                        ((0xC0000000&(data))>>30)
#define TMDS_SCR3_REG_RESERVE_shift                                                  (14)
#define TMDS_SCR3_REG_RESERVE_mask                                                   (0x3FFFC000)
#define TMDS_SCR3_REG_RESERVE(data)                                                  (0x3FFFC000&((data)<<14))
#define TMDS_SCR3_REG_RESERVE_src(data)                                              ((0x3FFFC000&(data))>>14)
#define TMDS_SCR3_get_REG_RESERVE(data)                                              ((0x3FFFC000&(data))>>14)
#define TMDS_SCR3_REG_CEC_ENB_shift                                                  (13)
#define TMDS_SCR3_REG_CEC_ENB_mask                                                   (0x00002000)
#define TMDS_SCR3_REG_CEC_ENB(data)                                                  (0x00002000&((data)<<13))
#define TMDS_SCR3_REG_CEC_ENB_src(data)                                              ((0x00002000&(data))>>13)
#define TMDS_SCR3_get_REG_CEC_ENB(data)                                              ((0x00002000&(data))>>13)
#define TMDS_SCR3_REG_EN_MHL_shift                                                   (12)
#define TMDS_SCR3_REG_EN_MHL_mask                                                    (0x00001000)
#define TMDS_SCR3_REG_EN_MHL(data)                                                   (0x00001000&((data)<<12))
#define TMDS_SCR3_REG_EN_MHL_src(data)                                               ((0x00001000&(data))>>12)
#define TMDS_SCR3_get_REG_EN_MHL(data)                                               ((0x00001000&(data))>>12)
#define TMDS_SCR3_REG_FORCE_RXSENSE_shift                                            (11)
#define TMDS_SCR3_REG_FORCE_RXSENSE_mask                                             (0x00000800)
#define TMDS_SCR3_REG_FORCE_RXSENSE(data)                                            (0x00000800&((data)<<11))
#define TMDS_SCR3_REG_FORCE_RXSENSE_src(data)                                        ((0x00000800&(data))>>11)
#define TMDS_SCR3_get_REG_FORCE_RXSENSE(data)                                        ((0x00000800&(data))>>11)
#define TMDS_SCR3_REG_RXSENSE_shift                                                  (9)
#define TMDS_SCR3_REG_RXSENSE_mask                                                   (0x00000600)
#define TMDS_SCR3_REG_RXSENSE(data)                                                  (0x00000600&((data)<<9))
#define TMDS_SCR3_REG_RXSENSE_src(data)                                              ((0x00000600&(data))>>9)
#define TMDS_SCR3_get_REG_RXSENSE(data)                                              ((0x00000600&(data))>>9)
#define TMDS_SCR3_REG_MHL_DIV_shift                                                  (8)
#define TMDS_SCR3_REG_MHL_DIV_mask                                                   (0x00000100)
#define TMDS_SCR3_REG_MHL_DIV(data)                                                  (0x00000100&((data)<<8))
#define TMDS_SCR3_REG_MHL_DIV_src(data)                                              ((0x00000100&(data))>>8)
#define TMDS_SCR3_get_REG_MHL_DIV(data)                                              ((0x00000100&(data))>>8)
#define TMDS_SCR3_REG_MHL_VCM_shift                                                  (6)
#define TMDS_SCR3_REG_MHL_VCM_mask                                                   (0x000000C0)
#define TMDS_SCR3_REG_MHL_VCM(data)                                                  (0x000000C0&((data)<<6))
#define TMDS_SCR3_REG_MHL_VCM_src(data)                                              ((0x000000C0&(data))>>6)
#define TMDS_SCR3_get_REG_MHL_VCM(data)                                              ((0x000000C0&(data))>>6)
#define TMDS_SCR3_REG_DIFF_RT_EN_shift                                               (5)
#define TMDS_SCR3_REG_DIFF_RT_EN_mask                                                (0x00000020)
#define TMDS_SCR3_REG_DIFF_RT_EN(data)                                               (0x00000020&((data)<<5))
#define TMDS_SCR3_REG_DIFF_RT_EN_src(data)                                           ((0x00000020&(data))>>5)
#define TMDS_SCR3_get_REG_DIFF_RT_EN(data)                                           ((0x00000020&(data))>>5)
#define TMDS_SCR3_REG_CABLE_DET_EN_shift                                             (4)
#define TMDS_SCR3_REG_CABLE_DET_EN_mask                                              (0x00000010)
#define TMDS_SCR3_REG_CABLE_DET_EN(data)                                             (0x00000010&((data)<<4))
#define TMDS_SCR3_REG_CABLE_DET_EN_src(data)                                         ((0x00000010&(data))>>4)
#define TMDS_SCR3_get_REG_CABLE_DET_EN(data)                                         ((0x00000010&(data))>>4)
#define TMDS_SCR3_REG_LDO_TMDS_VSEL20_shift                                          (1)
#define TMDS_SCR3_REG_LDO_TMDS_VSEL20_mask                                           (0x0000000E)
#define TMDS_SCR3_REG_LDO_TMDS_VSEL20(data)                                          (0x0000000E&((data)<<1))
#define TMDS_SCR3_REG_LDO_TMDS_VSEL20_src(data)                                      ((0x0000000E&(data))>>1)
#define TMDS_SCR3_get_REG_LDO_TMDS_VSEL20(data)                                      ((0x0000000E&(data))>>1)
#define TMDS_SCR3_REG_LDO_TMDS_CAPSEL_shift                                          (0)
#define TMDS_SCR3_REG_LDO_TMDS_CAPSEL_mask                                           (0x00000001)
#define TMDS_SCR3_REG_LDO_TMDS_CAPSEL(data)                                          (0x00000001&((data)<<0))
#define TMDS_SCR3_REG_LDO_TMDS_CAPSEL_src(data)                                      ((0x00000001&(data))>>0)
#define TMDS_SCR3_get_REG_LDO_TMDS_CAPSEL(data)                                      ((0x00000001&(data))>>0)


#define TVPLL_CTRL2                                                                  0x9800D2A4
#define TVPLL_CTRL2_reg_addr                                                         "0x9800D2A4"
#define TVPLL_CTRL2_reg                                                              0x9800D2A4
#define set_TVPLL_CTRL2_reg(data)   (*((volatile unsigned int*) TVPLL_CTRL2_reg)=data)
#define get_TVPLL_CTRL2_reg   (*((volatile unsigned int*) TVPLL_CTRL2_reg))
#define TVPLL_CTRL2_inst_adr                                                         "0x00A9"
#define TVPLL_CTRL2_inst                                                             0x00A9
#define TVPLL_CTRL2_REG_TV_WDMODE_shift                                              (16)
#define TVPLL_CTRL2_REG_TV_WDMODE_mask                                               (0x00030000)
#define TVPLL_CTRL2_REG_TV_WDMODE(data)                                              (0x00030000&((data)<<16))
#define TVPLL_CTRL2_REG_TV_WDMODE_src(data)                                          ((0x00030000&(data))>>16)
#define TVPLL_CTRL2_get_REG_TV_WDMODE(data)                                          ((0x00030000&(data))>>16)
#define TVPLL_CTRL2_REG_TV_KVCO_shift                                                (15)
#define TVPLL_CTRL2_REG_TV_KVCO_mask                                                 (0x00008000)
#define TVPLL_CTRL2_REG_TV_KVCO(data)                                                (0x00008000&((data)<<15))
#define TVPLL_CTRL2_REG_TV_KVCO_src(data)                                            ((0x00008000&(data))>>15)
#define TVPLL_CTRL2_get_REG_TV_KVCO(data)                                            ((0x00008000&(data))>>15)
#define TVPLL_CTRL2_REG_TV_CS_shift                                                  (13)
#define TVPLL_CTRL2_REG_TV_CS_mask                                                   (0x00006000)
#define TVPLL_CTRL2_REG_TV_CS(data)                                                  (0x00006000&((data)<<13))
#define TVPLL_CTRL2_REG_TV_CS_src(data)                                              ((0x00006000&(data))>>13)
#define TVPLL_CTRL2_get_REG_TV_CS(data)                                              ((0x00006000&(data))>>13)
#define TVPLL_CTRL2_REG_TV_CP_shift                                                  (11)
#define TVPLL_CTRL2_REG_TV_CP_mask                                                   (0x00001800)
#define TVPLL_CTRL2_REG_TV_CP(data)                                                  (0x00001800&((data)<<11))
#define TVPLL_CTRL2_REG_TV_CP_src(data)                                              ((0x00001800&(data))>>11)
#define TVPLL_CTRL2_get_REG_TV_CP(data)                                              ((0x00001800&(data))>>11)
#define TVPLL_CTRL2_REG_TV_ICP_shift                                                 (8)
#define TVPLL_CTRL2_REG_TV_ICP_mask                                                  (0x00000700)
#define TVPLL_CTRL2_REG_TV_ICP(data)                                                 (0x00000700&((data)<<8))
#define TVPLL_CTRL2_REG_TV_ICP_src(data)                                             ((0x00000700&(data))>>8)
#define TVPLL_CTRL2_get_REG_TV_ICP(data)                                             ((0x00000700&(data))>>8)
#define TVPLL_CTRL2_REG_TV_RS_shift                                                  (5)
#define TVPLL_CTRL2_REG_TV_RS_mask                                                   (0x000000E0)
#define TVPLL_CTRL2_REG_TV_RS(data)                                                  (0x000000E0&((data)<<5))
#define TVPLL_CTRL2_REG_TV_RS_src(data)                                              ((0x000000E0&(data))>>5)
#define TVPLL_CTRL2_get_REG_TV_RS(data)                                              ((0x000000E0&(data))>>5)
#define TVPLL_CTRL2_REG_TV_BYPASS_PLL_shift                                          (4)
#define TVPLL_CTRL2_REG_TV_BYPASS_PLL_mask                                           (0x00000010)
#define TVPLL_CTRL2_REG_TV_BYPASS_PLL(data)                                          (0x00000010&((data)<<4))
#define TVPLL_CTRL2_REG_TV_BYPASS_PLL_src(data)                                      ((0x00000010&(data))>>4)
#define TVPLL_CTRL2_get_REG_TV_BYPASS_PLL(data)                                      ((0x00000010&(data))>>4)
#define TVPLL_CTRL2_REG_TV_FORCE_VC_shift                                            (3)
#define TVPLL_CTRL2_REG_TV_FORCE_VC_mask                                             (0x00000008)
#define TVPLL_CTRL2_REG_TV_FORCE_VC(data)                                            (0x00000008&((data)<<3))
#define TVPLL_CTRL2_REG_TV_FORCE_VC_src(data)                                        ((0x00000008&(data))>>3)
#define TVPLL_CTRL2_get_REG_TV_FORCE_VC(data)                                        ((0x00000008&(data))>>3)
#define TVPLL_CTRL2_REG_TV_SET_VC_shift                                              (1)
#define TVPLL_CTRL2_REG_TV_SET_VC_mask                                               (0x00000006)
#define TVPLL_CTRL2_REG_TV_SET_VC(data)                                              (0x00000006&((data)<<1))
#define TVPLL_CTRL2_REG_TV_SET_VC_src(data)                                          ((0x00000006&(data))>>1)
#define TVPLL_CTRL2_get_REG_TV_SET_VC(data)                                          ((0x00000006&(data))>>1)
#define TVPLL_CTRL2_REG_TV_TST_EN_shift                                              (0)
#define TVPLL_CTRL2_REG_TV_TST_EN_mask                                               (0x00000001)
#define TVPLL_CTRL2_REG_TV_TST_EN(data)                                              (0x00000001&((data)<<0))
#define TVPLL_CTRL2_REG_TV_TST_EN_src(data)                                          ((0x00000001&(data))>>0)
#define TVPLL_CTRL2_get_REG_TV_TST_EN(data)                                          ((0x00000001&(data))>>0)


#define MHL_CBUS                                                                     0x9800D2AC
#define MHL_CBUS_reg_addr                                                            "0x9800D2AC"
#define MHL_CBUS_reg                                                                 0x9800D2AC
#define set_MHL_CBUS_reg(data)   (*((volatile unsigned int*) MHL_CBUS_reg)=data)
#define get_MHL_CBUS_reg   (*((volatile unsigned int*) MHL_CBUS_reg))
#define MHL_CBUS_inst_adr                                                            "0x00AB"
#define MHL_CBUS_inst                                                                0x00AB
#define MHL_CBUS_REGO_TV_WDOUT_shift                                                 (11)
#define MHL_CBUS_REGO_TV_WDOUT_mask                                                  (0x00000800)
#define MHL_CBUS_REGO_TV_WDOUT(data)                                                 (0x00000800&((data)<<11))
#define MHL_CBUS_REGO_TV_WDOUT_src(data)                                             ((0x00000800&(data))>>11)
#define MHL_CBUS_get_REGO_TV_WDOUT(data)                                             ((0x00000800&(data))>>11)
#define MHL_CBUS_REGO_TX_PLL_WDOUT_shift                                             (10)
#define MHL_CBUS_REGO_TX_PLL_WDOUT_mask                                              (0x00000400)
#define MHL_CBUS_REGO_TX_PLL_WDOUT(data)                                             (0x00000400&((data)<<10))
#define MHL_CBUS_REGO_TX_PLL_WDOUT_src(data)                                         ((0x00000400&(data))>>10)
#define MHL_CBUS_get_REGO_TX_PLL_WDOUT(data)                                         ((0x00000400&(data))>>10)
#define MHL_CBUS_REGO_TX_PLL_LOCK_shift                                              (9)
#define MHL_CBUS_REGO_TX_PLL_LOCK_mask                                               (0x00000200)
#define MHL_CBUS_REGO_TX_PLL_LOCK(data)                                              (0x00000200&((data)<<9))
#define MHL_CBUS_REGO_TX_PLL_LOCK_src(data)                                          ((0x00000200&(data))>>9)
#define MHL_CBUS_get_REGO_TX_PLL_LOCK(data)                                          ((0x00000200&(data))>>9)
#define MHL_CBUS_REGO_CABLE_DETECT_shift                                             (1)
#define MHL_CBUS_REGO_CABLE_DETECT_mask                                              (0x000001FE)
#define MHL_CBUS_REGO_CABLE_DETECT(data)                                             (0x000001FE&((data)<<1))
#define MHL_CBUS_REGO_CABLE_DETECT_src(data)                                         ((0x000001FE&(data))>>1)
#define MHL_CBUS_get_REGO_CABLE_DETECT(data)                                         ((0x000001FE&(data))>>1)
#define MHL_CBUS_REGO_TV_PLL_LOCK_shift                                              (0)
#define MHL_CBUS_REGO_TV_PLL_LOCK_mask                                               (0x00000001)
#define MHL_CBUS_REGO_TV_PLL_LOCK(data)                                              (0x00000001&((data)<<0))
#define MHL_CBUS_REGO_TV_PLL_LOCK_src(data)                                          ((0x00000001&(data))>>0)
#define MHL_CBUS_get_REGO_TV_PLL_LOCK(data)                                          ((0x00000001&(data))>>0)


#define TMDS_STR0                                                                    0x9800D048
#define TMDS_STR0_reg_addr                                                           "0x9800D048"
#define TMDS_STR0_reg                                                                0x9800D048
#define set_TMDS_STR0_reg(data)   (*((volatile unsigned int*) TMDS_STR0_reg)=data)
#define get_TMDS_STR0_reg   (*((volatile unsigned int*) TMDS_STR0_reg))
#define TMDS_STR0_inst_adr                                                           "0x0012"
#define TMDS_STR0_inst                                                               0x0012
#define TMDS_STR0_tmds1ten_shift                                                     (31)
#define TMDS_STR0_tmds1ten_mask                                                      (0x80000000)
#define TMDS_STR0_tmds1ten(data)                                                     (0x80000000&((data)<<31))
#define TMDS_STR0_tmds1ten_src(data)                                                 ((0x80000000&(data))>>31)
#define TMDS_STR0_get_tmds1ten(data)                                                 ((0x80000000&(data))>>31)
#define TMDS_STR0_td1src_shift                                                       (30)
#define TMDS_STR0_td1src_mask                                                        (0x40000000)
#define TMDS_STR0_td1src(data)                                                       (0x40000000&((data)<<30))
#define TMDS_STR0_td1src_src(data)                                                   ((0x40000000&(data))>>30)
#define TMDS_STR0_get_td1src(data)                                                   ((0x40000000&(data))>>30)
#define TMDS_STR0_tmds1td_shift                                                      (16)
#define TMDS_STR0_tmds1td_mask                                                       (0x03FF0000)
#define TMDS_STR0_tmds1td(data)                                                      (0x03FF0000&((data)<<16))
#define TMDS_STR0_tmds1td_src(data)                                                  ((0x03FF0000&(data))>>16)
#define TMDS_STR0_get_tmds1td(data)                                                  ((0x03FF0000&(data))>>16)
#define TMDS_STR0_tmds0ten_shift                                                     (15)
#define TMDS_STR0_tmds0ten_mask                                                      (0x00008000)
#define TMDS_STR0_tmds0ten(data)                                                     (0x00008000&((data)<<15))
#define TMDS_STR0_tmds0ten_src(data)                                                 ((0x00008000&(data))>>15)
#define TMDS_STR0_get_tmds0ten(data)                                                 ((0x00008000&(data))>>15)
#define TMDS_STR0_td0src_shift                                                       (14)
#define TMDS_STR0_td0src_mask                                                        (0x00004000)
#define TMDS_STR0_td0src(data)                                                       (0x00004000&((data)<<14))
#define TMDS_STR0_td0src_src(data)                                                   ((0x00004000&(data))>>14)
#define TMDS_STR0_get_td0src(data)                                                   ((0x00004000&(data))>>14)
#define TMDS_STR0_tmds0td_shift                                                      (0)
#define TMDS_STR0_tmds0td_mask                                                       (0x000003FF)
#define TMDS_STR0_tmds0td(data)                                                      (0x000003FF&((data)<<0))
#define TMDS_STR0_tmds0td_src(data)                                                  ((0x000003FF&(data))>>0)
#define TMDS_STR0_get_tmds0td(data)                                                  ((0x000003FF&(data))>>0)


#define TMDS_STR1                                                                    0x9800D04c
#define TMDS_STR1_reg_addr                                                           "0x9800D04C"
#define TMDS_STR1_reg                                                                0x9800D04C
#define set_TMDS_STR1_reg(data)   (*((volatile unsigned int*) TMDS_STR1_reg)=data)
#define get_TMDS_STR1_reg   (*((volatile unsigned int*) TMDS_STR1_reg))
#define TMDS_STR1_inst_adr                                                           "0x0013"
#define TMDS_STR1_inst                                                               0x0013
#define TMDS_STR1_tmdscten_shift                                                     (31)
#define TMDS_STR1_tmdscten_mask                                                      (0x80000000)
#define TMDS_STR1_tmdscten(data)                                                     (0x80000000&((data)<<31))
#define TMDS_STR1_tmdscten_src(data)                                                 ((0x80000000&(data))>>31)
#define TMDS_STR1_get_tmdscten(data)                                                 ((0x80000000&(data))>>31)
#define TMDS_STR1_tdcsrc_shift                                                       (30)
#define TMDS_STR1_tdcsrc_mask                                                        (0x40000000)
#define TMDS_STR1_tdcsrc(data)                                                       (0x40000000&((data)<<30))
#define TMDS_STR1_tdcsrc_src(data)                                                   ((0x40000000&(data))>>30)
#define TMDS_STR1_get_tdcsrc(data)                                                   ((0x40000000&(data))>>30)
#define TMDS_STR1_tmdsctd_shift                                                      (16)
#define TMDS_STR1_tmdsctd_mask                                                       (0x03FF0000)
#define TMDS_STR1_tmdsctd(data)                                                      (0x03FF0000&((data)<<16))
#define TMDS_STR1_tmdsctd_src(data)                                                  ((0x03FF0000&(data))>>16)
#define TMDS_STR1_get_tmdsctd(data)                                                  ((0x03FF0000&(data))>>16)
#define TMDS_STR1_tmds2ten_shift                                                     (15)
#define TMDS_STR1_tmds2ten_mask                                                      (0x00008000)
#define TMDS_STR1_tmds2ten(data)                                                     (0x00008000&((data)<<15))
#define TMDS_STR1_tmds2ten_src(data)                                                 ((0x00008000&(data))>>15)
#define TMDS_STR1_get_tmds2ten(data)                                                 ((0x00008000&(data))>>15)
#define TMDS_STR1_td2src_shift                                                       (14)
#define TMDS_STR1_td2src_mask                                                        (0x00004000)
#define TMDS_STR1_td2src(data)                                                       (0x00004000&((data)<<14))
#define TMDS_STR1_td2src_src(data)                                                   ((0x00004000&(data))>>14)
#define TMDS_STR1_get_td2src(data)                                                   ((0x00004000&(data))>>14)
#define TMDS_STR1_tmds2td_shift                                                      (0)
#define TMDS_STR1_tmds2td_mask                                                       (0x000003FF)
#define TMDS_STR1_tmds2td(data)                                                      (0x000003FF&((data)<<0))
#define TMDS_STR1_tmds2td_src(data)                                                  ((0x000003FF&(data))>>0)
#define TMDS_STR1_get_tmds2td(data)                                                  ((0x000003FF&(data))>>0)


#define ASPCR1                                                                       0x9800D054
#define ASPCR1_reg_addr                                                              "0x9800D054"
#define ASPCR1_reg                                                                   0x9800D054
#define set_ASPCR1_reg(data)   (*((volatile unsigned int*) ASPCR1_reg)=data)
#define get_ASPCR1_reg   (*((volatile unsigned int*) ASPCR1_reg))
#define ASPCR1_inst_adr                                                              "0x0015"
#define ASPCR1_inst                                                                  0x0015
#define ASPCR1_write_en8_shift                                                       (28)
#define ASPCR1_write_en8_mask                                                        (0x10000000)
#define ASPCR1_write_en8(data)                                                       (0x10000000&((data)<<28))
#define ASPCR1_write_en8_src(data)                                                   ((0x10000000&(data))>>28)
#define ASPCR1_get_write_en8(data)                                                   ((0x10000000&(data))>>28)
#define ASPCR1_ycbcr422_8bits_shift                                                  (27)
#define ASPCR1_ycbcr422_8bits_mask                                                   (0x08000000)
#define ASPCR1_ycbcr422_8bits(data)                                                  (0x08000000&((data)<<27))
#define ASPCR1_ycbcr422_8bits_src(data)                                              ((0x08000000&(data))>>27)
#define ASPCR1_get_ycbcr422_8bits(data)                                              ((0x08000000&(data))>>27)
#define ASPCR1_write_en7_shift                                                       (26)
#define ASPCR1_write_en7_mask                                                        (0x04000000)
#define ASPCR1_write_en7(data)                                                       (0x04000000&((data)<<26))
#define ASPCR1_write_en7_src(data)                                                   ((0x04000000&(data))>>26)
#define ASPCR1_get_write_en7(data)                                                   ((0x04000000&(data))>>26)
#define ASPCR1_cts_pkt_hp_shift                                                      (25)
#define ASPCR1_cts_pkt_hp_mask                                                       (0x02000000)
#define ASPCR1_cts_pkt_hp(data)                                                      (0x02000000&((data)<<25))
#define ASPCR1_cts_pkt_hp_src(data)                                                  ((0x02000000&(data))>>25)
#define ASPCR1_get_cts_pkt_hp(data)                                                  ((0x02000000&(data))>>25)
#define ASPCR1_write_en6_shift                                                       (24)
#define ASPCR1_write_en6_mask                                                        (0x01000000)
#define ASPCR1_write_en6(data)                                                       (0x01000000&((data)<<24))
#define ASPCR1_write_en6_src(data)                                                   ((0x01000000&(data))>>24)
#define ASPCR1_get_write_en6(data)                                                   ((0x01000000&(data))>>24)
#define ASPCR1_Audioheader0_shift                                                    (16)
#define ASPCR1_Audioheader0_mask                                                     (0x00FF0000)
#define ASPCR1_Audioheader0(data)                                                    (0x00FF0000&((data)<<16))
#define ASPCR1_Audioheader0_src(data)                                                ((0x00FF0000&(data))>>16)
#define ASPCR1_get_Audioheader0(data)                                                ((0x00FF0000&(data))>>16)
#define ASPCR1_write_en5_shift                                                       (15)
#define ASPCR1_write_en5_mask                                                        (0x00008000)
#define ASPCR1_write_en5(data)                                                       (0x00008000&((data)<<15))
#define ASPCR1_write_en5_src(data)                                                   ((0x00008000&(data))>>15)
#define ASPCR1_get_write_en5(data)                                                   ((0x00008000&(data))>>15)
#define ASPCR1_samplepresent_shift                                                   (11)
#define ASPCR1_samplepresent_mask                                                    (0x00007800)
#define ASPCR1_samplepresent(data)                                                   (0x00007800&((data)<<11))
#define ASPCR1_samplepresent_src(data)                                               ((0x00007800&(data))>>11)
#define ASPCR1_get_samplepresent(data)                                               ((0x00007800&(data))>>11)
#define ASPCR1_write_en4_shift                                                       (10)
#define ASPCR1_write_en4_mask                                                        (0x00000400)
#define ASPCR1_write_en4(data)                                                       (0x00000400&((data)<<10))
#define ASPCR1_write_en4_src(data)                                                   ((0x00000400&(data))>>10)
#define ASPCR1_get_write_en4(data)                                                   ((0x00000400&(data))>>10)
#define ASPCR1_forcesamplepresent_shift                                              (9)
#define ASPCR1_forcesamplepresent_mask                                               (0x00000200)
#define ASPCR1_forcesamplepresent(data)                                              (0x00000200&((data)<<9))
#define ASPCR1_forcesamplepresent_src(data)                                          ((0x00000200&(data))>>9)
#define ASPCR1_get_forcesamplepresent(data)                                          ((0x00000200&(data))>>9)
#define ASPCR1_write_en3_shift                                                       (8)
#define ASPCR1_write_en3_mask                                                        (0x00000100)
#define ASPCR1_write_en3(data)                                                       (0x00000100&((data)<<8))
#define ASPCR1_write_en3_src(data)                                                   ((0x00000100&(data))>>8)
#define ASPCR1_get_write_en3(data)                                                   ((0x00000100&(data))>>8)
#define ASPCR1_b_frame_shift                                                         (4)
#define ASPCR1_b_frame_mask                                                          (0x000000F0)
#define ASPCR1_b_frame(data)                                                         (0x000000F0&((data)<<4))
#define ASPCR1_b_frame_src(data)                                                     ((0x000000F0&(data))>>4)
#define ASPCR1_get_b_frame(data)                                                     ((0x000000F0&(data))>>4)
#define ASPCR1_write_en2_shift                                                       (3)
#define ASPCR1_write_en2_mask                                                        (0x00000008)
#define ASPCR1_write_en2(data)                                                       (0x00000008&((data)<<3))
#define ASPCR1_write_en2_src(data)                                                   ((0x00000008&(data))>>3)
#define ASPCR1_get_write_en2(data)                                                   ((0x00000008&(data))>>3)
#define ASPCR1_forceb_frame_shift                                                    (2)
#define ASPCR1_forceb_frame_mask                                                     (0x00000004)
#define ASPCR1_forceb_frame(data)                                                    (0x00000004&((data)<<2))
#define ASPCR1_forceb_frame_src(data)                                                ((0x00000004&(data))>>2)
#define ASPCR1_get_forceb_frame(data)                                                ((0x00000004&(data))>>2)
#define ASPCR1_write_en1_shift                                                       (1)
#define ASPCR1_write_en1_mask                                                        (0x00000002)
#define ASPCR1_write_en1(data)                                                       (0x00000002&((data)<<1))
#define ASPCR1_write_en1_src(data)                                                   ((0x00000002&(data))>>1)
#define ASPCR1_get_write_en1(data)                                                   ((0x00000002&(data))>>1)
#define ASPCR1_audiolayout_shift                                                     (0)
#define ASPCR1_audiolayout_mask                                                      (0x00000001)
#define ASPCR1_audiolayout(data)                                                     (0x00000001&((data)<<0))
#define ASPCR1_audiolayout_src(data)                                                 ((0x00000001&(data))>>0)
#define ASPCR1_get_audiolayout(data)                                                 ((0x00000001&(data))>>0)


#define ACACR                                                                        0x9800D058
#define ACACR_reg_addr                                                               "0x9800D058"
#define ACACR_reg                                                                    0x9800D058
#define set_ACACR_reg(data)   (*((volatile unsigned int*) ACACR_reg)=data)
#define get_ACACR_reg   (*((volatile unsigned int*) ACACR_reg))
#define ACACR_inst_adr                                                               "0x0016"
#define ACACR_inst                                                                   0x0016
#define ACACR_write_en4_shift                                                        (15)
#define ACACR_write_en4_mask                                                         (0x00008000)
#define ACACR_write_en4(data)                                                        (0x00008000&((data)<<15))
#define ACACR_write_en4_src(data)                                                    ((0x00008000&(data))>>15)
#define ACACR_get_write_en4(data)                                                    ((0x00008000&(data))>>15)
#define ACACR_hdmi_pk3map_shift                                                      (12)
#define ACACR_hdmi_pk3map_mask                                                       (0x00007000)
#define ACACR_hdmi_pk3map(data)                                                      (0x00007000&((data)<<12))
#define ACACR_hdmi_pk3map_src(data)                                                  ((0x00007000&(data))>>12)
#define ACACR_get_hdmi_pk3map(data)                                                  ((0x00007000&(data))>>12)
#define ACACR_write_en3_shift                                                        (11)
#define ACACR_write_en3_mask                                                         (0x00000800)
#define ACACR_write_en3(data)                                                        (0x00000800&((data)<<11))
#define ACACR_write_en3_src(data)                                                    ((0x00000800&(data))>>11)
#define ACACR_get_write_en3(data)                                                    ((0x00000800&(data))>>11)
#define ACACR_hdmi_pk2map_shift                                                      (8)
#define ACACR_hdmi_pk2map_mask                                                       (0x00000700)
#define ACACR_hdmi_pk2map(data)                                                      (0x00000700&((data)<<8))
#define ACACR_hdmi_pk2map_src(data)                                                  ((0x00000700&(data))>>8)
#define ACACR_get_hdmi_pk2map(data)                                                  ((0x00000700&(data))>>8)
#define ACACR_write_en2_shift                                                        (7)
#define ACACR_write_en2_mask                                                         (0x00000080)
#define ACACR_write_en2(data)                                                        (0x00000080&((data)<<7))
#define ACACR_write_en2_src(data)                                                    ((0x00000080&(data))>>7)
#define ACACR_get_write_en2(data)                                                    ((0x00000080&(data))>>7)
#define ACACR_hdmi_pk1map_shift                                                      (4)
#define ACACR_hdmi_pk1map_mask                                                       (0x00000070)
#define ACACR_hdmi_pk1map(data)                                                      (0x00000070&((data)<<4))
#define ACACR_hdmi_pk1map_src(data)                                                  ((0x00000070&(data))>>4)
#define ACACR_get_hdmi_pk1map(data)                                                  ((0x00000070&(data))>>4)
#define ACACR_write_en1_shift                                                        (3)
#define ACACR_write_en1_mask                                                         (0x00000008)
#define ACACR_write_en1(data)                                                        (0x00000008&((data)<<3))
#define ACACR_write_en1_src(data)                                                    ((0x00000008&(data))>>3)
#define ACACR_get_write_en1(data)                                                    ((0x00000008&(data))>>3)
#define ACACR_hdmi_pk0map_shift                                                      (0)
#define ACACR_hdmi_pk0map_mask                                                       (0x00000007)
#define ACACR_hdmi_pk0map(data)                                                      (0x00000007&((data)<<0))
#define ACACR_hdmi_pk0map_src(data)                                                  ((0x00000007&(data))>>0)
#define ACACR_get_hdmi_pk0map(data)                                                  ((0x00000007&(data))>>0)


#define ACRPCR                                                                       0x9800D06c
#define ACRPCR_reg_addr                                                              "0x9800D06C"
#define ACRPCR_reg                                                                   0x9800D06C
#define set_ACRPCR_reg(data)   (*((volatile unsigned int*) ACRPCR_reg)=data)
#define get_ACRPCR_reg   (*((volatile unsigned int*) ACRPCR_reg))
#define ACRPCR_inst_adr                                                              "0x001B"
#define ACRPCR_inst                                                                  0x001B
#define ACRPCR_write_en6_shift                                                       (30)
#define ACRPCR_write_en6_mask                                                        (0x40000000)
#define ACRPCR_write_en6(data)                                                       (0x40000000&((data)<<30))
#define ACRPCR_write_en6_src(data)                                                   ((0x40000000&(data))>>30)
#define ACRPCR_get_write_en6(data)                                                   ((0x40000000&(data))>>30)
#define ACRPCR_Audio_info_hp_shift                                                   (29)
#define ACRPCR_Audio_info_hp_mask                                                    (0x20000000)
#define ACRPCR_Audio_info_hp(data)                                                   (0x20000000&((data)<<29))
#define ACRPCR_Audio_info_hp_src(data)                                               ((0x20000000&(data))>>29)
#define ACRPCR_get_Audio_info_hp(data)                                               ((0x20000000&(data))>>29)
#define ACRPCR_write_en5_shift                                                       (28)
#define ACRPCR_write_en5_mask                                                        (0x10000000)
#define ACRPCR_write_en5(data)                                                       (0x10000000&((data)<<28))
#define ACRPCR_write_en5_src(data)                                                   ((0x10000000&(data))>>28)
#define ACRPCR_get_write_en5(data)                                                   ((0x10000000&(data))>>28)
#define ACRPCR_ac_hw_ctrl_en_shift                                                   (27)
#define ACRPCR_ac_hw_ctrl_en_mask                                                    (0x08000000)
#define ACRPCR_ac_hw_ctrl_en(data)                                                   (0x08000000&((data)<<27))
#define ACRPCR_ac_hw_ctrl_en_src(data)                                               ((0x08000000&(data))>>27)
#define ACRPCR_get_ac_hw_ctrl_en(data)                                               ((0x08000000&(data))>>27)
#define ACRPCR_write_en4_shift                                                       (26)
#define ACRPCR_write_en4_mask                                                        (0x04000000)
#define ACRPCR_write_en4(data)                                                       (0x04000000&((data)<<26))
#define ACRPCR_write_en4_src(data)                                                   ((0x04000000&(data))>>26)
#define ACRPCR_get_write_en4(data)                                                   ((0x04000000&(data))>>26)
#define ACRPCR_fs_div4_shift                                                         (25)
#define ACRPCR_fs_div4_mask                                                          (0x02000000)
#define ACRPCR_fs_div4(data)                                                         (0x02000000&((data)<<25))
#define ACRPCR_fs_div4_src(data)                                                     ((0x02000000&(data))>>25)
#define ACRPCR_get_fs_div4(data)                                                     ((0x02000000&(data))>>25)
#define ACRPCR_write_en3_shift                                                       (24)
#define ACRPCR_write_en3_mask                                                        (0x01000000)
#define ACRPCR_write_en3(data)                                                       (0x01000000&((data)<<24))
#define ACRPCR_write_en3_src(data)                                                   ((0x01000000&(data))>>24)
#define ACRPCR_get_write_en3(data)                                                   ((0x01000000&(data))>>24)
#define ACRPCR_disablecrp_shift                                                      (23)
#define ACRPCR_disablecrp_mask                                                       (0x00800000)
#define ACRPCR_disablecrp(data)                                                      (0x00800000&((data)<<23))
#define ACRPCR_disablecrp_src(data)                                                  ((0x00800000&(data))>>23)
#define ACRPCR_get_disablecrp(data)                                                  ((0x00800000&(data))>>23)
#define ACRPCR_write_en2_shift                                                       (22)
#define ACRPCR_write_en2_mask                                                        (0x00400000)
#define ACRPCR_write_en2(data)                                                       (0x00400000&((data)<<22))
#define ACRPCR_write_en2_src(data)                                                   ((0x00400000&(data))>>22)
#define ACRPCR_get_write_en2(data)                                                   ((0x00400000&(data))>>22)
#define ACRPCR_cts_source_shift                                                      (21)
#define ACRPCR_cts_source_mask                                                       (0x00200000)
#define ACRPCR_cts_source(data)                                                      (0x00200000&((data)<<21))
#define ACRPCR_cts_source_src(data)                                                  ((0x00200000&(data))>>21)
#define ACRPCR_get_cts_source(data)                                                  ((0x00200000&(data))>>21)
#define ACRPCR_write_en1_shift                                                       (20)
#define ACRPCR_write_en1_mask                                                        (0x00100000)
#define ACRPCR_write_en1(data)                                                       (0x00100000&((data)<<20))
#define ACRPCR_write_en1_src(data)                                                   ((0x00100000&(data))>>20)
#define ACRPCR_get_write_en1(data)                                                   ((0x00100000&(data))>>20)
#define ACRPCR_n_value_shift                                                         (0)
#define ACRPCR_n_value_mask                                                          (0x000FFFFF)
#define ACRPCR_n_value(data)                                                         (0x000FFFFF&((data)<<0))
#define ACRPCR_n_value_src(data)                                                     ((0x000FFFFF&(data))>>0)
#define ACRPCR_get_n_value(data)                                                     ((0x000FFFFF&(data))>>0)


#define ACRPCTSR                                                                     0x9800D070
#define ACRPCTSR_reg_addr                                                            "0x9800D070"
#define ACRPCTSR_reg                                                                 0x9800D070
#define set_ACRPCTSR_reg(data)   (*((volatile unsigned int*) ACRPCTSR_reg)=data)
#define get_ACRPCTSR_reg   (*((volatile unsigned int*) ACRPCTSR_reg))
#define ACRPCTSR_inst_adr                                                            "0x001C"
#define ACRPCTSR_inst                                                                0x001C
#define ACRPCTSR_ctssw_shift                                                         (0)
#define ACRPCTSR_ctssw_mask                                                          (0x000FFFFF)
#define ACRPCTSR_ctssw(data)                                                         (0x000FFFFF&((data)<<0))
#define ACRPCTSR_ctssw_src(data)                                                     ((0x000FFFFF&(data))>>0)
#define ACRPCTSR_get_ctssw(data)                                                     ((0x000FFFFF&(data))>>0)


#define ACRPPR                                                                       0x9800D074
#define ACRPPR_reg_addr                                                              "0x9800D074"
#define ACRPPR_reg                                                                   0x9800D074
#define set_ACRPPR_reg(data)   (*((volatile unsigned int*) ACRPPR_reg)=data)
#define get_ACRPPR_reg   (*((volatile unsigned int*) ACRPPR_reg))
#define ACRPPR_inst_adr                                                              "0x001D"
#define ACRPPR_inst                                                                  0x001D
#define ACRPPR_ctshw_shift                                                           (0)
#define ACRPPR_ctshw_mask                                                            (0x000FFFFF)
#define ACRPPR_ctshw(data)                                                           (0x000FFFFF&((data)<<0))
#define ACRPPR_ctshw_src(data)                                                       ((0x000FFFFF&(data))>>0)
#define ACRPPR_get_ctshw(data)                                                       ((0x000FFFFF&(data))>>0)


#define GCPCR                                                                        0x078
#define GCPCR_reg_addr                                                               "0x9800D078"
#define GCPCR_reg                                                                    0x9800D078
#define set_GCPCR_reg(data)   (*((volatile unsigned int*) GCPCR_reg)=data)
#define get_GCPCR_reg   (*((volatile unsigned int*) GCPCR_reg))
#define GCPCR_inst_adr                                                               "0x001E"
#define GCPCR_inst                                                                   0x001E
#define GCPCR_enablegcp_shift                                                        (3)
#define GCPCR_enablegcp_mask                                                         (0x00000008)
#define GCPCR_enablegcp(data)                                                        (0x00000008&((data)<<3))
#define GCPCR_enablegcp_src(data)                                                    ((0x00000008&(data))>>3)
#define GCPCR_get_enablegcp(data)                                                    ((0x00000008&(data))>>3)
#define GCPCR_gcp_clearavmute_shift                                                  (2)
#define GCPCR_gcp_clearavmute_mask                                                   (0x00000004)
#define GCPCR_gcp_clearavmute(data)                                                  (0x00000004&((data)<<2))
#define GCPCR_gcp_clearavmute_src(data)                                              ((0x00000004&(data))>>2)
#define GCPCR_get_gcp_clearavmute(data)                                              ((0x00000004&(data))>>2)
#define GCPCR_gcp_setavmute_shift                                                    (1)
#define GCPCR_gcp_setavmute_mask                                                     (0x00000002)
#define GCPCR_gcp_setavmute(data)                                                    (0x00000002&((data)<<1))
#define GCPCR_gcp_setavmute_src(data)                                                ((0x00000002&(data))>>1)
#define GCPCR_get_gcp_setavmute(data)                                                ((0x00000002&(data))>>1)
#define GCPCR_write_data_shift                                                       (0)
#define GCPCR_write_data_mask                                                        (0x00000001)
#define GCPCR_write_data(data)                                                       (0x00000001&((data)<<0))
#define GCPCR_write_data_src(data)                                                   ((0x00000001&(data))>>0)
#define GCPCR_get_write_data(data)                                                   ((0x00000001&(data))>>0)


#define ORP6PH                                                                       0x9800D07c
#define ORP6PH_reg_addr                                                              "0x9800D07C"
#define ORP6PH_reg                                                                   0x9800D07C
#define set_ORP6PH_reg(data)   (*((volatile unsigned int*) ORP6PH_reg)=data)
#define get_ORP6PH_reg   (*((volatile unsigned int*) ORP6PH_reg))
#define ORP6PH_inst_adr                                                              "0x001F"
#define ORP6PH_inst                                                                  0x001F
#define ORP6PH_once_pkt_shift                                                        (0)
#define ORP6PH_once_pkt_mask                                                         (0xFFFFFFFF)
#define ORP6PH_once_pkt(data)                                                        (0xFFFFFFFF&((data)<<0))
#define ORP6PH_once_pkt_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define ORP6PH_get_once_pkt(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define ORP6W_0                                                                      0x9800D080
#define ORP6W_1                                                                      0x9800D084
#define ORP6W_2                                                                      0x9800D088
#define ORP6W_3                                                                      0x9800D08C
#define ORP6W_4                                                                      0x9800D090
#define ORP6W_5                                                                      0x9800D094
#define ORP6W_6                                                                      0x9800D098
#define ORP6W_7                                                                      0x9800D09C
#define ORP6W_0_reg_addr                                                             "0x9800D080"
#define ORP6W_1_reg_addr                                                             "0x9800D084"
#define ORP6W_2_reg_addr                                                             "0x9800D088"
#define ORP6W_3_reg_addr                                                             "0x9800D08C"
#define ORP6W_4_reg_addr                                                             "0x9800D090"
#define ORP6W_5_reg_addr                                                             "0x9800D094"
#define ORP6W_6_reg_addr                                                             "0x9800D098"
#define ORP6W_7_reg_addr                                                             "0x9800D09C"
#define ORP6W_0_reg                                                                  0x9800D080
#define ORP6W_1_reg                                                                  0x9800D084
#define ORP6W_2_reg                                                                  0x9800D088
#define ORP6W_3_reg                                                                  0x9800D08C
#define ORP6W_4_reg                                                                  0x9800D090
#define ORP6W_5_reg                                                                  0x9800D094
#define ORP6W_6_reg                                                                  0x9800D098
#define ORP6W_7_reg                                                                  0x9800D09C
#define set_ORP6W_0_reg(data)   (*((volatile unsigned int*) ORP6W_0_reg)=data)
#define set_ORP6W_1_reg(data)   (*((volatile unsigned int*) ORP6W_1_reg)=data)
#define set_ORP6W_2_reg(data)   (*((volatile unsigned int*) ORP6W_2_reg)=data)
#define set_ORP6W_3_reg(data)   (*((volatile unsigned int*) ORP6W_3_reg)=data)
#define set_ORP6W_4_reg(data)   (*((volatile unsigned int*) ORP6W_4_reg)=data)
#define set_ORP6W_5_reg(data)   (*((volatile unsigned int*) ORP6W_5_reg)=data)
#define set_ORP6W_6_reg(data)   (*((volatile unsigned int*) ORP6W_6_reg)=data)
#define set_ORP6W_7_reg(data)   (*((volatile unsigned int*) ORP6W_7_reg)=data)
#define get_ORP6W_0_reg   (*((volatile unsigned int*) ORP6W_0_reg))
#define get_ORP6W_1_reg   (*((volatile unsigned int*) ORP6W_1_reg))
#define get_ORP6W_2_reg   (*((volatile unsigned int*) ORP6W_2_reg))
#define get_ORP6W_3_reg   (*((volatile unsigned int*) ORP6W_3_reg))
#define get_ORP6W_4_reg   (*((volatile unsigned int*) ORP6W_4_reg))
#define get_ORP6W_5_reg   (*((volatile unsigned int*) ORP6W_5_reg))
#define get_ORP6W_6_reg   (*((volatile unsigned int*) ORP6W_6_reg))
#define get_ORP6W_7_reg   (*((volatile unsigned int*) ORP6W_7_reg))
#define ORP6W_0_inst_adr                                                             "0x0020"
#define ORP6W_1_inst_adr                                                             "0x0021"
#define ORP6W_2_inst_adr                                                             "0x0022"
#define ORP6W_3_inst_adr                                                             "0x0023"
#define ORP6W_4_inst_adr                                                             "0x0024"
#define ORP6W_5_inst_adr                                                             "0x0025"
#define ORP6W_6_inst_adr                                                             "0x0026"
#define ORP6W_7_inst_adr                                                             "0x0027"
#define ORP6W_0_inst                                                                 0x0020
#define ORP6W_1_inst                                                                 0x0021
#define ORP6W_2_inst                                                                 0x0022
#define ORP6W_3_inst                                                                 0x0023
#define ORP6W_4_inst                                                                 0x0024
#define ORP6W_5_inst                                                                 0x0025
#define ORP6W_6_inst                                                                 0x0026
#define ORP6W_7_inst                                                                 0x0027
#define ORP6W_once_pkt_shift                                                         (0)
#define ORP6W_once_pkt_mask                                                          (0xFFFFFFFF)
#define ORP6W_once_pkt(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ORP6W_once_pkt_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ORP6W_get_once_pkt(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define RPCR                                                                         0x9800D0a0
#define RPCR_reg_addr                                                                "0x9800D0A0"
#define RPCR_reg                                                                     0x9800D0A0
#define set_RPCR_reg(data)   (*((volatile unsigned int*) RPCR_reg)=data)
#define get_RPCR_reg   (*((volatile unsigned int*) RPCR_reg))
#define RPCR_inst_adr                                                                "0x0028"
#define RPCR_inst                                                                    0x0028
#define RPCR_write_en6_shift                                                         (29)
#define RPCR_write_en6_mask                                                          (0x20000000)
#define RPCR_write_en6(data)                                                         (0x20000000&((data)<<29))
#define RPCR_write_en6_src(data)                                                     ((0x20000000&(data))>>29)
#define RPCR_get_write_en6(data)                                                     ((0x20000000&(data))>>29)
#define RPCR_prp5period_shift                                                        (25)
#define RPCR_prp5period_mask                                                         (0x1E000000)
#define RPCR_prp5period(data)                                                        (0x1E000000&((data)<<25))
#define RPCR_prp5period_src(data)                                                    ((0x1E000000&(data))>>25)
#define RPCR_get_prp5period(data)                                                    ((0x1E000000&(data))>>25)
#define RPCR_write_en5_shift                                                         (24)
#define RPCR_write_en5_mask                                                          (0x01000000)
#define RPCR_write_en5(data)                                                         (0x01000000&((data)<<24))
#define RPCR_write_en5_src(data)                                                     ((0x01000000&(data))>>24)
#define RPCR_get_write_en5(data)                                                     ((0x01000000&(data))>>24)
#define RPCR_prp4period_shift                                                        (20)
#define RPCR_prp4period_mask                                                         (0x00F00000)
#define RPCR_prp4period(data)                                                        (0x00F00000&((data)<<20))
#define RPCR_prp4period_src(data)                                                    ((0x00F00000&(data))>>20)
#define RPCR_get_prp4period(data)                                                    ((0x00F00000&(data))>>20)
#define RPCR_write_en4_shift                                                         (19)
#define RPCR_write_en4_mask                                                          (0x00080000)
#define RPCR_write_en4(data)                                                         (0x00080000&((data)<<19))
#define RPCR_write_en4_src(data)                                                     ((0x00080000&(data))>>19)
#define RPCR_get_write_en4(data)                                                     ((0x00080000&(data))>>19)
#define RPCR_prp3period_shift                                                        (15)
#define RPCR_prp3period_mask                                                         (0x00078000)
#define RPCR_prp3period(data)                                                        (0x00078000&((data)<<15))
#define RPCR_prp3period_src(data)                                                    ((0x00078000&(data))>>15)
#define RPCR_get_prp3period(data)                                                    ((0x00078000&(data))>>15)
#define RPCR_write_en3_shift                                                         (14)
#define RPCR_write_en3_mask                                                          (0x00004000)
#define RPCR_write_en3(data)                                                         (0x00004000&((data)<<14))
#define RPCR_write_en3_src(data)                                                     ((0x00004000&(data))>>14)
#define RPCR_get_write_en3(data)                                                     ((0x00004000&(data))>>14)
#define RPCR_prp2period_shift                                                        (10)
#define RPCR_prp2period_mask                                                         (0x00003C00)
#define RPCR_prp2period(data)                                                        (0x00003C00&((data)<<10))
#define RPCR_prp2period_src(data)                                                    ((0x00003C00&(data))>>10)
#define RPCR_get_prp2period(data)                                                    ((0x00003C00&(data))>>10)
#define RPCR_write_en2_shift                                                         (9)
#define RPCR_write_en2_mask                                                          (0x00000200)
#define RPCR_write_en2(data)                                                         (0x00000200&((data)<<9))
#define RPCR_write_en2_src(data)                                                     ((0x00000200&(data))>>9)
#define RPCR_get_write_en2(data)                                                     ((0x00000200&(data))>>9)
#define RPCR_prp1period_shift                                                        (5)
#define RPCR_prp1period_mask                                                         (0x000001E0)
#define RPCR_prp1period(data)                                                        (0x000001E0&((data)<<5))
#define RPCR_prp1period_src(data)                                                    ((0x000001E0&(data))>>5)
#define RPCR_get_prp1period(data)                                                    ((0x000001E0&(data))>>5)
#define RPCR_write_en1_shift                                                         (4)
#define RPCR_write_en1_mask                                                          (0x00000010)
#define RPCR_write_en1(data)                                                         (0x00000010&((data)<<4))
#define RPCR_write_en1_src(data)                                                     ((0x00000010&(data))>>4)
#define RPCR_get_write_en1(data)                                                     ((0x00000010&(data))>>4)
#define RPCR_prp0period_shift                                                        (0)
#define RPCR_prp0period_mask                                                         (0x0000000F)
#define RPCR_prp0period(data)                                                        (0x0000000F&((data)<<0))
#define RPCR_prp0period_src(data)                                                    ((0x0000000F&(data))>>0)
#define RPCR_get_prp0period(data)                                                    ((0x0000000F&(data))>>0)


#define RPEN                                                                         0x9800D0a4
#define RPEN_reg_addr                                                                "0x9800D0A4"
#define RPEN_reg                                                                     0x9800D0A4
#define set_RPEN_reg(data)   (*((volatile unsigned int*) RPEN_reg)=data)
#define get_RPEN_reg   (*((volatile unsigned int*) RPEN_reg))
#define RPEN_inst_adr                                                                "0x0029"
#define RPEN_inst                                                                    0x0029
#define RPEN_enprpkt5_shift                                                          (6)
#define RPEN_enprpkt5_mask                                                           (0x00000040)
#define RPEN_enprpkt5(data)                                                          (0x00000040&((data)<<6))
#define RPEN_enprpkt5_src(data)                                                      ((0x00000040&(data))>>6)
#define RPEN_get_enprpkt5(data)                                                      ((0x00000040&(data))>>6)
#define RPEN_enprpkt4_shift                                                          (5)
#define RPEN_enprpkt4_mask                                                           (0x00000020)
#define RPEN_enprpkt4(data)                                                          (0x00000020&((data)<<5))
#define RPEN_enprpkt4_src(data)                                                      ((0x00000020&(data))>>5)
#define RPEN_get_enprpkt4(data)                                                      ((0x00000020&(data))>>5)
#define RPEN_enprpkt3_shift                                                          (4)
#define RPEN_enprpkt3_mask                                                           (0x00000010)
#define RPEN_enprpkt3(data)                                                          (0x00000010&((data)<<4))
#define RPEN_enprpkt3_src(data)                                                      ((0x00000010&(data))>>4)
#define RPEN_get_enprpkt3(data)                                                      ((0x00000010&(data))>>4)
#define RPEN_enprpkt2_shift                                                          (3)
#define RPEN_enprpkt2_mask                                                           (0x00000008)
#define RPEN_enprpkt2(data)                                                          (0x00000008&((data)<<3))
#define RPEN_enprpkt2_src(data)                                                      ((0x00000008&(data))>>3)
#define RPEN_get_enprpkt2(data)                                                      ((0x00000008&(data))>>3)
#define RPEN_enprpkt1_shift                                                          (2)
#define RPEN_enprpkt1_mask                                                           (0x00000004)
#define RPEN_enprpkt1(data)                                                          (0x00000004&((data)<<2))
#define RPEN_enprpkt1_src(data)                                                      ((0x00000004&(data))>>2)
#define RPEN_get_enprpkt1(data)                                                      ((0x00000004&(data))>>2)
#define RPEN_enprpkt0_shift                                                          (1)
#define RPEN_enprpkt0_mask                                                           (0x00000002)
#define RPEN_enprpkt0(data)                                                          (0x00000002&((data)<<1))
#define RPEN_enprpkt0_src(data)                                                      ((0x00000002&(data))>>1)
#define RPEN_get_enprpkt0(data)                                                      ((0x00000002&(data))>>1)
#define RPEN_write_data_shift                                                        (0)
#define RPEN_write_data_mask                                                         (0x00000001)
#define RPEN_write_data(data)                                                        (0x00000001&((data)<<0))
#define RPEN_write_data_src(data)                                                    ((0x00000001&(data))>>0)
#define RPEN_get_write_data(data)                                                    ((0x00000001&(data))>>0)


#define RPRBDR                                                                       0x9800D0a8
#define RPRBDR_reg_addr                                                              "0x9800D0A8"
#define RPRBDR_reg                                                                   0x9800D0A8
#define set_RPRBDR_reg(data)   (*((volatile unsigned int*) RPRBDR_reg)=data)
#define get_RPRBDR_reg   (*((volatile unsigned int*) RPRBDR_reg))
#define RPRBDR_inst_adr                                                              "0x002A"
#define RPRBDR_inst                                                                  0x002A
#define RPRBDR_isramrbd_shift                                                        (0)
#define RPRBDR_isramrbd_mask                                                         (0x0003FFFF)
#define RPRBDR_isramrbd(data)                                                        (0x0003FFFF&((data)<<0))
#define RPRBDR_isramrbd_src(data)                                                    ((0x0003FFFF&(data))>>0)
#define RPRBDR_get_isramrbd(data)                                                    ((0x0003FFFF&(data))>>0)


#define OPCR                                                                         0x9800D0b0
#define OPCR_reg_addr                                                                "0x9800D0B0"
#define OPCR_reg                                                                     0x9800D0B0
#define set_OPCR_reg(data)   (*((volatile unsigned int*) OPCR_reg)=data)
#define get_OPCR_reg   (*((volatile unsigned int*) OPCR_reg))
#define OPCR_inst_adr                                                                "0x002C"
#define OPCR_inst                                                                    0x002C
#define OPCR_write_en4_shift                                                         (14)
#define OPCR_write_en4_mask                                                          (0x00004000)
#define OPCR_write_en4(data)                                                         (0x00004000&((data)<<14))
#define OPCR_write_en4_src(data)                                                     ((0x00004000&(data))>>14)
#define OPCR_get_write_en4(data)                                                     ((0x00004000&(data))>>14)
#define OPCR_enrbpktsram_shift                                                       (13)
#define OPCR_enrbpktsram_mask                                                        (0x00002000)
#define OPCR_enrbpktsram(data)                                                       (0x00002000&((data)<<13))
#define OPCR_enrbpktsram_src(data)                                                   ((0x00002000&(data))>>13)
#define OPCR_get_enrbpktsram(data)                                                   ((0x00002000&(data))>>13)
#define OPCR_write_en3_shift                                                         (12)
#define OPCR_write_en3_mask                                                          (0x00001000)
#define OPCR_write_en3(data)                                                         (0x00001000&((data)<<12))
#define OPCR_write_en3_src(data)                                                     ((0x00001000&(data))>>12)
#define OPCR_get_write_en3(data)                                                     ((0x00001000&(data))>>12)
#define OPCR_wrdes_shift                                                             (11)
#define OPCR_wrdes_mask                                                              (0x00000800)
#define OPCR_wrdes(data)                                                             (0x00000800&((data)<<11))
#define OPCR_wrdes_src(data)                                                         ((0x00000800&(data))>>11)
#define OPCR_get_wrdes(data)                                                         ((0x00000800&(data))>>11)
#define OPCR_write_en2_shift                                                         (10)
#define OPCR_write_en2_mask                                                          (0x00000400)
#define OPCR_write_en2(data)                                                         (0x00000400&((data)<<10))
#define OPCR_write_en2_src(data)                                                     ((0x00000400&(data))>>10)
#define OPCR_get_write_en2(data)                                                     ((0x00000400&(data))>>10)
#define OPCR_rprwcmd_shift                                                           (9)
#define OPCR_rprwcmd_mask                                                            (0x00000200)
#define OPCR_rprwcmd(data)                                                           (0x00000200&((data)<<9))
#define OPCR_rprwcmd_src(data)                                                       ((0x00000200&(data))>>9)
#define OPCR_get_rprwcmd(data)                                                       ((0x00000200&(data))>>9)
#define OPCR_write_en1_shift                                                         (8)
#define OPCR_write_en1_mask                                                          (0x00000100)
#define OPCR_write_en1(data)                                                         (0x00000100&((data)<<8))
#define OPCR_write_en1_src(data)                                                     ((0x00000100&(data))>>8)
#define OPCR_get_write_en1(data)                                                     ((0x00000100&(data))>>8)
#define OPCR_rpadd_shift                                                             (0)
#define OPCR_rpadd_mask                                                              (0x000000FF)
#define OPCR_rpadd(data)                                                             (0x000000FF&((data)<<0))
#define OPCR_rpadd_src(data)                                                         ((0x000000FF&(data))>>0)
#define OPCR_get_rpadd(data)                                                         ((0x000000FF&(data))>>0)


#define DIPCCR                                                                       0x9800D0b4
#define DIPCCR_reg_addr                                                              "0x9800D0B4"
#define DIPCCR_reg                                                                   0x9800D0B4
#define set_DIPCCR_reg(data)   (*((volatile unsigned int*) DIPCCR_reg)=data)
#define get_DIPCCR_reg   (*((volatile unsigned int*) DIPCCR_reg))
#define DIPCCR_inst_adr                                                              "0x002D"
#define DIPCCR_inst                                                                  0x002D
#define DIPCCR_write_en2_shift                                                       (11)
#define DIPCCR_write_en2_mask                                                        (0x00000800)
#define DIPCCR_write_en2(data)                                                       (0x00000800&((data)<<11))
#define DIPCCR_write_en2_src(data)                                                   ((0x00000800&(data))>>11)
#define DIPCCR_get_write_en2(data)                                                   ((0x00000800&(data))>>11)
#define DIPCCR_vbidipcnt_shift                                                       (6)
#define DIPCCR_vbidipcnt_mask                                                        (0x000007C0)
#define DIPCCR_vbidipcnt(data)                                                       (0x000007C0&((data)<<6))
#define DIPCCR_vbidipcnt_src(data)                                                   ((0x000007C0&(data))>>6)
#define DIPCCR_get_vbidipcnt(data)                                                   ((0x000007C0&(data))>>6)
#define DIPCCR_write_en1_shift                                                       (5)
#define DIPCCR_write_en1_mask                                                        (0x00000020)
#define DIPCCR_write_en1(data)                                                       (0x00000020&((data)<<5))
#define DIPCCR_write_en1_src(data)                                                   ((0x00000020&(data))>>5)
#define DIPCCR_get_write_en1(data)                                                   ((0x00000020&(data))>>5)
#define DIPCCR_hbidipcnt_shift                                                       (0)
#define DIPCCR_hbidipcnt_mask                                                        (0x0000001F)
#define DIPCCR_hbidipcnt(data)                                                       (0x0000001F&((data)<<0))
#define DIPCCR_hbidipcnt_src(data)                                                   ((0x0000001F&(data))>>0)
#define DIPCCR_get_hbidipcnt(data)                                                   ((0x0000001F&(data))>>0)


#define SCHCR                                                                        0x9800D0b8
#define SCHCR_reg_addr                                                               "0x9800D0B8"
#define SCHCR_reg                                                                    0x9800D0B8
#define set_SCHCR_reg(data)   (*((volatile unsigned int*) SCHCR_reg)=data)
#define get_SCHCR_reg   (*((volatile unsigned int*) SCHCR_reg))
#define SCHCR_inst_adr                                                               "0x002E"
#define SCHCR_inst                                                                   0x002E
#define SCHCR_write_en12_shift                                                       (28)
#define SCHCR_write_en12_mask                                                        (0x10000000)
#define SCHCR_write_en12(data)                                                       (0x10000000&((data)<<28))
#define SCHCR_write_en12_src(data)                                                   ((0x10000000&(data))>>28)
#define SCHCR_get_write_en12(data)                                                   ((0x10000000&(data))>>28)
#define SCHCR_color_transform_en_shift                                               (27)
#define SCHCR_color_transform_en_mask                                                (0x08000000)
#define SCHCR_color_transform_en(data)                                               (0x08000000&((data)<<27))
#define SCHCR_color_transform_en_src(data)                                           ((0x08000000&(data))>>27)
#define SCHCR_get_color_transform_en(data)                                           ((0x08000000&(data))>>27)
#define SCHCR_write_en11_shift                                                       (26)
#define SCHCR_write_en11_mask                                                        (0x04000000)
#define SCHCR_write_en11(data)                                                       (0x04000000&((data)<<26))
#define SCHCR_write_en11_src(data)                                                   ((0x04000000&(data))>>26)
#define SCHCR_get_write_en11(data)                                                   ((0x04000000&(data))>>26)
#define SCHCR_ycbcr422_algo_shift                                                    (25)
#define SCHCR_ycbcr422_algo_mask                                                     (0x02000000)
#define SCHCR_ycbcr422_algo(data)                                                    (0x02000000&((data)<<25))
#define SCHCR_ycbcr422_algo_src(data)                                                ((0x02000000&(data))>>25)
#define SCHCR_get_ycbcr422_algo(data)                                                ((0x02000000&(data))>>25)
#define SCHCR_write_en10_shift                                                       (24)
#define SCHCR_write_en10_mask                                                        (0x01000000)
#define SCHCR_write_en10(data)                                                       (0x01000000&((data)<<24))
#define SCHCR_write_en10_src(data)                                                   ((0x01000000&(data))>>24)
#define SCHCR_get_write_en10(data)                                                   ((0x01000000&(data))>>24)
#define SCHCR_422_pixel_repeat_shift                                                 (23)
#define SCHCR_422_pixel_repeat_mask                                                  (0x00800000)
#define SCHCR_422_pixel_repeat(data)                                                 (0x00800000&((data)<<23))
#define SCHCR_422_pixel_repeat_src(data)                                             ((0x00800000&(data))>>23)
#define SCHCR_get_422_pixel_repeat(data)                                             ((0x00800000&(data))>>23)
#define SCHCR_write_en9_shift                                                        (22)
#define SCHCR_write_en9_mask                                                         (0x00400000)
#define SCHCR_write_en9(data)                                                        (0x00400000&((data)<<22))
#define SCHCR_write_en9_src(data)                                                    ((0x00400000&(data))>>22)
#define SCHCR_get_write_en9(data)                                                    ((0x00400000&(data))>>22)
#define SCHCR_vsyncpolin_shift                                                       (21)
#define SCHCR_vsyncpolin_mask                                                        (0x00200000)
#define SCHCR_vsyncpolin(data)                                                       (0x00200000&((data)<<21))
#define SCHCR_vsyncpolin_src(data)                                                   ((0x00200000&(data))>>21)
#define SCHCR_get_vsyncpolin(data)                                                   ((0x00200000&(data))>>21)
#define SCHCR_write_en8_shift                                                        (20)
#define SCHCR_write_en8_mask                                                         (0x00100000)
#define SCHCR_write_en8(data)                                                        (0x00100000&((data)<<20))
#define SCHCR_write_en8_src(data)                                                    ((0x00100000&(data))>>20)
#define SCHCR_get_write_en8(data)                                                    ((0x00100000&(data))>>20)
#define SCHCR_hsyncpolin_shift                                                       (19)
#define SCHCR_hsyncpolin_mask                                                        (0x00080000)
#define SCHCR_hsyncpolin(data)                                                       (0x00080000&((data)<<19))
#define SCHCR_hsyncpolin_src(data)                                                   ((0x00080000&(data))>>19)
#define SCHCR_get_hsyncpolin(data)                                                   ((0x00080000&(data))>>19)
#define SCHCR_write_en7_shift                                                        (18)
#define SCHCR_write_en7_mask                                                         (0x00040000)
#define SCHCR_write_en7(data)                                                        (0x00040000&((data)<<18))
#define SCHCR_write_en7_src(data)                                                    ((0x00040000&(data))>>18)
#define SCHCR_get_write_en7(data)                                                    ((0x00040000&(data))>>18)
#define SCHCR_vsyncpolinv_shift                                                      (17)
#define SCHCR_vsyncpolinv_mask                                                       (0x00020000)
#define SCHCR_vsyncpolinv(data)                                                      (0x00020000&((data)<<17))
#define SCHCR_vsyncpolinv_src(data)                                                  ((0x00020000&(data))>>17)
#define SCHCR_get_vsyncpolinv(data)                                                  ((0x00020000&(data))>>17)
#define SCHCR_write_en6_shift                                                        (16)
#define SCHCR_write_en6_mask                                                         (0x00010000)
#define SCHCR_write_en6(data)                                                        (0x00010000&((data)<<16))
#define SCHCR_write_en6_src(data)                                                    ((0x00010000&(data))>>16)
#define SCHCR_get_write_en6(data)                                                    ((0x00010000&(data))>>16)
#define SCHCR_hsyncpolinv_shift                                                      (15)
#define SCHCR_hsyncpolinv_mask                                                       (0x00008000)
#define SCHCR_hsyncpolinv(data)                                                      (0x00008000&((data)<<15))
#define SCHCR_hsyncpolinv_src(data)                                                  ((0x00008000&(data))>>15)
#define SCHCR_get_hsyncpolinv(data)                                                  ((0x00008000&(data))>>15)
#define SCHCR_write_en5_shift                                                        (14)
#define SCHCR_write_en5_mask                                                         (0x00004000)
#define SCHCR_write_en5(data)                                                        (0x00004000&((data)<<14))
#define SCHCR_write_en5_src(data)                                                    ((0x00004000&(data))>>14)
#define SCHCR_get_write_en5(data)                                                    ((0x00004000&(data))>>14)
#define SCHCR_pixelencycbcr422_shift                                                 (13)
#define SCHCR_pixelencycbcr422_mask                                                  (0x00002000)
#define SCHCR_pixelencycbcr422(data)                                                 (0x00002000&((data)<<13))
#define SCHCR_pixelencycbcr422_src(data)                                             ((0x00002000&(data))>>13)
#define SCHCR_get_pixelencycbcr422(data)                                             ((0x00002000&(data))>>13)
#define SCHCR_write_en4_shift                                                        (12)
#define SCHCR_write_en4_mask                                                         (0x00001000)
#define SCHCR_write_en4(data)                                                        (0x00001000&((data)<<12))
#define SCHCR_write_en4_src(data)                                                    ((0x00001000&(data))>>12)
#define SCHCR_get_write_en4(data)                                                    ((0x00001000&(data))>>12)
#define SCHCR_hdmi_videoxs_shift                                                     (7)
#define SCHCR_hdmi_videoxs_mask                                                      (0x00000F80)
#define SCHCR_hdmi_videoxs(data)                                                     (0x00000F80&((data)<<7))
#define SCHCR_hdmi_videoxs_src(data)                                                 ((0x00000F80&(data))>>7)
#define SCHCR_get_hdmi_videoxs(data)                                                 ((0x00000F80&(data))>>7)
#define SCHCR_write_en3_shift                                                        (6)
#define SCHCR_write_en3_mask                                                         (0x00000040)
#define SCHCR_write_en3(data)                                                        (0x00000040&((data)<<6))
#define SCHCR_write_en3_src(data)                                                    ((0x00000040&(data))>>6)
#define SCHCR_get_write_en3(data)                                                    ((0x00000040&(data))>>6)
#define SCHCR_pixelencfmt_shift                                                      (4)
#define SCHCR_pixelencfmt_mask                                                       (0x00000030)
#define SCHCR_pixelencfmt(data)                                                      (0x00000030&((data)<<4))
#define SCHCR_pixelencfmt_src(data)                                                  ((0x00000030&(data))>>4)
#define SCHCR_get_pixelencfmt(data)                                                  ((0x00000030&(data))>>4)
#define SCHCR_write_en2_shift                                                        (3)
#define SCHCR_write_en2_mask                                                         (0x00000008)
#define SCHCR_write_en2(data)                                                        (0x00000008&((data)<<3))
#define SCHCR_write_en2_src(data)                                                    ((0x00000008&(data))>>3)
#define SCHCR_get_write_en2(data)                                                    ((0x00000008&(data))>>3)
#define SCHCR_pixelrepeat_shift                                                      (2)
#define SCHCR_pixelrepeat_mask                                                       (0x00000004)
#define SCHCR_pixelrepeat(data)                                                      (0x00000004&((data)<<2))
#define SCHCR_pixelrepeat_src(data)                                                  ((0x00000004&(data))>>2)
#define SCHCR_get_pixelrepeat(data)                                                  ((0x00000004&(data))>>2)
#define SCHCR_write_en1_shift                                                        (1)
#define SCHCR_write_en1_mask                                                         (0x00000002)
#define SCHCR_write_en1(data)                                                        (0x00000002&((data)<<1))
#define SCHCR_write_en1_src(data)                                                    ((0x00000002&(data))>>1)
#define SCHCR_get_write_en1(data)                                                    ((0x00000002&(data))>>1)
#define SCHCR_hdmi_modesel_shift                                                     (0)
#define SCHCR_hdmi_modesel_mask                                                      (0x00000001)
#define SCHCR_hdmi_modesel(data)                                                     (0x00000001&((data)<<0))
#define SCHCR_hdmi_modesel_src(data)                                                 ((0x00000001&(data))>>0)
#define SCHCR_get_hdmi_modesel(data)                                                 ((0x00000001&(data))>>0)


#define ICR                                                                          0x9800D0bc
#define ICR_reg_addr                                                                 "0x9800D0BC"
#define ICR_reg                                                                      0x9800D0BC
#define set_ICR_reg(data)   (*((volatile unsigned int*) ICR_reg)=data)
#define get_ICR_reg   (*((volatile unsigned int*) ICR_reg))
#define ICR_inst_adr                                                                 "0x002F"
#define ICR_inst                                                                     0x002F
#define ICR_write_en3_shift                                                          (28)
#define ICR_write_en3_mask                                                           (0x10000000)
#define ICR_write_en3(data)                                                          (0x10000000&((data)<<28))
#define ICR_write_en3_src(data)                                                      ((0x10000000&(data))>>28)
#define ICR_get_write_en3(data)                                                      ((0x10000000&(data))>>28)
#define ICR_enaudio_shift                                                            (27)
#define ICR_enaudio_mask                                                             (0x08000000)
#define ICR_enaudio(data)                                                            (0x08000000&((data)<<27))
#define ICR_enaudio_src(data)                                                        ((0x08000000&(data))>>27)
#define ICR_get_enaudio(data)                                                        ((0x08000000&(data))>>27)
#define ICR_write_en2_shift                                                          (26)
#define ICR_write_en2_mask                                                           (0x04000000)
#define ICR_write_en2(data)                                                          (0x04000000&((data)<<26))
#define ICR_write_en2_src(data)                                                      ((0x04000000&(data))>>26)
#define ICR_get_write_en2(data)                                                      ((0x04000000&(data))>>26)
#define ICR_envitd_shift                                                             (25)
#define ICR_envitd_mask                                                              (0x02000000)
#define ICR_envitd(data)                                                             (0x02000000&((data)<<25))
#define ICR_envitd_src(data)                                                         ((0x02000000&(data))>>25)
#define ICR_get_envitd(data)                                                         ((0x02000000&(data))>>25)
#define ICR_write_en1_shift                                                          (24)
#define ICR_write_en1_mask                                                           (0x01000000)
#define ICR_write_en1(data)                                                          (0x01000000&((data)<<24))
#define ICR_write_en1_src(data)                                                      ((0x01000000&(data))>>24)
#define ICR_get_write_en1(data)                                                      ((0x01000000&(data))>>24)
#define ICR_vitd_shift                                                               (0)
#define ICR_vitd_mask                                                                (0x00FFFFFF)
#define ICR_vitd(data)                                                               (0x00FFFFFF&((data)<<0))
#define ICR_vitd_src(data)                                                           ((0x00FFFFFF&(data))>>0)
#define ICR_get_vitd(data)                                                           ((0x00FFFFFF&(data))>>0)


#define ICR1                                                                         0x9800D150
#define ICR1_reg_addr                                                                "0x9800D150"
#define ICR1_reg                                                                     0x9800D150
#define set_ICR1_reg(data)   (*((volatile unsigned int*) ICR1_reg)=data)
#define get_ICR1_reg   (*((volatile unsigned int*) ICR1_reg))
#define ICR1_inst_adr                                                                "0x0054"
#define ICR1_inst                                                                    0x0054
#define ICR1_write_en1_shift                                                         (12)
#define ICR1_write_en1_mask                                                          (0x00001000)
#define ICR1_write_en1(data)                                                         (0x00001000&((data)<<12))
#define ICR1_write_en1_src(data)                                                     ((0x00001000&(data))>>12)
#define ICR1_get_write_en1(data)                                                     ((0x00001000&(data))>>12)
#define ICR1_vitd_shift                                                              (0)
#define ICR1_vitd_mask                                                               (0x00000FFF)
#define ICR1_vitd(data)                                                              (0x00000FFF&((data)<<0))
#define ICR1_vitd_src(data)                                                          ((0x00000FFF&(data))>>0)
#define ICR1_get_vitd(data)                                                          ((0x00000FFF&(data))>>0)


#define CRCCR                                                                        0x9800D0c0
#define CRCCR_reg_addr                                                               "0x9800D0C0"
#define CRCCR_reg                                                                    0x9800D0C0
#define set_CRCCR_reg(data)   (*((volatile unsigned int*) CRCCR_reg)=data)
#define get_CRCCR_reg   (*((volatile unsigned int*) CRCCR_reg))
#define CRCCR_inst_adr                                                               "0x0030"
#define CRCCR_inst                                                                   0x0030
#define CRCCR_write_en2_shift                                                        (4)
#define CRCCR_write_en2_mask                                                         (0x00000010)
#define CRCCR_write_en2(data)                                                        (0x00000010&((data)<<4))
#define CRCCR_write_en2_src(data)                                                    ((0x00000010&(data))>>4)
#define CRCCR_get_write_en2(data)                                                    ((0x00000010&(data))>>4)
#define CRCCR_crcmode_shift                                                          (3)
#define CRCCR_crcmode_mask                                                           (0x00000008)
#define CRCCR_crcmode(data)                                                          (0x00000008&((data)<<3))
#define CRCCR_crcmode_src(data)                                                      ((0x00000008&(data))>>3)
#define CRCCR_get_crcmode(data)                                                      ((0x00000008&(data))>>3)
#define CRCCR_write_en1_shift                                                        (2)
#define CRCCR_write_en1_mask                                                         (0x00000004)
#define CRCCR_write_en1(data)                                                        (0x00000004&((data)<<2))
#define CRCCR_write_en1_src(data)                                                    ((0x00000004&(data))>>2)
#define CRCCR_get_write_en1(data)                                                    ((0x00000004&(data))>>2)
#define CRCCR_crcchsel_shift                                                         (0)
#define CRCCR_crcchsel_mask                                                          (0x00000003)
#define CRCCR_crcchsel(data)                                                         (0x00000003&((data)<<0))
#define CRCCR_crcchsel_src(data)                                                     ((0x00000003&(data))>>0)
#define CRCCR_get_crcchsel(data)                                                     ((0x00000003&(data))>>0)


#define CRCDOR                                                                       0x9800D0c4
#define CRCDOR_reg_addr                                                              "0x9800D0C4"
#define CRCDOR_reg                                                                   0x9800D0C4
#define set_CRCDOR_reg(data)   (*((volatile unsigned int*) CRCDOR_reg)=data)
#define get_CRCDOR_reg   (*((volatile unsigned int*) CRCDOR_reg))
#define CRCDOR_inst_adr                                                              "0x0031"
#define CRCDOR_inst                                                                  0x0031
#define CRCDOR_crcvalue_shift                                                        (0)
#define CRCDOR_crcvalue_mask                                                         (0xFFFFFFFF)
#define CRCDOR_crcvalue(data)                                                        (0xFFFFFFFF&((data)<<0))
#define CRCDOR_crcvalue_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define CRCDOR_get_crcvalue(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define HDCP_KOWR                                                                    0x9800D0f0
#define HDCP_KOWR_reg_addr                                                           "0x9800D0F0"
#define HDCP_KOWR_reg                                                                0x9800D0F0
#define set_HDCP_KOWR_reg(data)   (*((volatile unsigned int*) HDCP_KOWR_reg)=data)
#define get_HDCP_KOWR_reg   (*((volatile unsigned int*) HDCP_KOWR_reg))
#define HDCP_KOWR_inst_adr                                                           "0x003C"
#define HDCP_KOWR_inst                                                               0x003C
#define HDCP_KOWR_hdcprekeykeepoutwin_shift                                          (0)
#define HDCP_KOWR_hdcprekeykeepoutwin_mask                                           (0x000000FF)
#define HDCP_KOWR_hdcprekeykeepoutwin(data)                                          (0x000000FF&((data)<<0))
#define HDCP_KOWR_hdcprekeykeepoutwin_src(data)                                      ((0x000000FF&(data))>>0)
#define HDCP_KOWR_get_hdcprekeykeepoutwin(data)                                      ((0x000000FF&(data))>>0)


#define HDCP_KOWRSE                                                                  0x9800D0f4
#define HDCP_KOWRSE_reg_addr                                                         "0x9800D0F4"
#define HDCP_KOWRSE_reg                                                              0x9800D0F4
#define set_HDCP_KOWRSE_reg(data)   (*((volatile unsigned int*) HDCP_KOWRSE_reg)=data)
#define get_HDCP_KOWRSE_reg   (*((volatile unsigned int*) HDCP_KOWRSE_reg))
#define HDCP_KOWRSE_inst_adr                                                         "0x003D"
#define HDCP_KOWRSE_inst                                                             0x003D
#define HDCP_KOWRSE_write_en2_shift                                                  (25)
#define HDCP_KOWRSE_write_en2_mask                                                   (0x02000000)
#define HDCP_KOWRSE_write_en2(data)                                                  (0x02000000&((data)<<25))
#define HDCP_KOWRSE_write_en2_src(data)                                              ((0x02000000&(data))>>25)
#define HDCP_KOWRSE_get_write_en2(data)                                              ((0x02000000&(data))>>25)
#define HDCP_KOWRSE_hdcpverkeepoutwinend_shift                                       (13)
#define HDCP_KOWRSE_hdcpverkeepoutwinend_mask                                        (0x01FFE000)
#define HDCP_KOWRSE_hdcpverkeepoutwinend(data)                                       (0x01FFE000&((data)<<13))
#define HDCP_KOWRSE_hdcpverkeepoutwinend_src(data)                                   ((0x01FFE000&(data))>>13)
#define HDCP_KOWRSE_get_hdcpverkeepoutwinend(data)                                   ((0x01FFE000&(data))>>13)
#define HDCP_KOWRSE_write_en1_shift                                                  (12)
#define HDCP_KOWRSE_write_en1_mask                                                   (0x00001000)
#define HDCP_KOWRSE_write_en1(data)                                                  (0x00001000&((data)<<12))
#define HDCP_KOWRSE_write_en1_src(data)                                              ((0x00001000&(data))>>12)
#define HDCP_KOWRSE_get_write_en1(data)                                              ((0x00001000&(data))>>12)
#define HDCP_KOWRSE_hdcpvertkeepoutwinstart_shift                                    (0)
#define HDCP_KOWRSE_hdcpvertkeepoutwinstart_mask                                     (0x00000FFF)
#define HDCP_KOWRSE_hdcpvertkeepoutwinstart(data)                                    (0x00000FFF&((data)<<0))
#define HDCP_KOWRSE_hdcpvertkeepoutwinstart_src(data)                                ((0x00000FFF&(data))>>0)
#define HDCP_KOWRSE_get_hdcpvertkeepoutwinstart(data)                                ((0x00000FFF&(data))>>0)


#define HDCP_OWR                                                                     0x9800D0f8
#define HDCP_OWR_reg_addr                                                            "0x9800D0F8"
#define HDCP_OWR_reg                                                                 0x9800D0F8
#define set_HDCP_OWR_reg(data)   (*((volatile unsigned int*) HDCP_OWR_reg)=data)
#define get_HDCP_OWR_reg   (*((volatile unsigned int*) HDCP_OWR_reg))
#define HDCP_OWR_inst_adr                                                            "0x003E"
#define HDCP_OWR_inst                                                                0x003E
#define HDCP_OWR_write_en2_shift                                                     (25)
#define HDCP_OWR_write_en2_mask                                                      (0x02000000)
#define HDCP_OWR_write_en2(data)                                                     (0x02000000&((data)<<25))
#define HDCP_OWR_write_en2_src(data)                                                 ((0x02000000&(data))>>25)
#define HDCP_OWR_get_write_en2(data)                                                 ((0x02000000&(data))>>25)
#define HDCP_OWR_hdcpoppwinend_shift                                                 (13)
#define HDCP_OWR_hdcpoppwinend_mask                                                  (0x01FFE000)
#define HDCP_OWR_hdcpoppwinend(data)                                                 (0x01FFE000&((data)<<13))
#define HDCP_OWR_hdcpoppwinend_src(data)                                             ((0x01FFE000&(data))>>13)
#define HDCP_OWR_get_hdcpoppwinend(data)                                             ((0x01FFE000&(data))>>13)
#define HDCP_OWR_write_en1_shift                                                     (12)
#define HDCP_OWR_write_en1_mask                                                      (0x00001000)
#define HDCP_OWR_write_en1(data)                                                     (0x00001000&((data)<<12))
#define HDCP_OWR_write_en1_src(data)                                                 ((0x00001000&(data))>>12)
#define HDCP_OWR_get_write_en1(data)                                                 ((0x00001000&(data))>>12)
#define HDCP_OWR_hdcpoppwinstart_shift                                               (0)
#define HDCP_OWR_hdcpoppwinstart_mask                                                (0x00000FFF)
#define HDCP_OWR_hdcpoppwinstart(data)                                               (0x00000FFF&((data)<<0))
#define HDCP_OWR_hdcpoppwinstart_src(data)                                           ((0x00000FFF&(data))>>0)
#define HDCP_OWR_get_hdcpoppwinstart(data)                                           ((0x00000FFF&(data))>>0)


#define HDCP_CR                                                                      0x9800D0fc
#define HDCP_CR_reg_addr                                                             "0x9800D0FC"
#define HDCP_CR_reg                                                                  0x9800D0FC
#define set_HDCP_CR_reg(data)   (*((volatile unsigned int*) HDCP_CR_reg)=data)
#define get_HDCP_CR_reg   (*((volatile unsigned int*) HDCP_CR_reg))
#define HDCP_CR_inst_adr                                                             "0x003F"
#define HDCP_CR_inst                                                                 0x003F
#define HDCP_CR_write_en4_shift                                                      (7)
#define HDCP_CR_write_en4_mask                                                       (0x00000080)
#define HDCP_CR_write_en4(data)                                                      (0x00000080&((data)<<7))
#define HDCP_CR_write_en4_src(data)                                                  ((0x00000080&(data))>>7)
#define HDCP_CR_get_write_en4(data)                                                  ((0x00000080&(data))>>7)
#define HDCP_CR_en1_1_feature_shift                                                  (6)
#define HDCP_CR_en1_1_feature_mask                                                   (0x00000040)
#define HDCP_CR_en1_1_feature(data)                                                  (0x00000040&((data)<<6))
#define HDCP_CR_en1_1_feature_src(data)                                              ((0x00000040&(data))>>6)
#define HDCP_CR_get_en1_1_feature(data)                                              ((0x00000040&(data))>>6)
#define HDCP_CR_write_en3_shift                                                      (5)
#define HDCP_CR_write_en3_mask                                                       (0x00000020)
#define HDCP_CR_write_en3(data)                                                      (0x00000020&((data)<<5))
#define HDCP_CR_write_en3_src(data)                                                  ((0x00000020&(data))>>5)
#define HDCP_CR_get_write_en3(data)                                                  ((0x00000020&(data))>>5)
#define HDCP_CR_downstrisrepeater_shift                                              (4)
#define HDCP_CR_downstrisrepeater_mask                                               (0x00000010)
#define HDCP_CR_downstrisrepeater(data)                                              (0x00000010&((data)<<4))
#define HDCP_CR_downstrisrepeater_src(data)                                          ((0x00000010&(data))>>4)
#define HDCP_CR_get_downstrisrepeater(data)                                          ((0x00000010&(data))>>4)
#define HDCP_CR_write_en2_shift                                                      (3)
#define HDCP_CR_write_en2_mask                                                       (0x00000008)
#define HDCP_CR_write_en2(data)                                                      (0x00000008&((data)<<3))
#define HDCP_CR_write_en2_src(data)                                                  ((0x00000008&(data))>>3)
#define HDCP_CR_get_write_en2(data)                                                  ((0x00000008&(data))>>3)
#define HDCP_CR_aninfluencemode_shift                                                (2)
#define HDCP_CR_aninfluencemode_mask                                                 (0x00000004)
#define HDCP_CR_aninfluencemode(data)                                                (0x00000004&((data)<<2))
#define HDCP_CR_aninfluencemode_src(data)                                            ((0x00000004&(data))>>2)
#define HDCP_CR_get_aninfluencemode(data)                                            ((0x00000004&(data))>>2)
#define HDCP_CR_write_en1_shift                                                      (1)
#define HDCP_CR_write_en1_mask                                                       (0x00000002)
#define HDCP_CR_write_en1(data)                                                      (0x00000002&((data)<<1))
#define HDCP_CR_write_en1_src(data)                                                  ((0x00000002&(data))>>1)
#define HDCP_CR_get_write_en1(data)                                                  ((0x00000002&(data))>>1)
#define HDCP_CR_hdcp_encryptenable_shift                                             (0)
#define HDCP_CR_hdcp_encryptenable_mask                                              (0x00000001)
#define HDCP_CR_hdcp_encryptenable(data)                                             (0x00000001&((data)<<0))
#define HDCP_CR_hdcp_encryptenable_src(data)                                         ((0x00000001&(data))>>0)
#define HDCP_CR_get_hdcp_encryptenable(data)                                         ((0x00000001&(data))>>0)


#define HDCP_AUTH                                                                    0x9800D100
#define HDCP_AUTH_reg_addr                                                           "0x9800D100"
#define HDCP_AUTH_reg                                                                0x9800D100
#define set_HDCP_AUTH_reg(data)   (*((volatile unsigned int*) HDCP_AUTH_reg)=data)
#define get_HDCP_AUTH_reg   (*((volatile unsigned int*) HDCP_AUTH_reg))
#define HDCP_AUTH_inst_adr                                                           "0x0040"
#define HDCP_AUTH_inst                                                               0x0040
#define HDCP_AUTH_write_en9_shift                                                    (17)
#define HDCP_AUTH_write_en9_mask                                                     (0x00020000)
#define HDCP_AUTH_write_en9(data)                                                    (0x00020000&((data)<<17))
#define HDCP_AUTH_write_en9_src(data)                                                ((0x00020000&(data))>>17)
#define HDCP_AUTH_get_write_en9(data)                                                ((0x00020000&(data))>>17)
#define HDCP_AUTH_ddpken_shift                                                       (16)
#define HDCP_AUTH_ddpken_mask                                                        (0x00010000)
#define HDCP_AUTH_ddpken(data)                                                       (0x00010000&((data)<<16))
#define HDCP_AUTH_ddpken_src(data)                                                   ((0x00010000&(data))>>16)
#define HDCP_AUTH_get_ddpken(data)                                                   ((0x00010000&(data))>>16)
#define HDCP_AUTH_write_en8_shift                                                    (15)
#define HDCP_AUTH_write_en8_mask                                                     (0x00008000)
#define HDCP_AUTH_write_en8(data)                                                    (0x00008000&((data)<<15))
#define HDCP_AUTH_write_en8_src(data)                                                ((0x00008000&(data))>>15)
#define HDCP_AUTH_get_write_en8(data)                                                ((0x00008000&(data))>>15)
#define HDCP_AUTH_resetkmacc_shift                                                   (14)
#define HDCP_AUTH_resetkmacc_mask                                                    (0x00004000)
#define HDCP_AUTH_resetkmacc(data)                                                   (0x00004000&((data)<<14))
#define HDCP_AUTH_resetkmacc_src(data)                                               ((0x00004000&(data))>>14)
#define HDCP_AUTH_get_resetkmacc(data)                                               ((0x00004000&(data))>>14)
#define HDCP_AUTH_write_en7_shift                                                    (13)
#define HDCP_AUTH_write_en7_mask                                                     (0x00002000)
#define HDCP_AUTH_write_en7(data)                                                    (0x00002000&((data)<<13))
#define HDCP_AUTH_write_en7_src(data)                                                ((0x00002000&(data))>>13)
#define HDCP_AUTH_get_write_en7(data)                                                ((0x00002000&(data))>>13)
#define HDCP_AUTH_update_an_shift                                                    (12)
#define HDCP_AUTH_update_an_mask                                                     (0x00001000)
#define HDCP_AUTH_update_an(data)                                                    (0x00001000&((data)<<12))
#define HDCP_AUTH_update_an_src(data)                                                ((0x00001000&(data))>>12)
#define HDCP_AUTH_get_update_an(data)                                                ((0x00001000&(data))>>12)
#define HDCP_AUTH_write_en6_shift                                                    (11)
#define HDCP_AUTH_write_en6_mask                                                     (0x00000800)
#define HDCP_AUTH_write_en6(data)                                                    (0x00000800&((data)<<11))
#define HDCP_AUTH_write_en6_src(data)                                                ((0x00000800&(data))>>11)
#define HDCP_AUTH_get_write_en6(data)                                                ((0x00000800&(data))>>11)
#define HDCP_AUTH_aninfreq_shift                                                     (10)
#define HDCP_AUTH_aninfreq_mask                                                      (0x00000400)
#define HDCP_AUTH_aninfreq(data)                                                     (0x00000400&((data)<<10))
#define HDCP_AUTH_aninfreq_src(data)                                                 ((0x00000400&(data))>>10)
#define HDCP_AUTH_get_aninfreq(data)                                                 ((0x00000400&(data))>>10)
#define HDCP_AUTH_write_en5_shift                                                    (9)
#define HDCP_AUTH_write_en5_mask                                                     (0x00000200)
#define HDCP_AUTH_write_en5(data)                                                    (0x00000200&((data)<<9))
#define HDCP_AUTH_write_en5_src(data)                                                ((0x00000200&(data))>>9)
#define HDCP_AUTH_get_write_en5(data)                                                ((0x00000200&(data))>>9)
#define HDCP_AUTH_seedload_shift                                                     (8)
#define HDCP_AUTH_seedload_mask                                                      (0x00000100)
#define HDCP_AUTH_seedload(data)                                                     (0x00000100&((data)<<8))
#define HDCP_AUTH_seedload_src(data)                                                 ((0x00000100&(data))>>8)
#define HDCP_AUTH_get_seedload(data)                                                 ((0x00000100&(data))>>8)
#define HDCP_AUTH_write_en4_shift                                                    (7)
#define HDCP_AUTH_write_en4_mask                                                     (0x00000080)
#define HDCP_AUTH_write_en4(data)                                                    (0x00000080&((data)<<7))
#define HDCP_AUTH_write_en4_src(data)                                                ((0x00000080&(data))>>7)
#define HDCP_AUTH_get_write_en4(data)                                                ((0x00000080&(data))>>7)
#define HDCP_AUTH_deviceauthenticated_shift                                          (6)
#define HDCP_AUTH_deviceauthenticated_mask                                           (0x00000040)
#define HDCP_AUTH_deviceauthenticated(data)                                          (0x00000040&((data)<<6))
#define HDCP_AUTH_deviceauthenticated_src(data)                                      ((0x00000040&(data))>>6)
#define HDCP_AUTH_get_deviceauthenticated(data)                                      ((0x00000040&(data))>>6)
#define HDCP_AUTH_write_en3_shift                                                    (5)
#define HDCP_AUTH_write_en3_mask                                                     (0x00000020)
#define HDCP_AUTH_write_en3(data)                                                    (0x00000020&((data)<<5))
#define HDCP_AUTH_write_en3_src(data)                                                ((0x00000020&(data))>>5)
#define HDCP_AUTH_get_write_en3(data)                                                ((0x00000020&(data))>>5)
#define HDCP_AUTH_forcetounauthenticated_shift                                       (4)
#define HDCP_AUTH_forcetounauthenticated_mask                                        (0x00000010)
#define HDCP_AUTH_forcetounauthenticated(data)                                       (0x00000010&((data)<<4))
#define HDCP_AUTH_forcetounauthenticated_src(data)                                   ((0x00000010&(data))>>4)
#define HDCP_AUTH_get_forcetounauthenticated(data)                                   ((0x00000010&(data))>>4)
#define HDCP_AUTH_write_en2_shift                                                    (3)
#define HDCP_AUTH_write_en2_mask                                                     (0x00000008)
#define HDCP_AUTH_write_en2(data)                                                    (0x00000008&((data)<<3))
#define HDCP_AUTH_write_en2_src(data)                                                ((0x00000008&(data))>>3)
#define HDCP_AUTH_get_write_en2(data)                                                ((0x00000008&(data))>>3)
#define HDCP_AUTH_authcompute_shift                                                  (2)
#define HDCP_AUTH_authcompute_mask                                                   (0x00000004)
#define HDCP_AUTH_authcompute(data)                                                  (0x00000004&((data)<<2))
#define HDCP_AUTH_authcompute_src(data)                                              ((0x00000004&(data))>>2)
#define HDCP_AUTH_get_authcompute(data)                                              ((0x00000004&(data))>>2)
#define HDCP_AUTH_write_en1_shift                                                    (1)
#define HDCP_AUTH_write_en1_mask                                                     (0x00000002)
#define HDCP_AUTH_write_en1(data)                                                    (0x00000002&((data)<<1))
#define HDCP_AUTH_write_en1_src(data)                                                ((0x00000002&(data))>>1)
#define HDCP_AUTH_get_write_en1(data)                                                ((0x00000002&(data))>>1)
#define HDCP_AUTH_authrequest_shift                                                  (0)
#define HDCP_AUTH_authrequest_mask                                                   (0x00000001)
#define HDCP_AUTH_authrequest(data)                                                  (0x00000001&((data)<<0))
#define HDCP_AUTH_authrequest_src(data)                                              ((0x00000001&(data))>>0)
#define HDCP_AUTH_get_authrequest(data)                                              ((0x00000001&(data))>>0)


#define HDCP_SR                                                                      0x9800D104
#define HDCP_SR_reg_addr                                                             "0x9800D104"
#define HDCP_SR_reg                                                                  0x9800D104
#define set_HDCP_SR_reg(data)   (*((volatile unsigned int*) HDCP_SR_reg)=data)
#define get_HDCP_SR_reg   (*((volatile unsigned int*) HDCP_SR_reg))
#define HDCP_SR_inst_adr                                                             "0x0041"
#define HDCP_SR_inst                                                                 0x0041
#define HDCP_SR_hdcpcipherstate_shift                                                (24)
#define HDCP_SR_hdcpcipherstate_mask                                                 (0xFF000000)
#define HDCP_SR_hdcpcipherstate(data)                                                (0xFF000000&((data)<<24))
#define HDCP_SR_hdcpcipherstate_src(data)                                            ((0xFF000000&(data))>>24)
#define HDCP_SR_get_hdcpcipherstate(data)                                            ((0xFF000000&(data))>>24)
#define HDCP_SR_curdpkaccdone_shift                                                  (3)
#define HDCP_SR_curdpkaccdone_mask                                                   (0x00000008)
#define HDCP_SR_curdpkaccdone(data)                                                  (0x00000008&((data)<<3))
#define HDCP_SR_curdpkaccdone_src(data)                                              ((0x00000008&(data))>>3)
#define HDCP_SR_get_curdpkaccdone(data)                                              ((0x00000008&(data))>>3)
#define HDCP_SR_hdcp_encrypt_status_shift                                            (2)
#define HDCP_SR_hdcp_encrypt_status_mask                                             (0x00000004)
#define HDCP_SR_hdcp_encrypt_status(data)                                            (0x00000004&((data)<<2))
#define HDCP_SR_hdcp_encrypt_status_src(data)                                        ((0x00000004&(data))>>2)
#define HDCP_SR_get_hdcp_encrypt_status(data)                                        ((0x00000004&(data))>>2)
#define HDCP_SR_authenticatedok_shift                                                (1)
#define HDCP_SR_authenticatedok_mask                                                 (0x00000002)
#define HDCP_SR_authenticatedok(data)                                                (0x00000002&((data)<<1))
#define HDCP_SR_authenticatedok_src(data)                                            ((0x00000002&(data))>>1)
#define HDCP_SR_get_authenticatedok(data)                                            ((0x00000002&(data))>>1)
#define HDCP_SR_anready_shift                                                        (0)
#define HDCP_SR_anready_mask                                                         (0x00000001)
#define HDCP_SR_anready(data)                                                        (0x00000001&((data)<<0))
#define HDCP_SR_anready_src(data)                                                    ((0x00000001&(data))>>0)
#define HDCP_SR_get_anready(data)                                                    ((0x00000001&(data))>>0)


#define HDCP_ANLR                                                                    0x9800D108
#define HDCP_ANLR_reg_addr                                                           "0x9800D108"
#define HDCP_ANLR_reg                                                                0x9800D108
#define set_HDCP_ANLR_reg(data)   (*((volatile unsigned int*) HDCP_ANLR_reg)=data)
#define get_HDCP_ANLR_reg   (*((volatile unsigned int*) HDCP_ANLR_reg))
#define HDCP_ANLR_inst_adr                                                           "0x0042"
#define HDCP_ANLR_inst                                                               0x0042
#define HDCP_ANLR_anlsw_shift                                                        (0)
#define HDCP_ANLR_anlsw_mask                                                         (0xFFFFFFFF)
#define HDCP_ANLR_anlsw(data)                                                        (0xFFFFFFFF&((data)<<0))
#define HDCP_ANLR_anlsw_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define HDCP_ANLR_get_anlsw(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define HDCP_ANMR                                                                    0x9800D10c
#define HDCP_ANMR_reg_addr                                                           "0x9800D10C"
#define HDCP_ANMR_reg                                                                0x9800D10C
#define set_HDCP_ANMR_reg(data)   (*((volatile unsigned int*) HDCP_ANMR_reg)=data)
#define get_HDCP_ANMR_reg   (*((volatile unsigned int*) HDCP_ANMR_reg))
#define HDCP_ANMR_inst_adr                                                           "0x0043"
#define HDCP_ANMR_inst                                                               0x0043
#define HDCP_ANMR_anmsw_shift                                                        (0)
#define HDCP_ANMR_anmsw_mask                                                         (0xFFFFFFFF)
#define HDCP_ANMR_anmsw(data)                                                        (0xFFFFFFFF&((data)<<0))
#define HDCP_ANMR_anmsw_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define HDCP_ANMR_get_anmsw(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define HDCP_ANILR                                                                   0x9800D110
#define HDCP_ANILR_reg_addr                                                          "0x9800D110"
#define HDCP_ANILR_reg                                                               0x9800D110
#define set_HDCP_ANILR_reg(data)   (*((volatile unsigned int*) HDCP_ANILR_reg)=data)
#define get_HDCP_ANILR_reg   (*((volatile unsigned int*) HDCP_ANILR_reg))
#define HDCP_ANILR_inst_adr                                                          "0x0044"
#define HDCP_ANILR_inst                                                              0x0044
#define HDCP_ANILR_aninfluencelsw_shift                                              (0)
#define HDCP_ANILR_aninfluencelsw_mask                                               (0xFFFFFFFF)
#define HDCP_ANILR_aninfluencelsw(data)                                              (0xFFFFFFFF&((data)<<0))
#define HDCP_ANILR_aninfluencelsw_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define HDCP_ANILR_get_aninfluencelsw(data)                                          ((0xFFFFFFFF&(data))>>0)


#define HDCP_ANIMR                                                                   0x9800D114
#define HDCP_ANIMR_reg_addr                                                          "0x9800D114"
#define HDCP_ANIMR_reg                                                               0x9800D114
#define set_HDCP_ANIMR_reg(data)   (*((volatile unsigned int*) HDCP_ANIMR_reg)=data)
#define get_HDCP_ANIMR_reg   (*((volatile unsigned int*) HDCP_ANIMR_reg))
#define HDCP_ANIMR_inst_adr                                                          "0x0045"
#define HDCP_ANIMR_inst                                                              0x0045
#define HDCP_ANIMR_aninfluencemsw_shift                                              (0)
#define HDCP_ANIMR_aninfluencemsw_mask                                               (0xFFFFFFFF)
#define HDCP_ANIMR_aninfluencemsw(data)                                              (0xFFFFFFFF&((data)<<0))
#define HDCP_ANIMR_aninfluencemsw_src(data)                                          ((0xFFFFFFFF&(data))>>0)
#define HDCP_ANIMR_get_aninfluencemsw(data)                                          ((0xFFFFFFFF&(data))>>0)


#define HDCP_DPKLR                                                                   0x9800D118
#define HDCP_DPKLR_reg_addr                                                          "0x9800D118"
#define HDCP_DPKLR_reg                                                               0x9800D118
#define set_HDCP_DPKLR_reg(data)   (*((volatile unsigned int*) HDCP_DPKLR_reg)=data)
#define get_HDCP_DPKLR_reg   (*((volatile unsigned int*) HDCP_DPKLR_reg))
#define HDCP_DPKLR_inst_adr                                                          "0x0046"
#define HDCP_DPKLR_inst                                                              0x0046
#define HDCP_DPKLR_ddpklsb24_shift                                                   (8)
#define HDCP_DPKLR_ddpklsb24_mask                                                    (0xFFFFFF00)
#define HDCP_DPKLR_ddpklsb24(data)                                                   (0xFFFFFF00&((data)<<8))
#define HDCP_DPKLR_ddpklsb24_src(data)                                               ((0xFFFFFF00&(data))>>8)
#define HDCP_DPKLR_get_ddpklsb24(data)                                               ((0xFFFFFF00&(data))>>8)
#define HDCP_DPKLR_dpkencpnt_shift                                                   (0)
#define HDCP_DPKLR_dpkencpnt_mask                                                    (0x000000FF)
#define HDCP_DPKLR_dpkencpnt(data)                                                   (0x000000FF&((data)<<0))
#define HDCP_DPKLR_dpkencpnt_src(data)                                               ((0x000000FF&(data))>>0)
#define HDCP_DPKLR_get_dpkencpnt(data)                                               ((0x000000FF&(data))>>0)


#define HDCP_DPKMR                                                                   0x9800D11c
#define HDCP_DPKMR_reg_addr                                                          "0x9800D11C"
#define HDCP_DPKMR_reg                                                               0x9800D11C
#define set_HDCP_DPKMR_reg(data)   (*((volatile unsigned int*) HDCP_DPKMR_reg)=data)
#define get_HDCP_DPKMR_reg   (*((volatile unsigned int*) HDCP_DPKMR_reg))
#define HDCP_DPKMR_inst_adr                                                          "0x0047"
#define HDCP_DPKMR_inst                                                              0x0047
#define HDCP_DPKMR_ddpkmsw_shift                                                     (0)
#define HDCP_DPKMR_ddpkmsw_mask                                                      (0xFFFFFFFF)
#define HDCP_DPKMR_ddpkmsw(data)                                                     (0xFFFFFFFF&((data)<<0))
#define HDCP_DPKMR_ddpkmsw_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define HDCP_DPKMR_get_ddpkmsw(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define HDCP_LIR                                                                     0x9800D120
#define HDCP_LIR_reg_addr                                                            "0x9800D120"
#define HDCP_LIR_reg                                                                 0x9800D120
#define set_HDCP_LIR_reg(data)   (*((volatile unsigned int*) HDCP_LIR_reg)=data)
#define get_HDCP_LIR_reg   (*((volatile unsigned int*) HDCP_LIR_reg))
#define HDCP_LIR_inst_adr                                                            "0x0048"
#define HDCP_LIR_inst                                                                0x0048
#define HDCP_LIR_ri_shift                                                            (8)
#define HDCP_LIR_ri_mask                                                             (0x00FFFF00)
#define HDCP_LIR_ri(data)                                                            (0x00FFFF00&((data)<<8))
#define HDCP_LIR_ri_src(data)                                                        ((0x00FFFF00&(data))>>8)
#define HDCP_LIR_get_ri(data)                                                        ((0x00FFFF00&(data))>>8)
#define HDCP_LIR_pj_shift                                                            (0)
#define HDCP_LIR_pj_mask                                                             (0x000000FF)
#define HDCP_LIR_pj(data)                                                            (0x000000FF&((data)<<0))
#define HDCP_LIR_pj_src(data)                                                        ((0x000000FF&(data))>>0)
#define HDCP_LIR_get_pj(data)                                                        ((0x000000FF&(data))>>0)


#define HDCP_SHACR                                                                   0x9800D124
#define HDCP_SHACR_reg_addr                                                          "0x9800D124"
#define HDCP_SHACR_reg                                                               0x9800D124
#define set_HDCP_SHACR_reg(data)   (*((volatile unsigned int*) HDCP_SHACR_reg)=data)
#define get_HDCP_SHACR_reg   (*((volatile unsigned int*) HDCP_SHACR_reg))
#define HDCP_SHACR_inst_adr                                                          "0x0049"
#define HDCP_SHACR_inst                                                              0x0049
#define HDCP_SHACR_shastart_shift                                                    (3)
#define HDCP_SHACR_shastart_mask                                                     (0x00000008)
#define HDCP_SHACR_shastart(data)                                                    (0x00000008&((data)<<3))
#define HDCP_SHACR_shastart_src(data)                                                ((0x00000008&(data))>>3)
#define HDCP_SHACR_get_shastart(data)                                                ((0x00000008&(data))>>3)
#define HDCP_SHACR_shafirst_shift                                                    (2)
#define HDCP_SHACR_shafirst_mask                                                     (0x00000004)
#define HDCP_SHACR_shafirst(data)                                                    (0x00000004&((data)<<2))
#define HDCP_SHACR_shafirst_src(data)                                                ((0x00000004&(data))>>2)
#define HDCP_SHACR_get_shafirst(data)                                                ((0x00000004&(data))>>2)
#define HDCP_SHACR_rstshaptr_shift                                                   (1)
#define HDCP_SHACR_rstshaptr_mask                                                    (0x00000002)
#define HDCP_SHACR_rstshaptr(data)                                                   (0x00000002&((data)<<1))
#define HDCP_SHACR_rstshaptr_src(data)                                               ((0x00000002&(data))>>1)
#define HDCP_SHACR_get_rstshaptr(data)                                               ((0x00000002&(data))>>1)
#define HDCP_SHACR_write_data_shift                                                  (0)
#define HDCP_SHACR_write_data_mask                                                   (0x00000001)
#define HDCP_SHACR_write_data(data)                                                  (0x00000001&((data)<<0))
#define HDCP_SHACR_write_data_src(data)                                              ((0x00000001&(data))>>0)
#define HDCP_SHACR_get_write_data(data)                                              ((0x00000001&(data))>>0)


#define HDCP_SHARR                                                                   0x9800D128
#define HDCP_SHARR_reg_addr                                                          "0x9800D128"
#define HDCP_SHARR_reg                                                               0x9800D128
#define set_HDCP_SHARR_reg(data)   (*((volatile unsigned int*) HDCP_SHARR_reg)=data)
#define get_HDCP_SHARR_reg   (*((volatile unsigned int*) HDCP_SHARR_reg))
#define HDCP_SHARR_inst_adr                                                          "0x004A"
#define HDCP_SHARR_inst                                                              0x004A
#define HDCP_SHARR_vmatch_shift                                                      (1)
#define HDCP_SHARR_vmatch_mask                                                       (0x00000002)
#define HDCP_SHARR_vmatch(data)                                                      (0x00000002&((data)<<1))
#define HDCP_SHARR_vmatch_src(data)                                                  ((0x00000002&(data))>>1)
#define HDCP_SHARR_get_vmatch(data)                                                  ((0x00000002&(data))>>1)
#define HDCP_SHARR_shaready_shift                                                    (0)
#define HDCP_SHARR_shaready_mask                                                     (0x00000001)
#define HDCP_SHARR_shaready(data)                                                    (0x00000001&((data)<<0))
#define HDCP_SHARR_shaready_src(data)                                                ((0x00000001&(data))>>0)
#define HDCP_SHARR_get_shaready(data)                                                ((0x00000001&(data))>>0)


#define HDCP_SHADR                                                                   0x9800D12c
#define HDCP_SHADR_reg_addr                                                          "0x9800D12C"
#define HDCP_SHADR_reg                                                               0x9800D12C
#define set_HDCP_SHADR_reg(data)   (*((volatile unsigned int*) HDCP_SHADR_reg)=data)
#define get_HDCP_SHADR_reg   (*((volatile unsigned int*) HDCP_SHADR_reg))
#define HDCP_SHADR_inst_adr                                                          "0x004B"
#define HDCP_SHADR_inst                                                              0x004B
#define HDCP_SHADR_sha_data_shift                                                    (0)
#define HDCP_SHADR_sha_data_mask                                                     (0xFFFFFFFF)
#define HDCP_SHADR_sha_data(data)                                                    (0xFFFFFFFF&((data)<<0))
#define HDCP_SHADR_sha_data_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define HDCP_SHADR_get_sha_data(data)                                                ((0xFFFFFFFF&(data))>>0)


#define HDCP_MILSW                                                                   0x9800D130
#define HDCP_MILSW_reg_addr                                                          "0x9800D130"
#define HDCP_MILSW_reg                                                               0x9800D130
#define set_HDCP_MILSW_reg(data)   (*((volatile unsigned int*) HDCP_MILSW_reg)=data)
#define get_HDCP_MILSW_reg   (*((volatile unsigned int*) HDCP_MILSW_reg))
#define HDCP_MILSW_inst_adr                                                          "0x004C"
#define HDCP_MILSW_inst                                                              0x004C
#define HDCP_MILSW_milsw_shift                                                       (0)
#define HDCP_MILSW_milsw_mask                                                        (0xFFFFFFFF)
#define HDCP_MILSW_milsw(data)                                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_MILSW_milsw_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_MILSW_get_milsw(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_MIMSW                                                                   0x9800D134
#define HDCP_MIMSW_reg_addr                                                          "0x9800D134"
#define HDCP_MIMSW_reg                                                               0x9800D134
#define set_HDCP_MIMSW_reg(data)   (*((volatile unsigned int*) HDCP_MIMSW_reg)=data)
#define get_HDCP_MIMSW_reg   (*((volatile unsigned int*) HDCP_MIMSW_reg))
#define HDCP_MIMSW_inst_adr                                                          "0x004D"
#define HDCP_MIMSW_inst                                                              0x004D
#define HDCP_MIMSW_mimsw_shift                                                       (0)
#define HDCP_MIMSW_mimsw_mask                                                        (0xFFFFFFFF)
#define HDCP_MIMSW_mimsw(data)                                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_MIMSW_mimsw_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_MIMSW_get_mimsw(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_KMLSW                                                                   0x9800D138
#define HDCP_KMLSW_reg_addr                                                          "0x9800D138"
#define HDCP_KMLSW_reg                                                               0x9800D138
#define set_HDCP_KMLSW_reg(data)   (*((volatile unsigned int*) HDCP_KMLSW_reg)=data)
#define get_HDCP_KMLSW_reg   (*((volatile unsigned int*) HDCP_KMLSW_reg))
#define HDCP_KMLSW_inst_adr                                                          "0x004E"
#define HDCP_KMLSW_inst                                                              0x004E
#define HDCP_KMLSW_kmlsw_shift                                                       (0)
#define HDCP_KMLSW_kmlsw_mask                                                        (0xFFFFFFFF)
#define HDCP_KMLSW_kmlsw(data)                                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_KMLSW_kmlsw_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_KMLSW_get_kmlsw(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_KMMSW                                                                   0x9800D13c
#define HDCP_KMMSW_reg_addr                                                          "0x9800D13C"
#define HDCP_KMMSW_reg                                                               0x9800D13C
#define set_HDCP_KMMSW_reg(data)   (*((volatile unsigned int*) HDCP_KMMSW_reg)=data)
#define get_HDCP_KMMSW_reg   (*((volatile unsigned int*) HDCP_KMMSW_reg))
#define HDCP_KMMSW_inst_adr                                                          "0x004F"
#define HDCP_KMMSW_inst                                                              0x004F
#define HDCP_KMMSW_kmmsw_shift                                                       (0)
#define HDCP_KMMSW_kmmsw_mask                                                        (0xFFFFFFFF)
#define HDCP_KMMSW_kmmsw(data)                                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_KMMSW_kmmsw_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_KMMSW_get_kmmsw(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_CTRL                                                                0x9800D2b0
#define HDCP_2_2_CTRL_reg_addr                                                       "0x9800D2B0"
#define HDCP_2_2_CTRL_reg                                                            0x9800D2B0
#define set_HDCP_2_2_CTRL_reg(data)   (*((volatile unsigned int*) HDCP_2_2_CTRL_reg)=data)
#define get_HDCP_2_2_CTRL_reg   (*((volatile unsigned int*) HDCP_2_2_CTRL_reg))
#define HDCP_2_2_CTRL_inst_adr                                                       "0x00AC"
#define HDCP_2_2_CTRL_inst                                                           0x00AC
#define HDCP_2_2_CTRL_write_en5_shift                                                (9)
#define HDCP_2_2_CTRL_write_en5_mask                                                 (0x00000200)
#define HDCP_2_2_CTRL_write_en5(data)                                                (0x00000200&((data)<<9))
#define HDCP_2_2_CTRL_write_en5_src(data)                                            ((0x00000200&(data))>>9)
#define HDCP_2_2_CTRL_get_write_en5(data)                                            ((0x00000200&(data))>>9)
#define HDCP_2_2_CTRL_pkt_vdo_cnt_add_shift                                          (8)
#define HDCP_2_2_CTRL_pkt_vdo_cnt_add_mask                                           (0x00000100)
#define HDCP_2_2_CTRL_pkt_vdo_cnt_add(data)                                          (0x00000100&((data)<<8))
#define HDCP_2_2_CTRL_pkt_vdo_cnt_add_src(data)                                      ((0x00000100&(data))>>8)
#define HDCP_2_2_CTRL_get_pkt_vdo_cnt_add(data)                                      ((0x00000100&(data))>>8)
#define HDCP_2_2_CTRL_write_en4_shift                                                (7)
#define HDCP_2_2_CTRL_write_en4_mask                                                 (0x00000080)
#define HDCP_2_2_CTRL_write_en4(data)                                                (0x00000080&((data)<<7))
#define HDCP_2_2_CTRL_write_en4_src(data)                                            ((0x00000080&(data))>>7)
#define HDCP_2_2_CTRL_get_write_en4(data)                                            ((0x00000080&(data))>>7)
#define HDCP_2_2_CTRL_hdcp_2_2_en_shift                                              (6)
#define HDCP_2_2_CTRL_hdcp_2_2_en_mask                                               (0x00000040)
#define HDCP_2_2_CTRL_hdcp_2_2_en(data)                                              (0x00000040&((data)<<6))
#define HDCP_2_2_CTRL_hdcp_2_2_en_src(data)                                          ((0x00000040&(data))>>6)
#define HDCP_2_2_CTRL_get_hdcp_2_2_en(data)                                          ((0x00000040&(data))>>6)
#define HDCP_2_2_CTRL_write_en3_shift                                                (5)
#define HDCP_2_2_CTRL_write_en3_mask                                                 (0x00000020)
#define HDCP_2_2_CTRL_write_en3(data)                                                (0x00000020&((data)<<5))
#define HDCP_2_2_CTRL_write_en3_src(data)                                            ((0x00000020&(data))>>5)
#define HDCP_2_2_CTRL_get_write_en3(data)                                            ((0x00000020&(data))>>5)
#define HDCP_2_2_CTRL_aes_sw_en_shift                                                (4)
#define HDCP_2_2_CTRL_aes_sw_en_mask                                                 (0x00000010)
#define HDCP_2_2_CTRL_aes_sw_en(data)                                                (0x00000010&((data)<<4))
#define HDCP_2_2_CTRL_aes_sw_en_src(data)                                            ((0x00000010&(data))>>4)
#define HDCP_2_2_CTRL_get_aes_sw_en(data)                                            ((0x00000010&(data))>>4)
#define HDCP_2_2_CTRL_write_en2_shift                                                (3)
#define HDCP_2_2_CTRL_write_en2_mask                                                 (0x00000008)
#define HDCP_2_2_CTRL_write_en2(data)                                                (0x00000008&((data)<<3))
#define HDCP_2_2_CTRL_write_en2_src(data)                                            ((0x00000008&(data))>>3)
#define HDCP_2_2_CTRL_get_write_en2(data)                                            ((0x00000008&(data))>>3)
#define HDCP_2_2_CTRL_aes_sw_start1_shift                                            (2)
#define HDCP_2_2_CTRL_aes_sw_start1_mask                                             (0x00000004)
#define HDCP_2_2_CTRL_aes_sw_start1(data)                                            (0x00000004&((data)<<2))
#define HDCP_2_2_CTRL_aes_sw_start1_src(data)                                        ((0x00000004&(data))>>2)
#define HDCP_2_2_CTRL_get_aes_sw_start1(data)                                        ((0x00000004&(data))>>2)
#define HDCP_2_2_CTRL_write_en1_shift                                                (1)
#define HDCP_2_2_CTRL_write_en1_mask                                                 (0x00000002)
#define HDCP_2_2_CTRL_write_en1(data)                                                (0x00000002&((data)<<1))
#define HDCP_2_2_CTRL_write_en1_src(data)                                            ((0x00000002&(data))>>1)
#define HDCP_2_2_CTRL_get_write_en1(data)                                            ((0x00000002&(data))>>1)
#define HDCP_2_2_CTRL_aes_sw_start2_shift                                            (0)
#define HDCP_2_2_CTRL_aes_sw_start2_mask                                             (0x00000001)
#define HDCP_2_2_CTRL_aes_sw_start2(data)                                            (0x00000001&((data)<<0))
#define HDCP_2_2_CTRL_aes_sw_start2_src(data)                                        ((0x00000001&(data))>>0)
#define HDCP_2_2_CTRL_get_aes_sw_start2(data)                                        ((0x00000001&(data))>>0)


#define HDCP_2_2_STATUS                                                              0x9800D2b4
#define HDCP_2_2_STATUS_reg_addr                                                     "0x9800D2B4"
#define HDCP_2_2_STATUS_reg                                                          0x9800D2B4
#define set_HDCP_2_2_STATUS_reg(data)   (*((volatile unsigned int*) HDCP_2_2_STATUS_reg)=data)
#define get_HDCP_2_2_STATUS_reg   (*((volatile unsigned int*) HDCP_2_2_STATUS_reg))
#define HDCP_2_2_STATUS_inst_adr                                                     "0x00AD"
#define HDCP_2_2_STATUS_inst                                                         0x00AD
#define HDCP_2_2_STATUS_rgs_sw_done_1_shift                                          (1)
#define HDCP_2_2_STATUS_rgs_sw_done_1_mask                                           (0x00000002)
#define HDCP_2_2_STATUS_rgs_sw_done_1(data)                                          (0x00000002&((data)<<1))
#define HDCP_2_2_STATUS_rgs_sw_done_1_src(data)                                      ((0x00000002&(data))>>1)
#define HDCP_2_2_STATUS_get_rgs_sw_done_1(data)                                      ((0x00000002&(data))>>1)
#define HDCP_2_2_STATUS_rgs_sw_done_2_shift                                          (0)
#define HDCP_2_2_STATUS_rgs_sw_done_2_mask                                           (0x00000001)
#define HDCP_2_2_STATUS_rgs_sw_done_2(data)                                          (0x00000001&((data)<<0))
#define HDCP_2_2_STATUS_rgs_sw_done_2_src(data)                                      ((0x00000001&(data))>>0)
#define HDCP_2_2_STATUS_get_rgs_sw_done_2(data)                                      ((0x00000001&(data))>>0)


#define HDCP_2_2_SW_DATA_1_1                                                         0x9800D2b8
#define HDCP_2_2_SW_DATA_1_1_reg_addr                                                "0x9800D2B8"
#define HDCP_2_2_SW_DATA_1_1_reg                                                     0x9800D2B8
#define set_HDCP_2_2_SW_DATA_1_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_1_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_1_reg))
#define HDCP_2_2_SW_DATA_1_1_inst_adr                                                "0x00AE"
#define HDCP_2_2_SW_DATA_1_1_inst                                                    0x00AE
#define HDCP_2_2_SW_DATA_1_1_sw_data_1_1_shift                                       (0)
#define HDCP_2_2_SW_DATA_1_1_sw_data_1_1_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_1_1_sw_data_1_1(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_1_1_sw_data_1_1_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_1_1_get_sw_data_1_1(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_1_2                                                         0x9800D2bc
#define HDCP_2_2_SW_DATA_1_2_reg_addr                                                "0x9800D2BC"
#define HDCP_2_2_SW_DATA_1_2_reg                                                     0x9800D2BC
#define set_HDCP_2_2_SW_DATA_1_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_1_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_2_reg))
#define HDCP_2_2_SW_DATA_1_2_inst_adr                                                "0x00AF"
#define HDCP_2_2_SW_DATA_1_2_inst                                                    0x00AF
#define HDCP_2_2_SW_DATA_1_2_sw_data_1_2_shift                                       (0)
#define HDCP_2_2_SW_DATA_1_2_sw_data_1_2_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_1_2_sw_data_1_2(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_1_2_sw_data_1_2_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_1_2_get_sw_data_1_2(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_1_3                                                         0x9800D2c0
#define HDCP_2_2_SW_DATA_1_3_reg_addr                                                "0x9800D2C0"
#define HDCP_2_2_SW_DATA_1_3_reg                                                     0x9800D2C0
#define set_HDCP_2_2_SW_DATA_1_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_1_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_3_reg))
#define HDCP_2_2_SW_DATA_1_3_inst_adr                                                "0x00B0"
#define HDCP_2_2_SW_DATA_1_3_inst                                                    0x00B0
#define HDCP_2_2_SW_DATA_1_3_sw_data_1_3_shift                                       (0)
#define HDCP_2_2_SW_DATA_1_3_sw_data_1_3_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_1_3_sw_data_1_3(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_1_3_sw_data_1_3_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_1_3_get_sw_data_1_3(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_1_4                                                         0x9800D2c4
#define HDCP_2_2_SW_DATA_1_4_reg_addr                                                "0x9800D2C4"
#define HDCP_2_2_SW_DATA_1_4_reg                                                     0x9800D2C4
#define set_HDCP_2_2_SW_DATA_1_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_1_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_1_4_reg))
#define HDCP_2_2_SW_DATA_1_4_inst_adr                                                "0x00B1"
#define HDCP_2_2_SW_DATA_1_4_inst                                                    0x00B1
#define HDCP_2_2_SW_DATA_1_4_sw_data_1_4_shift                                       (0)
#define HDCP_2_2_SW_DATA_1_4_sw_data_1_4_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_1_4_sw_data_1_4(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_1_4_sw_data_1_4_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_1_4_get_sw_data_1_4(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_2_1                                                         0x9800D2c8
#define HDCP_2_2_SW_DATA_2_1_reg_addr                                                "0x9800D2C8"
#define HDCP_2_2_SW_DATA_2_1_reg                                                     0x9800D2C8
#define set_HDCP_2_2_SW_DATA_2_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_2_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_1_reg))
#define HDCP_2_2_SW_DATA_2_1_inst_adr                                                "0x00B2"
#define HDCP_2_2_SW_DATA_2_1_inst                                                    0x00B2
#define HDCP_2_2_SW_DATA_2_1_sw_data_2_1_shift                                       (0)
#define HDCP_2_2_SW_DATA_2_1_sw_data_2_1_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_2_1_sw_data_2_1(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_2_1_sw_data_2_1_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_2_1_get_sw_data_2_1(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_2_2                                                         0x9800D2cc
#define HDCP_2_2_SW_DATA_2_2_reg_addr                                                "0x9800D2CC"
#define HDCP_2_2_SW_DATA_2_2_reg                                                     0x9800D2CC
#define set_HDCP_2_2_SW_DATA_2_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_2_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_2_reg))
#define HDCP_2_2_SW_DATA_2_2_inst_adr                                                "0x00B3"
#define HDCP_2_2_SW_DATA_2_2_inst                                                    0x00B3
#define HDCP_2_2_SW_DATA_2_2_sw_data_2_2_shift                                       (0)
#define HDCP_2_2_SW_DATA_2_2_sw_data_2_2_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_2_2_sw_data_2_2(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_2_2_sw_data_2_2_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_2_2_get_sw_data_2_2(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_2_3                                                         0x9800D2d0
#define HDCP_2_2_SW_DATA_2_3_reg_addr                                                "0x9800D2D0"
#define HDCP_2_2_SW_DATA_2_3_reg                                                     0x9800D2D0
#define set_HDCP_2_2_SW_DATA_2_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_2_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_3_reg))
#define HDCP_2_2_SW_DATA_2_3_inst_adr                                                "0x00B4"
#define HDCP_2_2_SW_DATA_2_3_inst                                                    0x00B4
#define HDCP_2_2_SW_DATA_2_3_sw_data_2_3_shift                                       (0)
#define HDCP_2_2_SW_DATA_2_3_sw_data_2_3_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_2_3_sw_data_2_3(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_2_3_sw_data_2_3_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_2_3_get_sw_data_2_3(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_2_4                                                         0x9800D2d4
#define HDCP_2_2_SW_DATA_2_4_reg_addr                                                "0x9800D2D4"
#define HDCP_2_2_SW_DATA_2_4_reg                                                     0x9800D2D4
#define set_HDCP_2_2_SW_DATA_2_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_2_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_2_4_reg))
#define HDCP_2_2_SW_DATA_2_4_inst_adr                                                "0x00B5"
#define HDCP_2_2_SW_DATA_2_4_inst                                                    0x00B5
#define HDCP_2_2_SW_DATA_2_4_sw_data_2_4_shift                                       (0)
#define HDCP_2_2_SW_DATA_2_4_sw_data_2_4_mask                                        (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_2_4_sw_data_2_4(data)                                       (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_2_4_sw_data_2_4_src(data)                                   ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_2_4_get_sw_data_2_4(data)                                   ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_1_1                                                          0x9800D2d8
#define HDCP_2_2_SW_KEY_1_1_reg_addr                                                 "0x9800D2D8"
#define HDCP_2_2_SW_KEY_1_1_reg                                                      0x9800D2D8
#define set_HDCP_2_2_SW_KEY_1_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_1_reg)=data)
#define get_HDCP_2_2_SW_KEY_1_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_1_reg))
#define HDCP_2_2_SW_KEY_1_1_inst_adr                                                 "0x00B6"
#define HDCP_2_2_SW_KEY_1_1_inst                                                     0x00B6
#define HDCP_2_2_SW_KEY_1_1_sw_key_1_1_shift                                         (0)
#define HDCP_2_2_SW_KEY_1_1_sw_key_1_1_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_1_1_sw_key_1_1(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_1_1_sw_key_1_1_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_1_1_get_sw_key_1_1(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_1_2                                                          0x9800D2dc
#define HDCP_2_2_SW_KEY_1_2_reg_addr                                                 "0x9800D2DC"
#define HDCP_2_2_SW_KEY_1_2_reg                                                      0x9800D2DC
#define set_HDCP_2_2_SW_KEY_1_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_2_reg)=data)
#define get_HDCP_2_2_SW_KEY_1_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_2_reg))
#define HDCP_2_2_SW_KEY_1_2_inst_adr                                                 "0x00B7"
#define HDCP_2_2_SW_KEY_1_2_inst                                                     0x00B7
#define HDCP_2_2_SW_KEY_1_2_sw_key_1_2_shift                                         (0)
#define HDCP_2_2_SW_KEY_1_2_sw_key_1_2_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_1_2_sw_key_1_2(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_1_2_sw_key_1_2_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_1_2_get_sw_key_1_2(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_1_3                                                          0x9800D2e0
#define HDCP_2_2_SW_KEY_1_3_reg_addr                                                 "0x9800D2E0"
#define HDCP_2_2_SW_KEY_1_3_reg                                                      0x9800D2E0
#define set_HDCP_2_2_SW_KEY_1_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_3_reg)=data)
#define get_HDCP_2_2_SW_KEY_1_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_3_reg))
#define HDCP_2_2_SW_KEY_1_3_inst_adr                                                 "0x00B8"
#define HDCP_2_2_SW_KEY_1_3_inst                                                     0x00B8
#define HDCP_2_2_SW_KEY_1_3_sw_key_1_3_shift                                         (0)
#define HDCP_2_2_SW_KEY_1_3_sw_key_1_3_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_1_3_sw_key_1_3(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_1_3_sw_key_1_3_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_1_3_get_sw_key_1_3(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_1_4                                                          0x9800D2e4
#define HDCP_2_2_SW_KEY_1_4_reg_addr                                                 "0x9800D2E4"
#define HDCP_2_2_SW_KEY_1_4_reg                                                      0x9800D2E4
#define set_HDCP_2_2_SW_KEY_1_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_4_reg)=data)
#define get_HDCP_2_2_SW_KEY_1_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_1_4_reg))
#define HDCP_2_2_SW_KEY_1_4_inst_adr                                                 "0x00B9"
#define HDCP_2_2_SW_KEY_1_4_inst                                                     0x00B9
#define HDCP_2_2_SW_KEY_1_4_sw_key_1_4_shift                                         (0)
#define HDCP_2_2_SW_KEY_1_4_sw_key_1_4_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_1_4_sw_key_1_4(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_1_4_sw_key_1_4_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_1_4_get_sw_key_1_4(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_2_1                                                          0x9800D2e8
#define HDCP_2_2_SW_KEY_2_1_reg_addr                                                 "0x9800D2E8"
#define HDCP_2_2_SW_KEY_2_1_reg                                                      0x9800D2E8
#define set_HDCP_2_2_SW_KEY_2_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_1_reg)=data)
#define get_HDCP_2_2_SW_KEY_2_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_1_reg))
#define HDCP_2_2_SW_KEY_2_1_inst_adr                                                 "0x00BA"
#define HDCP_2_2_SW_KEY_2_1_inst                                                     0x00BA
#define HDCP_2_2_SW_KEY_2_1_sw_key_2_1_shift                                         (0)
#define HDCP_2_2_SW_KEY_2_1_sw_key_2_1_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_2_1_sw_key_2_1(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_2_1_sw_key_2_1_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_2_1_get_sw_key_2_1(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_2_2                                                          0x9800D2ec
#define HDCP_2_2_SW_KEY_2_2_reg_addr                                                 "0x9800D2EC"
#define HDCP_2_2_SW_KEY_2_2_reg                                                      0x9800D2EC
#define set_HDCP_2_2_SW_KEY_2_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_2_reg)=data)
#define get_HDCP_2_2_SW_KEY_2_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_2_reg))
#define HDCP_2_2_SW_KEY_2_2_inst_adr                                                 "0x00BB"
#define HDCP_2_2_SW_KEY_2_2_inst                                                     0x00BB
#define HDCP_2_2_SW_KEY_2_2_sw_key_2_2_shift                                         (0)
#define HDCP_2_2_SW_KEY_2_2_sw_key_2_2_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_2_2_sw_key_2_2(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_2_2_sw_key_2_2_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_2_2_get_sw_key_2_2(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_2_3                                                          0x9800D2f0
#define HDCP_2_2_SW_KEY_2_3_reg_addr                                                 "0x9800D2F0"
#define HDCP_2_2_SW_KEY_2_3_reg                                                      0x9800D2F0
#define set_HDCP_2_2_SW_KEY_2_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_3_reg)=data)
#define get_HDCP_2_2_SW_KEY_2_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_3_reg))
#define HDCP_2_2_SW_KEY_2_3_inst_adr                                                 "0x00BC"
#define HDCP_2_2_SW_KEY_2_3_inst                                                     0x00BC
#define HDCP_2_2_SW_KEY_2_3_sw_key_2_3_shift                                         (0)
#define HDCP_2_2_SW_KEY_2_3_sw_key_2_3_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_2_3_sw_key_2_3(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_2_3_sw_key_2_3_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_2_3_get_sw_key_2_3(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_KEY_2_4                                                          0x9800D2f4
#define HDCP_2_2_SW_KEY_2_4_reg_addr                                                 "0x9800D2F4"
#define HDCP_2_2_SW_KEY_2_4_reg                                                      0x9800D2F4
#define set_HDCP_2_2_SW_KEY_2_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_4_reg)=data)
#define get_HDCP_2_2_SW_KEY_2_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_KEY_2_4_reg))
#define HDCP_2_2_SW_KEY_2_4_inst_adr                                                 "0x00BD"
#define HDCP_2_2_SW_KEY_2_4_inst                                                     0x00BD
#define HDCP_2_2_SW_KEY_2_4_sw_key_2_4_shift                                         (0)
#define HDCP_2_2_SW_KEY_2_4_sw_key_2_4_mask                                          (0xFFFFFFFF)
#define HDCP_2_2_SW_KEY_2_4_sw_key_2_4(data)                                         (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_KEY_2_4_sw_key_2_4_src(data)                                     ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_KEY_2_4_get_sw_key_2_4(data)                                     ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_1_1                                                     0x9800D2f8
#define HDCP_2_2_SW_DATA_XOR_1_1_reg_addr                                            "0x9800D2F8"
#define HDCP_2_2_SW_DATA_XOR_1_1_reg                                                 0x9800D2F8
#define set_HDCP_2_2_SW_DATA_XOR_1_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_1_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_1_reg))
#define HDCP_2_2_SW_DATA_XOR_1_1_inst_adr                                            "0x00BE"
#define HDCP_2_2_SW_DATA_XOR_1_1_inst                                                0x00BE
#define HDCP_2_2_SW_DATA_XOR_1_1_sw_data_xor_1_1_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_1_1_sw_data_xor_1_1_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_1_1_sw_data_xor_1_1(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_1_1_sw_data_xor_1_1_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_1_1_get_sw_data_xor_1_1(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_1_2                                                     0x9800D2fc
#define HDCP_2_2_SW_DATA_XOR_1_2_reg_addr                                            "0x9800D2FC"
#define HDCP_2_2_SW_DATA_XOR_1_2_reg                                                 0x9800D2FC
#define set_HDCP_2_2_SW_DATA_XOR_1_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_1_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_2_reg))
#define HDCP_2_2_SW_DATA_XOR_1_2_inst_adr                                            "0x00BF"
#define HDCP_2_2_SW_DATA_XOR_1_2_inst                                                0x00BF
#define HDCP_2_2_SW_DATA_XOR_1_2_sw_data_xor_1_2_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_1_2_sw_data_xor_1_2_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_1_2_sw_data_xor_1_2(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_1_2_sw_data_xor_1_2_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_1_2_get_sw_data_xor_1_2(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_1_3                                                     0x9800D300
#define HDCP_2_2_SW_DATA_XOR_1_3_reg_addr                                            "0x9800D300"
#define HDCP_2_2_SW_DATA_XOR_1_3_reg                                                 0x9800D300
#define set_HDCP_2_2_SW_DATA_XOR_1_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_1_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_3_reg))
#define HDCP_2_2_SW_DATA_XOR_1_3_inst_adr                                            "0x00C0"
#define HDCP_2_2_SW_DATA_XOR_1_3_inst                                                0x00C0
#define HDCP_2_2_SW_DATA_XOR_1_3_sw_data_xor_1_3_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_1_3_sw_data_xor_1_3_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_1_3_sw_data_xor_1_3(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_1_3_sw_data_xor_1_3_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_1_3_get_sw_data_xor_1_3(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_1_4                                                     0x9800D304
#define HDCP_2_2_SW_DATA_XOR_1_4_reg_addr                                            "0x9800D304"
#define HDCP_2_2_SW_DATA_XOR_1_4_reg                                                 0x9800D304
#define set_HDCP_2_2_SW_DATA_XOR_1_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_1_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_1_4_reg))
#define HDCP_2_2_SW_DATA_XOR_1_4_inst_adr                                            "0x00C1"
#define HDCP_2_2_SW_DATA_XOR_1_4_inst                                                0x00C1
#define HDCP_2_2_SW_DATA_XOR_1_4_sw_data_xor_1_4_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_1_4_sw_data_xor_1_4_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_1_4_sw_data_xor_1_4(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_1_4_sw_data_xor_1_4_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_1_4_get_sw_data_xor_1_4(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_2_1                                                     0x9800D308
#define HDCP_2_2_SW_DATA_XOR_2_1_reg_addr                                            "0x9800D308"
#define HDCP_2_2_SW_DATA_XOR_2_1_reg                                                 0x9800D308
#define set_HDCP_2_2_SW_DATA_XOR_2_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_2_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_1_reg))
#define HDCP_2_2_SW_DATA_XOR_2_1_inst_adr                                            "0x00C2"
#define HDCP_2_2_SW_DATA_XOR_2_1_inst                                                0x00C2
#define HDCP_2_2_SW_DATA_XOR_2_1_sw_data_xor_2_1_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_2_1_sw_data_xor_2_1_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_2_1_sw_data_xor_2_1(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_2_1_sw_data_xor_2_1_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_2_1_get_sw_data_xor_2_1(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_2_2                                                     0x9800D30c
#define HDCP_2_2_SW_DATA_XOR_2_2_reg_addr                                            "0x9800D30C"
#define HDCP_2_2_SW_DATA_XOR_2_2_reg                                                 0x9800D30C
#define set_HDCP_2_2_SW_DATA_XOR_2_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_2_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_2_reg))
#define HDCP_2_2_SW_DATA_XOR_2_2_inst_adr                                            "0x00C3"
#define HDCP_2_2_SW_DATA_XOR_2_2_inst                                                0x00C3
#define HDCP_2_2_SW_DATA_XOR_2_2_sw_data_xor_2_2_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_2_2_sw_data_xor_2_2_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_2_2_sw_data_xor_2_2(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_2_2_sw_data_xor_2_2_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_2_2_get_sw_data_xor_2_2(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_2_3                                                     0x9800D310
#define HDCP_2_2_SW_DATA_XOR_2_3_reg_addr                                            "0x9800D310"
#define HDCP_2_2_SW_DATA_XOR_2_3_reg                                                 0x9800D310
#define set_HDCP_2_2_SW_DATA_XOR_2_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_2_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_3_reg))
#define HDCP_2_2_SW_DATA_XOR_2_3_inst_adr                                            "0x00C4"
#define HDCP_2_2_SW_DATA_XOR_2_3_inst                                                0x00C4
#define HDCP_2_2_SW_DATA_XOR_2_3_sw_data_xor_2_3_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_2_3_sw_data_xor_2_3_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_2_3_sw_data_xor_2_3(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_2_3_sw_data_xor_2_3_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_2_3_get_sw_data_xor_2_3(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_XOR_2_4                                                     0x9800D314
#define HDCP_2_2_SW_DATA_XOR_2_4_reg_addr                                            "0x9800D314"
#define HDCP_2_2_SW_DATA_XOR_2_4_reg                                                 0x9800D314
#define set_HDCP_2_2_SW_DATA_XOR_2_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_XOR_2_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_XOR_2_4_reg))
#define HDCP_2_2_SW_DATA_XOR_2_4_inst_adr                                            "0x00C5"
#define HDCP_2_2_SW_DATA_XOR_2_4_inst                                                0x00C5
#define HDCP_2_2_SW_DATA_XOR_2_4_sw_data_xor_2_4_shift                               (0)
#define HDCP_2_2_SW_DATA_XOR_2_4_sw_data_xor_2_4_mask                                (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_XOR_2_4_sw_data_xor_2_4(data)                               (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_XOR_2_4_sw_data_xor_2_4_src(data)                           ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_XOR_2_4_get_sw_data_xor_2_4(data)                           ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_1_1                                                     0x9800D318
#define HDCP_2_2_SW_DATA_OUT_1_1_reg_addr                                            "0x9800D318"
#define HDCP_2_2_SW_DATA_OUT_1_1_reg                                                 0x9800D318
#define set_HDCP_2_2_SW_DATA_OUT_1_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_1_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_1_reg))
#define HDCP_2_2_SW_DATA_OUT_1_1_inst_adr                                            "0x00C6"
#define HDCP_2_2_SW_DATA_OUT_1_1_inst                                                0x00C6
#define HDCP_2_2_SW_DATA_OUT_1_1_data_out_1_1_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_1_1_data_out_1_1_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_1_1_data_out_1_1(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_1_1_data_out_1_1_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_1_1_get_data_out_1_1(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_1_2                                                     0x9800D31c
#define HDCP_2_2_SW_DATA_OUT_1_2_reg_addr                                            "0x9800D31C"
#define HDCP_2_2_SW_DATA_OUT_1_2_reg                                                 0x9800D31C
#define set_HDCP_2_2_SW_DATA_OUT_1_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_1_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_2_reg))
#define HDCP_2_2_SW_DATA_OUT_1_2_inst_adr                                            "0x00C7"
#define HDCP_2_2_SW_DATA_OUT_1_2_inst                                                0x00C7
#define HDCP_2_2_SW_DATA_OUT_1_2_data_out_1_2_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_1_2_data_out_1_2_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_1_2_data_out_1_2(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_1_2_data_out_1_2_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_1_2_get_data_out_1_2(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_1_3                                                     0x9800D320
#define HDCP_2_2_SW_DATA_OUT_1_3_reg_addr                                            "0x9800D320"
#define HDCP_2_2_SW_DATA_OUT_1_3_reg                                                 0x9800D320
#define set_HDCP_2_2_SW_DATA_OUT_1_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_1_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_3_reg))
#define HDCP_2_2_SW_DATA_OUT_1_3_inst_adr                                            "0x00C8"
#define HDCP_2_2_SW_DATA_OUT_1_3_inst                                                0x00C8
#define HDCP_2_2_SW_DATA_OUT_1_3_data_out_1_3_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_1_3_data_out_1_3_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_1_3_data_out_1_3(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_1_3_data_out_1_3_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_1_3_get_data_out_1_3(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_1_4                                                     0x9800D324
#define HDCP_2_2_SW_DATA_OUT_1_4_reg_addr                                            "0x9800D324"
#define HDCP_2_2_SW_DATA_OUT_1_4_reg                                                 0x9800D324
#define set_HDCP_2_2_SW_DATA_OUT_1_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_1_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_1_4_reg))
#define HDCP_2_2_SW_DATA_OUT_1_4_inst_adr                                            "0x00C9"
#define HDCP_2_2_SW_DATA_OUT_1_4_inst                                                0x00C9
#define HDCP_2_2_SW_DATA_OUT_1_4_data_out_1_4_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_1_4_data_out_1_4_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_1_4_data_out_1_4(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_1_4_data_out_1_4_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_1_4_get_data_out_1_4(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_2_1                                                     0x9800D328
#define HDCP_2_2_SW_DATA_OUT_2_1_reg_addr                                            "0x9800D328"
#define HDCP_2_2_SW_DATA_OUT_2_1_reg                                                 0x9800D328
#define set_HDCP_2_2_SW_DATA_OUT_2_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_1_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_2_1_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_1_reg))
#define HDCP_2_2_SW_DATA_OUT_2_1_inst_adr                                            "0x00CA"
#define HDCP_2_2_SW_DATA_OUT_2_1_inst                                                0x00CA
#define HDCP_2_2_SW_DATA_OUT_2_1_data_out_2_1_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_2_1_data_out_2_1_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_2_1_data_out_2_1(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_2_1_data_out_2_1_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_2_1_get_data_out_2_1(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_2_2                                                     0x9800D32c
#define HDCP_2_2_SW_DATA_OUT_2_2_reg_addr                                            "0x9800D32C"
#define HDCP_2_2_SW_DATA_OUT_2_2_reg                                                 0x9800D32C
#define set_HDCP_2_2_SW_DATA_OUT_2_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_2_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_2_2_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_2_reg))
#define HDCP_2_2_SW_DATA_OUT_2_2_inst_adr                                            "0x00CB"
#define HDCP_2_2_SW_DATA_OUT_2_2_inst                                                0x00CB
#define HDCP_2_2_SW_DATA_OUT_2_2_data_out_2_2_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_2_2_data_out_2_2_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_2_2_data_out_2_2(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_2_2_data_out_2_2_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_2_2_get_data_out_2_2(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_2_3                                                     0x9800D330
#define HDCP_2_2_SW_DATA_OUT_2_3_reg_addr                                            "0x9800D330"
#define HDCP_2_2_SW_DATA_OUT_2_3_reg                                                 0x9800D330
#define set_HDCP_2_2_SW_DATA_OUT_2_3_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_3_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_2_3_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_3_reg))
#define HDCP_2_2_SW_DATA_OUT_2_3_inst_adr                                            "0x00CC"
#define HDCP_2_2_SW_DATA_OUT_2_3_inst                                                0x00CC
#define HDCP_2_2_SW_DATA_OUT_2_3_data_out_2_3_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_2_3_data_out_2_3_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_2_3_data_out_2_3(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_2_3_data_out_2_3_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_2_3_get_data_out_2_3(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_SW_DATA_OUT_2_4                                                     0x9800D334
#define HDCP_2_2_SW_DATA_OUT_2_4_reg_addr                                            "0x9800D334"
#define HDCP_2_2_SW_DATA_OUT_2_4_reg                                                 0x9800D334
#define set_HDCP_2_2_SW_DATA_OUT_2_4_reg(data)   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_4_reg)=data)
#define get_HDCP_2_2_SW_DATA_OUT_2_4_reg   (*((volatile unsigned int*) HDCP_2_2_SW_DATA_OUT_2_4_reg))
#define HDCP_2_2_SW_DATA_OUT_2_4_inst_adr                                            "0x00CD"
#define HDCP_2_2_SW_DATA_OUT_2_4_inst                                                0x00CD
#define HDCP_2_2_SW_DATA_OUT_2_4_data_out_2_4_shift                                  (0)
#define HDCP_2_2_SW_DATA_OUT_2_4_data_out_2_4_mask                                   (0xFFFFFFFF)
#define HDCP_2_2_SW_DATA_OUT_2_4_data_out_2_4(data)                                  (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_SW_DATA_OUT_2_4_data_out_2_4_src(data)                              ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_SW_DATA_OUT_2_4_get_data_out_2_4(data)                              ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_HW_RIV_1                                                            0x9800D338
#define HDCP_2_2_HW_RIV_1_reg_addr                                                   "0x9800D338"
#define HDCP_2_2_HW_RIV_1_reg                                                        0x9800D338
#define set_HDCP_2_2_HW_RIV_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_RIV_1_reg)=data)
#define get_HDCP_2_2_HW_RIV_1_reg   (*((volatile unsigned int*) HDCP_2_2_HW_RIV_1_reg))
#define HDCP_2_2_HW_RIV_1_inst_adr                                                   "0x00CE"
#define HDCP_2_2_HW_RIV_1_inst                                                       0x00CE
#define HDCP_2_2_HW_RIV_1_hw_riv_1_1_shift                                           (0)
#define HDCP_2_2_HW_RIV_1_hw_riv_1_1_mask                                            (0xFFFFFFFF)
#define HDCP_2_2_HW_RIV_1_hw_riv_1_1(data)                                           (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_HW_RIV_1_hw_riv_1_1_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_HW_RIV_1_get_hw_riv_1_1(data)                                       ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_HW_RIV_2                                                            0x9800D33c
#define HDCP_2_2_HW_RIV_2_reg_addr                                                   "0x9800D33C"
#define HDCP_2_2_HW_RIV_2_reg                                                        0x9800D33C
#define set_HDCP_2_2_HW_RIV_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_RIV_2_reg)=data)
#define get_HDCP_2_2_HW_RIV_2_reg   (*((volatile unsigned int*) HDCP_2_2_HW_RIV_2_reg))
#define HDCP_2_2_HW_RIV_2_inst_adr                                                   "0x00CF"
#define HDCP_2_2_HW_RIV_2_inst                                                       0x00CF
#define HDCP_2_2_HW_RIV_2_hw_riv_1_2_shift                                           (0)
#define HDCP_2_2_HW_RIV_2_hw_riv_1_2_mask                                            (0xFFFFFFFF)
#define HDCP_2_2_HW_RIV_2_hw_riv_1_2(data)                                           (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_HW_RIV_2_hw_riv_1_2_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_HW_RIV_2_get_hw_riv_1_2(data)                                       ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_HW_FRAME_NUM_1                                                      0x9800D340
#define HDCP_2_2_HW_FRAME_NUM_1_reg_addr                                             "0x9800D340"
#define HDCP_2_2_HW_FRAME_NUM_1_reg                                                  0x9800D340
#define set_HDCP_2_2_HW_FRAME_NUM_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_1_reg)=data)
#define get_HDCP_2_2_HW_FRAME_NUM_1_reg   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_1_reg))
#define HDCP_2_2_HW_FRAME_NUM_1_inst_adr                                             "0x00D0"
#define HDCP_2_2_HW_FRAME_NUM_1_inst                                                 0x00D0
#define HDCP_2_2_HW_FRAME_NUM_1_frame_num_1_shift                                    (0)
#define HDCP_2_2_HW_FRAME_NUM_1_frame_num_1_mask                                     (0xFFFFFFFF)
#define HDCP_2_2_HW_FRAME_NUM_1_frame_num_1(data)                                    (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_HW_FRAME_NUM_1_frame_num_1_src(data)                                ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_HW_FRAME_NUM_1_get_frame_num_1(data)                                ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_HW_FRAME_NUM_2                                                      0x9800D344
#define HDCP_2_2_HW_FRAME_NUM_2_reg_addr                                             "0x9800D344"
#define HDCP_2_2_HW_FRAME_NUM_2_reg                                                  0x9800D344
#define set_HDCP_2_2_HW_FRAME_NUM_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_2_reg)=data)
#define get_HDCP_2_2_HW_FRAME_NUM_2_reg   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_2_reg))
#define HDCP_2_2_HW_FRAME_NUM_2_inst_adr                                             "0x00D1"
#define HDCP_2_2_HW_FRAME_NUM_2_inst                                                 0x00D1
#define HDCP_2_2_HW_FRAME_NUM_2_frame_num_2_shift                                    (0)
#define HDCP_2_2_HW_FRAME_NUM_2_frame_num_2_mask                                     (0x0000003F)
#define HDCP_2_2_HW_FRAME_NUM_2_frame_num_2(data)                                    (0x0000003F&((data)<<0))
#define HDCP_2_2_HW_FRAME_NUM_2_frame_num_2_src(data)                                ((0x0000003F&(data))>>0)
#define HDCP_2_2_HW_FRAME_NUM_2_get_frame_num_2(data)                                ((0x0000003F&(data))>>0)


#define HDCP_2_2_HW_FRAME_NUM_ADD_1                                                  0x9800D348
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_reg_addr                                         "0x9800D348"
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_reg                                              0x9800D348
#define set_HDCP_2_2_HW_FRAME_NUM_ADD_1_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_ADD_1_reg)=data)
#define get_HDCP_2_2_HW_FRAME_NUM_ADD_1_reg   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_ADD_1_reg))
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_inst_adr                                         "0x00D2"
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_inst                                             0x00D2
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_frame_num_add_1_shift                            (0)
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_frame_num_add_1_mask                             (0xFFFFFFFF)
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_frame_num_add_1(data)                            (0xFFFFFFFF&((data)<<0))
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_frame_num_add_1_src(data)                        ((0xFFFFFFFF&(data))>>0)
#define HDCP_2_2_HW_FRAME_NUM_ADD_1_get_frame_num_add_1(data)                        ((0xFFFFFFFF&(data))>>0)


#define HDCP_2_2_HW_FRAME_NUM_ADD_2                                                  0x9800D34c
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_reg_addr                                         "0x9800D34C"
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_reg                                              0x9800D34C
#define set_HDCP_2_2_HW_FRAME_NUM_ADD_2_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_ADD_2_reg)=data)
#define get_HDCP_2_2_HW_FRAME_NUM_ADD_2_reg   (*((volatile unsigned int*) HDCP_2_2_HW_FRAME_NUM_ADD_2_reg))
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_inst_adr                                         "0x00D3"
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_inst                                             0x00D3
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_frame_num_add_2_shift                            (0)
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_frame_num_add_2_mask                             (0x0000003F)
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_frame_num_add_2(data)                            (0x0000003F&((data)<<0))
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_frame_num_add_2_src(data)                        ((0x0000003F&(data))>>0)
#define HDCP_2_2_HW_FRAME_NUM_ADD_2_get_frame_num_add_2(data)                        ((0x0000003F&(data))>>0)


#define HDCP_2_2_HW_DATA_NUM                                                         0x9800D350
#define HDCP_2_2_HW_DATA_NUM_reg_addr                                                "0x9800D350"
#define HDCP_2_2_HW_DATA_NUM_reg                                                     0x9800D350
#define set_HDCP_2_2_HW_DATA_NUM_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_DATA_NUM_reg)=data)
#define get_HDCP_2_2_HW_DATA_NUM_reg   (*((volatile unsigned int*) HDCP_2_2_HW_DATA_NUM_reg))
#define HDCP_2_2_HW_DATA_NUM_inst_adr                                                "0x00D4"
#define HDCP_2_2_HW_DATA_NUM_inst                                                    0x00D4
#define HDCP_2_2_HW_DATA_NUM_data_num_shift                                          (0)
#define HDCP_2_2_HW_DATA_NUM_data_num_mask                                           (0x03FFFFFF)
#define HDCP_2_2_HW_DATA_NUM_data_num(data)                                          (0x03FFFFFF&((data)<<0))
#define HDCP_2_2_HW_DATA_NUM_data_num_src(data)                                      ((0x03FFFFFF&(data))>>0)
#define HDCP_2_2_HW_DATA_NUM_get_data_num(data)                                      ((0x03FFFFFF&(data))>>0)


#define HDCP_2_2_HW_DATA_NUM_ADD                                                     0x9800D354
#define HDCP_2_2_HW_DATA_NUM_ADD_reg_addr                                            "0x9800D354"
#define HDCP_2_2_HW_DATA_NUM_ADD_reg                                                 0x9800D354
#define set_HDCP_2_2_HW_DATA_NUM_ADD_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_DATA_NUM_ADD_reg)=data)
#define get_HDCP_2_2_HW_DATA_NUM_ADD_reg   (*((volatile unsigned int*) HDCP_2_2_HW_DATA_NUM_ADD_reg))
#define HDCP_2_2_HW_DATA_NUM_ADD_inst_adr                                            "0x00D5"
#define HDCP_2_2_HW_DATA_NUM_ADD_inst                                                0x00D5
#define HDCP_2_2_HW_DATA_NUM_ADD_data_num_add_shift                                  (0)
#define HDCP_2_2_HW_DATA_NUM_ADD_data_num_add_mask                                   (0x03FFFFFF)
#define HDCP_2_2_HW_DATA_NUM_ADD_data_num_add(data)                                  (0x03FFFFFF&((data)<<0))
#define HDCP_2_2_HW_DATA_NUM_ADD_data_num_add_src(data)                              ((0x03FFFFFF&(data))>>0)
#define HDCP_2_2_HW_DATA_NUM_ADD_get_data_num_add(data)                              ((0x03FFFFFF&(data))>>0)


#define HDCP_2_2_HW_FREE_RUN                                                         0x9800D358
#define HDCP_2_2_HW_FREE_RUN_reg_addr                                                "0x9800D358"
#define HDCP_2_2_HW_FREE_RUN_reg                                                     0x9800D358
#define set_HDCP_2_2_HW_FREE_RUN_reg(data)   (*((volatile unsigned int*) HDCP_2_2_HW_FREE_RUN_reg)=data)
#define get_HDCP_2_2_HW_FREE_RUN_reg   (*((volatile unsigned int*) HDCP_2_2_HW_FREE_RUN_reg))
#define HDCP_2_2_HW_FREE_RUN_inst_adr                                                "0x00D6"
#define HDCP_2_2_HW_FREE_RUN_inst                                                    0x00D6
#define HDCP_2_2_HW_FREE_RUN_write_en2_shift                                         (28)
#define HDCP_2_2_HW_FREE_RUN_write_en2_mask                                          (0x10000000)
#define HDCP_2_2_HW_FREE_RUN_write_en2(data)                                         (0x10000000&((data)<<28))
#define HDCP_2_2_HW_FREE_RUN_write_en2_src(data)                                     ((0x10000000&(data))>>28)
#define HDCP_2_2_HW_FREE_RUN_get_write_en2(data)                                     ((0x10000000&(data))>>28)
#define HDCP_2_2_HW_FREE_RUN_free_run_mod_en_shift                                   (27)
#define HDCP_2_2_HW_FREE_RUN_free_run_mod_en_mask                                    (0x08000000)
#define HDCP_2_2_HW_FREE_RUN_free_run_mod_en(data)                                   (0x08000000&((data)<<27))
#define HDCP_2_2_HW_FREE_RUN_free_run_mod_en_src(data)                               ((0x08000000&(data))>>27)
#define HDCP_2_2_HW_FREE_RUN_get_free_run_mod_en(data)                               ((0x08000000&(data))>>27)
#define HDCP_2_2_HW_FREE_RUN_write_en1_shift                                         (26)
#define HDCP_2_2_HW_FREE_RUN_write_en1_mask                                          (0x04000000)
#define HDCP_2_2_HW_FREE_RUN_write_en1(data)                                         (0x04000000&((data)<<26))
#define HDCP_2_2_HW_FREE_RUN_write_en1_src(data)                                     ((0x04000000&(data))>>26)
#define HDCP_2_2_HW_FREE_RUN_get_write_en1(data)                                     ((0x04000000&(data))>>26)
#define HDCP_2_2_HW_FREE_RUN_keep_out_win_shift                                      (0)
#define HDCP_2_2_HW_FREE_RUN_keep_out_win_mask                                       (0x03FFFFFF)
#define HDCP_2_2_HW_FREE_RUN_keep_out_win(data)                                      (0x03FFFFFF&((data)<<0))
#define HDCP_2_2_HW_FREE_RUN_keep_out_win_src(data)                                  ((0x03FFFFFF&(data))>>0)
#define HDCP_2_2_HW_FREE_RUN_get_keep_out_win(data)                                  ((0x03FFFFFF&(data))>>0)


#define DBG                                                                          0x9800D140
#define DBG_reg_addr                                                                 "0x9800D140"
#define DBG_reg                                                                      0x9800D140
#define set_DBG_reg(data)   (*((volatile unsigned int*) DBG_reg)=data)
#define get_DBG_reg   (*((volatile unsigned int*) DBG_reg))
#define DBG_inst_adr                                                                 "0x0050"
#define DBG_inst                                                                     0x0050
#define DBG_chsel0_shift                                                             (4)
#define DBG_chsel0_mask                                                              (0x000000F0)
#define DBG_chsel0(data)                                                             (0x000000F0&((data)<<4))
#define DBG_chsel0_src(data)                                                         ((0x000000F0&(data))>>4)
#define DBG_get_chsel0(data)                                                         ((0x000000F0&(data))>>4)
#define DBG_chsel1_shift                                                             (0)
#define DBG_chsel1_mask                                                              (0x0000000F)
#define DBG_chsel1(data)                                                             (0x0000000F&((data)<<0))
#define DBG_chsel1_src(data)                                                         ((0x0000000F&(data))>>0)
#define DBG_get_chsel1(data)                                                         ((0x0000000F&(data))>>0)


#define HDMI_DUMMY_0                                                                  144
#define HDMI_DUMMY_1                                                                  148
#define HDMI_DUMMY_0_reg_addr                                                         "0x9800D144"
#define HDMI_DUMMY_1_reg_addr                                                         "0x9800D148"
#define HDMI_DUMMY_0_reg                                                              0x9800D144
#define HDMI_DUMMY_1_reg                                                              0x9800D148
#define HDMI_set_DUMMY_0_reg(data)   (*((volatile unsigned int*) DUMMY_0_reg)=data)
#define HDMI_set_DUMMY_1_reg(data)   (*((volatile unsigned int*) DUMMY_1_reg)=data)
#define HDMI_get_DUMMY_0_reg   (*((volatile unsigned int*) DUMMY_0_reg))
#define HDMI_get_DUMMY_1_reg   (*((volatile unsigned int*) DUMMY_1_reg))
#define HDMI_DUMMY_0_inst_adr                                                         "0x0051"
#define HDMI_DUMMY_1_inst_adr                                                         "0x0052"
#define HDMI_DUMMY_0_inst                                                             0x0051
#define HDMI_DUMMY_1_inst                                                             0x0052
#define HDMI_DUMMY_dummy_shift                                                        (0)
#define HDMI_DUMMY_dummy_mask                                                         (0xFFFFFFFF)
#define HDMI_DUMMY_dummy(data)                                                        (0xFFFFFFFF&((data)<<0))
#define HDMI_DUMMY_dummy_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define HDMI_DUMMY_get_dummy(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define PHY                                                                          14C
#define PHY_reg_addr                                                                 "0x9800D14C"
#define PHY_reg                                                                      0x9800D14C
#define set_PHY_reg(data)   (*((volatile unsigned int*) PHY_reg)=data)
#define get_PHY_reg   (*((volatile unsigned int*) PHY_reg))
#define PHY_inst_adr                                                                 "0x0053"
#define PHY_inst                                                                     0x0053
#define PHY_test_mode_shift                                                          (1)
#define PHY_test_mode_mask                                                           (0x00000002)
#define PHY_test_mode(data)                                                          (0x00000002&((data)<<1))
#define PHY_test_mode_src(data)                                                      ((0x00000002&(data))>>1)
#define PHY_get_test_mode(data)                                                      ((0x00000002&(data))>>1)
#define PHY_data_realign_shift                                                       (0)
#define PHY_data_realign_mask                                                        (0x00000001)
#define PHY_data_realign(data)                                                       (0x00000001&((data)<<0))
#define PHY_data_realign_src(data)                                                   ((0x00000001&(data))>>0)
#define PHY_get_data_realign(data)                                                   ((0x00000001&(data))>>0)


#define H_PARA1                                                                      234
#define H_PARA1_reg_addr                                                             "0x9800D234"
#define H_PARA1_reg                                                                  0x9800D234
#define set_H_PARA1_reg(data)   (*((volatile unsigned int*) H_PARA1_reg)=data)
#define get_H_PARA1_reg   (*((volatile unsigned int*) H_PARA1_reg))
#define H_PARA1_inst_adr                                                             "0x008D"
#define H_PARA1_inst                                                                 0x008D
#define H_PARA1_hblank_shift                                                         (16)
#define H_PARA1_hblank_mask                                                          (0x3FFF0000)
#define H_PARA1_hblank(data)                                                         (0x3FFF0000&((data)<<16))
#define H_PARA1_hblank_src(data)                                                     ((0x3FFF0000&(data))>>16)
#define H_PARA1_get_hblank(data)                                                     ((0x3FFF0000&(data))>>16)
#define H_PARA1_hactive_shift                                                        (0)
#define H_PARA1_hactive_mask                                                         (0x00003FFF)
#define H_PARA1_hactive(data)                                                        (0x00003FFF&((data)<<0))
#define H_PARA1_hactive_src(data)                                                    ((0x00003FFF&(data))>>0)
#define H_PARA1_get_hactive(data)                                                    ((0x00003FFF&(data))>>0)


#define H_PARA2                                                                      238
#define H_PARA2_reg_addr                                                             "0x9800D238"
#define H_PARA2_reg                                                                  0x9800D238
#define set_H_PARA2_reg(data)   (*((volatile unsigned int*) H_PARA2_reg)=data)
#define get_H_PARA2_reg   (*((volatile unsigned int*) H_PARA2_reg))
#define H_PARA2_inst_adr                                                             "0x008E"
#define H_PARA2_inst                                                                 0x008E
#define H_PARA2_hsync_shift                                                          (16)
#define H_PARA2_hsync_mask                                                           (0x3FFF0000)
#define H_PARA2_hsync(data)                                                          (0x3FFF0000&((data)<<16))
#define H_PARA2_hsync_src(data)                                                      ((0x3FFF0000&(data))>>16)
#define H_PARA2_get_hsync(data)                                                      ((0x3FFF0000&(data))>>16)
#define H_PARA2_hfront_shift                                                         (0)
#define H_PARA2_hfront_mask                                                          (0x00003FFF)
#define H_PARA2_hfront(data)                                                         (0x00003FFF&((data)<<0))
#define H_PARA2_hfront_src(data)                                                     ((0x00003FFF&(data))>>0)
#define H_PARA2_get_hfront(data)                                                     ((0x00003FFF&(data))>>0)


#define H_PARA3                                                                      23c
#define H_PARA3_reg_addr                                                             "0x9800D23C"
#define H_PARA3_reg                                                                  0x9800D23C
#define set_H_PARA3_reg(data)   (*((volatile unsigned int*) H_PARA3_reg)=data)
#define get_H_PARA3_reg   (*((volatile unsigned int*) H_PARA3_reg))
#define H_PARA3_inst_adr                                                             "0x008F"
#define H_PARA3_inst                                                                 0x008F
#define H_PARA3_hback_shift                                                          (0)
#define H_PARA3_hback_mask                                                           (0x00003FFF)
#define H_PARA3_hback(data)                                                          (0x00003FFF&((data)<<0))
#define H_PARA3_hback_src(data)                                                      ((0x00003FFF&(data))>>0)
#define H_PARA3_get_hback(data)                                                      ((0x00003FFF&(data))>>0)


#define V_PARA1                                                                      240
#define V_PARA1_reg_addr                                                             "0x9800D240"
#define V_PARA1_reg                                                                  0x9800D240
#define set_V_PARA1_reg(data)   (*((volatile unsigned int*) V_PARA1_reg)=data)
#define get_V_PARA1_reg   (*((volatile unsigned int*) V_PARA1_reg))
#define V_PARA1_inst_adr                                                             "0x0090"
#define V_PARA1_inst                                                                 0x0090
#define V_PARA1_Vact_video_shift                                                     (16)
#define V_PARA1_Vact_video_mask                                                      (0x3FFF0000)
#define V_PARA1_Vact_video(data)                                                     (0x3FFF0000&((data)<<16))
#define V_PARA1_Vact_video_src(data)                                                 ((0x3FFF0000&(data))>>16)
#define V_PARA1_get_Vact_video(data)                                                 ((0x3FFF0000&(data))>>16)
#define V_PARA1_vactive_shift                                                        (0)
#define V_PARA1_vactive_mask                                                         (0x00003FFF)
#define V_PARA1_vactive(data)                                                        (0x00003FFF&((data)<<0))
#define V_PARA1_vactive_src(data)                                                    ((0x00003FFF&(data))>>0)
#define V_PARA1_get_vactive(data)                                                    ((0x00003FFF&(data))>>0)


#define V_PARA2                                                                      244
#define V_PARA2_reg_addr                                                             "0x9800D244"
#define V_PARA2_reg                                                                  0x9800D244
#define set_V_PARA2_reg(data)   (*((volatile unsigned int*) V_PARA2_reg)=data)
#define get_V_PARA2_reg   (*((volatile unsigned int*) V_PARA2_reg))
#define V_PARA2_inst_adr                                                             "0x0091"
#define V_PARA2_inst                                                                 0x0091
#define V_PARA2_Vact_space1_shift                                                    (16)
#define V_PARA2_Vact_space1_mask                                                     (0x3FFF0000)
#define V_PARA2_Vact_space1(data)                                                    (0x3FFF0000&((data)<<16))
#define V_PARA2_Vact_space1_src(data)                                                ((0x3FFF0000&(data))>>16)
#define V_PARA2_get_Vact_space1(data)                                                ((0x3FFF0000&(data))>>16)
#define V_PARA2_Vact_space_shift                                                     (0)
#define V_PARA2_Vact_space_mask                                                      (0x00003FFF)
#define V_PARA2_Vact_space(data)                                                     (0x00003FFF&((data)<<0))
#define V_PARA2_Vact_space_src(data)                                                 ((0x00003FFF&(data))>>0)
#define V_PARA2_get_Vact_space(data)                                                 ((0x00003FFF&(data))>>0)


#define V_PARA3                                                                      248
#define V_PARA3_reg_addr                                                             "0x9800D248"
#define V_PARA3_reg                                                                  0x9800D248
#define set_V_PARA3_reg(data)   (*((volatile unsigned int*) V_PARA3_reg)=data)
#define get_V_PARA3_reg   (*((volatile unsigned int*) V_PARA3_reg))
#define V_PARA3_inst_adr                                                             "0x0092"
#define V_PARA3_inst                                                                 0x0092
#define V_PARA3_Vblank3_shift                                                        (16)
#define V_PARA3_Vblank3_mask                                                         (0x3FFF0000)
#define V_PARA3_Vblank3(data)                                                        (0x3FFF0000&((data)<<16))
#define V_PARA3_Vblank3_src(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA3_get_Vblank3(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA3_Vact_space2_shift                                                    (0)
#define V_PARA3_Vact_space2_mask                                                     (0x00003FFF)
#define V_PARA3_Vact_space2(data)                                                    (0x00003FFF&((data)<<0))
#define V_PARA3_Vact_space2_src(data)                                                ((0x00003FFF&(data))>>0)
#define V_PARA3_get_Vact_space2(data)                                                ((0x00003FFF&(data))>>0)


#define V_PARA4                                                                      24C
#define V_PARA4_reg_addr                                                             "0x9800D24C"
#define V_PARA4_reg                                                                  0x9800D24C
#define set_V_PARA4_reg(data)   (*((volatile unsigned int*) V_PARA4_reg)=data)
#define get_V_PARA4_reg   (*((volatile unsigned int*) V_PARA4_reg))
#define V_PARA4_inst_adr                                                             "0x0093"
#define V_PARA4_inst                                                                 0x0093
#define V_PARA4_vsync_shift                                                          (16)
#define V_PARA4_vsync_mask                                                           (0x3FFF0000)
#define V_PARA4_vsync(data)                                                          (0x3FFF0000&((data)<<16))
#define V_PARA4_vsync_src(data)                                                      ((0x3FFF0000&(data))>>16)
#define V_PARA4_get_vsync(data)                                                      ((0x3FFF0000&(data))>>16)
#define V_PARA4_vblank_shift                                                         (0)
#define V_PARA4_vblank_mask                                                          (0x00003FFF)
#define V_PARA4_vblank(data)                                                         (0x00003FFF&((data)<<0))
#define V_PARA4_vblank_src(data)                                                     ((0x00003FFF&(data))>>0)
#define V_PARA4_get_vblank(data)                                                     ((0x00003FFF&(data))>>0)


#define V_PARA5                                                                      250
#define V_PARA5_reg_addr                                                             "0x9800D250"
#define V_PARA5_reg                                                                  0x9800D250
#define set_V_PARA5_reg(data)   (*((volatile unsigned int*) V_PARA5_reg)=data)
#define get_V_PARA5_reg   (*((volatile unsigned int*) V_PARA5_reg))
#define V_PARA5_inst_adr                                                             "0x0094"
#define V_PARA5_inst                                                                 0x0094
#define V_PARA5_vback_shift                                                          (16)
#define V_PARA5_vback_mask                                                           (0x3FFF0000)
#define V_PARA5_vback(data)                                                          (0x3FFF0000&((data)<<16))
#define V_PARA5_vback_src(data)                                                      ((0x3FFF0000&(data))>>16)
#define V_PARA5_get_vback(data)                                                      ((0x3FFF0000&(data))>>16)
#define V_PARA5_vfront_shift                                                         (0)
#define V_PARA5_vfront_mask                                                          (0x00003FFF)
#define V_PARA5_vfront(data)                                                         (0x00003FFF&((data)<<0))
#define V_PARA5_vfront_src(data)                                                     ((0x00003FFF&(data))>>0)
#define V_PARA5_get_vfront(data)                                                     ((0x00003FFF&(data))>>0)


#define V_PARA6                                                                      254
#define V_PARA6_reg_addr                                                             "0x9800D254"
#define V_PARA6_reg                                                                  0x9800D254
#define set_V_PARA6_reg(data)   (*((volatile unsigned int*) V_PARA6_reg)=data)
#define get_V_PARA6_reg   (*((volatile unsigned int*) V_PARA6_reg))
#define V_PARA6_inst_adr                                                             "0x0095"
#define V_PARA6_inst                                                                 0x0095
#define V_PARA6_Vsync1_shift                                                         (16)
#define V_PARA6_Vsync1_mask                                                          (0x3FFF0000)
#define V_PARA6_Vsync1(data)                                                         (0x3FFF0000&((data)<<16))
#define V_PARA6_Vsync1_src(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA6_get_Vsync1(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA6_Vblank1_shift                                                        (0)
#define V_PARA6_Vblank1_mask                                                         (0x00003FFF)
#define V_PARA6_Vblank1(data)                                                        (0x00003FFF&((data)<<0))
#define V_PARA6_Vblank1_src(data)                                                    ((0x00003FFF&(data))>>0)
#define V_PARA6_get_Vblank1(data)                                                    ((0x00003FFF&(data))>>0)


#define V_PARA7                                                                      258
#define V_PARA7_reg_addr                                                             "0x9800D258"
#define V_PARA7_reg                                                                  0x9800D258
#define set_V_PARA7_reg(data)   (*((volatile unsigned int*) V_PARA7_reg)=data)
#define get_V_PARA7_reg   (*((volatile unsigned int*) V_PARA7_reg))
#define V_PARA7_inst_adr                                                             "0x0096"
#define V_PARA7_inst                                                                 0x0096
#define V_PARA7_Vback1_shift                                                         (16)
#define V_PARA7_Vback1_mask                                                          (0x3FFF0000)
#define V_PARA7_Vback1(data)                                                         (0x3FFF0000&((data)<<16))
#define V_PARA7_Vback1_src(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA7_get_Vback1(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA7_Vfront1_shift                                                        (0)
#define V_PARA7_Vfront1_mask                                                         (0x00003FFF)
#define V_PARA7_Vfront1(data)                                                        (0x00003FFF&((data)<<0))
#define V_PARA7_Vfront1_src(data)                                                    ((0x00003FFF&(data))>>0)
#define V_PARA7_get_Vfront1(data)                                                    ((0x00003FFF&(data))>>0)


#define V_PARA8                                                                      25C
#define V_PARA8_reg_addr                                                             "0x9800D25C"
#define V_PARA8_reg                                                                  0x9800D25C
#define set_V_PARA8_reg(data)   (*((volatile unsigned int*) V_PARA8_reg)=data)
#define get_V_PARA8_reg   (*((volatile unsigned int*) V_PARA8_reg))
#define V_PARA8_inst_adr                                                             "0x0097"
#define V_PARA8_inst                                                                 0x0097
#define V_PARA8_Vsync2_shift                                                         (16)
#define V_PARA8_Vsync2_mask                                                          (0x3FFF0000)
#define V_PARA8_Vsync2(data)                                                         (0x3FFF0000&((data)<<16))
#define V_PARA8_Vsync2_src(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA8_get_Vsync2(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA8_Vblank2_shift                                                        (0)
#define V_PARA8_Vblank2_mask                                                         (0x00003FFF)
#define V_PARA8_Vblank2(data)                                                        (0x00003FFF&((data)<<0))
#define V_PARA8_Vblank2_src(data)                                                    ((0x00003FFF&(data))>>0)
#define V_PARA8_get_Vblank2(data)                                                    ((0x00003FFF&(data))>>0)


#define V_PARA9                                                                      260
#define V_PARA9_reg_addr                                                             "0x9800D260"
#define V_PARA9_reg                                                                  0x9800D260
#define set_V_PARA9_reg(data)   (*((volatile unsigned int*) V_PARA9_reg)=data)
#define get_V_PARA9_reg   (*((volatile unsigned int*) V_PARA9_reg))
#define V_PARA9_inst_adr                                                             "0x0098"
#define V_PARA9_inst                                                                 0x0098
#define V_PARA9_Vback2_shift                                                         (16)
#define V_PARA9_Vback2_mask                                                          (0x3FFF0000)
#define V_PARA9_Vback2(data)                                                         (0x3FFF0000&((data)<<16))
#define V_PARA9_Vback2_src(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA9_get_Vback2(data)                                                     ((0x3FFF0000&(data))>>16)
#define V_PARA9_Vfront2_shift                                                        (0)
#define V_PARA9_Vfront2_mask                                                         (0x00003FFF)
#define V_PARA9_Vfront2(data)                                                        (0x00003FFF&((data)<<0))
#define V_PARA9_Vfront2_src(data)                                                    ((0x00003FFF&(data))>>0)
#define V_PARA9_get_Vfront2(data)                                                    ((0x00003FFF&(data))>>0)


#define V_PARA12                                                                     264
#define V_PARA12_reg_addr                                                            "0x9800D264"
#define V_PARA12_reg                                                                 0x9800D264
#define set_V_PARA12_reg(data)   (*((volatile unsigned int*) V_PARA12_reg)=data)
#define get_V_PARA12_reg   (*((volatile unsigned int*) V_PARA12_reg))
#define V_PARA12_inst_adr                                                            "0x0099"
#define V_PARA12_inst                                                                0x0099
#define V_PARA12_vsynci_shift                                                        (16)
#define V_PARA12_vsynci_mask                                                         (0x3FFF0000)
#define V_PARA12_vsynci(data)                                                        (0x3FFF0000&((data)<<16))
#define V_PARA12_vsynci_src(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA12_get_vsynci(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA12_vblanki_shift                                                       (0)
#define V_PARA12_vblanki_mask                                                        (0x00003FFF)
#define V_PARA12_vblanki(data)                                                       (0x00003FFF&((data)<<0))
#define V_PARA12_vblanki_src(data)                                                   ((0x00003FFF&(data))>>0)
#define V_PARA12_get_vblanki(data)                                                   ((0x00003FFF&(data))>>0)


#define V_PARA13                                                                     268
#define V_PARA13_reg_addr                                                            "0x9800D268"
#define V_PARA13_reg                                                                 0x9800D268
#define set_V_PARA13_reg(data)   (*((volatile unsigned int*) V_PARA13_reg)=data)
#define get_V_PARA13_reg   (*((volatile unsigned int*) V_PARA13_reg))
#define V_PARA13_inst_adr                                                            "0x009A"
#define V_PARA13_inst                                                                0x009A
#define V_PARA13_vbacki_shift                                                        (16)
#define V_PARA13_vbacki_mask                                                         (0x3FFF0000)
#define V_PARA13_vbacki(data)                                                        (0x3FFF0000&((data)<<16))
#define V_PARA13_vbacki_src(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA13_get_vbacki(data)                                                    ((0x3FFF0000&(data))>>16)
#define V_PARA13_vfronti_shift                                                       (0)
#define V_PARA13_vfronti_mask                                                        (0x00003FFF)
#define V_PARA13_vfronti(data)                                                       (0x00003FFF&((data)<<0))
#define V_PARA13_vfronti_src(data)                                                   ((0x00003FFF&(data))>>0)
#define V_PARA13_get_vfronti(data)                                                   ((0x00003FFF&(data))>>0)


#define V_PARA10                                                                     26C
#define V_PARA10_reg_addr                                                            "0x9800D26C"
#define V_PARA10_reg                                                                 0x9800D26C
#define set_V_PARA10_reg(data)   (*((volatile unsigned int*) V_PARA10_reg)=data)
#define get_V_PARA10_reg   (*((volatile unsigned int*) V_PARA10_reg))
#define V_PARA10_inst_adr                                                            "0x009B"
#define V_PARA10_inst                                                                0x009B
#define V_PARA10_G_shift                                                             (0)
#define V_PARA10_G_mask                                                              (0x00000FFF)
#define V_PARA10_G(data)                                                             (0x00000FFF&((data)<<0))
#define V_PARA10_G_src(data)                                                         ((0x00000FFF&(data))>>0)
#define V_PARA10_get_G(data)                                                         ((0x00000FFF&(data))>>0)


#define V_PARA11                                                                     270
#define V_PARA11_reg_addr                                                            "0x9800D270"
#define V_PARA11_reg                                                                 0x9800D270
#define set_V_PARA11_reg(data)   (*((volatile unsigned int*) V_PARA11_reg)=data)
#define get_V_PARA11_reg   (*((volatile unsigned int*) V_PARA11_reg))
#define V_PARA11_inst_adr                                                            "0x009C"
#define V_PARA11_inst                                                                0x009C
#define V_PARA11_B_shift                                                             (16)
#define V_PARA11_B_mask                                                              (0x0FFF0000)
#define V_PARA11_B(data)                                                             (0x0FFF0000&((data)<<16))
#define V_PARA11_B_src(data)                                                         ((0x0FFF0000&(data))>>16)
#define V_PARA11_get_B(data)                                                         ((0x0FFF0000&(data))>>16)
#define V_PARA11_R_shift                                                             (0)
#define V_PARA11_R_mask                                                              (0x00000FFF)
#define V_PARA11_R(data)                                                             (0x00000FFF&((data)<<0))
#define V_PARA11_R_src(data)                                                         ((0x00000FFF&(data))>>0)
#define V_PARA11_get_R(data)                                                         ((0x00000FFF&(data))>>0)


#define BIST1_CTRL                                                                   280
#define BIST1_CTRL_reg_addr                                                          "0x9800D280"
#define BIST1_CTRL_reg                                                               0x9800D280
#define set_BIST1_CTRL_reg(data)   (*((volatile unsigned int*) BIST1_CTRL_reg)=data)
#define get_BIST1_CTRL_reg   (*((volatile unsigned int*) BIST1_CTRL_reg))
#define BIST1_CTRL_inst_adr                                                          "0x00A0"
#define BIST1_CTRL_inst                                                              0x00A0
#define BIST1_CTRL_dft_test_resume_shift                                             (7)
#define BIST1_CTRL_dft_test_resume_mask                                              (0x00000080)
#define BIST1_CTRL_dft_test_resume(data)                                             (0x00000080&((data)<<7))
#define BIST1_CTRL_dft_test_resume_src(data)                                         ((0x00000080&(data))>>7)
#define BIST1_CTRL_get_dft_test_resume(data)                                         ((0x00000080&(data))>>7)
#define BIST1_CTRL_dft_bist_mode_shift                                               (6)
#define BIST1_CTRL_dft_bist_mode_mask                                                (0x00000040)
#define BIST1_CTRL_dft_bist_mode(data)                                               (0x00000040&((data)<<6))
#define BIST1_CTRL_dft_bist_mode_src(data)                                           ((0x00000040&(data))>>6)
#define BIST1_CTRL_get_dft_bist_mode(data)                                           ((0x00000040&(data))>>6)
#define BIST1_CTRL_bist_mode_shift                                                   (5)
#define BIST1_CTRL_bist_mode_mask                                                    (0x00000020)
#define BIST1_CTRL_bist_mode(data)                                                   (0x00000020&((data)<<5))
#define BIST1_CTRL_bist_mode_src(data)                                               ((0x00000020&(data))>>5)
#define BIST1_CTRL_get_bist_mode(data)                                               ((0x00000020&(data))>>5)
#define BIST1_CTRL_rme_shift                                                         (4)
#define BIST1_CTRL_rme_mask                                                          (0x00000010)
#define BIST1_CTRL_rme(data)                                                         (0x00000010&((data)<<4))
#define BIST1_CTRL_rme_src(data)                                                     ((0x00000010&(data))>>4)
#define BIST1_CTRL_get_rme(data)                                                     ((0x00000010&(data))>>4)
#define BIST1_CTRL_rm_shift                                                          (0)
#define BIST1_CTRL_rm_mask                                                           (0x0000000F)
#define BIST1_CTRL_rm(data)                                                          (0x0000000F&((data)<<0))
#define BIST1_CTRL_rm_src(data)                                                      ((0x0000000F&(data))>>0)
#define BIST1_CTRL_get_rm(data)                                                      ((0x0000000F&(data))>>0)


#define BIST2_CTRL                                                                   29C
#define BIST2_CTRL_reg_addr                                                          "0x9800D29C"
#define BIST2_CTRL_reg                                                               0x9800D29C
#define set_BIST2_CTRL_reg(data)   (*((volatile unsigned int*) BIST2_CTRL_reg)=data)
#define get_BIST2_CTRL_reg   (*((volatile unsigned int*) BIST2_CTRL_reg))
#define BIST2_CTRL_inst_adr                                                          "0x00A7"
#define BIST2_CTRL_inst                                                              0x00A7
#define BIST2_CTRL_dft_test_resume_shift                                             (7)
#define BIST2_CTRL_dft_test_resume_mask                                              (0x00000080)
#define BIST2_CTRL_dft_test_resume(data)                                             (0x00000080&((data)<<7))
#define BIST2_CTRL_dft_test_resume_src(data)                                         ((0x00000080&(data))>>7)
#define BIST2_CTRL_get_dft_test_resume(data)                                         ((0x00000080&(data))>>7)
#define BIST2_CTRL_dft_bist_mode_shift                                               (6)
#define BIST2_CTRL_dft_bist_mode_mask                                                (0x00000040)
#define BIST2_CTRL_dft_bist_mode(data)                                               (0x00000040&((data)<<6))
#define BIST2_CTRL_dft_bist_mode_src(data)                                           ((0x00000040&(data))>>6)
#define BIST2_CTRL_get_dft_bist_mode(data)                                           ((0x00000040&(data))>>6)
#define BIST2_CTRL_bist_mode_shift                                                   (5)
#define BIST2_CTRL_bist_mode_mask                                                    (0x00000020)
#define BIST2_CTRL_bist_mode(data)                                                   (0x00000020&((data)<<5))
#define BIST2_CTRL_bist_mode_src(data)                                               ((0x00000020&(data))>>5)
#define BIST2_CTRL_get_bist_mode(data)                                               ((0x00000020&(data))>>5)
#define BIST2_CTRL_rme_shift                                                         (4)
#define BIST2_CTRL_rme_mask                                                          (0x00000010)
#define BIST2_CTRL_rme(data)                                                         (0x00000010&((data)<<4))
#define BIST2_CTRL_rme_src(data)                                                     ((0x00000010&(data))>>4)
#define BIST2_CTRL_get_rme(data)                                                     ((0x00000010&(data))>>4)
#define BIST2_CTRL_rm_shift                                                          (0)
#define BIST2_CTRL_rm_mask                                                           (0x0000000F)
#define BIST2_CTRL_rm(data)                                                          (0x0000000F&((data)<<0))
#define BIST2_CTRL_rm_src(data)                                                      ((0x0000000F&(data))>>0)
#define BIST2_CTRL_get_rm(data)                                                      ((0x0000000F&(data))>>0)


#define BIST1_ST                                                                     284
#define BIST1_ST_reg_addr                                                            "0x9800D284"
#define BIST1_ST_reg                                                                 0x9800D284
#define set_BIST1_ST_reg(data)   (*((volatile unsigned int*) BIST1_ST_reg)=data)
#define get_BIST1_ST_reg   (*((volatile unsigned int*) BIST1_ST_reg))
#define BIST1_ST_inst_adr                                                            "0x00A1"
#define BIST1_ST_inst                                                                0x00A1
#define BIST1_ST_bist1_fail0_shift                                                   (1)
#define BIST1_ST_bist1_fail0_mask                                                    (0x00000002)
#define BIST1_ST_bist1_fail0(data)                                                   (0x00000002&((data)<<1))
#define BIST1_ST_bist1_fail0_src(data)                                               ((0x00000002&(data))>>1)
#define BIST1_ST_get_bist1_fail0(data)                                               ((0x00000002&(data))>>1)
#define BIST1_ST_bist1_done_shift                                                    (0)
#define BIST1_ST_bist1_done_mask                                                     (0x00000001)
#define BIST1_ST_bist1_done(data)                                                    (0x00000001&((data)<<0))
#define BIST1_ST_bist1_done_src(data)                                                ((0x00000001&(data))>>0)
#define BIST1_ST_get_bist1_done(data)                                                ((0x00000001&(data))>>0)


#define DRF_BIST1_ST                                                                 288
#define DRF_BIST1_ST_reg_addr                                                        "0x9800D288"
#define DRF_BIST1_ST_reg                                                             0x9800D288
#define set_DRF_BIST1_ST_reg(data)   (*((volatile unsigned int*) DRF_BIST1_ST_reg)=data)
#define get_DRF_BIST1_ST_reg   (*((volatile unsigned int*) DRF_BIST1_ST_reg))
#define DRF_BIST1_ST_inst_adr                                                        "0x00A2"
#define DRF_BIST1_ST_inst                                                            0x00A2
#define DRF_BIST1_ST_drf_bist1_start_pause_shift                                     (16)
#define DRF_BIST1_ST_drf_bist1_start_pause_mask                                      (0x00010000)
#define DRF_BIST1_ST_drf_bist1_start_pause(data)                                     (0x00010000&((data)<<16))
#define DRF_BIST1_ST_drf_bist1_start_pause_src(data)                                 ((0x00010000&(data))>>16)
#define DRF_BIST1_ST_get_drf_bist1_start_pause(data)                                 ((0x00010000&(data))>>16)
#define DRF_BIST1_ST_drf_bist1_fail0_shift                                           (1)
#define DRF_BIST1_ST_drf_bist1_fail0_mask                                            (0x00000002)
#define DRF_BIST1_ST_drf_bist1_fail0(data)                                           (0x00000002&((data)<<1))
#define DRF_BIST1_ST_drf_bist1_fail0_src(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST1_ST_get_drf_bist1_fail0(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST1_ST_drf_bist1_done_shift                                            (0)
#define DRF_BIST1_ST_drf_bist1_done_mask                                             (0x00000001)
#define DRF_BIST1_ST_drf_bist1_done(data)                                            (0x00000001&((data)<<0))
#define DRF_BIST1_ST_drf_bist1_done_src(data)                                        ((0x00000001&(data))>>0)
#define DRF_BIST1_ST_get_drf_bist1_done(data)                                        ((0x00000001&(data))>>0)


#define BIST2_ST                                                                     28C
#define BIST2_ST_reg_addr                                                            "0x9800D28C"
#define BIST2_ST_reg                                                                 0x9800D28C
#define set_BIST2_ST_reg(data)   (*((volatile unsigned int*) BIST2_ST_reg)=data)
#define get_BIST2_ST_reg   (*((volatile unsigned int*) BIST2_ST_reg))
#define BIST2_ST_inst_adr                                                            "0x00A3"
#define BIST2_ST_inst                                                                0x00A3
#define BIST2_ST_bist2_fail0_shift                                                   (1)
#define BIST2_ST_bist2_fail0_mask                                                    (0x00000002)
#define BIST2_ST_bist2_fail0(data)                                                   (0x00000002&((data)<<1))
#define BIST2_ST_bist2_fail0_src(data)                                               ((0x00000002&(data))>>1)
#define BIST2_ST_get_bist2_fail0(data)                                               ((0x00000002&(data))>>1)
#define BIST2_ST_bist2_done_shift                                                    (0)
#define BIST2_ST_bist2_done_mask                                                     (0x00000001)
#define BIST2_ST_bist2_done(data)                                                    (0x00000001&((data)<<0))
#define BIST2_ST_bist2_done_src(data)                                                ((0x00000001&(data))>>0)
#define BIST2_ST_get_bist2_done(data)                                                ((0x00000001&(data))>>0)


#define DRF_BIST2_ST                                                                 290
#define DRF_BIST2_ST_reg_addr                                                        "0x9800D290"
#define DRF_BIST2_ST_reg                                                             0x9800D290
#define set_DRF_BIST2_ST_reg(data)   (*((volatile unsigned int*) DRF_BIST2_ST_reg)=data)
#define get_DRF_BIST2_ST_reg   (*((volatile unsigned int*) DRF_BIST2_ST_reg))
#define DRF_BIST2_ST_inst_adr                                                        "0x00A4"
#define DRF_BIST2_ST_inst                                                            0x00A4
#define DRF_BIST2_ST_drf_bist2_start_pause_shift                                     (16)
#define DRF_BIST2_ST_drf_bist2_start_pause_mask                                      (0x00010000)
#define DRF_BIST2_ST_drf_bist2_start_pause(data)                                     (0x00010000&((data)<<16))
#define DRF_BIST2_ST_drf_bist2_start_pause_src(data)                                 ((0x00010000&(data))>>16)
#define DRF_BIST2_ST_get_drf_bist2_start_pause(data)                                 ((0x00010000&(data))>>16)
#define DRF_BIST2_ST_drf_bist2_fail0_shift                                           (1)
#define DRF_BIST2_ST_drf_bist2_fail0_mask                                            (0x00000002)
#define DRF_BIST2_ST_drf_bist2_fail0(data)                                           (0x00000002&((data)<<1))
#define DRF_BIST2_ST_drf_bist2_fail0_src(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST2_ST_get_drf_bist2_fail0(data)                                       ((0x00000002&(data))>>1)
#define DRF_BIST2_ST_drf_bist2_done_shift                                            (0)
#define DRF_BIST2_ST_drf_bist2_done_mask                                             (0x00000001)
#define DRF_BIST2_ST_drf_bist2_done(data)                                            (0x00000001&((data)<<0))
#define DRF_BIST2_ST_drf_bist2_done_src(data)                                        ((0x00000001&(data))>>0)
#define DRF_BIST2_ST_get_drf_bist2_done(data)                                        ((0x00000001&(data))>>0)


#define MHLCTRL                                                                      298
#define MHLCTRL_reg_addr                                                             "0x9800D298"
#define MHLCTRL_reg                                                                  0x9800D298
#define set_MHLCTRL_reg(data)   (*((volatile unsigned int*) MHLCTRL_reg)=data)
#define get_MHLCTRL_reg   (*((volatile unsigned int*) MHLCTRL_reg))
#define MHLCTRL_inst_adr                                                             "0x00A6"
#define MHLCTRL_inst                                                                 0x00A6
#define MHLCTRL_write_en6_shift                                                      (13)
#define MHLCTRL_write_en6_mask                                                       (0x00002000)
#define MHLCTRL_write_en6(data)                                                      (0x00002000&((data)<<13))
#define MHLCTRL_write_en6_src(data)                                                  ((0x00002000&(data))>>13)
#define MHLCTRL_get_write_en6(data)                                                  ((0x00002000&(data))>>13)
#define MHLCTRL_mhl_pp_ch1sel_shift                                                  (12)
#define MHLCTRL_mhl_pp_ch1sel_mask                                                   (0x00001000)
#define MHLCTRL_mhl_pp_ch1sel(data)                                                  (0x00001000&((data)<<12))
#define MHLCTRL_mhl_pp_ch1sel_src(data)                                              ((0x00001000&(data))>>12)
#define MHLCTRL_get_mhl_pp_ch1sel(data)                                              ((0x00001000&(data))>>12)
#define MHLCTRL_write_en5_shift                                                      (11)
#define MHLCTRL_write_en5_mask                                                       (0x00000800)
#define MHLCTRL_write_en5(data)                                                      (0x00000800&((data)<<11))
#define MHLCTRL_write_en5_src(data)                                                  ((0x00000800&(data))>>11)
#define MHLCTRL_get_write_en5(data)                                                  ((0x00000800&(data))>>11)
#define MHLCTRL_mhl_phy_test_mode_shift                                              (10)
#define MHLCTRL_mhl_phy_test_mode_mask                                               (0x00000400)
#define MHLCTRL_mhl_phy_test_mode(data)                                              (0x00000400&((data)<<10))
#define MHLCTRL_mhl_phy_test_mode_src(data)                                          ((0x00000400&(data))>>10)
#define MHLCTRL_get_mhl_phy_test_mode(data)                                          ((0x00000400&(data))>>10)
#define MHLCTRL_write_en4_shift                                                      (9)
#define MHLCTRL_write_en4_mask                                                       (0x00000200)
#define MHLCTRL_write_en4(data)                                                      (0x00000200&((data)<<9))
#define MHLCTRL_write_en4_src(data)                                                  ((0x00000200&(data))>>9)
#define MHLCTRL_get_write_en4(data)                                                  ((0x00000200&(data))>>9)
#define MHLCTRL_xor_pixel_sel_shift                                                  (6)
#define MHLCTRL_xor_pixel_sel_mask                                                   (0x000001C0)
#define MHLCTRL_xor_pixel_sel(data)                                                  (0x000001C0&((data)<<6))
#define MHLCTRL_xor_pixel_sel_src(data)                                              ((0x000001C0&(data))>>6)
#define MHLCTRL_get_xor_pixel_sel(data)                                              ((0x000001C0&(data))>>6)
#define MHLCTRL_write_en3_shift                                                      (5)
#define MHLCTRL_write_en3_mask                                                       (0x00000020)
#define MHLCTRL_write_en3(data)                                                      (0x00000020&((data)<<5))
#define MHLCTRL_write_en3_src(data)                                                  ((0x00000020&(data))>>5)
#define MHLCTRL_get_write_en3(data)                                                  ((0x00000020&(data))>>5)
#define MHLCTRL_mhl_enc_sel_shift                                                    (4)
#define MHLCTRL_mhl_enc_sel_mask                                                     (0x00000010)
#define MHLCTRL_mhl_enc_sel(data)                                                    (0x00000010&((data)<<4))
#define MHLCTRL_mhl_enc_sel_src(data)                                                ((0x00000010&(data))>>4)
#define MHLCTRL_get_mhl_enc_sel(data)                                                ((0x00000010&(data))>>4)
#define MHLCTRL_write_en2_shift                                                      (3)
#define MHLCTRL_write_en2_mask                                                       (0x00000008)
#define MHLCTRL_write_en2(data)                                                      (0x00000008&((data)<<3))
#define MHLCTRL_write_en2_src(data)                                                  ((0x00000008&(data))>>3)
#define MHLCTRL_get_write_en2(data)                                                  ((0x00000008&(data))>>3)
#define MHLCTRL_mhl_pp_mode_shift                                                    (2)
#define MHLCTRL_mhl_pp_mode_mask                                                     (0x00000004)
#define MHLCTRL_mhl_pp_mode(data)                                                    (0x00000004&((data)<<2))
#define MHLCTRL_mhl_pp_mode_src(data)                                                ((0x00000004&(data))>>2)
#define MHLCTRL_get_mhl_pp_mode(data)                                                ((0x00000004&(data))>>2)
#define MHLCTRL_write_en1_shift                                                      (1)
#define MHLCTRL_write_en1_mask                                                       (0x00000002)
#define MHLCTRL_write_en1(data)                                                      (0x00000002&((data)<<1))
#define MHLCTRL_write_en1_src(data)                                                  ((0x00000002&(data))>>1)
#define MHLCTRL_get_write_en1(data)                                                  ((0x00000002&(data))>>1)
#define MHLCTRL_mhl_enable_shift                                                     (0)
#define MHLCTRL_mhl_enable_mask                                                      (0x00000001)
#define MHLCTRL_mhl_enable(data)                                                     (0x00000001&((data)<<0))
#define MHLCTRL_mhl_enable_src(data)                                                 ((0x00000001&(data))>>0)
#define MHLCTRL_get_mhl_enable(data)                                                 ((0x00000001&(data))>>0)


#define CHSWAP                                                                       2A0
#define CHSWAP_reg_addr                                                              "0x9800D2A0"
#define CHSWAP_reg                                                                   0x9800D2A0
#define set_CHSWAP_reg(data)   (*((volatile unsigned int*) CHSWAP_reg)=data)
#define get_CHSWAP_reg   (*((volatile unsigned int*) CHSWAP_reg))
#define CHSWAP_inst_adr                                                              "0x00A8"
#define CHSWAP_inst                                                                  0x00A8
#define CHSWAP_write_en3_shift                                                       (5)
#define CHSWAP_write_en3_mask                                                        (0x00000020)
#define CHSWAP_write_en3(data)                                                       (0x00000020&((data)<<5))
#define CHSWAP_write_en3_src(data)                                                   ((0x00000020&(data))>>5)
#define CHSWAP_get_write_en3(data)                                                   ((0x00000020&(data))>>5)
#define CHSWAP_mhl_ch_sel_shift                                                      (4)
#define CHSWAP_mhl_ch_sel_mask                                                       (0x00000010)
#define CHSWAP_mhl_ch_sel(data)                                                      (0x00000010&((data)<<4))
#define CHSWAP_mhl_ch_sel_src(data)                                                  ((0x00000010&(data))>>4)
#define CHSWAP_get_mhl_ch_sel(data)                                                  ((0x00000010&(data))>>4)
#define CHSWAP_write_en2_shift                                                       (3)
#define CHSWAP_write_en2_mask                                                        (0x00000008)
#define CHSWAP_write_en2(data)                                                       (0x00000008&((data)<<3))
#define CHSWAP_write_en2_src(data)                                                   ((0x00000008&(data))>>3)
#define CHSWAP_get_write_en2(data)                                                   ((0x00000008&(data))>>3)
#define CHSWAP_hdmi_chcclk_swap_shift                                                (2)
#define CHSWAP_hdmi_chcclk_swap_mask                                                 (0x00000004)
#define CHSWAP_hdmi_chcclk_swap(data)                                                (0x00000004&((data)<<2))
#define CHSWAP_hdmi_chcclk_swap_src(data)                                            ((0x00000004&(data))>>2)
#define CHSWAP_get_hdmi_chcclk_swap(data)                                            ((0x00000004&(data))>>2)
#define CHSWAP_write_en1_shift                                                       (1)
#define CHSWAP_write_en1_mask                                                        (0x00000002)
#define CHSWAP_write_en1(data)                                                       (0x00000002&((data)<<1))
#define CHSWAP_write_en1_src(data)                                                   ((0x00000002&(data))>>1)
#define CHSWAP_get_write_en1(data)                                                   ((0x00000002&(data))>>1)
#define CHSWAP_hdmi_chab_swap_shift                                                  (0)
#define CHSWAP_hdmi_chab_swap_mask                                                   (0x00000001)
#define CHSWAP_hdmi_chab_swap(data)                                                  (0x00000001&((data)<<0))
#define CHSWAP_hdmi_chab_swap_src(data)                                              ((0x00000001&(data))>>0)
#define CHSWAP_get_hdmi_chab_swap(data)                                              ((0x00000001&(data))>>0)


#define PREFIFO_CTRL                                                                 294
#define PREFIFO_CTRL_reg_addr                                                        "0x9800D294"
#define PREFIFO_CTRL_reg                                                             0x9800D294
#define set_PREFIFO_CTRL_reg(data)   (*((volatile unsigned int*) PREFIFO_CTRL_reg)=data)
#define get_PREFIFO_CTRL_reg   (*((volatile unsigned int*) PREFIFO_CTRL_reg))
#define PREFIFO_CTRL_inst_adr                                                        "0x00A5"
#define PREFIFO_CTRL_inst                                                            0x00A5
#define PREFIFO_CTRL_write_en2_shift                                                 (3)
#define PREFIFO_CTRL_write_en2_mask                                                  (0x00000008)
#define PREFIFO_CTRL_write_en2(data)                                                 (0x00000008&((data)<<3))
#define PREFIFO_CTRL_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define PREFIFO_CTRL_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define PREFIFO_CTRL_hdmi_prefifo_inv_shift                                          (2)
#define PREFIFO_CTRL_hdmi_prefifo_inv_mask                                           (0x00000004)
#define PREFIFO_CTRL_hdmi_prefifo_inv(data)                                          (0x00000004&((data)<<2))
#define PREFIFO_CTRL_hdmi_prefifo_inv_src(data)                                      ((0x00000004&(data))>>2)
#define PREFIFO_CTRL_get_hdmi_prefifo_inv(data)                                      ((0x00000004&(data))>>2)
#define PREFIFO_CTRL_write_en1_shift                                                 (1)
#define PREFIFO_CTRL_write_en1_mask                                                  (0x00000002)
#define PREFIFO_CTRL_write_en1(data)                                                 (0x00000002&((data)<<1))
#define PREFIFO_CTRL_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define PREFIFO_CTRL_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define PREFIFO_CTRL_async_update_shift                                              (0)
#define PREFIFO_CTRL_async_update_mask                                               (0x00000001)
#define PREFIFO_CTRL_async_update(data)                                              (0x00000001&((data)<<0))
#define PREFIFO_CTRL_async_update_src(data)                                          ((0x00000001&(data))>>0)
#define PREFIFO_CTRL_get_async_update(data)                                          ((0x00000001&(data))>>0)


#define PHYCHCRTL                                                                    2AC
#define PHYCHCRTL_reg_addr                                                           "0x9800D2AC"
#define PHYCHCRTL_reg                                                                0x9800D2AC
#define set_PHYCHCRTL_reg(data)   (*((volatile unsigned int*) PHYCHCRTL_reg)=data)
#define get_PHYCHCRTL_reg   (*((volatile unsigned int*) PHYCHCRTL_reg))
#define PHYCHCRTL_inst_adr                                                           "0x00D7"
#define PHYCHCRTL_inst                                                               0x00D7
#define PHYCHCRTL_write_en5_shift                                                    (13)
#define PHYCHCRTL_write_en5_mask                                                     (0x00002000)
#define PHYCHCRTL_write_en5(data)                                                    (0x00002000&((data)<<13))
#define PHYCHCRTL_write_en5_src(data)                                                ((0x00002000&(data))>>13)
#define PHYCHCRTL_get_write_en5(data)                                                ((0x00002000&(data))>>13)
#define PHYCHCRTL_data_pola_inv_shift                                                (12)
#define PHYCHCRTL_data_pola_inv_mask                                                 (0x00001000)
#define PHYCHCRTL_data_pola_inv(data)                                                (0x00001000&((data)<<12))
#define PHYCHCRTL_data_pola_inv_src(data)                                            ((0x00001000&(data))>>12)
#define PHYCHCRTL_get_data_pola_inv(data)                                            ((0x00001000&(data))>>12)
#define PHYCHCRTL_write_en4_shift                                                    (11)
#define PHYCHCRTL_write_en4_mask                                                     (0x00000800)
#define PHYCHCRTL_write_en4(data)                                                    (0x00000800&((data)<<11))
#define PHYCHCRTL_write_en4_src(data)                                                ((0x00000800&(data))>>11)
#define PHYCHCRTL_get_write_en4(data)                                                ((0x00000800&(data))>>11)
#define PHYCHCRTL_hdmi_chclk_data_swap_shift                                         (9)
#define PHYCHCRTL_hdmi_chclk_data_swap_mask                                          (0x00000600)
#define PHYCHCRTL_hdmi_chclk_data_swap(data)                                         (0x00000600&((data)<<9))
#define PHYCHCRTL_hdmi_chclk_data_swap_src(data)                                     ((0x00000600&(data))>>9)
#define PHYCHCRTL_get_hdmi_chclk_data_swap(data)                                     ((0x00000600&(data))>>9)
#define PHYCHCRTL_write_en3_shift                                                    (8)
#define PHYCHCRTL_write_en3_mask                                                     (0x00000100)
#define PHYCHCRTL_write_en3(data)                                                    (0x00000100&((data)<<8))
#define PHYCHCRTL_write_en3_src(data)                                                ((0x00000100&(data))>>8)
#define PHYCHCRTL_get_write_en3(data)                                                ((0x00000100&(data))>>8)
#define PHYCHCRTL_hdmi_chc_data_swap_shift                                           (6)
#define PHYCHCRTL_hdmi_chc_data_swap_mask                                            (0x000000C0)
#define PHYCHCRTL_hdmi_chc_data_swap(data)                                           (0x000000C0&((data)<<6))
#define PHYCHCRTL_hdmi_chc_data_swap_src(data)                                       ((0x000000C0&(data))>>6)
#define PHYCHCRTL_get_hdmi_chc_data_swap(data)                                       ((0x000000C0&(data))>>6)
#define PHYCHCRTL_write_en2_shift                                                    (5)
#define PHYCHCRTL_write_en2_mask                                                     (0x00000020)
#define PHYCHCRTL_write_en2(data)                                                    (0x00000020&((data)<<5))
#define PHYCHCRTL_write_en2_src(data)                                                ((0x00000020&(data))>>5)
#define PHYCHCRTL_get_write_en2(data)                                                ((0x00000020&(data))>>5)
#define PHYCHCRTL_hdmi_chb_data_swap_shift                                           (3)
#define PHYCHCRTL_hdmi_chb_data_swap_mask                                            (0x00000018)
#define PHYCHCRTL_hdmi_chb_data_swap(data)                                           (0x00000018&((data)<<3))
#define PHYCHCRTL_hdmi_chb_data_swap_src(data)                                       ((0x00000018&(data))>>3)
#define PHYCHCRTL_get_hdmi_chb_data_swap(data)                                       ((0x00000018&(data))>>3)
#define PHYCHCRTL_write_en1_shift                                                    (2)
#define PHYCHCRTL_write_en1_mask                                                     (0x00000004)
#define PHYCHCRTL_write_en1(data)                                                    (0x00000004&((data)<<2))
#define PHYCHCRTL_write_en1_src(data)                                                ((0x00000004&(data))>>2)
#define PHYCHCRTL_get_write_en1(data)                                                ((0x00000004&(data))>>2)
#define PHYCHCRTL_hdmi_cha_data_swap_shift                                           (0)
#define PHYCHCRTL_hdmi_cha_data_swap_mask                                            (0x00000003)
#define PHYCHCRTL_hdmi_cha_data_swap(data)                                           (0x00000003&((data)<<0))
#define PHYCHCRTL_hdmi_cha_data_swap_src(data)                                       ((0x00000003&(data))>>0)
#define PHYCHCRTL_get_hdmi_cha_data_swap(data)                                       ((0x00000003&(data))>>0)


#endif
