# OS Lab Assignment 7 — Report

**Name:** Manogna  
**Roll No.:** 2401MC46  
**Environment:** xv6-riscv on Ubuntu/WSL2 with QEMU  
**Date:** [fill in submission date]

## 1. Objective
The objective of this assignment is to implement shared-address-space threads, semaphore-based synchronization, user-space deadlock detection and Banker's safety checking, and priority-based preemptive CPU scheduling with aging in xv6-riscv.

## 2. Q1 — User-Level Threads
The `clone(fcn, arg, stack)` interface creates a thread that runs `fcn(arg)` while sharing user memory with the calling process. Each thread requires its own kernel execution context and user stack. The `join()` interface waits for a thread to terminate and reclaims its process resources.

The test program creates three threads. Each increments a shared global counter 100,000 times. Since the increment operation is not atomic, a race condition can cause a final value below 300,000. This is the expected demonstration for Q1.

**Implementation files:** `kernel/proc.c`, `kernel/proc.h`, syscall plumbing files, `user/threadtest.c` (plus any additional files modified).

**Observed output:** [paste actual QEMU output here]  
**Screenshot:** [insert Q1 screenshot]

## 3. Q2 — Semaphores and Producer–Consumer
The semaphore interface consists of `sem_init`, `sem_wait`, and `sem_signal`. The kernel semaphore table is protected by a lock, and waiting processes sleep until a permit becomes available. The check-and-sleep path must avoid lost wakeups.

The synchronized counter test protects the increment with a mutex semaphore. The expected result is exactly 300,000. The Producer–Consumer test uses a circular buffer of size five and three semaphores: `empty` counts free slots, `full` counts occupied slots, and `mutex` protects buffer indices and data.

**Observed counter output:** [paste actual output]  
**Observed Producer–Consumer output:** [paste actual output]  
**Screenshot:** [insert Q2 screenshot]

## 4. Q3 — Deadlock Detection and Banker's Algorithm
The deadlock detection algorithm starts with `Work = Available`. It finds an unfinished process whose outstanding request can be satisfied, simulates completion, and releases that process's allocated resources back to `Work`. If no more processes can finish, the remaining unfinished processes are reported as deadlocked.

Banker's algorithm computes `Need = Max - Allocation` and checks whether a safe sequence exists before granting a hypothetical request. A request that exceeds `Need` or `Available` must be rejected. If the tentative allocation produces an unsafe state, the request must be rolled back.

**Test 1 — Deadlocked state:** [matrix and actual output]  
**Test 2 — Safe state:** [matrix and actual output]  
**Test 3 — Unsafe after a request:** [request, matrix and actual output]  
**Live pipe/shared-resource circular wait:** [describe and attach output if implemented]  
**Screenshot:** [insert Q3 screenshot]

## 5. Q4 — Priority Scheduling with Aging
Each process has a priority from 1 (highest) to 20 (lowest), with default priority 10. The scheduler selects a RUNNABLE process with the lowest numerical priority and should rotate fairly among processes with equal priority. Aging improves the priority of a process that has waited for more than 30 ticks, reducing its numerical priority by one, down to a minimum of 1.

The test program forks four CPU-bound children with priorities 2, 6, 12, and 20. The output should show the selected priorities and completion behavior. Actual order may vary with implementation and timing, so conclusions must be based on the captured run.

**Observed output and completion order:** [paste actual output]  
**Evidence of aging:** [paste wait-tick/priority changes]  
**Screenshot:** [insert Q4 screenshot]

## 6. Problems encountered and resolutions
- **System-call integration:** [record any syscall-number, declaration, or stub issue and how it was resolved.]
- **Thread address-space lifetime:** [record how shared page tables and cleanup were handled.]
- **Semaphore blocking/wakeup:** [record any synchronization issue and resolution.]
- **Scheduling fairness/aging:** [record how starvation was tested and addressed.]

## 7. Conclusion
The assignment demonstrates the relationship between process management, shared-memory concurrency, synchronization, deadlock handling, and CPU scheduling. Replace every bracketed placeholder with verified results from the final xv6/QEMU run before submitting. Do not report an unimplemented feature as completed.
