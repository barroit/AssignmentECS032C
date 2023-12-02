#ifndef SELSORT_H
#define SELSORT_H

typedef struct node
{
	struct node* prev;
	struct node* next;
	int value;
} node;

typedef struct
{
	node* head;
	node* tail;
} dl_list;

void append(dl_list *list, node *n);

void print_list_sorted(dl_list *list);

// usage prints program usage with the correct command name
void usage(char *cmd_name);

// is_empty returns true if the passed in list is empty
bool isEmpty(dl_list* list);

// connect will connect the the two nodes passed in
void connect(node* prev, node* next);

// disconnect will disconnect a node by connecting it's prev and next nodes together
void disconnect(node* n);

// newUnconnectedNode will create a new node with the passed in value but will make no attempt to connect it to an existing list
node* newUnconnectedNode(int value);

// printList will print the list values inside of square brackets in a forward direction
void printList(node* head);

// printListReversed will print the list values inside of square brackets in a backwards direction
void printListReversed(dl_list* list);

// findMinimum returns the node that contains the minimum value in the list referenced by head
node* findMinimum(dl_list* list);

// sortList creates a sorted list
void sortList(dl_list* list);

// freeList will free all allocated memory for the list
void freeList(dl_list* list);

// makeEmptyList will return a list structure structure that does not contain any nodes
dl_list* makeEmptyList();

#endif
