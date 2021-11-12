#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
        int fd, info;
        struct flock lock;
        struct tm tm;
        time_t t;

        fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
        info = fcntl(fd, F_GETLK, &lock);

        if (lock.l_type == F_UNLCK)
        {
                printf("Estado: desbloqueado\n");
                lock.l_type = F_WRLCK;
				
                t = time(NULL);
                tm = *localtime(&t);
                printf("Hora actual: %i:%i\n", tm.tm_hour, tm.tm_min);
                
				sleep(30);
                lock.l_type = F_UNLCK;
        }
		else
		{
				printf("Estado: bloqueado\n");
		}

		return 0;
}
