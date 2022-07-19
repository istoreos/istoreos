/*
 * testapp-filewrite-ch.c: example for using buffer_send API to send stream or frame to channel
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

int main(int argc, char *argv[])
{
    ChannelId ch;
    int i;

    if (argc < 3) {
	printf("Usage: %s <channel-id> <file1> [<file2> ...]\n", argv[0]);
	return 1;
    }

    ch = atoi(argv[1]);

    for (i = 2; i < argc; i++) {
	do_filewrite(ch, argv[i]);
    }

    return 0;
}
