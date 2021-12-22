#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

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
                printf("Conexión iniciada -> HOST: %s    SERV: %s\n", host, serv);

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

                printf("Conexión finalizada\n");
        }

        close(sd);
		freeaddrinfo(res);
        return 0;
}
