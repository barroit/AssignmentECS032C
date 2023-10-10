#include <stdio.h>
#include <ctype.h>

int between(char lower_bound, char upper_bound, char target)
{
	if (!(isupper(lower_bound) && isupper(upper_bound) && isupper(target))) return -1;
	
	if (lower_bound > upper_bound) return -2;

	if (target >= lower_bound && target <= upper_bound) return 1;

	return 0;
}
