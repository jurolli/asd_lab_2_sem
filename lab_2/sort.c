
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

void swapKeys(keyType *a, keyType *b)
{
    keyType c = *a;
    *a = *b;
    *b = c;
}

void swapStrings(char **a, char **b)
{
    char *c = *a;
    *a = *b;
    *b = c;
}

void heapy(Table *table, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && table->keys[left] > table->keys[largest])
    {
        largest = left;
    }
    if (right < n && table->keys[right] > table->keys[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        swapKeys(&table->keys[i], &table->keys[largest]);
        swapStrings(&table->data[i], &table->data[largest]);
        heapy(table, n, largest);
    }
}

void heap_sort(Table *table)
{
    int n = table->size;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapy(table, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swapKeys(&table->keys[0], &table->keys[i]);
        swapStrings(&table->data[0], &table->data[i]);
        heapy(table, i, 0);
    }
}
