#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>

struct node* newNode(int value, struct node *left, struct node *right)
{
	struct node *node = malloc(sizeof(struct node));

	node->value = value;
	node->left = left;
	node->right = right;

	return node;
}

struct node* leaf(int value)
{
	return newNode(value, NULL, NULL);
}

struct node* insert(struct node *tree, int value)
{
	if (!tree) return leaf(value);

	if (tree->value > value)
		tree->left = insert(tree->left, value);

	if (tree->value < value)
		tree->right = insert(tree->right, value);

	return tree;
}

struct node* delete(struct node *tree, int value)
{
	if (!tree) return NULL;

	if (tree->value > value)
		tree->left = delete(tree->left, value);

	if (tree->value < value)
		tree->right = delete(tree->right, value);

	if (tree->value == value)
	{
		if (!(tree->left && tree->right))
		{
			struct node *subtree = tree->left ? tree->left : tree->right;
			free(tree);
			return subtree;
		}

		tree->value = rightmostValue(tree->left);
		tree->left = delete(tree->left, tree->value);
	}

	return tree;
}

int rightmostValue(struct node *tree)
{
	return tree->right ? rightmostValue(tree->right) : tree->value;
}

void freeNodes(struct node *node)
{
	if (!node) return;

	freeNodes(node->left);
	freeNodes(node->right);

	free(node);
}

void printTree(struct node *tree)
{
	if (!tree) return;

	printTree(tree->left);

	printf("%d ", tree->value);

	printTree(tree->right);
}

void printTreeReverse(struct node *tree)
{
	if (!tree) return;

	printTree(tree->right);

	printf("%d ", tree->value);

	printTree(tree->left);
}