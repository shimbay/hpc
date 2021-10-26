#include <cstdio>

#include "util.h"

class Test {
 public:
  int a;
  int b;
};

int main() {
  printf("Hello World!\n");
  Test t{};
  gdb_print(&t, "Test");
}
