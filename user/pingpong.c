#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);
  if (fork() == 0) {
    read(p[0], 0, 1);
    close(p[0]);
    close(p[1]);
    printf("%d: received ping\n", getpid());
  } else {
    write(p[1], " ", 1);
    close(p[0]);
    close(p[1]);
    wait((int *) 0);
    printf("%d: received pong\n", getpid());
  }
  exit(0);
}
