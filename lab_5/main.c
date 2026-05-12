#include <stdio.h>
#include <stdlib.h>
#include "krascal.h"

int main() {
    int V, E;
    printf("Введите количество вершин и ребер: ");
    if (scanf("%d %d", &V, &E) != 2) {
        return 1;
    }

    Edge* edges = (Edge*)malloc(E * sizeof(Edge));
    printf("Введите ребра (откуда куда вес):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %lf", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    int mst_count = 0;
    double total_w = 0;
    Edge* result = run_krascal(edges, V, E, &mst_count, &total_w);

    printf("\nМинимальное остовное дерево:\n");
    for (int i = 0; i < mst_count; i++) {
        printf("%d - %d (вес: %.2f)\n", result[i].src, result[i].dest, result[i].weight);
    }
    printf("Общий вес: %.2f\n", total_w);

    if (mst_count < V - 1) {
        printf("Предупреждение: Граф несвязный, MST неполный.\n");
    }

    free(edges);
    free(result);
    return 0;
}
