#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../include/semaphores.h"
#include "../include/shared_buffer.h"
#include "../include/shared_memory.h"

int main() {
  int shm_fd = open_shared_memory(SHM_NAME, sizeof(SegmentPD));
  if (shm_fd == -1) {
    exit(EXIT_FAILURE);
  }
  SegmentPD* buffer = (SegmentPD*)map_shared_memory(shm_fd, sizeof(SegmentPD));
  if (buffer == NULL) {
    close_shared_memory(shm_fd);
    exit(EXIT_FAILURE);
  }

  sem_t* sem_prod = open_semaphore(SEM_WRITE_TO_SHM);
  sem_t* sem_cons = open_semaphore(SEM_READ_FROM_SHM);
  if (sem_prod == NULL || sem_cons == NULL) {
    unmap_shared_memory(buffer, sizeof(SegmentPD));
    exit(EXIT_FAILURE);
  }

  FILE* file = fopen("./input.txt", "r");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  char item[NELE];
  while (fgets(item, NELE, file) != NULL) {
    sem_wait(sem_prod);
    printf("Wysłano do shm: %s\n", item);
    strncpy(buffer->bufor[buffer->wstaw], item, NELE);
    buffer->wstaw = (buffer->wstaw + 1) % NBUF;
    sem_post(sem_cons);

    sleep(rand() % 2);
  }
  // sleep(2);
  // buffer->wstaw = -1;

  fclose(file);

  close_semaphore(sem_prod);
  close_semaphore(sem_cons);
  unmap_shared_memory(buffer, sizeof(SegmentPD));
  close_shared_memory(shm_fd);

  return 0;
}