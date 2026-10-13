// Q1: Shared-address-space thread test for xv6-riscv.
#include "kernel/types.h"
#include "user/user.h"

#define NTHREADS 3
#define ITERATIONS 100000
#define STACK_SIZE 4096

volatile int counter = 0;

void worker(void *arg)
{
  int i;
  int id = *(int *)arg;
  for(i = 0; i < ITERATIONS; i++)
    counter++; // Deliberately unsynchronized: race expected.
  printf("thread %d finished\n", id);
  exit(0);
}

int main(void)
{
  void *stacks[NTHREADS];
  int ids[NTHREADS];
  int i;

  for(i = 0; i < NTHREADS; i++) {
    stacks[i] = malloc(STACK_SIZE);
    if(stacks[i] == 0) {
      printf("threadtest: stack allocation failed\n");
      exit(1);
    }
    ids[i] = i + 1;
    if(clone(worker, &ids[i], stacks[i] + STACK_SIZE) < 0) {
      printf("threadtest: clone failed\n");
      exit(1);
    }
  }
  for(i = 0; i < NTHREADS; i++)
    if(join() < 0)
      printf("threadtest: join failed\n");

  printf("Final counter = %d (expected maximum %d; race is intentional)\n",
         counter, NTHREADS * ITERATIONS);
  for(i = 0; i < NTHREADS; i++) free(stacks[i]);
  exit(0);
}
