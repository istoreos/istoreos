#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


#include <OSAL/remote_malloc.h>
#include <SVCFunc.h>


#include <AudioRPC_Agent.h>
#include <AudioRPC_System.h>
#include <VideoRPC_Agent.h>
#include <VideoRPC_System.h>
#include <RPCProxy.h>
//#include <InbandAPI.h>
#include "OSAL/debug_level.h"
#include "OSAL/Threads.h"
#include "OSAL/PLI.h"

#include "../display.h"
#include "../nvr_hdmi.h"
#include "../gst_display.h"
#include "../gst_decode.h"

#define RPC_DBGREG_GET	0
#define RPC_DBGREG_SET	1
#define RPC_DBGREG_AFLAG	0
#define RPC_DBGREG_VFLAG	1
#define RPC_IOCTRGETDBGREG_A _IOWR(RPC_IOC_MAGIC,  0x10, RPC_DBG_FLAG)
#define RPC_IOCTRGETDBGREG_V _IOWR(RPC_IOC_MAGIC,  0x11, RPC_DBG_FLAG)

#define VIDEO_TEST 1
#define AUDIO_TEST 1

typedef struct RPC_DBG_FLAG
{
  int op;	//0:get, 1:set
  unsigned int flagValue;
  unsigned int flagAddr;
} RPC_DBG_FLAG;

void firmware_init(void) {
    struct REG_STRUCT *rnode = NULL;

    rnode = (struct REG_STRUCT *)R_PROGRAM_0_register(rnode);
#ifdef HAS_VIDEO
    rnode = (struct REG_STRUCT *)VIDEO_AGENT_0_register(rnode);
#endif
#ifdef HAS_AUDIO
    rnode = (struct REG_STRUCT *)AUDIO_AGENT_0_register(rnode);
#endif
    rnode = (struct REG_STRUCT *)ReplyHandler_register(rnode); // Reply Handler
    if(initRPCProxy(rnode)==-1)
        ipc_unregister(rnode);

    //firmware_initialized = true;
}

void firmware_uninit(void) {
    DeInitRPCProxy();
}


