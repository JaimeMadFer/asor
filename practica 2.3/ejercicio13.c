#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int cont = 0;

void manejador(int s)
{
        if (s == SIGUSR1) { cont++; }
}

int main(int argc, char **argv)
{
        sigset_t wait;
        struct sigaction sa;
        
		sa.sa_handler = manejador;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGUSR1, &sa, NULL);

        int secs = sleep(atoi(argv[1]));

        sigemptyset(&wait);

        while (cont == 0 && secs != 0)
        {
                sigsuspend(&wait);
        }
		
		if (cont == 0)
        {
                remove(argv[0]);
                printf("El fichero se ha borrado\n");
        }
		else
		{
                printf("El fichero vive\n");
        }
		
        return 0;
}
