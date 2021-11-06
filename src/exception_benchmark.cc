#include <exception>
#include <stdexcept>

#include "benchmark/benchmark.h"

const int randomRange = 2;  // Give me a number between 0 and 2.
const int errorInt = 0;     // Stop every time the number is 0.

template <class T>
class Expected {
 private:
  // Our union of value and error. Only one of these can exist in any `Expected`
  // object created.
  union {
    T m_value;
    std::exception m_exception;
  };

 public:
  // Instantiate the `Expected` object with the successfully created value.
  Expected(const T& value) { m_value = value; }

  // Instantiate the `Expected` object with an exception.
  Expected(const std::exception& ex) { m_exception = ex; }

  // Was there an error?
  bool hasError();

  // Access the value.
  T value() { return m_value; }

  // Access the exception.
  std::exception error() { return m_exception; }
};

int getRandom() { return random() % randomRange; }

// 1.
void exitWithBasicException() {
  if (getRandom() == errorInt) {
    throw -2;
  }
}

// 2.
void exitWithMessageException() {
  if (getRandom() == errorInt) {
    throw std::runtime_error("Halt! Who goes there?");
  }
}

// 3.
void exitWithReturn() {
  if (getRandom() == errorInt) {
    return;
  }
}

// 4.
int exitWithErrorCode() {
  if (getRandom() == errorInt) {
    return -1;
  }
  return 0;
}

// 5. Expected! Testcase 5 function.
Expected<int> exitWithExpected() {
  if (getRandom() == errorInt) {
    return std::runtime_error();  //  Return; don't throw!
  }
  return 0;
}

// 1.
void BM_exitWithBasicException(benchmark::State& state) {
  for (auto _ : state) {
    try {
      exitWithBasicException();
    } catch (int ex) {
      // Caught! Carry on next iteration.
    }
  }
}
// 2.
void BM_exitWithMessageException(benchmark::State& state) {
  for (auto _ : state) {
    try {
      exitWithMessageException();
    } catch (const std::runtime_error& ex) {
      // Caught! Carry on next iteration.
    }
  }
}
// 3.
void BM_exitWithReturn(benchmark::State& state) {
  for (auto _ : state) {
    exitWithReturn();
  }
}
// 4.
void BM_exitWithErrorCode(benchmark::State& state) {
  for (auto _ : state) {
    auto err = exitWithErrorCode();
    if (err < 0) {
      // `handle_error()` ...
    }
  }
}

// Add the tests.
BENCHMARK(BM_exitWithBasicException);
BENCHMARK(BM_exitWithMessageException);
BENCHMARK(BM_exitWithReturn);
BENCHMARK(BM_exitWithErrorCode);

// Run the tests!
BENCHMARK_MAIN();
