/*
 * testapp-filewrite-disp.c: example for using buffer_send API to send stream or frame to display
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rtkcontrol.h"
#include "testapp-utils.h"


#define PLAYER_NUM	9

#define CHECK(x) do {                                                     \
        if (x != RTK_SUCCESS) {                                         \
            printf("err on line %d\n", __LINE__);           \
        }                                                                 \
    } while (0)

typedef struct channelPos
{
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
}channelPos;

channelPos chTbl[PLAYER_NUM] =
{
    {0, 0, 640, 360},
    {0, 360, 640, 360},
    {0, 720, 640, 360},
    {640, 0, 640, 360},
    {640, 360, 640, 360},
    {640, 720, 640, 360},
    {1280, 0, 640, 360},
    {1280, 360, 640, 360},
    {1280, 720, 640, 360},
};

// set 1 to enable, default is 0 as disabled
int debuglevel = 1;


void printUsage(void)
{
    printf("\n\n");
    printf("Usage:\n");
    printf("\t./testapp-filewrite-disp [OPTION] [FILEPATH]\n");
    printf("[OPTION]\n");
    printf("\t-d: DP output. (Default: disable)\n");
    printf("\t-h: HDMI output. (Default: enable)\n");
    printf("\t-f: input stream is file type. (Default: live type)\n");
    printf("\n[FILEPATH]\n");
    printf("\tEX: /root/nfs/Testfiles/mp4/720p.mp4\n\n");
}


int main(int argc, char* argv[])
{
    ChannelId channelID[9] = {-1};
    WindowId wndlID[9] = {-1};
    char *filename = NULL;
    pid_t pid;
    int i;
    int ch;
    unsigned int hdmiOutput = 0;
    unsigned int dpOutput = 0;
    InputStreamType_e live = INPUT_STREAM_LIVE;
    RtkReturn_e ret = RTK_SUCCESS;

    while((ch=getopt(argc, argv, "dhf")) != -1)
    {
        switch(ch)
        {
            case 'd':
                dpOutput = 1;
                break;
            case 'h':
                hdmiOutput = 1;
                break;
            case 'f':
                live = INPUT_STREAM_FILE;
                break;
            default:
                printUsage();
                return 0;
                break;
        }
    }

    if (argv[optind])
        filename = strdup(argv[optind]);
    else
    {
        printUsage();
        return 0;
    }

    printf("Play %s\n", filename);

    /* Initialize */
    ret = rtk_serv_initialize();
    if(ret != RTK_SUCCESS)
    {
        printf("initialize fail\n");
        return 0;
    }

    if(hdmiOutput && dpOutput)
        ret = rtk_disp_set_output(HDMI_1080P_60, DP_1080P_60);
    else if(dpOutput)
        ret = rtk_disp_set_output(HDMI_NONE, DP_1080P_60);
    else
        ret = rtk_disp_set_output(HDMI_1080P_60, DP_NONE);

    if(ret != RTK_SUCCESS)
    {
        printf("set output format fail\n");
    }


    for (i = 0; i < PLAYER_NUM; i++) {
        channelID[i] = rtk_dec_add_channel_video(-1, -1);
        wndlID[i] = rtk_disp_create(chTbl[i].x, chTbl[i].y, chTbl[i].width, chTbl[i].height, live);
        if(channelID[i]>=0 && wndlID[i]>=0)
        {
            if(rtk_dec_bind(channelID[i], wndlID[i]) != RTK_SUCCESS)
                goto errExit;

            if(rtk_dec_set_play(CH_STATE_PLAY, channelID[i]) != RTK_SUCCESS)
            {
                printf("set play fail\n");
                ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
                CHECK(ret);
                goto errExit;
            }
        }
        else
        {
            printf("init fail\n");
            goto errExit;
        }
    }

    sleep(3);
    for (i = 0; i < 9; i++) {
	pid = fork();
	if (pid == 0) {		// child
	    do_filewrite(channelID[i], filename);
	    return 0;
	}
	// parent
    }

    //blank test
    sleep(10);
    printf("blank test...\n");
    ret = rtk_disp_set_blank(1, 5, wndlID[0], wndlID[2], wndlID[4],
		       wndlID[6], wndlID[8]);
    CHECK(ret);
    sleep(15);
    ret = rtk_disp_set_blank(0, 5, wndlID[0], wndlID[2], wndlID[4],
		       wndlID[6], wndlID[8]);
    CHECK(ret);
    ret = rtk_disp_set_blank(1, 4, wndlID[1], wndlID[3], wndlID[5],
		       wndlID[7]);
    CHECK(ret);
    sleep(15);
    ret = rtk_disp_set_blank(0, 4, wndlID[1], wndlID[3], wndlID[5],
		       wndlID[7]);
    CHECK(ret);
    sleep(5);

    //resize test: channel 0 full screen
    printf("full screen test...\n");
    ret = rtk_disp_resize(channelID[1], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[2], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[3], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[4], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[5], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[6], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[7], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[8], 0, 0, 0, 0);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[0], 0, 0, 1920, 1080);
    CHECK(ret);

    sleep(15);

    //resize test: modify the display layout and only show channel 1, 2
    printf("resize test...\n");
    ret = rtk_disp_resize(channelID[0], 0, 0, 1536, 810);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[1], 0, 810, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[2], 384, 810, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[3], 768, 810, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[4], 1152, 810, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[5], 1536, 810, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[6], 1536, 0, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[7], 1536, 270, 384, 270);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[8], 1536, 540, 384, 270);
    CHECK(ret);

    sleep(15);

    ret = rtk_disp_set_blank(1, 7, wndlID[1], wndlID[2], wndlID[3],
		       wndlID[4], wndlID[6], wndlID[7],
		       wndlID[8]);
    CHECK(ret);

    //zoom in test: zoom in channel 1
    printf("zoom in test...\n");
    ret = rtk_disp_crop(channelID[0], 112, 60, 360, 240);
    CHECK(ret);
    sleep(15);
    ret = rtk_disp_crop(channelID[0], 0, 0, 1280, 720);
    CHECK(ret);
    sleep(10);
    ret = rtk_disp_set_blank(0, 7, wndlID[1], wndlID[2], wndlID[3],
		       wndlID[4], wndlID[6], wndlID[7],
		       wndlID[8]);
    CHECK(ret);

    sleep(10);

    //printf("snapshot test...\n");
    //ret = rtk_snapshot_display("/tmp/snapshot.jpg");
    //CHECK(ret);

    sleep(180);

    ret = rtk_disp_set_blank(1, 9, wndlID[0], wndlID[1], wndlID[2], wndlID[3],
    	       wndlID[4], wndlID[5], wndlID[6], wndlID[7],
    	       wndlID[8]);
    CHECK(ret);

    for (i = 0; i < PLAYER_NUM; i++)
    {
        ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
        CHECK(ret);
    }

errExit:
    for (i = 0; i < PLAYER_NUM; i++)
    {
        if(wndlID[i]>=0)
        {
            ret = rtk_disp_destroy(wndlID[i]);
            CHECK(ret);
        }

        if(channelID[i]>=0)
        {
            ret = rtk_dec_remove_channel(channelID[i]);
            CHECK(ret);
        }
    }

    free(filename);
    /* Terminate */
    ret = rtk_serv_terminate();
    CHECK(ret);

    return 0;
}
