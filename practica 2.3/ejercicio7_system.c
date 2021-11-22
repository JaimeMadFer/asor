#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        char *comando;
        int i;
		
		comando = malloc(sizeof(char)*1024);

        for (i = 1; i < argc; i++)
        {
                strcat(comando, argv[i]);
                strcat(comando, " ");
        }
		
        system(comando);
        printf("El comando terminó de ejecutarse\n");

        return 0;
}
