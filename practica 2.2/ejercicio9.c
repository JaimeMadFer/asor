#include <stdio.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char **argv)
{
        struct stat info;
        struct tm tm;
        time_t t;

        stat(argv[1], &info);

        printf("Major: %i\n", major(info.st_dev));
        printf("Minor: %i\n", minor(info.st_dev));
        printf("Inodo: %i\n", info.st_ino);

        printf("Tipo: %i -> ", info.st_mode);

        if ((info.st_mode & S_IFMT) == S_IFDIR)
        {
                printf("directorio\n");
        }
		else if ((info.st_mode & S_IFMT) == S_IFLNK)
        {
                printf("enlace simbolico\n");
        }
		else
		{
                printf("fichero ordinario\n");
        }

		t = info.st_atime;
        tm = *localtime(&t);
        printf("Hora de último acceso: %i:%i\n", tm.tm_hour, tm.tm_min);

        return 0;
}

// st_mtime: tiempo de última modificación del fichero
// st_ctime: tiempo de último cambio del inodo
