#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>

void haz_conn(int cliente_sd)
{
        while (1)
        {
                char buffer[80];

                int bytes = recv(cliente_sd, buffer, 79, 0);
                if (bytes == 0)
                {
                        close(cliente_sd);
                        break;
                }
                buffer[bytes] = '\0';

                send(cliente_sd, buffer, bytes, 0);
        }
}

int main(int argc, char **argv)
{
        struct addrinfo hints;
        struct addrinfo *res;

        memset(&hints, 0, sizeof(struct addrinfo));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
        if (rc != 0)
        {
                printf("getaddrinfo: %s\n", gai_strerror(rc));
                return 1;
        }

		int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        bind(sd, res->ai_addr, res->ai_addrlen);
        listen(sd, 16);

        char host[NI_MAXHOST], serv[NI_MAXSERV];
        struct sockaddr_storage client;
        socklen_t clientlen = sizeof(struct sockaddr_storage);

        struct sigaction sa;
        sa.sa_handler = SIG_IGN;
        sa.sa_flags = SA_RESTART;
        sigaction(SIGCHLD, &sa, NULL);

        while (1)
        {
                int cliente_sd = accept(sd, (struct sockaddr *) &client, &clien$

                getnameinfo((struct sockaddr *) &client, clientlen, host, NI_MA$

                pid_t pid = fork();
                switch (pid)
                {
                        case -1:
                                return 1;
                        case 0:
                               	close(sd);

                                printf("Conexión iniciada -> HOST: %s    SERV: $
                                haz_conn(cliente_sd);
                                printf("Conexión finalizada\n");

                                return 0;
                        default:
                                break;
                }
                close(cliente_sd);
        }

		// close(sd);
        freeaddrinfo(res);
        return 0;
}

// T1: $ ./ej9 :: 2222
// T2: $ nc -6 fd00::a:0:0:0:1 2222
// T3: $ nc -6 fd00::a:0:0:0:1 2222
// T4: $ ps -aHj
// T2: ^C
// T3: ^C
// T4: $ ps -aHj
