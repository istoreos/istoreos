#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rtkadec.h"

#define BUFFER_SIZE 1024

#define DEFAULT_PARAM_CODEC 1
#define DEFAULT_PARAM_DEPTH 16
#define DEFAULT_PARAM_RATE 44100
#define DEFAULT_PARAM_CHANNELS 2

int main(int argc, char **argv)
{
    ChannelId player;
    ChannelParams_t param;
    int fd, len;
    char buf[BUFFER_SIZE];

    if (argc < 2) {
	printf
	    ("Usage: %s [/path/to/audiofile] <[codec] [depth] [rate] [channels]>\n",
	     argv[0]);
	printf("Options:\n");
	printf("  codec: 1=PCM, 2=A Law, 3=Mu Law, 4=AAC (default 1)\n");
	printf("  depth: (default 16)\n");
	printf("  rate: (default 44100)\n");
	printf("  channels: (default 2)\n");
	return 1;
    }

    if (argc > 2)
	param.aud_codec = atoi(argv[2]);
    else
	param.aud_codec = DEFAULT_PARAM_CODEC;

    if (argc > 3)
	param.aud_bitsPerSample = atoi(argv[3]);
    else
	param.aud_bitsPerSample = DEFAULT_PARAM_DEPTH;

    if (argc > 4)
	param.aud_samplerate = atoi(argv[4]);
    else
	param.aud_samplerate = DEFAULT_PARAM_RATE;

    if (argc > 5)
	param.aud_channels = atoi(argv[5]);
    else
	param.aud_channels = DEFAULT_PARAM_CHANNELS;

    printf(" Codec: %d\n Depth: %d\n Rate: %d\n Channels: %d\n",
	   param.aud_codec, param.aud_bitsPerSample, param.aud_samplerate,
	   param.aud_channels);

    player = rtk_adec_add_channel();
    rtk_adec_set_params(player, &param);

    rtk_adec_set_play(CH_STATE_PLAY, player);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
	printf("Open %s failed\n", argv[1]);
	return 1;
    }

    for (;;) {
	len = read(fd, buf, BUFFER_SIZE);
	if (len <= 0)
	    break;

	rtk_adec_write_channel(player, buf, len);
    }

    /* Wait playback */
    sleep(10);

    rtk_adec_set_play(CH_STATE_STOP, player);
    rtk_adec_remove_channel(player);

    close(fd);

    return 0;
}
