#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define NELE 20
#define NBUF 5

typedef struct {
  char bufor[NBUF][NELE];
  int wstaw, wyjmij;
} SegmentPD;

int main() {
  int des = shm_open("/segment", O_RDWR, 0777);
  if (des == -1) {
    perror("shm_open");
    exit(EXIT_FAILURE);
  }
  SegmentPD *wpd = (SegmentPD *)mmap(NULL, sizeof(SegmentPD), PROT_READ | PROT_WRITE, MAP_SHARED, des, 0);

  FILE *file;
  char line[NELE];
  file = fopen("output.txt", "w");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while (1) {
    while (wpd->wstaw == wpd->wyjmij) {
      printf("Nie wstawia\n");
      sleep(1);
    }
    fprintf(file, "%s", wpd->bufor[wpd->wyjmij % NBUF]);
    wpd->wyjmij++;
  }

  fclose(file);
  munmap(wpd, sizeof(SegmentPD));
  close(des);
}