#include <stdio.h>
#include <malloc.h>

/*
 * Created by Caishangqi on 2023/12/6.
 * Documentation and Implementation of Binary
 * tree implementation in C
 */

struct node {
    int value;
    struct node *left;
    struct node *right;
};

struct node *newNode(int value, struct node *left, struct node *right);

/*!
 * Create a leaf node, we only need value because
 * leaf do not have right or left node, it is at the
 * and of the binary tree
 * @param value - The value of the leaf node
 * @return struct node
 */
struct node *leaf(int value);

/*!
 *
 * @param tree -
 * @param value -
 * @return A modified tree
 */
struct node *insert(struct node *tree, int value);

/*!
 *
 * @param tree
 */
void printTree(struct node *tree);

/*!
 * TODO: Implement Reverse print the tree (Big to Small)
 * @param tree - The tree you wang to print
 */
void printTreeReverse(struct node *tree);

/*!
 *
 * @param tree
 */
void freeNodes(struct node *node);

int main() {


}

struct node *newNode(int value, struct node *left, struct node *right) {
    struct node *n = malloc(sizeof(struct node));
    n->value = value;
    n->left = left;
    n->right = right;
    return n; // value gone but we have the address
}

struct node *leaf(int value) {
    return newNode(value, NULL, NULL);
}

struct node *insert(struct node *tree, int value) {
    if (!tree)
        return leaf(value); // If tree point nothing, we create a leaf
    if (value < tree->value)
        tree->left = insert(tree->left, value); // move the tree pointer to left (@ 26:56)
    if (value > tree->value)
        tree->right = insert(tree->right, value); // move the tree pointer to right
    return tree;
}

void printTree(struct node *tree) {
    if (!tree)
        return;
    printTree(tree->left);
    printf("%d ", tree->value);
    printTree(tree->right);
}

void freeNodes(struct node *node) {
    if (!node)
        return;
    freeNodes(node->left);
    freeNodes(node->right);
    // Right now, the nodes do not have children
    free(node);
}