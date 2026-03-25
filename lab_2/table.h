#ifndef TABLE_H
#define TABLE_H

typedef double keyType;

typedef struct
{
    char **data;
    keyType *keys;
    int size;
} Table;

void free_table(Table *table);
void read_file(const char *file_name, Table *table);
void print_table(Table *table);
char *binary_search(Table *table, keyType key);
void heap_sort(Table *table);

#endif