#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

extern const char *__progname;
inline void gdb_print(const void *p, const char *s, bool hex = false) {
  char dbx[256];

  std::string x{};
  if (hex) {
    x = "/x";
  }
  sprintf(dbx,
          "echo 'where\n detach' | gdb -q --batch -ex \"p%s (struct %s)*%p\n\" "
          "%s %d 2>/dev/null",
          x.data(), s, p, __progname, getpid());
  system(dbx);
}
