#include <stdio.h>

int filterOut(const char*, const char*, const char*);

int main(int argv, char** argc)
{
	if (argv != 4) return 1;

	int res = filterOut(argc[1], argc[2], argc[3]);
	printf("%d\n", res);

	return 0;
}
