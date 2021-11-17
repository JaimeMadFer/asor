#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

int main()
{
        int pid;
        char *buf, *dir;
        struct rlimit rlim;

        pid = getpid();
        buf = malloc(sizeof(char) * 512);
        dir = getcwd(buf, 512);
        getrlimit(RLIMIT_NOFILE, &rlim);

        printf("PID: %i\n", pid);
        printf("PPID: %i\n", getppid());
        printf("GPID: %i\n", getpgid(pid));
        printf("SID: %i\n", getsid(pid));
        printf("Num ficheros que se pueden abrir: %i\n", rlim.rlim_max);
        printf("Directorio actual: %s\n", dir);

        free(buf);

        return 0;
}
