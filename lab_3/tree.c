
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parse.h"

TreeNode *create_sign_node(char sign, TreeNode *left, TreeNode *right)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->sign = sign;
    node->left = left;
    node->right = right;
    node->value = 0;
    return node;
}

TreeNode *create_value_node(int value)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->value = value;
    node->sign = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

TreeNode *copy_tree(TreeNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->sign != 0)
    {
        TreeNode *left_copy = copy_tree(root->left);
        TreeNode *right_copy = copy_tree(root->right);
        return create_sign_node(root->sign, left_copy, right_copy);
    }
    else
    {
        return create_value_node(root->value);
    }
}

TreeNode *transform(TreeNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    root->left = transform(root->left);
    root->right = transform(root->right);

    if (root->sign == '^' && root->right && root->right->sign == 0)
    {
        int pow = root->right->value;
        TreeNode *new_root = NULL;

        if (pow <= 0)
        {
            new_root = create_value_node(1);
        }
        else if (pow == 1)
        {
            new_root = copy_tree(root->left);
        }
        else
        {
            new_root = copy_tree(root->left);
            for (int i = 1; i < pow; i++)
            {
                new_root = create_sign_node('*', new_root, copy_tree(root->left));
            }
        }

        free_tree(root);
        return new_root;
    }
    return root;
}

void print_postfix(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    print_postfix(root->left);
    print_postfix(root->right);
    if (root->sign == 0)
    {
        printf("%d ", root->value);
    }
    else
    {
        printf("%c ", root->sign);
    }
}

void print_tree(TreeNode *root, int level)
{
    if (root == NULL)
    {
        return;
    }
    print_tree(root->right, level + 1);

    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    if (root->sign == 0)
    {
        printf("%d\n", root->value);
    }
    else
    {
        printf("%c\n", root->sign);
    }
    print_tree(root->left, level + 1);
}

void print_infix(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->sign == 0)
    {
        printf("%d", root->value);
        return;
    }

    int prio = priority(root->sign);

    if (root->left && root->left->sign != 0 && priority(root->left->sign) < prio)
    {
        printf("(");
        print_infix(root->left);
        printf(")");
    }
    else
    {
        print_infix(root->left);
    }
    printf(" %c ", root->sign);

    if (root->right && root->right->sign != 0 && priority(root->right->sign) < prio)
    {
        printf("(");
        print_infix(root->right);
        printf(")");
    }
    else
    {
        print_infix(root->right);
    }
}