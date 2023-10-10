#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc != 3) return 1;

	char *src = argv[1];
	char *dest = argv[2];

	int prev_matches = 0;
	char result = '0';

	for (int i = strlen(src) - 1; i >= 0; i--)
	{
		char next_char = src[i];
		int next_matches = 0;

		for (int j = 0; dest[j] != '\0'; j++)
		{
			if (next_char == dest[j]) next_matches++;
		}

		if (next_matches >= prev_matches)
		{
			prev_matches = next_matches;
			result = next_char;
		}
	}

	printf("Most often: %c No. times: %d\n", result, prev_matches);

	return 0;
}
