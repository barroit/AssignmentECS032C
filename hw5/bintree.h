#ifndef BINTREE_H
#define BINTREE_H

struct node
{
	struct node *left;
	struct node *right;
	int value;
};

struct node* newNode(int value, struct node *left, struct node *right);

struct node* leaf(int value);

struct node* insert(struct node *tree, int value);

struct node* delete(struct node *tree, int value);

int rightmostValue(struct node *tree);

void freeNodes(struct node *node);

void printTree(struct node *tree);

void printTreeReverse(struct node *tree);

#endif