static unsigned int reverseInteger(unsigned int value)
{
    unsigned int b0 = value & 0x000000ff;
    unsigned int b1 = (value & 0x0000ff00) >> 8;
    unsigned int b2 = (value & 0x00ff0000) >> 16;
    unsigned int b3 = (value & 0xff000000) >> 24;

    return (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
}

// Inter-processor write memroy, will perform swap 4 bytes (endian swap) and write to the destination if cross CPU with different endianess
void    pli_IPCWriteULONG(BYTE* des, unsigned int data)
{
    volatile unsigned int A;  // prevent gcc -O3 optimization to create non-atomic access
    if (((long)des & 0x3) != 0)
        printf("error in pli_IPCWriteULONG()...\n");

    A = reverseInteger(data);
    *(unsigned int *)des = A;
}

// Inter-processor write memroy, will perform swap 4 bytes (endian swap) and write to the destination if cross CPU with different endianess
unsigned int    pli_IPCReadULONG(BYTE* src)
{
    volatile unsigned long A;  // prevent gcc -O3 optimization to create non-atomic access
    if (((long)src & 0x3) != 0)
        printf("error in pli_IPCReadULONG()...\n");
    A = *(unsigned int *)src;
    return reverseInteger(A);
}


void get_debug_flag_v2(int AVflag, RPC_DBG_FLAG *dFlag)
{
    int rpcfd = open("/dev/rpc100", O_RDWR);

    dFlag->op = RPC_DBGREG_GET;
    if (AVflag == RPC_DBGREG_AFLAG)
    {
        ioctl(rpcfd, RPC_IOCTRGETDBGREG_A, dFlag);
    }
    else if (AVflag == RPC_DBGREG_VFLAG)
    {
        ioctl(rpcfd, RPC_IOCTRGETDBGREG_V, dFlag);
    }
    dFlag->flagValue = pli_IPCReadULONG((BYTE*)&dFlag->flagValue);
//printf("%s:%d AVflag:%d dFlag->flagAddr=0x%.8x dFlag->flagValue=0x%.8x dFlag->op=%d\n", __func__, __LINE__, AVflag, dFlag->flagAddr, dFlag->flagValue, dFlag->op);
    close(rpcfd);
}

void set_debug_flag_v2(int AVflag, RPC_DBG_FLAG *dFlag)
{
    int rpcfd = open("/dev/rpc100", O_RDWR);
    unsigned long PhyAddr;
    CLNT_STRUCT clnt;
    unsigned long DebugFlag;

    dFlag->op = RPC_DBGREG_SET;

    pli_IPCWriteULONG((BYTE*)&DebugFlag, dFlag->flagValue);
    dFlag->flagValue = DebugFlag;

    if (AVflag == RPC_DBGREG_AFLAG)
    {
        ioctl(rpcfd, RPC_IOCTRGETDBGREG_A, dFlag);
    }
    else if (AVflag == RPC_DBGREG_VFLAG)
    {
        ioctl(rpcfd, RPC_IOCTRGETDBGREG_V, dFlag);
    }

    PhyAddr = dFlag->flagAddr;
//printf("%s:%d AVflag:%d dFlag->flagAddr=0x%.8x dFlag->flagValue=0x%.8x dFlag->op=%d\n", __func__, __LINE__, AVflag, dFlag->flagAddr, dFlag->flagValue, dFlag->op);

    if (AVflag == RPC_DBGREG_AFLAG)
    {
        clnt = prepareCLNT(BLOCK_MODE | USE_INTR_BUF | SEND_AUDIO_CPU, D_PROGRAM, D_VERSION);
    }
    else if (AVflag == RPC_DBGREG_VFLAG)
    {
        clnt = prepareCLNT(BLOCK_MODE | USE_INTR_BUF | SEND_VIDEO_CPU, D_PROGRAM, D_VERSION);
    }
    set_debug_flag_0((int*)&PhyAddr, &clnt);

    close(rpcfd);
}

void disableAudioFwLog(void)
{
    RPC_DBG_FLAG dFlag;
    get_debug_flag_v2(RPC_DBGREG_AFLAG, &dFlag);
    dFlag.flagValue = 0;
    set_debug_flag_v2(RPC_DBGREG_AFLAG, &dFlag);
    get_debug_flag_v2(RPC_DBGREG_AFLAG, &dFlag);
    printf("SET [adbg:0x%.8x] = %08x\n", dFlag.flagAddr|(0xa0000000), dFlag.flagValue);
}

int main (int argc, const char **argv)
{
    ChannelId channelID[9];
    int wndlID[9];
    pid_t pid;
    //SnapshotBuffer_t snapshotBuf;
    //GstBus *bus1, *bus2, *bus3, *bus4;
    //GstMessage *msg1, *msg2, *msg3, *msg4;

    firmware_init();

    disableAudioFwLog();
    sleep(5);
    display_init();
    hdmi_init();

    /* Initialize GStreamer */
    gst_init (NULL, NULL);

    pid = getpid();

    channelID[0] = gst_dec_add_channel(pid);
    channelID[1] = gst_dec_add_channel(pid);
    channelID[2] = gst_dec_add_channel(pid);
    channelID[3] = gst_dec_add_channel(pid);
    channelID[4] = gst_dec_add_channel(pid);
    channelID[5] = gst_dec_add_channel(pid);
    channelID[6] = gst_dec_add_channel(pid);
    channelID[7] = gst_dec_add_channel(pid);
    channelID[8] = gst_dec_add_channel(pid);
    /* Set the URI to play */
    //multaudio.mp4:720p 24fps(h264+aac)

    gst_dec_open(channelID[0], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[1], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[2], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[3], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[4], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[5], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[6], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[7], "/root/nfs/Testfiles/mp4/multaudio.mp4");
    gst_dec_open(channelID[8], "/root/nfs/Testfiles/mp4/multaudio.mp4");


    wndlID[0] = gst_disp_create(0, 0, 640, 360, 0, pid);
    wndlID[1] = gst_disp_create(0, 360, 640, 360, 0, pid);
    wndlID[2] = gst_disp_create(0, 720, 640, 360, 0, pid);
    wndlID[3] = gst_disp_create(640, 0, 640, 360, 0, pid);
    wndlID[4] = gst_disp_create(640, 360, 640, 360, 0, pid);
    wndlID[5] = gst_disp_create(640, 720, 640, 360, 0, pid);
    wndlID[6] = gst_disp_create(1280, 0, 640, 360, 0, pid);
    wndlID[7] = gst_disp_create(1280, 360, 640, 360, 0, pid);
    wndlID[8] = gst_disp_create(1280, 720, 640, 360, 0, pid);

    gst_dec_bind(channelID[0], wndlID[0]);
    gst_dec_bind(channelID[1], wndlID[1]);
    gst_dec_bind(channelID[2], wndlID[2]);
    gst_dec_bind(channelID[3], wndlID[3]);
    gst_dec_bind(channelID[4], wndlID[4]);
    gst_dec_bind(channelID[5], wndlID[5]);
    gst_dec_bind(channelID[6], wndlID[6]);
    gst_dec_bind(channelID[7], wndlID[7]);
    gst_dec_bind(channelID[8], wndlID[8]);

    /* Start playing */
    gst_dec_set_play(CH_STATE_PLAY, channelID[0]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[1]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[2]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[3]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[4]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[5]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[6]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[7]);
        sleep(2);

    gst_dec_set_play(CH_STATE_PLAY, channelID[8]);
        sleep(2);

    /* Listen to the bus */
   // bus1 = gst_element_get_bus (data1.pipeline);
    //bus2 = gst_element_get_bus (data2.pipeline);
    //bus3 = gst_element_get_bus (data3.pipeline);
    //bus4 = gst_element_get_bus (data4.pipeline);
#if AUDIO_TEST
    sleep(10);
    gst_dec_start_audio(channelID[0]);

    sleep(10);
    gst_dec_stop_audio(channelID[0]);

    sleep(10);
    gst_dec_start_audio(channelID[1]);

    sleep(10);
    gst_dec_stop_audio(channelID[1]);

    sleep(10);
    gst_dec_start_audio(channelID[2]);

    sleep(10);
    gst_dec_stop_audio(channelID[2]);

    sleep(10);
    gst_dec_start_audio(channelID[3]);

    sleep(10);
    gst_dec_stop_audio(channelID[3]);

    sleep(10);
    gst_dec_start_audio(channelID[6]);

    sleep(10);
    gst_dec_stop_audio(channelID[6]);

    sleep(10);
    gst_dec_start_audio(channelID[5]);

    sleep(10);
    gst_dec_stop_audio(channelID[5]);

    sleep(10);
    gst_dec_start_audio(channelID[8]);

    sleep(10);
#endif

#if VIDEO_TEST

    //blank test
    printf("blank test...\n");
    gst_disp_set_blank(1, 5, channelID[0], channelID[2], channelID[4], channelID[6], channelID[8]);
    sleep(15);
    gst_disp_set_blank(0, 5, channelID[0], channelID[2], channelID[4], channelID[6], channelID[8]);
    gst_disp_set_blank(1, 4, channelID[1], channelID[3], channelID[5], channelID[7]);
    sleep(15);
    gst_disp_set_blank(0, 4, channelID[1], channelID[3], channelID[5], channelID[7]);
    sleep(5);

    //resize test: channel 0 full screen
    printf("full screen test...\n");
    gst_disp_resize(channelID[1], 0, 0, 0, 0);
    gst_disp_resize(channelID[2], 0, 0, 0, 0);
    gst_disp_resize(channelID[3], 0, 0, 0, 0);
    gst_disp_resize(channelID[4], 0, 0, 0, 0);
    gst_disp_resize(channelID[5], 0, 0, 0, 0);
    gst_disp_resize(channelID[6], 0, 0, 0, 0);
    gst_disp_resize(channelID[7], 0, 0, 0, 0);
    gst_disp_resize(channelID[8], 0, 0, 0, 0);
    gst_disp_resize(channelID[0], 0, 0, 1920, 1080);

    sleep(15);

    //resize test: modify the display layout and only show channel 1, 2
    printf("resize test...\n");
    gst_disp_resize(channelID[0], 0, 0, 1536, 810);
    gst_disp_resize(channelID[1], 0, 810, 384, 270);
    gst_disp_resize(channelID[2], 384, 810, 384, 270);
    gst_disp_resize(channelID[3], 768, 810, 384, 270);
    gst_disp_resize(channelID[4], 1152, 810, 384, 270);
    gst_disp_resize(channelID[5], 1536, 810, 384, 270);
    gst_disp_resize(channelID[6], 1536, 0, 384, 270);
    gst_disp_resize(channelID[7], 1536, 270, 384, 270);
    gst_disp_resize(channelID[8], 1536, 540, 384, 270);

    sleep(15);

    gst_disp_set_blank(1, 7, channelID[1], channelID[2], channelID[3], channelID[4], channelID[6], channelID[7], channelID[8]);

    //zoom in test: zoom in channel 1
    printf("zoom in test...\n");
    gst_disp_crop(channelID[0], 120, 60, 360, 240);
    sleep(15);
    gst_disp_crop(channelID[0], 0, 0, 1280, 720);
    sleep(10);
    gst_disp_set_blank(0, 7, channelID[1], channelID[2], channelID[3], channelID[4], channelID[6], channelID[7], channelID[8]);


    sleep(10);

    //get snapshot
    printf("snapshot test...\n");
    gst_snapshot_display("./snapshot0.jpg");
    sleep(10);

    HDMIMode_e mode;
	DPMode_e modeDP;
    gst_disp_get_output(&mode, &modeDP);
    printf("get HDMI mode =%d, DP mode =%d\n",mode, modeDP);
    printf("set 720p\n");
    gst_disp_set_output(HDMI_720P_60, DP_NONE);
    gst_disp_get_output(&mode, &modeDP);
    printf("get HDMI mode =%d, DP mode =%d\n",mode, modeDP);
    sleep(10);
    printf("set auto\n");
    gst_disp_set_output(HDMI_AUTO, DP_1080P_60);
    sleep(10);
    gst_disp_get_output(&mode, &modeDP);
    printf("get HDMI mode =%d, DP mode =%d\n",mode, modeDP);
    sleep(10);
#endif
    /* Free resources */
    //gst_object_unref (bus1);
    //gst_object_unref (bus2);
    //gst_object_unref (bus3);
    //gst_object_unref (bus4);

    sleep(300);
    printf("\n\nstop\n\n");
    gst_dec_set_play(CH_STATE_STOP, channelID[0]);
    gst_dec_set_play(CH_STATE_STOP, channelID[1]);
    gst_dec_set_play(CH_STATE_STOP, channelID[2]);
    gst_dec_set_play(CH_STATE_STOP, channelID[3]);
    gst_dec_set_play(CH_STATE_STOP, channelID[4]);
    gst_dec_set_play(CH_STATE_STOP, channelID[5]);
    gst_dec_set_play(CH_STATE_STOP, channelID[6]);
    gst_dec_set_play(CH_STATE_STOP, channelID[7]);
    gst_dec_set_play(CH_STATE_STOP, channelID[8]);

    gst_dec_remove_channel(channelID[0]);
    gst_dec_remove_channel(channelID[1]);
    gst_dec_remove_channel(channelID[2]);
    gst_dec_remove_channel(channelID[3]);
    gst_dec_remove_channel(channelID[4]);
    gst_dec_remove_channel(channelID[5]);
    gst_dec_remove_channel(channelID[6]);
    gst_dec_remove_channel(channelID[7]);
    gst_dec_remove_channel(channelID[8]);

    gst_disp_destroy(wndlID[0]);
    gst_disp_destroy(wndlID[1]);
    gst_disp_destroy(wndlID[2]);
    gst_disp_destroy(wndlID[3]);
    gst_disp_destroy(wndlID[4]);
    gst_disp_destroy(wndlID[5]);
    gst_disp_destroy(wndlID[6]);
    gst_disp_destroy(wndlID[7]);
    gst_disp_destroy(wndlID[8]);

    hdmi_uninit();
    display_uninit();
    firmware_uninit();

    return 0;
}

