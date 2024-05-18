#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "mylib.h"

#define NELE 20
#define NBUF 5

typedef struct {
  char bufor[NBUF][NELE];
  int wstaw, wyjmij;
} SegmentPD;

int main() {
  int des = shm_open("/segment", O_CREAT | O_RDWR, 0777);
  if (des == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }
  int truncate_status = ftruncate(des, sizeof(SegmentPD));
  if (truncate_status == -1) {
    perror("ftruncate");
    exit(EXIT_FAILURE);
  }
  // SegmentPD *wpd = (SegmentPD *)mmap(NULL, sizeof(SegmentPD), PROT_READ | PROT_WRITE, MAP_SHARED, des, 0);

  int fork_status = fork();

  switch (fork_status) {
    case -1: {
      perror("fork");
      exit(EXIT_FAILURE);
      break;
    }
    case 0: {
      execlp("./output/write_to_shm", "write_to_shm", NULL);
      break;
    }
    default: {
      execlp("./output/read_from_shm", "read_from_shm", NULL);
      wait(NULL);
      break;
    }
  }

  shm_unlink("/segment");
  exit(EXIT_SUCCESS);
}