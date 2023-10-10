#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool prime_test(int n)
{
	if (n == 2) return true;
	if (n < 2 || n % 2 == 0) return false;

	for (int i = 3; i * i <= n; i += 2)
 	{
 		if (n % i == 0) return false;
 	}

	return true;
}

int main(int argc, char* argv[])
{
	printf("%s\n", argv[0]);
	
	int num = 2;
	int idx = 1;

	while (idx <= 100)
	{
		if (prime_test(num))
		{
			printf(idx % 10 == 0 ? "%d\n" : "%d\t", num);
			idx++;
		}
		num++;
	}

	return 0;
}
