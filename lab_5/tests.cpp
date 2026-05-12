#include <gtest/gtest.h>
#include "krascal.h"

TEST(DSUTest, UnionFind) {
    DSU* d = create_dsu(10);
    union_sets(d, 1, 2);
    union_sets(d, 2, 3);
    EXPECT_EQ(find_set(d, 1), find_set(d, 3));
    EXPECT_NE(find_set(d, 1), find_set(d, 4));
    free_dsu(d);
}

TEST(KrascalTest, SimpleGraph) {
    int V = 3, E = 3;
    Edge edges[] = {
        {0, 1, 10.0},
        {1, 2, 5.0},
        {0, 2, 2.0}
    };

    int mst_size = 0;
    double total_weight = 0;
    Edge* mst = run_krascal(edges, V, E, &mst_size, &total_weight);

    EXPECT_EQ(mst_size, 2);
    EXPECT_DOUBLE_EQ(total_weight, 7.0);

    free(mst);
}

TEST(KrascalTest, SingleVertex) {
    int V = 1, E = 0;
    Edge* edges = nullptr; // Ребер нет

    int mst_size = 0;
    double total_weight = 0;
    Edge* mst = run_krascal(edges, V, E, &mst_size, &total_weight);

    EXPECT_EQ(mst_size, 0);
    EXPECT_DOUBLE_EQ(total_weight, 0.0);

    free(mst);
}

TEST(KrascalTest, DisconnectedGraph) {
    int V = 4, E = 2;
    // Ребра: (0-1) и (2-3). Связи между ними нет.
    Edge edges[] = {
        {0, 1, 1.0},
        {2, 3, 2.0}
    };

    int mst_size = 0;
    double total_weight = 0;
    Edge* mst = run_krascal(edges, V, E, &mst_size, &total_weight);

    EXPECT_EQ(mst_size, 2);
    EXPECT_DOUBLE_EQ(total_weight, 3.0);

    free(mst);
}

TEST(KrascalTest, ParallelEdges) {
    int V = 2, E = 3;
    Edge edges[] = {
        {0, 1, 10.0},
        {0, 1, 2.0},
        {0, 1, 5.0}
    };

    int mst_size = 0;
    double total_weight = 0;
    Edge* mst = run_krascal(edges, V, E, &mst_size, &total_weight);

    EXPECT_EQ(mst_size, 1);
    EXPECT_DOUBLE_EQ(total_weight, 2.0);

    free(mst);
}
