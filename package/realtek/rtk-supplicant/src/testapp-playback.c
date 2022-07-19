#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "rtkcontrol.h"

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

void printUsage(void)
{
    printf("\n\n");
    printf("Usage:\n");
    printf("\t./testapp-playback [OPTION] [FILEPATH]\n");
    printf("[OPTION]\n");
    printf("\t-a: audio test. Mute, Volume......(Default: disable)\n");
    printf("\t-v: video test. Blank, Resize, Crop...... (Default: disable)\n");
    printf("\t-d: DP output. (Default: disable)\n");
    printf("\t-h: HDMI output. (Default: enable, 1080P@60)\n");
    printf("\t\t0)1080P@60 \t4)1080I@50\n");
    printf("\t\t1)1080P@50 \t5)720P@60\n");
    printf("\t\t2)1080P@30 \t6)720P@50\n");
    printf("\t\t3)1080I@60 \t7)4k@30\n");
    printf("\t-n: number channel output. (Default: 9 channels)\n");
    printf("\t-f: input stream is file type. (Default: live type)\n");
    printf("\n[FILEPATH]\n");
    printf("\tEX: /root/nfs/Testfiles/mp4/720p.mp4\n\n");
    printf("\nExample:\n");
    printf("\t./testapp-playback -h 2 -f -n 1 /root/nfs/Testfiles/mp4/720p.mp4\n\n");
}

