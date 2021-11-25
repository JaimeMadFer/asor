#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main()
{
        sigset_t set, pend;

        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        sigaddset(&set, SIGTSTP);

        sigprocmask(SIG_BLOCK, &set, NULL);

        //char *sleep_secs = getenv("SLEEP_SECS");
        //int secs = atoi(sleep_secs);
        //printf("Valor de SLEEP_SECS: %i\n", secs);
        //sleep(secs);
        sleep(20);

        sigpending(&pend);

        if (sigismember(&pend, SIGINT))
        {
                printf("El proceso recibió la señal SIGINT\n");
                sigdelset(&set, SIGINT);
        }
		if (sigismember(&pend, SIGTSTP))
        {
                printf("El proceso recibió la señal SIGTSTP\n");
                sigdelset(&set, SIGTSTP);
        }

		sigprocmask(SIG_UNBLOCK, &set, NULL);
        printf("Fin del programa\n");

        return 0;
}
