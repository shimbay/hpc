#include <benchmark/benchmark.h>

#include "iter.h"

static void Arg_Iter(benchmark::internal::Benchmark *b) {
  for (int i : {100, 1000, 10000}) {
    b = b->Args({i});
  }
}

static void BM_VecIter(benchmark::State &state) {
  VecIter vi(state.range(0));
  int64_t t = 0;
  for (auto _ : state) {
    t = vi.Iter();
  }
}

BENCHMARK(BM_VecIter)->Apply(Arg_Iter);

static void BM_ListIter(benchmark::State &state) {
  ListIter li(state.range(0));
  for (auto _ : state) {
    li.Iter();
  }
}

BENCHMARK(BM_ListIter)->Apply(Arg_Iter);
