#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

void haz_msg(int sd)
{
        // while (1)
        // {
		char host[NI_MAXHOST], serv[NI_MAXSERV];

        char buffer[2];
        struct sockaddr_storage client;
        socklen_t clientlen = sizeof(struct sockaddr_storage);

        int bytes = recvfrom(sd, buffer, 2, 0, (struct sockaddr *) &client, &clientlen);
        buffer[bytes] = '\0';

        getnameinfo((struct sockaddr *) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        printf("BYTES: %i    HOST: %s    SERV: %s    PID: %i\n", bytes, host, serv, getpid());

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        char *error;
        char s[100];
        size_t tam_t;

        if (buffer[0] == 't')
        {
                tam_t = strftime(s, 100, "%H:%M:%S\n", &tm);
                sendto(sd, s, tam_t, 0, (struct sockaddr *) &client, clientlen);
        }
		else if (buffer[0] == 'd')
        {
                tam_t = strftime(s, 100, "%d/%m/%Y\n", &tm);
                sendto(sd, s, tam_t, 0, (struct sockaddr *) &client, clientlen);
        }
		/*else if (buffer[0] == 'q')
        {
                printf("Saliendo...\n");
                return 1;
        }*/
		else
		{
                error = "Opción incorrecta\n";
                sendto(sd, error, strlen(error), 0, (struct sockaddr *) &client, clientlen);
        }
		// }
}

int main(int argc, char **argv)
{
		struct addrinfo hints;
		struct addrinfo *res;

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
        hints.ai_flags = AI_PASSIVE;

        int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
        if (rc != 0)
        {
                printf("ERROR: %s\n", gai_strerror(rc));
                return 1;
        }

		int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        char *error;
        if (sd == -1) { perror("error"); }

        bind(sd, res->ai_addr, res->ai_addrlen);
		
		int i;
        for (i = 0; i < 5; i++)
        {
                pid_t pid = fork();

                switch (pid)
                {
                        case -1:
                                return 1;
                        case 0:
                               	haz_msg(sd);
                                return 0;
                        default:
                                break;
                }
        }

		for (i = 0; i < 5; ++i)
        {
                int hijo = wait(NULL);
                printf("Fin hijo %i\n", hijo);
        }

        freeaddrinfo(res);
        return 0;
}

// T1:
// $ ./ej5 :: 3000
// BYTES: 2    HOST: ::ffff:192.168.0.1    SERV: 49716    PID: 21629
// Fin hijo 21629
// BYTES: 2    HOST: ::ffff:192.168.0.1    SERV: 49716    PID: 21630
// Fin hijo 21630
// BYTES: 2    HOST: ::ffff:192.168.0.1    SERV: 49716    PID: 21631
// Fin hijo 21631
// BYTES: 2    HOST: ::ffff:192.168.0.1    SERV: 49716    PID: 21632
// Fin hijo 21632
// BYTES: 2    HOST: ::ffff:192.168.0.1    SERV: 49716    PID: 21628
// Fin hijo 21628

// T2:
// $ nc -u 192.168.0.1 3000
// y
// Opción incorrecta
// d
// 21/12/2021
// t
// 13:49:36
// t
// 13:49:37
// d
// 21/12/2021
// p
// Ncat: Connection refused.
