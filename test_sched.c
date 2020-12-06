#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int
main(int argc, char *argv[])
{
  int i,j,k,pid;

  for (i = 0; i < 3; i++) {
    pid = fork();
    if (pid == 0) {
      for(j = 0; j < 100000000; j++)
        for(k = 0;k < 10000000; k++)
          pid = j*j*j/j;
    }
  }
  while(wait());

  exit();
}