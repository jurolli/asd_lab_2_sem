#include "tree.c"
#include <stdio.h>

void test_create_node()
{
    printf("\n Тест 1. Создание дерева\n");
    struct node *n = create_node(42);
    if (n != NULL)
    {
        if (n->data == 42)
        {
            if (n->first_child == NULL)
            {
                if (n->next == NULL)
                {
                    printf("  create_node работает корректно\n");
                }
            }
        }
    }
    else
    {
        printf("  create_node работает некорректно\n");
    }
    free(n);
}

void test_insert_node()
{
    printf("\n Тест 2. Добавить новый узел\n");
    struct node *root = create_node(1);
    insert_node(root, 2);
    insert_node(root, 3);
    if (root->first_child != NULL)
    {
        if (root->first_child->data == 2)
        {
            if (root->first_child->next != NULL)
            {
                if (root->first_child->next->data == 3)
                {
                    printf("  insert_node работает корректно\n");
                }
            }
        }
    }
    else
    {
        printf("  insert_node работает некорректно\n");
    }
    free_tree(root);
}

void test_empty_tree()
{
    printf("\n Тест 3. Пустое дерево\n");
    struct node *root = NULL;
    int nodes = count_nodes(root);
    int matching = count_nodes_with_matching_degree(root);
    if (nodes == 0)
    {
        if (matching == 0)
        {
            printf("  Функции корректно работают с пустым деревом\n");
        }
    }
    else
    {
        printf("  Ошибка в работе с пустым деревом\n");
    }
}

void test_count_nodes()
{
    printf("\n Тест 4. Подсчет узлов\n");
    struct node *root = create_node(1);
    insert_node(root, 2);
    insert_node(root, 3);
    insert_node(root->first_child, 4);
    int total = count_nodes(root);
    if (total == 4)
    {
        printf("  count_nodes работает корректно (найдено %d узлов)\n", total);
    }
    else
    {
        printf("  count_nodes работает некорректно (ожидалось 4, получено %d)\n", total);
    }
    free_tree(root);
}

void test_large_tree()
{
    printf("\n Тест 5. Большое дерево\n");
    struct node *root = create_node(1);
    insert_node(root, 2);
    insert_node(root, 3);
    insert_node(root->first_child, 4);
    insert_node(root->first_child->next, 5);
    int total = count_nodes(root);
    if (total == 5)
    {
        printf("  Дерево создано корректно (5 узлов)\n");
    }
    else
    {
        printf("  Ошибка при создании дерева (ожидалось 5, получено %d)\n", total);
    }
    free_tree(root);
}

void test_matching_degree()
{
    printf("\n Тест 6. Функция\n");
    struct node *root = create_node(2); // степень 2 (два потомка)
    insert_node(root, 3);
    insert_node(root, 4);
    insert_node(root->first_child, 1); // степень 0
    int matching = count_nodes_with_matching_degree(root);
    if (matching == 1)
    {
        printf("  count_nodes_with_matching_degree работает корректно (найдено %d узлов)\n", matching);
    }
    else
    {
        printf("  count_nodes_with_matching_degree работает некорректно (ожидалось 1, получено %d)\n", matching);
    }
    free_tree(root);
}

int main()
{
    test_create_node();
    test_insert_node();
    test_empty_tree();
    test_count_nodes();
    test_large_tree();
    test_matching_degree();
    printf("\nВсе тесты завершены\n");
    return 0;
}