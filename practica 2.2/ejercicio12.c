#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        int old_fd, new_fd;

        old_fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC);
        new_fd = dup2(old_fd, 1);

        printf("Salida estándar:\n", argv[1]);
        printf("Esta es la salida, no hay más\n", argv[1]);

        dup2(new_fd, old_fd);
        close(new_fd);
        close(old_fd);

        return 0;
}
