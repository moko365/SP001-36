#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "cdata_ioctl.h"

int main(void)
{
    int i;
    int fd;
    pid_t child;

    fd = open("/dev/cdata-misc", O_RDWR);
    child = fork();

    if (child != 0) {
	while (1) {
            write(fd, "ABCDEFG", 7);
	    sleep(1);
	}
    } else {
	while (1) {
            write(fd, "12345", 5);
	    sleep(1);
	}
    }

    close(fd);
}
