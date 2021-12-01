#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
        int fd;
        ssize_t tam;

        fd = open("tub", O_WRONLY, 0777);
        write(fd, argv[1], strlen(argv[1]));

        return 0;
}

// T1: ./ej1 AEIOU
// T2: $ cat tub
// T2: AEIOU
