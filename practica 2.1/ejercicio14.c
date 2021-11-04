#include <stdio.h>
#include <time.h>

int main()
{
	struct tm lt;
	time_t t;

	t = time(NULL);
	lt = *localtime(&t);

	printf("%i\n", 1900 + lt.tm_year);

	return 0;
}
