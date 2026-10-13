// Q2 support header: counting semaphores for xv6-riscv.
// Integrate into your xv6 tree and compile kernel/semaphore.c from kernel/Makefile.
#ifndef XV6_SEMAPHORE_H
#define XV6_SEMAPHORE_H

#define NSEMAPHORES 10

struct semaphore {
  int value;
  int initialized;
  // Semaphore operations must use xv6 sleep(chan, lk)/wakeup(chan)
  // with a lock that is atomically released while sleeping.
};

void semaphores_init(void);
int semaphore_init(int sem_id, int value);
int semaphore_wait(int sem_id);
int semaphore_signal(int sem_id);

#endif
