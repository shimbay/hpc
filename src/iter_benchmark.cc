#include <benchmark/benchmark.h>

#include <cstddef>

#include "iter.h"

static void Arg_Iter(benchmark::internal::Benchmark *b) {
  for (int i : {100, 1000, 10000}) {
    b = b->Args({i});
  }
}

static void BM_VecIter(benchmark::State &state) {
  VecIter vi(state.range(0));
  size_t total = 0;
  for (auto _ : state) {
    total += vi.Iter();
  }
  printf("total: %ld\n", total);
}

BENCHMARK(BM_VecIter)->Apply(Arg_Iter);

static void BM_ListIter(benchmark::State &state) {
  size_t total = 0;
  ListIter li(state.range(0));
  for (auto _ : state) {
    total += li.Iter();
  }
  printf("total: %ld\n", total);
}

BENCHMARK(BM_ListIter)->Apply(Arg_Iter);
