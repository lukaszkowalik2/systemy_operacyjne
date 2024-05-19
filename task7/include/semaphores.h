#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <semaphore.h>

typedef enum {
  SEM_WAIT_ERROR,
  SEM_WAIT_SUCCESS,
  SEM_WAIT_TIMEOUT
} sem_wait_status;

sem_t *create_semaphore(const char *name, unsigned int value);
sem_t *open_semaphore(const char *name);
int get_semaphore_value(sem_t *sem, int *value);
int wait_semaphore(sem_t *sem);
int post_semaphore(sem_t *sem);
int close_semaphore(sem_t *sem);
int unlink_semaphore(const char *name);
sem_wait_status wait_for_semaphore_with_timeout(sem_t *sem, int timeout_sec);

#endif
