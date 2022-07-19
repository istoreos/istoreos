/*
 * testapp-slim-rtkrtsp-fetchframe.c: example for using fetch decoded frame api and rtk_IVA_disp_image api
 *
 * rtk_fetch_frame_mmap/rtk_fetch_frame_munmap API to fetched current decoded frame through the specified channel
 * rtk_IVA_disp_image API to display the frame that has processed by customer, user needs rtk_disp_create() first
 *
 * After run this program, user can press 's' to scaling down long run, 'l' to original size long run 100 frames, 'f' to fetch one frame and show,'q' to quit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>
#include <signal.h>

#include "rtkcontrol.h"
#include "rtkrtsp.h"

#include <sys/mman.h>
#include "rtk-ion.h"
#include "rtk-se.h"

#define PLAYER_NUM  4
#define HLS_TARGETDURATION  6
#define FETCHFRAME_SHARE_MEM_KEY (0x46534D4B)  //FSMK

#define CHECK(x) do {                                                     \
        if (x != RTK_SUCCESS) {                                         \
            printf("err on line %d\n", __LINE__);           \
        }                                                                 \
    } while (0)

ChannelId channelID[PLAYER_NUM] = { -1};
WindowId wndlID[PLAYER_NUM] = { -1};
WindowId fdfwndlID[PLAYER_NUM] = { -1};

/*ion init */
int fbIonFd = -1;
ion_user_handle_t ion_handle;
void * mapIonAddr = NULL;

typedef struct channelPos
{
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
} channelPos;

channelPos chTbl_1[1] =
{
    {0, 0, 960, 540},
};

channelPos chTbl_4[4] =
{
    {0, 0, 960, 540},
    {0, 540, 960, 540},
    {960, 0, 960, 540},
    {960, 540, 960, 540},
};

int gSigDone = 0;

static void sig_handler(int sig)
{
    gSigDone = 1;
}

void printUsage(void)
{
    printf("Usage: ./testapp-slim-rtkrtsp-fetchframe <rtsp://IPaddress:port/stream> [h264/h265] [Number of Windows(1~%d, default 1)]\n", PLAYER_NUM);
    printf("Example: ./testapp-slim-rtkrtsp-fetchframe rtsp://192.168.0.188:43794/profile1 h265 1\n");
    printf("Example: ./testapp-slim-rtkrtsp-fetchframe rtsp://192.168.0.188:43794/profile1 h264 4\n");
}

RtkReturn_e start_nvr(int num, Stream codec)
{
    RtkReturn_e ret = RTK_SUCCESS;
    int i;
    ChannelParams_t param = {0};
    channelPos *pChTbl;

    if (num == 1)
        pChTbl = chTbl_1;
    else if (num > 1 && num <= 4)
        pChTbl = chTbl_4;

    for (i = 0; i < num; i++) {
        channelID[i] = rtk_dec_add_channel_video(-1, -1);
        wndlID[i] = rtk_disp_create(pChTbl[i].x, pChTbl[i].y, pChTbl[i].width, pChTbl[i].height, INPUT_STREAM_LIVE);
        param.vid_codec = (codec == ES_H265) ? VIDEO_H265 : VIDEO_H264;
        rtk_dec_set_channel_video(channelID[i], &param);
        if (channelID[i] >= 0 && wndlID[i] >= 0)
        {
            if (rtk_dec_bind(channelID[i], wndlID[i]) != RTK_SUCCESS)
                ret |= RTK_ERR_FAILURE;

            if (rtk_dec_set_play(CH_STATE_PLAY, channelID[i]) != RTK_SUCCESS)
            {
                printf("set play fail\n");
                ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
                CHECK(ret);
                ret |= RTK_ERR_FAILURE;
            }
        }
        else
            ret |= RTK_ERR_FAILURE;
    }

    return ret;
}