int main(int argc, char* argv[])
{
    ChannelId channelID[9] = {-1};
    WindowId wndlID[9] = {-1};
    double volume;
    char *filename = NULL;
    int ch;
    unsigned int audioTest = 0;
    unsigned int videoTest = 0;
    unsigned int hdmiOutput = 0;
    unsigned int hdmitype = 0;
    unsigned int dpOutput = 0;
    unsigned int chNum = PLAYER_NUM;
    InputStreamType_e live = INPUT_STREAM_LIVE;
    unsigned char value = 0;
    RtkReturn_e ret = RTK_SUCCESS;
    int i = 0;

    while((ch=getopt(argc, argv, "adfh:n:v")) != -1)
    {
        switch(ch)
        {
            case 'a':
                audioTest = 1;
                break;
            case 'd':
                dpOutput = 1;
                break;
            case 'h':
                hdmiOutput = 1;
                hdmitype = atoi(optarg);
                break;
            case 'v':
                videoTest = 1;
                break;
            case 'n':
                chNum = atoi(optarg);
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

    if(chNum < PLAYER_NUM && (audioTest || videoTest))
    {
        printf("Only 9 channel can do video/audio test!\n");
        return 0;
    }

    if (argv[optind])
        filename = strdup(argv[optind]);
    else
    {
        printUsage();
        return 0;
    }

    printf("Play %s\n",filename);

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
    {
        if(hdmitype == 0)
        {
            ret = rtk_disp_set_output(HDMI_1080P_60, DP_NONE);
            printf("HDMI 1080P@60\n");
        }
        else if(hdmitype == 1)
        {
            ret = rtk_disp_set_output(HDMI_1080P_50, DP_NONE);
            printf("HDMI 1080P@50\n");
        }
        else if(hdmitype == 2)
        {
            ret = rtk_disp_set_output(HDMI_1080P_30, DP_NONE);
            printf("HDMI 1080P@30\n");
        }
        else if(hdmitype == 3)
        {
            ret = rtk_disp_set_output(HDMI_1080I_60, DP_NONE);
            printf("HDMI 1080I@60\n");
        }
        else if(hdmitype == 4)
        {
            ret = rtk_disp_set_output(HDMI_1080I_50, DP_NONE);
            printf("HDMI 1080I@50\n");
        }
        else if(hdmitype == 5)
        {
            ret = rtk_disp_set_output(HDMI_720P_60, DP_NONE);
            printf("HDMI 720P@60\n");
        }
        else if(hdmitype == 6)
        {
            ret = rtk_disp_set_output(HDMI_720P_50, DP_NONE);
            printf("HDMI 720P@50\n");
        }
        else if(hdmitype == 7)
        {
            ret = rtk_disp_set_output(HDMI_4K_30, DP_NONE);
            printf("HDMI 4K@30\n");
        }
    }

    if(ret != RTK_SUCCESS)
    {
        printf("set output format fail\n");
    }

    printf("%s\n", live?"LIVE":"FILE");

    for (i = 0; i < chNum; i++) {
        channelID[i] = rtk_dec_add_channel();
        if(rtk_dec_open(channelID[i], filename) != RTK_SUCCESS)
        {
            ret = rtk_dec_remove_channel(channelID[i]);
            CHECK(ret);
            printf("file is not exist\n");
            goto errExit;
        }
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
        sleep(5); //it is optional
    }


    if(audioTest)
    {
        ret = rtk_dec_start_audio(channelID[0]);
        CHECK(ret);
        sleep(25);
        ret = rtk_dec_stop_audio(channelID[0]);
        CHECK(ret);
        sleep(5);

        ret = rtk_dec_start_audio(channelID[0]);
        CHECK(ret);
        sleep(25);
        ret = rtk_dec_stop_audio(channelID[0]);
        CHECK(ret);
        sleep(5);

        if(chNum == PLAYER_NUM)
        {
            ret = rtk_dec_start_audio(channelID[6]);
            CHECK(ret);

            sleep(20);
            ret = rtk_dec_set_mute(true, channelID[6]);//mute on
            CHECK(ret);

            sleep(10);
            ret = rtk_dec_set_mute(false, channelID[6]);//mute off
            CHECK(ret);

            sleep(10);
            ret = rtk_dec_set_volume(5.0f, channelID[6]);//set volume
            CHECK(ret);

            sleep(20);
            ret = rtk_dec_increase_volume(channelID[6]);//increase 0.5f each time
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_get_volume(channelID[6], &volume);
            CHECK(ret);
            printf ("audio volume: %lf ! \n", volume);

            sleep(2);
            ret = rtk_dec_increase_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_increase_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_get_volume(channelID[6], &volume);
            CHECK(ret);
            printf ("audio volume: %lf ! \n", volume);

            sleep(2);
            ret = rtk_dec_increase_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_decrease_volume(channelID[6]);//decrease 0.5f each time
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_decrease_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_get_volume(channelID[6], &volume);
            CHECK(ret);
            printf ("audio volume: %lf ! \n", volume);

            sleep(2);
            ret = rtk_dec_decrease_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_decrease_volume(channelID[6]);
            CHECK(ret);

            sleep(5);
            ret = rtk_dec_set_volume(1.0f, channelID[6]);//set volume
            CHECK(ret);

            sleep(20);
            ret = rtk_dec_decrease_volume(channelID[6]);
            CHECK(ret);
            sleep(5);
            ret = rtk_dec_get_volume(channelID[6], &volume);
            CHECK(ret);
            printf ("audio volume: %lf ! \n", volume);
            sleep(2);
            sleep(10);
            ret = rtk_dec_stop_audio(channelID[6]);
            CHECK(ret);
            sleep(5);
        }
    }

    if(videoTest && (chNum == PLAYER_NUM))
    {
        //blank test
        printf("blank test...\n");
        ret = rtk_disp_set_blank(1, 5, wndlID[0], wndlID[2], wndlID[4],
                   wndlID[6], wndlID[8]);
        CHECK(ret);

        sleep(15);
        ret = rtk_disp_set_blank(0, 5, wndlID[0], wndlID[2], wndlID[4],
                   channelID[6], wndlID[8]);
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
        ret = rtk_disp_resize(wndlID[1], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[2], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[3], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[4], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[5], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[6], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[7], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[8], 0, 0, 0, 0);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[0], 0, 0, 1920, 1080);
        CHECK(ret);

        sleep(15);

        //resize test: modify the display layout and only show channel 1, 2
        printf("resize test...\n");
        ret = rtk_disp_resize(wndlID[0], 0, 0, 1536, 810);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[1], 0, 810, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[2], 384, 810, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[3], 768, 810, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[4], 1152, 810, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[5], 1536, 810, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[6], 1536, 0, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[7], 1536, 270, 384, 270);
        CHECK(ret);
        ret = rtk_disp_resize(wndlID[8], 1536, 540, 384, 270);
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

        sleep(10);

        ret = rtk_disp_set_blank(0, 7, wndlID[1], wndlID[2], wndlID[3],
                   wndlID[4], wndlID[6], wndlID[7],
                   wndlID[8]);
        CHECK(ret);

        sleep(10);

        printf("channel swap...\n");
        ret = rtk_disp_swap(wndlID[0], wndlID[8]);
        CHECK(ret);

        sleep(10);

        printf("zoom out test...\n");
        ret = rtk_disp_crop(wndlID[0], 0, 0, 1280, 720);
        CHECK(ret);

        sleep(10);

        printf("fps change...\n");
        ret = rtk_disp_set_outputFrameRate(channelID[0], 10);
        CHECK(ret);

        sleep(10);

        printf("fps change back...\n");
        ret = rtk_disp_set_outputFrameRate(channelID[0], 0);
        CHECK(ret);

        printf("brightness change...\n");
        ret = rtk_disp_get_brightness(&value);
        CHECK(ret);
        ret = rtk_disp_set_brightness(64);
        CHECK(ret);
        sleep(10);

        printf("brightness change back...\n");
        ret = rtk_disp_set_brightness(value);
        CHECK(ret);
        sleep(5);

        printf("contrast change...\n");
        ret = rtk_disp_get_contrast(&value);
        CHECK(ret);
        ret = rtk_disp_set_contrast(0);
        CHECK(ret);
        sleep(10);

        printf("contrast change back...\n");
        ret = rtk_disp_set_contrast(value);
        CHECK(ret);
        sleep(5);

        printf("hue change...\n");
        ret = rtk_disp_get_hue(&value);
        CHECK(ret);
        ret = rtk_disp_set_hue(55);
        CHECK(ret);
        sleep(10);

        printf("hue change back...\n");
        ret = rtk_disp_set_hue(value);
        CHECK(ret);
        sleep(5);

        printf("saturation change...\n");
        ret = rtk_disp_get_saturation(&value);
        CHECK(ret);
        ret = rtk_disp_set_saturation(5);
        CHECK(ret);
        sleep(10);

        printf("saturation change back...\n");
        ret = rtk_disp_set_saturation(value);
        CHECK(ret);
        sleep(5);

        //sleep(10);
        //printf("snapshot test...\n");
        //rtk_snapshot_display("/tmp/snapshot.jpg");

    }

    sleep(100);

     for (i = 0; i < chNum; i++)
    {
        ret = rtk_disp_set_blank(1, 1, wndlID[i]);
        CHECK(ret);
    }

    for (i = 0; i < chNum; i++)
    {
        ret = rtk_dec_set_play(CH_STATE_STOP, channelID[i]);
        CHECK(ret);
    }

errExit:
    for (i = 0; i < chNum; i++) {
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
