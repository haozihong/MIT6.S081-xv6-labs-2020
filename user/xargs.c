#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
  char buf[512], *p;
  memmove(argv, argv + 1, (argc - 1) * sizeof(char *));
  argv[argc-1] = buf;
  
  p = buf;
  int n;
  do {
    n = read(0, p++, 1);
    if ((n == 0  || p[-1] == '\n') && (p-1 != buf)) {
      p[-1] = 0;
      if (fork() == 0) {
        exec(argv[0], argv);
        exit(1);
      }
      wait(0);
      p = buf;
    }
  } while (n);
  exit(0);
}
