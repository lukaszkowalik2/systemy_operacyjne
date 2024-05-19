#include "semaphores.h"

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

sem_t *create_semaphore(const char *name, unsigned int value) {
  sem_t *sem = sem_open(name, O_CREAT | O_EXCL, 0666, value);
  if (sem == SEM_FAILED) {
    perror("sem_open (create)");
    return NULL;
  }
  return sem;
}

sem_t *open_semaphore(const char *name) {
  sem_t *sem = sem_open(name, 0);
  if (sem == SEM_FAILED) {
    perror("sem_open (open)");
    return NULL;
  }
  return sem;
}

int get_semaphore_value(sem_t *sem, int *value) {
  if (sem_getvalue(sem, value) == -1) {
    perror("sem_getvalue");
    return 0;
  }
  return 1;
}

int wait_semaphore(sem_t *sem) {
  if (sem_wait(sem) == -1) {
    perror("sem_wait");
    return 0;
  }
  return 1;
}

int post_semaphore(sem_t *sem) {
  if (sem_post(sem) == -1) {
    perror("sem_post");
    return 0;
  }
  return 1;
}

int close_semaphore(sem_t *sem) {
  if (sem_close(sem) == -1) {
    perror("sem_close");
    return 0;
  }
  return 1;
}

int unlink_semaphore(const char *name) {
  if (sem_unlink(name) == -1) {
    perror("sem_unlink");
    return 0;
  }
  return 1;
}

sem_wait_status wait_for_semaphore_with_timeout(sem_t *sem, int timeout_sec) {
  struct timespec ts;
  if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
    perror("clock_gettime");
    return SEM_WAIT_ERROR;
  }
  ts.tv_sec += timeout_sec;

  int ret = sem_timedwait(sem, &ts);
  if (ret == 0) {
    return SEM_WAIT_SUCCESS;
  } else if (errno == ETIMEDOUT) {
    return SEM_WAIT_TIMEOUT;
  } else {
    perror("sem_timedwait");
    return SEM_WAIT_ERROR;
  }
}
