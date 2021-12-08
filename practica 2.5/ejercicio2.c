#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

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

        while (1)
        {
                char host[NI_MAXHOST], serv[NI_MAXSERV];

                char buffer[2];
                struct sockaddr_storage client;
                socklen_t clientlen = sizeof(struct sockaddr_storage);

                int bytes = recvfrom(sd, buffer, 2, 0, (struct sockaddr *) &client, &clientlen);
                buffer[bytes] = '\0';

                getnameinfo((struct sockaddr *) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                printf("BYTES: %i    HOST: %s    SERV: %s\n", bytes, host, serv);

                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

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
                else if (buffer[0] == 'q')
                {
                        printf("Saliendo...\n");
                        return 1;
                }
                else
                {
                        error = "Opción incorrecta\n";
                        sendto(sd, error, strlen(error), 0, (struct sockaddr *) &client, clientlen);
                }
        }

		freeaddrinfo(res);
		return 0;
}
