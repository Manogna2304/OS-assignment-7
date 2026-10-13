# OS Lab Assignment 7 — xv6-riscv

**Name:** Manogna  
**Roll Number:** 2401MC46  
**Environment:** Ubuntu/WSL2 with QEMU

## Overview

This assignment explores process and thread management, synchronization, deadlock handling, and priority-based CPU scheduling in xv6-riscv.

The assignment consists of four parts:

1. **User-Level Threads:** Implement `clone()` and `join()` for thread creation and management.
2. **Semaphores and Producer–Consumer:** Implement semaphore operations and use them to synchronize shared data and coordinate producer–consumer processes.
3. **Deadlock Detection and Banker’s Algorithm:** Detect deadlocks, calculate resource requirements, and determine whether a system state is safe.
4. **Priority Scheduling with Aging:** Implement priority-based CPU scheduling and aging to prevent process starvation.

## Repository Structure

```text
OS-assignment-7/
├── REPORT.md
└── user/
    ├── threadtest.c
    ├── synctest.c
    ├── deadlock.c
    └── priotest.c
```

## Test Programs

### Q1 — User-Level Threads (`threadtest.c`)

- Creates three threads sharing a counter.
- Each thread increments the counter 100,000 times.
- Demonstrates race conditions caused by unsynchronized access.
- Maximum expected counter value: `300000`.

### Q2 — Semaphores (`synctest.c`)

- Uses a mutex semaphore to protect a shared counter.
- Implements Producer–Consumer synchronization using a circular buffer of size five.
- Uses `empty`, `full`, and `mutex` semaphores.
- Expected synchronized counter value: `300000`.

### Q3 — Deadlock Detection (`deadlock.c`)

- Detects deadlocks using allocation, request, and available-resource matrices.
- Implements Banker’s safety algorithm.
- Calculates `Need = Max - Allocation`.
- Checks whether resource allocation leaves the system in a safe state.

### Q4 — Priority Scheduling (`priotest.c`)

- Creates four CPU-bound child processes.
- Assigns priorities `2`, `6`, `12`, and `20`.
- Uses lower numerical values to represent higher priorities.
- Tests scheduling behavior and priority aging.

## Build and Execution

Run the following commands from the root of your modified xv6-riscv source directory:

```bash
make clean
make
make qemu
```

Execute the test programs from the xv6 shell:

```text
threadtest
synctest
deadlock
priotest
```

These commands require the corresponding programs to be registered in the Makefile and the necessary kernel changes and system calls to be implemented.

## Expected Deliverables

- Modified xv6-riscv kernel source files.
- System-call implementations and user-space declarations.
- Four test programs.
- `REPORT.md` containing implementation details and verified results.
- Screenshots demonstrating the execution of each question.

## Conclusion

This assignment demonstrates operating-system concepts involving threads, synchronization, deadlock handling, and CPU scheduling. All implementation details and results should be verified against the final xv6-riscv source and actual QEMU execution output.
