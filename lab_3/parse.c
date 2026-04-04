#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "stack.h"

int priority(char sign)
{
    switch (sign)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

TreeNode *build_node(char sign, NodeStack *values)
{
    TreeNode *right = pop_node(values);
    TreeNode *left = pop_node(values);
    return create_sign_node(sign, left, right);
}

TreeNode *parse_expression(char *expr)
{
    CharStack signs;
    NodeStack values;
    create_char_stack(&signs);
    create_node_stack(&values);

    for (int i = 0; expr[i]; i++)
    {
        if (isspace(expr[i]))
        {
            continue;
        }
        if (isdigit(expr[i]))
        {
            int value = 0;
            while (isdigit(expr[i]))
            {
                value = value * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            push_node(&values, create_value_node(value));
        }
        else if (expr[i] == '(')
        {
            push_char(&signs, '(');
        }
        else if (expr[i] == ')')
        {
            while (!is_char_empty(&signs) && peek_char(&signs) != '(')
            {
                push_node(&values, build_node(pop_char(&signs), &values));
            }
            pop_char(&signs);
        }
        else if (priority(expr[i]) > 0)
        {
            while (!is_char_empty(&signs) && priority(peek_char(&signs)) >= priority(expr[i]))
            {
                push_node(&values, build_node(pop_char(&signs), &values));
            }
            push_char(&signs, expr[i]);
        }
    }

    while (!is_char_empty(&signs))
    {
        push_node(&values, build_node(pop_char(&signs), &values));
    }

    TreeNode *root = pop_node(&values);

    free_char_stack(&signs);
    free_node_stack(&values);

    return root;
}