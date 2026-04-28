
#ifndef TREE_H
#define TREE_H

#define RED 1
#define BLACK 0

typedef struct Node
{
    char key[7];
    double value;
    int color;
    struct Node *left, *right, *parent;
} Node;

typedef struct
{
    Node *root;
} Tree;

void initTree(Tree *tree);

void insert(Tree *tree, char *key, double value);
void deleteNode(Tree *tree, char *key);
Node *search(Tree *tree, char *key);

void printTree(Tree *tree);
void destroyTree(Tree *tree);

#endif // TREE_H