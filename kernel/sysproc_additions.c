// Merge these handler bodies into the existing kernel/sysproc.c.
// Do not replace the entire sysproc.c file with this fragment.
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

// Semaphore handlers.
uint64
sys_sem_init(void)
{
  int id, value;
  if(argint(0, &id) < 0 || argint(1, &value) < 0)
    return -1;
  return semaphore_init(id, value);
}

uint64
sys_sem_wait(void)
{
  int id;
  if(argint(0, &id) < 0)
    return -1;
  return semaphore_wait(id);
}

uint64
sys_sem_signal(void)
{
  int id;
  if(argint(0, &id) < 0)
    return -1;
  return semaphore_signal(id);
}

// Priority handlers.
// These assume the stock xv6 proc[] table and struct proc locks.
// Verify names/visibility in your exact proc.c/proc.h before merging.
uint64
sys_set_priority(void)
{
  int pid, priority;
  struct proc *p;
  if(argint(0, &pid) < 0 || argint(1, &priority) < 0)
    return -1;
  if(priority < 1 || priority > 20)
    return -1;

  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->pid == pid && p->state != UNUSED) {
      p->priority = priority;
      p->wait_ticks = 0;
      release(&p->lock);
      return 0;
    }
    release(&p->lock);
  }
  return -1;
}

uint64
sys_get_priority(void)
{
  int pid;
  struct proc *p;
  if(argint(0, &pid) < 0)
    return -1;

  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->pid == pid && p->state != UNUSED) {
      int priority = p->priority;
      release(&p->lock);
      return priority;
    }
    release(&p->lock);
  }
  return -1;
}
