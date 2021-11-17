#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

void pids(const char *msg, pid_t pid)
{
        char *buf, *dir;
        struct rlimit rlim;

        buf = malloc(sizeof(char) * 512);
        dir = getcwd(buf, 512);
        getrlimit(RLIMIT_NOFILE, &rlim);

        printf("%s\n", msg);
        printf("PID: %i\n", pid);
        printf("PPID: %i\n", getppid());
        printf("GPID: %i\n", getpgid(pid));
        printf("SID: %i\n", getsid(pid));
        printf("Num ficheros que se pueden abrir: %i\n", rlim.rlim_max);
        printf("Directorio actual: %s\n\n", dir);

        free(buf);
}

int main()
{
        pid_t pid = fork();
        pid_t nueva_sesion;

        switch (pid)
        {
		case -1:
                perror("fork()");
                break;
        case 0:
               	nueva_sesion = setsid();
                chdir("/tmp");
               	
                pids("HIJO", pid);
                break;
        default:
                pids("PADRE", pid);
                sleep(3);
        }

	return 0;
}

// Si termina antes el padre, el hijo se queda huérfano (ppid=1 es init, que hereda el proceso)
// Si termina antes el hijo, el proceso se queda zombie
