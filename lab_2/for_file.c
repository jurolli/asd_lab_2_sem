
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

void free_table(Table *table)
{
    if (table->data)
    {
        for (int i = 0; i < table->size; i++)
        {
            if (table->data[i])
            {
                free(table->data[i]);
            }
        }
    }
    free(table->data);
    free(table->keys);
    table->keys = NULL;
    table->data = NULL;
    table->size = 0;
}

void read_file(const char *file_name, Table *table)
{
    FILE *file = fopen(file_name, "r");
    if (!file)
    {
        printf("! Не удалось открыть файл %s\n", file_name);
        return;
    }

    fscanf(file, "%d", &table->size);

    table->data = (char **)malloc(table->size * sizeof(char *));
    table->keys = (keyType *)malloc(table->size * sizeof(keyType));

    for (int i = 0; i < table->size; i++)
    {
        if (fscanf(file, "%lf", &table->keys[i]) != 1)
        {
            printf("! Ошибка чтения ключа из файла\n");
            free_table(table);
            fclose(file);
            return;
        }

        char *line = NULL;
        size_t len = 0;

        if (getline(&line, &len, file) == -1)
        {
            printf("! Ошибка чтения строки из файла\n");
            free(line);
            fclose(file);
            free_table(table);
            return;
        }

        size_t line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
        }
        table->data[i] = line;
    }
    fclose(file);
}

void print_table(Table *table)
{
    for (int i = 0; i < table->size; i++)
    {
        printf("%g: %s\n", table->keys[i], table->data[i]);
    }
}
