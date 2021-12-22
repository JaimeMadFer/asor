#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

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

                char s[100];
                size_t tam_t;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                char buffer[2];
                struct sockaddr_storage client;
                socklen_t clientlen = sizeof(struct sockaddr_storage);

                fd_set readfds;
                FD_ZERO(&readfds);
                FD_SET(sd, &readfds);
                FD_SET(0, &readfds);
				
                int cambios = select(sd + 1, &readfds, NULL, NULL, NULL);

                ssize_t bytes;
                if (cambios == -1)
                        perror("select()");

                if (!FD_ISSET(sd, &readfds))
                {
                        bytes = read(0, buffer, 2);
                        buffer[bytes] = '\0';

                        if (buffer[0] == 't')
                        {
                                tam_t = strftime(s, 100, "%H:%M:%S\n", &tm);
                                s[tam_t] = '\0';
                                printf("%s\n", s);
                        }
                        else if (buffer[0] == 'd')
                        {
                                tam_t = strftime(s, 100, "%d/%m/%Y\n", &tm);
                                s[tam_t] = '\0';
                                printf("%s\n", s);
                        }
                        else if (buffer[0] == 'q')
                        {
                                printf("Saliendo...\n");
                                return 1;
                        }
                        else
                        {
                                error = "Opción incorrecta\n";
                                printf("%s\n", error);
                        }
                }

                else
                {
                        int bytes = recvfrom(sd, buffer, 2, 0, (struct sockaddr *) &client, &clientlen);
                        buffer[bytes] = '\0';

                        getnameinfo((struct sockaddr *) &client, clientlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                        printf("BYTES: %i    HOST: %s    SERV: %s\n", bytes, host, serv);

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
        }

		freeaddrinfo(res);
        return 0;
}

// T1: $ ./ej4 :: 3000
// T2: $ nc -u 192.168.0.1 3000
// T1: t
// T1: 18:30:53
// T1: q
// T1: Saliendo...
