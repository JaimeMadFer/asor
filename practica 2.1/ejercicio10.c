#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

int main()
{
	uid_t real, effective;
	struct passwd info_user;

	real = getuid();
	effective = geteuid();

	printf("ID de usuario real: %i\n", real);
	printf("ID de usuario efectivo: %i\n\n", effective);

	info_user = *getpwuid(real);

	printf("Nombre de usuario: %s\n", info_user.pw_name);
	printf("Directorio home: %s\n", info_user.pw_dir);
	printf("Descripción del usuario: %s\n", info_user.pw_gecos);
	
	return 0;
}
