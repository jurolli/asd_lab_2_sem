
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include <math.h>

char *binary_search(Table *table, keyType key)
{
    int left = 0;
    int right = table->size - 1;
    double eps = 0.000001;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (fabs(table->keys[mid] - key) < eps)
        {
            return table->data[mid];
        }
        else if (table->keys[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return NULL;
}
