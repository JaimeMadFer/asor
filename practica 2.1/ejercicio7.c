include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd;
	int name;
	int errno = 0;

	if ((fpathconf(fd, name) == -1) && errno != 0)
	{
		printf("Error nº %i: %s\n", errno, strerror(errno));
	}
	else
	{
		printf("%i\n", fpathconf(fd, _PC_LINK_MAX));
		printf("%i\n", fpathconf(fd, _PC_PATH_MAX));
		printf("%i\n", fpathconf(fd, _PC_NAME_MAX));
	}

	return 0;
}
