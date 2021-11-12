#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char **argv)
{
        struct stat buf_dir, buf_general;
        struct dirent *st_dir;
        DIR *p_dir;
        char *buf_sym;
        int bytes = 0;

        stat(argv[1], &buf_dir);

        if (S_ISDIR(buf_dir.st_mode))
        {
                p_dir = opendir(argv[1]);

                while ((st_dir = readdir(p_dir)) != NULL)
                {
                        stat(st_dir->d_name, &buf_general);

                        if (S_ISREG(buf_general.st_mode))
                        {
                                printf("%s\n", st_dir->d_name);
                        }
                        else if (S_ISDIR(buf_general.st_mode))
                        {
                                printf("%s/\n", st_dir->d_name);
                        }
                        else if (S_ISLNK(buf_general.st_mode))
                        {
                                readlink(st_dir->d_name, buf_sym, buf_general.s$
                                printf("%s->%s\n", st_dir->d_name, buf_sym);
                        }
                        else //ejecutable
                        {
                                printf("%s*\n", st_dir->d_name);
                        }
                        bytes += buf_general.st_size;
                }
                printf("Tamaño: %i KB\n", bytes / 1024);
                closedir(p_dir);
        }
		else
		{
				printf("ERROR: No has introducido un directorio\n");
		}

	return 0;
}
