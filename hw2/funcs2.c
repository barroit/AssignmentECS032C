#include <stdio.h>

void sum3(int a, int b, int c, int *sum)
{
	if (sum == NULL) return;
	*sum = a + b + c;
}

int eachContains(char** strings, char target, unsigned num_strings, char** first_offending)
{
	if (first_offending == NULL || strings == NULL) return 0;	

	for (unsigned i = 0; i < num_strings; i++)
	{
		char* c = strings[i];

		while (*c != '\0')
		{
			if (*c == target) break;
			c++;
		}

		if (*c == '\0')
		{
			*first_offending = strings[i];
			return 0;
		}
	}

	return 1;
}

int filterOut(const char* input_filename, const char* target, const char* output_filename)
{
	if (input_filename == NULL || target == NULL || output_filename == NULL) return 0;

	FILE *input_file = fopen(input_filename, "r");
	if (input_file == NULL) return 0;

	FILE *output_file = fopen(output_filename, "w");
	if (output_file == NULL)
	{
		fclose(input_file);
		return 0;
	}

	char line[100];
	while (fgets(line, 100, input_file) != NULL)
	{
		unsigned j = 0;
		for (unsigned i = 0; line[i] != '\0'; i++)
		{
			if (line[i] == *target)
			{
				for (j = 0; target[j] != '\0' && line[i + j] == target[j]; j++);
				if (target[j] == '\0') break;
			}
		}
		if (target[j] != '\0') fputs(line, output_file);
	}

	fclose(input_file);
	fclose(output_file);
	return 1;
}
