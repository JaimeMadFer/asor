#include <stdio.h>
#include <sys/utsname.h>
#include <errno.h>

int main()
{
	struct utsname u;
	char *s;

	if (uname(&u) == -1)
	{
		perror(s);
	}
	else
	{
		printf("%s \n", u.sysname);
		printf("%s \n", u.nodename);
		printf("%s \n", u.release);
		printf("%s \n", u.version);
		printf("%s \n", u.machine);
	}

	return 0;
}
