#ifndef STACK_H
#define STACK_H

#include "tree.h"

typedef struct CharNode
{
    char data;
    struct CharNode *next;
} CharNode;

typedef struct
{
    CharNode *top;
} CharStack;

typedef struct NodeNode
{
    TreeNode *data;
    struct NodeNode *next;
} NodeNode;

typedef struct NodeStack
{
    NodeNode *top;
} NodeStack;

void create_node_stack(NodeStack *stack);
void free_node_stack(NodeStack *stack);
int is_node_empty(NodeStack *s);
void push_node(NodeStack *stack, TreeNode *data);
TreeNode *pop_node(NodeStack *stack);

void create_char_stack(CharStack *stack);
void free_char_stack(CharStack *stack);
int is_char_empty(CharStack *stack);
void push_char(CharStack *stack, char data);
char pop_char(CharStack *stack);
char peek_char(CharStack *stack);

#endif