#include <cassert>
#include <string>
#include <vector>

#include "common.h"

class ImageRotater {
 public:
  virtual HPCStatus Rotate(const int *input, int width, int height,
                           std::vector<int> &output) = 0;

  virtual ~ImageRotater() = default;
};

class TrivialImageRotater : public ImageRotater {
 public:
  TrivialImageRotater() = default;

  ~TrivialImageRotater() = default;

  HPCStatus Rotate(const int *input, int width, int height,
                   std::vector<int> &output) {
    output.resize(width * height);

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        output[j * height + height - 1 - i] = input[i * width + j];
      }
    }

    return kHPCStatusOK;
  };
};

class TileImageRotater : public ImageRotater {
 public:
  TileImageRotater(int width_tile_size, int height_tile_size)
      : width_tile_size_(width_tile_size), height_tile_size_(height_tile_size) {
    assert(width_tile_size_ > 0);
    assert(height_tile_size_ > 0);
  };

  ~TileImageRotater() = default;

  void RotateKernal(const int *input, int width, int height, int w_start, int h_start,
                    int w_max, int h_max, int *output) {
    for (int hi = h_start; hi < h_max; hi++) {
      for (int wi = w_start; wi < w_max; wi++) {
        output[wi * height + height - 1 - hi] = input[hi * width + wi];
      }
    }
  };

  HPCStatus Rotate(const int *input, int width, int height,
                   std::vector<int> &output) {
    output.resize(width * height);

    for (int i = 0; i < height; i = i + height_tile_size_) {
      int h_max = std::min(height, i + height_tile_size_);
      for (int j = 0; j < width; j = j + width_tile_size_) {
        int w_max = std::min(width, j + width_tile_size_);
        RotateKernal(input, width, height, j, i, w_max, h_max, output.data());
      }
    }

    return kHPCStatusOK;
  };

 private:
  int width_tile_size_ = 0;
  int height_tile_size_ = 0;
};

void PrintMatrix(const int *data, int width, int height);
