#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_trace_syscalls(void)
{
  int state;
  uint prev = ticks;

  if(argint(0, &state) < 0 || state < 0 || state > 1)
    return -1;

  set_trace_state(state);
  

  if (myproc()->pid != 2) {
    cprintf("sys_trace_syscalls: Trace state set to %d\n", state);
    return 1;
  }

  cprintf("\nsys_trace_syscalls: Process ID = 2 started! \nThis process will print traces if state is 1\n\n");
  while(1) {
    if (!get_trace_state())
      continue;
    acquire(&tickslock);
    if (ticks - prev > 500) {
      print_traces();
      prev = ticks;
    }
    release(&tickslock);
  }
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
