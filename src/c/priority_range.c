#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

static int done = 1;

void task_quit(int sig) {
  done = 0;
}

void ShowSchedulerPolicy() {
  int policy = sched_getscheduler(0);
  switch (policy) {
    case SCHED_OTHER:
      printf("Policy is normal\n");
      break;
    case SCHED_RR:
      printf("Policy is round-robin\n");
      break;
    case SCHED_FIFO:
      printf("Policy is first-in, first-out\n");
      break;
    case -1:
      perror("sched_getscheduler");
      break;
    default:
      fprintf(stderr, "Unknown policy\n");
  }
}

int main() {
  struct sigaction newsig;
  memset(&newsig, 0, sizeof(newsig));
  sigemptyset(&newsig.sa_mask);
  newsig.sa_flags = 0;
  newsig.sa_handler = task_quit;
  sigaction(SIGINT, &newsig, NULL);
  sigaction(SIGTERM, &newsig, NULL);


  ShowSchedulerPolicy();

  int min, max;
  min = sched_get_priority_min(SCHED_FIFO);
  if (min == -1) {
    perror("sched_get_priority_min");
    return 1;
  }

  max = sched_get_priority_max(SCHED_FIFO);
  if (max == -1) {
    perror("sched_get_priority_max");
    return 1;
  }

  printf("SCHED_FIFO priority range is %d - %d\n", min, max);
 
  // absolute value
  /*
  struct sched_param sp = { .sched_priority = 1 };
  int ret = sched_setscheduler(0, SCHED_FIFO, &sp);
  if (ret == -1) {
    perror("sched_setscheduler");
    return 1;
  }*/
  
  // nice value
  int val = nice(0);
  val = 10;
  errno  = 0;
  int ret = nice(val);
  if (ret == -1 && errno != 0) {
    perror("nice");
  } else {
    printf("nice value is now %d\n", ret);
  }

  ShowSchedulerPolicy();
  clock_t last = clock();
  while (done) {
    clock_t current = clock();
    double elapsed = (double)(current - last) / CLOCKS_PER_SEC;
    last = current;
    if (elapsed > 0.5) {
      printf("20 ms timeout\n");
    }
    sleep(0.5);
  }
  return 0;
}
