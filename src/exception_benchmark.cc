#include <exception>
#include <stdexcept>

#include "benchmark/benchmark.h"
#include "nonstd/expected.hpp"

const int randomRange = 2;  // Give me a number between 0 and 2.
const int errorInt = -1;    // Stop every time the number is 0.

int getRandom() { return random() % randomRange; }

void exitWithBasicException() {
  if (getRandom() == errorInt) {
    throw -2;
  }
}

void exitWithMessageException() {
  if (getRandom() == errorInt) {
    throw std::runtime_error("Halt! Who goes there?");
  }
}

void exitWithReturn() {
  if (getRandom() == errorInt) {
    return;
  }
}

int exitWithErrorCode() {
  if (getRandom() == errorInt) {
    return -1;
  }
  return 0;
}

using namespace nonstd;
expected<int, std::string> exitWithExpected() {
  if (getRandom() == errorInt) {
    return make_unexpected("error");
  }
  return 1;
}

void BM_exitWithBasicException(benchmark::State& state) {
  for (auto _ : state) {
    try {
      exitWithBasicException();
    } catch (int ex) {
      // Caught! Carry on next iteration.
    }
  }
}

void BM_exitWithMessageException(benchmark::State& state) {
  for (auto _ : state) {
    try {
      exitWithMessageException();
    } catch (const std::runtime_error& ex) {
      // Caught! Carry on next iteration.
    }
  }
}

void BM_exitWithReturn(benchmark::State& state) {
  for (auto _ : state) {
    exitWithReturn();
  }
}

void BM_exitWithErrorCode(benchmark::State& state) {
  for (auto _ : state) {
    auto err = exitWithErrorCode();
    if (err < 0) {
      // `handle_error()` ...
    }
  }
}

void BM_exitWithExpected(benchmark::State& state) {
  for (auto _ : state) {
    auto ret = exitWithExpected();
    if (ret.has_exception<std::string>()) {
      // `handle_error()` ...
    }
  }
}

BENCHMARK(BM_exitWithBasicException);
BENCHMARK(BM_exitWithMessageException);
BENCHMARK(BM_exitWithReturn);
BENCHMARK(BM_exitWithErrorCode);
BENCHMARK(BM_exitWithExpected);
