#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main()
{
        char *c;

        if (setuid(2) == -1)
        {
                perror(c);
        }

	return 0;
}
