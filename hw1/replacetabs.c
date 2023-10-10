#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char **argv)
{
	if (argc != 2) return 1;

	char *endptr;
	errno = 0;

	long int num = strtol(argv[1], &endptr, 10);

	if (endptr == argv[1] || errno == ERANGE || num > INT_MAX || num < INT_MIN || *endptr != '\0') return 1;
	int space_size = (int)num;

	int c;
	while ((c = getchar()) != EOF)
	{
		if (c == 9)
			for (int i = 0; i < space_size; i++)
				putchar(' ');
		else
			putchar(c);
	}

	return 0;
}
