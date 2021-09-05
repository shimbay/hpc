#include <gtest/gtest.h>
#include <vector>

#include "image_rotate.h"

class ImageRotateTest : public ::testing::Test {
 public:
  static void SetUpTestSuite() {}

  static void TearDownTestSuite() {}

  static int w;
  static int h;
  static std::vector<int> v;
  static std::vector<int> r;

  static int w1;
  static int h1;
  static std::vector<int> v1;

  static int w2;
  static int h2;
  static std::vector<int> v2;
};

int ImageRotateTest::w = 4;
int ImageRotateTest::h = 3;
std::vector<int> ImageRotateTest::v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
std::vector<int> ImageRotateTest::r{9, 5, 1, 10, 6, 2, 11, 7, 3, 12, 8, 4};

int ImageRotateTest::w1 = 32;
int ImageRotateTest::h1 = 32;
std::vector<int> ImageRotateTest::v1;

int ImageRotateTest::w2 = 512;
int ImageRotateTest::h2 = 512;
std::vector<int> ImageRotateTest::v2;

TEST_F(ImageRotateTest, Init) {
  v1.resize(w1 * h1);
  for (int i = 0; i < v1.size(); i++) {
    v1[i] = i;
  }
  PrintMatrix(v1.data(), w1, h1);
  v2.resize(w2 * h2);
  for (int i = 0; i < v2.size(); i++) {
    v2[i] = i;
  }
  PrintMatrix(v2.data(), w2, h2);
}

TEST_F(ImageRotateTest, TrivialImpl) {
  std::vector<int> output(v.size());
  TrivialImageRotater tir;
  tir.Rotate(v.data(), w, h, output);
  ASSERT_TRUE(output == r);
}

TEST_F(ImageRotateTest, TileImpl) {
  std::vector<int> output(v.size());
  TileImageRotater tir(8, 8);
  tir.Rotate(v.data(), w, h, output);
  ASSERT_TRUE(output == r);
}

TEST_F(ImageRotateTest, TileImpl1) {
  TrivialImageRotater tir1;
  TileImageRotater tir2(8, 8);
  std::vector<int> o1(v1.size());
  tir1.Rotate(v1.data(), w1, h1, o1);
  std::vector<int> o2(v1.size());
  tir2.Rotate(v1.data(), w1, h1, o2);
  ASSERT_TRUE(o1 == o2);
}

TEST_F(ImageRotateTest, TileImpl2) {
  TrivialImageRotater tir1;
  TileImageRotater tir2(8, 8);
  std::vector<int> o1(v2.size());
  tir1.Rotate(v2.data(), w2, h2, o1);
  std::vector<int> o2(v1.size());
  tir2.Rotate(v2.data(), w2, h2, o2);
  ASSERT_TRUE(o1 == o2);
}
