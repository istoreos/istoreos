#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <libgen.h>

#include "rtkcontrol.h"
#include "rtkrtsp.h"

#define PLAYER_NUM	9

#define HLS_TARGETDURATION	6

#define CHECK(x) do {                                                     \
        if (x != RTK_SUCCESS) {                                         \
            printf("err on line %d\n", __LINE__);           \
        }                                                                 \
    } while (0)

ChannelId channelID[PLAYER_NUM] = {-1};
WindowId wndlID[PLAYER_NUM] = {-1};

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

RtkReturn_e start_nvr(void)
{
    RtkReturn_e ret = RTK_SUCCESS;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        channelID[i] = rtk_dec_add_channel_video(-1, -1);
        wndlID[i] = rtk_disp_create(chTbl[i].x, chTbl[i].y, chTbl[i].width, chTbl[i].height, INPUT_STREAM_LIVE);
        if(channelID[i]>=0 && wndlID[i]>=0)
        {
            if(rtk_dec_bind(channelID[i], wndlID[i]) != RTK_SUCCESS)
                ret |= RTK_ERR_FAILURE;

            if(rtk_dec_set_play(CH_STATE_PLAY, channelID[i]) != RTK_SUCCESS)
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

int stop_nvr()
{
    int i;
    RtkReturn_e ret = RTK_SUCCESS;

    for (i = 0; i < PLAYER_NUM; i++)
    {
        if(wndlID[i]>=0)
        {
            ret = rtk_disp_set_blank(1, 1, wndlID[i]);
            CHECK(ret);

            ret = rtk_disp_destroy(wndlID[i]);
            CHECK(ret);
        }

        if(channelID[i]>=0)
        {
            ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
            CHECK(ret);

            ret = rtk_dec_remove_channel(channelID[i]);
            CHECK(ret);
        }
    }

    /* Terminate */
    ret = rtk_serv_terminate();
    CHECK(ret);

    return 0;
}

int main(int argc, char **argv)
{
    RtspPlayer *players[PLAYER_NUM];
    char *url = NULL;
    char path[80], *dirc;
    int i;
    int mode;
    int key;
    time_t now;
    struct tm *tm;
    char tstr[16];
    RtkReturn_e ret = RTK_SUCCESS;

    if (argc < 2) {
	printf("Usage: %s <rtsp://IPaddress:port/stream> [/path/to/rec] [HDMI output resoultion(default 1080p@60)]\n",
	       argv[0]);
	printf("HDMI output resolution:\n");
	printf("\t0)1080P@60\t4)1080I@50\n");
	printf("\t1)1080P@50\t5)720P@60\n");
	printf("\t2)1080P@30\t6)720P@50\n");
	printf("\t3)1080I@60\t7)4K@30\n");
	printf
	    ("Example: %s rtsp://192.168.0.188:43794/profile1 /home/rec 0\n",
	     argv[0]);
	return 1;
    }

    url = argv[1];

    /* Initialize */
    ret = rtk_serv_initialize();
    if(ret != RTK_SUCCESS)
    {
        printf("initialize fail\n");
        return 0;
    }

    if((argc == 3 && (argv[2][0] >='0') && (argv[2][0] <='9')) || (argc == 4 && (argv[3][0] >='0') && (argv[3][0] <='9')))
    {
        if(argc == 3)
            mode = atoi(argv[2]);
        else if(argc == 4)
            mode = atoi(argv[3]);

        switch(mode)
        {
            case 1:
                ret = rtk_disp_set_output(HDMI_1080P_50, DP_NONE);
                printf("1080P@50\n");
                break;
            case 2:
                ret = rtk_disp_set_output(HDMI_1080P_30, DP_NONE);
                printf("1080P@30\n");
                break;
            case 3:
                ret = rtk_disp_set_output(HDMI_1080I_60, DP_NONE);
                printf("1080I@60\n");
                break;
            case 4:
                ret = rtk_disp_set_output(HDMI_1080I_50, DP_NONE);
                printf("1080I@50\n");
                break;
            case 5:
                ret = rtk_disp_set_output(HDMI_720P_60, DP_NONE);
                printf("720P@60\n");
                break;
            case 6:
                ret = rtk_disp_set_output(HDMI_720P_50, DP_NONE);
                printf("720P@50\n");
                break;
            case 7:
                ret = rtk_disp_set_output(HDMI_4K_30, DP_NONE);
                printf("4K@30\n");
                break;
            default:
            case 0:
                ret = rtk_disp_set_output(HDMI_1080P_60, DP_NONE);
                printf("1080P@60\n");
                break;
        }
    }

    if(ret != RTK_SUCCESS)
    {
        printf("set output format fail\n");
    }

    memset(channelID, 0, sizeof(channelID));
    memset(wndlID, 0, sizeof(wndlID));

    ret = start_nvr();
    if(ret != RTK_SUCCESS)
    {
        printf("start nvr fail\n");
        goto fail;
    }
    sleep(1);

    for (i = 0; i < PLAYER_NUM; i++)
    	players[i] = rtsp_player_new(url, channelID[i]);

    /* Do recording */
    if((argc == 3 && ((argv[2][0] < '0') || (argv[2][0] > '9'))) || (argc == 4)) {
	now = time(NULL);
	tm = localtime(&now);
	strftime(tstr, sizeof(tstr), "%Y%m%d_%H%M%S", tm);

	for (i = 0; i < PLAYER_NUM; i++) {
	    memset(path, 0, sizeof(path));
	    sprintf(path, "%s/%d/%s", argv[2], i, tstr);
	    dirc = strdup(path);
	    mkdir(dirname(dirc), 0755);
	    mkdir(path, 0755);
	    free(dirc);

	    rtsp_player_rec_start(players[i], path, HLS_TARGETDURATION);
	}
    }

    for (i = 0; i < PLAYER_NUM; i++)
	rtsp_player_play(players[i]);

    do {
	printf
	    ("Press 'q' to quit program, 'h' to start HLS, 'x' to stop HLS, 'c' to change HLS.\n");
	fflush(stdout);

	if (key == 'h') {
	    if (argc > 2) {
		now = time(NULL);
		tm = localtime(&now);
		strftime(tstr, sizeof(tstr), "%Y%m%d_%H%M%S", tm);

		for (i = 0; i < PLAYER_NUM; i++) {
		    memset(path, 0, sizeof(path));
		    sprintf(path, "%s/%d/%s", argv[2], i, tstr);
		    dirc = strdup(path);
		    mkdir(dirname(dirc), 0755);
		    mkdir(path, 0755);
		    free(dirc);

		    rtsp_player_rec_start(players[i], path, HLS_TARGETDURATION);
		}
	    } else
		printf("ERROR: No path\n");
	} else if (key == 'x') {
	    for (i = 0; i < PLAYER_NUM; i++) {
		rtsp_player_rec_stop(players[i]);
	    }
	} else if (key == 'c') {
	    if (argc > 2) {
		now = time(NULL);
		tm = localtime(&now);
		strftime(tstr, sizeof(tstr), "%Y%m%d_%H%M%S", tm);

		for (i = 0; i < PLAYER_NUM; i++) {
		    memset(path, 0, sizeof(path));
		    sprintf(path, "%s/%d/%s", argv[2], i, tstr);
		    dirc = strdup(path);
		    mkdir(dirname(dirc), 0755);
		    mkdir(path, 0755);
		    free(dirc);

		    rtsp_player_rec_change(players[i], path, HLS_TARGETDURATION);
		}
	    }
	}
    } while ((key = getchar()) != 'q');

    for (i = 0; i < PLAYER_NUM; i++)
	rtsp_player_stop(players[i]);

    for (i = 0; i < PLAYER_NUM; i++)
	rtsp_player_free(players[i]);
fail:
    stop_nvr();

    return 0;
}
