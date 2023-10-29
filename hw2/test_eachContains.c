#include <stdio.h>

int eachContains (char**, char, unsigned, char**);

int main(void)
{
	char* strings[] = { "abcde", "hi there jack", "apple", "banana" };
	char* firstOffending;

	if (eachContains(strings, 'a', 4, NULL))
		printf("000\n");
	else
		printf("Will have failed\n");

	if (eachContains(NULL, 'a', 4, &firstOffending))
		printf("000\n");
	else
		printf("Will have failed\n");

	if (eachContains(strings, 'a', 4, &firstOffending))
		printf("AAA\n");
	else
		printf("firstOffending: %s\n", firstOffending);

	if (eachContains(strings, 'b', 4, &firstOffending))
		printf("BBB\n");
	else
		printf("firstOffending: %s\n", firstOffending);

	if (eachContains(strings, 'e', 4, &firstOffending))
		printf("CCC\n");
	else
		printf("firstOffending: %s\n", firstOffending);

	return 0;
}
