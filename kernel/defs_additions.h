// Merge into kernel/defs.h in the appropriate declaration section.
void semaphores_init(void);
int semaphore_init(int sem_id, int value);
int semaphore_wait(int sem_id);
int semaphore_signal(int sem_id);

// If your clone/join and priority implementations use helpers, declare those
// helpers here as appropriate for the exact implementation.
