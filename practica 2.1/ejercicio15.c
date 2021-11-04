#include <stdio.h>
#include <time.h>

int main()
{
	struct tm lt;
	time_t t;
	char s[200], *format;

	t = time(NULL);
	lt = *localtime(&t);

	format = "%A, %d %B, %H:%M";
	strftime(s, sizeof(s), format, &lt);

	printf("%s (%i)\n", s, lt.tm_year + 1900);

	return 0;
}
