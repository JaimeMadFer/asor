#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        execvp(argv[1], &argv[1]);
        printf("El comando terminó de ejecutarse\n");

        return 0;
}

// Después de ejecutar system()	se imprime la cadena, pero con execvp()	no se imprime la cadena
// execvp() sustituye la imagen del proceso actual por otra que ejecuta el fichero seleccionado, por lo que la cadena no se imprime en la nueva imagen del proceso
// En cambio system() crea un nuevo proceso con	fork() y luego vuelve al proceso inicial para continuar su ejecución

// ./ejecuta ps -el: tiene dos argumentos. Se debe usar con execvp() y se puede usar con system si se concatenan los argumentos (como he hecho yo en mi implementación)
// ./ejecuta "ps -el": tiene un argumento. Se puede usar con system() pasando como comando únicamente argv[1] (es la opción más sencilla)
