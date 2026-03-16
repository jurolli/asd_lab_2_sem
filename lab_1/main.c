

#include <stdlib.h>
#include <stdio.h>
#include "tree.c"

int main()
{
    int choice, data, parent_data;
    struct node *root = NULL;
    struct node *parent_node = NULL;
    do
    {
        printf("\n   Выберите команду:\n1. Создать дерево\n2. Напечатать дерево\n3. Добавить новый узел\n4. Удалить дерево\n5. Определить число вершин дерева,\n   степень которых совпадает со значением элемента\n0. Выйти\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("! Ошибка ввода\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            if (root != NULL)
            {
                printf("! Дерево уже существует\n");
            }
            else
            {
                printf("Введите корень: ");
                scanf("%d", &data);
                root = create_node(data);
                if (root)
                    printf("Дерево создано\n");
            }
            break;

        case 2:
            if (root == NULL)
            {
                printf("! Дерево не создано\n");
            }
            else
            {
                printf("Дерево:\n");
                print_tree(root, 0);
            }
            break;

        case 3:
            if (root == NULL)
            {
                printf("! Дерево не создано\n");
            }
            else
            {
                printf("Введите значение родительского узла: ");
                scanf("%d", &parent_data);
                parent_node = find_node(root, parent_data);
                if (parent_node == NULL)
                {
                    printf("! Родительский узел со значением %d не найден\n", parent_data);
                    break;
                }
                printf("Введите значение для нового узла: ");
                scanf("%d", &data);
                insert_node(parent_node, data);
            }
            break;

        case 4:
            if (root == NULL)
            {
                printf("! Дерево не создано\n");
            }
            else
            {
                free_tree(root);
                root = NULL;
                printf("Дерево удалено\n");
            }
            break;

        case 5:
            if (root == NULL)
            {
                printf("! Дерево не создано\n");
            }
            else
            {
                int count = count_nodes_with_matching_degree(root);
                printf("Вершин, степень которых совпадает со значением: %d\n", count);
            }
            break;

        case 0:
            if (root != NULL)
            {
                free_tree(root);
            }
            printf("Программа завершена\n\n");
            break;

        default:
            printf("! Неверный выбор. Попробуйте снова\n");
        }

    } while (choice != 0);
    return 0;
}
