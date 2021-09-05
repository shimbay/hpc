#include <benchmark/benchmark.h>

#include "image_rotate.h"

static void Arg_WH(benchmark::internal::Benchmark *b) {
  for (int i : {64, 128, 256, 512}) {
    b = b->Args({i, i});
  }
}

static void BM_TrivialImpl(benchmark::State &state) {
  TrivialImageRotater tir;
  const int w = state.range(0);
  const int h = state.range(1);
  std::vector<int> v(w * h);
  std::vector<int> o(w * h);
  // Perform setup here
  for (auto _ : state) {
    tir.Rotate(v.data(), w, h, o);
  }
}

BENCHMARK(BM_TrivialImpl)->Apply(Arg_WH);

static void BM_TileImpl(benchmark::State &state) {
  TileImageRotater tir(4, 4);
  const int w = state.range(0);
  const int h = state.range(1);
  std::vector<int> v(w * h);
  std::vector<int> o(w * h);
  for (auto _ : state) {
    tir.Rotate(v.data(), w, h, o);
  }
}

BENCHMARK(BM_TileImpl)->Apply(Arg_WH);
