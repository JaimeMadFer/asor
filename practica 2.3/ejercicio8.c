#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        pid_t pid = fork(), nueva_sesion;
        int oldfd_1, oldfd_2, oldfd_0;
        int newfd_1, newfd_2, newfd_0;

        switch (pid)
        {
	case -1:
                perror("fork()");
                break;
        case 0:
               	nueva_sesion = setsid();
                chdir("/tmp");
                printf("HIJO (pid: %i)\n", pid);

                oldfd_1 = open("daemon.out", O_CREAT | O_RDWR, 0777);
                oldfd_2 = open("daemon.err", O_CREAT | O_RDWR, 0777);
                oldfd_0 = open("/dev/null", O_CREAT | O_RDWR, 0777);

                newfd_1 = dup2(oldfd_1, 1);
                newfd_2 = dup2(oldfd_2, 2);
                newfd_0 = dup2(oldfd_0, 0);

                execvp(argv[1], &argv[1]);
                break;
        default:
                printf("PADRE (pid: %i)\n", pid);
        }

	return 0;
}
