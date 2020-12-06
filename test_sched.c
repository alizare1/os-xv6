#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int
main(int argc, char *argv[])
{
  int i,j,pid;

  for (i = 0; i < 3; i++) {
    pid = fork();
    if (pid == 0) {
      for(j = 0; j < 100000000; j++)
        i = j*j*j/j;
      
      exit();
    }
  }

  exit();
}