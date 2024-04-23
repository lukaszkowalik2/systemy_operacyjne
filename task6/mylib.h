#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#ifndef _MYLIB_H_
#define _MYLIB_H_

sem_t create_sem(const char *name) {
  sem_t sem = *sem_open(name, O_CREAT);
  if (&sem == SEM_FAILED) {
    perror("create_sem failed");
    return NULL;
  }

  return sem;
}

sem_t open_sem() {
}

sem_t close_sem_for_proc(sem_t *sem) {
  int sem_status = sem_close(sem);
  if (sem_status == -1) {
  }
}

#endif