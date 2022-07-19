/*
 * testapp-rtspclient-disp.c: example for using rtksink (buffer_send API) to send liveview data to display
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int main(int argc, const char **argv)
{
    ChannelId channelID[9]={-1};
    WindowId wndlID[9]={-1};
    char *uri = NULL;
    char *filepath = NULL;
    pid_t pid;
    int i;
    RtkReturn_e ret = RTK_SUCCESS;

    if (argc < 2 || argc > 3) {
        printf("Usage: %s <rtsp://IPaddress:port/stream> </path/to>\n", argv[0]);
        printf("Example: %s rtsp://192.168.0.188:43794/profile1 /mnt/sda1\n", argv[0]);
        printf("Or: if you don't want to record files\n");
        printf("Usage: %s <rtsp://IPaddress:port/stream>\n", argv[0]);
        printf("Example: %s rtsp://192.168.0.188:43794/profile1\n", argv[0]);
        return 1;
    }

    uri = strdup(argv[1]);
    printf("Play %s\n", uri);

    if (argv[2]) {
        filepath = strdup (argv[2]);
        printf ("files path : %s\n", filepath);

        struct stat st = {0};
        if (stat(filepath, &st) == -1) {
            printf ("%s does not exit!\n", filepath);
            return 1;
        }
        else if ((st.st_mode & S_IFMT) != S_IFDIR) {
            printf ("%s is not a directory!\n", filepath);
            return 1;
        }
    }

    /* Initialize */
    ret = rtk_serv_initialize();
    if(ret != RTK_SUCCESS)
    {
        printf("initialize fail\n");
        return 0;
    }

    for (i = 0; i < PLAYER_NUM; i++) {
        channelID[i] = rtk_dec_add_channel_video(-1, -1);
        wndlID[i] = rtk_disp_create(chTbl[i].x, chTbl[i].y, chTbl[i].width, chTbl[i].height, INPUT_STREAM_LIVE);
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
            goto errExit;
        }
    }


    sleep(3);
    for (i = 0; i < PLAYER_NUM; i++) {
	pid = fork();
	if (pid == 0) {		// child
        char channel_id_num[10];
        sprintf(channel_id_num,"%d", channelID[i]);
        if (argv[2]) {
            char filename[128];
            sprintf(filename, "%s/ipcamera_for_test%d.ts", filepath, i);
            execl("./test-rtspclient", "./test-rtspclient", uri, channel_id_num, filename, NULL);
        } else
            execl("./test-rtspclient", "./test-rtspclient", uri, channel_id_num, NULL);
        sleep(1);
		return 0;
	}
	// parent
    }

	sleep(3);
    //get snapshot
    //printf("snapshot test...\n");
    //rtk_snapshot_display("./snapshot0.jpg");

    sleep(10);

    while(1){
    printf("freeze test...\n");
    ret = rtk_disp_set_freeze(1, 1, wndlID[0]);
    CHECK(ret);
    sleep(5);
    ret = rtk_disp_set_freeze(0, 1, wndlID[0]);
    CHECK(ret);
    sleep(5);

    //blank test
    printf("blank test...\n");
    ret = rtk_disp_set_blank(1, 5, wndlID[0], wndlID[2], wndlID[4],
		       wndlID[6], wndlID[8]);
    CHECK(ret);
    sleep(5);
    ret = rtk_disp_set_blank(0, 5, wndlID[0], wndlID[2], wndlID[4],
		       wndlID[6], wndlID[8]);
    CHECK(ret);
    ret = rtk_disp_set_blank(1, 4, wndlID[1], wndlID[3], wndlID[5],
		       wndlID[7]);
    CHECK(ret);
    sleep(5);
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
#if 0
    printf("resize test...\n");
    rtk_disp_resize(channelID[0], 0, 0, 1536, 810);
    rtk_disp_resize(channelID[1], 0, 810, 384, 270);
    rtk_disp_resize(channelID[2], 384, 810, 384, 270);
    rtk_disp_resize(channelID[3], 768, 810, 384, 270);
    rtk_disp_resize(channelID[4], 1152, 810, 384, 270);
    rtk_disp_resize(channelID[5], 1536, 810, 384, 270);
    rtk_disp_resize(channelID[6], 1536, 0, 384, 270);
    rtk_disp_resize(channelID[7], 1536, 270, 384, 270);
    rtk_disp_resize(channelID[8], 1536, 540, 384, 270);

    rtk_disp_set_blank(1, 7, wndlID[1], wndlID[2], wndlID[3],
		       wndlID[4], wndlID[6], wndlID[7],
		       wndlID[8]);
#else
    ret = rtk_disp_resize(channelID[0], 0, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[1], 0, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[2], 0, 720, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[3], 640, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[4], 640, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[5], 640, 720, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[6], 1280, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[7], 1280, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[8], 1280, 720, 640, 360);
    CHECK(ret);
#endif
    sleep(15);

    //zoom in test: zoom in channel 1
    printf("zoom in test...\n");
    ret = rtk_disp_crop(channelID[0], 112, 60, 360, 240);
    CHECK(ret);
    sleep(10);

#if 0
    rtk_disp_set_blank(0, 7, wndlID[1], wndlID[2], wndlID[3],
		       wndlID[4], wndlID[6], wndlID[7],
		       wndlID[8]);

    sleep(10);
#endif
    printf("channel swap...\n");
    ret = rtk_disp_swap(channelID[0], channelID[8]);
    CHECK(ret);
    sleep(10);

    printf("zoom out test...\n");
    ret = rtk_disp_crop(channelID[0], 0, 0, 1280, 720);
    CHECK(ret);
    sleep(10);

    printf("fps change...\n");
    ret = rtk_disp_set_outputFrameRate(channelID[0], 10);
    CHECK(ret);
    sleep(10);

    printf("fps change back...\n");
    ret = rtk_disp_set_outputFrameRate(channelID[0], 0);
    CHECK(ret);
    sleep(10);

    ret = rtk_disp_resize(channelID[0], 0, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[1], 0, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[2], 0, 720, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[3], 640, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[4], 640, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[5], 640, 720, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[6], 1280, 0, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[7], 1280, 360, 640, 360);
    CHECK(ret);
    ret = rtk_disp_resize(channelID[8], 1280, 720, 640, 360);
    CHECK(ret);
    }


    for (i = 0; i < PLAYER_NUM; i++)
    {
        ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
        CHECK(ret);
    }

errExit:
    for (i = 0; i < PLAYER_NUM; i++) {
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
    free(uri);
    free(filepath);
    /* Terminate */
    ret = rtk_serv_terminate();
    CHECK(ret);

    return 0;
}
