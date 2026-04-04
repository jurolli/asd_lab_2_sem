#include <stdio.h>
#include <string.h>
#include "parse.h"
#include "tree.h"

void sprint_postfix(TreeNode *root, char *buffer)
{
    if (root == NULL)
    {
        return;
    }
    sprint_postfix(root->left, buffer);
    sprint_postfix(root->right, buffer);
    char temp[32];
    if (root->sign == 0)
    {
        sprintf(temp, "%d ", root->value);
    }
    else
    {
        sprintf(temp, "%c ", root->sign);
    }
    strcat(buffer, temp);
}

void test_simple_number()
{
    printf("\nТест 1. Одиночное число\n");
    TreeNode *root = parse_expression("42");
    if (root && root->value == 42 && root->sign == 0)
    {
        printf("  Парсинг числа 42: ОК\n");
    }
    else
    {
        printf("  Ошибка в парсинге числа\n");
    }
    free_tree(root);
}

void test_priorities()
{
    printf("\nТест 2. Приоритеты операций\n");
    TreeNode *root = parse_expression("(7 + 4 * 5) ^ 2");
    if (root && root->sign == '^' && root->left->sign == '+' && root->left->left->value == 7 && root->left->right->sign == '*' && root->left->right->left->value == 4 && root->left->right->right->value == 5 && root->right->value == 2)
    {
        printf("  Парсинг выражения '(7 + 4 * 5) ^ 2': ОК\n");
    }
    else
    {
        printf("  Ошибка в парсинге приоритетов\n");
    }
    free_tree(root);
}

void test_pow_zero()
{
    printf("\nТест 3. Степень 0 (5 ^ 0)\n");
    TreeNode *root = parse_expression("5 ^ 0");
    root = transform(root);
    if (root && root->sign == 0 && root->value == 1)
    {
        printf("  5^0  в 1: ОК\n");
    }
    else
    {
        printf("  Ошибка в обработке нулевой степени\n");
    }
    free_tree(root);
}

void test_pow_three()
{
    printf("\nТест 4. Возведение в куб (2^3)\n");
    TreeNode *root = parse_expression("2^3");
    root = transform(root);
    char res[100] = "";
    sprint_postfix(root, res);
    if (strcmp(res, "2 2 * 2 * ") == 0)
        printf("  Результат: %s - ОК\n", res);
    else
        printf("  Ошибка! Получено: %s\n", res);
    free_tree(root);
}

void test_complex_base()
{
    printf("\nТест 5. Сложное основание ((1+2)^2)\n");
    TreeNode *root = parse_expression("(1+2)^2");
    root = transform(root);
    char res[100] = "";
    sprint_postfix(root, res);
    if (strcmp(res, "1 2 + 1 2 + * ") == 0)
        printf("  Результат: %s - ОК\n", res);
    else
        printf("  Ошибка! Получено: %s\n", res);
    free_tree(root);
}

int main()
{
    test_simple_number();
    test_priorities();
    test_pow_zero();
    test_pow_three();
    test_complex_base();
    return 0;
}