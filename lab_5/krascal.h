
#ifndef KRASCAL_H
#define KRASCAL_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int src, dest;
    double weight;
} Edge;

typedef struct {
    int *parent;
    int *size;
    int n;
} DSU;

DSU* create_dsu(int n);
int find_set(DSU *d, int v);
void union_sets(DSU *d, int a, int b);
void free_dsu(DSU *d);

Edge* run_krascal(Edge* edges, int num_vertices, int num_edges, int* mst_size, double* total_weight);
#ifdef __cplusplus
}
#endif
#endif //KRASCAL_H
