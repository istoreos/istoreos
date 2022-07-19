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

typedef struct
{
  unsigned char *bitstream;
  unsigned int bitstream_len;
  unsigned char *sps_buf;
  unsigned int sps_len;
  unsigned char *pps_buf;
  unsigned int pps_len;
} stream_t;

// set 1 to enable, default is 0 as disabled
int debuglevel = 1;

#define WAIT_PLAYTIME	180

int main(int argc, char *argv[])
{
    ChannelId ch;
    WindowId wnd;
    ChannelState_e state;
    stream_t *stream;
    unsigned char sps[512], pps[512];
    unsigned char bs[5120000];    // 5 MB
    int buf_size;
    int fd;
    int ret;
    char c_input;
    RtkReturn_e err = RTK_SUCCESS;


    if (argc < 2) {
        printf ("Usage: %s <bitstream> [<SPS> <PPS>]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Initialize */
    err = rtk_serv_initialize();
    if(err != RTK_SUCCESS)
    {
        printf("initialize fail\n");
        return 0;
    }

    /* Set up window and channel */
    wnd = rtk_disp_create(0, 0, 1920, 1080, INPUT_STREAM_LIVE);
    ch = rtk_dec_add_channel_video(-1, -1);
    rtk_dec_bind(ch, wnd);
    printf("wnd=%d ch=%d\n", wnd, ch);

    rtk_dec_set_play(CH_STATE_PLAY, ch);


    /* Allocate memory for structures */
    stream = malloc (sizeof (stream_t));
    memset (stream, 0, sizeof (stream_t));


    /* Get bitstream */
    if (argc > 1) {
        memset (bs, 0, sizeof (bs));
        fd = open (argv[1], O_RDONLY);
        if (fd > 0) {
            stream->bitstream_len = read (fd, bs, sizeof (bs));
            stream->bitstream = bs;
        }
        close (fd);
        printf ("Read stream size: %d\n", stream->bitstream_len);
    }

    /* Get SPS */
    if (argc > 2) {
        memset (sps, 0, sizeof (sps));
        fd = open (argv[2], O_RDONLY);
        if (fd > 0) {
            stream->sps_len = read (fd, sps, sizeof (sps));
            stream->sps_buf = sps;
        }
        close (fd);
        printf ("Read SPS size: %d\n", stream->sps_len);
    }

    /* Get PPS */
    if (argc > 3) {
        memset (pps, 0, sizeof (pps));
        fd = open (argv[3], O_RDONLY);
        if (fd > 0) {
            stream->pps_len = read (fd, pps, sizeof (pps));
            stream->pps_buf = pps;
        }
        close (fd);
        printf ("Read PPS size: %d\n", stream->pps_len);
    }

    buf_size = stream->sps_len + stream->pps_len + stream->bitstream_len;

    if (buf_size < 1)
        return RTK_ERR_INVALID_PARAM;


    sleep(1);

    do
    {
        /* Call buffer_send API to send stream or frame to channel */
        ret = rtk_buffer_send(ch, stream->sps_buf,  stream->sps_len, -1, 0);

        if(ret == -1){
            printf("rtk_buffer_send(ch=%d): write %d \n", ch, ret);
        }

        ret = rtk_buffer_send(ch, stream->pps_buf, stream->pps_len, -1, 0);

        if(ret == -1){
            printf("rtk_buffer_send(ch=%d): write %d \n", ch, ret);
        }

        ret = rtk_buffer_send(ch, stream->bitstream, stream->bitstream_len, -1 , 0);

        if(ret == -1){
            printf("rtk_buffer_send(ch=%d): write %d \n", ch, ret);
        }

        printf("Put any key to continue. or q to quit!\n");
        c_input = getchar();
    }while(c_input !=  'q');

    /* Wait for playing */
    printf("sleep %d s\n", 5);
    sleep(5);

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
