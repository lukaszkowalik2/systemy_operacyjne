#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define NELE 20
#define NBUF 5

typedef struct {
  char bufor[NBUF][NELE];
  int wstaw, wyjmij;
} SegmentPD;

int main() {
  int des = shm_open("/segment", O_RDWR | O_CREAT, 0777);
  if (des == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }

  SegmentPD *wpd = (SegmentPD *)mmap(NULL, sizeof(SegmentPD), PROT_READ | PROT_WRITE, MAP_SHARED, des, 0);
  if (wpd == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  char line[NELE];
  file = fopen("input.txt", "r");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while (fgets(line, NELE, file) != NULL) {
    while (wpd->wstaw - wpd->wyjmij == NBUF) {
      printf("Nie pobiera\n");
      sleep(1);
    }
    strncpy(wpd->bufor[wpd->wstaw % NBUF], line, NELE);
    wpd->wstaw++;
  }

  munmap(wpd, sizeof(SegmentPD));
  close(des);
  exit(EXIT_SUCCESS);
}