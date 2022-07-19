#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "rtkcontrol.h"

// set 1 to enable, default is 0 as disabled
int debuglevel = 1;


void printUsage(void)
{
    printf("\n\n");
    printf("Usage:\n");
    printf("\t./testapp-playback-speed [OPTION] [FILEPATH]\n");
    printf("[OPTION]\n");
    printf("\t-d: DP output. (Default: disable)\n");
    printf("\t-h: HDMI output. (Default: enable)\n");
    printf("\t-f: input stream is file type. (Default: live type)\n");
    printf("\n[FILEPATH]\n");
    printf("\tEX: /root/nfs/Testfiles/mp4/720p.mp4\n\n");
}

int main(int argc, char* argv[])
{
    ChannelId channelID[9];
    WindowId wndlID[9];
#ifdef MULTI
    double volume;
#endif
    char *filename = NULL;
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

    channelID[0] = rtk_dec_add_channel();
    channelID[1] = rtk_dec_add_channel();
    channelID[2] = rtk_dec_add_channel();
    channelID[3] = rtk_dec_add_channel();

    /* Set the URI to play */
    //multaudio.mp4:720p 24fps(h264+aac)
    //720p.mp4:720p 30fps(h264+aac)
    rtk_dec_open(channelID[0], filename);
    rtk_dec_open(channelID[1], filename);
    rtk_dec_open(channelID[2], filename);
    rtk_dec_open(channelID[3], filename);

    wndlID[0] = rtk_disp_create(0, 0, 960, 540, live);
    wndlID[1] = rtk_disp_create(0, 540, 960, 540, live);
    wndlID[2] = rtk_disp_create(960, 0, 960, 540, live);
    wndlID[3] = rtk_disp_create(960, 540, 960, 540, live);

    rtk_dec_bind(channelID[0], wndlID[0]);
    rtk_dec_bind(channelID[1], wndlID[1]);
    rtk_dec_bind(channelID[2], wndlID[2]);
    rtk_dec_bind(channelID[3], wndlID[3]);

    /* Start playing */
    rtk_dec_set_play(CH_STATE_PLAY, channelID[0]);
    sleep(5);
    rtk_dec_set_play(CH_STATE_PLAY, channelID[1]);
    sleep(5);
    rtk_dec_set_play(CH_STATE_PLAY, channelID[2]);
    sleep(5);
    rtk_dec_set_play(CH_STATE_PLAY, channelID[3]);

    sleep(5);
    rtk_dec_start_audio(channelID[0]);
    sleep(5);

    rtk_dec_speed(channelID[0], 2);

    sleep(100);



    //blank test
    rtk_disp_set_blank(1, 4, wndlID[0], wndlID[1], wndlID[2], wndlID[3]);
    sleep(1);


    rtk_disp_destroy(wndlID[0]);
    rtk_disp_destroy(wndlID[1]);
    rtk_disp_destroy(wndlID[2]);
    rtk_disp_destroy(wndlID[3]);


    rtk_dec_set_play(CH_STATE_STOP, channelID[0]);
    rtk_dec_set_play(CH_STATE_STOP, channelID[1]);
    rtk_dec_set_play(CH_STATE_STOP, channelID[2]);
    rtk_dec_set_play(CH_STATE_STOP, channelID[3]);

    rtk_dec_remove_channel(channelID[0]);
    rtk_dec_remove_channel(channelID[1]);
    rtk_dec_remove_channel(channelID[2]);
    rtk_dec_remove_channel(channelID[3]);

    sleep(1);

    free(filename);

    /* Terminate */
    rtk_serv_terminate();

    return 0;
}
