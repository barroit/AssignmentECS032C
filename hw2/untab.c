#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2) return 1;

	unsigned tabstop = atoi(argv[1]);

	char c;
	unsigned pos = 1;

	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			unsigned spaces = tabstop - ((pos - 1) % tabstop);
			while (spaces-- > 0)
			{
				putchar(' ');
				pos++;
			}
		}
		else
		{
			if (c == '\n') pos = 1;
			else pos++;
			putchar(c);
		}
	}

	return 0;
}