int stop_nvr(int num)
{
    int i;
    RtkReturn_e ret = RTK_SUCCESS;

    if(mapIonAddr != NULL){
        ret = rtk_fetch_frame_munmap(channelID[0], mapIonAddr);
        CHECK(ret);
    }

    if (fbIonFd >= 0){
        se_close();

        ret = ion_free(fbIonFd, ion_handle);
        CHECK(ret);

        ret = ion_close(fbIonFd);
        CHECK(ret);
    }

    for (i = 0; i < num; i++)
    {
        if (wndlID[i] >= 0)
        {
            ret = rtk_disp_destroy(wndlID[i]);
            CHECK(ret);
        }

        if (fdfwndlID[i] >= 0)
        {
            ret = rtk_disp_destroy(fdfwndlID[i]);
            CHECK(ret);
        }

        if (channelID[i] >= 0)
        {
            ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
            CHECK(ret);

            ret = rtk_dec_remove_channel(channelID[i]);
            CHECK(ret);
        }
    }

    //blank all
    ret = rtk_disp_set_blank(1, 1, -1);
    CHECK(ret);

    /* Terminate */
    rtk_serv_terminate();
    return 0;
}

int main(int argc, char **argv)
{
    struct sigaction newact;
    RtspPlayer *players[PLAYER_NUM];
    char *url = NULL;
    int i;
    int number = 1;
    int key;
    RtkReturn_e ret = RTK_SUCCESS;
    Stream codec = ES_H264;

    if (argc < 3) {
        printUsage();
        return 1;
    }

    if ((strcmp(argv[2], "h264") == 0))
        codec = ES_H264;
    else if ((strcmp(argv[2], "h265") == 0))
        codec = ES_H265;
    else
    {
        printUsage();
        return 1;
    }

    newact.sa_handler = (__sighandler_t)sig_handler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGSEGV, &newact, NULL);
    sigaction(SIGILL, &newact, NULL);
    sigaction(SIGABRT, &newact, NULL);
    sigaction(SIGBUS, &newact, NULL);
    sigaction(SIGTERM, &newact, NULL);
    sigaction(SIGKILL, &newact, NULL);
    sigaction(SIGINT, &newact, NULL);
    sigaction(SIGHUP, &newact, NULL);

    url = argv[1];

    /* Initialize */
    ret = rtk_serv_initialize();
    if (ret != RTK_SUCCESS)
    {
        printf("initialize error\n");
        rtk_serv_force_terminate();
        ret = rtk_serv_initialize();
        if (ret != RTK_SUCCESS)
        {
            printf("renitialize error\n");
            return 0;
        }
    }

    rtk_disp_set_videoFB_Resolution(FRAME_BUFFER_1920x1088);

    if ((argc == 4 && (argv[3][0] >= '0') && (argv[3][0] <= '9')) || (argc == 5 && (argv[4][0] >= '0') && (argv[4][0] <= '9')))
    {
        if (argc == 4)
            number = atoi(argv[3]);
        else if (argc == 5)
            number = atoi(argv[4]);

        if (number <= 0 || number > PLAYER_NUM )
        {
            printf("Only support 1~%d windows, reset to 1 window\n", PLAYER_NUM);
            number = 1;
        }
    }

    memset(channelID, 0, sizeof(channelID));
    memset(wndlID, 0, sizeof(wndlID));

    ret = start_nvr(number, codec);
    if (ret != RTK_SUCCESS)
    {
        printf("start nvr fail\n");
        goto fail;
    }
    sleep(1);

    for (i = 0; i < number; i++)
        players[i] = rtsp_player_new(url, channelID[i]);

    for (i = 0; i < number; i++)
    {
        rtsp_player_set_stream(players[i], codec);
        rtsp_player_play(players[i]);
    }

    do {
        printf
        ("Press 's' to scaling down long run, 'l' to original size long run 100 frames, 'f' to fetch one frame and show,'q' to quit.\n");
        fflush(stdout);

        if (key == 's') {
            int mapfd, fbsize;
            unsigned int fbAllocSize;
            unsigned long vPlanePhy;
            unsigned char * bufVirt;

            printf("scaling down to 640*480\n");

            FrameMetadata_t f_metadata = {0};

            /* Allocate ion buffer */
            fbsize = 640 * 480 * 1.5;
            fbIonFd = ion_open();

            ret = ion_alloc(fbIonFd, fbsize, 1 << 12, RTK_PHOENIX_ION_HEAP_MEDIA_MASK, (ION_FLAG_NONCACHED | ION_FLAG_ACPUACC | ION_FLAG_SCPUACC), &ion_handle);
            if (ret < 0)
            {
                printf("In[%s][%d] fail to allocate frame buffer, fbsize:%d", __func__, __LINE__, fbsize);
            }
            ret = ion_phys(fbIonFd, ion_handle, &vPlanePhy, &fbAllocSize);
            if (ret < 0)
            {
                printf("In[%s][%d] ion_phys fail", __func__, __LINE__);
            }
            ret = ion_map(fbIonFd, ion_handle, fbAllocSize, PROT_READ | PROT_WRITE, MAP_SHARED, 0, &bufVirt, &mapfd);
            if (ret < 0)
            {
                printf("In[%s][%d] ion_map fail", __func__, __LINE__);
            }
            close(mapfd);

            /* SE copy*/
            se_open();

            for (;;) {

                /* fetch decoded frame */
                ret = rtk_fetch_frame_mmap(channelID[0], &mapIonAddr, &f_metadata);
                if (ret != RTK_SUCCESS)
                {
                    printf("rtk_fetch_frame_mmap fail\n");
                    goto fail;
                }

                ret = SE_Scaler_API(vPlanePhy, f_metadata.YPhyAddr, 640, 480, 1280, 720, NULL, 0);
                if (ret < 0) {
                    printf("SE_Scaler_API fail\n");
                    goto fail;
                }

                /* free */
                ret = rtk_fetch_frame_munmap(channelID[0], mapIonAddr);
                if (ret != RTK_SUCCESS)
                {
                    printf("rtk_fetch_frame_munmap fail\n");
                    goto fail;
                }

                /* show on display*/
                if (!fdfwndlID[2]) {
                    fdfwndlID[2] = rtk_disp_create(0, 0, 0, 0, INPUT_STREAM_LIVE);
                    rtk_disp_resize(fdfwndlID[2], 0, 540, 640, 480);
                }

                ret = rtk_IVA_disp_image(channelID[0], fdfwndlID[2], vPlanePhy, vPlanePhy + (640 * 480), fbsize, 640, 480);
                if (ret != RTK_SUCCESS)
                {
                    printf("rtk_fetch_frame_munmap fail\n");
                    goto fail;
                }
            }

            se_close();
            ion_free(fbIonFd, ion_handle);
            ion_close(fbIonFd);

        } else if (key == 'l') {
            FrameMetadata_t f_metadata = {0};

            for (i = 0; i < 100; i++) {
                ret = rtk_fetch_frame_mmap(channelID[0], &mapIonAddr, &f_metadata);
                if (ret != RTK_SUCCESS)
                {
                    printf("rtk_fetch_frame_mmap fail\n");
                    goto fail;
                }
                if (!fdfwndlID[1]) {
                    fdfwndlID[1] = rtk_disp_create(0, 0, 0, 0, INPUT_STREAM_LIVE);
                    rtk_disp_resize(fdfwndlID[1], 960, 0, 960, 540);
                }
                rtk_IVA_disp_image(channelID[0], fdfwndlID[1], f_metadata.YPhyAddr, f_metadata.UVPhyAddr, f_metadata.bufSize, f_metadata.width, f_metadata.height);
                rtk_fetch_frame_munmap(channelID[0], mapIonAddr);
            }
        } else if (key == 'f') {
            FrameMetadata_t f_metadata = {0};

            ret = rtk_fetch_frame_mmap(channelID[0], &mapIonAddr, &f_metadata);
            if (ret != RTK_SUCCESS)
            {
                printf("rtk_fetch_frame_mmap fail\n");
                goto fail;
            }

            if (!fdfwndlID[3]) {
                fdfwndlID[3] = rtk_disp_create(0, 0, 0, 0, INPUT_STREAM_LIVE);
                rtk_disp_resize(fdfwndlID[3], 960, 540, 960, 540);
            }

            rtk_IVA_disp_image(channelID[0], fdfwndlID[3], f_metadata.YPhyAddr, f_metadata.UVPhyAddr, f_metadata.bufSize, f_metadata.width, f_metadata.height);
            rtk_fetch_frame_munmap(channelID[0], mapIonAddr);

        }
    } while ((key = getchar()) != 'q' && !gSigDone);

    for (i = 0; i < number; i++)
        rtsp_player_stop(players[i]);

    for (i = 0; i < number; i++)
        rtsp_player_free(players[i]);
fail:
    stop_nvr(number);

    return 0;
}
