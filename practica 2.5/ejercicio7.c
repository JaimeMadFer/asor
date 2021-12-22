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
        connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

        while (1)
        {
                char buffer_lectura[80];
                char buffer_recibido[80];

                int bytes = read(0, buffer_lectura, 79);
                buffer_lectura[bytes] = '\0';

                if (bytes == 2 && buffer_lectura[0] == 'Q')
                        break;

                send(sd, buffer_lectura, bytes, 0);

                bytes = recv(sd, buffer_recibido, 79, 0);
                buffer_recibido[bytes] = '\0';
                printf("%s", buffer_recibido);
        }

		close(sd);
        freeaddrinfo(res);
        return 0;
}
