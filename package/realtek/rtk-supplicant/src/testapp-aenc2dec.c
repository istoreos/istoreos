#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rtkaenc.h"
#include "rtkadec.h"

#define PLAYER_NUM 1
#define BUFFER_SIZE 10240

#define DEFAULT_PARAM_CODEC 1
#define DEFAULT_PARAM_DEPTH 16
#define DEFAULT_PARAM_RATE 44100
#define DEFAULT_PARAM_CHANNELS 2

int main(int argc, char **argv)
{
    ChannelId player;
    ChannelParams_t param;
    int len;
    char buf[BUFFER_SIZE];

    if (argc < 2) {
	printf("Usage: %s [codec] <[depth] [rate] [channels]>\n", argv[0]);
	printf("Options:\n");
	printf("  codec: 1=PCM, 2=A Law, 3=Mu Law, 4=AAC\n");
	printf("  depth: (default 16)\n");
	printf("  rate: (default 44100)\n");
	printf("  channels: (default 2)\n");
	return 1;
    }

    if (argc > 1)
	param.aud_codec = atoi(argv[1]);
    else
	param.aud_codec = DEFAULT_PARAM_CODEC;

    if (argc > 2)
	param.aud_bitsPerSample = atoi(argv[2]);
    else
	param.aud_bitsPerSample = DEFAULT_PARAM_DEPTH;

    if (argc > 3)
	param.aud_samplerate = atoi(argv[3]);
    else
	param.aud_samplerate = DEFAULT_PARAM_RATE;

    if (argc > 4)
	param.aud_channels = atoi(argv[4]);
    else
	param.aud_channels = DEFAULT_PARAM_CHANNELS;

    printf(" Codec: %d\n Depth: %d\n Rate: %d\n Channels: %d\n",
	   param.aud_codec, param.aud_bitsPerSample, param.aud_samplerate,
	   param.aud_channels);

    /* Start capture/encoding */
//    rtk_aenc_set_device("hw:0,3");
    rtk_aenc_start(&param);

    /* Start decoding/playback */
    player = rtk_adec_add_channel();
    rtk_adec_set_params(player, &param);
    rtk_adec_set_play(CH_STATE_PLAY, player);

    /* FIXME: Stop the loop */
    for (;;) {
	len = rtk_aenc_read(buf, BUFFER_SIZE);
	if (len < 0)
	    break;

	rtk_adec_write_channel(player, buf, len);
    }

    /* Stop decoding/playback */
    rtk_adec_set_play(CH_STATE_STOP, player);
    rtk_adec_remove_channel(player);

    /* Stop capture/encoding */
    rtk_aenc_stop();

    return 0;
}
