#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        int fd;
        fd = open("/home/cursoredes/fichero_ej5.c" , O_CREAT, 0645);
        close (fd);

        return 0;
}

// $ ls -l fichero_ej5.c
// -rw-r--r-x 1 cursoredes cursoredes 0 Nov  6 20:31 fichero_ej5.c
