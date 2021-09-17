#include "iter.h"

#include <gtest/gtest.h>

class IterTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() {}

  static void TearDownTestSuite() {}
};

TEST_F(IterTest, VecIterTest) {
  VecIter vi(1000);
  int64_t res = vi.Iter();
  ASSERT_TRUE(res == 0);
}

TEST_F(IterTest, ListIterTest) {
  ListIter li(1000);
  int64_t res = li.Iter();
  ASSERT_TRUE(res == 0);
}
