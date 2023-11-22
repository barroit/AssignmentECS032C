#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct int_node {
	struct int_node *next;
	int value;
} int_node;

void push(int_node **top, int value)
{
	int_node *node = (int_node *)malloc(sizeof(int_node));
	node->value = value;
	node->next = *top;
	*top = node;
}

int pop(int_node **top)
{
	int_node *node = *top;
	int value = node->value;
	*top = node->next;
	free(node);
	return value;
}

void usage(void)
{
	printf("bigadd <operand one> <operand two>\n");
	exit(1);
}

void prepareCalc(int_node **top, char **operand)
{
	int padding = strlen(operand[0]) - strlen(operand[1]);
	int exchange = padding < 0;

	char *lo = operand[exchange];
	char *ro = operand[!exchange];

	for (int p = abs(padding); *lo != 0; lo++, p && p--)
	{
		push(top, p ? 0 : *ro++ - 48);
		push(top, *lo - 48);
	}
}

void calculate(int_node **in, int_node **out)
{
	int carry = 0;

	while (*in)
	{
		int l = pop(in), r = pop(in);
		int sum = l + r + carry;
		int result = sum % 10;
		carry = (sum - result) / 10;

		push(out, result);
	}

	if (carry)
		push(out, carry);
}

int main(int argc, char **argv)
{
	if (argc != 3) usage();

	int_node *operand_buffer = NULL;
	prepareCalc(&operand_buffer, argv + 1);

	int_node *result_buffer = NULL;
	calculate(&operand_buffer, &result_buffer);

	while (result_buffer)
		putchar(pop(&result_buffer) + 48);
	putchar('\n');

	return 0;
}
