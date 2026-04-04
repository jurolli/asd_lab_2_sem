#ifndef TREE_H
#define TREE_H

typedef struct TreeNode
{
    int value;
    char sign;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_value_node(int value);
TreeNode *create_sign_node(char sign, TreeNode *left, TreeNode *right);

void free_tree(TreeNode *root);
TreeNode *transform(TreeNode *root);
TreeNode *copy_tree(TreeNode *root);

void print_postfix(TreeNode *root);
void print_tree(TreeNode *root, int level);
void print_infix(TreeNode *root);

#endif
