#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char *argv[])
{
    int fromFile = 0;

    if (argc == 2)
    {
        fromFile = 1;

        if (!freopen(argv[1], "r", stdin))
        {
            printf("Ошибка открытия файла %s\n", argv[1]);
            return 1;
        }
    }

    Tree tree;
    initTree(&tree);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("Доступные команды:\n");
        printf("1. Добавление значение по ключу\n");
        printf("2. Удаление узла по ключу\n");
        printf("3. Выведение дерева\n");
        printf("4. Нахождение значения по ключу\n");
        printf("0. Выход\n");
        printf("Ввод: ");

        read = getline(&line, &len, stdin);
        if (read == -1)
            break;

        if (read > 0 && line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (strcmp(line, "0") == 0)
            break;

        if (line[0] == '\0')
            continue;

        char *token = strtok(line, " ");
        if (!token)
            continue;

        int cmd = atoi(token);

        switch (cmd)
        {
        case 1:
        {
            char *key = strtok(NULL, " ");
            char *valStr = strtok(NULL, " ");

            if (!key || !valStr)
            {
                break;
            }

            double value = atof(valStr);
            insert(&tree, key, value);
            break;
        }

        case 2:
        {
            char *key = strtok(NULL, " ");
            if (!key)
            {
                printf("Ошибка: нужен key\n");
                break;
            }

            deleteNode(&tree, key);
            break;
        }

        case 3:
            printTree(&tree);
            break;

        case 4:
        {
            char *key = strtok(NULL, " ");
            if (!key)
            {
                printf("Ошибка: нужен key\n");
                break;
            }

            Node *res = search(&tree, key);
            if (res == NULL || strcmp(res->key, key) != 0)
                printf("Не найдено\n");
            else
                printf("Значение: %.2lf\n", res->value);

            break;
        }

        default:
            printf("Неизвестная команда\n");
        }
    }

    free(line);
    destroyTree(&tree);

    return 0;
}