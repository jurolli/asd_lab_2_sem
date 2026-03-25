
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

void free_table(Table *table);
void read_file(const char *file_name, Table *table);
void print_table(Table *table);

void heap_sort(Table *table);

char *binary_search(Table *table, keyType key);

int main()
{
    Table table;
    read_file("files/text.txt", &table);
    if (table.size == 0)
    {
        printf("! Таблица пуста\n");
        return 1;
    }

    printf("Таблица до сортировки:\n");
    print_table(&table);

    heap_sort(&table);

    printf("\nТаблица после сортировки:\n");
    print_table(&table);

    int choice;

    do
    {
        printf("1. Поиск элемента в таблице по ключу\n");
        printf("0. Выход\n");
        printf("Действие: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Неправильный формат ввода\n");
            return 0;
        }
        keyType x;
        switch (choice)
        {
        case 1:
            printf("Введите ключ: ");
            if (scanf("%lf", &x) != 1)
            {
                printf("Неправильный формат ввода\n");
                continue;
            }
            char *finded = binary_search(&table, x);
            if (finded == NULL)
            {
                printf("Данный элемент не найден.\n");
            }
            else
            {
                printf("%s\n", finded);
            }
            break;
        case 0:
            break;
        default:
            printf("?\n");
            break;
        }
    } while (choice);

    free_table(&table);
    return 0;
}