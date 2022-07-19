#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rtkcontrol.h"

int do_filewrite(ChannelId ch, const char *filename)
{
    char buf[256];
    int fd, ret, size = 0, total = 0;

    printf("%s(ch=%d filename='%s')\n", __func__, ch, filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
	printf("open %s: %s\n", filename, strerror(errno));
	return -1;
    }

    memset(buf, 0, sizeof(buf));
    while ((size = read(fd, buf, sizeof(buf))) > 0) {
	/* Call buffer_send API to send stream or frame to channel */
	ret = rtk_buffer_send(ch, buf, size, -1, 0);

	total += ret;
	if(ret == -1){
		printf("filewrite(ch=%d read=%d): write %d total %d\n\n", ch, size, ret, total);
	}
	memset(buf, 0, sizeof(buf));

    }
    printf("filewrite(ch=%d read=%d): EOF\n", ch, size);

    return 0;
}
