#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"

int main(void)
{
    int i;
    int fd;
    pid_t child;

    fd = open("/dev/cdata-ts", O_RDWR);
    while(1) {
	sleep(60);
    }
    close(fd);
}
