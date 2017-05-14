#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"

int main(void)
{
    int fd;
    int size = 0;
    int frame = 0;
    unsigned char d[4] = {0x11, 0x22, 0x33, 0x44};

    fd = open("/dev/cdata-misc", O_RDWR);

    while(1) {
        write(fd, &d[frame], 1);

	size++;
	if (size >= 640*480*1) {
	    size = 0;
	    frame++;
	    frame %= 4;
	}
    }

    close(fd);
}
