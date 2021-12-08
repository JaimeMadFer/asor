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

        sendto(sd, argv[3], 1, 0, res->ai_addr, res->ai_addrlen);

        char buffer[80];
        int bytes = recvfrom(sd, buffer, 79, 0, res->ai_addr, &res->ai_addrlen);
        buffer[bytes] = '\0';
        printf("%s", buffer);

        freeaddrinfo(res);
        return 0;
}

// T1: $ ./ej2 :: 3000
// T2: $ ./ej3 192.168.0.1 3000 t
// T1: BYTES: 1    HOST: ::ffff:192.168.0.1    SERV: 55161
// T2: 17:34:38
