
#include <stdlib.h>
#include "stack.h"

void create_char_stack(CharStack *stack)
{
    stack->top = NULL;
}

int is_char_empty(CharStack *stack)
{
    return stack->top == NULL;
}

void free_char_stack(CharStack *stack)
{
    while (!is_char_empty(stack))
    {
        pop_char(stack);
    }
}

void push_char(CharStack *stack, char data)
{
    CharNode *new_node = (CharNode *)malloc(sizeof(CharNode));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

char pop_char(CharStack *stack)
{
    if (is_char_empty(stack))
    {
        return 0;
    }
    CharNode *top_node = stack->top;
    stack->top = top_node->next;
    char value = top_node->data;
    free(top_node);
    return value;
}

char peek_char(CharStack *stack)
{
    if (is_char_empty(stack))
    {
        return 0;
    }
    return stack->top->data;
}

void create_node_stack(NodeStack *stack)
{
    stack->top = NULL;
}

int is_node_empty(NodeStack *stack)
{
    return stack->top == NULL;
}

void free_node_stack(NodeStack *stack)
{
    while (!is_node_empty(stack))
    {
        pop_node(stack);
    }
}

void push_node(NodeStack *stack, TreeNode *data)
{
    NodeNode *new_node = (NodeNode *)malloc(sizeof(NodeNode));
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
}

TreeNode *pop_node(NodeStack *stack)
{
    if (is_node_empty(stack))
    {
        return NULL;
    }
    NodeNode *top_node = stack->top;
    stack->top = top_node->next;
    TreeNode *value = top_node->data;
    free(top_node);
    return value;
}

TreeNode *peek_node(NodeStack *stack)
{
    if (is_node_empty(stack))
    {
        return NULL;
    }
    return stack->top->data;
}