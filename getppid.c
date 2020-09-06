#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t parent;

	for(unsigned long int i = 0 ; i < 1000 * 1000 * 1000; i++)
		parent = getppid();

	printf("%u\n", parent);
	return 0;
}
