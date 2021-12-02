#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
        int fd, fd2, cambios, nfds;
        char buffer[256];
        ssize_t tam, tam2;
        fd_set readfds;
        struct timeval timeout;

        fd = open("tub", O_RDWR | O_NONBLOCK);
        fd2 = open("tub2", O_RDWR | O_NONBLOCK);

        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        FD_SET(fd2, &readfds);

        timeout.tv_sec = 10;
        nfds = (fd > fd2) ? fd + 1 : fd2 + 1;

        cambios = select(nfds, &readfds, NULL, NULL, &timeout);

        if (cambios == -1)
                perror("select()");
        else if (cambios)
        {
                if ((tam = read(fd, buffer, sizeof(buffer))) != -1)
                {
                        buffer[tam] = '\0';
                        printf("tub: %s", buffer);
                }

                else if ((tam2 = read(fd2, buffer, sizeof(buffer))) != -1)
                {
                        buffer[tam2] = '\0';
                        printf("tub2: %s", buffer);
                }
        }
		else
            	printf("Ningún dato nuevo en 10 segundos\n");

        close(fd);
        fd = open("tub", O_RDWR | O_NONBLOCK);

        close(fd2);
        fd2 = open("tub2", O_RDWR | O_NONBLOCK);

        return 0;
}

// $ mkfifo tub2

// T1: $ ./ej5
// T2: $ echo "AEIOU" > tub
// T1: tub: AEIOU

// T1: $ ./ej5
// T2: $ echo "AEIOU" > tub2
// T1: tub2: AEIOU
