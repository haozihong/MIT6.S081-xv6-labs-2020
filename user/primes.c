#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p = 1;
  if (argc > 1) {
    if(!read(0, &p, 4)) exit(0);
  }
  if (p != 1) printf("prime %d\n", p);

  int ps[2];
  pipe(ps);
  if (fork() == 0) {
    char *argv[] = { "primes", "", 0 };
    close(0);
    dup(ps[0]);
    close(ps[0]);
    close(ps[1]);
    exec("primes", argv);
    exit(1);
  }
  close(ps[0]);
  if (p == 1) {
    for (int i = 2; i <= 35; i++) {
      write(ps[1], &i, 4);
    }
  } else {
    int n;
    while (read(0, &n, 4)) {
      if (n % p != 0)
        write(ps[1], &n, 4);
    }
  }
  close(ps[1]);
  while (wait(0) != -1);

  exit(0);
}

