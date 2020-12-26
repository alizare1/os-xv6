#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"



int
main(int argc, char *argv[])
{
  int i = 0;

  semaphore_initialize(i, 1, 0);
  semaphore_acquire(i);
  if (fork() == 0) {
      semaphore_acquire(i);
      printf(1, "Child got the semaphore\n");
      semaphore_release(i);
      exit();
  }
  if (fork() == 0) {
      semaphore_acquire(i);
      printf(1, "Child got the semaphore\n");    
      semaphore_release(i);
      exit();
  }
  printf(1, "Parent got the semaphore\n");
  sleep(100);
  semaphore_release(i);
  wait();
  wait();
  exit();
}