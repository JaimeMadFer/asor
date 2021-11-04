include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int errno = 0;

	if (((sysconf(_SC_ARG_MAX) == -1) || (sysconf(_SC_CHILD_MAX) == -1) ||
			(sysconf(_SC_OPEN_MAX) == -1)) && errno != 0)
	{
		printf("Error nº %i: %s\n", errno, strerror(errno));
	}
	else
	{
		printf("%i\n", sysconf(_SC_ARG_MAX));
		printf("%i\n", sysconf(_SC_CHILD_MAX));
		printf("%i\n", sysconf(_SC_OPEN_MAX));
	}
	
	return 0;
}
