#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/semaphores.h"
#include "../include/shared_buffer.h"
#include "../include/shared_memory.h"

void cleanup() {
  unlink_semaphore(SEM_WRITE_TO_SHM);
  unlink_semaphore(SEM_READ_FROM_SHM);
  unlink_shared_memory(SHM_NAME);
}

void handle_sigint(int sig) {
  cleanup();
  exit(EXIT_FAILURE);
}

int main() {
  atexit(cleanup);
  signal(SIGINT, handle_sigint);

  int shm_fd = create_shared_memory(SHM_NAME, sizeof(SegmentPD));
  if (shm_fd == -1) {
    perror("create_shared_memory");
    exit(EXIT_FAILURE);
  }
  SegmentPD* buffer = (SegmentPD*)map_shared_memory(shm_fd, sizeof(SegmentPD));
  if (buffer == NULL) {
    close_shared_memory(shm_fd);
    exit(EXIT_FAILURE);
  }

  buffer->wstaw = 0;
  buffer->wyjmij = 0;

  sem_t* sem_prod = create_semaphore(SEM_WRITE_TO_SHM, NBUF);
  sem_t* sem_cons = create_semaphore(SEM_READ_FROM_SHM, 0);
  if (sem_prod == NULL || sem_cons == NULL) {
    perror("create_semaphore");
    exit(EXIT_FAILURE);
  }

  pid_t write_to_shm_pid = fork();
  switch (write_to_shm_pid) {
    case -1: {
      perror("fork write_to_shm");
      break;
    }
    case 0: {
      int status = execlp("./output/write_to_shm", "./output/write_to_shm", NULL);
      if (status == -1) {
        perror("execlp write_to_shm");
        exit(EXIT_FAILURE);
      }
      break;
    }
  }

  pid_t read_from_shm_pid = fork();
  switch (read_from_shm_pid) {
    case -1: {
      perror("fork read_from_shm");
      break;
    }
    case 0: {
      int status = execlp("./output/read_from_shm", "./output/read_from_shm", NULL);
      if (status == -1) {
        perror("execlp read_from_shm");
        exit(EXIT_FAILURE);
      }
      break;
    }
  }

  wait(NULL);
  wait(NULL);

  close_semaphore(sem_prod);
  close_semaphore(sem_cons);
  unmap_shared_memory(buffer, sizeof(SegmentPD));
  close_shared_memory(shm_fd);

  return 0;
}
