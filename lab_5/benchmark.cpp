#include <benchmark/benchmark.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include "krascal.h"

using namespace std;

vector<Edge> generateGraphEdges(int n, int m) {
    vector<Edge> edges;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(1, 100);
    uniform_int_distribution<int> vert(0, n - 1);

    for (int i = 0; i < m; ++i) {
        edges.push_back({vert(rng), vert(rng), (double)dist(rng)});
    }
    return edges;
}

void MyKrascalBenchmark(benchmark::State &state) {
    int n = state.range(0);
    int m = n * 4;

    auto edges_data = generateGraphEdges(n, m);

    for (auto _ : state) {
        int mst_size = 0;
        double total_weight = 0;

        vector<Edge> temp_edges = edges_data;

        Edge* result = run_krascal(temp_edges.data(), n, m, &mst_size, &total_weight);

        benchmark::DoNotOptimize(result);
        free(result);
    }
    state.SetComplexityN(n);
}
BENCHMARK(MyKrascalBenchmark)->RangeMultiplier(10)->Range(100, 10000)->Complexity();


void KrascalStandardBenchmark(benchmark::State &state) {
    int n = state.range(0);
    int m = n * 4;

    auto edges_data = generateGraphEdges(n, m);

    for (auto _ : state) {
        sort(edges_data.begin(), edges_data.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        auto find = [&](auto self, int v) -> int {
            if (v == parent[v]) return v;
            return parent[v] = self(self, parent[v]);
        };

        int edges_count = 0;
        for (const auto& e : edges_data) {
            int root_u = find(find, e.src);
            int root_v = find(find, e.dest);
            if (root_u != root_v) {
                parent[root_u] = root_v;
                edges_count++;
                if (edges_count == n - 1) break;
            }
        }
        benchmark::DoNotOptimize(edges_count);
    }
    state.SetComplexityN(n);
}
BENCHMARK(KrascalStandardBenchmark)->RangeMultiplier(10)->Range(100, 10000)->Complexity();

BENCHMARK_MAIN();