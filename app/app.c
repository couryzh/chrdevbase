/*
 * app test for chrdevbase.ko
 * Author: zhpp couryzh@aliyun.com
 * Date: 2021-03-21 17:05
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char *user_data = "user data here";

int main(int argc, char **argv)
{
	int fd;
	int ret;
	char rbuf[128];

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file-name r/w\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		printf("open dev %s failed\n", argv[1]);
		return -1;
	}

	if (!strcmp(argv[2], "r")) {
		ret = read(fd, rbuf, 50);
		if (ret < 0) {
			printf("read to %s failed\n", argv[1]);
		}
		else {
			printf("read data: (%s)\n", rbuf);
		}
	}
	else if (!strcmp(argv[2], "w")) {
		ret = write(fd, user_data, strlen(user_data));
		if (ret < 0) {
			printf("write to %s failed\n", argv[1]);
		}
		else {
			printf("write (%s) success\n", user_data);
		}
	}

	ret = close(fd);
	if (ret < 0) {
		printf("cannot close file: %s\n", argv[1]);
		return -1;
	}

	return 0;
}

