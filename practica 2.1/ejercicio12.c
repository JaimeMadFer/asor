#include <stdio.h>
#include <time.h>

int main()
{
	time_t t;
	t = time(NULL);

	printf("%i\n", t);
	
	return 0;
}
