#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        int old_fd, new_fd, fd_errores;
        char *s;

        old_fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
        new_fd = dup2(old_fd, 1);
        fd_errores = dup2(old_fd, 2);

        printf("Salida estándar:\n", argv[1]);
        printf("Esta es la salida, no hay más\n", argv[1]);

       if (setuid(0) == -1)
       {
                perror(s);
       }

		//dup2(new_fd, old_fd);
        //dup2(fd_errores, old_fd);

        return 0;
}

// ls > dirlist 2>&1: la salida estándar y de errores pasan a estar en dirlist
// ls 2>&1 > dirlist: salida de errores en salida estándar y salida estándar en dirlist
