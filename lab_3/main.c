
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parse.h"

int main()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("\nВведите выражение: ");
    read = getline(&line, &len, stdin);
    if (read == -1)
    {
        perror("\nОшибка чтения строки");
        free(line);
        return 1;
    }
    else
    {
        if (read > 0 && line[read - 1] == '\n')
        {
            line[read - 1] = '\0';
        }
        TreeNode *root = parse_expression(line);
        printf("\nИсходное выражение в дереве:\n");
        print_tree(root, 0);
        printf("\nПостфиксная запись:\n");
        print_postfix(root);
        printf("\n");
        root = transform(root);
        printf("\n");
        printf("\nПреобразованное выражение:\n\n");
        print_infix(root);
        printf("\n\n");
        print_tree(root, 0);

        free_tree(root);
    }
    free(line);
    return 0;
}