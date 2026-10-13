// Q4: Priority scheduler test. Lower numeric value means higher priority.
#include "kernel/types.h"
#include "user/user.h"

#define CHILDREN 4
#define WORK 12000000

int main(void)
{
  int priorities[CHILDREN] = {2, 6, 12, 20};
  int i, pid;
  for(i = 0; i < CHILDREN; i++) {
    pid = fork();
    if(pid < 0) { printf("priotest: fork failed\n"); exit(1); }
    if(pid == 0) {
      int j;
      int mypid = getpid();
      if(set_priority(mypid, priorities[i]) < 0) {
        printf("child pid %d: set_priority failed\n", mypid);
        exit(1);
      }
      printf("child pid %d started with priority %d\n", mypid, get_priority(mypid));
      volatile unsigned long x = 0;
      for(j = 0; j < WORK; j++) x += (unsigned long)j;
      printf("child pid %d completed, priority now %d\n", mypid, get_priority(mypid));
      exit(0);
    }
  }
  for(i = 0; i < CHILDREN; i++) wait(0);
  printf("priotest: all children completed\n");
  exit(0);
}
