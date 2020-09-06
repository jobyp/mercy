#include <stdio.h>
#include <stdlib.h>	/* for exit() */
#include <sys/types.h>	/* for open() */
#include <sys/stat.h>	/* for open() */
#include <fcntl.h>	/* for open() */
#include <unistd.h>	/* for close() */

int main(int argc, char *argv[])
{
	char *pathname = "hello_world";
	int fd = 0;
	int ret = 0;
	pid_t my_pid = 0;
	
	if (argc > 1) {
		pathname = argv[1];
	}

	fd = open(pathname, O_RDONLY);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	
	ret = close(fd);
	if (ret == -1) {
		perror("close()");
		exit(EXIT_FAILURE);
	}

	my_pid = getpid();
	printf("My PID is: %ld\n", (long)my_pid);

	printf("sizeof(long) = %zu\n", sizeof(long));
	printf("sizeof(long long) = %zu\n", sizeof(long long));
	
	exit(EXIT_SUCCESS);
}
