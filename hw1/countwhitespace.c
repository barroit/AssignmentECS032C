#include<stdio.h>

int main(void)
{
	int c;
	int tabs = 0, lines = 0, spaces = 0;

	while((c = getchar()) != EOF)
	{
		switch (c)
		{
			case 9:
				tabs++;
				break;
			case 10:
				lines++;
				break;
			case 32:
				spaces++;
		}
	}

	printf("Lines: %d\n", lines);
	printf("Tabs: %d\n", tabs);
	printf("Spaces: %d\n", spaces);

	return 0;
}
