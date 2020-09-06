#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>

#define BUF_SIZE 1024


int main(int argc, char *argv[])
{
	char *src_file;
	char *dst_file;
	int src_fd;
	int dst_fd;
	int ret = EXIT_SUCCESS;
	char *buffer = NULL;
	ssize_t count;

	
	if (argc != 3) {
		printf("usage: %s <src_file> <dst_file>\n", argv[0]);
		ret = EXIT_FAILURE;
		goto exit;
	}

	buffer = (char *)malloc(BUF_SIZE * sizeof(char));
	if (buffer == NULL) {
		perror("malloc()");
		ret = EXIT_FAILURE;
		goto exit;
	}

	src_file = argv[1];
	dst_file = argv[2];
	
	src_fd = open(src_file, O_RDONLY);
	if (src_fd == -1) {
		fprintf(stderr, "failed to open %s\n", src_file);
		perror("open()");
		ret = EXIT_FAILURE;
		goto exit;
	}

	dst_fd = open(dst_file, O_WRONLY|O_CREAT|O_TRUNC|O_APPEND,
		      S_IRUSR|S_IRGRP|S_IWUSR|S_IWGRP);
	if (dst_fd == -1) {
		fprintf(stderr, "failed to open %s\n", dst_fd);
		perror("open()");
		ret = EXIT_FAILURE;
		goto close_src_fd;
	}


	while(true) {
		count = read(src_fd, buffer, BUF_SIZE);
		if (count == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("read()");
				ret = EXIT_FAILURE;
				goto close_dst_fd;
			}
		}

		if (count == 0)
			break;

		/* count > 0 */
		size_t to_write = (size_t) count;
		char *buf = buffer;

		while(to_write > 0) {
			count = write(dst_fd, buf, to_write);
			if (count == -1) {
				if (errno == EINTR) {
					count = 0;
					continue;
				}
			}

			if (count > 0) {
				buf = buf + count;
				to_write = to_write - (size_t)count;
			}
		}
	}

close_dst_fd:
	if (close(dst_fd) == -1) {
		perror("close()");
		ret = EXIT_FAILURE;
	}

close_src_fd:
	if (close(src_fd) == -1) {
		perror("close()");
		ret = EXIT_FAILURE;
	}

	free(buffer);
	buffer = NULL;

exit:
	exit(ret);
}
