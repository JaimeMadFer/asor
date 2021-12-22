#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

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

        while (1)
        {
                int cliente_sd = accept(sd, (struct sockaddr *) &client, &clientlen);

                getnameinfo((struct sockaddr *) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

                pid_t pid = fork();
                switch (pid)
                {
                        case -1:
                                return 1;
                        case 0:
                               	close(sd);

                                printf("Conexión iniciada -> HOST: %s    SERV: %s    PID: %i\n", host, serv, getpid());
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

// T1: $ ./ej8 :: 2222
// T2: $ nc -6 fd00::a:0:0:0:1 2222
// T3: $ nc -6 fd00::a:0:0:0:1 2222
// T1: Conexión iniciada -> HOST: fd00:0:0:a::1    SERV: 35508    PID: 27531
// T1: Conexión iniciada -> HOST: fd00:0:0:a::1    SERV: 35510    PID: 27533
