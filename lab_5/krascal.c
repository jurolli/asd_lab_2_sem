#include <stdlib.h>
#include "krascal.h"

int compare_edges(const void* a, const void* b) {
    Edge* e1 = (Edge*)a;
    Edge* e2 = (Edge*)b;
    if (e1->weight < e2->weight) return -1;
    if (e1->weight > e2->weight) return 1;
    return 0;
}

DSU* create_dsu(int n) {
    DSU *d = (DSU*)malloc(sizeof(DSU));
    d->n = n;
    d->parent = (int*)malloc(n * sizeof(int));
    d->size = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        d->parent[i] = i;
        d->size[i] = 1;
    }
    return d;
}

int find_set(DSU *d, int v) {
    if (v == d->parent[v]) return v;
    return d->parent[v] = find_set(d, d->parent[v]);
}

void union_sets(DSU *d, int a, int b) {
    a = find_set(d, a);
    b = find_set(d, b);
    if (a != b) {
        if (d->size[a] < d->size[b]) {
            int temp = a; a = b; b = temp;
        }
        d->parent[b] = a;
        d->size[a] += d->size[b];
    }
}

void free_dsu(DSU *d) {
    free(d->parent);
    free(d->size);
    free(d);
}

Edge* run_krascal(Edge* edges, int num_vertices, int num_edges, int* mst_size, double* total_weight) {
    // 1. Сортируем ребра
    qsort(edges, num_edges, sizeof(Edge), compare_edges);

    DSU* d = create_dsu(num_vertices);
    Edge* mst = (Edge*)malloc((num_vertices - 1) * sizeof(Edge));
    *mst_size = 0;
    *total_weight = 0;

    // 2. Проход по ребрам
    for (int i = 0; i < num_edges; i++) {
        if (find_set(d, edges[i].src) != find_set(d, edges[i].dest)) {
            union_sets(d, edges[i].src, edges[i].dest);
            mst[*mst_size] = edges[i];
            (*mst_size)++;
            *total_weight += edges[i].weight;
        }
    }

    free_dsu(d);
    return mst;
}