#include <utility>

template <int i, int j>
inline void IntSwap(int* data) {
  if (data[i] > data[j]) std::swap(data[i], data[j]);
}

template <int i, int j>
inline void IntBubbleSortLoop(int* data) {
  IntSwap<j, j + 1>(data);
  IntBubbleSortLoop < j < i - 1 ? i : 0, j<i - 1 ? (j + 1) : 0>(data);
}
template <>
inline void IntBubbleSortLoop<0, 0>(int*) {}

template <int n>
inline void IntBubbleSort(int* data) {
  IntBubbleSortLoop<n - 1, 0>(data);
  IntBubbleSort<n - 1>(data);
}

template <>
inline void IntBubbleSort<1>(int* data) {}

inline void bubbleSort4(int* data) {
#define COMP_SWAP(i, j) \
  if (data[i] > data[j]) std::swap(data[i], data[j])
  COMP_SWAP(0, 1);
  COMP_SWAP(1, 2);
  COMP_SWAP(2, 3);
  COMP_SWAP(0, 1);
  COMP_SWAP(1, 2);
  COMP_SWAP(0, 1);
}
