#include <stdio.h>
#include <string.h>
#include "tree.h"

void test_insert_one()
{
    printf("\nТест 1. Вставка одного элемента\n");

    Tree t;
    initTree(&t);

    insert(&t, "a", 10);

    Node *res = search(&t, "a");
    if (res && strcmp(res->key, "a") == 0 && res->value == 10)
        printf("  Вставка одного элемента: ОК\n");
    else
        printf("  Ошибка вставки\n");

    destroyTree(&t);
}

// void test_insert_many()
// {
//     printf("\nТест 2. Вставка нескольких элементов\n");

//     Tree t;
//     initTree(&t);

//     insert(&t, "a", 1);
//     insert(&t, "b", 2);
//     insert(&t, "c", 3);

//     if (search(&t, "a") && search(&t, "b") && search(&t, "c"))
//         printf("  Вставка нескольких элементов: ОК\n");
//     else
//         printf("  Ошибка вставки нескольких\n");

//     destroyTree(&t);
// }

void test_duplicate_key()
{
    printf("\nТест 3. Дубликат ключа\n");

    Tree t;
    initTree(&t);

    insert(&t, "a", 10);
    insert(&t, "a", 20);

    Node *res = search(&t, "a");

    if (res && res->value == 20)
        printf("  Обновление значения: ОК\n");
    else
        printf("  Ошибка обновления\n");

    destroyTree(&t);
}

void test_delete_leaf()
{
    printf("\nТест 4. Удаление листа\n");

    Tree t;
    initTree(&t);

    insert(&t, "a", 1);
    insert(&t, "b", 2);

    deleteNode(&t, "b");

    Node *res = search(&t, "b");

    if (res == NULL || strcmp(res->key, "b") != 0)
        printf("  Удаление листа: ОК\n");
    else
        printf("  Ошибка удаления\n");

    destroyTree(&t);
}

void test_delete_root()
{
    printf("\nТест 5. Удаление корня\n");

    Tree t;
    initTree(&t);

    insert(&t, "a", 1);

    deleteNode(&t, "a");

    if (t.root == NULL || t.root->key[0] == '\0')
        printf("  Удаление корня: ОК\n");
    else
        printf("  Ошибка удаления корня\n");

    destroyTree(&t);
}

void test_search_not_found()
{
    printf("\nТест 6. Поиск несуществующего ключа\n");

    Tree t;
    initTree(&t);

    insert(&t, "a", 1);

    Node *res = search(&t, "z");

    if (res == NULL || strcmp(res->key, "z") != 0)
        printf("  Поиск отсутствующего: ОК\n");
    else
        printf("  Ошибка поиска\n");

    destroyTree(&t);
}

int main()
{
    test_insert_one();
    // test_insert_many();
    test_duplicate_key();
    test_delete_leaf();
    test_delete_root();
    test_search_not_found();

    return 0;
}