#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <semaphore.h>

#define SEM_NAME "/task6_semaphore"
#define FILE_NAME "numer.txt"

sem_t *create_semaphore(unsigned int value);
sem_t *open_semaphore();
int get_semaphore_value(sem_t *sem, int *value);
int wait_semaphore(sem_t *sem);
int post_semaphore(sem_t *sem);
int close_semaphore(sem_t *sem);
int unlink_semaphore();

#endif
