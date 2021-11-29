#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
        int fd[2];
        int pid;

        pipe(fd);
        pid = fork();

        switch(pid)
        {
		case -1:
                perror("fork()");
                break;
        case 0:
               	printf("HIJO:\n");
                close(fd[1]);
                dup2(fd[0], 0);
                close(fd[0]);
                execlp(argv[3], argv[3], argv[4], 0);
                break;
        default:
                printf("PADRE:\n");
                close(fd[0]);
                dup2(fd[1], 1);
                close(fd[1]);
                execlp(argv[1], argv[1], argv[2], 0);
        }

	return 0;
}
