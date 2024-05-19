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
    close_shared_memory(shm_fd);
    exit(EXIT_FAILURE);
  }

  int output_file = open("./output.txt", O_WRONLY | O_TRUNC);
  if (output_file == -1) {
    perror("open output_file");
    exit(EXIT_FAILURE);
  }

  char item[NELE];
  while (buffer->wstaw != -1) {
    sem_wait(sem_cons);
    strncpy(item, buffer->bufor[buffer->wyjmij], NELE);
    buffer->wyjmij = (buffer->wyjmij + 1) % NBUF;
    printf("Odebrano z shm: %s\n", item);
    // item[NELE - 1] = '\0';
    write(output_file, item, strlen(item));
    sem_post(sem_prod);

    sleep(1);
  }

  close_semaphore(sem_prod);
  close_semaphore(sem_cons);
  unmap_shared_memory(buffer, sizeof(SegmentPD));
  close_shared_memory(shm_fd);
  close(output_file);

  return 0;
}
