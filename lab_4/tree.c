
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

static Node *NIL;

Node *createNode(char *key, double value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NULL;
    return newNode;
}

void initTree(Tree *tree)
{
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NULL;
    tree->root = NIL;
}

// повороты

void leftRotate(Tree *tree, Node *a)
{
    Node *b = a->right;
    a->right = b->left;

    if (b->left != NIL)
    {
        b->left->parent = a;
    }
    b->parent = a->parent;
    if (a->parent == NIL)
    {
        tree->root = b;
    }
    else if (a == a->parent->left)
    {
        a->parent->left = b;
    }
    else
    {
        a->parent->right = b;
    }
    b->left = a;
    a->parent = b;
}

void rightRotate(Tree *tree, Node *b)
{
    Node *a = b->left;
    b->left = a->right;

    if (a->right != NIL)
    {
        a->right->parent = b;
    }
    a->parent = b->parent;

    if (b->parent == NIL)
    {
        tree->root = a;
    }
    else if (b == b->parent->right)
    {
        b->parent->right = a;
    }
    else
    {
        b->parent->left = a;
    }
    a->right = b;
    b->parent = a;
}

// вставка

void fixInsert(Tree *tree, Node *x)
{
    while (x->parent->color == RED)
    {
        if (x->parent == x->parent->parent->left)
        {
            Node *b = x->parent->parent->right;

            if (b->color == RED)
            {
                x->parent->color = BLACK;
                b->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    leftRotate(tree, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rightRotate(tree, x->parent->parent);
            }
        }
        else
        {
            Node *b = x->parent->parent->left;
            if (b->color == RED)
            {
                x->parent->color = BLACK;
                b->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rightRotate(tree, x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                leftRotate(tree, x->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

void insert(Tree *tree, char *key, double value)
{
    Node *c = createNode(key, value);
    Node *b = NIL;
    Node *a = tree->root;

    while (a != NIL)
    {
        b = a;
        if (strcmp(c->key, a->key) < 0)
        {
            a = a->left;
        }
        else
        {
            a = a->right;
        }
    }
    c->parent = b;

    if (b == NIL)
    {
        tree->root = c;
    }
    else if (strcmp(c->key, b->key) < 0)
    {
        b->left = c;
    }
    else
    {
        b->right = c;
    }

    fixInsert(tree, c);
}

// поиск

Node *search(Tree *tree, char *key)
{
    Node *node = tree->root;

    while (node != NIL)
    {
        int cmp = strcmp(key, node->key);
        if (cmp == 0)
        {
            return node;
        }
        else if (cmp < 0)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return NIL;
}

// удаление

Node *minimum(Node *node)
{
    while (node->left != NIL)
        node = node->left;
    return node;
}

void trans(Tree *tree, Node *u, Node *v)
{
    if (u->parent == NIL)
    {
        tree->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void fixDelete(Tree *tree, Node *x)
{
    while (x != tree->root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            Node *w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else
        {
            Node *w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                w->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void deleteNode(Tree *tree, char *key)
{
    Node *z = search(tree, key);
    if (z == NIL)
        return;

    Node *y = z;
    Node *x;
    int yColor = y->color;

    if (z->left == NIL)
    {
        x = z->right;
        trans(tree, z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        trans(tree, z, z->left);
    }
    else
    {
        y = minimum(z->right);
        yColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            trans(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        trans(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yColor == BLACK)
    {
        fixDelete(tree, x);
    }
}

// печать

void printHelper(Node *n, int depth)
{
    if (n == NIL)
        return;

    printHelper(n->right, depth + 1);

    for (int i = 0; i < depth; i++)
        printf("   ");

    printf("%s %.2lf (%c)\n", n->key, n->value, n->color == RED ? 'R' : 'B');

    printHelper(n->left, depth + 1);
}

void printTree(Tree *tree)
{
    if (tree->root == NIL)
    {
        printf("Дерево пустое\n");
        return;
    }

    printHelper(tree->root, 0);
}

// удаление

void freeNodes(Node *n)
{
    if (n == NIL)
        return;

    freeNodes(n->left);
    freeNodes(n->right);
    free(n);
}

void destroyTree(Tree *t)
{
    freeNodes(t->root);
    free(NIL);
}