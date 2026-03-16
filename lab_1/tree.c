
#include <stdlib.h>
#include <stdio.h>

struct node
{
    struct node *first_child;
    struct node *next;
    int data;
};

struct node *create_node(int data)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    if (!n)
    {
        printf("! Не получилось(\n");
        return NULL;
    }
    n->first_child = NULL;
    n->next = NULL;
    n->data = data;
    return n;
}

struct node *find_node(struct node *root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == data)
    {
        return root;
    }
    struct node *found = find_node(root->first_child, data);
    if (found != NULL)
    {
        return found;
    }
    return find_node(root->next, data);
}

void insert_node(struct node *parent, int data)
{
    if (!parent)
    {
        printf("! Родитель не существует\n");
        return;
    }
    struct node *new_node = create_node(data);
    if (!new_node)
        return;
    if (parent->first_child == NULL)
    {
        parent->first_child = new_node;
    }
    else
    {
        struct node *current = parent->first_child;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
    printf("Узел %d добавлен как потомок узла %d\n", data, parent->data);
}

int count_nodes(struct node *root)
{
    if (root == NULL)
        return 0;
    return 1 + count_nodes(root->first_child) + count_nodes(root->next);
}

int get_node_degree(struct node *node)
{
    if (node == NULL)
        return 0;
    int degree = 0;
    struct node *child = node->first_child;
    while (child != NULL)
    {
        degree++;
        child = child->next;
    }
    return degree;
}

int count_nodes_with_matching_degree(struct node *root)
{
    if (root == NULL)
        return 0;

    int count = 0;
    if (get_node_degree(root) == root->data)
        count = 1;
    return count + count_nodes_with_matching_degree(root->first_child) + count_nodes_with_matching_degree(root->next);
}

void free_tree(struct node *root)
{
    if (root == NULL)
        return;
    free_tree(root->first_child);
    free_tree(root->next);
    free(root);
}

struct node *find_parent(struct node *root, struct node *target)
{
    if (root == NULL)
        return NULL;
    struct node *child = root->first_child;
    while (child != NULL)
    {
        if (child == target)
            return root;

        struct node *found = find_parent(child, target);
        if (found != NULL)
            return found;
        child = child->next;
    }
    return NULL;
}

void remove_child(struct node *parent, struct node *child_to_remove)
{
    if (parent->first_child == child_to_remove)
    {
        parent->first_child = child_to_remove->next;
        return;
    }
    struct node *prev = parent->first_child;
    while (prev->next != child_to_remove)
    {
        prev = prev->next;
    }
    prev->next = child_to_remove->next;
}

void delete_node(struct node **root, struct node *node_to_delete)
{
    if (root == NULL || *root == NULL || node_to_delete == NULL)
        return;

    if (*root == node_to_delete)
    {
        free_tree(*root);
        *root = NULL;
        printf("Корень удален\n");
        return;
    }

    struct node *parent = find_parent(*root, node_to_delete);

    if (parent == NULL)
    {
        printf("Узел не найден\n");
        return;
    }
    remove_child(parent, node_to_delete);
    node_to_delete->next = NULL;
    free_tree(node_to_delete);
    printf("Узел удален\n");
}

void print_tree(struct node *root, int level)
{
    if (root == NULL)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("%d\n", root->data);
    print_tree(root->first_child, level + 1);
    print_tree(root->next, level);
}