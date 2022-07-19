/*
 * testapp-filewrite-wnd.c: example for using buffer_send API to send stream or frame to a window
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

// set 1 to enable, default is 0 as disabled
int debuglevel = 1;

#define WAIT_PLAYTIME	180

void printUsage(void)
{
    printf("\n\n");
    printf("Usage:\n");
    printf("\t./testapp-filewrite-wnd [OPTION] [FILEPATH]\n");
    printf("[OPTION]\n");
    printf("\t-d: DP output. (Default: disable)\n");
    printf("\t-h: HDMI output. (Default: enable)\n");
    printf("\t-f: input stream is file type. (Default: live type)\n");
    printf("\n[FILEPATH]\n");
    printf("\tEX: /root/nfs/Testfiles/mp4/720p.mp4\n\n");
}

int main(int argc, char *argv[])
{
    ChannelId ch;
    WindowId wnd;
    ChannelState_e state;
    int i;
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

    if (!argv[optind])
    {
        printUsage();
        return 0;
    }

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

    /* Set up window and channel */
    wnd = rtk_disp_create(0, 0, 640, 360, live);
    ch = rtk_dec_add_channel_video(-1, -1);
    rtk_dec_bind(ch, wnd);
    printf("wnd=%d ch=%d\n", wnd, ch);

    rtk_dec_set_play(CH_STATE_PLAY, ch);

    sleep(1);

    for (i = optind; i < argc; i++) {
	do_filewrite(ch, argv[i]);
    }

    /* Wait for playing */
    printf("sleep %d s\n", WAIT_PLAYTIME);
    sleep(WAIT_PLAYTIME);

    rtk_dec_get_play(ch, &state);
    printf("ch=%d state %d\n", ch, state);


    rtk_disp_set_blank(1, 1, wnd);

    rtk_disp_destroy(wnd);
    sleep(1);


    rtk_dec_set_play(CH_STATE_STOP, ch);

    /* Clean up channel and window */
    rtk_dec_remove_channel(ch);

    /* Terminate */
    rtk_serv_terminate();

    return 0;
}
