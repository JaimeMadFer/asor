#include <unistd.h>
#include <stdio.h>

#define MAX_SIZE 512

int main()
{
        int p_h[2], h_p[2];
        ssize_t bytes;
        char mensaje[MAX_SIZE];
        char *letra;

        pipe(p_h);
        pipe(h_p);
        int pid = fork();

        switch(pid)
        {
		case -1:
                perror("fork()");
                break;
        case 0:
               	close(p_h[1]);
                close(h_p[0]);

                int i;
                for (i = 0; i < 10; ++i)
                {
                       bytes = read(p_h[0], mensaje, MAX_SIZE);
                        mensaje[bytes] = '\0';

                        write(1, mensaje, bytes);
                        sleep(1);

                        if (i < 9)
                                write(h_p[1], "l", 1);
                        else
                            	write(h_p[1], "q", 1);
                }
                close(p_h[0]);
                close(h_p[1]);
                break;

        default:
                close(p_h[0]);
                close(h_p[1]);

                while (letra != "q")
                {
                        bytes = read(0, mensaje, MAX_SIZE);
                        mensaje[bytes] = '\0';

                        write(p_h[1], mensaje, bytes);

                        read(h_p[0], letra, 1);
                }
                close(p_h[1]);
                close(h_p[0]);
        }

        return 0;
}
