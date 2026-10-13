// Q2: Semaphore-protected counter and bounded-buffer Producer/Consumer test.
#include "kernel/types.h"
#include "user/user.h"

#define NTHREADS 3
#define ITERATIONS 100000
#define STACK_SIZE 4096
#define BUFFER_SIZE 5
#define ITEMS 12

volatile int counter = 0;
int counter_ids[NTHREADS];
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void counter_worker(void *arg)
{
  int i, id = *(int *)arg;
  for(i = 0; i < ITERATIONS; i++) {
    sem_wait(0);
    counter++;
    sem_signal(0);
  }
  printf("counter thread %d finished\n", id);
  exit(0);
}

void producer(void *arg)
{
  int i;
  (void)arg;
  for(i = 1; i <= ITEMS; i++) {
    sem_wait(1);             // empty slots
    sem_wait(3);             // mutex
    buffer[in] = i;
    in = (in + 1) % BUFFER_SIZE;
    printf("produced %d\n", i);
    sem_signal(3);
    sem_signal(2);           // full slots
  }
  exit(0);
}

void consumer(void *arg)
{
  int i, item;
  (void)arg;
  for(i = 0; i < ITEMS; i++) {
    sem_wait(2);             // full slots
    sem_wait(3);             // mutex
    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("consumed %d\n", item);
    sem_signal(3);
    sem_signal(1);           // empty slots
  }
  exit(0);
}

int main(void)
{
  void *stacks[NTHREADS];
  int i;
  sem_init(0, 1); // counter mutex
  sem_init(1, BUFFER_SIZE); // empty
  sem_init(2, 0); // full
  sem_init(3, 1); // producer-consumer mutex

  for(i = 0; i < NTHREADS; i++) {
    stacks[i] = malloc(STACK_SIZE);
    if(stacks[i] == 0) { printf("synctest: malloc failed\n"); exit(1); }
    counter_ids[i] = i + 1;
    if(clone(counter_worker, &counter_ids[i], stacks[i] + STACK_SIZE) < 0) {
      printf("synctest: clone failed\n"); exit(1);
    }
  }
  for(i = 0; i < NTHREADS; i++) join();
  printf("Synchronized final counter = %d (expected %d)\n", counter, NTHREADS * ITERATIONS);
  for(i = 0; i < NTHREADS; i++) free(stacks[i]);

  // Run producer/consumer sequentially as separate processes/threads.
  // Each gets its own stack; join after both finish.
  {
    void *ps = malloc(STACK_SIZE), *cs = malloc(STACK_SIZE);
    if(ps == 0 || cs == 0) { printf("synctest: buffer test stack allocation failed\n"); exit(1); }
    if(clone(producer, 0, ps + STACK_SIZE) < 0 || clone(consumer, 0, cs + STACK_SIZE) < 0) {
      printf("synctest: producer/consumer clone failed\n"); exit(1);
    }
    join(); join();
    free(ps); free(cs);
  }
  exit(0);
}
