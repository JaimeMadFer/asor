#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

volatile int cont_int = 0;
volatile int cont_tstp = 0;

void manejador(int s)
{
        if (s == SIGINT) { cont_int++; }
        if (s == SIGTSTP) { cont_tstp++; }
}

int main()
{
        sigset_t suspend;
        struct sigaction sa;

        sa.sa_handler = manejador;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGINT, &sa, 0);
        sigaction(SIGTSTP, &sa, 0);

        sigemptyset(&suspend);

        while ((cont_int + cont_tstp) < 10)
        {
                sigsuspend(&suspend);
        }

        printf("Contador SIGINT: %i\n", cont_int);
        printf("Contador SIGTSTP: %i\n", cont_tstp);

        return 0;
}
