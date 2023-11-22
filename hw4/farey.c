#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int num;
	int den;
	struct node *next;
} node;

node *head = NULL;
int order = 0;

node* makeFareyNode(int num, int den, node* next)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->num = num;
	new_node->den = den;
	new_node->next = next;
	return new_node;
}

void farey(node *l, node *r)
{
	int num = l->num + r->num, den = l->den + r->den;
	if (den > order) return;

	node *current = makeFareyNode(num, den, r);
	l->next = current;
	farey(l, current);
	farey(current, r);
}

int main(int argc, char **argv)
{
	if (argc != 2 || (order = atoi(argv[1])) < 1)
	{
		printf("Usage: farey <n>\n       where n >= 1 is the level of the Farey sequence.\n");
		exit(1);
	}

	head = makeFareyNode(0, 1, makeFareyNode(1, 1, NULL));
	farey(head, head->next);

	node *tmp;
	for (int i = 1; i <= order; i++)
	{
		tmp = head;
		putchar('(');
		while (tmp)
		{
			if (tmp->den <= i)
				printf(tmp->next != NULL ? "%d/%d, " : "%d/%d)\n", tmp->num, tmp->den);
			tmp = tmp->next;
		}
	}

	tmp = head;
	while (tmp)
	{
		node *next = tmp->next;
		free(tmp);
		tmp = next;
	}

	return 0;
}
