
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "table.h"

void empty_table()
{
    printf("Тест 1: Пустая таблица\n");
    Table table;
    table.size = 0;
    table.keys = NULL;
    table.data = NULL;
    print_table(&table);

    heap_sort(&table);
    assert(table.size == 0);
    free_table(&table);
    printf("Тест 1 пройден\n");
}

void already_sorted_table()
{
    printf("Тест 2: Уже отсортированная таблица\n");
    Table table;
    read_file("files/test_2.txt", &table);
    print_table(&table);

    heap_sort(&table);

    for (int i = 0; i < table.size - 1; i++)
    {
        assert(table.keys[i] < table.keys[i + 1]);
    }
    free_table(&table);
    printf("Тест 2 пройден\n");
}

void reverse_sorted_table()
{
    printf("Тест 3: Обратная сортировка таблицы\n");
    Table table;
    read_file("files/test_3.txt", &table);
    print_table(&table);

    heap_sort(&table);

    for (int i = 0; i < table.size - 1; i++)
    {
        assert(table.keys[i] <= table.keys[i + 1]);
    }
    free_table(&table);
    printf("Тест 3 пройден\n");
}

void unsorted_table()
{
    printf("Тест 4: Неотсортированная таблица\n");
    Table table;
    read_file("files/test_4.txt", &table);
    print_table(&table);

    heap_sort(&table);

    for (int i = 0; i < table.size - 1; i++)
    {
        assert(table.keys[i] < table.keys[i + 1]);
    }
    free_table(&table);
    printf("Тест 4 пройден\n");
}

void binary_search_test()
{
    printf("Тест 5: Бинарный поиск\n");
    Table table;
    read_file("files/test_5.txt", &table);
    print_table(&table);

    heap_sort(&table);

    keyType key = 33.5;
    char *data = binary_search(&table, key);
    assert(data != NULL);
    assert(strcmp(data, "zxcVBN789") == 0);

    char *result = binary_search(&table, 345643);
    assert(result == NULL);

    free_table(&table);
    printf("Тест 5 пройден\n");
}

int main()
{
    binary_search_test();
    unsorted_table();
    reverse_sorted_table();
    empty_table();
    already_sorted_table();
    printf("\nВсе тесты завершены\n");
    return 0;
}