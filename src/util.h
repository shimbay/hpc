#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern const char *__progname;
inline void gdb_print(const void *p, const char *s) {
  char dbx[256];

  printf("GDB print ==> struct: %s, ptr: %p\n", s, p);
  sprintf(dbx,
          "echo 'where\n detach' | gdb -q --batch -ex \"p (struct %s)*%p\n\" "
          "%s %d 2>/dev/null",
          s, p, __progname, getpid());
  system(dbx);
}
