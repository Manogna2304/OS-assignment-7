# OS Lab Assignment 7 — Submission Package (xv6-riscv)

This package contains the four user-space test programs and supporting submission documents for the assignment PDF.

## Contents
- `user/threadtest.c` — Q1 shared-counter thread test
- `user/synctest.c` — Q2 semaphore counter and bounded-buffer Producer–Consumer test
- `user/deadlock.c` — Q3 resource-matrix deadlock detection and Banker's safety test
- `user/priotest.c` — Q4 priority scheduler test
- `KERNEL_INTEGRATION_CHECKLIST.md` — kernel changes and syscall wiring that must be completed
- `REPORT_TEMPLATE.md` — 2–3 page report draft; replace placeholders with your real results
- `SUBMISSION_CHECKLIST.md` — final deliverables checklist
- `MAKEFILE_SNIPPET.txt` — `UPROGS` entries

## Critical status note
This is **not a drop-in, fully implemented kernel patch**. The programs rely on kernel changes that must exist in your `~/xv6-riscv` tree. Do not claim that a test passed until you run it in QEMU and record the actual output. In particular, Q1 needs correct shared-address-space thread semantics; Q2 needs working blocking semaphores; Q3's included program tests matrix algorithms but does not yet demonstrate a live circular wait using two real xv6 processes and pipes; Q4 needs scheduler changes and aging in the kernel.

## Install user programs
From Ubuntu/WSL2, after extracting this ZIP and adjusting the path to where you extracted it:

```sh
cd ~/xv6-riscv
cp /path/to/OS_Lab_Assignment_7_Submission/user/*.c user/
```

Add the lines in `MAKEFILE_SNIPPET.txt` to the `UPROGS` list in `Makefile`, preserving the existing backslash formatting. Then:

```sh
make clean
make
make qemu
```

At the xv6 shell, run one test at a time:

```text
threadtest
synctest
deadlock
priotest
```

Save genuine terminal screenshots for each question. If the kernel implementation is incomplete, the build or tests may fail; resolve those errors before submission.
