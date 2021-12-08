#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
        struct addrinfo hints;
        struct addrinfo *res;

        memset(&hints, 0, sizeof(struct addrinfo));

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = 0; // SOCK_STREAM | SOCK_DGRAM
        hints.ai_flags = AI_PASSIVE;

        int rc = getaddrinfo(argv[1], NULL, &hints, &res);

        if (rc != 0)
        {
                printf("ERROR: %s\n", gai_strerror(rc));
                return 1;
        }

// Las familias 2 y 10 son AF_INET y AF_INET6, respectivamente (ver socket.h)
// Los tipos 1, 2, 3 son SOCK_STREAM, SOCK_DGRAM y SOCK_RAW, respectivamente

        struct addrinfo *i;
        for (i = res; i != NULL; i = i->ai_next)
        {
                char host[NI_MAXHOST], serv[NI_MAXSERV];

                getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST,
                        serv, NI_MAXSERV, NI_NUMERICHOST);

                printf("%s      %i      %i\n", host, i->ai_family, i->ai_socktype);
        }

        freeaddrinfo(res);
        return 0;
}
