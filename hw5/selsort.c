#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "selsort.h"

int main(int argc, char** argv)
{
	dl_list* list = makeEmptyList();

	bool do_sort = false;

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][strlen(argv[i]) - 1] == 's')
			do_sort = true;
		else
			append(list, newUnconnectedNode(atoi(argv[i])));
	}

	if (isEmpty(list)) usage(argv[0]);

	printList(list->head);

	printListReversed(list);

	if (do_sort)
	{
		sortList(list);
		print_list_sorted(list);
	}

	freeList(list);

	return 0;
}

dl_list* makeEmptyList()
{
	dl_list *list = (dl_list *)malloc(sizeof(dl_list));

	list->head = NULL;
	list->tail = NULL;

	return list;
}

void freeList(dl_list* list)
{
	node *crt = list->head;

	while (crt)
	{
		node *tmp = crt;
		crt = crt->next;
	
		free(tmp);
	}	

	free(list);
}

void sortList(dl_list* list)
{
	dl_list *buffer = makeEmptyList();

	while (list->head)
	{
		node *min = findMinimum(list);	

		if (list->head == min)
			list->head = min->next;

		disconnect(min);
		append(buffer, min);
	}

	list->head = buffer->head;
	list->tail = buffer->tail;

	free(buffer);
}

node* findMinimum(dl_list* list)
{
	node *tmp = list->head;
	node *min = list->head;
	
	while (tmp)
	{
		if (tmp->value < min->value)
			min = tmp;

		tmp = tmp->next;
	}

	return min;
}

void printListReversed(dl_list* list)
{
	node *tmp = list->tail;
	printf("Rrsd:\t[ ");

	while (tmp)
	{
		printf("%d ", tmp->value);
		tmp = tmp->prev;
	}

	printf("]\n");
}

void printList(node* head)
{
	node *tmp = head;
	printf("Frwd:\t[ ");

	while (tmp)
	{
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}

	printf("]\n");
}

node* newUnconnectedNode(int value)
{
	node *n = (node *)malloc(sizeof(node));
	n->value = value;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

void disconnect(node* n)
{
	if (!n) return;

	node *prev = n->prev;
	node *next = n->next;

	if (prev != NULL)
		prev->next = next;

	if (next != NULL)
		next->prev = prev;

	n->prev = NULL;
	n->next = NULL;
}

void connect(node* prev, node* next)
{
	if (prev != NULL)
		prev->next = next;

	if (next != NULL)
		next->prev = prev;
}

bool isEmpty(dl_list* list)
{
	return list->head == NULL;
}

void usage(char *cmd_name)
{
	printf("Usage: %s [-s] <space separated list of numbers>\n", cmd_name);
	exit(1);
}

void append(dl_list *list, node *n)
{
	if (!list->head)
	{
		list->head = n;
		list->tail = n;
	}
	else
	{
		connect(list->tail, n);
		list->tail = n;
	}
}

void print_list_sorted(dl_list *list)
{
	node *tmp = list->head;
	printf("Srtd:\t[ ");

	while (tmp)
	{
		printf("%d ", tmp->value);
		tmp = tmp->next;
	}

	printf("]\n");
}
