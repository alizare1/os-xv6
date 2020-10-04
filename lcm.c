#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int 
gcd(int num1, int num2) {
    int tmp;
    
    while (num2 != 0) {
        tmp = num2;
        num2 = num1 % num2;  
        num1 = tmp;
    }
    return num1;
}

int
main(int argc, char *argv[])
{
  int i, lcm, fd;
  
  if (argc < 2) {
      printf(1, "lcm: No numbers were provided!\n");
      exit();
  }

  lcm = atoi(argv[1]);
  for(i = 2; i < argc; i++)
    lcm = (atoi(argv[i]) * lcm) / gcd(atoi(argv[i]), lcm);

  fd = open("lcm_result.txt", O_CREATE | O_WRONLY);
  printf(fd, "%d\n", lcm);
  close(fd);

  exit();
}