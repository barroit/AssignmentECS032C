#include <stdio.h>

void sum3(int, int, int, int *); 

int main(void)
{
	int s;

	sum3 (4, 10, -1, &s);
	printf ("%d\n", s);

	sum3 (0, 2, -10, NULL);
	printf ("%d\n", s);
}
