// Q3: User-space deadlock detection and Banker's safety test.
#include "kernel/types.h"
#include "user/user.h"

#define N 5
#define M 3

int allocation[N][M] = {
  {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
};
int request[N][M] = {
  {0, 0, 0}, {2, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 0, 2}
};
int available[M] = {0, 0, 0};

int can_finish(int p, int work[M])
{
  int j;
  for(j = 0; j < M; j++) if(request[p][j] > work[j]) return 0;
  return 1;
}

void print_state(int work[M], int finish[N])
{
  int i, j;
  printf("Available:");
  for(j = 0; j < M; j++) printf(" %d", work[j]);
  printf("\nUnfinished processes:");
  for(i = 0; i < N; i++) if(!finish[i]) printf(" P%d", i);
  printf("\n");
}

int detect_deadlock(void)
{
  int work[M], finish[N], i, j, progress, deadlocked = 0;
  for(j = 0; j < M; j++) work[j] = available[j];
  for(i = 0; i < N; i++) {
    finish[i] = 1;
    for(j = 0; j < M; j++) if(allocation[i][j] != 0) finish[i] = 0;
  }
  do {
    progress = 0;
    for(i = 0; i < N; i++) if(!finish[i] && can_finish(i, work)) {
      printf("P%d can finish; release its allocation\n", i);
      for(j = 0; j < M; j++) work[j] += allocation[i][j];
      finish[i] = 1;
      progress = 1;
      print_state(work, finish);
    }
  } while(progress);
  for(i = 0; i < N; i++) if(!finish[i]) {
    printf("Deadlocked process: P%d\n", i);
    deadlocked++;
  }
  if(!deadlocked) printf("No deadlock detected\n");
  return deadlocked;
}

int is_safe_state(int alloc[N][M], int max[N][M], int avail[M])
{
  int work[M], finish[N], need[N][M], i, j, found, count = 0;
  for(j = 0; j < M; j++) work[j] = avail[j];
  for(i = 0; i < N; i++) {
    finish[i] = 0;
    for(j = 0; j < M; j++) need[i][j] = max[i][j] - alloc[i][j];
  }
  while(count < N) {
    found = 0;
    for(i = 0; i < N; i++) if(!finish[i]) {
      for(j = 0; j < M && need[i][j] <= work[j]; j++);
      if(j == M) {
        for(j = 0; j < M; j++) work[j] += alloc[i][j];
        finish[i] = 1; count++; found = 1;
        printf("Banker: P%d can finish\n", i);
      }
    }
    if(!found) return 0;
  }
  return 1;
}

int main(void)
{
  int alloc[N][M] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
  int max[N][M] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
  int avail[M] = {3,3,2};
  printf("=== Deadlock detection test ===\n");
  detect_deadlock();
  printf("=== Banker's algorithm test ===\n");
  if(is_safe_state(alloc, max, avail)) printf("State is SAFE\n");
  else printf("State is UNSAFE\n");
  exit(0);
}
