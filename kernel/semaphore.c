// Q2 reference implementation sketch for xv6-riscv.
// NOTE: validate against the lock/sleep semantics of YOUR xv6 version.
// In standard xv6-riscv, acquire/release are spinlock primitives, and
// sleep(chan, lk) atomically releases lk while sleeping and reacquires it.
#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"
#include "semaphore.h"

static struct {
  struct spinlock lk;
  struct semaphore sem[NSEMAPHORES];
} semtab;

void
semaphores_init(void)
{
  int i;
  initlock(&semtab.lk, "semtab");
  for(i = 0; i < NSEMAPHORES; i++) {
    semtab.sem[i].value = 0;
    semtab.sem[i].initialized = 0;
  }
}

int
semaphore_init(int sem_id, int value)
{
  if(sem_id < 0 || sem_id >= NSEMAPHORES || value < 0)
    return -1;
  acquire(&semtab.lk);
  semtab.sem[sem_id].value = value;
  semtab.sem[sem_id].initialized = 1;
  wakeup(&semtab.sem[sem_id]);
  release(&semtab.lk);
  return 0;
}

int
semaphore_wait(int sem_id)
{
  if(sem_id < 0 || sem_id >= NSEMAPHORES)
    return -1;
  acquire(&semtab.lk);
  if(!semtab.sem[sem_id].initialized) {
    release(&semtab.lk);
    return -1;
  }
  while(semtab.sem[sem_id].value == 0)
    sleep(&semtab.sem[sem_id], &semtab.lk);
  semtab.sem[sem_id].value--;
  release(&semtab.lk);
  return 0;
}

int
semaphore_signal(int sem_id)
{
  if(sem_id < 0 || sem_id >= NSEMAPHORES)
    return -1;
  acquire(&semtab.lk);
  if(!semtab.sem[sem_id].initialized) {
    release(&semtab.lk);
    return -1;
  }
  semtab.sem[sem_id].value++;
  wakeup(&semtab.sem[sem_id]);
  release(&semtab.lk);
  return 0;
}
