#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        int fd;
        mode_t old_masc, new_masc;

        old_masc = umask(0027);
        fd = open("fichero_ej5.c", O_WRONLY | O_CREAT, 0777);
        close (fd);
        new_masc = umask(old_masc);

        printf("%i\n", new_masc);

        return 0;
}

// $ ls -l fichero_ej5.c
// -rwxr-x--- 1 cursoredes cursoredes 0 Nov  9 17:41 fichero_ej5.c
