#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>

void usage()
{
	puts("Usage: ./btdemo <space separated list of numbers>");
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc < 2) usage();

	int i = 1;
	struct node *tree = NULL;

	while (i < argc)
	{
		tree = insert(tree, atoi(argv[i++]));
		printTree(tree);
		putchar('\n');
	}

	printTreeReverse(tree);
	putchar('\n');

	i = 1;
	while (i < argc)
	{
		printTree(tree);
		putchar('\n');
		tree = delete(tree, atoi(argv[i++]));
	}

	return 0;
}