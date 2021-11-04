#include <stdio.h>
#include <unistd.h>

int main()
{
	uid_t real, effective;

	real = getuid();
	effective = geteuid();

	printf("Real user ID: %i\n", real);
	printf("Effective user ID: %i\n", effective);
	
	return 0;
}

// Si el proceso que realiza la llamada es privilegiado, estará activado el bit setuid.
