#include "image_rotate.h"

void PrintMatrix(const int *data, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("%d, ", data[width * i + j]);
    }
    printf("\n");
  }
}
