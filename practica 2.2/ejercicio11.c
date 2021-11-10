#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
        struct stat info;
        stat(argv[1], &info);

        if ((info.st_mode & S_IFMT) == S_IFREG)
        {
                link(argv[1], "f_ej11.hard");
                symlink(argv[1], "f_ej11.sym");
        }
		else
		{
				printf("[ERROR] %s no es un fichero regular", argv[1]);
		}

		return 0;
}

// $ ls -i -1 ejercicio1.c f_ej11.hard f_ej11.sym
// 50520725 ejercicio1.c
// 50520725 f_ej11.hard
// 53013174 f_ej11.sym
